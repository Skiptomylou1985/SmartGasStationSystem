using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.Net;
using System.Net.Sockets;
//using System.Windows.Forms.DataVisualization.Charting;

namespace SPManager
{
     partial class FormMain
    {
        int updateCount = 0;
        [DllImport("user32.dll")]
        static extern uint RegisterWindowMessage(string lpString);
        static uint WM_AREACAR = RegisterWindowMessage("AREACAR");
        static uint WM_KILLPROCESS = RegisterWindowMessage("KILLPROCESS");
        static uint WM_HEARTBEAT = RegisterWindowMessage("HEARTBEAT");
        DateTime lastMessageTime = DateTime.Now;
        protected override void DefWndProc(ref Message m)
        {
            if (m.Msg == Convert.ToInt32(WM_AREACAR))
            {
                int areaNo = (int)m.WParam;
                string info = "Main->DefWndProc: 收到动态库视频识别车辆消息，识别区：" +
                    areaNo.ToString() + "  视频通道:" + m.LParam.ToString();
                Global.LogServer.Add(new LogInfo("Debug", info, (int)EnumLogLevel.DEBUG));
                ShowRTBInfo(info);
                GetAreaCarFromDll(areaNo);
                ShowAreaCarList();
            }
            else if (m.Msg == Convert.ToInt32(Global.WM_CARSNAP))
            {
                
                int nNozzleID = (int)m.WParam;
                int nNozzleStatus = (int)m.LParam;
                UpdateStationBoardNozzleControlStatus(nNozzleID, nNozzleStatus);
                ShowRTBInfo("DIT信号:油枪" + nNozzleID.ToString() + " 状态" + nNozzleStatus.ToString());
                Global.LogServer.Add(new LogInfo("Run", "Main->DefWndProc: 收到DIT消息,油枪号：" + nNozzleID.ToString() + "  状态号:"+nNozzleStatus.ToString(), (int)EnumLogLevel.RUN));
                if (Global.nCaptureFlag == 1) //抓拍使能开启，抓拍实时数据
                {
                    ProcSnapFromDIT_Capture(nNozzleID, nNozzleStatus);
                }
                else if(Global.nVideoRecogFlag == 1)
                {
                    ProcSnapFromDIT_WithoutCap(nNozzleID, nNozzleStatus);
                }
                ShowNozzleCarList();
            }
            else 
            {
                base.DefWndProc(ref m);
            }
        }
        #region 系统初始化代码包含 1 数据库 2 日志系统 3 运行参数 4 设备及算法 5 网络服务
        private int Init()
        {
            int ret = 0;
            if (!InitLogServer())
            {
                ret += 1 ;
            }
            if (!InitDatabase())
            {
                ret += 1 << 1;
            }
            
            if (!InitParam())
            {
                ret += 1 << 2;
            }
            if (!InitDev())
            {
                ret += 1 << 4;
            }
            if (!InitAlg())
            {
                ret += 1 << 3;
            }
            
            if (!InitSocket())
            {
                ret += 1 << 5;
            }
            if(!InitPicWork())
            {
                ret += 1 << 6;
            }
            return ret;
        }


        private bool InitDatabase()
        {
            try
            {
                DBInfo info = new DBInfo();
                Global.iniPath = Application.StartupPath + "\\config.ini";
                info.type = INIUnit.GetINIValue(Global.iniPath, "Database", "type");
                info.ip = INIUnit.GetINIValue(Global.iniPath, "Database", "ip");
                info.dbname = INIUnit.GetINIValue(Global.iniPath, "Database", "name");
                info.username = INIUnit.GetINIValue(Global.iniPath, "Database", "username");
                info.password = INIUnit.GetINIValue(Global.iniPath, "Database", "password");
                info.port = int.Parse(INIUnit.GetINIValue(Global.iniPath, "Database", "port"));
                Global.LogServer.Add(new LogInfo("Debug", "main->InitDatabase param value" +
                   Global.iniPath + " " + info.type + " " + info.ip + " " + info.dbname + " " + info.username + " " + info.password, (int)EnumLogLevel.DEBUG));
                Global.mysqlHelper = new MysqlHelper(info);
                
                Global.dllEncoder = INIUnit.GetINIValue(Global.iniPath, "main", "encode");
            }
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main:InitDatabase 初始化数据库失败:" + ex.Message,(int)EnumLogLevel.ERROR));
                return false;
            }
            return true;
        }
       
        #endregion

        #region 获取，处理数据

