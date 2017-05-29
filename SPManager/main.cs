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
        static uint WM_CARDATA = RegisterWindowMessage("CAR");    //抓拍
        DateTime lastMessageTime = DateTime.Now;
        protected override void DefWndProc(ref Message m)
        {
            if (m.Msg == Convert.ToInt32(WM_CARDATA))
            {
                MessageBox.Show("1");
                lastUpdateTime = DateTime.Now;
                Global.LogServer.Add(new LogInfo("Debug", "Main->DefWndProc: 收到动态库车辆消息", (int)EnumLogLevel.DEBUG));
                GetCarFromDll_Array();
            }
            else if (m.Msg == Convert.ToInt32(Global.WM_CARSNAP))
            {
                
                int nNozzleID = (int)m.WParam;
                int nNozzleStatus = (int)m.LParam;
                if (richTextBoxDIT.Lines.Length > 200)
                {
                    richTextBoxDIT.Clear();
                }
                richTextBoxDIT.AppendText("DIT信号:油枪" + nNozzleID.ToString() + " 状态" + nNozzleStatus.ToString()+"\n");

                Global.LogServer.Add(new LogInfo("Run", "Main->DefWndProc: 收到DIT消息,油枪号：" + nNozzleID.ToString() + "  状态号:"+nNozzleStatus.ToString(), (int)EnumLogLevel.RUN));
               // ProcSnapFromDIT(nNozzleID, nNozzleStatus);
                //ProcSnapFromDIT_Backward(nNozzleID, nNozzleStatus);
                ProcSnapFromDIT_Array(nNozzleID, nNozzleStatus);
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
                //return ret;  
            }
            
            if (!InitParam())
            {
                ret += 1 << 2;
                //return ret;
            }
            if (!InitAlg())
            {
                ret += 1 << 3;
                //return ret;
            }
            if (!InitDev())
            {
                ret += 1 << 4;
                //return ret;
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
        private bool InitPicWork()
        {
            try
            {
                Global.picWork = new PictureWork();
                Global.picWork.Run();
                Global.LogServer.Add(new LogInfo("Debug", "main->InitPicWork done ", (int)EnumLogLevel.DEBUG));
            }
            catch (Exception ex)
            {
                return false;
            }

            return true;
        }
        
        private bool InitParam()
        {
            GetMainParam();
            GetVideoHostParam();
            GetAreaNozzleParam();
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
                    //else if (paramName == "nvrip")
                    //    Global.clsNvrInfo.ip = paramValue;
                    //else if (paramName == "nvrport")
                    //    Global.clsNvrInfo.port = int.Parse(paramValue);
                    //else if (paramName == "nvradmin")
                    //    Global.clsNvrInfo.loginName = paramValue;
                    //else if (paramName == "nvrpassword")
                    //    Global.clsNvrInfo.password = paramValue;
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


        private void GetVideoHostParam()
        {
            string queryString = "select * from videohost limit 0,1";
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                if (dt == null || dt.Rows.Count < 1)
                {
                    Global.LogServer.Add(new LogInfo("Error", "Main->GetVideoHostParam 获取NVR信息失败！数据为空", (int)EnumLogLevel.ERROR));
                    return;
                }
                foreach (DataRow dr in dt.Rows)
                {
                    ClsNVRInfo nvr = new ClsNVRInfo();
                    Global.clsNvrInfo.id = int.Parse(dr["id"].ToString());
                    Global.clsNvrInfo.nvrType = dr["hosttype"].ToString();
                    Global.clsNvrInfo.nvrName = dr["hostname"].ToString();
                    Global.clsNvrInfo.ip = dr["hostip"].ToString();
                    Global.clsNvrInfo.password = dr["loginpwd"].ToString();
                    Global.clsNvrInfo.loginName = dr["loginname"].ToString();
                    Global.clsNvrInfo.port = int.Parse(dr["hostport"].ToString());
                }
            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->GetVideoHostParam 获取NVR信息失败:" + ex.Message, (int)EnumLogLevel.ERROR));
               
            }
        }
        private bool GetAreaNozzleParam()
        {
            string queryString = "select a.vchno,a.vchAttr,b.id,b.x1,b.x2,b.y1,b.y2,b.vchid from vch a right join analysisarea b on a.id = b.vchid ";
            try
            {
                int index = 0;
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);

                Global.arrayAreaCar = new ClsCarInfo[dt.Rows.Count];
                for (int i =0;i<dt.Rows.Count;i++)
                {
                    Global.arrayAreaCar[i] = new ClsCarInfo();
                }
                foreach (DataRow dr in dt.Rows)
                {
                   
                    ClsRecogArea area = new ClsRecogArea();
                    area.left = double.Parse(dr["x1"].ToString());
                    area.right = double.Parse(dr["x2"].ToString());
                    area.top = double.Parse(dr["y1"].ToString());
                    area.bottom = double.Parse(dr["y2"].ToString());
                    area.id = int.Parse(dr["id"].ToString());
                    area.videoid = int.Parse(dr["vchid"].ToString());
                    area.videoChannel = int.Parse(dr["vchno"].ToString());
                    area.areaFlag = int.Parse(dr["vchAttr"].ToString());
                    Global.areaMap.Add(area.id, index);
                    Global.arrayAreaCar[index].areaNo = area.id;
                    Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetAreaNozzleParam 识别区映射 " + area.id.ToString()+":"+index.ToString(), (int)EnumLogLevel.DEBUG));
                    index++;
                    if (area.areaFlag == 99)
                    {
                        Global.entryAreaID = area.id;
                        Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetAreaNozzleParam 入口识别区:" + area.id.ToString(), (int)EnumLogLevel.DEBUG));
                    } 
                    else if(area.areaFlag == 100)
                    {
                        Global.exitAreaID = area.id;
                        Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetAreaNozzleParam 出口识别区:" + area.id.ToString(), (int)EnumLogLevel.DEBUG));
                    }
                    string sqlString = "select * from nozzle where areaid = " + area.id.ToString();
                    DataTable dt2 = Global.mysqlHelper.GetDataTable(sqlString);
                    if (dt2.Rows.Count > 0)
                    {
                        foreach (DataRow dr2 in dt2.Rows)
                        {
                            ClsNozzle nozzle = new ClsNozzle();
                            nozzle.areaid = area.id;
                            nozzle.oilType = int.Parse(dr2["oiltype"].ToString());
                            nozzle.nozzleNo = int.Parse(dr2["nozzleno"].ToString());
                            Global.nozzleList.Add(nozzle);
                            area.nozzleList.Add(nozzle);
                            StringBuilder loginfo = new StringBuilder();
                            loginfo.Append(" areaid：" + area.id.ToString());
                            loginfo.Append("nozzleNo：" + nozzle.nozzleNo.ToString());
                            loginfo.Append(" oilType：" + nozzle.oilType.ToString());
                            Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetAreaNozzleParam get param:" + loginfo.ToString(), (int)EnumLogLevel.DEBUG));

                        }
                    }
                    Global.areaList.Add(area);
                   
                    StringBuilder info = new StringBuilder();
                    info.Append(" areaid：" + area.id.ToString());
                    info.Append(" left：" + area.left.ToString());
                    info.Append(" right：" + area.right.ToString());
                    info.Append(" top：" + area.top.ToString());
                    info.Append(" bottom：" + area.bottom.ToString());
                    Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetAreaNozzleParam get param:" + info.ToString(), (int)EnumLogLevel.DEBUG));
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
            Global.LogServer.Add(new LogInfo("Debug", "main->InitSocket done ", (int)EnumLogLevel.DEBUG));
            return Global.clsServiceStatus.bSocketIsRun;
           // return true;
        }
        private bool InitDev()
        {
            Global.LogServer.Add(new LogInfo("Debug","main->InitDev in", (int)EnumLogLevel.DEBUG));
            
            int structLenth = Marshal.SizeOf(typeof(struArea));
            //IntPtr ip = Marshal.AllocHGlobal(Global.nozzleList.Count* structLenth);
            struArea[] area = new struArea[Global.nozzleList.Count];
            byte[] ipp = new byte[1024];
            int offset = 0;
            for (int i =0;i<Global.areaList.Count;i++)
            {
                area[i].areaNo = Global.areaList[i].id;
                area[i].videoChanNo = Global.areaList[i].videoChannel;
                area[i].left = (int)(Global.areaList[i].left*Global.nDefaultHeight);
                area[i].right = (int)(Global.areaList[i].right*Global.nDefaultWidth);
                area[i].top = (int)(Global.areaList[i].top * Global.nDefaultHeight);
                area[i].bottom = (int)(Global.areaList[i].bottom * Global.nDefaultHeight);
                area[i].areaFlag = Global.areaList[i].areaFlag;
                byte[] bArea = SystemUnit.StrutsToBytesArray(area[i]);
                Buffer.BlockCopy(bArea, 0, ipp, offset,structLenth);
                offset += structLenth;
            }
          
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev->SP_InitNVR begin, param value " + Global.clsNvrInfo.ip + " "
                + Global.clsNvrInfo.port.ToString() + " " + Global.clsNvrInfo.loginName + " " + Global.clsNvrInfo.password, (int)EnumLogLevel.DEBUG));

            int ret = SPlate.SP_InitNVR(Global.clsNvrInfo.ip, Global.clsNvrInfo.port, Global.clsNvrInfo.loginName, Global.clsNvrInfo.password);
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev->SP_InitNVR done, return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));
            
            if (ret == 0)
            {
                SPlate.SP_InitRunParam(ipp, Global.areaList.Count);
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

            th_PlateIDCfg.nMaxImageWidth = 2100;
            th_PlateIDCfg.nMaxImageHeight = 1500;

            th_PlateIDCfg.nFastMemorySize = 16000;//DSP内存大小  
            th_PlateIDCfg.pFastMemory = Marshal.AllocHGlobal(16000);//DSP申请内存 

            th_PlateIDCfg.pMemory = Marshal.AllocHGlobal(100000000);//申请普通内存  
            th_PlateIDCfg.nMemorySize = 100000000;
            th_PlateIDCfg.bUTF8 = 0;
            th_PlateIDCfg.bShadow = 1;
            th_PlateIDCfg.bCarLogo = 0;
            th_PlateIDCfg.bLeanCorrection = 1;
            th_PlateIDCfg.bCarModel = 0;

            //TODO 注意模式切换
            th_PlateIDCfg.bOutputSingleFrame = 0;  
            th_PlateIDCfg.bMovingImage = 0;   //0 识别静止图片，1识别动态视频（结果输出延时）
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
                try
                {
                    struCarInfoOut struCarOut = new struCarInfoOut();
                    IntPtr pCarOut = Marshal.AllocHGlobal(Marshal.SizeOf(struCarOut));
                    int lenth = 0;

                    SPlate.SP_GetFirstCarInfo(pCarOut, ref lenth);
                    if (lenth != Marshal.SizeOf(struCarOut))
                    {
                        Global.LogServer.Add(new LogInfo("Error", "Main->GetCarFromDLL: 动态库输出结构体与上位机定义结构图长度不一致", (int)EnumLogLevel.ERROR));
                        return;
                    }
                    struCarOut = (struCarInfoOut)Marshal.PtrToStructure(pCarOut, typeof(struCarInfoOut));
                    Marshal.FreeHGlobal(pCarOut);
                    string license = System.Text.Encoding.Default.GetString(struCarOut.license);
                    Global.LogServer.Add(new LogInfo("Run", "Main->GetCarFromDll: 提取动态库车辆信息，车牌号:" + license + "  识别区号:" + struCarOut.nAreaNo, (int)EnumLogLevel.RUN));
                  
                    if (Global.nMatchMode == (int)EnumMatchMode.NON_IN_OUT)
                    {


                        ClsCarInfo info = new ClsCarInfo();
                        info.license = license;
                        info.licenseColor = struCarOut.nColor;
                        info.carLogo = struCarOut.nCarLogo;
                        info.subCarLogo = struCarOut.nSubCarLogo;
                        info.carColor = struCarOut.nCarColor;
                        info.arriveTime = DateTime.Now;  //都取当前时间，再收到DIT信息后修改加油及离开时间
                        info.beginTime = DateTime.Now;
                        info.endTime = DateTime.Now;
                        info.leaveTime = DateTime.Now;
                        info.areaNo = struCarOut.nAreaNo;
                        lock (Global.lockObj)
                        {
                            Global.carList.Add(info);
                        }
                            

                        //Global.mysqlHelper.ExecuteSql(info.toSaveSqlString());
                        Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll: 无出入口相机模式下，车辆入队列；车牌号" + license + "  识别区号:" + struCarOut.nAreaNo, (int)EnumLogLevel.DEBUG));

                        ClsPicture pic = new ClsPicture();
                        pic.picBufer = new byte[struCarOut.nPicLenth];
                        Buffer.BlockCopy(struCarOut.pic, 0, pic.picBufer, 0, struCarOut.nPicLenth);
                        pic.picPath =Global.basePicPath + info.arriveTime.ToString("yyyyMMdd") +"\\"+ info.license.Trim() + "\\";
                        
                       // Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll: 车辆图片入队列,图片路径：" + pic.picPath+ pic.picName, (int)EnumLogLevel.DEBUG));
                        pic.picName = info.arriveTime.ToString("HHmmss") + ".jpg";
                        pic.picWidth = struCarOut.nPicWidth;
                        pic.picHeight = struCarOut.nPicHeight;
                        pic.picType = struCarOut.nPicType;
                        Global.picWork.Add(pic);
                        Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll: 车辆图片入队列,图片路径：" + pic.picPath +pic.picName, (int)EnumLogLevel.DEBUG));
                        
                    }
                    else if (Global.nMatchMode == (int)EnumMatchMode.WITH_IN_OUT)
                    {
                        Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll: 进入WITH_IN_OUT匹配", (int)EnumLogLevel.DEBUG));
                        //string license = System.Text.Encoding.Default.GetString(struCarOut.license);
                        int areaNo = struCarOut.nAreaNo; //
                        if (areaNo == Global.entryAreaID) 
                        {
                            if(checkRepeatLicense(areaNo, license))
                                continue;
                            sendCallbackInfo(struCarOut, 1);
                            AddNewCarToList(struCarOut);
                        } 
                        else if(areaNo == Global.exitAreaID)
                        {
                            if (checkRepeatLicense(areaNo, license))
                                continue;
                            sendCallbackInfo(struCarOut, 2);
                            ProcCarLeave(struCarOut);
                        }
                        else
                        {
                            MatchCarInList(struCarOut);
                        }
                    }
                    
                }
                catch (System.Exception ex)
                {
                    Global.LogServer.Add(new LogInfo("Error", "Main->GetCarFromDll " + ex.Message, (int)EnumLogLevel.ERROR));

                }
                
            }
        }

        private void GetCarFromDll_Array()
        {
            int count = SPlate.SP_GetCarCount();
            Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll_Array: 动态库缓存数据长度" + count.ToString(), (int)EnumLogLevel.DEBUG));
            if (count < 1)
                return;
            for (int i = 0; i < count; i++)
            {
               
                struCarInfoOut struCarOut = new struCarInfoOut();
                IntPtr pCarOut = Marshal.AllocHGlobal(Marshal.SizeOf(struCarOut));
                int lenth = 0;

                SPlate.SP_GetFirstCarInfo(pCarOut, ref lenth);
                if (lenth != Marshal.SizeOf(struCarOut))
                {
                    Global.LogServer.Add(new LogInfo("Error", "Main->GetCarFromDll_Array: 动态库输出结构体与上位机定义结构图长度不一致", (int)EnumLogLevel.ERROR));
                    return;
                }
                struCarOut = (struCarInfoOut)Marshal.PtrToStructure(pCarOut, typeof(struCarInfoOut));
                Marshal.FreeHGlobal(pCarOut);
                string license = System.Text.Encoding.Default.GetString(struCarOut.license);
                Global.LogServer.Add(new LogInfo("Run", "Main->GetCarFromDll_Array: 提取动态库车辆信息，车牌号:" + license + "  识别区号:" + struCarOut.nAreaNo, (int)EnumLogLevel.RUN));
                if (checkRepeatLicense(struCarOut.nAreaNo, license))
                {
                    Global.LogServer.Add(new LogInfo("Run", "Main->GetCarFromDll_Array: 对应区域车牌重复", (int)EnumLogLevel.RUN));
                    continue;
                }

                int index = Global.areaMap[struCarOut.nAreaNo];
                if (struCarOut.nAreaNo == Global.entryAreaID)
                    {
                        sendCallbackInfo(struCarOut, 1);
                        Global.entryLicenseList.Add(license);
                        if (Global.entryLicenseList.Count > 20)
                        {
                            Global.entryLicenseList.RemoveAt(0);
                        }
                        
                    } 
                    else if(struCarOut.nAreaNo == Global.exitAreaID)
                    {
                        sendCallbackInfo(struCarOut, 2);
                        ProcCarLeave_Array(struCarOut);
                        Global.entryLicenseList.Add(license);
                        if (Global.entryLicenseList.Count > 20)
                        {
                        Global.entryLicenseList.RemoveAt(0);
                        }

                }
                else
                {
                    
                    Global.arrayAreaCar[index].license = license;
                    Global.arrayAreaCar[index].licenseColor = struCarOut.nColor;
                    Global.arrayAreaCar[index].carLogo = struCarOut.nCarLogo;
                    Global.arrayAreaCar[index].subCarLogo = struCarOut.nSubCarLogo;
                    Global.arrayAreaCar[index].carColor = struCarOut.nCarColor;
                    Global.arrayAreaCar[index].arriveTime = DateTime.Now;  //都取当前时间，再收到DIT信息后修改加油及离开时间
                    Global.arrayAreaCar[index].beginTime = DateTime.Now;
                    Global.arrayAreaCar[index].endTime = DateTime.Now;
                    Global.arrayAreaCar[index].leaveTime = DateTime.Now;
                    Global.arrayAreaCar[index].areaNo = struCarOut.nAreaNo;
                    Global.arrayAreaCar[index].matchFlag = 0;
                }
                    ClsPicture pic = new ClsPicture();
                    pic.picBufer = new byte[struCarOut.nPicLenth];
                    Buffer.BlockCopy(struCarOut.pic, 0, pic.picBufer, 0, struCarOut.nPicLenth);
                    pic.picPath = Global.basePicPath + Global.arrayAreaCar[index].arriveTime.ToString("yyyyMMdd") + "\\" + Global.arrayAreaCar[index].license.Trim() + "\\";

                    // Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll: 车辆图片入队列,图片路径：" + pic.picPath+ pic.picName, (int)EnumLogLevel.DEBUG));
                    pic.picName = Global.arrayAreaCar[index].arriveTime.ToString("HHmmss") + ".jpg";
                    pic.picWidth = struCarOut.nPicWidth;
                    pic.picHeight = struCarOut.nPicHeight;
                    pic.picType = struCarOut.nPicType;
                    Global.picWork.Add(pic);
                    Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll_Array: 车辆图片入队列,图片路径：" + pic.picPath + pic.picName, (int)EnumLogLevel.DEBUG));
                
            }
        }
        private bool checkRepeatLicense(int areaId,string license)
        {
            try
            {
                if (areaId == Global.exitAreaID)
                {
                    foreach (string lic in Global.exitLicenseList)
                    {
                        if (lic == license)
                        {
                            return true;
                        }
                    }
                    return false;
                }
                else if (areaId == Global.entryAreaID)
                {
                    foreach (string lic in Global.entryLicenseList)
                    {
                        if (lic == license)
                        {
                            return true;
                        }
                    }
                    return false;
                }
                else
                {
                    foreach (ClsCarInfo car in Global.carList)
                    {
                        if (areaId == car.areaNo && license == car.license)
                        {
                            return true;
                        }
                    }
                    return false;
                }
            }
            catch (System.Exception ex)
            {
                return false;
            }
            
           
            
           
        }

        private void showCarList()
        {
            listViewCache.Items.Clear();
            listViewCache.BeginUpdate();

            for (int i = 0; i < Global.arrayAreaCar.Length; i++)
            {
                ListViewItem lvi = new ListViewItem();
                lvi.Text = i.ToString();
                lvi.SubItems.Add(Global.arrayAreaCar[i].areaNo.ToString());
                lvi.SubItems.Add(Global.arrayAreaCar[i].license);
                lvi.SubItems.Add(Global.arrayAreaCar[i].nozzleNo.ToString());
                lvi.SubItems.Add(Global.arrayAreaCar[i].matchFlag.ToString());
                listViewCache.Items.Add(lvi);
            }
            listViewCache.EndUpdate();


        }

        private void showCarArray()
        {
            listViewCache.Items.Clear();
            listViewCache.BeginUpdate();
            for (int i= 0;i<Global.arrayAreaCar.Length;i++)
            {
                ListViewItem lvi = new ListViewItem();
                lvi.Text = (i+1).ToString();
                lvi.SubItems.Add(Global.arrayAreaCar[i].areaNo.ToString());
                lvi.SubItems.Add(Global.arrayAreaCar[i].license);
                lvi.SubItems.Add(Global.arrayAreaCar[i].nozzleNo.ToString());
                lvi.SubItems.Add(Global.arrayAreaCar[i].matchFlag.ToString());
                listViewCache.Items.Add(lvi);
            }
            listViewCache.EndUpdate();
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
            info.areaNo = carOut.nAreaNo;
            info.picPath = Global.basePicPath + info.arriveTime.ToString("yyyy\\MM\\dd") + "\\"+info.license.Trim() + "\\";
            
            lock (Global.lockObj)
            {
                Global.carList.Add(info);
            }
            Global.LogServer.Add(new LogInfo("Run", "Main->AddNewCarToList: a new car added to list   license "+info.license,(int)EnumLogLevel.RUN));

            ClsPicture pic = new ClsPicture();
            pic.picBufer = new byte[carOut.nPicLenth];
            Buffer.BlockCopy(carOut.pic, 0, pic.picBufer, 0, carOut.nPicLenth);
            pic.picPath = info.picPath;
            pic.picName = info.arriveTime.ToString("HHmmss") +"_in"+ ".jpg";
            pic.picWidth = carOut.nPicWidth;
            pic.picHeight = carOut.nPicHeight;
            pic.picType = carOut.nPicType;
            Global.picWork.Add(pic);
            //info.oilType = GetOilType(struCarOut.nNozzleNo);
        }
        private void AddPumpCarToList(struCarInfoOut carOut)
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
            info.areaNo = carOut.nAreaNo;
            info.picPath = Global.basePicPath + info.arriveTime.ToString("yyyy\\MM\\dd") + "\\" + info.license.Trim() + "\\";
            lock (Global.lockObj)
            {
                Global.carList.Add(info);
            }
            Global.LogServer.Add(new LogInfo("Run", "Main->AddNewCarToList:  油枪区域车辆在入口中匹配失败，作为新车辆加入队列,车牌号： " + info.license, (int)EnumLogLevel.RUN));

            ClsPicture pic = new ClsPicture();
            pic.picBufer = new byte[carOut.nPicLenth];
            Buffer.BlockCopy(carOut.pic, 0, pic.picBufer, 0, carOut.nPicLenth);
            pic.picPath = info.picPath;
            pic.picName = info.arriveTime.ToString("HHmmss")  + ".jpg";
            pic.picWidth = carOut.nPicWidth;
            pic.picHeight = carOut.nPicHeight;
            pic.picType = carOut.nPicType;
            Global.picWork.Add(pic);
        }

        private void MatchCarInList(struCarInfoOut carOut)
        {
            string license = System.Text.Encoding.Default.GetString(carOut.license).Trim();
            lock(Global.lockObj)
            {
                foreach (ClsCarInfo car in Global.carList)
                {
                    if (car.license == license)
                    {
                        car.areaNo = carOut.nAreaNo;
                        car.beginTime = DateTime.Now;
                        car.endTime = DateTime.Now;
                        car.leaveTime = DateTime.Now;

                        ClsPicture pic = new ClsPicture();
                        pic.picBufer = new byte[carOut.nPicLenth];
                        Buffer.BlockCopy(carOut.pic, 0, pic.picBufer, 0, carOut.nPicLenth);
                        pic.picPath = car.picPath;
                        pic.picName = car.arriveTime.ToString("HHmmss") + "_" + car.nozzleNo.ToString() + ".jpg";
                        pic.picWidth = carOut.nPicWidth;
                        pic.picHeight = carOut.nPicHeight;
                        pic.picType = carOut.nPicType;
                        Global.picWork.Add(pic);
                        Global.LogServer.Add(new LogInfo("Run", "Main->MatchCarInList: 匹配成功，车牌号： " + car.license + " 识别区号:" + car.areaNo.ToString(), (int)EnumLogLevel.RUN));
                        return;//匹配成功，结束匹配，返回。
                    }
                }
            }
            //未返回则匹配失败,新加入队列
            AddPumpCarToList(carOut);
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
                    pic.picPath  = car.picPath;
                    pic.picName = car.leaveTime.ToString("HHmmss") + "_out"+ ".jpg";
                    pic.picWidth = carOut.nPicWidth;
                    pic.picHeight = carOut.nPicHeight;
                    pic.picType = carOut.nPicType;
                    Global.picWork.Add(pic);

                    Global.mysqlHelper.ExecuteSql(car.toSaveSqlString());
                    Global.LogServer.Add(new LogInfo("Run", "Main->ProcCarLeave: 车辆出站匹配存储完毕,车牌:"+license, (int)EnumLogLevel.RUN));
                    Global.carList.Remove(car);
                    return;
                }
            }
            //未匹配到车辆，直接入库
            Global.LogServer.Add(new LogInfo("Run", "Main->ProcCarLeave: 车辆出站未匹配到车辆，直接入库。车牌：", (int)EnumLogLevel.RUN));
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
            info.areaNo = carOut.nAreaNo;
            info.picPath = Global.basePicPath + info.arriveTime.ToString("yyyy\\MM\\dd") + "\\" + info.license.Trim() + "\\";
            Global.mysqlHelper.ExecuteSql(info.toSaveSqlString());

            ClsPicture pic2 = new ClsPicture(); 
            pic2.picBufer = new byte[carOut.nPicLenth];
            Buffer.BlockCopy(carOut.pic, 0, pic2.picBufer, 0, carOut.nPicLenth);
            pic2.picPath = info.picPath;
            pic2.picName = info.leaveTime.ToString("HHmmss") + "_out" + ".jpg";
            pic2.picWidth = carOut.nPicWidth;
            pic2.picHeight = carOut.nPicHeight;
            pic2.picType = carOut.nPicType;
            Global.picWork.Add(pic2);


        }


        private void ProcCarLeave_Array(struCarInfoOut carOut)
        {
            string now = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            string license = System.Text.Encoding.Default.GetString(carOut.license);
            string sqlString = "update carlog set leavetime = '" + now +
                "' where carnumber = '" + carOut.license + "' order by arrivetime desc limit 1";
            Global.mysqlHelper.ExecuteSql(sqlString);
        }
        private void ProcSnapFromDIT(int nozzleNo,int nozzleStatus)
        {
            NET_DVR_PLATE_RESULT snapData = new NET_DVR_PLATE_RESULT();
            snapData.byPumpID = (byte)nozzleNo;
            snapData.byPumpStatus = (byte)nozzleStatus;
            snapData.sLicense = new byte[16];
            int areaId = GetAreaIdByNozzNo(nozzleNo);
            bool bMatched = false;
            foreach (ClsCarInfo car in Global.carList)
            {
                if (car.areaNo == areaId)
                {
                    bMatched = true;
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

                    Global.LogServer.Add(new LogInfo("Run", "Main->ProcSnapFromDIT: 发送车辆信息到DIT  车牌号:"+car.license + "  油枪号："+ nozzleNo.ToString(), (int)EnumLogLevel.RUN));
                    car.nozzleNo = nozzleNo;
                    DateTime dt = DateTime.Now;
                    switch (nozzleStatus)
                    {
                        case 0:  //不生效 默认开始时间
                            car.beginTime = dt;
                            break;
                        case 1:  //提枪
                            car.beginTime = dt;
                            car.endTime = dt;
                            car.leaveTime = dt;
                            break;
                        case 2: //加油
                            car.beginTime = dt;
                            car.endTime = dt;
                            car.leaveTime = dt;
                            break;
                        case 3: //挂枪
                            car.endTime = dt;
                            car.leaveTime = dt;
                            if (Global.nMatchMode == (int)EnumMatchMode.NON_IN_OUT)
                            {
                                Global.mysqlHelper.ExecuteSql(car.toSaveSqlString());

                                //TODO 添加锁
                                lock (Global.lockObj)
                                {
                                    Global.carList.Remove(car);
                                }
                            }
                            break;
                        default:
                            car.beginTime = DateTime.Now;
                            break;
                    }
                    return;
                }
            }
            if (!bMatched)
            {
               // byte[] license = System.Text.Encoding.Default.GetBytes("无车牌");
               // Buffer.BlockCopy(license, 0, snapData.sLicense, 0, license.Length);
                snapData.byColor = 0;
                snapData.byPlateColor = 0;
                snapData.byVehicleShape = 0;
                snapData.wVehicleLogoRecog = 0;
                snapData.wVehicleSubLogoRecog = 0;

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
                Global.LogServer.Add(new LogInfo("Run", "Main->ProcSnapFromDIT: 未匹配到车牌信息，回复空信息  " + "  油枪号：" + nozzleNo.ToString(), (int)EnumLogLevel.RUN));
            }
        }

        private void ProcSnapFromDIT_Backward(int nozzleNo, int nozzleStatus)
        {
            NET_DVR_PLATE_RESULT snapData = new NET_DVR_PLATE_RESULT();
            snapData.byPumpID = (byte)nozzleNo;
            snapData.byPumpStatus = (byte)nozzleStatus;
            snapData.sLicense = new byte[16];
            int areaId = GetAreaIdByNozzNo(nozzleNo);
            bool bMatched = false;
            //foreach (ClsCarInfo car in Global.carList)
            lock (Global.lockObj)
            {
                for (int i = Global.carList.Count - 1; i >= 0; i--)
                {
                    if (areaId == Global.carList[i].areaNo)
                    {
                        byte[] license = System.Text.Encoding.Default.GetBytes(Global.carList[i].license);
                        Buffer.BlockCopy(license, 0, snapData.sLicense, 0, license.Length);
                        snapData.byColor = (byte)Global.carList[i].carColor;
                        snapData.byPlateColor = (byte)Global.carList[i].licenseColor;
                        snapData.byVehicleShape = (byte)Global.carList[i].type;
                        snapData.wVehicleLogoRecog = (short)Global.carList[i].carLogo;
                        snapData.wVehicleSubLogoRecog = (short)Global.carList[i].subCarLogo;

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

                        Global.LogServer.Add(new LogInfo("Run", "Main->ProcSnapFromDIT: 发送车辆信息到DIT  车牌号:" + Global.carList[i].license + "  油枪号：" + nozzleNo.ToString(), (int)EnumLogLevel.RUN));

                        Global.carList[i].nozzleNo = nozzleNo;
                        DateTime dt = DateTime.Now;
                        switch (nozzleStatus)
                        {
                            case 0:  //不生效 默认开始时间
                                Global.carList[i].beginTime = dt;
                                break;
                            case 1:  //提枪
                                Global.carList[i].beginTime = dt;
                                Global.carList[i].endTime = dt;
                                Global.carList[i].leaveTime = dt;
                                break;
                            case 2: //加油
                                Global.carList[i].beginTime = dt;
                                Global.carList[i].endTime = dt;
                                Global.carList[i].leaveTime = dt;
                                break;
                            case 3: //挂枪
                                Global.carList[i].endTime = dt;
                                Global.carList[i].leaveTime = dt;
                                if (Global.nMatchMode == (int)EnumMatchMode.NON_IN_OUT)
                                {
                                    Global.mysqlHelper.ExecuteSql(Global.carList[i].toSaveSqlString());
                                    Global.carList.RemoveAt(i);
                                }
                                break;
                            default:
                                Global.carList[i].beginTime = DateTime.Now;
                                break;
                        }
                        return;
                    }
                }
            }
            if (!bMatched)
            {
                snapData.byColor = 0;
                snapData.byPlateColor = 0;
                snapData.byVehicleShape = 0;
                snapData.wVehicleLogoRecog = 0;
                snapData.wVehicleSubLogoRecog = 0;

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
                Global.LogServer.Add(new LogInfo("Run", "Main->ProcSnapFromDIT: 未匹配到车牌信息，回复空信息  " + "  油枪号：" + nozzleNo.ToString(), (int)EnumLogLevel.RUN));
            }
        }
        private void ProcSnapFromDIT_Array(int nozzleNo, int nozzleStatus)
        {
            NET_DVR_PLATE_RESULT snapData = new NET_DVR_PLATE_RESULT();
            snapData.byPumpID = (byte)nozzleNo;
            snapData.byPumpStatus = (byte)nozzleStatus;
            snapData.sLicense = new byte[16];
            int areaId = GetAreaIdByNozzNo(nozzleNo);
            int index = Global.areaMap[GetAreaIdByNozzNo(nozzleNo)];

            byte[] license = System.Text.Encoding.Default.GetBytes(Global.arrayAreaCar[index].license);
            Buffer.BlockCopy(license, 0, snapData.sLicense, 0, license.Length);
            snapData.byColor = (byte)Global.arrayAreaCar[index].carColor;
            snapData.byPlateColor = (byte)Global.arrayAreaCar[index].licenseColor;
            snapData.byVehicleShape = (byte)Global.arrayAreaCar[index].type;
            snapData.wVehicleLogoRecog = (short)Global.arrayAreaCar[index].carLogo;
            snapData.wVehicleSubLogoRecog = (short)Global.arrayAreaCar[index].subCarLogo;

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

            Global.LogServer.Add(new LogInfo("Run", "Main->ProcSnapFromDIT_Array: 发送车辆信息到DIT  车牌号:" + 
                Global.arrayAreaCar[index].license + "  油枪号：" + nozzleNo.ToString(), (int)EnumLogLevel.RUN));

            Global.arrayAreaCar[index].nozzleNo = nozzleNo;
            Global.arrayAreaCar[index].matchFlag = nozzleStatus;
            DateTime dt = DateTime.Now;
            switch (nozzleStatus)
            {
                case 0:  //不生效 默认开始时间
                    Global.arrayAreaCar[index].beginTime = dt;
                    break;
                case 1:  //提枪
                    Global.arrayAreaCar[index].beginTime = dt;
                    Global.arrayAreaCar[index].endTime = dt;
                    Global.arrayAreaCar[index].leaveTime = dt;
                    break;
                case 2: //加油
                    Global.arrayAreaCar[index].beginTime = dt;
                    Global.arrayAreaCar[index].endTime = dt;
                    Global.arrayAreaCar[index].leaveTime = dt;
                    break;
                case 3: //挂枪
                    Global.arrayAreaCar[index].endTime = dt;
                    Global.arrayAreaCar[index].leaveTime = dt;
                    Global.mysqlHelper.ExecuteSql(Global.arrayAreaCar[index].toSaveSqlString());
                    //Global.arrayAreaCar[index].
                    break;
                default:
                    break;
            }
        }
        private int GetAreaIdByNozzNo(int nozzleNo)
        {
            foreach (ClsNozzle nozz in Global.nozzleList)
            {
                if (nozz.nozzleNo == nozzleNo)
                {
                    return nozz.areaid;
                }
            }
            Global.LogServer.Add(new LogInfo("Error", "Main->GetAreaIdByNozzNo fail. nozzleNo:"+nozzleNo.ToString() , (int)EnumLogLevel.ERROR));
            return 0;
        }
        private int GetOilType(int nozzleNo)
        {
            foreach (ClsNozzle nozz in Global.nozzleList)
            {
                if (nozzleNo == nozz.nozzleNo)
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
            ProcessStartInfo psi = new ProcessStartInfo();
            psi.FileName = "Kill.exe";
            psi.UseShellExecute = false;
            psi.CreateNoWindow = true;
            Process.Start(psi);

            Global.socketTool.Close();
            SPlate.SP_Close();
            
            Global.picWork.Stop();
            
            if (Global.LogServer != null)
                Global.LogServer.Stop();
            this.toExit = true;
            
            //启动强制退出线程
           
            System.Environment.Exit(0);
        }

        private void sendCallbackInfo(struCarInfoOut carOut,int InOrOut)
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

        private void addListViewHead()
        {
            listViewCache.View = View.Details;
            //ColumnHeader ch = new ColumnHeader();
            //ch.Text = "序号";
            //ch.Width = 60;
            //listViewCache.Columns.Add(ch);
            listViewCache.Columns.Add("序号", 60);
            listViewCache.Columns.Add("识别区", 60);
            listViewCache.Columns.Add("车牌", 100);
            listViewCache.Columns.Add("当前油枪", 60);
            listViewCache.Columns.Add("油枪状态", 60);

        }
    }
}
