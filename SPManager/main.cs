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
            //TODO 临时注销
            //if (!InitParam())
            //{
            //    ret += 1 << 2;
            //    return ret;
            //}
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

            string queryString = "select paramName,paramValue,content,defaultValue from param ";
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                foreach (DataRow dr in dt.Rows)
                {
                    string paramName = (string)dr[0];
                    string paramValue = (string)dr[1];
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
                Global.LogServer.Add(new LogInfo("Error", "Main:InitRumParm 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            //queryString = "select "
            
            return true;
        }
       
        private bool InitSocket()
        {
            return true;
        }
        private bool InitDev()
        {
            Global.LogServer.Add(new LogInfo("Debug","main:InitDev in", (int)EnumLogLevel.DEBUG));
            byte[] videoChan = new byte[] { 36, 37, 38, 39 };
            IntPtr ip = Marshal.AllocHGlobal(videoChan.Length);
            Marshal.Copy(videoChan, 0, ip, videoChan.Length);
            int ret = SPlate.SP_InitRunParam(ip, videoChan.Length);
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
            TH_PlateIDCfg th_PlateIDCfg = new TH_PlateIDCfg();
            th_PlateIDCfg.nMaxPlateWidth = 400;
            th_PlateIDCfg.nMinPlateWidth = 60;

            th_PlateIDCfg.nMaxImageWidth = 3000;
            th_PlateIDCfg.nMaxImageHeight = 2500;

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
            th_PlateIDCfg.bMovingImage = 0;
            int ret = SPlate.SP_InitAlg(ref th_PlateIDCfg);
            Global.LogServer.Add(new LogInfo("Debug", "main->SP_InitAlg done, return value" + ret.ToString(), (int)EnumLogLevel.DEBUG));
            if (ret == 0)
                return true;
            else
                return false;
        }

        #endregion

        #region 获取，处理数据
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
