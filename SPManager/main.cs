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

namespace SPManager
{
     partial class FormMain
    {
        int updateCount = 0;
        [DllImport("user32.dll")]
        static extern uint RegisterWindowMessage(string lpString);
        static uint WM_CARDATA = RegisterWindowMessage("CARDATA");    //抓拍
        protected override void DefWndProc(ref Message m)
        {
            if (m.Msg == Convert.ToInt32(WM_CARDATA))
            {
                Global.LogServer.Add(new LogInfo("Debug", "Main->DefWndProc: 收到动态库车辆消息", (int)EnumLogLevel.DEBUG));
                GetCarFromDll();
            }
            else if (m.Msg == Convert.ToInt32(Global.WM_CARSNAP))
            {
                int nNozzleID = (int)m.WParam;
                int nNozzleStatus = (int)m.LParam;
                
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
                return ret;  
            }
            
            if (!InitParam())
            {
                ret += 1 << 2;
                return ret;
            }
            if (!InitAlg())
            {
                ret += 1 << 3;
                return ret;
            }
            if (!InitDev())
            {
                ret += 1 << 4;
                return ret;
            }
            if (!InitSocket())
            {
                ret += 1 << 5;
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
               
            }
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main:InitDatabase 初始化数据库失败:" + ex.Message,(int)EnumLogLevel.ERROR));
                return false;
            }
            return true;
        }
        private bool InitLogServer()
        {

            try
            {
                Global.LogServer = new Log(Global.nLogLevel);
                Global.LogServer.Run();
            }
            catch(Exception ex)
            {
                return false;
            }
           
            return true;
        }
        
        private bool InitParam()
        {
            GetMainParam();
            GetNozzleChannelParam();
            return true;
        }
       
        private bool GetMainParam()
        {

            string queryString = "select paramName,paramValue,content,defaultValue from param ";
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                foreach (DataRow dr in dt.Rows)
                {
                    string paramName = dr["paramName"].ToString();
                    string paramValue = dr["paramValue"].ToString();
                    if (paramName == "loglevel")
                        Global.nLogLevel = int.Parse(paramValue);
                    else if (paramName == "stationname")
                        Global.stationInfo.stationName = paramValue;
                    else if (paramName == "stationcode")
                        Global.stationInfo.stationCode = paramValue;
                    else if (paramName == "province")
                        Global.stationInfo.province = paramValue;
                    else if (paramName == "city")
                        Global.stationInfo.city = paramValue;
                    else if (paramName == "district")
                        Global.stationInfo.district = paramValue;
                    else if (paramName == "address")
                        Global.stationInfo.addr = paramValue;
                    else if (paramName == "version")
                        Global.softVersion = paramValue;
                    else if (paramName == "updatetime")
                        Global.updateTime = DateTime.Parse(paramValue);
                    else if (paramName == "nvrip")
                        Global.clsNvrInfo.ip = paramValue;
                    else if (paramName == "nvrport")
                        Global.clsNvrInfo.port = int.Parse(paramValue);
                    else if (paramName == "nvradmin")
                        Global.clsNvrInfo.loginName = paramValue;
                    else if (paramName == "nvrpassword")
                        Global.clsNvrInfo.password = paramValue;
                    else if (paramName == "matchmode")
                        Global.nMatchMode = int.Parse(paramValue);
                    else if (paramName == "picpath")
                        Global.basePicPath = paramValue;
                    //TODO 一系列参数的初始化
                }
            }
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetMainParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            //queryString = "select "

