using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
namespace SPManager
{
    public static class Global
    {
        
        [DllImport("user32.dll")]
        static extern uint RegisterWindowMessage(string lpString);
        public static uint WM_CARSNAP = RegisterWindowMessage("CARSNAP");    //抓拍
        public static byte byNozzle = 0;
        public static byte byNozzleStatus = 0;
        public static string softVersion;
        public static DateTime updateTime; 
        public static Log LogServer;
        public static int nLogLevel = 3;
        public static string iniPath ="config.ini";
        public static string basePicPath = "D:\\images\\";
        public static string updateAppName = "\\AutoUpdater\\AutoUpdater.exe";
        public static MysqlHelper mysqlHelper;
        public static SocketTool socketTool;
        public static string socketIP = "127.0.0.1";
        public static int socketPort = 8870;
        public static ClsStationInfo stationInfo = new ClsStationInfo();
        public static ClsNVRInfo clsNvrInfo = new ClsNVRInfo();
        public static Image greenImage = Image.FromFile(Application.StartupPath+"\\images\\Box_Green.png");
        public static Image redImage = Image.FromFile(Application.StartupPath + "\\images\\Box_red.png");
        public static int nMatchMode = 2;//匹配模式，1 有出入口相机，2 无出入口相机
        public static List<ClsCarInfo> carList = new List<ClsCarInfo>();
        public static List<ClsNozzle> nozzleList = new List<ClsNozzle>();
        // public static QueueManager<ClsPicture> picQueue = new QueueManager<ClsPicture>();
        public static PictureWork picWork;
        public static int nDefaultWidth = 1920;
        public static int nDefaultHeight = 1020;
        public static NET_DVR_IPPARACFG_V40 net_dvr_cfg = new NET_DVR_IPPARACFG_V40();
        public static ClsServiceStatus clsServiceStatus = new ClsServiceStatus();

    }
    
}
