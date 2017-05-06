using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;

namespace SPManager
{
     partial class FormMain
    {
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
                //info.type = INIUnit.GetINIValue(Global.iniPath, "General", "loglevel");
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
                        Global.nvrInfo.ip = paramValue;
                    else if (paramName == "nvrport")
                        Global.nvrInfo.port = int.Parse(paramValue);
                    else if (paramName == "nvradmin")
                        Global.nvrInfo.loginName = paramValue;
                    else if (paramName == "nvrpassword")
                        Global.nvrInfo.password = paramValue;
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
                    Nozzle nozzle = new Nozzle();
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
            return true;
        }
        private bool InitDev()
        {
            Global.LogServer.Add(new LogInfo("Debug","main->InitDev in", (int)EnumLogLevel.DEBUG));
            
            int structLenth = Marshal.SizeOf(typeof(structNozzle));
            IntPtr ip = Marshal.AllocHGlobal(Global.nozzleList.Count* structLenth);
            structNozzle[] nozz = new structNozzle[Global.nozzleList.Count];
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
            int ret = SPlate.SP_InitRunParam(ipp, Global.nozzleList.Count);

            Global.LogServer.Add(new LogInfo("Debug", "main:InitDev SP_InitRunParam done return value"+ret.ToString(), (int)EnumLogLevel.DEBUG));
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev->SP_InitNVR begin, param value " + Global.nvrInfo.ip + " "
                + Global.nvrInfo.port.ToString() + " " + Global.nvrInfo.loginName + " " + Global.nvrInfo.password, (int)EnumLogLevel.DEBUG));

            ret = SPlate.SP_InitNVR(Global.nvrInfo.ip, Global.nvrInfo.port, Global.nvrInfo.loginName, Global.nvrInfo.password);
            Global.LogServer.Add(new LogInfo("Debug", "main->InitDev->SP_InitNVR done, return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));
            if (ret == 0)
                return true;
            else
                return false;
            
        }
        private bool InitAlg()
        {
            //TODO 临时操作
            return true;
            TH_PlateIDCfg th_PlateIDCfg = new TH_PlateIDCfg();
            th_PlateIDCfg.nMaxPlateWidth = 400;
            th_PlateIDCfg.nMinPlateWidth = 60;

            th_PlateIDCfg.nMaxImageWidth = 3000;
            th_PlateIDCfg.nMaxImageHeight = 2500;

            th_PlateIDCfg.nFastMemorySize = 16000;//DSP内存大小  
            th_PlateIDCfg.pFastMemory = Marshal.AllocHGlobal(16000);//DSP申请内存 

            th_PlateIDCfg.pMemory = Marshal.AllocHGlobal(50000000);//申请普通内存  
            th_PlateIDCfg.nMemorySize = 50000000;
            th_PlateIDCfg.bUTF8 = 0;
            th_PlateIDCfg.bShadow = 1;
            th_PlateIDCfg.bCarLogo = 0;
            th_PlateIDCfg.bLeanCorrection = 1;
            th_PlateIDCfg.bCarModel = 0;
            th_PlateIDCfg.bOutputSingleFrame = 1;
            th_PlateIDCfg.bMovingImage = 0;
            Global.LogServer.Add(new LogInfo("Debug", "main->SP_InitAlg begin", (int)EnumLogLevel.DEBUG));
            int ret = SPlate.SP_InitAlg(ref th_PlateIDCfg);
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
            NET_DVR_IPPARACFG_V40 nvrConfig = new NET_DVR_IPPARACFG_V40();
        }
        private void GetCarFromDll()
        {
            int count =  SPlate.SP_GetCarCount();
            if (count < 1)
                return;
            for (int i =0;i<count;i++)
            {
                CarInfoOut carOut = new CarInfoOut();
                IntPtr pCarOut = Marshal.AllocHGlobal(Marshal.SizeOf(carOut));
                SPlate.SP_GetFirstCarInfo(pCarOut);
                carOut = (CarInfoOut)Marshal.PtrToStructure(pCarOut, typeof(CarInfoOut));
                CarInfo info = new CarInfo();
                
            }
        }

        #endregion

    }
}
