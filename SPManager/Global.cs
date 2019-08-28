using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Collections;
using SPManager.tool;

namespace SPManager
{
    public static class Global
    {
        
        [DllImport("user32.dll")]
        static extern uint RegisterWindowMessage(string lpString);
        public static uint WM_CARSNAP = RegisterWindowMessage("CARSNAP");    //抓拍

        //基础信息参数
        public static string softVersion;  //软件版本
        public static string iniPath = "config.ini";
        public static string basePicPath = "D:\\images\\";
        public static string updateAppName = "\\AutoUpdater\\AutoUpdater.exe";


        //系统运行参数
        public static string password = "1";  //系统密码
        public static string dllEncoder = "utf8"; //从动态库获取车牌的编码方式
        public static int nShowMode = 2;   //车牌匹配情况显示模式,1 carlog,2 tradelog；
        public static bool bShowStationBoard = false;
        public static bool bStationBoardInSet = false;  //是否设置面板
        public static int nStationBoardDirection = 1; //站点面板排布方向 0 水平 1 垂直
        public static string remoteIP = "127.0.0.1"; //远程服务器IP
        public static int remotePort = 6700; //远程服务器端口
        public static int nMonthTotal = 0;  //当月车辆总数
        public static int nMonthMatch = 0;  //当月匹配车辆数
        public static int nTodayCount = 0; //当天车辆总数
        public static int nTodayMatch = 0;   //当天匹配车辆
        public static int nMonthRatio = 0;   //总匹配率
        public static int nTodayRatio = 0; //当天匹配率
        public static int nStatus = 0;   //当前运行状态
        public static int nRunMode = 4;//运行模式，1，抓图实时识别，无视频流 2、海康超脑 3、大华超脑 4、多路视频流识别
        public static int nCaptureFlag = 1;  //抓拍使能; 0 关闭 1开启
        public static int nVideoRecogFlag = 1; //视频识别是否开启，0 关闭，1开启
        public static int nVideoSource = 1;  //视频来源，1 海康 2 大华 3 科达
        public static int nVideoRecogType = 1;//视频识别模式， 1 文通算法识别， 2 NVR识别
        public static string defaultProvice = "鲁"; //文通识别算法默认省份
        public static int nMaxCarInSingleArea = 2; //单个识别区最多车牌数
        public static DateTime updateTime;  
        public static int nLogLevel = 3;   //日志级别 
        public static int ditMode = 2;     //DIT交互模式,1:通过动态库,2,软件直连
        public static string localDitIP = "0.0.0.0";  //DIT服务IP
        public static int localDitPort = 8870;   //DIT服务端口
        public static string DitIP = "127.0.0.1"; //DIT软件IP，发送进出站信息连接IP
        public static int DitPort = 7890;  //DIT软件端口，发送进出站信息连接端口
        public static string localTradeIP = "0.0.0.0"; //作为服务端，接收交易信息IP
        public static int localTradePort = 9100; //作为服务端，接收交易信息端口
        public static int ditCallBackMode = 2; //DIT车牌回调模式 1:无出入口相机，新出现车牌直接回调， 2:有出入口相机，出口入相机车牌回调
        public static int isUpload =0; //是否开启数据上传 0x0000  pay,order,car,trade
        public static string upLoadUrl = ""; //数据上传地址
        public static bool bUseCacheCar = false;


        //运行服务
        public static Log LogServer;
        public static MysqlHelper mysqlHelper;
        public static MysqlHelper mysqlHelper2;
        public static MysqlHelper mysqlHelper3;
        public static SocketTool socketDit;
        public static SocketTool socketTrade;
        public static Upload uploadTrade;
        public static Upload uploadOrder;
        public static Upload uploadPayment;
        public static Upload uploadCar;
        public static Upload uploadCarRecord;
        public static Upload uploadHeartBeat;


        public static ClsStationInfo stationInfo = new ClsStationInfo();
        public static ClsNVRInfo clsNvrInfo = new ClsNVRInfo();
        public static Image greenImage = Image.FromFile(Application.StartupPath+"\\images\\Box_Green.png");
        public static Image redImage = Image.FromFile(Application.StartupPath + "\\images\\Box_red.png");
        public static int nMatchMode = 2;//匹配模式，1 有出入口相机，2 无出入口相机
        public static List<ClsNozzle> nozzleList = new List<ClsNozzle>();
        public static List<ClsRecogArea> areaList = new List<ClsRecogArea>();
        public static List<ClsVideoChannel> videoChanList = new List<ClsVideoChannel>();
        public static List<string> entryLicenseList = new List<string>();
        public static List<string> exitLicenseList = new List<string>();
        // public static QueueManager<ClsPicture> picQueue = new QueueManager<ClsPicture>();
        public static int nSavePicture = 0;  //0不存图片，1存图片
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
        public static Dictionary<string, string> controlMap = new Dictionary<string, string>();
        public static Dictionary<int, int> DicAreaIndexInList = new Dictionary<int, int>();
        public static Dictionary<int, int> DicNozzleIndexInList = new Dictionary<int, int>();
        public static Hashtable carLogoHashtable = new Hashtable();
        public static ClsCarInfo[] arrayAreaCar;
        public static ClsCarInfo[] arrayNozzleCar;
        public static ClsGasIsland[] arrayIsland;
        public static List<ControlBoard> listControls = new List<ControlBoard>();
        public static int[] carCount = new int[24];
        public static int[] waitTime = new int[24];
        public static List<ClsCarArrive> listCarArrive;
        public static PumpInfo []currentPump = new PumpInfo [100];

        public static Hashtable oilInfoHashtable = new Hashtable();
        public static Hashtable carBrandHashtable = new Hashtable();
        
    }

}
