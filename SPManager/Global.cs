using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
namespace SPManager
{
    public static class Global
    {
        public static string softVersion;
        public static DateTime updateTime; 
        public static Log LogServer;
        public static int nLogLevel = 1;
        public static string iniPath ="config.ini";
        public static MysqlHelper mysqlHelper;
        public static StationInfo stationInfo = new StationInfo();
        public static Image greenImage = Image.FromFile(Application.StartupPath+"\\images\\Box_Green.png");
        public static Image redImage = Image.FromFile(Application.StartupPath + "\\images\\Box_red.png");
    }
    
}
