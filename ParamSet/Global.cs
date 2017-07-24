using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
namespace ParamSet
{
    public static class Global
    {

        
        public static string softVersion;
        public static DateTime updateTime; 
        public static Log LogServer;
        public static int nLogLevel = 3;
        public static string iniPath ="config.ini";
        public static string basePicPath = "D:\\images\\";
        public static int nAuthType = 0;  //算法授权模式 0本地授权 1 网络授权
        public static int nCaptureFlag = 1; //
        public static int nVideoRecogFlag = 1; 
        public static int nVideoRecogType = 0; // 0 算法识别，1 海康超脑，2大华超脑
        public static int nVideoSource = 0;  //0海康 1大华 2科达
        public static MysqlHelper mysqlHelper;
        public static ClsStationInfo stationInfo = new ClsStationInfo();
        public static List<ClsNVRInfo> nvrList = new List<ClsNVRInfo>();
        public static List<ClsVideoChannel> videoList = new List<ClsVideoChannel>();
        public static List<ClsRecogArea> recogAreaList = new List<ClsRecogArea>();
        public static List<ClsNozzle> nozzleList = new List<ClsNozzle>();
        public static Image greenImage = Image.FromFile(Application.StartupPath+"\\images\\Box_Green.png");
        public static Image redImage = Image.FromFile(Application.StartupPath + "\\images\\Box_red.png");
        public static int nMatchMode = 1;//匹配模式，1 有出入口相机，2 无出入口相机
        public static int nDefaultWidth = 1920;
        public static int nDefaultHeight = 1020;
        public static NET_DVR_IPPARACFG_V40 net_dvr_cfg = new NET_DVR_IPPARACFG_V40();
        public static bool bReDraw;
        public static bool bShowDraw;
        public static int nCurSelectedVideoChan  = 4;
        public static string sCurSelectedNvrName = "NVR01";
        public static bool bVideoInShow = false;
        public static int nCurStatus = 0;   //0显示 1 添加 2修改 
        public static ClsVideoChannel clsCurVideo = null;
        
    }
    
}
