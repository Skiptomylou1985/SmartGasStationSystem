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

namespace SPManager
{
    partial class FormMain
    {
        private bool InitLogServer()
        {

            try
            {
                Global.LogServer = new Log(Global.nLogLevel);
                Global.LogServer.Run();
            }
            catch (Exception ex)
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
            GetCarLogoParam();
            GetVideoHostParam();
            GetVideoChanParam();
            GetNozzleParam();
            GetAreaParam();
            GetEntryAndExit();
            GetSatationBoardParamFromDB();
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
                    if (paramName == "defaultwidth")
                        Global.nDefaultWidth = int.Parse(paramValue);
                    if (paramName == "defaultheight")
                        Global.nDefaultHeight = int.Parse(paramValue);
                    else if (paramName == "stationname")
                        Global.stationInfo.stationName = paramValue;
                    else if (paramName == "stationcode")
                        Global.stationInfo.stationCode = paramValue;
                    else if (paramName == "stationip")
                        Global.stationInfo.stationIP = paramValue;
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
                    else if (paramName == "videorecogtype")
                        Global.nVideoRecogType = int.Parse(paramValue);
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
                    else if (paramName == "showstationboard")
                        Global.bShowStationBoard = bool.Parse(paramValue);
                    else if (paramName == "stationboarddirection")
                        Global.nStationBoardDirection = int.Parse(paramValue);
                    else if (paramName == "runpwd")
                        Global.password = paramValue;

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

        private bool GetCarLogoParam()
        {
            string sql = "select * from carbrand";
            DataTable dt = Global.mysqlHelper.GetDataTable(sql);

            if (dt == null || dt.Rows.Count == 0)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetCarLogoParam table carbrand is null", (int)EnumLogLevel.ERROR));
                return false;
            }

            foreach (DataRow dr in dt.Rows)
            {
                string key = dr["carcode"].ToString() + "-" + dr["subcarcode"].ToString();
                string value = dr["subcarlogo"].ToString();
                Global.carLogoHashtable.Add(key, value);
            }
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

                if (dt3 == null || dt3.Rows.Count < 1)
                {
                    Global.LogServer.Add(new LogInfo("Error", "Main->GetVideoChanParam 从数据库表【vch】获取视频通道为空", (int)EnumLogLevel.ERROR));
                    return false;
                }
                foreach (DataRow dr3 in dt3.Rows)
                {
                    ClsVideoChannel videoChan = new ClsVideoChannel();
                    videoChan.channelNo = int.Parse(dr3["vchno"].ToString());
                    videoChan.id = int.Parse(dr3["id"].ToString());
                    videoChan.ip = dr3["vchip"].ToString();
                    videoChan.loginName = dr3["loginname"].ToString();
                    videoChan.password = dr3["loginpwd"].ToString();
                    videoChan.port = int.Parse(dr3["vchport"].ToString());
                    videoChan.videoType = int.Parse(dr3["vchAttr"].ToString());
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
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetVideoChanParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            return true;




        }

        private bool GetAreaParam()
        {
            string queryString = "select a.vchno,a.vchAttr,b.id,b.x1,b.x2,b.y1,b.y2,b.vchid,b.vchlane from vch a right join analysisarea b on a.id = b.vchid ";
            try
            {
                Global.areaList.Clear();
                Global.areaMap.Clear();
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                if (dt == null || dt.Rows.Count < 1)
                {
                    Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetAreaParam 从数据库获取识别区为空", (int)EnumLogLevel.ERROR));
                    return false;
                }


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
                    area.videoLaneNo = int.Parse(dr["vchlane"].ToString());
                    Global.areaList.Add(area);
                    int index = Global.areaList.IndexOf(area);
                    Global.areaMap.Add(area.id, index);
                    Global.arrayAreaCar[index].areaNo = area.id;
                    Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetAreaNozzleParam 识别区映射 " + area.id.ToString() + ":" + index.ToString(), (int)EnumLogLevel.DEBUG));
                    
                    StringBuilder info = new StringBuilder();
                    info.Append(" areaid：" + area.id.ToString());
                    info.Append(" left：" + area.left.ToString());
                    info.Append(" right：" + area.right.ToString());
                    info.Append(" top：" + area.top.ToString());
                    info.Append(" bottom：" + area.bottom.ToString());
                    info.Append(" vchlane: " + area.videoLaneNo.ToString());
                    Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetAreaParam 识别区参数:" + info.ToString(), (int)EnumLogLevel.DEBUG));
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

                if (dt2 == null || dt2.Rows.Count < 1)
                {
                    Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetNozzleParam 从数据库表【nozzle】获取油枪为空", (int)EnumLogLevel.ERROR));
                    return false;
                }
                int index = 0;
                Global.arrayNozzleCar = new ClsCarInfo[dt2.Rows.Count];
                for (int i = 0; i < Global.arrayNozzleCar.Length; i++)
                {
                    Global.arrayNozzleCar[i] = new ClsCarInfo();
                }
                Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetNozzleParam 获取油枪数： " + Global.arrayNozzleCar.Length.ToString(), (int)EnumLogLevel.DEBUG));
                foreach (DataRow dr2 in dt2.Rows)
                {
                    ClsNozzle nozzle = new ClsNozzle();
                    nozzle.oilType = int.Parse(dr2["oiltype"].ToString());
                    nozzle.nozzleNo = int.Parse(dr2["nozzleno"].ToString());
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
                    
                    Global.nozzleList.Add(nozzle);
                    Global.nozzleMap.Add(nozzle.nozzleNo, Global.nozzleList.IndexOf(nozzle));
                    StringBuilder loginfo = new StringBuilder();
                    loginfo.Append("nozzleNo：" + nozzle.nozzleNo.ToString());
                    loginfo.Append(" areaid：" + nozzle.areaid.ToString());
                    loginfo.Append(" oilType：" + nozzle.oilType.ToString());
                    loginfo.Append(" subAreaid：" + nozzle.subAreaid.ToString());
                    Global.LogServer.Add(new LogInfo("Debug", "Main->InitParam->GetNozzleParam get param:" + loginfo.ToString(), (int)EnumLogLevel.DEBUG));

                }


            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetNozzleParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            return true;

        }

        //油枪号为98代表入口，99代表出口
        private void GetEntryAndExit()
        {
            if (Global.ditCallBackMode == 1)
            {
                Global.listCarArrive = new List<ClsCarArrive>();
                timerClearCarlist.Enabled = true;
            } 
            else
            {
                DataTable dt = Global.mysqlHelper.GetDataTable("select * from nozzle_area where nozzleNo in (98,99)");
                if (dt != null && dt.Rows.Count > 0)
                {
                    for (int i = 0; i < dt.Rows.Count; i++)
                    {
                        if ("98" == dt.Rows[i]["nozzleNo"].ToString())
                        {
                            Global.entryAreaID = int.Parse(dt.Rows[i]["areaid"].ToString());
                        }
                        else if ("99" == dt.Rows[i]["nozzleNo"].ToString())
                        {
                            Global.exitAreaID = int.Parse(dt.Rows[i]["areaid"].ToString());
                        }
                    }
                }
            }


            
        }


        private bool InitSocket()
        {
            Global.socketTool = new SocketTool(Global.socketIP, Global.socketPort);
            Global.clsServiceStatus.bSocketIsRun = Global.socketTool.Run();
            Global.LogServer.Add(new LogInfo("Debug", "Main->InitSocket 初始化网络服务完成，网络服务状态 "+Global.clsServiceStatus.bSocketIsRun.ToString(), (int)EnumLogLevel.DEBUG));
            return Global.clsServiceStatus.bSocketIsRun;
        }

        private bool InitDev()
        {
            if (Global.dllEncoder == "utf8")
            {
                SPlate.SP_SetCodeType(1);
            }
            else
            {
                SPlate.SP_SetCodeType(2);
            }
            int ret = SPlate.SP_InitNVR(Global.clsNvrInfo.ip, Global.clsNvrInfo.port, Global.clsNvrInfo.loginName, Global.clsNvrInfo.password);
            Global.LogServer.Add(new LogInfo("Debug", "Main->InitDev->SP_InitNVR 初始化设备完成,返回值：" + ret.ToString(), (int)EnumLogLevel.DEBUG));

            if (ret == 0)
            {
                if (Global.nCaptureFlag == 1)
                {
                    SetNozzleParamToDll();
                }
                if (Global.nVideoRecogFlag == 1)
                {
                    SetVideoChanParamToDll();
                }
                return true;
            }
            else
                return false;

        }

        private void SetNozzleParamToDll()
        {
            int structLenth = Marshal.SizeOf(typeof(struNozzleRecog));
            struNozzleRecog[] nozzleRecog = new struNozzleRecog[Global.nozzleList.Count];
            byte[] ipp = new byte[10000];
            int offset = 0;
            for (int i = 0; i < Global.nozzleList.Count; i++)
            {

                nozzleRecog[i].nozzleNo = Global.nozzleList[i].nozzleNo;
                nozzleRecog[i].areas = new struArea[8];
                nozzleRecog[i].areaCount = Global.nozzleList[i].linkedMainAreaList.Count;
                for (int j = 0; j < nozzleRecog[i].areaCount; j++)
                {
                    if (Global.areaMap.ContainsKey(Global.nozzleList[i].linkedMainAreaList[j]))
                    {
                        int index = Global.areaMap[Global.nozzleList[i].linkedMainAreaList[j]];
                        nozzleRecog[i].videoChan = Global.areaList[index].videoChannel;
                        nozzleRecog[i].areas[j].areaNo = Global.areaList[index].id;
                        nozzleRecog[i].areas[j].left = (int)(Global.areaList[index].left * Global.nDefaultWidth);
                        nozzleRecog[i].areas[j].right = (int)(Global.areaList[index].right * Global.nDefaultWidth);
                        nozzleRecog[i].areas[j].top = (int)(Global.areaList[index].top * Global.nDefaultHeight);
                        nozzleRecog[i].areas[j].bottom = (int)(Global.areaList[index].bottom * Global.nDefaultHeight);
                        nozzleRecog[i].areas[j].videoLaneNo = Global.areaList[index].videoLaneNo;
                    }
//                     foreach (ClsRecogArea area in Global.areaList)
//                     {
//                         if (Global.nozzleList[i].linkedMainAreaList[j] == area.id)
//                         {
//                             nozzleRecog[i].videoChan = area.videoChannel;
//                             nozzleRecog[i].areas[j].areaNo = area.id;
//                             nozzleRecog[i].areas[j].left = (int)(area.left * Global.nDefaultWidth);
//                             nozzleRecog[i].areas[j].right = (int)(area.right * Global.nDefaultWidth);
//                             nozzleRecog[i].areas[j].top = (int)(area.top * Global.nDefaultHeight);
//                             nozzleRecog[i].areas[j].bottom = (int)(area.bottom * Global.nDefaultHeight);
//                             nozzleRecog[i].areas[j].videoLaneNo = area.videoLaneNo;
//                         }
//                     }
                }

                byte[] bNozzle = SystemUnit.StrutsToBytesArray(nozzleRecog[i]);
                Buffer.BlockCopy(bNozzle, 0, ipp, offset, structLenth);
                offset += structLenth;
            }
            SPlate.SP_InitRunParam_Nozzle(ipp, Global.nozzleList.Count);
            Global.LogServer.Add(new LogInfo("Debug", "Main->InitDev->SetNozzleParamToDll 油枪参数传入动态库完成，油枪数：" + Global.nozzleList.Count.ToString(), (int)EnumLogLevel.DEBUG));

        }
        private void SetVideoChanParamToDll()
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
                videoChan[i].videoType = Global.videoChanList[i].videoType;
                videoChan[i].areas = new struArea[8];
                for (int j = 0; j < videoChan[i].areaCount; j++)
                {

                    if (Global.areaMap.ContainsKey(Global.videoChanList[i].areaNoList[j]))
                    {
                        int index = Global.areaMap[Global.videoChanList[i].areaNoList[j]];
                        videoChan[i].areas[j].areaNo = Global.areaList[index].id;
                        videoChan[i].areas[j].left = (int)(Global.areaList[index].left * Global.nDefaultWidth);
                        videoChan[i].areas[j].right = (int)(Global.areaList[index].right * Global.nDefaultWidth);
                        videoChan[i].areas[j].top = (int)(Global.areaList[index].top * Global.nDefaultHeight);
                        videoChan[i].areas[j].bottom = (int)(Global.areaList[index].bottom * Global.nDefaultHeight);
                        videoChan[i].areas[j].videoChanNo = videoChan[i].chanNo;
                        videoChan[i].areas[j].videoLaneNo = Global.areaList[index].videoLaneNo;
                    }

                }
                byte[] byVideo = SystemUnit.StrutsToBytesArray(videoChan[i]);
                Buffer.BlockCopy(byVideo, 0, ipp, offset, structLenth);
                offset += structLenth;
            }
            SPlate.SP_InitRunParam_Video(ipp, Global.videoChanList.Count);
            Global.LogServer.Add(new LogInfo("Debug", "Main->InitDev->SetVideoParamToDll 视频通道参数传入动态库完成，油枪数：" + Global.videoChanList.Count.ToString(), (int)EnumLogLevel.DEBUG));

        }

        private bool InitAlg()
        {
            Global.LogServer.Add(new LogInfo("Debug", "main->SP_InitAlg 识别算法初始化开始", (int)EnumLogLevel.DEBUG));
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

            
            int lenth = Marshal.SizeOf(th_PlateIDCfg);
            int ret = SPlate.SP_InitAlg(ref th_PlateIDCfg, lenth);
            Global.LogServer.Add(new LogInfo("Debug", "main->SP_InitAlg 识别算法初始化完成,返回值：" + ret.ToString(), (int)EnumLogLevel.DEBUG));
            if (ret == 0)
                return true;
            else
                return false;
        }

    }
}
