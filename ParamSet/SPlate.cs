using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace ParamSet
{
   
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
        public static extern int SP_InitNVR(string ipAddress, int nPort, string sAdmin, string sPassword);
        [DllImport("SPlate.dll")]
        public static extern int SP_GetNvrCfg(IntPtr nvrCfg,ref int lenth);
        [DllImport("SPlate.dll")]
        public static extern int SP_Close();
       
        [DllImport("SPlate.dll")]
        public static extern int SP_PreviewInfo(ref NET_DVR_PREVIEWINFO previewInfo,int lenth);
        [DllImport("SPlate.dll")]
        public static extern int SP_TestAPI();
        [DllImport("SPlate.dll")]
        public static extern int SP_GetNvrStatus();
        [DllImport("SPlate.dll")]
        public static extern int SP_SetLogLevel(int loglevel);
    }
}
