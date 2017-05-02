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
            if (!InitDevAlg())
            {
                ret += 1 << 3;
                return ret;
            }
            if (!InitSocket())
            {
                ret += 1 << 4;
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
                    {
                        Global.nLogLevel = int.Parse(paramValue);
                    }
                    else if (paramName == "stationname")
                    {
                        Global.stationInfo.stationName = paramValue;
                    }
                    else if (paramName == "stationcode")
                    {
                        Global.stationInfo.stationCode = paramValue;
                    }
                    else if (paramName == "province")
                    {
                        Global.stationInfo.province = paramValue;
                    }
                    else if (paramName == "city")
                    {
                        Global.stationInfo.city = paramValue;
                    }
                    else if (paramName == "district")
                    {
                        Global.stationInfo.district = paramValue;
                    }
                    else if (paramName == "address")
                    {
                        Global.stationInfo.addr = paramValue;
                    }
                    else if (paramName == "version")
                    {
                        Global.softVersion = paramValue;
                    }
                    else if (paramName == "updatetime")
                    {
                        Global.updateTime = DateTime.Parse(paramValue);
                    }
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
        private bool InitDevAlg()
        {

            return true;
        }
        private bool InitSocket()
        {
            return true;
        }
        
        #endregion

    }
}