        private void ProcSnapFromDIT_WithoutCap(int nozzleNo, int nozzleStatus)
        {
            
            foreach (ClsNozzle nozzle in Global.nozzleList)
            {
                if (nozzleNo == nozzle.nozzleNo)
                {
                    if (!nozzle.bMatched)
                    {
                        ClsCarInfo car = FindCarInAreaCarList(nozzleNo);
                        if (car != null)
                        {
                            nozzle.nozzleCar = car;
                            nozzle.bMatched = true;
                        }
                    }
                    nozzle.curStatus = nozzleStatus;
                    NET_DVR_PLATE_RESULT snapData = new NET_DVR_PLATE_RESULT();
                    snapData.byPumpID = (byte)nozzleNo;
                    snapData.byPumpStatus = (byte)nozzleStatus;
                    snapData.sLicense = new byte[16];
                    byte[] license = System.Text.Encoding.Default.GetBytes(nozzle.nozzleCar.license);
                    Buffer.BlockCopy(license, 0, snapData.sLicense, 0, license.Length);
                    snapData.byColor = (byte)nozzle.nozzleCar.carColor;
                    snapData.byPlateColor = (byte)nozzle.nozzleCar.licenseColor;
                    snapData.byVehicleShape = (byte)nozzle.nozzleCar.carLogo;
                    snapData.wVehicleLogoRecog = (short)nozzle.nozzleCar.carLogo;
                    snapData.wVehicleSubLogoRecog = (short)nozzle.nozzleCar.subCarLogo;
                    SendSnapToDIT(snapData);

                    DateTime dt = DateTime.Now;
                    switch (nozzleStatus)
                    {
                        case 0:  //不生效 默认开始时间
                            nozzle.nozzleCar.beginTime = dt;
                            break;
                        case 1:  //提枪
                            nozzle.nozzleCar.arriveTime = dt;
                            nozzle.nozzleCar.beginTime = dt;
                            nozzle.nozzleCar.endTime = dt;
                            nozzle.nozzleCar.leaveTime = dt;
                            nozzle.nozzleCar.picPath = Global.basePicPath + dt.ToString("yyyyMMdd") + @"\\" + nozzle.nozzleCar.license.Trim() + @"\\";
                            break;
                        case 2: //加油
                            nozzle.nozzleCar.beginTime = dt;
                            nozzle.nozzleCar.endTime = dt;
                            nozzle.nozzleCar.leaveTime = dt;
                            break;
                        case 3: //挂枪
                            nozzle.nozzleCar.endTime = dt;
                            nozzle.nozzleCar.leaveTime = dt;
                            nozzle.nozzleCar.picPath = Global.basePicPath + dt.ToString("yyyyMMdd") + @"\\" + nozzle.nozzleCar.license.Trim() + @"\\";
                            Global.mysqlHelper.ExecuteSql(nozzle.nozzleCar.toSaveSqlString());
                            for (int i = 0; i < Global.arrayAreaCar.Length; i++)
                            {
                                if (nozzle.nozzleCar.license == Global.arrayAreaCar[i].license)
                                {
                                    Global.arrayAreaCar[i].license = "";
                                    Global.arrayAreaCar[i].nozzleNo = 0;
                                    Global.arrayAreaCar[i].matchFlag = 0;
                                    Global.arrayAreaCar[i].carLogo = 0;
                                    Global.arrayAreaCar[i].subCarLogo = 0;
                                }
                            }
                            nozzle.bMatched = false;
                            nozzle.nozzleCar.license = "";
                            nozzle.curStatus = 0;
                            SetRealtimeDGV(dataGridRealtime);
                            //Global.arrayAreaCar[index].
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        private ClsCarInfo FindCarInAreaCarList(int nozzleNo)
        {
            //查找关联油岛及区域并在其中查找车牌
            Global.LogServer.Add(new LogInfo("Debug", "Main->FindCarInAreaCarList: 开始查找车牌" , (int)EnumLogLevel.DEBUG));
           
            foreach(ClsNozzle nozzle in Global.nozzleList)
            {
                if (nozzleNo == nozzle.nozzleNo)
                {
                    Global.LogServer.Add(new LogInfo("Debug", "Main->FindCarInAreaCarList: 找到油枪列："+nozzleNo.ToString(), (int)EnumLogLevel.DEBUG));
                   
                    foreach (int areaNo in nozzle.linkedMainAreaList)
                    {
                        Global.LogServer.Add(new LogInfo("Debug", "Main->FindCarInAreaCarList: 开始主识别区查找车辆", (int)EnumLogLevel.DEBUG));
                        if (Global.areaMap.ContainsKey(areaNo))
                        {
                            int areaIndex = Global.areaMap[areaNo];
                            if (Global.arrayAreaCar[areaIndex].matchFlag == 0 && Global.arrayAreaCar[areaIndex].license != ""
                                && LicenseIsMatched(Global.arrayAreaCar[areaIndex].license, nozzleNo) == 0)
                            {
                                ShowRTBInfo("油枪号：" + nozzleNo.ToString() + " 视频流主识别区匹配车牌成功，识别区：" + areaIndex.ToString());
                                Global.LogServer.Add(new LogInfo("Debug", "Main->FindCarInAreaCarList: 主识别区匹配到车辆，车牌：" +
                                Global.arrayAreaCar[areaIndex].license + " 识别区：" + areaIndex.ToString(), (int)EnumLogLevel.DEBUG));
                                nozzle.bMatched = true;
                                Global.arrayAreaCar[areaIndex].matchFlag = 1;
                                Global.arrayAreaCar[areaIndex].nozzleNo = nozzleNo;

                                ClsCarInfo Car = new ClsCarInfo();
                                Car.license = Global.arrayAreaCar[areaIndex].license;
                                Car.arriveTime = Global.arrayAreaCar[areaIndex].arriveTime;
                                Car.carLogo = Global.arrayAreaCar[areaIndex].carLogo;
                                Car.subCarLogo = Global.arrayAreaCar[areaIndex].subCarLogo;
                                Car.licenseColor = Global.arrayAreaCar[areaIndex].licenseColor;
                                Car.carColor = Global.arrayAreaCar[areaIndex].carColor;
                                return Car;
                            
                            }
                         }
                     }
                       
                    Global.LogServer.Add(new LogInfo("Debug", "Main->FindCarInAreaCarList: 主识别区未查找车辆，进入副识别区查找车辆", (int)EnumLogLevel.DEBUG));
                    foreach (int areaNo in nozzle.linkedSubAreaList)
                    {
                        if (Global.areaMap.ContainsKey(areaNo))
                        {
                            int areaIndex = Global.areaMap[areaNo];
                            if (Global.arrayAreaCar[areaIndex].matchFlag == 0 && Global.arrayAreaCar[areaIndex].license != ""
                        && LicenseIsMatched(Global.arrayAreaCar[areaIndex].license, nozzleNo) == 0)
                            {
                                ShowRTBInfo("油枪号：" + nozzleNo.ToString() + " 视频流副识别区匹配车牌成功，识别区：" + areaIndex.ToString());
                                Global.LogServer.Add(new LogInfo("Debug", "Main->FindCarInAreaCarList: 副识别区匹配到车辆，车牌：" +
                               Global.arrayAreaCar[areaIndex].license + " 识别区：" + areaIndex.ToString(), (int)EnumLogLevel.DEBUG));
                                nozzle.bMatched = true;
                                Global.arrayAreaCar[areaIndex].matchFlag = 1;
                                Global.arrayAreaCar[areaIndex].nozzleNo = nozzleNo;
                                ClsCarInfo Car = new ClsCarInfo();
                                Car.license = Global.arrayAreaCar[areaIndex].license;
                                Car.arriveTime = Global.arrayAreaCar[areaIndex].arriveTime;
                                return Car;
                            }
                        }
                        
                    }

                }
            }
            Global.LogServer.Add(new LogInfo("Debug", "Main->FindCarInAreaCarList: 匹配结束，未匹配到任何车辆", (int)EnumLogLevel.DEBUG));
            return null;
        }
        
        private void GetAreaCarFromDll(int areaNo)
        {
            struCarInfoOut struCarOut = new struCarInfoOut();
            IntPtr pCarOut = Marshal.AllocHGlobal(Marshal.SizeOf(struCarOut));
            SPlate.SP_GetAreaCarInfo(pCarOut, areaNo);
            struCarOut = (struCarInfoOut)Marshal.PtrToStructure(pCarOut, typeof(struCarInfoOut));
            Marshal.FreeHGlobal(pCarOut);
            string lic = Encoding.Default.GetString(struCarOut.license,0,GetStrLength(struCarOut.license));

            if (Global.ditCallBackMode == 2) //使用出入口相机
            {
                if (Global.entryAreaID == areaNo)
                {
                    SendCallbackInfo(struCarOut, 1);
                    ShowRTBInfo("获取入口车牌：" + lic + " 车辆品牌:" + struCarOut.nCarLogo.ToString() + " 车辆子品牌:" + struCarOut.nSubCarLogo.ToString());
                    return;
                }
                else if (Global.exitAreaID == areaNo)
                {
                    SendCallbackInfo(struCarOut, 2);
                    ShowRTBInfo("获取出口车牌：" + lic + " 车辆品牌:" + struCarOut.nCarLogo.ToString() + " 车辆子品牌:" + struCarOut.nSubCarLogo.ToString());
                    return;
                }
            }
            else // 不使用出入口相机，根据视频流车牌先后判断进站
            {
                ClsCarArrive carArrive = getCarArriveInList(lic);
                if (carArrive == null)
                {
                    SendCallbackInfo(struCarOut, 1);
                    ShowRTBInfo("新车辆被捕获，发送给DIT：" + lic + " 车辆品牌:" + struCarOut.nCarLogo.ToString() + " 车辆子品牌:" + struCarOut.nSubCarLogo.ToString());
                    carArrive = new ClsCarArrive(lic, struCarOut,DateTime.Now);
                    lock (Global.lockObj)
                    {
                        Global.listCarArrive.Add(carArrive);
                    }
                    
                } 
            }
            ShowRTBInfo("视频流车牌获取区域:" + areaNo.ToString()+"  获取车牌：" + lic+" 车辆品牌:" + struCarOut.nCarLogo.ToString() + " 车辆子品牌:" + struCarOut.nSubCarLogo.ToString());
            for (int i=0;i<Global.arrayAreaCar.Length;i++)
            {   
                if (Global.arrayAreaCar[i].license == lic && lic.Length > 5)
                {
                    Global.arrayAreaCar[i].license = "";
                    Global.arrayAreaCar[i].matchFlag = 0;
                    Global.arrayAreaCar[i].carLogo = 0;
                    Global.arrayAreaCar[i].subCarLogo = 0;
                }
            }
            //if (checkRepeatLicense(struCarOut.nAreaNo, license))
            //{
            //}
            if (CheckDBcarRepeat(lic))
            {
                ShowRTBInfo("车牌"+ lic + "10分钟内已加油,视为无效车辆，不匹配识别区" );
                return;
            }
            if (Global.areaMap.ContainsKey(areaNo))
            {
                int index = Global.areaMap[areaNo];
                Global.arrayAreaCar[index].license = lic;
                Global.arrayAreaCar[index].licenseColor = struCarOut.nColor;
                Global.arrayAreaCar[index].carLogo = struCarOut.nCarLogo;
                Global.arrayAreaCar[index].subCarLogo = struCarOut.nSubCarLogo;
                Global.arrayAreaCar[index].carColor = struCarOut.nCarColor;
                Global.arrayAreaCar[index].arriveTime = DateTime.Now;  //都取当前时间，再收到DIT信息后修改加油及离开时间
                Global.arrayAreaCar[index].beginTime = DateTime.Now;
                Global.arrayAreaCar[index].endTime = DateTime.Now;
                Global.arrayAreaCar[index].leaveTime = DateTime.Now;
                Global.arrayAreaCar[index].areaNo = areaNo;
                Global.arrayAreaCar[index].matchFlag = 0;
                //Global.arrayAreaCar[index].matchFlag = 0;
                //Global.arrayAreaCar[index].nozzleNo = 0;
                Global.LogServer.Add(new LogInfo("Debug", "Main->GetAreaCarFromDll: 获取区域:" + areaNo.ToString() + "车牌：" + Global.arrayAreaCar[index].license, (int)EnumLogLevel.DEBUG));
            }
            UpdateStationBoardAreaControlStatus(areaNo, lic,Color.Yellow);


        }

        //从车里队列中查找车牌
        public ClsCarArrive getCarArriveInList(string plate)
        {
            lock (Global.lockObj)
            {
                foreach (ClsCarArrive car in Global.listCarArrive)
                {
                    if (plate == car.plate)
                    {
                        return car;
                    }
                }
            }
            return null;
        }

        private bool CheckDBcarRepeat(string license)
        {
            if (license.Length < 5)
            {
                return true;
            }
            DateTime leave = DateTime.Now;
            string sql = "select count(*) as count from carlog where carnumber = '"+license+"' and leavetime > '" + 
                leave.AddMinutes(-10).ToString("yyyy-MM-dd HH:mm:ss")+"'";
            Global.LogServer.Add(new LogInfo("Debug", "Main->checkDBcarRepeat: query string :" + sql, (int)EnumLogLevel.DEBUG));
            DataTable dt = Global.mysqlHelper.GetDataTable(sql);
            
            if (dt == null || dt.Rows.Count == 0)
            {
                Global.LogServer.Add(new LogInfo("Debug", "Main->checkDBcarRepeat: not repeat", (int)EnumLogLevel.DEBUG));
                return false;
            } 
            else
            {
                int count = int.Parse(dt.Rows[0]["count"].ToString());
                if (count > 0)
                {
                    Global.LogServer.Add(new LogInfo("Debug", "Main->checkDBcarRepeat: license repeat ", (int)EnumLogLevel.DEBUG));
                    return true;
                } 
                else
                {
                    Global.LogServer.Add(new LogInfo("Debug", "Main->checkDBcarRepeat: not repeat", (int)EnumLogLevel.DEBUG));
                    return false;
                }
               
            }
        }
       
        private void ShowNozzleCarList()
        {
            listViewCache.Items.Clear();
            listViewCache.BeginUpdate();
             for (int i = 0; i < Global.nozzleList.Count; i++)
            {
                ListViewItem lvi = new ListViewItem();
                lvi.Text = Global.nozzleList[i].nozzleNo.ToString();
                lvi.SubItems.Add(Global.nozzleList[i].nozzleCar.license);
                //lvi.SubItems.Add(Global.nozzleList[i].curStatus.ToString());
                if (Global.nozzleList[i].curStatus == 1)
                {
                    lvi.SubItems.Add("已提枪");
                }
                else if (Global.nozzleList[i].curStatus == 2)
                {
                    lvi.SubItems.Add("加油中");
                }
                else
                {
                    lvi.SubItems.Add("空闲");
                }
                string carlogoKey = Global.nozzleList[i].nozzleCar.carLogo.ToString() + "-" + Global.nozzleList[i].nozzleCar.subCarLogo.ToString();
                string carlogo = "未知";
                if (Global.carLogoHashtable.Contains(carlogoKey))
                {
                    carlogo = (string)Global.carLogoHashtable[carlogoKey];
                }
                //lvi.SubItems.Add(Global.nozzleList[i].nozzleCar.carLogo.ToString());
                lvi.SubItems.Add(carlogo);
                listViewCache.Items.Add(lvi);
            }
            listViewCache.EndUpdate();
        }

        private void ShowAreaCarList()
        {
            listViewArea.Items.Clear();
            listViewArea.BeginUpdate();
            for (int i = 0; i < Global.arrayAreaCar.Length; i++)
            {
                ListViewItem lvi = new ListViewItem();
                lvi.Text = Global.arrayAreaCar[i].areaNo.ToString();
                int j = Global.areaMap[Global.arrayAreaCar[i].areaNo];
                lvi.SubItems.Add(Global.areaList[j].videoChannel.ToString());
                lvi.SubItems.Add(Global.areaList[j].videoLaneNo.ToString());
                lvi.SubItems.Add(Global.arrayAreaCar[i].license);
                string carlogoKey = Global.arrayAreaCar[i].carLogo.ToString() + "-" + Global.arrayAreaCar[i].subCarLogo.ToString();
                string carlogo = "未知";
                if (Global.carLogoHashtable.Contains(carlogoKey))
                {
                    carlogo = (string)Global.carLogoHashtable[carlogoKey];
                }
                lvi.SubItems.Add(carlogo);
                listViewArea.Items.Add(lvi);
            }
            listViewArea.EndUpdate();
        }
      




        private void ProcCarLeave_Array(struCarInfoOut carOut)
        {
            string license = System.Text.Encoding.Default.GetString(carOut.license);
            string sqlString = "update carlog set leavetime = '" + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") +
                "' where carnumber = '" + carOut.license + "' order by arrivetime desc limit 1";
            Global.mysqlHelper.ExecuteSql(sqlString);
        }
       

       
        private void ProcSnapFromDIT_Capture(int nozzleNo,int nozzleStatus)
        {
            NET_DVR_PLATE_RESULT snapData = new NET_DVR_PLATE_RESULT();
            snapData.byPumpID = (byte)nozzleNo;
            snapData.byPumpStatus = (byte)nozzleStatus;
            snapData.sLicense = new byte[16];


            if (!Global.nozzleMap.ContainsKey(nozzleNo))
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->ProcSnapFromDIT_Capture: 未找到对应油枪信息，油枪号：" + nozzleNo.ToString(), (int)EnumLogLevel.ERROR));
                return;
            }
            int index = Global.nozzleMap[nozzleNo];
            Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture:获取油枪序号："+index.ToString()+ " 油枪号：" + nozzleNo.ToString(), (int)EnumLogLevel.DEBUG));

            if (nozzleStatus ==1 || Global.nozzleList[index].nozzleCar.matchFlag == 0)
            {
                IntPtr pCarOut = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(struCarInfoOut_V2)));
                Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture: 开始抓拍，油枪号：" + nozzleNo.ToString(), (int)EnumLogLevel.DEBUG));
                ShowRTBInfo("油枪号：" + nozzleNo.ToString()+ " 开始抓拍");
                SPlate.SP_Capture(nozzleNo, pCarOut);
                struCarInfoOut_V2 struCarOut;
                struCarOut = (struCarInfoOut_V2)Marshal.PtrToStructure(pCarOut, typeof(struCarInfoOut_V2));
                Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture: 识别车牌数量：" + struCarOut.nLicenseCount.ToString(), (int)EnumLogLevel.DEBUG));
                ShowRTBInfo("油枪号：" + nozzleNo.ToString()+" 抓拍完成，识别车牌数量：" + struCarOut.nLicenseCount.ToString());
                Marshal.FreeHGlobal(pCarOut);

                ClsCarInfo car = MatchCar(struCarOut, nozzleNo);
                if (car != null) //抓拍匹配到车辆
                {
                    
                    ShowRTBInfo("油枪号：" + nozzleNo.ToString() + " 匹配抓拍车牌:" + car.license +" 车辆品牌:"+car.carLogo.ToString() + " 车辆子品牌:"+ car.subCarLogo.ToString());
                    Global.nozzleList[index].nozzleCar = car;
                    Global.nozzleList[index].nozzleCar.matchFlag = nozzleStatus;

                    
                }
                else if (Global.nVideoRecogFlag == 1) //如开启了视频识别，从视频识别结果中查找车牌
                {
                    ShowRTBInfo("油枪号：" + nozzleNo.ToString() + " 抓拍匹配失败，从视频流车牌中匹配车牌");
                    car = FindCarInAreaCarList(nozzleNo);
                    if (car != null)
                    {
                        ShowRTBInfo("油枪号：" + nozzleNo.ToString() + " 视频流匹配车牌成功，匹配车牌:" + car.license);
                        Global.nozzleList[index].nozzleCar = car;
                        Global.nozzleList[index].nozzleCar.matchFlag = nozzleStatus;
                    }
                    else
                    {
                        ShowRTBInfo("油枪号：" + nozzleNo.ToString() + " 视频流匹配车牌失败");
                    }
                }
                if (car != null)
                {
                    for (int i=0;i<Global.arrayAreaCar.Length;i++)
                    {
                        if (car.license == Global.arrayAreaCar[i].license)
                        {
                            Global.arrayAreaCar[i].matchFlag = 1;
                        }
                    }
                }

                

                ClsPicture pic = new ClsPicture();
                pic.picBufer = new byte[struCarOut.nPicLenth];
                Buffer.BlockCopy(struCarOut.pic, 0, pic.picBufer, 0, struCarOut.nPicLenth);
                //pic.picPath = Global.basePicPath + dt.ToString("yyyyMMdd") + @"\\" + Global.arrayNozzleCar[index].license.Trim() + @"\\";
                pic.picPath = Global.basePicPath + DateTime.Now.ToString("yyyyMMdd") + @"\\";
                // Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll: 车辆图片入队列,图片路径：" + pic.picPath+ pic.picName, (int)EnumLogLevel.DEBUG));
                pic.picName = Global.nozzleList[index].nozzleNo.ToString()+"_"+DateTime.Now.ToString("HHmmss") + ".jpg";
                pic.picWidth = struCarOut.nPicWidth;
                pic.picHeight = struCarOut.nPicHeight;
                pic.picType = struCarOut.nPicType;
                Global.picWork.Add(pic);
                Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture: 车辆图片入队列,图片长度：" +struCarOut.nPicLenth.ToString(), (int)EnumLogLevel.DEBUG));

                if (pic.picBufer.Length > 2)
                {
                    Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture: 车辆图片入队列,图片类型：" + pic.picBufer[0].ToString() + pic.picBufer[1].ToString() +
                    "图片路径：" + pic.picPath + pic.picName, (int)EnumLogLevel.DEBUG));
                }
                
            }
            //int index = Global.nozzleMap[nozzleNo];
            
            Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture: 匹配车牌：" + Global.arrayNozzleCar[index].license, (int)EnumLogLevel.DEBUG));
            Global.nozzleList[index].nozzleCar.nozzleNo = nozzleNo;
            Global.nozzleList[index].curStatus = nozzleStatus;
            byte[] license = System.Text.Encoding.Default.GetBytes(Global.nozzleList[index].nozzleCar.license);
            Buffer.BlockCopy(license, 0, snapData.sLicense, 0, license.Length);
            snapData.byColor = (byte)Global.nozzleList[index].nozzleCar.carColor;
            snapData.byPlateColor = (byte)Global.nozzleList[index].nozzleCar.licenseColor;
            snapData.byVehicleShape = (byte)Global.nozzleList[index].nozzleCar.carLogo;
            snapData.wVehicleLogoRecog = (short)Global.nozzleList[index].nozzleCar.carLogo;
            snapData.wVehicleSubLogoRecog = (short)Global.nozzleList[index].nozzleCar.subCarLogo;
            SendSnapToDIT(snapData);
            DateTime dt = DateTime.Now;
            Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture:进入油枪状态判断处理，油枪状态："+ nozzleStatus.ToString(), (int)EnumLogLevel.DEBUG));

