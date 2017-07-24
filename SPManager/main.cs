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

namespace SPManager
{
     partial class FormMain
    {
        int updateCount = 0;
        [DllImport("user32.dll")]
        static extern uint RegisterWindowMessage(string lpString);
        static uint WM_CARDATA = RegisterWindowMessage("CARDATA");
        static uint WM_VIDEOCAR = RegisterWindowMessage("VIDEOCAR");
        static uint WM_AREACAR = RegisterWindowMessage("AREACAR");
        DateTime lastMessageTime = DateTime.Now;
        protected override void DefWndProc(ref Message m)
        {
            if (m.Msg == Convert.ToInt32(WM_CARDATA))
            {
                lastUpdateTime = DateTime.Now;
                Global.LogServer.Add(new LogInfo("Debug", "Main->DefWndProc: 收到动态库车辆消息", (int)EnumLogLevel.DEBUG));
                GetCarFromDll_Array();
            }
            else if (m.Msg == Convert.ToInt32(WM_AREACAR))
            {
                int areaNo = (int)m.WParam;
                string info = "Main->DefWndProc: 收到动态库视频识别车辆消息，识别区：" +
                    areaNo.ToString() + "  视频通道:" + m.LParam.ToString();
                Global.LogServer.Add(new LogInfo("Debug", info, (int)EnumLogLevel.DEBUG));
                showRTBInfo(info);

                GetAreaCarFromDll(areaNo);
            }
            else if (m.Msg == Convert.ToInt32(Global.WM_CARSNAP))
            {
                
                int nNozzleID = (int)m.WParam;
                int nNozzleStatus = (int)m.LParam;
               
                showRTBInfo("DIT信号:油枪" + nNozzleID.ToString() + " 状态" + nNozzleStatus.ToString());
                Global.LogServer.Add(new LogInfo("Run", "Main->DefWndProc: 收到DIT消息,油枪号：" + nNozzleID.ToString() + "  状态号:"+nNozzleStatus.ToString(), (int)EnumLogLevel.RUN));
                // ProcSnapFromDIT(nNozzleID, nNozzleStatus);
                //ProcSnapFromDIT_Backward(nNozzleID, nNozzleStatus);
                if (Global.nCaptureFlag == 1) //抓拍使能开启，抓拍实时数据
                {
                    ProcSnapFromDIT_Capture_V2(nNozzleID, nNozzleStatus);
                }
                else if(Global.nVideoRecogFlag == 1)
                {
                    ProcSnapFromDIT_WithoutCap(nNozzleID, nNozzleStatus);
                }
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
            if (!InitDev())
            {
                ret += 1 << 4;
                //return ret;
            }
            if (!InitAlg())
            {
                ret += 1 << 3;
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

        private bool InitDevice()
        {

            if (Global.nRunMode == 1)
            {
                return InitDev();
            } 
            else if(Global.nRunMode == 2)
            {
                return InitDev_HKCN();
            }
            else if (Global.nRunMode == 4)
            {
                return InitDev_MultiChan();
            }
            
            return false;
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
            GetVideoChanParam();
            GetNozzleParam();
            GetAreaParam();
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
                    else if (paramName == "runmode")
                        Global.nRunMode = int.Parse(paramValue);
                    else if (paramName == "captureflag")
                        Global.nCaptureFlag = int.Parse(paramValue);
                    else if (paramName == "videorecog")
                        Global.nVideoRecogFlag = int.Parse(paramValue);
                    else if (paramName == "videorecogmode")
                        Global.nVideoRocogMode = int.Parse(paramValue);
                    else if (paramName == "videosource")
                        Global.nVideoSource = int.Parse(paramValue);
                    else if (paramName == "defaultprovince")
                        Global.clsNvrInfo.loginName = paramValue;
                    else if (paramName == "socketip")
                        Global.socketIP = paramValue;
                    else if (paramName == "socketport")
                        Global.socketPort = int.Parse(paramValue);
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
        private bool GetVideoChanParam()
        {
            try
           {
                string sqlString = "select * from vch";
                DataTable dt3 = Global.mysqlHelper.GetDataTable(sqlString);
                if (dt3.Rows.Count > 0)
                {
                    foreach (DataRow dr3 in dt3.Rows)
                    {
                        ClsVideoChannel videoChan = new ClsVideoChannel();
                        videoChan.channelNo = int.Parse(dr3["vchno"].ToString());
                        videoChan.id = int.Parse(dr3["id"].ToString());
                        videoChan.ip = dr3["vchip"].ToString();
                        videoChan.loginName = dr3["loginname"].ToString();
                        videoChan.password = dr3["loginpwd"].ToString();
                        videoChan.port = int.Parse(dr3["vchport"].ToString());
                        string sql = "select * from analysisarea where vchid = " + videoChan.id.ToString();
                        DataTable dtt = Global.mysqlHelper.GetDataTable(sql);
                        if (dtt.Rows.Count > 0)
                        {
                            foreach (DataRow drr in dtt.Rows)
                            {
                                int areaNo = int.Parse(drr["id"].ToString());
                                videoChan.areaNoList.Add(areaNo);
                            }
                        }
                        Global.videoChanList.Add(videoChan);
                    }

                }

            }
                catch (System.Exception ex)
                {
                    Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetVideoChanParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                    return false;
                }
                return true;

            

           
        }

        private bool GetAreaParam()
        {
            string queryString = "select a.vchno,a.vchAttr,b.id,b.x1,b.x2,b.y1,b.y2,b.vchid from vch a right join analysisarea b on a.id = b.vchid ";
            try
            {
                int index = 0;
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);

                Global.arrayAreaCar = new ClsCarInfo[dt.Rows.Count];
                for (int i = 0; i < dt.Rows.Count; i++)
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
                    Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetAreaNozzleParam 识别区映射 " + area.id.ToString() + ":" + index.ToString(), (int)EnumLogLevel.DEBUG));
                    index++;
                    Global.areaList.Add(area);

                    StringBuilder info = new StringBuilder();
                    info.Append(" areaid：" + area.id.ToString());
                    info.Append(" left：" + area.left.ToString());
                    info.Append(" right：" + area.right.ToString());
                    info.Append(" top：" + area.top.ToString());
                    info.Append(" bottom：" + area.bottom.ToString());
                    Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetAreaParam get param:" + info.ToString(), (int)EnumLogLevel.DEBUG));
                  }
            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetAreaParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            return true;

        }
        private bool GetNozzleParam()
        {
            try
            {
                string sqlString = "select * from nozzle ";
                DataTable dt2 = Global.mysqlHelper.GetDataTable(sqlString);
                if (dt2.Rows.Count > 0)
                {
                    int index = 0;
                    Global.arrayNozzleCar = new ClsCarInfo[dt2.Rows.Count];
                    for (int i = 0; i < Global.arrayNozzleCar.Length; i++)
                    {
                        Global.arrayNozzleCar[i] = new ClsCarInfo();
                    }
                    Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetNozzleParam arrayNozzleCar lenth " + Global.arrayNozzleCar.Length.ToString(), (int)EnumLogLevel.DEBUG));
                    foreach (DataRow dr2 in dt2.Rows)
                    {
                        ClsNozzle nozzle = new ClsNozzle();
                       // nozzle.areaid = int.Parse(dr2["areaid"].ToString()); ;
                        nozzle.oilType = int.Parse(dr2["oiltype"].ToString());
                        nozzle.nozzleNo = int.Parse(dr2["nozzleno"].ToString());
                      //  nozzle.subAreaid = int.Parse(dr2["subareaid"].ToString());

                        sqlString = "select * from nozzle_area where nozzleNo = " + nozzle.nozzleNo.ToString();
                        DataTable dtna = Global.mysqlHelper.GetDataTable(sqlString);
                        if (dtna.Rows.Count > 0)
                        {
                            foreach (DataRow drna in dtna.Rows)
                            {
                                if ("1" == drna["linkmode"].ToString())  //主识别区
                                {
                                    nozzle.linkedMainAreaList.Add(int.Parse(drna["areaid"].ToString()));
                                }
                                else //副识别区
                                {
                                    nozzle.linkedSubAreaList.Add(int.Parse(drna["areaid"].ToString()));
                                }
                            }

                        }
                        Global.nozzleMap.Add(nozzle.nozzleNo, index);
                        index++;
                        Global.nozzleList.Add(nozzle);
                        StringBuilder loginfo = new StringBuilder();
                        loginfo.Append("nozzleNo：" + nozzle.nozzleNo.ToString());
                        loginfo.Append(" areaid：" + nozzle.areaid.ToString());
                        loginfo.Append(" oilType：" + nozzle.oilType.ToString());
                        loginfo.Append(" subAreaid：" + nozzle.subAreaid.ToString());
                        Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetNozzleParam get param:" + loginfo.ToString(), (int)EnumLogLevel.DEBUG));

                    }
                }

            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetNozzleParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
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
        //private bool InitDev()
        //{
        //    Global.LogServer.Add(new LogInfo("Debug","main->InitDev in", (int)EnumLogLevel.DEBUG));
            
        //    int structLenth = Marshal.SizeOf(typeof(struArea));
        //    //IntPtr ip = Marshal.AllocHGlobal(Global.nozzleList.Count* structLenth);
        //    struArea[] area = new struArea[Global.areaList.Count];
        //    byte[] ipp = new byte[10240];
        //    int offset = 0;
        //    for (int i =0;i<Global.areaList.Count;i++)
        //    {
        //        area[i].areaNo = Global.areaList[i].id;
        //        area[i].videoChanNo = Global.areaList[i].videoChannel;
        //        area[i].left = (int)(Global.areaList[i].left*Global.nDefaultHeight);
        //        area[i].right = (int)(Global.areaList[i].right*Global.nDefaultWidth);
        //        area[i].top = (int)(Global.areaList[i].top * Global.nDefaultHeight);
        //        area[i].bottom = (int)(Global.areaList[i].bottom * Global.nDefaultHeight);
        //        area[i].areaFlag = Global.areaList[i].areaFlag;
        //        byte[] bArea = SystemUnit.StrutsToBytesArray(area[i]);
        //        Buffer.BlockCopy(bArea, 0, ipp, offset,structLenth);
        //        offset += structLenth;
        //    }
        //    Global.LogServer.Add(new LogInfo("Debug", "main->InitDev->SP_InitNVR begin, param value " + Global.clsNvrInfo.ip + " "
        //        + Global.clsNvrInfo.port.ToString() + " " + Global.clsNvrInfo.loginName + " " + Global.clsNvrInfo.password, (int)EnumLogLevel.DEBUG));

        //    int ret = SPlate.SP_InitNVR(Global.clsNvrInfo.ip, Global.clsNvrInfo.port, Global.clsNvrInfo.loginName, Global.clsNvrInfo.password);
        //    Global.LogServer.Add(new LogInfo("Debug", "main->InitDev->SP_InitNVR done, return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));
            
        //    if (ret == 0)
        //    {
        //        SPlate.SP_InitRunParam(ipp, Global.areaList.Count);
        //        Global.LogServer.Add(new LogInfo("Debug", "main:InitDev SP_InitRunParam done return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));
        //        return true;
        //    }
        //    else
        //        return false;
            
        //}
        private bool InitDev()
        {
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev in", (int)EnumLogLevel.DEBUG));
            int ret = SPlate.SP_InitNVR(Global.clsNvrInfo.ip, Global.clsNvrInfo.port, Global.clsNvrInfo.loginName, Global.clsNvrInfo.password);
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev->SP_InitNVR done, return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));

            if (ret == 0)
            //if (true)
            {
                if (Global.nCaptureFlag == 1)
                {
                    SetNozzleParamToDll();
                }
                if (Global.nVideoRecogFlag == 1)
                {
                    SetVideoParamToDll();
                }
                return true;
            }
            else
                return false;

        }

        private bool InitDev_MultiChan()
        {
            int ret = SPlate.SP_InitNVR(Global.clsNvrInfo.ip, Global.clsNvrInfo.port, Global.clsNvrInfo.loginName, Global.clsNvrInfo.password);
            if (ret == 0)
            {
               // SPlate.SP_BeginRecog_MultiChan();
               // SPlate.SP_InitRunParam_V2(ipp, Global.nozzleList.Count);
                Global.LogServer.Add(new LogInfo("Debug", "main:InitDev_V2->SP_InitRunParam done return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));
                return true;
            }
            else
                return false;
        }
        private void SetNozzleParamToDll()
        {
            int structLenth = Marshal.SizeOf(typeof(struNozzleRecog));
            //IntPtr ip = Marshal.AllocHGlobal(Global.nozzleList.Count* structLenth);
            struNozzleRecog[] nozzleRecog = new struNozzleRecog[Global.nozzleList.Count];
            byte[] ipp = new byte[10000];
            int offset = 0;
            for (int i = 0; i < Global.nozzleList.Count; i++)
            {

                nozzleRecog[i].nozzleNo = Global.nozzleList[i].nozzleNo;
                nozzleRecog[i].areas = new struArea[8];
                nozzleRecog[i].areaCount = Global.nozzleList[i].linkedMainAreaList.Count;
                for (int j=0;j< nozzleRecog[i].areaCount;j++)
                {
                    foreach (ClsRecogArea area in Global.areaList)
                    {
                        if (Global.nozzleList[i].linkedMainAreaList[j] == area.id)
                        {
                            nozzleRecog[i].videoChan = area.videoChannel;
                            nozzleRecog[i].areas[j].areaNo = area.id;
                            nozzleRecog[i].areas[j].left = (int)(area.left * Global.nDefaultWidth);
                            nozzleRecog[i].areas[j].right = (int)(area.right * Global.nDefaultWidth);
                            nozzleRecog[i].areas[j].top = (int)(area.top * Global.nDefaultHeight);
                            nozzleRecog[i].areas[j].bottom = (int)(area.bottom * Global.nDefaultHeight);
                            nozzleRecog[i].areas[j].areaFlag = area.areaFlag;
                        }
                    }
                }
                
                byte[] bNozzle = SystemUnit.StrutsToBytesArray(nozzleRecog[i]);
                Buffer.BlockCopy(bNozzle, 0, ipp, offset, structLenth);
                offset += structLenth;
            }
            SPlate.SP_InitRunParam_Nozzle(ipp, Global.nozzleList.Count);
        }
        private void SetVideoParamToDll()
        {
            int structLenth = Marshal.SizeOf(typeof(struVideoChan));
            //IntPtr ip = Marshal.AllocHGlobal(Global.nozzleList.Count* structLenth);
            struVideoChan[] videoChan = new struVideoChan[Global.videoChanList.Count];
            byte[] ipp = new byte[10000];
            int offset = 0;
            for (int i = 0; i < Global.videoChanList.Count; i++)
            {
                videoChan[i].chanNo = Global.videoChanList[i].channelNo;
                videoChan[i].areaCount = Global.videoChanList[i].areaNoList.Count;
                videoChan[i].areas = new struArea[8];
                for (int j=0;j< videoChan[i].areaCount;j++)
                {
                    foreach(ClsRecogArea area in Global.areaList)
                    {
                        if (area.id == Global.videoChanList[i].areaNoList[j])
                        {
                            videoChan[i].areas[j].areaNo = area.id;
                            videoChan[i].areas[j].left = (int)(area.left*Global.nDefaultWidth);
                            videoChan[i].areas[j].right = (int)(area.right * Global.nDefaultWidth);
                            videoChan[i].areas[j].top = (int)(area.top * Global.nDefaultHeight);
                            videoChan[i].areas[j].bottom = (int)(area.bottom * Global.nDefaultHeight);
                            videoChan[i].areas[j].videoChanNo = videoChan[i].chanNo;
                            break;
                        }
                    }
                }
                byte[] byVideo = SystemUnit.StrutsToBytesArray(videoChan[i]);
                Buffer.BlockCopy(byVideo, 0, ipp, offset, structLenth);
                offset += structLenth;
            }
            SPlate.SP_InitRunParam_Video(ipp, Global.videoChanList.Count);

        }
        private bool InitDev_HKCN()
        {
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev_HKCN in", (int)EnumLogLevel.DEBUG));

            int structLenth = Marshal.SizeOf(typeof(struArea));
            //IntPtr ip = Marshal.AllocHGlobal(Global.nozzleList.Count* structLenth);
            struArea[] area = new struArea[Global.areaList.Count];
            byte[] ipp = new byte[10240];
            int offset = 0;
            for (int i = 0; i < Global.areaList.Count; i++)
            {
                area[i].areaNo = Global.areaList[i].id;
                area[i].videoChanNo = Global.areaList[i].videoChannel;
                area[i].left = (int)(Global.areaList[i].left * Global.nDefaultHeight);
                area[i].right = (int)(Global.areaList[i].right * Global.nDefaultWidth);
                area[i].top = (int)(Global.areaList[i].top * Global.nDefaultHeight);
                area[i].bottom = (int)(Global.areaList[i].bottom * Global.nDefaultHeight);
                area[i].areaFlag = Global.areaList[i].areaFlag;
                byte[] bArea = SystemUnit.StrutsToBytesArray(area[i]);
                Buffer.BlockCopy(bArea, 0, ipp, offset, structLenth);
                offset += structLenth;
            }
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev_HKCN->SP_InitNVR_HKCN begin, param value " + Global.clsNvrInfo.ip + " "
                + Global.clsNvrInfo.port.ToString() + " " + Global.clsNvrInfo.loginName + " " + Global.clsNvrInfo.password, (int)EnumLogLevel.DEBUG));

            int ret = SPlate.SP_InitNVR_HKCN(Global.clsNvrInfo.ip, Global.clsNvrInfo.port, Global.clsNvrInfo.loginName, Global.clsNvrInfo.password);
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev_HKCN done return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));
            if (ret == 0)
            {
                SPlate.SP_InitRunParam(ipp, Global.areaList.Count);
                return true;
            }
            else
                return false;
        }
        private bool InitAlg()
        {
            //if (Global.nCaptureFlag != 1)
            //{
            //    return true;
            //}
            TH_PlateIDCfg th_PlateIDCfg = new TH_PlateIDCfg();
            th_PlateIDCfg.nMaxPlateWidth = 400;
            th_PlateIDCfg.nMinPlateWidth = 60;

            th_PlateIDCfg.nMaxImageWidth = 2000;
            th_PlateIDCfg.nMaxImageHeight = 1100;

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
            th_PlateIDCfg.bOutputSingleFrame = 1;  
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
                                }
                            }
                            nozzle.bMatched = false;
                            nozzle.nozzleCar.license = "";
                            nozzle.curStatus = 0;

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
                            int areaIndex = Global.areaMap[areaNo];
                            if (Global.arrayAreaCar[areaIndex].matchFlag == 0 && Global.arrayAreaCar[areaIndex].license != "" 
                            && LicenseIsMatched(Global.arrayAreaCar[areaIndex].license, nozzleNo) == 0 )
                            {
                                Global.LogServer.Add(new LogInfo("Debug", "Main->FindCarInAreaCarList: 匹配到车辆，车牌："+ 
                                    Global.arrayAreaCar[areaIndex].license + " 识别区："+areaIndex.ToString(), (int)EnumLogLevel.DEBUG));
                                nozzle.bMatched = true;
                                Global.arrayAreaCar[areaIndex].matchFlag = 1;
                                Global.arrayAreaCar[areaIndex].nozzleNo = nozzleNo;

                                ClsCarInfo Car = new ClsCarInfo();
                                Car.license = Global.arrayAreaCar[areaIndex].license;
                                Car.arriveTime = Global.arrayAreaCar[areaIndex].arriveTime;
                                return Car;
                                //bMatched = true;
                                //break;
                            }
                        }
                       