            return true;
        }

        private bool GetNozzleChannelParam()
        {
            string queryString = "select a.vchno,b.x1,b.x2,b.y1,b.y2,c.nozzleno,c.oiltype "+
                                    "from (vch a right join analysisarea b on a.id = b.vchid) right join nozzle c on b.id = c.areaid ";
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                foreach (DataRow dr in dt.Rows)
                {
                    ClsNozzle nozzle = new ClsNozzle();
                    nozzle.machineNo = int.Parse(dr["nozzleno"].ToString());
                    nozzle.oilType = int.Parse(dr["oiltype"].ToString());
                    nozzle.recogArea.left = (int)(double.Parse(dr["x1"].ToString()) * Global.nDefaultWidth);
                    nozzle.recogArea.right = (int)(double.Parse(dr["x2"].ToString()) * Global.nDefaultWidth);
                    nozzle.recogArea.top = (int)(double.Parse(dr["y1"].ToString()) * Global.nDefaultHeight);
                    nozzle.recogArea.bottom = (int)(double.Parse(dr["y2"].ToString()) * Global.nDefaultHeight);
                    nozzle.videoChanNo = int.Parse(dr["vchno"].ToString());
                    Global.nozzleList.Add(nozzle);
                   
                    StringBuilder info = new StringBuilder();
                    info.Append("machineNo：" + nozzle.machineNo.ToString());
                    info.Append(" videoChanNo：" + nozzle.videoChanNo.ToString());
                    info.Append(" oilType：" + nozzle.oilType.ToString());
                    info.Append(" left：" + nozzle.recogArea.left.ToString());
                    info.Append(" right：" + nozzle.recogArea.right.ToString());
                    info.Append(" top：" + nozzle.recogArea.top.ToString());
                    info.Append(" bottom：" + nozzle.recogArea.bottom.ToString());
                    Global.LogServer.Add(new LogInfo("Main", "Main->InitParam->GetNozzleChannelParam get param:"+info.ToString(), (int)EnumLogLevel.DEBUG));


                }
            }
            catch(Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetNozzleChannelParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            return true;
        }
        private bool InitSocket()
        {
            Global.socketTool = new SocketTool(Global.socketIP, Global.socketPort);
            Global.clsServiceStatus.bSocketIsRun = Global.socketTool.Run();
            return Global.clsServiceStatus.bSocketIsRun;
           // return true;
        }
        private bool InitDev()
        {
            Global.LogServer.Add(new LogInfo("Debug","main->InitDev in", (int)EnumLogLevel.DEBUG));
            
            int structLenth = Marshal.SizeOf(typeof(struNozzle));
            IntPtr ip = Marshal.AllocHGlobal(Global.nozzleList.Count* structLenth);
            struNozzle[] nozz = new struNozzle[Global.nozzleList.Count];
            byte[] ipp = new byte[1024];
            int offset = 0;
            for (int i =0;i<Global.nozzleList.Count;i++)
            {
                nozz[i].nozzleNo = Global.nozzleList[i].machineNo;
                nozz[i].videoChanNo = Global.nozzleList[i].videoChanNo;
                nozz[i].left = Global.nozzleList[i].recogArea.left;
                nozz[i].right = Global.nozzleList[i].recogArea.right;
                nozz[i].top = Global.nozzleList[i].recogArea.top;
                nozz[i].bottom = Global.nozzleList[i].recogArea.bottom;
                byte[] bNoz = SystemUnit.StrutsToBytesArray(nozz[i]);
                Buffer.BlockCopy(bNoz, 0, ipp, offset,structLenth);
                offset += structLenth;
            }
          
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev->SP_InitNVR begin, param value " + Global.clsNvrInfo.ip + " "
                + Global.clsNvrInfo.port.ToString() + " " + Global.clsNvrInfo.loginName + " " + Global.clsNvrInfo.password, (int)EnumLogLevel.DEBUG));

            int ret = SPlate.SP_InitNVR(Global.clsNvrInfo.ip, Global.clsNvrInfo.port, Global.clsNvrInfo.loginName, Global.clsNvrInfo.password);
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev->SP_InitNVR done, return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));
            
            if (ret == 0)
            {
                SPlate.SP_InitRunParam(ipp, Global.nozzleList.Count);
                Global.LogServer.Add(new LogInfo("Debug", "main:InitDev SP_InitRunParam done return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));
                return true;
            }
            else
                return false;
            
        }
        private bool InitAlg()
        {
            TH_PlateIDCfg th_PlateIDCfg = new TH_PlateIDCfg();
            th_PlateIDCfg.nMaxPlateWidth = 400;
            th_PlateIDCfg.nMinPlateWidth = 60;

            th_PlateIDCfg.nMaxImageWidth = 1920;
            th_PlateIDCfg.nMaxImageHeight = 1080;

            th_PlateIDCfg.nFastMemorySize = 16000;//DSP内存大小  
            th_PlateIDCfg.pFastMemory = Marshal.AllocHGlobal(16000);//DSP申请内存 

            th_PlateIDCfg.pMemory = Marshal.AllocHGlobal(100000000);//申请普通内存  
            th_PlateIDCfg.nMemorySize = 100000000;
            th_PlateIDCfg.bUTF8 = 0;
            th_PlateIDCfg.bShadow = 1;
            th_PlateIDCfg.bCarLogo = 0;
            th_PlateIDCfg.bLeanCorrection = 1;
            th_PlateIDCfg.bCarModel = 0;
            th_PlateIDCfg.bOutputSingleFrame = 1;
            th_PlateIDCfg.bMovingImage = 1;
            Global.LogServer.Add(new LogInfo("Debug", "main->SP_InitAlg begin", (int)EnumLogLevel.DEBUG));
            int lenth = Marshal.SizeOf(th_PlateIDCfg);
            int ret = SPlate.SP_InitAlg(ref th_PlateIDCfg,lenth);
            Global.LogServer.Add(new LogInfo("Debug", "main->SP_InitAlg done, return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));
            if (ret == 0)
                return true;
            else
                return false;
        }

        #endregion

        #region 获取，处理数据

        private void GetNvrConfig()
        {
            IntPtr ip = Marshal.AllocHGlobal(Marshal.SizeOf(Global.net_dvr_cfg));
            int lenth = 0;
            SPlate.SP_GetNvrCfg(ip, ref lenth);
            Global.net_dvr_cfg = (NET_DVR_IPPARACFG_V40)Marshal.PtrToStructure(ip, typeof(NET_DVR_IPPARACFG_V40));
        }
        private void GetCarFromDll()
        {
            int count =  SPlate.SP_GetCarCount();
            Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDLL: 动态库缓存数据长度"+count.ToString(), (int)EnumLogLevel.DEBUG));
            if (count < 1)
                return;
            for (int i =0;i<count;i++)
            {
                struCarInfoOut struCarOut = new struCarInfoOut();
                IntPtr pCarOut = Marshal.AllocHGlobal(Marshal.SizeOf(struCarOut));
                int lenth = 0;
                SPlate.SP_GetFirstCarInfo(pCarOut,ref lenth);
                if (lenth != Marshal.SizeOf(struCarOut))
                {
                    Global.LogServer.Add(new LogInfo("Error", "Main->GetCarFromDLL: 动态库输出结构体与上位机定义结构图长度不一致", (int)EnumLogLevel.ERROR));
                    return;
                }
                struCarOut = (struCarInfoOut)Marshal.PtrToStructure(pCarOut, typeof(struCarInfoOut));
                string license = System.Text.Encoding.Default.GetString(struCarOut.license);
                Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll: 提取动态库车辆信息，车牌号"+license + "  油枪号:"+struCarOut.nNozzleNo, (int)EnumLogLevel.DEBUG));
                
                if (Global.nMatchMode == (int)EnumMatchMode.NON_IN_OUT)//如果为无出入口站点，则直接存库
                {

                    ClsCarInfo info = new ClsCarInfo();
                    info.license = System.Text.Encoding.Default.GetString(struCarOut.license).Trim();
                    info.licenseColor = struCarOut.nColor;
                    info.carLogo = struCarOut.nCarLogo;
                    info.subCarLogo = struCarOut.nSubCarLogo;
                    info.carColor = struCarOut.nCarColor;
                    info.arriveTime = DateTime.Now;  //都取当前时间，再收到DIT信息后修改加油及离开时间
                    info.beginTime = DateTime.Now;
                    info.endTime = DateTime.Now;
                    info.leaveTime = DateTime.Now;
                    info.nozzleNo = struCarOut.nNozzleNo;
                    info.oilType = GetOilType(struCarOut.nNozzleNo);

                    Global.mysqlHelper.ExecuteSql(info.toSaveSqlString());
                    Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll: 无出入口相机模式下，车辆信息入库完成，车牌号" + license + "  油枪号:" + struCarOut.nNozzleNo, (int)EnumLogLevel.DEBUG));

                    ClsPicture pic = new ClsPicture();
                    pic.picBufer = new byte[struCarOut.nPicLenth];
                    Buffer.BlockCopy(struCarOut.pic, 0, pic.picBufer, 0, struCarOut.nPicLenth);
                    pic.picPath = Global.basePicPath + info.arriveTime.ToString("yyyy//MM//dd//") + info.license+"//";
                    pic.picName = info.arriveTime.ToString("HHmmss") + ".jpg";
                    pic.picWidth = struCarOut.nPicWidth;
                    pic.picHeight = struCarOut.nPicHeight;
                    Global.picQueue.Add(pic);


                }
                else if(Global.nMatchMode == (int)EnumMatchMode.WITH_IN_OUT)
                {
                    Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll: 进入WITH_IN_OUT匹配", (int)EnumLogLevel.DEBUG));
                    //string license = System.Text.Encoding.Default.GetString(struCarOut.license);
                    int nozzleNo = struCarOut.nNozzleNo; //油枪号 0位入口，100为出口，其他为真实油枪号
                    switch (nozzleNo)
                    {
                        case 0:  //新添加一条信息入队列
                            AddNewCarToList(struCarOut);
                            break;
                        case 100:
                            ProcCarLeave(struCarOut);
                            break;
                        default:
                            MatchCarInList(struCarOut);
                            break;
                    }

                }
            }
        }
        private void AddNewCarToList(struCarInfoOut carOut)
        {
            ClsCarInfo info = new ClsCarInfo();
            info.license = System.Text.Encoding.Default.GetString(carOut.license);
            info.licenseColor = carOut.nColor;
            info.carLogo = carOut.nCarLogo;
            info.subCarLogo = carOut.nSubCarLogo;
            info.carColor = carOut.nCarColor;
            info.arriveTime = DateTime.Now;  //都取当前时间，再收到DIT信息后修改加油及离开时间
            info.beginTime = DateTime.Now;
            info.endTime = DateTime.Now;
            info.leaveTime = DateTime.Now;
            info.nozzleNo = carOut.nNozzleNo;
            info.matchFlag = 1;
            info.picPath = Global.basePicPath + info.arriveTime.ToString("yyyy\\MM\\dd\\") + info.license + "\\";
            Global.carList.Add(info);
            Global.LogServer.Add(new LogInfo("Run", "Main->AddNewCarToList: a new car added to list   license "+info.license,(int)EnumLogLevel.RUN));

            ClsPicture pic = new ClsPicture();
            pic.picBufer = new byte[carOut.nPicLenth];
            Buffer.BlockCopy(carOut.pic, 0, pic.picBufer, 0, carOut.nPicLenth);
            pic.picPath = info.picPath;
            pic.picName = info.arriveTime.ToString("HHmmss") +"_in"+ ".jpg";
            pic.picWidth = carOut.nPicWidth;
            pic.picHeight = carOut.nPicHeight;
            Global.picQueue.Add(pic);
            //info.oilType = GetOilType(struCarOut.nNozzleNo);
        }

        private void MatchCarInList(struCarInfoOut carOut)
        {
            string license = System.Text.Encoding.Default.GetString(carOut.license).Trim();
            foreach (ClsCarInfo car in Global.carList)
            {
                if (car.license == license)
                {
                    car.nozzleNo = carOut.nNozzleNo;
                    car.oilType = GetOilType(carOut.nNozzleNo);
                    car.beginTime = DateTime.Now;
                    car.endTime = DateTime.Now;
                    car.leaveTime = DateTime.Now;

                    ClsPicture pic = new ClsPicture();
                    pic.picBufer = new byte[carOut.nPicLenth];
                    Buffer.BlockCopy(carOut.pic, 0, pic.picBufer, 0, carOut.nPicLenth);
                    pic.picPath = car.picPath;
                    pic.picName = car.arriveTime.ToString("HHmmss") +"_"+car.nozzleNo.ToString()+ ".jpg";
                    pic.picWidth = carOut.nPicWidth;
                    pic.picHeight = carOut.nPicHeight;
                    Global.picQueue.Add(pic);
                    Global.LogServer.Add(new LogInfo("Run", "Main->AddNewCarToList: 匹配成功，车牌号： " + car.license+" 油枪号:"+car.nozzleNo.ToString(), (int)EnumLogLevel.RUN));
                    return;//匹配成功，结束匹配，返回。
                }
            }
            //未匹配成功

        }
        private void ProcCarLeave(struCarInfoOut carOut)
        {
            string license = System.Text.Encoding.Default.GetString(carOut.license).Trim();
            foreach (ClsCarInfo car in Global.carList)
            {
                if (car.license == license)
                {
                    car.endTime = DateTime.Now;
                    car.leaveTime = DateTime.Now;

                    ClsPicture pic = new ClsPicture();
                    pic.picBufer = new byte[carOut.nPicLenth];
                    Buffer.BlockCopy(carOut.pic, 0, pic.picBufer, 0, carOut.nPicLenth);
                    pic.picPath = pic.picPath = car.picPath;
                    pic.picName = car.leaveTime.ToString("HHmmss") + "_out"+ ".jpg";
                    pic.picWidth = carOut.nPicWidth;
                    pic.picHeight = carOut.nPicHeight;
                    Global.picQueue.Add(pic);

                    Global.mysqlHelper.ExecuteSql(car.toSaveSqlString());
                    Global.carList.Remove(car);

                    Global.LogServer.Add(new LogInfo("Run", "Main->ProcCarLeave: 车辆匹配存储完毕", (int)EnumLogLevel.RUN));
                    return;
                }
            }

        }
        //private void MatchCarInList(struCarInfoOut struCarInfo)
        //{
        //    //1.判断为出入口相机或加油机相机
        //    if (Global.nMatchMode == 1) //有出入口相机
        //    {
        //    } 
        //    else if (Global.nMatchMode == 2) //无出入口相机
        //    {
        //        ClsCarInfo carInfo = new ClsCarInfo();
        //        carInfo.arriveTime = DateTime.Now;
        //        carInfo.license = System.Text.Encoding.Default.GetString(struCarInfo.license);
        //        carInfo.licenseColor = struCarInfo.nColor;
        //        carInfo.carColor = struCarInfo.nCarColor;
        //        carInfo.carLogo = struCarInfo.nCarLogo;
        //        carInfo.nozzleNo = struCarInfo.nNozzleNo;
        //        carInfo.oilType = GetOilType(struCarInfo.nNozzleNo);
        //        string picPath = Global.basePicPath + "\\" + DateTime.Now.ToString("yyyy\\MM\\dd")+"\\"+carInfo.license;
        //        carInfo.picPath = picPath;
        //        carInfo.matchFlag = 1;
        //        Global.carList.Add(carInfo);

        //        struPic pic = new struPic();
        //        pic.sPicPath = picPath;
        //        pic.nPicType = struCarInfo.nPicType;
        //        pic.nWidth = struCarInfo.nPicWidth;
        //        pic.nHeight = struCarInfo.nPicHeight;
        //        pic.nLenth = struCarInfo.nPicLenth;
        //        pic.nSaveType = 2;
        //        Buffer.BlockCopy(struCarInfo.pic, 0, pic.brPicBuffer, 0, struCarInfo.nPicLenth);

        //    }
            
        //}

        private void ProcSnapFromDIT(int nozzleNo,int nozzleStatus)
        {

            NET_DVR_PLATE_RESULT snapData = new NET_DVR_PLATE_RESULT();
            snapData.byPumpID = (byte)nozzleNo;
            snapData.byPumpStatus = (byte)nozzleStatus;

            foreach (ClsCarInfo car in Global.carList)
            {
                if (car.nozzleNo == nozzleNo)
                {
                    snapData.sLicense = new byte[16];
                    byte[] license = System.Text.Encoding.Default.GetBytes(car.license);
                    Buffer.BlockCopy(license, 0, snapData.sLicense, 0, license.Length);
                    snapData.byColor = (byte)car.carColor;
                    snapData.byPlateColor = (byte)car.licenseColor;
                    snapData.byVehicleShape = (byte)car.type;
                    snapData.wVehicleLogoRecog = (short)car.carLogo;
                    snapData.wVehicleSubLogoRecog = (short)car.subCarLogo;

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

                    switch (nozzleStatus)
                    {
                        case 0:  //不生效 默认开始时间
                            car.beginTime = DateTime.Now;
                            break;
                        case 1:  //提枪
                            car.beginTime = DateTime.Now;
                            break;
                        case 2: //加油
                            car.beginTime = DateTime.Now;
                            break;
                        case 3: //挂枪
                            car.endTime = DateTime.Now;
                            if (Global.nMatchMode == (int)EnumMatchMode.NON_IN_OUT)
                            {
                                Global.mysqlHelper.ExecuteSql(car.toSaveSqlString());

                                //TODO 添加锁
                                Global.carList.Remove(car);
                            }
                            break;
                        default:
                            car.beginTime = DateTime.Now;
                            break;
                    }
                    return;
                }
            }
            
            


        }

        private bool FindSnapDataInList(ref NET_DVR_PLATE_RESULT snapData,int nozzleNo)
        {
            
            foreach (ClsCarInfo car in Global.carList)
            {
                if (car.nozzleNo == nozzleNo)
                {
                    snapData.sLicense = new byte[16];
                    byte[] license = System.Text.Encoding.Default.GetBytes(car.license);
                    Buffer.BlockCopy(license, 0, snapData.sLicense, 0, license.Length);
                    snapData.byColor = (byte)car.carColor;
                    snapData.byPlateColor = (byte)car.licenseColor;
                    snapData.byVehicleShape = (byte)car.type;
                    snapData.wVehicleLogoRecog = (short)car.carLogo;
                    snapData.wVehicleSubLogoRecog = (short)car.subCarLogo;
                    return true;
                }
            }
            return false;
        }

        private void SavePicToDisk(ClsPicture pic)
        {
            
        }
        
        private int GetOilType(int nozzleNo)
        {
            foreach (ClsNozzle nozz in Global.nozzleList)
            {
                if (nozzleNo == nozz.machineNo)
                {
                    return nozz.oilType;
                }
            }
            return 1;
        }
        #endregion

        private void showMemoryInfo()
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

        private void checkSoftUpdate()
        {
            if (lastUpdateTime.AddDays(1).CompareTo(DateTime.Now) < 0)
            {
                Process proc = Process.Start(Global.updateAppName);
                if (proc != null)
                {
                    ExitApp();
                }
            }
        }
        private void ExitApp()
        {
            SPlate.SP_Close();
            if (Global.LogServer != null)
                Global.LogServer.Stop();
            this.toExit = true;
            Application.Exit();
        }
    }
}