            if (Global.ditCallBackMode == 1 && Global.nozzleList[index].nozzleCar.license != "")
                        
            {
                ClsCarArrive carArrive = getCarArriveInList(Global.nozzleList[index].nozzleCar.license);
                if (carArrive == null)
                {
                    struCarInfoOut car = new struCarInfoOut();
                    car.license = Encoding.Default.GetBytes(Global.nozzleList[index].nozzleCar.license);
                    car.nCarColor = Global.nozzleList[index].nozzleCar.carColor;
                    car.nColor = Global.nozzleList[index].nozzleCar.carColor;
                    car.nCarLogo = Global.nozzleList[index].nozzleCar.carLogo;
                    car.nSubCarLogo = Global.nozzleList[index].nozzleCar.subCarLogo;

                    SendCallbackInfo(car, 1);
                    ShowRTBInfo("新车辆被捕获，发送给DIT：" + Global.nozzleList[index].nozzleCar.license + " 车辆品牌:" 
                        + car.nCarLogo.ToString() + " 车辆子品牌:" + car.nSubCarLogo.ToString());
                    carArrive = new ClsCarArrive(Global.nozzleList[index].nozzleCar.license, car, DateTime.Now);
                    Global.listCarArrive.Add(carArrive);
                }
            }
            switch (nozzleStatus)
            {
                case 0:  //不生效 默认开始时间
                    Global.nozzleList[index].nozzleCar.beginTime = dt;
                    break;
                case 1:  //提枪
                    Global.nozzleList[index].nozzleCar.arriveTime = dt;
                    Global.nozzleList[index].nozzleCar.beginTime = dt;
                    Global.nozzleList[index].nozzleCar.endTime = dt;
                    Global.nozzleList[index].nozzleCar.leaveTime = dt;
                    Global.nozzleList[index].nozzleCar.picPath = Global.basePicPath + dt.ToString("yyyyMMdd") + @"\\" + Global.nozzleList[index].nozzleCar.license + @"\\";
                    //if(Global.nMatchMode == 1 && Global.nozzleList[index].nozzleCar.license != "")
                    //    SendCallbackInfo(Global.nozzleList[index].nozzleCar, 1);
                    UpdateStationBoardAreaControlStatus(Global.nozzleList[index].nozzleCar.areaNo, Global.nozzleList[index].nozzleCar.license,Color.Red);
                    break;
                case 2: //加油
                    Global.nozzleList[index].nozzleCar.beginTime = dt;
                    Global.nozzleList[index].nozzleCar.endTime = dt;
                    Global.nozzleList[index].nozzleCar.leaveTime = dt;
                    UpdateStationBoardAreaControlStatus(Global.nozzleList[index].nozzleCar.areaNo, Global.nozzleList[index].nozzleCar.license, Color.Red);
                    break;
                case 3: //挂枪
                    Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture:进入挂枪处理" , (int)EnumLogLevel.DEBUG));
                    Global.nozzleList[index].nozzleCar.endTime = dt;
                    Global.nozzleList[index].nozzleCar.leaveTime = dt;
                    Global.nozzleList[index].nozzleCar.picPath = Global.basePicPath + dt.ToString("yyyyMMdd") + @"\\" + Global.arrayNozzleCar[index].license.Trim() + @"\\";
                    Global.mysqlHelper.ExecuteSql(Global.nozzleList[index].nozzleCar.toSaveSqlString());
                    Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture:数据存储执行完毕,SQL:"+ Global.nozzleList[index].nozzleCar.toSaveSqlString(), (int)EnumLogLevel.DEBUG));
                    if (Global.nMatchMode == 1 && Global.nozzleList[index].nozzleCar.license != "")
                        SendCallbackInfo(Global.nozzleList[index].nozzleCar, 2);
                    //Global.arrayAreaCar[index].
                    Global.nozzleList[index].nozzleCar.license = "";
                    Global.nozzleList[index].nozzleCar.matchFlag = 0;
                    Global.nozzleList[index].nozzleCar.carLogo = 0;
                    Global.nozzleList[index].nozzleCar.subCarLogo = 0;
                    SetRealtimeDGV(dataGridRealtime);
                    UpdateStationBoardAreaControlStatus(Global.nozzleList[index].nozzleCar.areaNo, Global.nozzleList[index].nozzleCar.license, Color.LightGreen);
                    break;
                default:
                    break;
            }
            Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture:操作结束，油枪状态：" + nozzleStatus.ToString(), (int)EnumLogLevel.DEBUG));
            
        }

        private ClsCarInfo MatchCar(struCarInfoOut_V2 struCarInfo,int nozzleNo)
        {
            ClsCarInfo car = new ClsCarInfo();
            int index = 0;
            int nCurConfidence = 0;
            for (int i=0;i<struCarInfo.nLicenseCount;i++)
            {
                string license;
                if (Global.dllEncoder == "utf8")
                {
                    license = System.Text.Encoding.UTF8.GetString(struCarInfo.license[i].license, 0, GetStrLength(struCarInfo.license[i].license));
                } 
                else
                {
                    license = System.Text.Encoding.Default.GetString(struCarInfo.license[i].license, 0, GetStrLength(struCarInfo.license[i].license));
                }
               
                Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture: 车牌号：" + 
                    license+" 置信度："+ struCarInfo.license[i].nConfidence.ToString() + " 识别区："+ 
                    struCarInfo.license[i].nAreaNo.ToString(), (int)EnumLogLevel.DEBUG));
                if (LicenseIsMatched(license,nozzleNo) > 0)
                    continue;
                if (CheckDBcarRepeat(license))
                    continue;
                if (struCarInfo.license[i].nConfidence > nCurConfidence)
                {
                    index = i;
                    nCurConfidence = struCarInfo.license[i].nConfidence;
                }
                
            }

            if (nCurConfidence > 75)
            {
                if (Global.dllEncoder == "utf8")
                {
                    car.license = System.Text.Encoding.UTF8.GetString(struCarInfo.license[index].license, 0, GetStrLength(struCarInfo.license[index].license));
                }
                else
                {
                    car.license = System.Text.Encoding.Default.GetString(struCarInfo.license[index].license, 0, GetStrLength(struCarInfo.license[index].license));
                }

                
                car.licenseColor = struCarInfo.license[index].nColor;
                car.carColor = struCarInfo.license[index].nCarColor;
                car.carLogo = struCarInfo.license[index].nCarLogo;
                car.subCarLogo = struCarInfo.license[index].nSubCarLogo;
                car.areaNo = struCarInfo.license[index].nAreaNo;
                return car;
            }
            else
                return null;
            

        }
        private int LicenseIsMatched(string license,int exceptNozzleNo)
        {
            for (int i=0;i<Global.nozzleList.Count;i++)
            {
                //Global.LogServer.Add(new LogInfo("Debug", "Main->LicenseIsMatched  传入车牌：" + license + " 字符长度" + license.Length
                //    + "  对比车牌：" + Global.nozzleList[i].nozzleCar.license + " 字符长度" + Global.nozzleList[i].nozzleCar.license.Length +
                //    "  传入油枪号:" + exceptNozzleNo.ToString() + "  对比油枪号:" + Global.nozzleList[i].nozzleNo.ToString(), (int)EnumLogLevel.DEBUG));

                if (Global.nozzleList[i].nozzleCar.license == license && Global.nozzleList[i].nozzleNo != exceptNozzleNo)
                {
                    return Global.nozzleList[i].nozzleNo;
                }
            }
            
            return 0;
        }
        private void SendSnapToDIT(NET_DVR_PLATE_RESULT snapData)
        {
            byte[] data = SystemUnit.StrutsToBytesArray(snapData);
            byte[] sendbuf = new byte[data.Length + 8];
            sendbuf[0] = 0xFF;
            sendbuf[1] = 0xFF;
            sendbuf[2] = 0x03;
            sendbuf[3] = (byte)data.Length;
            Buffer.BlockCopy(data, 0, sendbuf, 4, data.Length);
            uint crc = SystemUnit.getCRC(sendbuf, 0, data.Length + 4);
            sendbuf[data.Length + 4] = (byte)(crc / 256);
            sendbuf[data.Length + 5] = (byte)(crc % 256);
            sendbuf[data.Length + 6] = 0xEE;
            sendbuf[data.Length + 7] = 0xEE;
            Global.socketTool.Send(sendbuf);

            Global.LogServer.Add(new LogInfo("Run", "Main->SendSnapToDIT: 发送车辆信息到DIT  车牌号:" +
                 System.Text.Encoding.Default.GetString(snapData.sLicense) + "  油枪号：" + snapData.byPumpID.ToString(), (int)EnumLogLevel.RUN));
        }

        #endregion

        private void ShowMemoryInfo()
        {
            MEMORY_INFO MemInfo;
            MemInfo = new MEMORY_INFO();
            try
            {
                SystemUnit.GlobalMemoryStatus(ref MemInfo);
                toolRAM.Text = MemInfo.dwMemoryLoad.ToString() + "%";
            }
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "main->showMemoryInfo Fail" + ex.ToString(), (int)EnumLogLevel.ERROR));
            }
           
        }

        private void ShowMatchRatio()
        {
            int match = 0;
            try
            {
                string sqlString = "select max(id) as id from carlog";
                DataTable dt = Global.mysqlHelper.GetDataTable(sqlString);
                if (dt != null && dt.Rows.Count > 0)
                {
                    Global.nTotalCount = int.Parse(dt.Rows[0]["id"].ToString());
                }


                sqlString = "select count(*) as matchcount from carlog where LENGTH(carnumber) > 5";
                dt = Global.mysqlHelper.GetDataTable(sqlString);
                int totalmatch = 0;
                if (dt != null && dt.Rows.Count > 0)
                {
                    totalmatch = int.Parse(dt.Rows[0]["matchcount"].ToString());
                }


                if (Global.nTotalCount > 0)
                {
                    Global.nTotalRatio = (totalmatch * 100) / Global.nTotalCount;
                }


                sqlString = "select count(*) as total from carlog where leavetime > '" + DateTime.Now.ToString("yyyy-MM-dd ") + "00:00:00'";
                dt = Global.mysqlHelper.GetDataTable(sqlString);
                if (dt != null && dt.Rows.Count > 0)
                {
                    Global.nCurrentCount = int.Parse(dt.Rows[0]["total"].ToString());
                }

                sqlString = "select count(*) as matchcount from carlog where LENGTH(carnumber) > 5 and leavetime > '" + DateTime.Now.ToString("yyyy-MM-dd ") + "00:00:00'";
                dt = Global.mysqlHelper.GetDataTable(sqlString);
                
                if (dt != null && dt.Rows.Count > 0)
                {
                    match = int.Parse(dt.Rows[0]["matchcount"].ToString());
                }
                if (Global.nCurrentCount > 0)
                {
                    Global.nCurrentRatio = (match * 100) / Global.nCurrentCount;
                }
            }
            catch (System.Exception ex)
            {
            	
            }

            lblTotalCount.Text = Global.nTotalCount.ToString();
            lblCurCount.Text = Global.nCurrentCount.ToString();
            lblCurRatio.Text = Global.nCurrentRatio.ToString() + "%";
//             toolMatchPoint.Text = "当天车辆总数:" + Global.nCurrentCount.ToString() + "   当天匹配数:" + match.ToString() + "   当天匹配率:" + Global.nCurrenrRatio.ToString()+"%"
//                                     + "   历史车辆总数:" + Global.nTotalCount.ToString() + "   总匹配率:" + Global.nTotalRatio.ToString()+"%";

        }

        private void ExitApp()
        {
            SystemUnit.PostMessage(SystemUnit.HWND_BROADCAST, (int)WM_KILLPROCESS, 0, 0);
            Global.socketTool.Close();
            SPlate.SP_Close();
            
            Global.picWork.Stop();
            
            if (Global.LogServer != null)
                Global.LogServer.Stop();
            this.toExit = true;
            
            //启动强制退出线程
            System.Environment.Exit(0);
        }

        private void SendCallbackInfo(struCarInfoOut carOut,int InOrOut)
        {

            NET_ITS_PLATE_RESULT callBackInfo = new NET_ITS_PLATE_RESULT();
            callBackInfo.sLicense = new byte[16];
            Buffer.BlockCopy(carOut.license, 0, callBackInfo.sLicense, 0, carOut.license.Length);
            callBackInfo.byColor = (byte)carOut.nCarColor;
            callBackInfo.byPlateColor = (byte)carOut.nColor;
            callBackInfo.wVehicleLogoRecog = (short)carOut.nCarLogo;
            callBackInfo.wVehicleSubLogoRecog = (short)carOut.nSubCarLogo;
            callBackInfo.byVehicleShape = 0;
            callBackInfo.byVehicleState = (byte)InOrOut;
            byte[] data = SystemUnit.StrutsToBytesArray(callBackInfo);

            byte[] sendbuf = new byte[data.Length + 8];
            sendbuf[0] = 0xFF;
            sendbuf[1] = 0xFF;
            sendbuf[2] = 0x06;
            sendbuf[3] = 24;
            Buffer.BlockCopy(data, 0, sendbuf, 4, data.Length);
            uint crc = SystemUnit.getCRC(sendbuf, 0, data.Length + 4);
            sendbuf[data.Length + 4] = (byte)(crc / 256);
            sendbuf[data.Length + 5] = (byte)(crc % 256);
            sendbuf[data.Length + 6] = 0xEE;
            sendbuf[data.Length + 7] = 0xEE;
            Global.socketTool.Send(sendbuf);
            string license = System.Text.Encoding.Default.GetString(carOut.license);
            string status = "";
            if (InOrOut == 1)
                status = "进站";
            else
                status = "出站";
            Global.LogServer.Add(new LogInfo("Run", "main->sendCallbackInfo 发送回调信息到DIT，车牌："+license + " 状态:"+status, (int)EnumLogLevel.RUN));
        }
        private void SendCallbackInfo(ClsCarInfo carOut, int InOrOut)
        {

            NET_ITS_PLATE_RESULT callBackInfo = new NET_ITS_PLATE_RESULT();
            callBackInfo.sLicense = new byte[16];
            byte[] lic = System.Text.Encoding.Default.GetBytes(carOut.license);
            Buffer.BlockCopy(lic, 0, callBackInfo.sLicense, 0, lic.Length);
            callBackInfo.byColor = (byte)carOut.carColor;
            callBackInfo.byPlateColor = (byte)carOut.licenseColor;
            callBackInfo.wVehicleLogoRecog = (short)carOut.carLogo;
            callBackInfo.wVehicleSubLogoRecog = (short)carOut.subCarLogo;
            callBackInfo.byVehicleShape = 0;
            callBackInfo.byVehicleState = (byte)InOrOut;
            byte[] data = SystemUnit.StrutsToBytesArray(callBackInfo);

            byte[] sendbuf = new byte[data.Length + 8];
            sendbuf[0] = 0xFF;
            sendbuf[1] = 0xFF;
            sendbuf[2] = 0x06;
            sendbuf[3] = 24;
            Buffer.BlockCopy(data, 0, sendbuf, 4, data.Length);
            uint crc = SystemUnit.getCRC(sendbuf, 0, data.Length + 4);
            sendbuf[data.Length + 4] = (byte)(crc / 256);
            sendbuf[data.Length + 5] = (byte)(crc % 256);
            sendbuf[data.Length + 6] = 0xEE;
            sendbuf[data.Length + 7] = 0xEE;
            Global.socketTool.Send(sendbuf);
            string status = "";
            if (InOrOut == 1)
                status = "进站";
            else
                status = "出站";
            Global.LogServer.Add(new LogInfo("Run", "main->sendCallbackInfo 发送回调信息到DIT，车牌：" + carOut.license + " 状态:" + status, (int)EnumLogLevel.RUN));
        }

        private void AddListViewHead()
        {
            listViewCache.View = View.Details;
            listViewCache.Columns.Add("油枪号", 60);
            listViewCache.Columns.Add("车牌", 100);
            listViewCache.Columns.Add("油枪状态", 80);
            listViewCache.Columns.Add("车辆品牌型号", 160);
            listViewArea.View = View.Details;
            listViewArea.Columns.Add("识别区号", 80);
            listViewArea.Columns.Add("视频通道", 80);
            listViewArea.Columns.Add("子识别区", 80);
            listViewArea.Columns.Add("车牌", 100);
            listViewArea.Columns.Add("车辆品牌型号", 160);
            
        }

        private void ShowRTBInfo(string infoString)
        {
            
            if (RTBLog.Lines.Length > 2000)
            {
                List<string> temp = new List<string>();
                temp.AddRange(RTBLog.Lines);
                RTBLog.Clear();
                RTBLog.Lines = temp.GetRange(temp.Count - 500, 500).ToArray();
                
                //RTBLog.Clear();
            }
            RTBLog.AppendText(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss")+":"+infoString + "\n");
            //让文本框获取焦点
            this.RTBLog.Focus();
            //设置光标的位置到文本尾
            this.RTBLog.Select(this.RTBLog.TextLength, 0);
            //滚动到控件光标处
            this.RTBLog.ScrollToCaret();
        }
        private int GetStrLength(byte[] src)
        {
            int lenth = 0;
            for (int i=0;i<src.Length;i++)
            {
                if (src[i] > 0)
                {
                    lenth++;
                }
            }
            return lenth;
        }
        public void SetRealtimeDGV(DataGridView dgv)
        {
            string sql = "select id,carnumber,nozzleno,oiltype,arrivetime,begintime,leavetime,carlogo,carcolor,picpath from carlog order by id desc limit 0,100";
            DataTable dt = Global.mysqlHelper.GetDataTable(sql);
            if (dt == null || dt.Rows.Count <1)
            {
                return;
            }
            dgv.DataSource = dt;

            dgv.Columns[0].HeaderText = "序号";
            dgv.Columns[1].HeaderText = "车牌号";
            dgv.Columns[2].HeaderText = "油枪号";
            dgv.Columns[3].HeaderText = "油类型";
            dgv.Columns[4].HeaderText = "进站时间";
            dgv.Columns[5].HeaderText = "加油时间";
            dgv.Columns[6].HeaderText = "出站时间";
            dgv.Columns[7].HeaderText = "车辆品牌";
            dgv.Columns[8].HeaderText = "车辆颜色";
            dgv.Columns[9].Visible = false;
            dgv.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            dgv.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            //dgv.AllowUserToAddRows = false;
            //dgv.AllowUserToResizeRows = false;
            dgv.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
            foreach (DataGridViewColumn item in dgv.Columns)
            {
                item.DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
                
                item.ReadOnly = true;
            }
        }

        private void SendStatusToRemote()
        {
            try
            {
                //创建负责通信的Socket
                Socket socketSend = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPAddress ipa = IPAddress.Parse(Global.remoteIP);
                IPEndPoint point = new IPEndPoint(ipa, Global.remotePort);
                //获得要连接的远程服务器应用程序的IP地址和端口号
                socketSend.Connect(point);
                StationInfo info = new StationInfo();
                info.StationName = Global.stationInfo.stationName;
                info.StationCode = Global.stationInfo.stationCode;
                info.IP = Global.stationInfo.stationIP;
                info.Status = Global.nStatus;
                info.CurrentRatio = Global.nCurrentRatio;
                info.TotalRatio = Global.nTotalRatio;
                info.CurrentCount = Global.nCurrentCount;
                info.TotalCount = Global.nTotalCount;
                info.SoftVersion = Global.softVersion;
                string json = JsonHelper.SerializeObject(info);
                byte[] data = System.Text.Encoding.UTF8.GetBytes(json);
                byte[] sendbuff = new byte[256];
                sendbuff[0] = 0xff;
                sendbuff[1] = 0xff;
                sendbuff[2] = 0x01;
                Buffer.BlockCopy(data, 0, sendbuff, 3, data.Length);
                socketSend.Send(sendbuff, data.Length + 3, SocketFlags.None);
                socketSend.Close();
            }
            catch
            {
            }

        }
        public DataTable QueryData(string columns, bool limit)
        {
            string arriveBegin = dateArriveBegin.Value.ToString("yyyy-MM-dd") + timeArriveBegin.Value.ToString(" HH:mm:ss");
            string arriveEnd = dateArriveEnd.Value.ToString("yyyy-MM-dd") + timeArriveEnd.Value.ToString(" HH:mm:ss");
            string leaveBegin = dateLeaveBegin.Value.ToString("yyyy-MM-dd") + timeLeaveBegin.Value.ToString(" HH:mm:ss");
            string leaveEnd = dateLeaveEnd.Value.ToString("yyyy-MM-dd") + timeLeaveEnd.Value.ToString(" HH:mm:ss");
            StringBuilder sbQuery = new StringBuilder();
            sbQuery.Append("select ");
            sbQuery.Append(columns);
            sbQuery.Append(" from carlog");
            sbQuery.Append(" where 1 = 1");
            if (textLicense.Text.Trim().Length > 0)
            {
                sbQuery.Append(" and carnumber like '%" + textLicense.Text.Trim() + "%'");
            }
            if (checkBoxArriveTime.Checked)
            {
                sbQuery.Append(" and (arrivetime between '" + arriveBegin + "' and '" + arriveEnd + "')");
            }
            if (checkBoxLeaveTime.Checked)
            {
                sbQuery.Append(" and (leavetime between '" + leaveBegin + "' and '" + leaveEnd + "')");
            }
            if (comboNozzle.SelectedIndex > 0)
            {
                sbQuery.Append(" and nozzleno = " + comboNozzle.Text);
            }
            sbQuery.Append(" order by leavetime desc");
            if (limit)
            {
                sbQuery.Append("  limit 0,500");
            }
            return Global.mysqlHelper.GetDataTable(sbQuery.ToString());

        }
        public void SetSearchDGV(DataGridView dgv)
        {

            dgv.Columns[0].HeaderText = "序号";
            dgv.Columns[1].HeaderText = "车牌号";
            dgv.Columns[2].HeaderText = "油枪号";
            dgv.Columns[3].HeaderText = "油类型";
            dgv.Columns[4].HeaderText = "进站时间";
            dgv.Columns[5].HeaderText = "加油时间";
            dgv.Columns[6].HeaderText = "出站时间";
            dgv.Columns[7].HeaderText = "车辆品牌";
            dgv.Columns[8].HeaderText = "车辆颜色";
            dgv.Columns[9].Visible = false;
            dgv.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            dgv.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            //dgv.AllowUserToAddRows = false;
            //dgv.AllowUserToResizeRows = false;
            foreach (DataGridViewColumn item in dgv.Columns)
            {
                item.DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
                item.ReadOnly = true;
            }
        }
        private void FlushSearchDataDetailBoard()
        {
            lblLicense.Text = "";
            lblNozzleNo.Text = "";
            lblOilType.Text = "";
            lblArriveTime.Text = "";
            lblLeaveTime.Text = "";
            lblCarLogo.Text = "";
            pictureBoxArrive.Image = null;
            pictureBoxLeave.Image = null;
            pictureBoxPump.Image = null;
        }

        private void InitFormInfo()
        {
            Global.softVersion = INIUnit.GetINIValue(Application.StartupPath + "//version.ini", "main", "version");
            this.Text = "加油站智能信息管理系统SPManager " + Global.softVersion;
            AddListViewHead();
            SetRealtimeDGV(dataGridRealtime);

            this.StationBoard.Visible = Global.bShowStationBoard;
            comboStationDirection.Visible = false;
            checkShowStationBoard.Visible = false;

            FlushStationBoard();
            SetChartFormat();
            toolStationName.Text = "站点名称:" + Global.stationInfo.stationName + "   ";
            comboLogLevel.Visible = false;
            btnReset.Visible = false;

        }
       

        
        private void SetChartFormat()
        {
            chartStatistics.ChartAreas[0].AxisX.Maximum = 26;
            chartStatistics.ChartAreas[0].AxisX.Minimum = 0;
            chartStatistics.ChartAreas[0].AxisX.Interval = 1;
            chartStatistics.ChartAreas[0].AxisY.Minimum = 0;
            chartStatistics.ChartAreas[0].AxisY.Interval = 10;
            chartStatistics.ChartAreas[0].AxisY2.Minimum = 0;
            chartStatistics.Series[0].Color = Color.Blue;
            chartStatistics.Series[1].Color = Color.Red;
        }

        private void QueryHourDataFromDB()
        {
            string sql = "select DATE_FORMAT(leavetime,'%H') hours,count(id) as count from carlog where leavetime > '"+DateTime.Now.ToString("yyyy-MM-dd ")+"00:00:00' GROUP BY hours";
            //string sql = "select DATE_FORMAT(leavetime,'%H') hours,count(id) as count from carlog where leavetime > '2017-05-22 00:00:00' GROUP BY hours";

            DataTable dt = Global.mysqlHelper.GetDataTable(sql);
            for (int i = 0;i<Global.carCount.Length;i++)
            {
                Global.carCount[i] = 0;
            }

            if (dt != null && dt.Rows.Count > 0)
            {
                foreach(DataRow dr in dt.Rows)
                {
                    int index = int.Parse(dr["hours"].ToString());
                    int count = int.Parse(dr["count"].ToString());
                    Global.carCount[index] = count;
                }
            }
            chartStatistics.Series[0].Points.Clear();
            chartStatistics.Series[1].Points.Clear();
            Random ran = new Random();
            for (int i = 0; i < 24; i++)
            {
                chartStatistics.Series[0].Points.AddXY(i.ToString() + ":00", Global.carCount[i]);
                chartStatistics.Series[1].Points.AddXY(i.ToString() + ":00", ran.Next(0, 300));

            }

        }

    }

}
