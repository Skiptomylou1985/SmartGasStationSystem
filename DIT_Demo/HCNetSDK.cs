using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
namespace DIT_Demo
{

    [StructLayout(LayoutKind.Sequential,Pack =1)]
    public struct NET_ITS_PLATE_RESULT
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[]sLicense;     //车牌号码
        public byte byPlateColor;                  //车牌颜色
        public byte byColor;                       ///车颜色
        public short wVehicleLogoRecog;             ///车品牌
        public short wVehicleSubLogoRecog;          ///子品牌
        public byte byVehicleShape;					///车型
        public byte byVehicleState;              //进出站标识 1进站 2出站
    }
    [StructLayout(LayoutKind.Sequential,Pack =1)]
    public struct NET_DVR_PLATE_RESULT
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] sLicense;     //车牌号码
        public byte byPlateColor;                  //车牌颜色
        public byte byColor;                           ///车颜色
        public short wVehicleLogoRecog;             ///车品牌
        public short wVehicleSubLogoRecog;              ///子品牌
        public byte byVehicleShape;                    ///车型
        public byte byPumpID;                      ///油枪ID
        public byte byPumpStatus;					///油枪状态

    }
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct NET_DVR_DEVICEINFO_V30
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 48)]
        public byte[] sSerialNumber;  //序列号
        public byte byAlarmInPortNum;                //报警输入个数
        public byte byAlarmOutPortNum;                //报警输出个数
        public byte byDiskNum;                    //硬盘个数
        public byte byDVRType;                    //设备类型, 1:DVR 2:ATM DVR 3:DVS ......
        public byte byChanNum;                    //模拟通道个数
        public byte byStartChan;                    //起始通道号,例如DVS-1,DVR - 1
        public byte byAudioChanNum;                //语音通道数
        public byte byIPChanNum;                    //最大数字通道个数，低位  
        public byte byZeroChanNum;            //零通道编码个数 //2010-01-16
        public byte byMainProto;            //主码流传输协议类型 0-private, 1-rtsp,2-同时支持private和rtsp
        public byte bySubProto;                //子码流传输协议类型0-private, 1-rtsp,2-同时支持private和rtsp
        public byte bySupport;        //能力，位与结果为0表示不支持，1表示支持，
                                      //bySupport & 0x1, 表示是否支持智能搜索
                                      //bySupport & 0x2, 表示是否支持备份
                                      //bySupport & 0x4, 表示是否支持压缩参数能力获取
                                      //bySupport & 0x8, 表示是否支持多网卡
                                      //bySupport & 0x10, 表示支持远程SADP
                                      //bySupport & 0x20, 表示支持Raid卡功能
                                      //bySupport & 0x40, 表示支持IPSAN 目录查找
                                      //bySupport & 0x80, 表示支持rtp over rtsp
        public byte bySupport1;        // 能力集扩充，位与结果为0表示不支持，1表示支持
                                       //bySupport1 & 0x1, 表示是否支持snmp v30
                                       //bySupport1 & 0x2, 支持区分回放和下载
                                       //bySupport1 & 0x4, 是否支持布防优先级    
                                       //bySupport1 & 0x8, 智能设备是否支持布防时间段扩展
                                       //bySupport1 & 0x10, 表示是否支持多磁盘数（超过33个）
                                       //bySupport1 & 0x20, 表示是否支持rtsp over http    
                                       //bySupport1 & 0x80, 表示是否支持车牌新报警信息2012-9-28, 且还表示是否支持NET_DVR_IPPARACFG_V40结构体
        public byte bySupport2; /*能力，位与结果为0表示不支持，非0表示支持
					 bySupport2 & 0x1, 表示解码器是否支持通过URL取流解码
					 bySupport2 & 0x2,  表示支持FTPV40
					 bySupport2 & 0x4,  表示支持ANR
					 bySupport2 & 0x8,  表示支持CCD的通道参数配置
					 bySupport2 & 0x10,  表示支持布防报警回传信息（仅支持抓拍机报警 新老报警结构）
					 bySupport2 & 0x20,  表示是否支持单独获取设备状态子项
					 bySupport2 & 0x40,  表示是否是码流加密设备*/
        public short wDevType;              //设备型号
        public byte bySupport3; //能力集扩展，位与结果为0表示不支持，1表示支持
                                //bySupport3 & 0x1, 表示是否多码流
                                // bySupport3 & 0x4 表示支持按组配置， 具体包含 通道图像参数、报警输入参数、IP报警输入、输出接入参数、
                                // 用户参数、设备工作状态、JPEG抓图、定时和时间抓图、硬盘盘组管理 
                                //bySupport3 & 0x8为1 表示支持使用TCP预览、UDP预览、多播预览中的"延时预览"字段来请求延时预览（后续都将使用这种方式请求延时预览）。而当bySupport3 & 0x8为0时，将使用 "私有延时预览"协议。
                                //bySupport3 & 0x10 表示支持"获取报警主机主要状态（V40）"。
                                //bySupport3 & 0x20 表示是否支持通过DDNS域名解析取流

        public byte byMultiStreamProto;//是否支持多码流,按位表示,0-不支持,1-支持,bit1-码流3,bit2-码流4,bit7-主码流，bit-8子码流
        public byte byStartDChan;        //起始数字通道号,0表示无效
        public byte byStartDTalkChan;    //起始数字对讲通道号，区别于模拟对讲通道号，0表示无效
        public byte byHighDChanNum;        //数字通道个数，高位
        public byte bySupport4;        //能力集扩展，位与结果为0表示不支持，1表示支持
                                       //bySupport4 & 0x4表示是否支持拼控统一接口
                                       // bySupport4 & 0x80 支持设备上传中心报警使能。表示判断调用接口是 NET_DVR_PDC_RULE_CFG_V42还是 NET_DVR_PDC_RULE_CFG_V41
        public byte byLanguageType;// 支持语种能力,按位表示,每一位0-不支持,1-支持  
                                   //  byLanguageType 等于0 表示 老设备
                                   //  byLanguageType & 0x1表示支持中文
                                   //  byLanguageType & 0x2表示支持英文
        public byte byVoiceInChanNum;   //音频输入通道数 
        public byte byStartVoiceInChanNo; //音频输入起始通道号 0表示无效
        public byte bySupport5;  //按位表示,0-不支持,1-支持,bit0-支持多码流
                                 //bySupport5 &0x01表示支持wEventTypeEx ,兼容dwEventType 的事件类型（支持行为事件扩展）--先占住，防止冲突
                                 //bySupport5 &0x04表示是否支持使用扩展的场景模式接口
                                 /*
                                 bySupport5 &0x08 设备返回该值表示是否支持计划录像类型V40接口协议(DVR_SET_RECORDCFG_V40/ DVR_GET_RECORDCFG_V40)(在该协议中设备支持类型类型13的配置)
                                 之前的部分发布的设备，支持录像类型13，则配置录像类型13。如果不支持，统一转换成录像类型3兼容处理。SDK通过命令探测处理)
                                 */
        public byte bySupport6;   //能力，按位表示，0-不支持,1-支持
                                  //bySupport6 0x1  表示设备是否支持压缩 
                                  //bySupport6 0x2 表示是否支持流ID方式配置流来源扩展命令，DVR_SET_STREAM_SRC_INFO_V40
                                  //bySupport6 0x4 表示是否支持事件搜索V40接口
                                  //bySupport6 0x8 表示是否支持扩展智能侦测配置命令
                                  //bySupport6 0x40表示图片查询结果V40扩展
        public byte byMirrorChanNum;    //镜像通道个数，<录播主机中用于表示导播通道>
        public short wStartMirrorChanNo;  //起始镜像通道号
        public byte bySupport7;   //能力,按位表示,0-不支持,1-支持
                                  // bySupport7 & 0x1  表示设备是否支持 INTER_VCA_RULECFG_V42 扩展
                                  // bySupport7 & 0x2  表示设备是否支持 IPC HVT 模式扩展
                                  // bySupport7 & 0x04  表示设备是否支持 返回锁定时间
                                  // bySupport7 & 0x08  表示设置云台PTZ位置时，是否支持带通道号
                                  // bySupport7 & 0x10  表示设备是否支持双系统升级备份
                                  // bySupport7 & 0x20  表示设备是否支持 OSD字符叠加 V50
                                  // bySupport7 & 0x40  表示设备是否支持 主从跟踪（从摄像机）
                                  // bySupport7 & 0x80  表示设备是否支持 报文加密
        public byte byRes2;        //保留
    }
    [StructLayout(LayoutKind.Sequential)]
    public struct NET_DVR_MANUALSNAP
    {
       public byte byPumpID;//油枪号 （0-不生效，）
       public byte byPumpStatus;//油枪状态 （0-不生效，1-提抢，2-开始加油，3-挂枪）   
    }
    [StructLayout(LayoutKind.Sequential,Pack =1)]
    public struct NET_ITS_TRANS_INFO
    {
        public int nPumpID;  //油枪ID
        public int nOilType;                  //油品编码
        public float fTradeLitre;                      //交易升数
        public float fTradeMoney;                      //交易金额
        public float fTradePrice;                      //交易单价
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public byte[] sStartTime;    //提枪时间
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public byte[] sEndTime;     //挂枪时间
        public float fStartRead;       //提枪泵码
        public float fEndRead;         //挂枪泵码
    }
    class HCNetSDK
    {
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_Init();
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_Cleanup();
        [DllImport("HCNetSDK.dll")]
        public static extern  int NET_DVR_Login_V30(string DVRIP,ushort wDVRPort,string sUserName,string sPassWord,ref NET_DVR_DEVICEINFO_V30 lpDeviceInfo);
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_Logout(uint lUserID);
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_ManualSnap(uint lUserID,ref NET_DVR_MANUALSNAP lpInter,IntPtr lpOuter);
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_SetConnectTime(int dwWaitTime,int dwTryTimes);
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_SetReconnect(int dwInterval,bool bEnableRecon);
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_SendTrans(NET_ITS_TRANS_INFO tradeInfo);

        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_SetDVRMessageCallBack_V31(MSGCallBack_V31 fMessageCallBack,IntPtr pUser);
        public delegate void MSGCallBack_V31(int lcomd, IntPtr para1,IntPtr pAlarmInfo, int lenth, IntPtr pUser);
    }
}
