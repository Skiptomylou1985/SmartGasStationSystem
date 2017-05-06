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
        public static int nLogLevel = 3;
        public static string iniPath ="config.ini";
        public static string basePicPath = "D:\\images\\";
        public static MysqlHelper mysqlHelper;
        public static StationInfo stationInfo = new StationInfo();
        public static NVRInfo nvrInfo = new NVRInfo();
        public static Image greenImage = Image.FromFile(Application.StartupPath+"\\images\\Box_Green.png");
        public static Image redImage = Image.FromFile(Application.StartupPath + "\\images\\Box_red.png");
        public static int nMatchMode = 1;//匹配模式，1 有出入口相机，2 无出入口相机
        public static List<CarInfo> carList = new List<CarInfo>();
        public static List<Nozzle> nozzleList = new List<Nozzle>();
        public static int nDefaultWidth = 1920;
        public static int nDefaultHeight = 1020;
    }
    
}
