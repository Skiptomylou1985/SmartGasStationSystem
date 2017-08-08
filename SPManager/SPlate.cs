using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace SPManager
{
    #region  算法数据结构定义块
    //矩形区域结构体  
    [StructLayout(LayoutKind.Explicit, CharSet = CharSet.Auto)]
    public struct TH_RECT
    {
        [FieldOffset(0)]
        public int left;
        [FieldOffset(4)]
        public int top;
        [FieldOffset(8)]
        public int right;
        [FieldOffset(12)]
        public int bottom;
    }

    //配置结构体  
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]   //此处不要加Pack =1 字节对齐
    public struct TH_PlateIDCfg
    {
        public int nMinPlateWidth;      //检测的最小车牌宽度，以像素为单位
        public int nMaxPlateWidth;      //检测的最大车牌宽度，以像素为单位
        public int nMaxImageWidth;      //最大图像宽度
        public int nMaxImageHeight;     //最大图像高度
        public byte bVertCompress;      //是否只取帧图像的一场进行识别。
        public byte bIsFieldImage;      //是否输入场图像
        public byte bOutputSingleFrame; //是否视频图像中同一个车的多幅图像只输出一次结果
        public byte bMovingImage;       //识别运动or 静止图像
        public byte bIsNight;           //夜间模式
        public byte nImageFormat;       //图像格式
        public IntPtr pFastMemory;      //DSP 等的片内内存，耗时多的运算优先使用这些内存
        public int nFastMemorySize;     //快速内存的大小
        public IntPtr pMemory;          //普通内存的地址，内建的内存管理，避免内存泄漏等问题
        public int nMemorySize;         //普通内存的大小
        //int (*DMA_DataCopy)(void *dst, void *src,int nSize);
        //int (*Check_DMA_Finished)();
        public IntPtr DMA_DataCopy;     //PC上用不到的函数指针,为了不影响下面的参数设置生效,暂时这么写
        public IntPtr Check_DMA_Finished;

        public int nLastError;          //用于传递错误信息
        // 0: 无错误
        // 1: Find Plate(没有找到车牌)
        // 2: 车牌评价值(0 分)
        // 3: 车牌评价值(不及格)
        // 4: 车牌识别分数(0 分)
        // 5: 车牌识别分数(不及格)
        public int nErrorModelSN;       //出错的模块编号
        public byte nOrderOpt;		    //输出顺序选项 0-置信度 1-自上而下 2-自下而上
        public byte bLeanCorrection;	//是否启用倾斜校正
        public byte bMovingOutputOpt; 	//0-内部推送+外部获取 1:外部获取
        public byte nImproveSpeed;      //0: 识别率优先 1:识别速度优先
        public byte bCarLogo;           //0: 不检测车标 1: 检测车标
        public byte bLotDetect;			//0: 不检测车位 1: 检测车位
        public byte bShadow;            //0: 针对无阴影的车牌 1：针对有阴影的车牌
        public byte bUTF8;				//0:汉字GBK,1:汉字UTF-8
        public byte bShieldRailing;		//0: 屏蔽栏杆干扰， 1:不屏蔽栏杆干扰
        public byte bCarModel;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 110)]
        public byte[] reserved;         //保留
    }

    //识别结果结构体 
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto,Pack =1)]
    public struct TH_PlateResult
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] license;      //车牌字符串 
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] color;        //车辆的颜色 
        public int nColor;          //颜色（数字）
        public int nType;	        //车牌类型
        public int nConfidence;	    //整牌可信度
        public int nBright;	        //亮度评价
        public int nDirection;      //运动方向，0 unknown, 1 left, 2 right, 3 up , 4 down
        public TH_RECT rcLocation;	//车牌在整个图像中的位置
        IntPtr pbyBits;	            //DSP等的片内内存，耗时多的运算优先使用这些内存
        public int nTime;	        //识别时间
        public byte nCarBright;     //车的亮度  保留
        public byte nCarColor;		//车的颜色  保留
        public byte nCarLogo;
        public byte nCarType;

        IntPtr pbyPlateBin;         //车牌二值化结果（按bit存储）
        public short nBinPlateWidth;  //二值化结果中车牌宽度
        public short nBinPlateHeight; //二值化结果中车牌高度


        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 70)]
        public byte[] reserved;     //保留

        public TH_RECT rcLogoLocation;			// 车标坐标
        public short nCarModel;		            // 车辆类型
        public short nCarModelConfidence;		//车型可信度	
    }



    #endregion

    #region NVR数据结构定义块
    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct NET_DVR_PREVIEWINFO
    {
        public Int32 lChannel;//通道号
        public uint dwStreamType;   // 码流类型，0-主码流，1-子码流，2-码流3，3-码流4 等以此类推
        public uint dwLinkMode;// 0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-RTP/RTSP,5-RSTP/HTTP 
        public IntPtr hPlayWnd;//播放窗口的句柄,为NULL表示不播放图象
        public bool bBlocked;  //0-非阻塞取流, 1-阻塞取流, 如果阻塞SDK内部connect失败将会有5s的超时才能够返回,不适合于轮询取流操作.
        public bool bPassbackRecord; //0-不启用录像回传,1启用录像回传
        public byte byPreviewMode;//预览模式，0-正常预览，1-延迟预览
        [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 32, ArraySubType = UnmanagedType.I1)]
        public byte[] byStreamID;//流ID，lChannel为0xffffffff时启用此参数
        public byte byProtoType; //应用层取流协议，0-私有协议，1-RTSP协议
        [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.I1)]
        public byte[] byRes1;
        public uint dwDisplayBufNum;
        [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 216, ArraySubType = UnmanagedType.I1)]
        public byte[] byRes;
    }
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto, Pack = 1)]
    public struct NET_DVR_IPPARACFG_V40
    {

        public int dwSize;                            /* 结构大小 */
        public int dwGroupNum;                    //     设备支持的总组数    
        public int dwAChanNum;                    //最大模拟通道个数
        public int dwDChanNum;                  //数字通道个数
        public int dwStartDChan;                    //起始数字通道
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] byAnalogChanEnable;    /* 模拟通道是否启用，从低到高表示1-64通道，0表示无效 1有效 */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public NET_DVR_IPDEVINFO_V31[] struIPDevInfo;      /* IP设备 */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public NET_DVR_STREAM_MODE[] struStreamMode;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public byte[] byRes2;                 // 保留字节

    }
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto, Pack = 1)]
    public struct NET_DVR_IPDEVINFO_V31
    {
        public byte byEnable;                    //该IP设备是否有效
        public byte byProType;                    //协议类型，0-私有协议，1-松下协议，2-索尼
        public byte byEnableQuickAdd;        // 0 不支持快速添加  1 使用快速添加 
                                             // 快速添加需要设备IP和协议类型，其他信息由设备默认指定
        public byte byRes1;                    //保留字段，置0
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] sUserName;        //用户名
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] sPassword;        //密码
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 64)]
        public byte[] byDomain;    //设备域名
        public NET_DVR_IPADDR struIP;            //IP地址
        public short wDVRPort;                     // 端口号
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
        public byte[] szDeviceID;  //设备ID
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public byte[] byRes2;                //保留字段，置0
    }
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto, Pack = 1)]
    public struct NET_DVR_IPADDR
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] sIpV4;                        /* IPv4地址 */
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 128)]
        public byte[] byIPv6;                        /* 保留 */
    }
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto, Pack = 1)]
    public struct NET_DVR_STREAM_MODE
    {
        public byte byGetStreamType; //取流方式GET_STREAM_TYPE，0-直接从设备取流，1-从流媒体取流、2-通过IPServer获得ip地址后取流,3.通过IPServer找到设备，再通过流媒体去设备的流
                              //4-通过流媒体由URL去取流,5-通过hkDDNS取流，6-直接从设备取流(扩展)，使用NET_DVR_IPCHANINFO_V40结构, 7-通过RTSP协议方式进行取流
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public byte[] byRes;        //保留字节
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 492)]
        public byte[] uGetStream;    // 不同取流方式结构体
    }
    #endregion
    class SPlate
    {
        [DllImport("SPlate.dll")]
        public static extern int SP_InitRunParam(byte[] nozzleInfo,int lenth);
        [DllImport("SPlate.dll")]
        public static extern int SP_InitRunParam_Nozzle(byte[] nozzleInfo, int nozzleCount);
        [DllImport("SPlate.dll")]
        public static extern int SP_InitRunParam_Video(byte[] videoInfo, int videoCount);
        [DllImport("SPlate.dll")]
        public static extern int SP_InitNVR(string ipAddress, int nPort, string sAdmin, string sPassword);
        [DllImport("SPlate.dll")]
        public static extern int SP_GetNvrCfg(IntPtr nvrCfg,ref int lenth);
        [DllImport("SPlate.dll")]
        public static extern int SP_Close();
        [DllImport("SPlate.dll")]
        public static extern int SP_InitAlg(ref TH_PlateIDCfg pPlateConfig,int lenth);
        [DllImport("SPlate.dll")]
        public static extern int SP_PreviewInfo(ref NET_DVR_PREVIEWINFO previewInfo,int lenth);
        [DllImport("SPlate.dll")]
        public static extern int SP_BeginRecog();
       
        [DllImport("SPlate.dll")]
        public static extern int SP_TestAPI();
        [DllImport("SPlate.dll")]
        public static extern int SP_GetCarCount();
        [DllImport("SPlate.dll")]
        public static extern int SP_GetFirstCarInfo(IntPtr pCarInfoOut,ref int lenth );
        [DllImport("SPlate.dll")]
        public static extern int SP_GetAreaCarInfo(IntPtr pCarInfoOut, int areaNo);
        [DllImport("SPlate.dll")]
        public static extern int SP_GetCarInfo(IntPtr pCarInfoOut, int carCount,ref int lenth);
        [DllImport("SPlate.dll")]
        public static extern int SP_GetNvrStatus();
        [DllImport("SPlate.dll")]
        public static extern int SP_SetLogLevel(int loglevel);
        [DllImport("SPlate.dll")]
        public static extern int SP_Capture(int nozzleNo, IntPtr carinfo);
       // [DllImport("SPlate.dll")]
       // public static extern int SP_Capture_V2(int nozzleNo, IntPtr carinfo);

       

    }
}