                            Global.LogServer.Add(new LogInfo("Debug", "Main->FindCarInAreaCarList: 主识别区未查找车辆，进入副识别区查找车辆", (int)EnumLogLevel.DEBUG));
                            foreach (int areaNo in nozzle.linkedSubAreaList)
                            {
                                int areaIndex = Global.areaMap[areaNo];
                                if (Global.arrayAreaCar[areaIndex].matchFlag == 0 && Global.arrayAreaCar[areaIndex].license != ""
                            && LicenseIsMatched(Global.arrayAreaCar[areaIndex].license, nozzleNo) == 0)
                                {
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
            
            Global.LogServer.Add(new LogInfo("Debug", "Main->FindCarInAreaCarList: 匹配结束，未匹配到任何车辆", (int)EnumLogLevel.DEBUG));
            return null;
        }
        private void GetNvrConfig()
        {
            IntPtr ip = Marshal.AllocHGlobal(Marshal.SizeOf(Global.net_dvr_cfg));
            int lenth = 0;
            SPlate.SP_GetNvrCfg(ip, ref lenth);
            Global.net_dvr_cfg = (NET_DVR_IPPARACFG_V40)Marshal.PtrToStructure(ip, typeof(NET_DVR_IPPARACFG_V40));
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
                int index = 0;
                try
                {
                    index = Global.areaMap[struCarOut.nAreaNo];
                }
                catch (Exception ex)
                {
                    Global.LogServer.Add(new LogInfo("Error", "Main->GetCarFromDll_Array 获取识别区下脚标失败，识别区号:" +struCarOut.nAreaNo.ToString() +"  "+ ex.Message, (int)EnumLogLevel.ERROR));
                    return;
                }
               
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
                    Global.arrayAreaCar[index].nozzleNo = 0;
                }
                ClsPicture pic = new ClsPicture();
                pic.picBufer = new byte[struCarOut.nPicLenth];
                //Buffer.BlockCopy(struCarOut.pic, 0, pic.picBufer, 0, struCarOut.nPicLenth);
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

        private void GetAreaCarFromDll(int areaNo)
        {
            struCarInfoOut struCarOut = new struCarInfoOut();
            IntPtr pCarOut = Marshal.AllocHGlobal(Marshal.SizeOf(struCarOut));
            SPlate.SP_GetAreaCarInfo(pCarOut, areaNo);
            struCarOut = (struCarInfoOut)Marshal.PtrToStructure(pCarOut, typeof(struCarInfoOut));
            Marshal.FreeHGlobal(pCarOut);
            int index = Global.areaMap[areaNo];
            
            string lic = Encoding.Default.GetString(struCarOut.license,0,getStrLength(struCarOut.license));
           
            showRTBInfo("视频流车牌获取区域:" + areaNo.ToString()+"  获取车牌：" + lic);
            for (int i=0;i<Global.arrayAreaCar.Length;i++)
            {   
                if (Global.arrayAreaCar[i].license == lic && lic.Length > 5)
                {
                    Global.arrayAreaCar[i].license = "";
                    Global.arrayAreaCar[i].matchFlag = 0;
                }
            }
            //if (checkRepeatLicense(struCarOut.nAreaNo, license))
            //{
            //    return;
            //}
            if (checkDBcarRepeat(lic))
            {
                showRTBInfo("车牌"+ lic + "10分钟内已加油,视为无效车辆，不匹配识别区" );
                return;
            }
            Global.arrayAreaCar[index].license = lic;
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
            //Global.arrayAreaCar[index].matchFlag = 0;
            //Global.arrayAreaCar[index].nozzleNo = 0;
            Global.LogServer.Add(new LogInfo("Debug", "Main->GetAreaCarFromDll: 获取区域:"+areaNo.ToString() + "车牌："+ Global.arrayAreaCar[index].license, (int)EnumLogLevel.DEBUG));

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

        private bool checkDBcarRepeat(string license)
        {
            DateTime leave = DateTime.Now;
            string sql = "select count(*) as count from carlog where carnumber like '%"+license.Substring(1)+"%' and leavetime > '" + 
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
        private void showCarList()
        {
            listViewCache.Items.Clear();
            listViewCache.BeginUpdate();
            //Global.LogServer.Add(new LogInfo("Debug", "main->showCarList Length:" + Global.arrayNozzleCar.Length.ToString(), (int)EnumLogLevel.DEBUG));
            for (int i = 0; i < Global.nozzleList.Count; i++)
            {
                //Global.LogServer.Add(new LogInfo("Debug", "main->showCarList arrayNozzleCar:" + i.ToString(), (int)EnumLogLevel.DEBUG));
                ListViewItem lvi = new ListViewItem();
                lvi.Text = Global.nozzleList[i].nozzleNo.ToString();
                lvi.SubItems.Add(Global.nozzleList[i].nozzleCar.license);
                lvi.SubItems.Add(Global.nozzleList[i].curStatus.ToString());
                listViewCache.Items.Add(lvi);
            }
            listViewCache.EndUpdate();

            listViewArea.Items.Clear();
            listViewArea.BeginUpdate();
            //Global.LogServer.Add(new LogInfo("Debug", "main->showCarList Length:" + Global.arrayNozzleCar.Length.ToString(), (int)EnumLogLevel.DEBUG));
            for (int i = 0; i < Global.arrayAreaCar.Length; i++)
            {
                //Global.LogServer.Add(new LogInfo("Debug", "main->showCarList arrayNozzleCar:" + i.ToString(), (int)EnumLogLevel.DEBUG));
                ListViewItem lvi = new ListViewItem();
                lvi.Text = Global.arrayAreaCar[i].areaNo.ToString();
                lvi.SubItems.Add(Global.arrayAreaCar[i].license);
                lvi.SubItems.Add(Global.arrayAreaCar[i].nozzleNo.ToString());
                lvi.SubItems.Add(Global.arrayAreaCar[i].matchFlag.ToString());
                listViewArea.Items.Add(lvi);
            }
            listViewArea.EndUpdate();


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
         //   Buffer.BlockCopy(carOut.pic, 0, pic.picBufer, 0, carOut.nPicLenth);
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
           // Buffer.BlockCopy(carOut.pic, 0, pic.picBufer, 0, carOut.nPicLenth);
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
                      //  Buffer.BlockCopy(carOut.pic, 0, pic.picBufer, 0, carOut.nPicLenth);
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
                   // Buffer.BlockCopy(carOut.pic, 0, pic.picBufer, 0, carOut.nPicLenth);
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
           // Buffer.BlockCopy(carOut.pic, 0, pic2.picBufer, 0, carOut.nPicLenth);
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
        private void ProcSnapFromDIT_Capture(int nozzleNo, int nozzleStatus)
        {
            struCarInfoOut carOut = new struCarInfoOut();
            NET_DVR_PLATE_RESULT snapData = new NET_DVR_PLATE_RESULT();
            snapData.byPumpID = (byte)nozzleNo;
            snapData.byPumpStatus = (byte)nozzleStatus;
            snapData.sLicense = new byte[16];
            int areaId = GetAreaIdByNozzNo(nozzleNo);
            int index = Global.areaMap[GetAreaIdByNozzNo(nozzleNo)];

            struCarInfoOut struCarOut = new struCarInfoOut();
            IntPtr pCarOut = Marshal.AllocHGlobal(Marshal.SizeOf(struCarOut));
            Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture: 开始抓拍，识别区："+areaId.ToString(), (int)EnumLogLevel.DEBUG));
            SPlate.SP_Capture(areaId, pCarOut);
            //if (lenth != Marshal.SizeOf(struCarOut))
            //{
            //    Global.LogServer.Add(new LogInfo("Error", "Main->GetCarFromDll_Array: 动态库输出结构体与上位机定义结构图长度不一致", (int)EnumLogLevel.ERROR));
            //    return;
            //}
            struCarOut = (struCarInfoOut)Marshal.PtrToStructure(pCarOut, typeof(struCarInfoOut));
            Marshal.FreeHGlobal(pCarOut);
            string tempLicense = System.Text.Encoding.Default.GetString(struCarOut.license);
            Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture: 抓拍车牌："+ tempLicense +
                "  置信度:"+struCarOut.nConfidence.ToString(), (int)EnumLogLevel.DEBUG));

            
            if (struCarOut.nConfidence > 75 || nozzleStatus == 1)
            {
                Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture: 抓拍车牌：" + tempLicense +
               "  置信度:" + struCarOut.nConfidence.ToString(), (int)EnumLogLevel.DEBUG));
                Global.arrayAreaCar[index].license = tempLicense;
                Global.arrayAreaCar[index].licenseColor = struCarOut.nColor;
                Global.arrayAreaCar[index].carLogo = struCarOut.nCarLogo;
                Global.arrayAreaCar[index].subCarLogo = struCarOut.nSubCarLogo;
                Global.arrayAreaCar[index].carColor = struCarOut.nCarColor;
            }
            Global.arrayAreaCar[index].nozzleNo = nozzleNo;
            Global.arrayAreaCar[index].matchFlag = nozzleStatus;
            byte[] license = System.Text.Encoding.Default.GetBytes(Global.arrayAreaCar[index].license);
            Buffer.BlockCopy(license, 0, snapData.sLicense, 0, license.Length);
            snapData.byColor = (byte)Global.arrayAreaCar[index].carColor;
            snapData.byPlateColor = (byte)Global.arrayAreaCar[index].licenseColor;
            snapData.byVehicleShape = (byte)Global.arrayAreaCar[index].carLogo;
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


            
            Global.LogServer.Add(new LogInfo("Run", "Main->ProcSnapFromDIT_Capture: 发送车辆信息到DIT  车牌号:" +
                Global.arrayAreaCar[index].license + "  油枪号：" + nozzleNo.ToString(), (int)EnumLogLevel.RUN));

            
            DateTime dt = DateTime.Now;
            switch (nozzleStatus)
            {
                case 0:  //不生效 默认开始时间
                    Global.arrayAreaCar[index].beginTime = dt;
                    break;
                case 1:  //提枪
                    Global.arrayAreaCar[index].arriveTime = dt;
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

        private void ProcSnapFromDIT_Capture_V2(int nozzleNo,int nozzleStatus)
        {
            NET_DVR_PLATE_RESULT snapData = new NET_DVR_PLATE_RESULT();
            snapData.byPumpID = (byte)nozzleNo;
            snapData.byPumpStatus = (byte)nozzleStatus;
            snapData.sLicense = new byte[16];
            int index = -1;
            for (int i=0;i<Global.nozzleList.Count;i++)
            {
                if (Global.nozzleList[i].nozzleNo == nozzleNo)
                {
                    index = i;
                    break;
                }
            }

            if (index < 0)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->ProcSnapFromDIT_Capture_V2: 未找到对应油枪信息，油枪号：" + nozzleNo.ToString(), (int)EnumLogLevel.ERROR));
                return;
            }

            if (nozzleStatus ==1 || Global.nozzleList[index].nozzleCar.matchFlag == 0)
            {
                IntPtr pCarOut = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(struCarInfoOut_V2)));
                Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture_V2: 开始抓拍，油枪号：" + nozzleNo.ToString(), (int)EnumLogLevel.DEBUG));
                showRTBInfo("Main->ProcSnapFromDIT_Capture_V2: 开始抓拍，油枪号：" + nozzleNo.ToString());
                SPlate.SP_Capture_V2(nozzleNo, pCarOut);
                struCarInfoOut_V2 struCarOut;
                struCarOut = (struCarInfoOut_V2)Marshal.PtrToStructure(pCarOut, typeof(struCarInfoOut_V2));
                Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture_V2: 识别车牌数量：" + struCarOut.nLicenseCount.ToString(), (int)EnumLogLevel.DEBUG));
                showRTBInfo("Main->ProcSnapFromDIT_Capture_V2: 识别车牌数量：" + struCarOut.nLicenseCount.ToString());
                Marshal.FreeHGlobal(pCarOut);

                ClsCarInfo car = MatchCar(struCarOut, nozzleNo);
                if (car != null) //抓拍未匹配到车辆
                {
                    showRTBInfo("匹配抓拍车牌:" + car.license);
                    Global.nozzleList[index].nozzleCar = car;
                    Global.nozzleList[index].nozzleCar.matchFlag = nozzleStatus;
                }
                else if (Global.nVideoRecogFlag == 1) //如开启了视频识别，从视频识别结果中查找车牌
                {
                    car = FindCarInAreaCarList(nozzleNo);
                    if (car != null)
                    {
                        showRTBInfo("抓拍匹配失败，从视频流车牌中匹配车牌:" + car.license);
                        Global.nozzleList[index].nozzleCar = car;
                        Global.nozzleList[index].nozzleCar.matchFlag = nozzleStatus;
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
                pic.picName = DateTime.Now.ToString("HHmmss") + ".jpg";
                pic.picWidth = struCarOut.nPicWidth;
                pic.picHeight = struCarOut.nPicHeight;
                pic.picType = struCarOut.nPicType;
                Global.picWork.Add(pic);
                Global.LogServer.Add(new LogInfo("Debug", "Main->GetCarFromDll: 车辆图片入队列,图片路径：" + pic.picPath + pic.picName, (int)EnumLogLevel.DEBUG));
            }
            //int index = Global.nozzleMap[nozzleNo];
            
            
            Regex.Replace(Global.nozzleList[index].nozzleCar.license, " ", "");
            Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture_V2: 匹配车牌：" + Global.arrayNozzleCar[index].license, (int)EnumLogLevel.DEBUG));
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
                    if(Global.nMatchMode == 1 && Global.nozzleList[index].nozzleCar.license != "")
                        sendCallbackInfo(Global.nozzleList[index].nozzleCar, 1);
                    break;
                case 2: //加油
                    Global.nozzleList[index].nozzleCar.beginTime = dt;
                    Global.nozzleList[index].nozzleCar.endTime = dt;
                    Global.nozzleList[index].nozzleCar.leaveTime = dt;
                    break;
                case 3: //挂枪

                    Global.nozzleList[index].nozzleCar.endTime = dt;
                    Global.nozzleList[index].nozzleCar.leaveTime = dt;
                    Global.nozzleList[index].nozzleCar.picPath = Global.basePicPath + dt.ToString("yyyyMMdd") + @"\\" + Global.arrayNozzleCar[index].license.Trim() + @"\\";
                    Global.mysqlHelper.ExecuteSql(Global.nozzleList[index].nozzleCar.toSaveSqlString());
                    if (Global.nMatchMode == 1 && Global.nozzleList[index].nozzleCar.license != "")
                        sendCallbackInfo(Global.nozzleList[index].nozzleCar, 2);
                    //Global.arrayAreaCar[index].
                    Global.nozzleList[index].nozzleCar.license = "";
                    Global.nozzleList[index].nozzleCar.matchFlag = 0;
                    break;
                default:
                    break;
            }
           
        }

