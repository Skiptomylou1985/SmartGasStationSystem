using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Collections;

namespace SPManager
{
    public static class Global
    {
        
        [DllImport("user32.dll")]
        static extern uint RegisterWindowMessage(string lpString);
        public static uint WM_CARSNAP = RegisterWindowMessage("CARSNAP");    //抓拍
        public static string softVersion;  //软件版本
        public static string dllEncoder = "utf8"; //
        public static string remoteIP = "127.0.0.1";
        public static int remotePort = 6700;
        public static int nTotalCount = 0;
        public static int nCurrentCount = 0;
        public static int nTotalRatio = 0;
        public static int nCurrenrRatio = 0;
        public static int nStatus = 0;
        public static int nRunMode = 4;//运行模式，1，抓图实时识别，无视频流 2、海康超脑 3、大华超脑 4、多路视频流识别
        public static int nCaptureFlag = 1;  //抓拍使能; 0 关闭 1开启
        public static int nVideoRecogFlag = 1; //视频识别是否开启，0 关闭，1开启
        public static int nVideoSource = 1;  //视频来源，1 海康 2 大华 3 科达
        public static int nVideoRecogType = 1;//视频识别模式， 1 文通算法识别， 2 NVR识别
        public static string defaultProvice = "鲁"; //文通识别算法默认省份
        public static int nMaxCarInSingleArea = 2; //单个识别区最多车牌数
        public static DateTime updateTime;  
        public static Log LogServer;
        public static int nLogLevel = 3;   //日志级别 
        public static string iniPath ="config.ini";
        public static string basePicPath = "D:\\images\\";
        public static string updateAppName = "\\AutoUpdater\\AutoUpdater.exe";
        public static MysqlHelper mysqlHelper;
        public static SocketTool socketTool;
        public static string socketIP = "0.0.0.0";  //DIT服务IP
        public static int socketPort = 8870;   //DIT服务端口
        public static ClsStationInfo stationInfo = new ClsStationInfo();
        public static ClsNVRInfo clsNvrInfo = new ClsNVRInfo();
        public static Image greenImage = Image.FromFile(Application.StartupPath+"\\images\\Box_Green.png");
        public static Image redImage = Image.FromFile(Application.StartupPath + "\\images\\Box_red.png");
        public static int nMatchMode = 2;//匹配模式，1 有出入口相机，2 无出入口相机
        public static List<ClsCarInfo> carList = new List<ClsCarInfo>();
        public static List<ClsNozzle> nozzleList = new List<ClsNozzle>();
        public static List<ClsRecogArea> areaList = new List<ClsRecogArea>();
        public static List<ClsVideoChannel> videoChanList = new List<ClsVideoChannel>();
        public static List<string> entryLicenseList = new List<string>();
        public static List<string> exitLicenseList = new List<string>();
        // public static QueueManager<ClsPicture> picQueue = new QueueManager<ClsPicture>();
        public static PictureWork picWork;
        public static int nDefaultWidth = 1920;
        public static int nDefaultHeight = 1080;
        public static NET_DVR_IPPARACFG_V40 net_dvr_cfg = new NET_DVR_IPPARACFG_V40();
        public static ClsServiceStatus clsServiceStatus = new ClsServiceStatus();
        public static int entryAreaID = 0;
        public static int exitAreaID = 0;
        public static object lockObj = new object();
        public static Dictionary<int, int> areaMap = new Dictionary<int, int>();
        public static Dictionary<int,int> nozzleMap = new Dictionary<int, int>();
        public static Dictionary<int, int> islandMap = new Dictionary<int, int>();
        public static Hashtable carLogoHashtable = new Hashtable();
        public static ClsCarInfo[] arrayAreaCar;
        public static ClsCarInfo[] arrayNozzleCar;
        public static ClsGasIsland[] arrayIsland;
    }
    
}