        private ClsCarInfo MatchCar(struCarInfoOut_V2 struCarInfo,int nozzleNo)
        {
            ClsCarInfo car = new ClsCarInfo();
            int index = 0;
            int nCurConfidence = 0;
            for (int i=0;i<struCarInfo.nLicenseCount;i++)
            {
               
                string license = Encoding.Default.GetString(struCarInfo.license[i].license,0,getStrLength(struCarInfo.license[i].license));
                Global.LogServer.Add(new LogInfo("Debug", "Main->ProcSnapFromDIT_Capture_V2: 车牌号：" + 
                    license+" 置信度："+ struCarInfo.license[i].nConfidence.ToString() + " 识别区："+ 
                    struCarInfo.license[i].nAreaNo.ToString(), (int)EnumLogLevel.DEBUG));
                if (LicenseIsMatched(license,nozzleNo) > 0)
                    continue;
                if (checkDBcarRepeat(license))
                    continue;
                if (struCarInfo.license[i].nConfidence > nCurConfidence)
                {
                    index = i;
                    nCurConfidence = struCarInfo.license[i].nConfidence;
                }
                
            }

            if (nCurConfidence > 75)
            {
                car.license = Encoding.Default.GetString(struCarInfo.license[index].license, 0, getStrLength(struCarInfo.license[index].license));
                // car.license = System.Text.Encoding.Default.GetString(struCarInfo.license[index].license,0,);
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

        private void showMatchRatio()
        {
            string sqlString = "select count(*) as total from carlog where leavetime > '" + DateTime.Now.ToString("yyyy-MM-dd ") + "00:00:00'";
            DataTable dt = Global.mysqlHelper.GetDataTable(sqlString);
            int total = int.Parse(dt.Rows[0]["total"].ToString());
            sqlString = "select count(*) as matchcount from carlog where LENGTH(carnumber) > 5 and leavetime > '" + DateTime.Now.ToString("yyyy-MM-dd ") + "00:00:00'";
            DataTable dtt = Global.mysqlHelper.GetDataTable(sqlString);
            int match = int.Parse(dtt.Rows[0]["matchcount"].ToString());
            int ratio = 0;
            if (total > 0)
            {
                ratio = (match * 100) / total;
            }
            toolMatchPoint.Text = "当天车辆总数：" + total.ToString() + " 匹配数：" + match.ToString() + " 匹配率:" + ratio.ToString()+"%";

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
        private void sendCallbackInfo(ClsCarInfo carOut, int InOrOut)
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

        private void addListViewHead()
        {
            listViewCache.View = View.Details;
            listViewCache.Columns.Add("油枪号", 60);
            //listViewCache.Columns.Add("识别区", 60);
            listViewCache.Columns.Add("车牌", 100);
           // listViewCache.Columns.Add("当前油枪", 60);
            listViewCache.Columns.Add("油枪状态", 60);

            listViewArea.View = View.Details;
            listViewArea.Columns.Add("识别区号", 60);
            //listViewCache.Columns.Add("识别区", 60);
            listViewArea.Columns.Add("车牌", 100);
            listViewArea.Columns.Add("匹配油枪", 60);
            // listViewCache.Columns.Add("当前油枪", 60);
            listViewArea.Columns.Add("匹配状态", 60);

        }

        private void showRTBInfo(string infoString)
        {
            if (richTextBoxDIT.Lines.Length > 500)
            {
                richTextBoxDIT.Clear();
            }
            richTextBoxDIT.AppendText(infoString + "\n");
            //让文本框获取焦点
            this.richTextBoxDIT.Focus();
            //设置光标的位置到文本尾
            this.richTextBoxDIT.Select(this.richTextBoxDIT.TextLength, 0);
            //滚动到控件光标处
            this.richTextBoxDIT.ScrollToCaret();
        }
        private int getStrLength(byte[] src)
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
    }
}
