// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 HCNETSDK_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// HCNETSDK_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef HCNETSDK_EXPORTS
#define HCNETSDK_API __declspec(dllexport)
#else
#define HCNETSDK_API __declspec(dllimport)
#endif

#include <WINSOCK2.H>

#define MAX_LICENSE_LEN 16
#define SERIALNO_LEN		    48      //序列号长度
#define MACADDR_LEN			    6       //mac地址长度
#define NAME_LEN			    32      //用户名长度
#define COMM_ITS_PLATE_RESULT     0x3050  //自动抓拍车牌信息上传


typedef struct tagNET_DVR_MANUALSNAP
{
	BYTE   byPumpID;//油枪号 （0-不生效，）
	BYTE   byPumpStatus;//油枪状态 （0-不生效，1-提抢，2-开始加油，3-挂枪）   		
}NET_DVR_MANUALSNAP, *LPNET_DVR_MANUALSNAP;
typedef struct tagNET_ITS_PLATE_RESULT
{
	char sLicense[MAX_LICENSE_LEN];		//车牌号码
	BYTE byPlateColor;					//车牌颜色
	BYTE byColor;						///车颜色
	WORD wVehicleLogoRecog;				///车品牌
	WORD	wVehicleSubLogoRecog;			///子品牌
	BYTE	byVehicleShape;					///车型
	BYTE	byVehicleState;              //进出站标识 1进站 2出站
}NET_ITS_PLATE_RESULT, *LPNET_ITS_PLATE_RESULT;

typedef struct tagNET_ITS_TRANS_INFO
{
	int nPumpID;	              //油枪ID
	int nItemCode;			 //油品编码
	float fTransVolume;		 //交易升数
	float fTransValue;		 //交易金额
	float fTransPrice;		 //交易单价
	char sStartTime[20];        //提枪时间
	char sEndTime[20];		 //挂枪时间
	float fPumpOpenCounter;     //提枪泵码
	float fPumpCloseCounter;    //挂枪泵码
}NET_ITS_TRANS_INFO, *LPNET_ITS_TRANS_INFO;


//手动抓拍传出结构体:
typedef struct tagNET_DVR_PLATE_RESULT
{
	char sLicense[MAX_LICENSE_LEN];		//车牌号码
	BYTE byPlateColor;					//车牌颜色
	BYTE byColor;							///车颜色
	WORD wVehicleLogoRecog;				///车品牌
	WORD wVehicleSubLogoRecog;				///子品牌
	BYTE byVehicleShape;					///车型
	BYTE byPumpID;						///油枪ID
	BYTE byPumpStatus;					///油枪状态
}NET_DVR_PLATE_RESULT, *LPNET_DVR_PLATE_RESULT;

//报警设备信息
typedef struct
{
	BYTE byUserIDValid;                 /* userid是否有效 0-无效，1-有效 */
	BYTE bySerialValid;                 /* 序列号是否有效 0-无效，1-有效 */
	BYTE byVersionValid;                /* 版本号是否有效 0-无效，1-有效 */
	BYTE byDeviceNameValid;             /* 设备名字是否有效 0-无效，1-有效 */
	BYTE byMacAddrValid;                /* MAC地址是否有效 0-无效，1-有效 */
	BYTE byLinkPortValid;               /* login端口是否有效 0-无效，1-有效 */
	BYTE byDeviceIPValid;               /* 设备IP是否有效 0-无效，1-有效 */
	BYTE bySocketIPValid;               /* socket ip是否有效 0-无效，1-有效 */
	LONG lUserID;                       /* NET_DVR_Login()返回值, 布防时有效 */
	BYTE sSerialNumber[SERIALNO_LEN];    /* 序列号 */
	DWORD dwDeviceVersion;                /* 版本信息 高16位表示主版本，低16位表示次版本*/
	char sDeviceName[NAME_LEN];            /* 设备名字 */
	BYTE byMacAddr[MACADDR_LEN];        /* MAC地址 */
	WORD wLinkPort;                     /* link port */
	char sDeviceIP[128];                /* IP地址 */
	char sSocketIP[128];                /* 报警主动上传时的socket IP地址 */
	BYTE byIpProtocol;                  /* Ip协议 0-IPV4, 1-IPV6 */
	BYTE byRes2[11];
}NET_DVR_ALARMER, *LPNET_DVR_ALARMER;
typedef struct
{
	BYTE sSerialNumber[SERIALNO_LEN];  //序列号
	BYTE byAlarmInPortNum;                //报警输入个数
	BYTE byAlarmOutPortNum;                //报警输出个数
	BYTE byDiskNum;                    //硬盘个数
	BYTE byDVRType;                    //设备类型, 1:DVR 2:ATM DVR 3:DVS ......
	BYTE byChanNum;                    //模拟通道个数
	BYTE byStartChan;                    //起始通道号,例如DVS-1,DVR - 1
	BYTE byAudioChanNum;                //语音通道数
	BYTE byIPChanNum;                    //最大数字通道个数，低位  
	BYTE byZeroChanNum;            //零通道编码个数 //2010-01-16
	BYTE byMainProto;            //主码流传输协议类型 0-private, 1-rtsp,2-同时支持private和rtsp
	BYTE bySubProto;                //子码流传输协议类型0-private, 1-rtsp,2-同时支持private和rtsp
	BYTE bySupport;        //能力，位与结果为0表示不支持，1表示支持，
						   //bySupport & 0x1, 表示是否支持智能搜索
						   //bySupport & 0x2, 表示是否支持备份
						   //bySupport & 0x4, 表示是否支持压缩参数能力获取
						   //bySupport & 0x8, 表示是否支持多网卡
						   //bySupport & 0x10, 表示支持远程SADP
						   //bySupport & 0x20, 表示支持Raid卡功能
						   //bySupport & 0x40, 表示支持IPSAN 目录查找
						   //bySupport & 0x80, 表示支持rtp over rtsp
	BYTE bySupport1;        // 能力集扩充，位与结果为0表示不支持，1表示支持
							//bySupport1 & 0x1, 表示是否支持snmp v30
							//bySupport1 & 0x2, 支持区分回放和下载
							//bySupport1 & 0x4, 是否支持布防优先级    
							//bySupport1 & 0x8, 智能设备是否支持布防时间段扩展
							//bySupport1 & 0x10, 表示是否支持多磁盘数（超过33个）
							//bySupport1 & 0x20, 表示是否支持rtsp over http    
							//bySupport1 & 0x80, 表示是否支持车牌新报警信息2012-9-28, 且还表示是否支持NET_DVR_IPPARACFG_V40结构体
	BYTE bySupport2; /*能力，位与结果为0表示不支持，非0表示支持
					 bySupport2 & 0x1, 表示解码器是否支持通过URL取流解码
					 bySupport2 & 0x2,  表示支持FTPV40
					 bySupport2 & 0x4,  表示支持ANR
					 bySupport2 & 0x8,  表示支持CCD的通道参数配置
					 bySupport2 & 0x10,  表示支持布防报警回传信息（仅支持抓拍机报警 新老报警结构）
					 bySupport2 & 0x20,  表示是否支持单独获取设备状态子项
					 bySupport2 & 0x40,  表示是否是码流加密设备*/
	WORD wDevType;              //设备型号
	BYTE bySupport3; //能力集扩展，位与结果为0表示不支持，1表示支持
					 //bySupport3 & 0x1, 表示是否多码流
					 // bySupport3 & 0x4 表示支持按组配置， 具体包含 通道图像参数、报警输入参数、IP报警输入、输出接入参数、
					 // 用户参数、设备工作状态、JPEG抓图、定时和时间抓图、硬盘盘组管理 
					 //bySupport3 & 0x8为1 表示支持使用TCP预览、UDP预览、多播预览中的"延时预览"字段来请求延时预览（后续都将使用这种方式请求延时预览）。而当bySupport3 & 0x8为0时，将使用 "私有延时预览"协议。
					 //bySupport3 & 0x10 表示支持"获取报警主机主要状态（V40）"。
					 //bySupport3 & 0x20 表示是否支持通过DDNS域名解析取流

	BYTE byMultiStreamProto;//是否支持多码流,按位表示,0-不支持,1-支持,bit1-码流3,bit2-码流4,bit7-主码流，bit-8子码流
	BYTE byStartDChan;        //起始数字通道号,0表示无效
	BYTE byStartDTalkChan;    //起始数字对讲通道号，区别于模拟对讲通道号，0表示无效
	BYTE byHighDChanNum;        //数字通道个数，高位
	BYTE bySupport4;        //能力集扩展，位与结果为0表示不支持，1表示支持
							//bySupport4 & 0x4表示是否支持拼控统一接口
							// bySupport4 & 0x80 支持设备上传中心报警使能。表示判断调用接口是 NET_DVR_PDC_RULE_CFG_V42还是 NET_DVR_PDC_RULE_CFG_V41
	BYTE byLanguageType;// 支持语种能力,按位表示,每一位0-不支持,1-支持  
						//  byLanguageType 等于0 表示 老设备
						//  byLanguageType & 0x1表示支持中文
						//  byLanguageType & 0x2表示支持英文
	BYTE byVoiceInChanNum;   //音频输入通道数 
	BYTE byStartVoiceInChanNo; //音频输入起始通道号 0表示无效
	BYTE  bySupport5;  //按位表示,0-不支持,1-支持,bit0-支持多码流
					   //bySupport5 &0x01表示支持wEventTypeEx ,兼容dwEventType 的事件类型（支持行为事件扩展）--先占住，防止冲突
					   //bySupport5 &0x04表示是否支持使用扩展的场景模式接口
					   /*
					   bySupport5 &0x08 设备返回该值表示是否支持计划录像类型V40接口协议(DVR_SET_RECORDCFG_V40/ DVR_GET_RECORDCFG_V40)(在该协议中设备支持类型类型13的配置)
					   之前的部分发布的设备，支持录像类型13，则配置录像类型13。如果不支持，统一转换成录像类型3兼容处理。SDK通过命令探测处理)
					   */
	BYTE  bySupport6;   //能力，按位表示，0-不支持,1-支持
						//bySupport6 0x1  表示设备是否支持压缩 
						//bySupport6 0x2 表示是否支持流ID方式配置流来源扩展命令，DVR_SET_STREAM_SRC_INFO_V40
						//bySupport6 0x4 表示是否支持事件搜索V40接口
						//bySupport6 0x8 表示是否支持扩展智能侦测配置命令
						//bySupport6 0x40表示图片查询结果V40扩展
	BYTE  byMirrorChanNum;    //镜像通道个数，<录播主机中用于表示导播通道>
	WORD wStartMirrorChanNo;  //起始镜像通道号
	BYTE bySupport7;   //能力,按位表示,0-不支持,1-支持
					   // bySupport7 & 0x1  表示设备是否支持 INTER_VCA_RULECFG_V42 扩展
					   // bySupport7 & 0x2  表示设备是否支持 IPC HVT 模式扩展
					   // bySupport7 & 0x04  表示设备是否支持 返回锁定时间
					   // bySupport7 & 0x08  表示设置云台PTZ位置时，是否支持带通道号
					   // bySupport7 & 0x10  表示设备是否支持双系统升级备份
					   // bySupport7 & 0x20  表示设备是否支持 OSD字符叠加 V50
					   // bySupport7 & 0x40  表示设备是否支持 主从跟踪（从摄像机）
					   // bySupport7 & 0x80  表示设备是否支持 报文加密
	BYTE  byRes2;        //保留
}NET_DVR_DEVICEINFO_V30, *LPNET_DVR_DEVICEINFO_V30;
typedef BOOL(CALLBACK *MSGCallBack_V31)(LONG lCommand, NET_DVR_ALARMER* pAlarmer, char* pAlarmInfo, DWORD dwBufLen, void* pUser);
extern "C" HCNETSDK_API BOOL NET_DVR_Init();
extern "C" HCNETSDK_API BOOL NET_DVR_Cleanup();
extern "C" HCNETSDK_API LONG NET_DVR_Login_V30(
	char  *sDVRIP,
	WORD wDVRPort,
	char  *sUserName,
	char  *sPassWord,
	LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo
);
extern "C" HCNETSDK_API BOOL NET_DVR_Logout(LONG lUserID);
extern "C" HCNETSDK_API BOOL NET_DVR_ManualSnap(
	LONG lUserID,
	NET_DVR_MANUALSNAP * lpInter,
	LPNET_DVR_PLATE_RESULT lpOuter
);
extern "C" HCNETSDK_API BOOL NET_DVR_SendTrans(NET_ITS_TRANS_INFO tradeInfo);
extern "C" HCNETSDK_API BOOL NET_DVR_SetDVRMessageCallBack_V31(
	MSGCallBack_V31 fMessageCallBack,
	void* pUser
);
extern "C" HCNETSDK_API BOOL NET_DVR_SetConnectTime(
	DWORD  dwWaitTime,
	DWORD  dwTryTimes
);
extern "C" HCNETSDK_API BOOL NET_DVR_SetReconnect(
	DWORD  dwInterval,
	BOOL    bEnableRecon
);
extern "C" HCNETSDK_API DWORD NET_DVR_GetLastError();
extern "C" HCNETSDK_API void NET_DVR_TestAPI();
typedef enum _VCA_PLATE_COLOR_
{
	VCA_BLUE_PLATE = 0,   //蓝色车牌
	VCA_YELLOW_PLATE,      //黄色车牌
	VCA_WHITE_PLATE,       //白色车牌
	VCA_BLACK_PLATE,       //黑色车牌
	VCA_GREEN_PLATE,       //绿色车牌
	VCA_BKAIR_PLATE,       //民航黑色车牌
	VCA_OTHER = 0xff       //其他
}VCA_PLATE_COLOR;

//车牌类型
typedef enum _VCA_PLATE_TYPE_
{
	VCA_STANDARD92_PLATE = 0,    //标准民用车与军车
	VCA_STANDARD02_PLATE,        //02式民用车牌 
	VCA_WJPOLICE_PLATE,            //武警车 
	VCA_JINGCHE_PLATE,            //警车
	STANDARD92_BACK_PLATE,         //民用车双行尾牌
	VCA_SHIGUAN_PLATE,          //使馆车牌
	VCA_NONGYONG_PLATE,         //农用车
	VCA_MOTO_PLATE              //摩托车
}VCA_PLATE_TYPE;

//车型识别结果
typedef enum _VTR_RESULT
{
	VTR_RESULT_OTHER = 0,  //未知
	VTR_RESULT_BUS = 1,  //客车
	VTR_RESULT_TRUCK = 2,  //货车
	VTR_RESULT_CAR = 3,  //轿车
	VTR_RESULT_MINIBUS = 4,  //面包车
	VTR_RESULT_SMALLTRUCK = 5,  //小货车
	VTR_RESULT_HUMAN = 6,  //行人
	VTR_RESULT_TUMBREL = 7,  //二轮车
	VTR_RESULT_TRIKE = 8,  //三轮车
	VTR_RESULT_SUV_MPV = 9,  //SUV/MPV
	VTR_RESULT_MEDIUM_BUS = 10,  //中型客车
	VTR_RESULT_MOTOR_VEHICLE = 11, //机动车
	VTR_RESULT_NON_MOTOR_VEHICLE = 12,  //非机动车
	VTR_RESULT_SMALLCAR = 13,   //小型轿车
	VTR_RESULT_MICROCAR = 14,   //微型轿车
	VTR_RESULT_PICKUP = 15    //皮卡车
}VTR_RESULT;


//车身颜色
typedef enum _VCR_CLR_CLASS
{
	VCR_CLR_UNSUPPORT = 0,      //不支持
	VCR_CLR_WHITE = 1,   //白
	VCR_CLR_SILVER = 2,   //银
	VCR_CLR_GRAY = 3,      //灰
	VCR_CLR_BLACK = 4,      //黑
	VCR_CLR_RED = 5,      //红
	VCR_CLR_DARKBLUE = 6,      //深蓝
	VCR_CLR_BLUE = 7,      //蓝
	VCR_CLR_YELLOW = 8,      //黄
	VCR_CLR_GREEN = 9,      //绿
	VCR_CLR_BROWN = 10,  //棕
	VCR_CLR_PINK = 11,  //粉
	VCR_CLR_PURPLE = 12,  //紫
	VCR_CLR_DARKGRAY = 13,  //深灰
	VCR_CLR_CYAN = 14  //青色
}VCR_CLR_CLASS;

//车辆操作类型 2013-11-04
typedef enum _VCA_OPERATE_TYPE_
{
	VCA_LICENSE_TYPE = 0x1,  //车牌号码
	VCA_PLATECOLOR_TYPE = 0x2,  //车牌颜色
	VCA_CARDNO_TYPE = 0x4,  //卡号
	VCA_PLATETYPE_TYPE = 0x8,  //车牌类型
	VCA_LISTTYPE_TYPE = 0x10, //车辆名单类型
	VCA_INDEX_TYPE = 0x20, //数据流水号 2014-02-25
	VCA_OPERATE_INDEX_TYPE = 0x40  //操作数 2014-03-03
}VCA_OPERATE_TYPE;

typedef enum _VCA_ILLEGAL_TYPE_
{
	VCA_POSTPIC_TYPE = 0x1, //卡口图片
	VCA_LOWSPEED_TYPE = 0x2,  //低速
	VCA_HIGHSPEED_TYPE = 0x4,  //高速
	VCA_RETROGRADE_TYPE = 0x8,  //逆行
	VCA_RUSH_REDLIGHT_TYPE = 0x10,   //闯红灯
	VCA_PRESS_LANE_TYPE = 0x20, //压车道线
	VCA_VIOLATE_GUIDE_TYPE = 0x40,//不按导向
	VCA_ROAD_STRAND_TYPE = 0x80,//路口滞留(设备不支持)
	VCA_VEHICLE_ILLEGAL_LANE_TYPE = 0x100,//机占非
	VCA_ILLEGAL_LANE_CHANGE_TYPE = 0x200,//违法变道
	VCA_ILLEGAL_LANE_DRIVE_TYPE = 0x400,//不按车道
	VCA_VIOLATE_BAN_TYPE = 0x800,//违法禁令
	VCA_CROSS_PARKING_TYPE = 0x1000,//路口停车
	VCA_GREEN_PARKING_TYPE = 0x2000//绿灯停车
}VCA_ILLEGAL_TYPE;

typedef enum _VCA_VEHICLE_TYPE_
{
	VCA_OTHER_TYPE = 0x1,  //其它车型
	VCA_SMALLCAR_TYPE = 0x2,  //小型车
	VCA_BIGCAR_TYPE = 0x4,  //大型车
	VCA_BUS_TYPE = 0x8,  //客车
	VCA_TRUCK_TYPE = 0x10,  //货车
	VCA_CAR_TYPE = 0x20,   //轿车
	VCA_MINIBUS_TYPE = 0x40,   //面包车
	VCA_SMALL_TRUCK_TYPE = 0x80  //小货车
}VCA_VEHICLE_TYPE;

//车辆品牌主类型
typedef enum _VLR_VEHICLE_CLASS
{
	VLR_OTHER = 0,    //其它
	VLR_VOLKSWAGEN = 1,    //大众
	VLR_BUICK = 2,    //别克
	VLR_BMW = 3,    //宝马
	VLR_HONDA = 4,    //本田
	VLR_PEUGEOT = 5,    //标致
	VLR_TOYOTA = 6,    //丰田
	VLR_FORD = 7,    //福特
	VLR_NISSAN = 8,    //日产
	VLR_AUDI = 9,    //奥迪
	VLR_MAZDA = 10,   //马自达
	VLR_CHEVROLET = 11,   //雪佛兰
	VLR_CITROEN = 12,   //雪铁龙
	VLR_HYUNDAI = 13,   //现代
	VLR_CHERY = 14,   //奇瑞
	VLR_KIA = 15,   //起亚
	VLR_ROEWE = 16,   //荣威
	VLR_MITSUBISHI = 17,   //三菱
	VLR_SKODA = 18,   //斯柯达
	VLR_GEELY = 19,   //吉利
	VLR_ZHONGHUA = 20,   //中华
	VLR_VOLVO = 21,   //沃尔沃
	VLR_LEXUS = 22,   //雷克萨斯
	VLR_FIAT = 23,   //菲亚特
	VLR_EMGRAND = 24,   //帝豪(吉利)
	VLR_DONGFENG = 25,   //东风
	VLR_BYD = 26,   //比亚迪
	VLR_SUZUKI = 27,   //铃木
	VLR_JINBEI = 28,   //金杯
	VLR_HAIMA = 29,   //海马
	VLR_SGMW = 30,   //五菱
	VLR_JAC = 31,   //江淮
	VLR_SUBARU = 32,   //斯巴鲁
	VLR_ENGLON = 33,   //英伦(吉利)
	VLR_GREATWALL = 34,   //长城
	VLR_HAFEI = 35,   //哈飞
	VLR_ISUZU = 36,   //五十铃(庆铃)
	VLR_SOUEAST = 37,   //东南
	VLR_CHANA = 38,   //长安
	VLR_FOTON = 39,   //福田
	VLR_XIALI = 40,   //夏利(一汽)
	VLR_BENZ = 41,   //奔驰
	VLR_FAW = 42,   //一汽
	VLR_NAVECO = 43,   //依维柯
	VLR_LIFAN = 44,   //力帆
	VLR_BESTURN = 45,   //一汽奔腾(一汽)
	VLR_CROWN = 46,   //皇冠(丰田)
	VLR_RENAULT = 47,   //雷诺
	VLR_JMC = 48,   //JMC(江铃)
	VLR_MG = 49,   //MG名爵
	VLR_KAMA = 50,   //凯马
	VLR_ZOTYE = 51,   //众泰
	VLR_CHANGHE = 52,   //昌河
	VLR_XMKINGLONG = 53,   //厦门金龙(金旅)
	VLR_HUIZHONG = 54,   //上海汇众(上汽集团)
	VLR_SZKINGLONG = 55,   //苏州金龙
	VLR_HIGER = 56,   //海格
	VLR_YUTONG = 57,   //宇通
	VLR_CNHTC = 58,   //中国重汽
	VLR_BEIBEN = 59,   //北奔重卡
	VLR_XINGMA = 60,   //华菱星马
	VLR_YUEJIN = 61,   //跃进
	VLR_HUANGHAI = 62,   //黄海
	VLR_OLDWALL = 63,   //老款长城
	VLR_CHANACOMMERCIAL = 64,   //长安商用
	VLR_PORSCHE = 65,               // 保时捷
	VLR_CADILLAC = 66,               // 凯迪拉克
	VLR_INFINITI = 67,               // 英菲尼迪
	VLR_GLEAGLE = 68,               // 吉利全球鹰(吉利)
	VLR_JEEP = 69,               // JEEP(吉普)
	VLR_LANDROVER = 70,               // 路虎
	VLR_CHANGFENG = 71,               // 长丰
	VLR_BENNI = 72,               // 长安奔奔(长安)
	VLR_ERA = 73,               // 福田时代(时代)
	VLR_TAURUS = 74,               // 长安金牛星(长安商用)
	VLR_EADO = 75,               // 长安逸动
	VLR_SHANQI = 76,               // 陕汽
	VLR_HONGYAN = 77,               // 红岩汽车(上汽依维柯红岩)
	VLR_DRAGON = 78,               // 霸龙汽车(东风柳汽)
	VLR_JACTEXT = 79,               // 江淮JAC (江淮)
	VLR_JACBUS = 80,               // 江淮现代客车 (江淮)
	VLR_ANKAI = 81,               // 安凯客车
	VLR_SHENLONG = 82,               // 申龙客车
	VLR_DAEWOO = 83,               // 大宇客车
	VLR_WUZHENG = 84,               // 五征汽车
	VLR_MAN = 85,               // MAN汽车
	VLR_ZHONGTONG = 86,               // 中通客车
	VLR_BAOJUN = 87,               // 宝骏
	VLR_BQWEIWANG = 88,               // 北汽威旺
	VLR_TRUMPCHE = 89,               // 传祺
	VLR_LUFENG = 90,               // 陆风
	VLR_HMZHENGZHOU = 91,               // 海马郑州
	VLR_BEIJING = 92,               // 北京汽车
	VLR_ZHONGSHUN = 93,               // 中顺
	VLR_WEILIN = 94,               // 威麟汽车
	VLR_OPEL = 95,               // 欧宝
	VLR_KARRY = 96,               // 开瑞
	VLR_SMA = 97,               // 华普汽车
	VLR_SMATEXT = 98,               // 华普汽车文字SMA
	VLR_YUWIN = 99,               // 江铃驭胜
	VLR_MINI = 100,               // 宝马MINI
	VLR_MARK = 101,               // 丰田MARKX 
	VLR_HAVAL = 102,               // 哈弗HAVAL
	VLR_OGA = 103,               // 讴歌
	VLR_VENUCIA = 104,               // 启辰
	VLR_BYD2 = 105,               // 比亚迪样式2 (比亚迪)
	VLR_SMART = 106,               // 奔驰SMART
	VLR_BAW = 107,               // 北京汽车制造厂BAW
	VLR_LUXGEN = 108,               // 纳智捷
	VLR_YEMA = 109,               // 野马
	VLR_ZTE = 110,               // 中兴
	VLR_EVERUS = 111,               // 理念
	VLR_CHRYSLER = 112,               // 克莱斯勒
	VLR_GONOW = 113,               // 吉奥汽车
	VLR_SHJIANG = 114,               // 松花江
	VLR_RUILIN = 115,               // 瑞麟
	VLR_FORTA = 116,               // 福达
	VLR_GAGUAR = 117,               // 捷豹
	VLR_HEIBAO = 118,               // 黑豹
	VLR_TKING = 119,               // 唐骏
	VLR_TKINGTEXT = 120,               // 唐骏文字
	VLR_FODAY = 121,               // 福迪
	VLR_LOTUS = 122,               // 莲花汽车
	VLR_NANJUN = 123,               // 南骏
	VLR_SHUANGHUAN = 124,               // 双环汽车
	VLR_SAIBAO = 125,               // 哈飞赛豹
	VLR_HAWTAI = 126,               // 华泰
	VLR_LIFO = 127,               // 永源飞碟
	VLR_JONWAY = 128,               // 永源汽车
	VLR_FULONGMA = 129,               // 福龙马
	VLR_WEILI = 130,               // 潍力
	VLR_ANCHI = 131,               // 江淮安驰
	VLR_PAIXI = 132,               // 派喜
	VLR_HIGERTEXT = 133,               // 海格HIGER文字
	VLR_RIYECAR = 134,               // 广汽日野轻卡
	VLR_RIYETRUCK = 135,               // 广汽日野重卡
	VLR_JIANGNAN = 136,               // 江南
	VLR_OLDZOTYE = 137,               // 老款众泰
	VLR_OLDXIALI = 138,               // 老款夏利
	VLR_NEWAOCHI = 139,               // 新奥驰
	VLR_CDW = 140,               // 王牌重汽
	VLR_CDWTEXT = 141,               // 王牌重汽文字
	VLR_CIIMO = 142,               // 本田思铭
	VLR_CHANADS = 143,               // 长安谛艾仕
	VLR_DS = 144,               // 道奇
	VLR_ROHENS = 145,               // 现代劳恩斯酷派
	VLR_YANTAI = 146,               // 燕台
	VLR_SHUANGLONG = 147,               // 双龙
	VLR_FENGLING = 148,               // 时代风菱
	VLR_XINKAI = 149,               // 新凯
	VLR_GMC = 150,               // GMC
	VLR_DATONG = 151,               // 上汽大通
	VLR_BQYINXIANG = 152,               // 北汽银翔
	VLR_NEWCHERY = 153,               // 新奇瑞
	VLR_MUDAN = 154,               // 牡丹
	VLR_DAYUN = 155,               // 大运汽车
	VLR_DONGWO = 156,               // 东沃汽车
	VLR_UNION = 157,               // 联合汽车
	VLR_CHUNZHOU = 158,               // 春洲客车
	VLR_SANY = 159,               // 三一重工
	VLR_YAXING = 160,               // 亚星客车
	VLR_HENGTONG = 161,               // 恒通客车
	VLR_SHAOLIN = 162,               // 少林客车
	VLR_YOUNG = 163,               // 青年客车
	VLR_STOM = 164,               // 十通
	VLR_SANHUAN = 165,               // 三环
	VLR_XUGONG = 166,               // 徐工
	VLR_BEIFANG = 167,               // 北方汽车
	VLR_JIANGHUAN = 168,               // 江环货车
	VLR_BJFARM = 169,               // 北京农用
	VLR_NEWDADI = 170,               // 新大地汽车
	VLR_SUNWIN = 171,               // 申沃客车
	VLR_YINGTIAN = 172,               // 英田
	VLR_QINGQI = 173,               // 轻骑
	VLR_CHUFENG = 174,               // 楚风汽车
	VLR_SCANIA = 175,               // 斯堪尼亚
	VLR_JIULONG = 176,               // 九龙客车
	VLR_YOUYI = 177,               // 友谊客车
	VLR_SHANGRAO = 178,               // 上饶客车
	VLR_JIJIANG = 179,               // 吉江
	VLR_YANGZI = 180,               // 扬子客车
	VLR_XIWO = 181,               // 西沃客车
	VLR_CHANGJIANG = 182,               // 长江客车
	VLR_WUYI = 183,               // 武夷
	VLR_CHENGDU = 184,               // 成都客车
	VLR_TIANMA = 185,               // 天马
	VLR_BAOLONG = 186,               // 宝龙
	VLR_NEWYATU = 187,               // 新雅途
	VLR_BARUI = 188,               // 起亚霸锐
	VLR_GUANZHI = 189,               // 观致
	VLR_XIYATE = 190,               // 西雅特
	VLR_BINLI = 191,               // 宾利
	VLR_DADI = 192,               // 大迪
	VLR_FUQI = 193,               // 富奇
	VLR_HANGTIAN = 194,               // 航天汽车
	VLR_HENGTIAN = 195,               // 恒天汽车
	VLR_JMCCAR = 196,               // 江铃轻汽
	VLR_KAERSEN = 197,               // 卡尔森汽车
	VLR_KAWEI = 198,               // 卡威汽车
	VLR_LANBOJINI = 199,               // 兰博基尼
	VLR_MASHALADI = 200,               // 玛莎拉蒂
	VLR_SHUCHI = 201,               // 舒驰客车
	VLR_SHILI = 202,               // 实力客车
	VLR_HUABEI = 203,               // 中客华北
	VLR_YIZHENG = 204,               // 上汽仪征
	VLR_CHUNLAN = 205,               // 春兰汽车
	VLR_DAFA = 206,               // 大发汽车
	VLR_SHENYE = 207,               // 神野汽车
	VLR_FALALI = 208,               // 法拉利汽车
	VLR_FUXING = 209,               // 福星汽车
	VLR_ANYUAN = 210,               // 安源客车
	VLR_JINGHUA = 211,               // 京华客车
	VLR_TAIHU = 212,               // 太湖客车
	VLR_WUZHOULONG = 213,               // 五洲龙
	VLR_CHANGLONG = 214,               // 常隆客车
	VLR_YUEXI = 215,               // 悦西客车
	VLR_SHENMA = 216,               // 神马客车
	VLR_LUSHAN = 217,               // 庐山牌
	VLR_WANFENG = 218,               // 万丰牌
	VLR_GZYUNBAO = 219,               // 广州云豹
	VLR_ZHONGDA = 220,               // 中大汽车
	VLR_THREEWHEEL = 221,               // 三轮车
	VLR_TWOWHEEL = 222,               // 二轮车
	VLR_JBC = 223,              // 金杯JBC
	VLR_YZJIANG = 224,               // 扬子江客车
	VLR_CNJ = 225,               // 南骏CNJ
	VLR_FORLAND = 226,               // 福田时代文字
	VLR_FARMCAR = 227,               // 农用车
	VLR_DONGFANGHONG = 228,               // 东方红
	VLR_STEYR = 229,               // 斯太尔汽车
	VLR_HONGQI = 230,               // 红旗
	VLR_USER1 = 231,   //用户1
	VLR_USER2 = 232,   //用户2
	VLR_USER3 = 233,   //用户3
	VLR_USER4 = 234,   //用户4
	VLR_USER5 = 235,   //用户5
	VLR_USER6 = 236,   //用户6
	VLR_USER7 = 237,   //用户7
	VLR_USER8 = 238    //用户8
}VLR_VEHICLE_CLASS;

/********************车辆品牌子类型Begin*************************/
//大众子品牌类型
typedef enum _VSB_VOLKSWAGEN_CLASS
{
	VSB_VOLKSWAGEN_OTHER = 0,   // 其他（保留）
	VSB_VOLKSWAGEN_LAVIDA = 1,   // 朗逸
	VSB_VOLKSWAGEN_CROSSLAVIDA = 2,   // 朗境
	VSB_VOLKSWAGEN_TIGUAN = 3,   // 途观
	VSB_VOLKSWAGEN_TOURAN = 4,   // 途安
	VSB_VOLKSWAGEN_SANTANA = 5,   // 桑塔纳
	VSB_VOLKSWAGEN_SANTANA2000 = 6,   // 桑塔纳2000
	VSB_VOLKSWAGEN_SANTANA3000 = 7,   // 桑塔纳3000
	VSB_VOLKSWAGEN_VISTA = 8,   // 桑塔纳-志俊
	VSB_VOLKSWAGEN_PASSAT = 9,   // 帕萨特
	VSB_VOLKSWAGEN_PASSATLINGYU = 10,  // 帕萨特-领驭
	VSB_VOLKSWAGEN_POLO = 11,  // 波罗
	VSB_VOLKSWAGEN_POLOCROSS = 12,  // 波罗-运动版
	VSB_VOLKSWAGEN_POLOGTI = 13,  // 波罗-GTI
	VSB_VOLKSWAGEN_SAGITAR = 14,  // 速腾
	VSB_VOLKSWAGEN_MAGOTAN = 15,  // 迈腾
	VSB_VOLKSWAGEN_JETTA = 16,  // 捷达
	VSB_VOLKSWAGEN_BORA = 17,  // 宝来
	VSB_VOLKSWAGEN_NEWGOLF = 18,  // 新高尔夫
	VSB_VOLKSWAGEN_GOLFGTI = 19,  // 高尔夫-GTI
	VSB_VOLKSWAGEN_GOL = 20,  // 高尔
	VSB_VOLKSWAGEN_CADDY = 21,  // 开迪
	VSB_VOLKSWAGEN_PHAETON = 22,  // 辉腾
	VSB_VOLKSWAGEN_TOUREG = 23,  // 途锐
	VSB_VOLKSWAGEN_SCIROCCO = 24,  // 尚酷
	VSB_VOLKSWAGEN_BEETLE = 25,  // 甲壳虫
	VSB_VOLKSWAGEN_SHARAN = 26,  // 夏朗
	VSB_VOLKSWAGEN_MULTIVAN = 27,  // 迈特威
	VSB_VOLKSWAGEN_CARBONCOPY = 28,  // 一汽大众-CC
	VSB_VOLKSWAGEN_VISTACHANGDA = 29,  // 桑塔纳志俊-畅达
	VSB_VOLKSWAGEN_BORASPORTLINE = 30,   // 宝来-SPORTLINE
	VSR_VOLKSWAGEN_CC_1 = 31,   //大众-CC-2012,2011,2010
	VSR_VOLKSWAGEN_Cross_POLO_1 = 32,   //大众-Cross-POLO-2010,2007
	VSR_VOLKSWAGEN_Cross_POLO_2 = 33,   //大众-Cross-POLO-2014,2012
	VSR_VOLKSWAGEN_MULTIVAN_1 = 34,   //大众-Multivan-2014,2012,2011
	VSR_VOLKSWAGEN_POLO_1 = 35,   //大众-POLO-2006,2005,2004,2003,2002
	VSR_VOLKSWAGEN_POLO_2 = 36,   //大众-POLO-2013,2012,2011
	VSR_VOLKSWAGEN_POLO_JINQU_1 = 37,   //大众-POLO劲取-2009,2008,2007,2006
	VSR_VOLKSWAGEN_POLO_JINQU_2 = 38,   //大众-POLO劲取-2011
	VSR_VOLKSWAGEN_Tiguan_1 = 39,   //大众-Tiguan-2011,2009
	VSR_VOLKSWAGEN_Tiguan_2 = 40,   //大众-Tiguan-2014,2013,2012
	VSR_VOLKSWAGEN_XIALANG_1 = 41,   //大众-夏朗-2013,2012
	VSR_VOLKSWAGEN_BAOLAI_1 = 42,   //大众-宝来-2005,2004
	VSR_VOLKSWAGEN_BAOLAI_2 = 43,   //大众-宝来-2006
	VSR_VOLKSWAGEN_BAOLAI_3 = 44,   //大众-宝来-2012,2011,2010,2009,2008
	VSR_VOLKSWAGEN_BAOLAI_4 = 45,   //大众-宝来-2014,2013
	VSR_VOLKSWAGEN_SHANGKU_1 = 46,   //大众-尚酷-2014,2013
	VSR_VOLKSWAGEN_PASATE_1 = 47,   //大众-帕萨特-2003进口,2001领驭
	VSR_VOLKSWAGEN_PASATE_2 = 48,   //大众-帕萨特-2007,2006,2005领驭
	VSR_VOLKSWAGEN_PASATE_3 = 49,   //大众-帕萨特-2009,2008,2007,2005,2004,2003,2001,2000
	VSR_VOLKSWAGEN_PASATE_4 = 50,   //大众-帕萨特-2011,2009领驭
	VSR_VOLKSWAGEN_PASATE_5 = 51,   //大众-帕萨特-2014,2013,2012,2011
	VSR_VOLKSWAGEN_JIEDA_1 = 52,   //大众-捷达-2005CIF伙伴,2002
	VSR_VOLKSWAGEN_JIEDA_2 = 53,   //大众-捷达-2009,2008,2006,2005,2004
	VSR_VOLKSWAGEN_JIEDA_3 = 54,   //大众-捷达-2012,2010
	VSR_VOLKSWAGEN_JIEDA_4 = 55,   //大众-捷达-2013
	VSR_VOLKSWAGEN_LANGYI_1 = 56,   //大众-朗逸-2012,2011,2010,2009,2008
	VSR_VOLKSWAGEN_LANGYI_2 = 57,   //大众-朗逸-2013
	VSR_VOLKSWAGEN_SANGTANA_1 = 58,   //大众-桑塔纳-2007,2002,2000,1999,1995
	VSR_VOLKSWAGEN_SANGTANA_2 = 59,   //大众-桑塔纳-2014,2013
	VSR_VOLKSWAGEN_SANGTANA_3 = 60,   //大众-桑塔纳2000-2003,2001,2000,1999,1998,1996
	VSR_VOLKSWAGEN_SANGTANA_4 = 61,   //大众-桑塔纳3000-2007,2006,2005,2004,2003
	VSR_VOLKSWAGEN_SANGTANAZHIJUN_1 = 62,   //大众-桑塔纳志俊(vista)-2011,2010,2009,2008
	VSR_VOLKSWAGEN_SANGTANAZHIJUN_2 = 63,   //大众-桑塔纳志俊(vista)-2006
	VSR_VOLKSWAGEN_JIAKECHONG_1 = 64,   //大众-甲壳虫-2010,2009,2008,2007,2006,2005
	VSR_VOLKSWAGEN_JIAKECHONG_2 = 65,   //大众-甲壳虫-2014,2013
	VSR_VOLKSWAGEN_HUITENG_2 = 66,   //大众-辉腾-2010,2009,2007,2006
	VSR_VOLKSWAGEN_MAITENG_1 = 67,   //大众-迈腾-2011,2010,2009,2008,2007
	VSR_VOLKSWAGEN_MAITENG_2 = 68,   //大众-迈腾-2013,2012
	VSR_VOLKSWAGEN_TUAN_3 = 69,   //大众-途安-2006,2005,2004
	VSR_VOLKSWAGEN_TUAN_1 = 70,   //大众-途安-2010,2009,2008
	VSR_VOLKSWAGEN_TUAN_2 = 71,   //大众-途安-2013,2012,2011
	VSR_VOLKSWAGEN_TUGUAN_1 = 72,   //大众-途观-2012,2011,2010
	VSR_VOLKSWAGEN_TURUI_1 = 73,   //大众-途锐-2006,2005,2003
	VSR_VOLKSWAGEN_TURUI_2 = 74,   //大众-途锐-2014,2013,2012,2011
	VSR_VOLKSWAGEN_SUTENG_1 = 75,   //大众-速腾-2010,2009,2007,2006
	VSR_VOLKSWAGEN_SUTENG_2 = 76,   //大众-速腾-2011
	VSR_VOLKSWAGEN_SUTENG_3 = 77,   //大众-速腾-2014,2013,2012
	VSR_VOLKSWAGEN_GAOERFU_1 = 78,   //大众-高尔夫-2008,2007,2006,2005,2004,2003
	VSR_VOLKSWAGEN_GAOERFU_2 = 79,   //大众-高尔夫-2012,2011进口,2012,2011,2010
	VSR_VOLKSWAGEN_GAOERFU_3 = 80,   //大众-高尔夫GTI-2013,2012,2011,2010
	VSR_VOLKSWAGEN_LANGYI_3 = 81,   //大众-朗逸-2014
	VSR_VOLKSWAGEN_HUITENG_1 = 82   //大众-辉腾-2004
} VSB_VOLKSWAGEN_CLASS;

//别克子品牌类型
typedef enum _VBR_BUICK_CLASS
{
	VBR_BUICK_OTHER = 0,   // 其他（保留）
	VBR_BUICK_ENCORE = 1,   // 昂科拉
	VBR_BUICK_GL8 = 2,   // GL8
	VBR_BUICK_LEGAL = 3,   // 君威
	VBR_BUICK_LACROSS = 4,   // 君越
	VBR_BUICK_EXCELLE = 5,   // 凯越
	VBR_BUICK_EXCELLEGT = 6,   // 英朗GT
	VBR_BUICK_WXCELLEXT = 7,   // 英朗XT
	VBR_BUICK_ENCLAVE = 8,   // 昂科雷
	VBR_BUICK_ROYAUM = 9,   // 荣御
	VBR_BUICK_SAIL = 10,  // 别克赛欧
	VBR_BUICK_EXCELLEHRV = 11,  // 凯越HRV
	VBR_BUICK_PARKAVENUE = 12,  // 林荫大道
	VBR_BUICK_CENTURY = 13,   // 新世纪
	VBR_BUICK_GL8_1 = 14,   // 别克-GL8-2004,2003
	VBR_BUICK_GL8_2 = 15,   // 别克-GL8-2007,2006,2005
	VBR_BUICK_GL8_3 = 16,   // 别克-GL8-2010_2008_2006_2005陆尊
	VBR_BUICK_GL8_4 = 17,   // 别克-GL8-2014,2013,2012,2011
	VBR_BUICK_GL8_5 = 18,   // 别克-GL8-2014_2013_2011豪华版
	VBR_BUICK_ENCORE_1 = 19,   // 别克-昂科拉-2014,2013
	VBR_BUICK_ENCLAVE_1 = 20,   // 别克-昂科雷-2013,2010,2009
	VBR_BUICK_LEGAL_1 = 21,   // 别克-君威-2001,2000,1999
	VBR_BUICK_LEGAL_2 = 22,   // 别克-君威-2008,2006,2005,2004,2002
	VBR_BUICK_LEGAL_3 = 23,   // 别克-君威-2013,2012,2011,2010,2009
	VBR_BUICK_LEGAL_4 = 24,   // 别克-君威-2013_2012_2011运动版
	VBR_BUICK_LEGAL_5 = 25,   // 别克-君威-2014
	VBR_BUICK_LEGAL_6 = 26,   // 别克-君威-2014运动版
	VBR_BUICK_LACROSS_1 = 27,   // 别克-君越-2008,2007,2006
	VBR_BUICK_LACROSS_2 = 28,   // 别克-君越-2012,2011,2010,2009
	VBR_BUICK_LACROSS_3 = 29,   // 别克-君越-2013
	VBR_BUICK_EXCELLE_1 = 30,   // 别克-凯越-2006,2005,2004
	VBR_BUICK_EXCELLE_2 = 31,   // 别克-凯越-2008_2006_2005_2004HRV
	VBR_BUICK_EXCELLE_3 = 32,   // 别克-凯越-2011,2009,2008
	VBR_BUICK_EXCELLE_4 = 33,   // 别克-凯越-2013
	VBR_BUICK_PARKAVENUE_1 = 34,   // 别克-林荫大道-2011,2010,2009,2008,2007
	VBR_BUICK_SAIL_1 = 35,   // 别克-赛欧-2004,2003
	VBR_BUICK_EXCELLEGT_1 = 36,   // 别克-英朗GT-2013,2012,2011,2010
	VBR_BUICK_WXCELLEXT_1 = 37,   // 别克-英朗XT-2014,2013,2012,2010
	VBR_BUICK_CENTURY_1 = 38,   // 别克-新世纪-2000
	VBR_BUICK_RONGYU_1 = 39   // 别克-荣御-2005,2004
}VBR_BUICK_CLASS;

//宝马子品牌类型
typedef enum _VSB_BMW_CLASS
{
	VSB_BMW_OTHER = 0,   // 其他（保留）
	VSB_BMW_3SERIES = 1,   // 宝马3系
	VSB_BMW_5SERIES = 2,   // 宝马5系
	VSB_BMW_X1 = 3,   // 宝马X1
	VSB_BMW_1SERIES = 4,   // 宝马1系
	VSB_BMW_7SERIES = 5,   // 宝马7系
	VSB_BMW_X3 = 6,   // 宝马X3
	VSB_BMW_X5 = 7,   // 宝马X5
	VSB_BMW_X6 = 8,   // 宝马X6
	VSB_BMW_Z4 = 9,   // 宝马Z4
	VSB_BMW_MINI = 10,  // 迷你
	VSB_BMW_6SERIES = 11,   //宝马6系
	VSB_BMW_YIXI_1 = 12,     // 宝马-1系-2011,2010,2008,2007
	VSB_BMW_YIXI_2 = 13,     // 宝马-1系-2013,2012
	VSB_BMW_SANXI_1 = 14,     // 宝马-3系-2004
	VSB_BMW_SANXI_2 = 15,     // 宝马-3系-2007,2005
	VSB_BMW_SANXI_3 = 16,     // 宝马-3系-2012,2011,2010,2009
	VSB_BMW_SANXI_4 = 17,     // 宝马-3系-2014,2013
	VSB_BMW_WUXI_1 = 18,     // 宝马-5系-2010,2009,2008
	VSB_BMW_WUXI_2 = 19,     // 宝马-5系-2013,2012,2011
	VSB_BMW_LIUXI_1 = 20,     // 宝马-6系-未知
	VSB_BMW_QIXI_1 = 21,     // 宝马-7系-2011,2010,2009
	VSB_BMW_QIXI_2 = 22,     // 宝马-7系-2013
	VSB_BMW_X1_1 = 23,     // 宝马-X1-2012,2010
	VSB_BMW_X1_2 = 24,     // 宝马-X1-2014,2013
	VSB_BMW_X3_1 = 25,     // 宝马-X3-2009,2008,2006
	VSB_BMW_X3_2 = 26,     // 宝马-X3-2013,2012,2011
	VSB_BMW_X5_1 = 27,     // 宝马-X5-2010,2009,2008
	VSB_BMW_X5_2 = 28,     // 宝马-X5-2013,2012,2011
	VSB_BMW_X5_3 = 29,     // 宝马-X5-2013运动型
	VSB_BMW_X6_1 = 30,     // 宝马-X6-2013,2012,2011,2009,2008
	VSB_BMW_Z4_1 = 31     // 宝马-Z4-2004
}VSB_BMW_CLASS;

//本田子品牌类型
typedef enum _VSB_HONDA_CLASS
{
	VSB_HONDA_OTHER = 0,   // 其他（保留）
	VSB_HONDA_CRV = 1,   // 本田CR-V(思威)
	VSB_HONDA_JADE = 2,   // 杰德
	VSB_HONDA_CIVIC = 3,   // 思域
	VSB_HONDA_SPIRIOR = 4,   // 思铂睿
	VSB_HONDA_CIIMO = 5,   // 思铭
	VSB_HONDA_ELYSION = 6,   // 艾力绅
	VSB_HONDA_OBYSSEY = 7,   // 奥赛德
	VSB_HONDA_FIT = 8,   // 飞度
	VSB_HONDA_NEWCITY = 9,   // 锋范
	VSB_HONDA_CROSSTOUR = 10,  // 歌诗图
	VSB_HONDA_CRIDER = 11,  // 凌派
	VSB_HONDA_ACCORD = 12,  // 雅阁
	VSB_HONDA_CITY = 13,  // 思迪
	VSB_HONDA_ANTILOCK = 14,  // 阿柯德
	VSB_HONDA_CRZ = 15,   // 本田CR-Z
	VSB_HONDA_CRV_1 = 16,   // 本田-CR-V-2004
	VSB_HONDA_CRV_2 = 17,   // 本田-CR-V-2005
	VSB_HONDA_CRV_3 = 18,   // 本田-CR-V-2008,2007
	VSB_HONDA_CRV_4 = 19,   // 本田-CR-V-2010
	VSB_HONDA_CRV_5 = 20,   // 本田-CR-V-2013,2012
	VSB_HONDA_CRIDER_1 = 21,   // 本田-凌派-2014,2013
	VSB_HONDA_OBYSSEY_1 = 22,   // 本田-奥德赛-2002
	VSB_HONDA_OBYSSEY_2 = 23,   // 本田-奥德赛-2006,2005,2004
	VSB_HONDA_OBYSSEY_3 = 24,   // 本田-奥德赛-2008,2007
	VSB_HONDA_OBYSSEY_4 = 25,   // 本田-奥德赛-2011豪华版
	VSB_HONDA_CIVIC_1 = 26,   // 本田-思域-2007
	VSB_HONDA_CIVIC_5 = 27,   // 本田-思域-1996
	VSB_HONDA_CIVIC_2 = 28,   // 本田-思域-2008,2006
	VSB_HONDA_CIVIC_3 = 29,   // 本田-思域-2009
	VSB_HONDA_CIVIC_4 = 30,   // 本田-思域-2013,2012,2011
	VSB_HONDA_CITY_1 = 31,   // 本田-思迪-2008,2007,2006
	VSB_HONDA_SPIRIOR_1 = 32,   // 本田-思铂睿-2009
	VSB_HONDA_SIMING_1 = 33,   // 本田-思铭-2012
	VSB_HONDA_JIEDE_1 = 34,   // 本田-杰德-2013
	VSB_HONDA_CROSSTOUR_1 = 35,   // 本田-歌诗图-2013,2012,2010
	VSB_HONDA_AILISHEN_1 = 36,   // 本田-艾力绅-2012
	VSB_HONDA_NEWCITY_1 = 37,   // 本田-锋范-2009
	VSB_HONDA_NEWCITY_2 = 38,   // 本田-锋范-2011
	VSB_HONDA_NEWCITY_3 = 39,   // 本田-锋范-2014,2012
	VSB_HONDA_ACCORD_1 = 40,   // 本田-雅阁-1996
	VSB_HONDA_ACCORD_2 = 41,   // 本田-雅阁-1999
	VSB_HONDA_ACCORD_3 = 42,   // 本田-雅阁-2001
	VSB_HONDA_ACCORD_4 = 43,   // 本田-雅阁-2003
	VSB_HONDA_ACCORD_5 = 44,   // 本田-雅阁-2008
	VSB_HONDA_ACCORD_6 = 45,   // 本田-雅阁-2010
	VSB_HONDA_ACCORD_7 = 46,   // 本田-雅阁-2011
	VSB_HONDA_ACCORD_8 = 47,   // 本田-雅阁-2012
	VSB_HONDA_ACCORD_9 = 48,   // 本田-雅阁-2013
	VSB_HONDA_ACCORD_10 = 49,   // 本田-雅阁-2014
	VSB_HONDA_FIT_1 = 50,   // 本田-飞度-2004
	VSB_HONDA_FIT_2 = 51,   // 本田-飞度-2004三厢
	VSB_HONDA_FIT_3 = 52,   // 本田-飞度-2005
	VSB_HONDA_FIT_4 = 53,   // 本田-飞度-2007
	VSB_HONDA_FIT_5 = 54,   // 本田-飞度-2008
	VSB_HONDA_FIT_6 = 55   // 本田-飞度-2013,2011
}VSB_HONDA_CLASS;

//标致子品牌类型
typedef enum _VSB_PEUGEOT_CLASS
{
	VSB_PEUGEOT_OTHER = 0,   // 其他（保留）
	VSB_PEUGEOT_2008 = 1,   // 标致2008
	VSB_PEUGEOT_207 = 2,   // 标致207
	VSB_PEUGEOT_SENNA = 3,   // 赛纳
	VSB_PEUGEOT_3008 = 4,   // 标致3008
	VSB_PEUGEOT_301 = 5,   // 标致301
	VSB_PEUGEOT_307 = 6,   // 标致307
	VSB_PEUGEOT_308 = 7,   // 标致308
	VSB_PEUGEOT_408 = 8,   // 标致408
	VSB_PEUGEOT_508 = 9,   // 标致508
	VSB_PEUGEOT_206 = 10,  // 标致206
	VSB_PEUGEOT_407 = 11,   // 标致407
	VSB_PEUGEOT_206_1 = 12, // 标致-206-未知
	VSB_PEUGEOT_207_1 = 13, // 标致-207两厢-2011,2010,2009
	VSB_PEUGEOT_207_2 = 14, // 标致-207两厢-2013
	VSB_PEUGEOT_3008_1 = 15, // 标致-3008-2014,2013
	VSB_PEUGEOT_301_1 = 16, // 标致-301-未知
	VSB_PEUGEOT_307_1 = 17, // 标致-307三厢-2007,2006,2005,2004
	VSB_PEUGEOT_307_2 = 18, // 标致-307三厢-2010,2009,2008
	VSB_PEUGEOT_307_3 = 19, // 标致-307两厢-2013_2012_2011CROSS
	VSB_PEUGEOT_308_1 = 20, // 标致-308-2014,2013,2012
	VSB_PEUGEOT_407_1 = 21, // 标致-407-未知
	VSB_PEUGEOT_408_1 = 22, // 标致-408-2012,2011,2010
	VSB_PEUGEOT_408_2 = 23, // 标致-408-2013
	VSB_PEUGEOT_508_1 = 24, // 标致-508-2014,2013,2012,2011
	VSB_PEUGEOT_207_3 = 25, // 标致-207三厢-2011,2010,2009
	VSB_PEUGEOT_307_4 = 26 // 标致-307两厢-2013,2012,2010,2009,2008

}VSB_PEUGEOT_CLASS;

//丰田子品牌类型
typedef enum _VSB_TOYOTA_CLASS
{
	VSB_TOYOTA_OTHER = 0,   // 其他（保留）
	VSB_TOYOTA_HIGHLANDER = 1,   // 汉兰达
	VSB_TOYOTA_CAMRY = 2,   // 凯美瑞
	VSB_TOYOTA_YARIS = 3,   // 雅力士
	VSB_TOYOTA_YARISL = 4,   // YARIS L致炫
	VSB_TOYOTA_VERSO = 5,   // 逸致
	VSB_TOYOTA_HUAGUAN = 6,   // 花冠
	VSB_TOYOTA_CROWN = 7,   // 皇冠
	VSB_TOYOTA_COROLLA = 8,   // 卡罗拉
	VSB_TOYOTA_COSTER = 9,   // 柯斯达
	VSB_TOYOTA_PRADO = 10,  // 普拉多
	VSB_TOYOTA_PRIUS = 11,  // 普锐斯
	VSB_TOYOTA_RAV4 = 12,  // 丰田RAV4
	VSB_TOYOTA_REZI = 13,  // 锐志
	VSB_TOYOTA_VIOS = 14,  // 威驰
	VSB_TOYOTA_PREVIA = 15,  // 普瑞维亚
	VSB_TOYOTA_HIACE = 16,  // 海狮
	VSB_TOYOTA_86 = 17,  // 丰田86
	VSB_TOYOTA_SPEQUOIA = 18,  // 红杉
	VSB_TOYOTA_LANDCRUISER = 19,  // 陆地巡洋舰(兰德酷路泽)
	VSB_TOYOTA_SIENNA = 20,  // 赛纳
	VSB_TOYOTA_CAMRYHYBRID = 21,  // 凯美瑞-HYBRID
	VSB_TOYOTA_GRACE = 22,  // 阁瑞斯
	VSB_TOYOTA_ALPHARD = 23,   // 埃尔法
	VSB_TOYOTA_RAV4_1 = 24,   // 丰田-RAV4-2012手动经典版,2011,2010,2009
	VSB_TOYOTA_RAV4_2 = 25,   // 丰田-RAV4-2013
	VSB_TOYOTA_86_1 = 26,   // 丰田-丰田86-未知
	VSB_TOYOTA_JIAMEI_2 = 27,   // 丰田-佳美-2001,2000,1999,1998
	VSB_TOYOTA_JIAMEI_3 = 28,   // 丰田-佳美-2004,2003,2002
	VSB_TOYOTA_LANDEKLZ_1 = 29,   // 丰田-兰德酷路泽-2011中东版,2010,2007
	VSB_TOYOTA_KAIMEIRUI_1 = 30,   // 丰田-凯美瑞-2008,2007,2006
	VSB_TOYOTA_KAIMEIRUI_2 = 31,   // 丰田-凯美瑞-2012尊瑞
	VSB_TOYOTA_KAIMEIRUI_3 = 32,   // 丰田-凯美瑞-2012经典版,2011,2010,2009
	VSB_TOYOTA_KAIMEIRUI_4 = 33,   // 丰田-凯美瑞-2013,2012
	VSB_TOYOTA_KAIMEIRUI_5 = 34,   // 丰田-凯美瑞-2013经典版
	VSB_TOYOTA_KAIMEIRUI_6 = 35,   // 丰田-凯美瑞-2014,2012骏瑞
	VSB_TOYOTA_KALUOLA_1 = 36,   // 丰田-卡罗拉-2010,2009,2008,2007,2006
	VSB_TOYOTA_KALUOLA_2 = 37,   // 丰田-卡罗拉-2013,2012,2011
	VSB_TOYOTA_AIERFA_1 = 38,   // 丰田-埃尔法-2011,2010
	VSB_TOYOTA_AIERFA_2 = 39,   // 丰田-埃尔法-2013,2012
	VSB_TOYOTA_WEICHI_1 = 40,   // 丰田-威驰-2004,2003
	VSB_TOYOTA_WEICHI_2 = 41,   // 丰田-威驰-2007,2006,2005
	VSB_TOYOTA_WEICHI_3 = 42,   // 丰田-威驰-2009,2008
	VSB_TOYOTA_WEICHI_4 = 43,   // 丰田-威驰-2013,2012,2011,2010
	VSB_TOYOTA_WEICHI_5 = 44,   // 丰田-威驰-2014
	VSB_TOYOTA_PULADUO_1 = 45,   // 丰田-普拉多-2007,2006,2005,2004
	VSB_TOYOTA_PULADUO_2 = 46,   // 丰田-普拉多-2010
	VSB_TOYOTA_PULADUO_3 = 47,   // 丰田-普拉多-2014
	VSB_TOYOTA_PURUIWEIYA_1 = 48,   // 丰田-普瑞维亚-2004
	VSB_TOYOTA_PURUIWEIYA_4 = 49,   // 丰田-普瑞维亚-2005
	VSB_TOYOTA_PURUIWEIYA_2 = 50,   // 丰田-普瑞维亚-2006
	VSB_TOYOTA_PURUIWEIYA_3 = 51,   // 丰田-普瑞维亚-2012,2010,2008,2007
	VSB_TOYOTA_KESIDA_1 = 52,   // 丰田-柯斯达-2007
	VSB_TOYOTA_KESIDA_2 = 53,   // 丰田-柯斯达-2011
	VSB_TOYOTA_HANLANDA_1 = 54,   // 丰田-汉兰达-2011,2009
	VSB_TOYOTA_HANLANDA_2 = 55,   // 丰田-汉兰达-2012
	VSB_TOYOTA_HANLANDA_3 = 56,   // 丰田-汉兰达-2013
	VSB_TOYOTA_HAISHI_1 = 57,   // 丰田-海狮-2001
	VSB_TOYOTA_HUANGGUAN_1 = 58,   // 丰田-皇冠-1999
	VSB_TOYOTA_HUANGGUAN_2 = 59,   // 丰田-皇冠-2009,2008,2007,2006,2005
	VSB_TOYOTA_HUANGGUAN_3 = 60,   // 丰田-皇冠-2010
	VSB_TOYOTA_HUANGGUAN_4 = 61,   // 丰田-皇冠-2012,2011
	VSB_TOYOTA_HONGSHAN_1 = 62,   // 丰田-红杉-未知
	VSB_TOYOTA_HUAGUAN_1 = 63,   // 丰田-花冠-2006,2005,2004
	VSB_TOYOTA_HUAGUAN_2 = 64,   // 丰田-花冠-2009,2008,2007
	VSB_TOYOTA_HUAGUAN_3 = 65,   // 丰田-花冠-2011,2010
	VSB_TOYOTA_YIZHI_1 = 66,   // 丰田-逸致-2014,2012,2011
	VSB_TOYOTA_RUIZHI_1 = 67,   // 丰田-锐志-2006,2005
	VSB_TOYOTA_RUIZHI_2 = 68,   // 丰田-锐志-2009,2008,2007
	VSB_TOYOTA_RUIZHI_3 = 69,   // 丰田-锐志-2010风度版
	VSB_TOYOTA_RUIZHI_4 = 70,   // 丰田-锐志-2012,2010
	VSB_TOYOTA_LUDIXUNYANG_1 = 71,   // 丰田-陆地巡洋舰-未知
	VSB_TOYOTA_YALISHI_1 = 72,   // 丰田-雅力士-2009,2008,2007
	VSB_TOYOTA_YALISHI_2 = 73,   // 丰田-雅力士-2012,2011,2010
	VSB_TOYOTA_RAV4_3 = 74,   // 丰田-RAV4-2013经典,精英,尊崇,2012
	VSB_TOYOTA_YARiSL_1 = 75,   // 丰田-YARiS-L
	VSB_TOYOTA_JIAMEI_1 = 76,   // 丰田-佳美-1996
	VSB_TOYOTA_PLATZ_1 = 77,   // 丰田-PLATZ-1999
	VSB_TOYOTA_LANDEKLZ_2 = 78   // 丰田-兰德酷路泽-2014,2012中东版,2012
}VSB_TOYOTA_CLASS;

//福特子品牌类型
typedef enum _VSB_FORD_CLASS
{
	VSB_FORD_OTHER = 0,   // 其他（保留）
	VSB_FORD_FOCUS = 1,   // 福克斯
	VSB_FORD_FIESTA = 2,   // 嘉年华
	VSB_FORD_SMAX = 3,   // 麦柯斯
	VSB_FORD_MONDEO = 4,   // 蒙迪欧
	VSB_FORD_ECOSPORT = 5,   // 翼博
	VSB_FORD_ESCAPE = 6,   // 翼虎
	VSB_FORD_ZHISHENG = 7,   // 致胜
	VSB_FORD_ESCORT = 8,   // 福睿斯
	VSB_FORD_EXPLORER = 9,   // 福特探险者
	VSB_FORD_EDGE = 10,  // 锐界
	VSB_FORD_TRANSIT = 11,   // 全顺
	VSB_FORD_QUANSHUN_1 = 12,    // 福特-全顺-未知
	VSB_FORD_JIANIANHUA_1 = 13,    // 福特-嘉年华三厢-2006,2005,2004
	VSB_FORD_JIANIANHUA_2 = 14,    // 福特-嘉年华三厢-2011,2010,2009
	VSB_FORD_JIANIANHUA_3 = 15,    // 福特-嘉年华三厢-2013
	VSB_FORD_JIANIANHUA_4 = 16,    // 福特-嘉年华两厢-2012
	VSB_FORD_TANXIANZHE_1 = 17,    // 福特-探险者-2013,2011
	VSB_FORD_FOCUS_1 = 18,    // 福特-福克斯三厢-2005
	VSB_FORD_FOCUS_2 = 19,    // 福特-福克斯三厢-2005经典型
	VSB_FORD_FOCUS_3 = 20,    // 福特-福克斯三厢-2008,2007,2006
	VSB_FORD_FOCUS_4 = 21,    // 福特-福克斯三厢-2013,2012经典,2011,2009
	VSB_FORD_FOCUS_5 = 22,    // 福特-福克斯两厢-2012
	VSB_FORD_FOCUS_6 = 23,    // 福特-福克斯两厢-2012基本,时尚,2011,2010,2009,2008
	VSB_FORD_YIBO_1 = 24,    // 福特-翼博-2013
	VSB_FORD_YIHU_1 = 25,    // 福特-翼虎-2013
	VSB_FORD_MENGDIOU_1 = 26,    // 福特-蒙迪欧-2003
	VSB_FORD_MENGDIOU_2 = 27,    // 福特-蒙迪欧-2005,2004
	VSB_FORD_MENGDIOU_3 = 28,    // 福特-蒙迪欧-2006
	VSB_FORD_MENGDIOU_4 = 29,    // 福特-蒙迪欧-2013
	VSB_FORD_MENGDIOU_5 = 30,    // 福特-蒙迪欧-致胜-2010,2008,2007
	VSB_FORD_MENGDIOU_6 = 31,    // 福特-蒙迪欧-致胜-2011
	VSB_FORD_RUIJIE_1 = 32,    // 福特-锐界-2012,2011
	VSB_FORD_MAIKESI_1 = 33    // 福特-麦柯斯-2008,2007
}VSB_FORD_CLASS;

//日产子品牌类型
typedef enum _VSB_NISSAN_CLASS
{
	VSB_NISSAN_OTHER = 0,   // 其他（保留）
	VSB_NISSAN_XTRAIL = 1,   // 奇骏
	VSB_NISSAN_MURANO = 2,   // 楼兰
	VSB_NISSAN_LIVINA = 3,   // 骊威
	VSB_NISSAN_MARCH = 4,   // 玛驰
	VSB_NISSAN_TIIDA = 5,   // 骐达
	VSB_NISSAN_TEANA = 6,   // 天籁
	VSB_NISSAN_QASHQAI = 7,   // 逍客
	VSB_NISSAN_SYLPHY = 8,   // 轩逸
	VSB_NISSAN_SUNNY = 9,   // 阳光
	VSB_NISSAN_D22PICKUP = 10,  // D22皮卡
	VSB_NISSAN_D22VAN = 11,  // D22厢式车
	VSB_NISSAN_CABSTAR = 12,  // 凯普斯达
	VSB_NISSAN_HV200 = 13,  // NV200
	VSB_NISSAN_PALADIN = 14,  // 帕拉丁
	VSB_NISSAN_YIDA = 15,  // 颐达
	VSB_NISSAN_DUCK = 16,  // 公爵
	VSB_NISSAN_CEFIRO = 17,  // 风度
	VSB_NISSAN_FENGSHENBLUEBIRD = 18,  // 风神蓝鸟
	VSB_NISSAN_FENGSHENSUNNY = 19,  // 风神阳光
	VSB_NISSAN_SUCCE = 20,  // 帅客
	VSB_NISSAN_FUGA = 21,  // 风雅
	VSB_NISSAN_BLUEBIRD4 = 22,  // 蓝鸟4代
	VSB_NISSAN_VENUCIA = 23,  // 启辰
	VSB_NISSAN_QUEST = 24,  // 贵士
	VSB_NISSAN_GENISS = 25,   // 俊逸
	VSB_NISSAN_NV200_1 = 26,  // 日产-NV200-2013,2012,2011,2010
	VSB_NISSAN_TIANLAI_1 = 27,  // 日产-天籁-2005,2004
	VSB_NISSAN_TIANLAI_2 = 28,  // 日产-天籁-2007,2006
	VSB_NISSAN_TIANLAI_3 = 29,  // 日产-天籁-2010,2008
	VSB_NISSAN_TIANLAI_4 = 30,  // 日产-天籁-2012,2011
	VSB_NISSAN_TIANLAI_5 = 31,  // 日产-天籁-2012云安全版,2011公爵
	VSB_NISSAN_TIANLAI_6 = 32,  // 日产-天籁-2014,2013
	VSB_NISSAN_QIJUN_1 = 33,  // 日产-奇骏-2010,2008
	VSB_NISSAN_QIJUN_2 = 34,  // 日产-奇骏-2012,2011进口
	VSB_NISSAN_PALADING_1 = 35,  // 日产-帕拉丁-2013,2011,2006,2004
	VSB_NISSAN_LOULAN_1 = 36,  // 日产-楼兰-2013,2011
	VSB_NISSAN_LOULAN_2 = 37,  // 日产-玛驰-2010
	VSB_NISSAN_LANNIAO_1 = 38,  // 日产-蓝鸟-2002
	VSB_NISSAN_LANNIAO_2 = 39,  // 日产-蓝鸟-2003
	VSB_NISSAN_LANNIAO_3 = 40,  // 日产-蓝鸟-2004
	VSB_NISSAN_GUISHI_1 = 41,  // 日产-贵士-2005
	VSB_NISSAN_XUANYI_1 = 42,  // 日产-轩逸-2006
	VSB_NISSAN_XUANYI_2 = 43,  // 日产-轩逸-2012经典,2009,2007
	VSB_NISSAN_XUANYI_3 = 44,  // 日产-轩逸-2014,2012
	VSB_NISSAN_XIAOKE_1 = 45,  // 日产-逍客-2009,2008
	VSB_NISSAN_XIAOKE_2 = 46,  // 日产-逍客-2013,2012,2011
	VSB_NISSAN_SUNNY_3 = 47,  // 日产-阳光-2004
	VSB_NISSAN_SUNNY_1 = 48,  // 日产-阳光-2006,2005
	VSB_NISSAN_SUNNY_2 = 49,  // 日产-阳光-2012,2011
	VSB_NISSAN_YIDA_1 = 50,  // 日产-颐达-2008,2006,2005
	VSB_NISSAN_YIDA_2 = 51,  // 日产-颐达-未知
	VSB_NISSAN_FENGDU_1 = 52,  // 日产-风度-未知
	VSB_NISSAN_FENGYA_1 = 53,  // 日产-风雅-未知
	VSB_NISSAN_LIWEI_1 = 54,  // 日产-骊威-2008,2007
	VSB_NISSAN_LIWEI_2 = 55,  // 日产-骊威-2009
	VSB_NISSAN_LIWEI_3 = 56,  // 日产-骊威-2010
	VSB_NISSAN_LIWEI_4 = 57,  // 日产-骊威-2011,2010劲锐,2008炫能型
	VSB_NISSAN_JUNYI_1 = 58,  // 日产-骏逸-2006
	VSB_NISSAN_QIDA_1 = 59,  // 日产-骐达-2006,2005
	VSB_NISSAN_QIDA_2 = 60,  // 日产-骐达-2009,2008
	VSB_NISSAN_QIDA_3 = 61,  // 日产-骐达-2013,2012,2011
	VSB_NISSAN_RUIQI_1 = 62   // 日产-锐骐皮卡-2009豪华型
}VSB_NISSAN_CLASS;

//奥迪子品牌类型
typedef enum _VSB_AUDI_CLASS
{
	VSB_AUDI_OTHER = 0,   // 其他（保留）
	VSB_AUDI_A3 = 1,   // 奥迪A3
	VSB_AUDI_A4L = 2,   // 奥迪A4L
	VSB_AUDI_A6L = 3,   // 奥迪A6L
	VSB_AUDI_Q3 = 4,   // 奥迪Q3
	VSB_AUDI_Q5 = 5,   // 奥迪Q5
	VSB_AUDI_A1 = 6,   // 奥迪A1
	VSB_AUDI_A4 = 7,   // 奥迪A4
	VSB_AUDI_A5 = 8,   // 奥迪A5
	VSB_AUDI_A6 = 9,   // 奥迪A6
	VSB_AUDI_A7 = 10,  // 奥迪A7
	VSB_AUDI_A8L = 11,  // 奥迪A8L
	VSB_AUDI_Q7 = 12,  // 奥迪Q7
	VSB_AUDI_S5 = 13,  // 奥迪S5
	VSB_AUDI_TT = 14,  // 奥迪TT
	VSB_AUDI_100 = 15,  // 奥迪100
	VSB_AUDI_200 = 16,  // 奥迪200
	VSB_AUDI_S7 = 17,  // 奥迪S7
	VSB_AUDI_S8 = 18,  // 奥迪S8
	VSB_AUDI_100_1 = 19,   // 奥迪-100-未知
	VSB_AUDI_200_1 = 20,   // 奥迪-200-未知
	VSB_AUDI_A1_1 = 21,   // 奥迪-A1-2014,2013,2012
	VSB_AUDI_A3_1 = 22,   // 奥迪-A3-2013,2010舒适版
	VSB_AUDI_A3_2 = 23,   // 奥迪-A3-2013技术型,2011,2010
	VSB_AUDI_A4_1 = 24,   // 奥迪-A4-2005国产,2000进口版
	VSB_AUDI_A4_2 = 25,   // 奥迪-A4-2007,2006国产,2004进口
	VSB_AUDI_A4L_1 = 26,   // 奥迪-A4L-2013
	VSB_AUDI_A5_1 = 27,   // 奥迪-A5-2011,2010
	VSB_AUDI_A6_1 = 28,   // 奥迪-A6-1996,1995,1991
	VSB_AUDI_A6L_1 = 29,   // 奥迪-A6L-2008,2007,2006,2005
	VSB_AUDI_A6L_2 = 30,   // 奥迪-A6L-2011,2010,2009
	VSB_AUDI_A6L_3 = 31,   // 奥迪-A6L-2014,2013,2012
	VSB_AUDI_A7_1 = 32,   // 奥迪-A7-2014,2013进取型,2012,2011
	VSB_AUDI_A8L_1 = 33,   // 奥迪-A8L-2006
	VSB_AUDI_A8L_2 = 34,   // 奥迪-A8L-2009,2008
	VSB_AUDI_A8L_3 = 35,   // 奥迪-A8L-2011
	VSB_AUDI_A8L_4 = 36,   // 奥迪-A8L-2013,2012
	VSB_AUDI_Q3_1 = 37,   // 奥迪-Q3-2014,2013,2012
	VSB_AUDI_Q5_1 = 38,   // 奥迪-Q5-2012,2010运动 
	VSB_AUDI_Q5_2 = 39,   // 奥迪-Q5-2012豪华型,2010越野版
	VSB_AUDI_Q5_3 = 40,   // 奥迪-Q5-2012进取型,2011,2010,2009
	VSB_AUDI_Q5_4 = 41,   // 奥迪-Q5-2013
	VSB_AUDI_Q7_1 = 42,   // 奥迪-Q7-2007
	VSB_AUDI_Q7_2 = 43,   // 奥迪-Q7-2014,2013
	VSB_AUDI_S7_1 = 44,   // 奥迪-S7-2013
	VSB_AUDI_S8_1 = 45,   // 奥迪-S8-2013
	VSB_AUDI_TT_2 = 46,   // 奥迪-TT-2010,2008,2007
	VSB_AUDI_TT_3 = 47,   // 奥迪-TT-2012,2011
	VSB_AUDI_TT_4 = 48,   // 奥迪-TT-2013,2013,2011TTS
	VSB_AUDI_TT_1 = 49   // 奥迪-TT-2008TTS
}VSB_AUDI_CLASS;

//马自达子品牌类型
typedef enum _VSB_MAZDA_CLASS
{
	VSB_MAZDA_OTHER = 0,   // 其他（保留）
	VSB_MAZDA_CX5 = 1,   // 马自达CX5
	VSB_MAZDA_2 = 2,   // 马自达2
	VSB_MAZDA_3 = 3,   // 马自达3
	VSB_MAZDA_6 = 4,   // 马自达6
	VSB_MAZDA_8 = 5,   // 马自达8
	VSB_MAZDA_COREWING = 6,   // 睿翼
	VSB_MAZDA_CX7 = 7,   // 马自达CX7
	VSB_MAZDA_X5 = 8,   // 马自达X5
	VSB_MAZDA_5 = 9,   // 马自达5
	VSB_MAZDA_PREMACY = 10,  // 老款普力马
	VSB_MAZDA_MPV = 11,   // 马自达MPV
	VSB_MAZDA_CX5_1 = 12,   // 马自达-CX-5-2014,2013,2012进口
	VSB_MAZDA_CX7_1 = 13,   // 马自达-CX-7-2014,2013,2011,2010
	VSB_MAZDA_2_1 = 14,   // 马自达-Mazda2两厢-2011,2009,2008,2007A
	VSB_MAZDA_3_1 = 15,   // 马自达-Mazda3三厢-2004,2002
	VSB_MAZDA_3_2 = 16,   // 马自达-Mazda3三厢-2009,2007
	VSB_MAZDA_3_3 = 17,   // 马自达-Mazda3三厢-2012,2010
	VSB_MAZDA_3_4 = 18,   // 马自达-Mazda3星骋两厢-2013,2012
	VSB_MAZDA_5_1 = 19,   // 马自达-Mazda5-2010,2008,2007
	VSB_MAZDA_5_2 = 20,   // 马自达-Mazda5-2013,2012,2011
	VSB_MAZDA_6_2 = 21,   // 马自达-Mazda6-2006
	VSB_MAZDA_6_3 = 22,   // 马自达-Mazda6-2007
	VSB_MAZDA_8_1 = 23,   // 马自达-Mazda8-2013,2011,2010
	VSB_MAZDA_PREMACY_1 = 24,   // 马自达-普力马-2003
	VSB_MAZDA_PREMACY_2 = 25,   // 马自达-普力马-2006,2005,2004
	VSB_MAZDA_COREWING_1 = 26,   // 马自达-睿翼-2012,2011,2010,2009
	VSB_MAZDA_COREWING_2 = 27,   // 马自达-睿翼轿跑-2011,2010
	VSB_MAZDA_COREWING_3 = 28,   // 马自达-睿翼轿跑-2012
	VSB_MAZDA_2_2 = 29,   // 马自达-Mazda2劲翔(三厢)-2011,2010,2008
	VSB_MAZDA_6_1 = 30,   // 马自达-Mazda6-2004
	VSB_MAZDA_6_4 = 31   // 马自达-Mazda6-2014,2013,2012,2011,2010
}VSB_MAZDA_CLASS;

//雪佛兰子品牌类型
typedef enum _VSB_CHEVROLET_CLASS
{
	VSB_CHEVROLET_OTHER = 0,   // 其他（保留）
	VSB_CHEVROLET_NEWAVEO = 1,   // 爱唯欧
	VSB_CHEVROLET_EPICA = 2,   // 景程
	VSB_CHEVROLET_CRUZE = 3,   // 科鲁兹
	VSB_CHEVROLET_CAPTIVA = 4,   // 科帕奇
	VSB_CHEVROLET_MALIBU = 5,   // 迈锐宝
	VSB_CHEVROLET_SAIL = 6,   // 赛欧
	VSB_CHEVROLET_CAMARO = 7,   // 科迈罗
	VSB_CHEVROLET_LECHENG = 8,   // 乐成
	VSB_CHEVROLET_LOVA = 9,   // 乐风
	VSB_CHEVROLET_OLDAVEO = 10,  // 乐骋-老款爱唯欧
	VSB_CHEVROLET_SPARK = 11,  // 乐驰
	VSB_CHEVROLET_SAILSRV = 12,   // 赛欧SRV
	VSB_CHEVROLET_LOVA_1 = 13,   // 雪佛兰-乐风-2009,2008,2007,2006
	VSB_CHEVROLET_LOVA_2 = 14,   // 雪佛兰-乐风-2010
	VSB_CHEVROLET_SPARK_1 = 15,   // 雪佛兰-乐驰-2010,2009,2006,2005,2004
	VSB_CHEVROLET_SPARK_2 = 16,   // 雪佛兰-乐驰-2010运动款
	VSB_CHEVROLET_OLDAVEO_1 = 17,   // 雪佛兰-乐骋-2005
	VSB_CHEVROLET_OLDAVEO_2 = 18,   // 雪佛兰-乐骋-2010,2009,2008
	VSB_CHEVROLET_EPICA_1 = 19,   // 雪佛兰-景程-2005
	VSB_CHEVROLET_EPICA_3 = 20,   // 雪佛兰-景程-2012,2011,2010
	VSB_CHEVROLET_EPICA_4 = 21,   // 雪佛兰-景程-2012,2011,2010致真版
	VSB_CHEVROLET_EPICA_5 = 22,   // 雪佛兰-景程-2013
	VSB_CHEVROLET_NEWAVEO_1 = 23,   // 雪佛兰-爱唯欧三厢-2013,2012,2011
	VSB_CHEVROLET_CAPTIVA_1 = 24,   // 雪佛兰-科帕奇-2010,2008
	VSB_CHEVROLET_CAPTIVA_2 = 25,   // 雪佛兰-科帕奇-2014,2013,2012,2011
	VSB_CHEVROLET_KEMAILUO_1 = 26,   // 雪佛兰-科迈罗-2012,2011
	VSB_CHEVROLET_CRUZE_1 = 27,   // 雪佛兰-科鲁兹-2014,2013,2012,2011,2010,2009
	VSB_CHEVROLET_SAIL_1 = 28,   // 雪佛兰-赛欧三厢-2005
	VSB_CHEVROLET_SAIL_2 = 29,   // 雪佛兰-赛欧三厢-2013,2011,2010
	VSB_CHEVROLET_MALIBU_1 = 30,   // 雪佛兰-迈锐宝-2014,2013,2012
	VSB_CHEVROLET_EPICA_2 = 31   // 雪佛兰-景程-2009,2008,2007
}VSB_CHEVROLET_CLASS;

//雪铁龙子品牌类型
typedef enum _VSB_CITROEN_CLASS
{
	VSB_CITROEN_OTHER = 0,   // 其他（保留）
	VSB_CITROEN_C2 = 1,   // 雪铁龙C2
	VSB_CITROEN_C4L = 2,   // 雪铁龙C4L
	VSB_CITROEN_C5 = 3,   // 雪铁龙C5
	VSB_CITROEN_ELYSEE = 4,   // 爱丽舍三厢
	VSB_CITROEN_CQUATRELIANGXIANG = 5,   // 世嘉两厢
	VSB_CITROEN_CQUATRESANXIANG = 6,   // 世嘉三厢
	VSB_CITROEN_SAEAPICASSO = 7,   // 萨拉-毕加索
	VSB_CITROEN_PICASSO = 8,   // 毕加索
	VSB_CITROEN_CTRIOMPHE = 9,   // 凯旋
	VSB_CITROEN_XSARA = 10,  // 塞纳  
	VSB_CITROEN_SHENLONGFUKANG = 11,  // 神龙富康
	VSB_CITROEN_CHANGANDS = 12,   // 长安DS
	VSB_CITROEN_C2_1 = 13,   // 雪铁龙-C2-2012,2010,2008,2007,2006
	VSB_CITROEN_C4L_1 = 14,   // 雪铁龙-C4L-2014,2013
	VSB_CITROEN_C4PICASSO_1 = 15,   // 雪铁龙-C4毕加索-2009舒适版
	VSB_CITROEN_C5_1 = 16,   // 雪铁龙-C5-2012,2011,2010
	VSB_CITROEN_CQUATRESANXIANG_1 = 17,   // 雪铁龙-世嘉三厢-2013,2012
	VSB_CITROEN_CQUATRELIANGXIANG_1 = 18,   // 雪铁龙-世嘉两厢-2011,2010,2009,2008
	VSB_CITROEN_CTRIOMPHE_1 = 19,   // 雪铁龙-凯旋-2010,2009,2008,2006
	VSB_CITROEN_FUKANG_1 = 20,   // 雪铁龙-富康-2006,2005,2004,2003,2002
	VSB_CITROEN_ELYSEE_1 = 21,   // 雪铁龙-爱丽舍三厢-2006,2005,2004,2003,2002
	VSB_CITROEN_ELYSEE_2 = 22,   // 雪铁龙-爱丽舍三厢-2013,2012,2011,2010,2009,2008,2007
	VSB_CITROEN_SAEAPICASSO_1 = 23    // 雪铁龙-萨拉-毕加索-2014 
}VSB_CITROEN_CLASS;

//现代子品牌类型
typedef enum _VSB_HYUNDAI_CLASS
{
	VSB_HYUNDAI_OTHER = 0,   // 其他（保留）
	VSB_HYUNDAI_IX35 = 1,   // 现代IX35
	VSB_HYUNDAI_LANGDONG = 2,   // 朗动
	VSB_HYUNDAI_MOINCA = 3,   // 名驭
	VSB_HYUNDAI_SHENGDA = 4,   // 胜达
	VSB_HYUNDAI_VERNA = 5,   // 瑞纳
	VSB_HYUNDAI_RUIYI = 6,   // 瑞奕
	VSB_HYUNDAI_SONATAEIGHT = 7,   // 索纳塔八
	VSB_HYUNDAI_TUCSON = 8,   // 途胜
	VSB_HYUNDAI_YUEDONG = 9,   // 悦动
	VSB_HYUNDAI_ELANTRA = 10,  // 伊兰特
	VSB_HYUNDAI_GRANDSANTAFE = 11,  // 格锐
	VSB_HYUNDAI_COUPE = 12,  // 酷派
	VSB_HYUNDAI_MATRIX = 13,  // 美佳
	VSB_HYUNDAI_ACCENT = 14,  // 雅绅特
	VSB_HYUNDAI_IX30 = 15,  // 现代IX30
	VSB_HYUNDAI_SONATA = 16,  // 索纳塔
	VSB_HYUNDAI_REFINE = 17,  // 现代瑞风商务车
	VSB_HYUNDAI_MISTRA = 18,  // 名图
	VSB_HYUNDAI_SONATAYUFENG = 19,  // 索纳塔-御翔
	VSB_HYUNDAI_SANTAFE = 20,  // 现代圣达菲
	VSB_HYUNDAI_HUIYI = 21,   // 进口辉翼
	VSB_HYUNDAI_I30_1 = 22,   // 现代-i30-2010,2009
	VSB_HYUNDAI_IX35_1 = 23,   // 现代-ix35-2012,2011,2010
	VSB_HYUNDAI_YILANTE_1 = 24,   // 现代-伊兰特-2006,2005,2004
	VSB_HYUNDAI_YILANTE_2 = 25,   // 现代-伊兰特-2007三厢
	VSB_HYUNDAI_YILANTE_3 = 26,   // 现代-伊兰特-2011
	VSB_HYUNDAI_SHENGDA_1 = 27,   // 现代-全新胜达-2013,2012
	VSB_HYUNDAI_MINGTU_1 = 28,   // 现代-名图-2014,2013
	VSB_HYUNDAI_MINGYU_1 = 29,   // 现代-名驭-2013,2011,2009
	VSB_HYUNDAI_SHENGDAFEI_1 = 30,   // 现代-圣达菲-未知
	VSB_HYUNDAI_YUXIANG_1 = 31,   // 现代-御翔-2005舒适版
	VSB_HYUNDAI_YUXIANG_2 = 32,   // 现代-御翔-2006,2005
	VSB_HYUNDAI_YUEDONG_1 = 33,   // 现代-悦动-2010,2009,2008
	VSB_HYUNDAI_YUEDONG_2 = 34,   // 现代-悦动-2012,2011
	VSB_HYUNDAI_SHENGDA_2 = 35,   // 现代-新胜达-2009,2006
	VSB_HYUNDAI_SHENGDA_3 = 36,   // 现代-新胜达-2012,2011,2010
	VSB_HYUNDAI_LANGDONG_1 = 37,   // 现代-朗动-2013,2012
	VSB_HYUNDAI_GERUI_1 = 38,   // 现代-格锐-未知
	VSB_HYUNDAI_RUIYI_1 = 39,   // 现代-瑞奕-2014
	VSB_HYUNDAI_RUINA_1 = 40,   // 现代-瑞纳三厢-2013,2010
	VSB_HYUNDAI_RUINA_2 = 41,   // 现代-瑞纳两厢-2014,2013,2011
	VSB_HYUNDAI_RUIFENG_1 = 42,   // 现代-瑞风-未知
	VSB_HYUNDAI_SUONATA_1 = 43,   // 现代-索纳塔-2008,2007,2006,2004,2003标准型
	VSB_HYUNDAI_SUONATA_2 = 44,   // 现代-索纳塔-2010,2009,2008,2006,2004
	VSB_HYUNDAI_SOUNATA_3 = 45,   // 现代-索纳塔八-2011,2010
	VSB_HYUNDAI_WEILAKESI_1 = 46,   // 现代-维拉克斯-2012,2010,2008,2007
	VSB_HYUNDAI_MEIJIA_1 = 47,   // 现代-美佳-未知
	VSB_HYUNDAI_JINKOUHUIYI_1 = 48,   // 现代-进口辉翼-未知
	VSB_HYUNDAI_TUSHENG_1 = 49,   // 现代-途胜-2005
	VSB_HYUNDAI_TUSHENG_2 = 50,   // 现代-途胜-2011,2009,2008,2006
	VSB_HYUNDAI_TUSHENG_3 = 51,   // 现代-途胜-2013
	VSB_HYUNDAI_KUPAI_1 = 52,   // 现代-酷派-未知
	VSB_HYUNDAI_YASHENTE_1 = 53,   // 现代-雅绅特-2008,2006
	VSB_HYUNDAI_YASHENTE_2 = 54,   // 现代-雅绅特-2011
	VSB_HYUNDAI_LINGXIANG_1 = 55,   // 现代-领翔-2009,2008
	VSB_HYUNDAI_FEISI_1 = 56    // 现代-飞思-2011
}VSB_HYUNDAI_CLASS;

//奇瑞子品牌类型
typedef enum _VSB_CHERY_CLASS
{
	VSB_CHERY_OTHER = 0,   // 其他（保留）
	VSB_CHERY_A1 = 1,   // 奇瑞A1
	VSB_CHERY_A3 = 2,   // 奇瑞A3
	VSB_CHERY_EASTAR = 3,   // 东方之子
	VSB_CHERY_FULWIN = 4,   // 风云
	VSB_CHERY_QQ = 5,   // 奇瑞QQ
	VSB_CHERY_E5 = 6,   // 奇瑞E5
	VSB_CHERY_COWIN = 7,   // 旗云
	VSB_CHERY_TIGGO = 8,   // 瑞虎
	VSB_CHERY_A5 = 9,   // 奇瑞A5
	VSB_CHERY_S16 = 10,  // 奇瑞S16
	VSB_CHERY_YOUYA = 11,  // 优雅
	VSB_CHERY_V5 = 12,  // 奇瑞V5
	VSB_CHERY_E3 = 13,   // 奇瑞E3
	VSB_CHERY_A1_1 = 14,     // 奇瑞-A1-2011,2008,2007
	VSB_CHERY_A3LIANGXIANG_1 = 15,     // 奇瑞-A3两厢-2012,2010,2009
	VSB_CHERY_A5_1 = 16,     // 奇瑞-A5-2009,2007,2006
	VSB_CHERY_QQ_1 = 17,     // 奇瑞-QQ-2006,2005,2004
	VSB_CHERY_QQ_2 = 18,     // 奇瑞-QQ-2010,2007,2006
	VSB_CHERY_QQ_3 = 19,     // 奇瑞-QQ-2012,2011,2010,2009,2007
	VSB_CHERY_QQ_4 = 20,     // 奇瑞-QQ-2012运动版
	VSB_CHERY_QQ_5 = 21,     // 奇瑞-QQ-2013
	VSB_CHERY_DONGFANGZHIZI_1 = 22,     // 奇瑞-东方之子-2005,2004,2003
	VSB_CHERY_DONGFANGZHIZI_2 = 23,     // 奇瑞-东方之子-2007,2006
	VSB_CHERY_DONGFANGZHIZI_3 = 24,     // 奇瑞-东方之子CROSS-2009,2008,2007
	VSB_CHERY_YOUYA_1 = 25,     // 奇瑞-优雅-未知
	VSB_CHERY_E3_1 = 26,     // 奇瑞-奇瑞E3-2013
	VSB_CHERY_E5_1 = 27,     // 奇瑞-奇瑞E5-2014,2012,2011
	VSB_CHERY_QIYUN1_1 = 28,     // 奇瑞-旗云1-2010
	VSB_CHERY_QIYUN1_2 = 29,     // 奇瑞-旗云1-2012
	VSB_CHERY_QIYUN_1 = 30,     // 奇瑞-旗云-2004
	VSB_CHERY_QIYUN_2 = 31,     // 奇瑞-旗云-2009,2008,2007,2006
	VSB_CHERY_QIYUN2_1 = 32,     // 奇瑞-旗云2-2012
	VSB_CHERY_QIYUN2_2 = 33,     // 奇瑞-旗云2-2012豪华型,2010
	VSB_CHERY_QIYUN3_1 = 34,     // 奇瑞-旗云3-2010
	VSB_CHERY_RUIHU_1 = 35,     // 奇瑞-瑞虎-2007,2006,2005
	VSB_CHERY_RUIHU_2 = 36,     // 奇瑞-瑞虎-2009,2007
	VSB_CHERY_RUIHU_3 = 37,     // 奇瑞-瑞虎-2012,2011
	VSB_CHERY_RUIHU_4 = 38,     // 奇瑞-瑞虎-2013,2012自动DVVT豪华型
	VSB_CHERY_RUIHU_5 = 39,     // 奇瑞-瑞虎-2013精英版豪华型,2012精英版舒适型
	VSB_CHERY_FENGYUN2SANXIANG_1 = 40,     // 奇瑞-风云2三厢-2010
	VSB_CHERY_AIRUIZE7_1 = 41     // 奇瑞-艾瑞泽7-2014,2013
}VSB_CHERY_CLASS;

//起亚子品牌类型
typedef enum _VSB_KIA_CLASS
{
	VSB_KIA_OTHER = 0,   // 其他（保留）
	VSB_KIA_K2 = 1,   // 起亚K2
	VSB_KIA_K3 = 2,   // 起亚K3
	VSB_KIA_K5 = 3,   // 起亚K5
	VSB_KIA_RIO = 4,   // 锐欧
	VSB_KIA_CERATO = 5,   // 赛拉图
	VSB_KIA_SPORTAGER = 6,   // 狮跑
	VSB_KIA_SOUL = 7,   // 秀尔
	VSB_KIA_ZHIPAO = 8,   // 智跑
	VSB_KIA_CARENS = 9,   // 佳乐
	VSB_KIA_CARNIVAL = 10,  // 嘉华
	VSB_KIA_OPTIMA = 11,  // 远舰
	VSB_KIA_OPIRUS = 12,  // 欧菲莱斯
	VSB_KIA_MAXIMA = 13,  // 千里马
	VSB_KIA_FORTE = 14,  // 福瑞迪
	VSB_KIA_SORENTO = 15,  // 索兰托
	VSB_KIA_K2_1 = 16,   // 起亚-K2-2013,2012,2011
	VSB_KIA_K3_1 = 17,   // 起亚-K3-2012
	VSB_KIA_K5_1 = 18,   // 起亚-K5-2012,2011
	VSB_KIA_RUIOU_1 = 19,   // 起亚-RIO锐欧-2009,2007
	VSB_KIA_QIANLIMA_1 = 20,   // 起亚-千里马-2004
	VSB_KIA_QIANLIMA_2 = 21,   // 起亚-千里马-2006,2005
	VSB_KIA_JIAHUA_1 = 22,   // 起亚-嘉华-未知
	VSB_KIA_XINJIALE_1 = 23,   // 起亚-新佳乐-2011
	VSB_KIA_ZHIPAO_1 = 24,   // 起亚-智跑-2014,2012,2011,2010
	VSB_KIA_SHIPAO_1 = 25,  // 起亚-狮跑-2008,2007,2005
	VSB_KIA_SHIPAO_2 = 26,  // 起亚-狮跑-2011,2009
	VSB_KIA_SHIPAO_3 = 27,  // 起亚-狮跑-2012
	VSB_KIA_SHIPAO_4 = 28,  // 起亚-狮跑-2013
	VSB_KIA_FURUIDI_1 = 29,  // 起亚-福瑞迪-2012,2011,2009
	VSB_KIA_FURUIDI_2 = 30,  // 起亚-福瑞迪-2014
	VSB_KIA_XIUER_1 = 31,  // 起亚-秀尔-2012,2010
	VSB_KIA_SUOLANTUO_1 = 32,  // 起亚-索兰托-2006
	VSB_KIA_SUOLANTUO_2 = 33,  // 起亚-索兰托-2012,2010,2009
	VSB_KIA_SAILATU_1 = 34,  // 起亚-赛拉图-2006,2005
	VSB_KIA_SAILATU_2 = 35,  // 起亚-赛拉图-2007
	VSB_KIA_SAILATU_3 = 36,  // 起亚-赛拉图-2012,2010GLS
	VSB_KIA_YUANJIAN_1 = 37   // 起亚-远舰-未知
}VSB_KIA_CLASS;

//奔驰子品牌类型
typedef enum _VSB_BENZ_CLASS
{
	VSB_BENZ_OTHER = 0,   // 其他（保留）
	VSB_BENZ_C = 1,   // 奔驰C级
	VSB_BENZ_E = 2,   // 奔驰E级
	VSB_BENZ_GLK = 3,   // 奔驰GLK级
	VSB_BENZ_WEITING = 4,   // 威霆-PINYIN
	VSB_BENZ_SPRINTER = 5,   // 凌特
	VSB_BENZ_VIANO = 6,   // 唯雅诺
	VSB_BENZ_M = 7,   // 奔驰M系
	VSB_BENZ_CLK = 8,   // 奔驰CLK系
	VSB_BENZ_G = 9,   // 奔驰G系
	VSB_BENZ_GL = 10,  // 奔驰GL系
	VSB_BENZ_R = 11,  // 奔驰R系
	VSB_BENZ_S = 12,  // 奔驰S系
	VSB_BENZ_A = 13,  // 奔驰A系
	VSB_BENZ_SMART = 14,  // 斯玛特(精灵)
	VSB_BENZ_B = 15,  // 奔驰B系
	VSB_BENZ_SLK = 16,  // 奔驰SLK系
	VSB_BENZ_MB100 = 17,  // 奔驰MB100
	VSB_BENZ_VITO = 18,  // 威特
	VSB_BENZ_CLS = 19,  // 奔驰CLS系
	VSB_BENZ_SL = 20,   // 奔驰SL系
	VSB_BENZ_AJI_1 = 21,   // 奔驰-A级-2011,2009
	VSB_BENZ_AJI_2 = 22,   // 奔驰-A级-2013
	VSB_BENZ_BJI_1 = 23,   // 奔驰-B级-2010,2009
	VSB_BENZ_CJI_1 = 24,   // 奔驰-C级-2010,2008,2007时尚型
	VSB_BENZ_CJI_2 = 25,   // 奔驰-C级-2013,2011,CGI
	VSB_BENZ_CJI_3 = 26,   // 奔驰-C级-2013,2011时尚型
	VSB_BENZ_EJI_1 = 27,   // 奔驰-E级-2002
	VSB_BENZ_EJI_2 = 28,   // 奔驰-E级-2007,2006
	VSB_BENZ_EJI_3 = 29,   // 奔驰-E级-2013,2012,2011,2010,2009
	VSB_BENZ_EJI_4 = 30,   // 奔驰-E级-2013,2012,2011,2010,2009时尚型
	VSB_BENZ_GLKJI_1 = 31,   // 奔驰-GLK级-2012,2011
	VSB_BENZ_GLKJI_2 = 32,   // 奔驰-GLK级-2012,2011豪华型,2008
	VSB_BENZ_GLKJI_3 = 33,   // 奔驰-GLK级-2014,2013
	VSB_BENZ_GLJI_1 = 34,   // 奔驰-GL级-2011
	VSB_BENZ_GLJI_2 = 35,   // 奔驰-GL级-2011尊贵型,2010
	VSB_BENZ_GLJI_3 = 36,   // 奔驰-GL级-2012,2010北美版
	VSB_BENZ_GJI_1 = 37,   // 奔驰-G级-2013,2010,2009
	VSB_BENZ_MB100_1 = 38,   // 奔驰-MB100-2000
	VSB_BENZ_MLJI_1 = 39,   // 奔驰-ML级-2006,2005
	VSB_BENZ_MLJI_2 = 40,   // 奔驰-ML级-2010,2008
	VSB_BENZ_MLJI_3 = 41,   // 奔驰-ML级-2014,2012
	VSB_BENZ_RJI_1 = 42,   // 奔驰-R级-2006
	VSB_BENZ_RJI_2 = 43,   // 奔驰-R级-2007
	VSB_BENZ_RJI_3 = 44,   // 奔驰-R级-2014,2011,2010,2009
	VSB_BENZ_SLKJI_2 = 45,   // 奔驰-SLK级-2006,2004
	VSB_BENZ_SLKJI_3 = 46,   // 奔驰-SLK级-2010,2009
	VSB_BENZ_SLKJI_1 = 47,   // 奔驰-SLK级-2011
	VSB_BENZ_SJI_1 = 48,   // 奔驰-S级-2004
	VSB_BENZ_SJI_2 = 49,   // 奔驰-S级-2009_Hybrid,2008,2006
	VSB_BENZ_SJI_3 = 50,   // 奔驰-S级-2009,2008商务型
	VSB_BENZ_SJI_4 = 51,   // 奔驰-S级-2012,2011,2010
	VSB_BENZ_LINGTE_1 = 52,   // 奔驰-凌特-2013,2012,2011
	VSB_BENZ_WEIYANUO_1 = 53,   // 奔驰-唯雅诺-2010,2006,2004
	VSB_BENZ_WEIYANUO_2 = 54,   // 奔驰-唯雅诺-2014,2013,2012,2011
	VSB_BENZ_WEITING_1 = 55,   // 奔驰-威霆-2013,2011,2010
	VSB_BENZ_KECHE_1 = 56    // 奔驰-客车车型1-A款
}VSB_BENZ_CLASS;

//斯柯达子品牌类型
typedef enum _VSB_SKODA_CLASS
{
	VSB_SKODA_OTHER = 0,   // 其他（保留）
	VSB_SKODA_HAORUI = 1,   // 昊锐
	VSB_SKODA_FABIA = 2,   // 晶锐
	VSB_SKODA_OCTAVIA = 3,   // 明锐
	VSB_SKODA_SUPERB = 4,   // 速派
	VSB_SKODA_SPACEBACK = 5,   // 昕动
	VSB_SKODA_RAPID = 6,   // 昕锐
	VSB_SKODA_YETI = 7,    // 野帝
	VSB_SKODA_HAORUI_1 = 8,      // 斯柯达-昊锐-2013,2012,2010,2009
	VSB_SKODA_MINGRUI_1 = 9,      // 斯柯达-明锐-2009,2008,2007
	VSB_SKODA_MINGRUI_2 = 10,      // 斯柯达-明锐-2014,2013,2012,2011,2010
	VSB_SKODA_MINGRUI_3 = 11,      // 斯柯达-明锐RS-2010
	VSB_SKODA_XINRUI_1 = 12,      // 斯柯达-昕锐-2013乐选型
	VSB_SKODA_JINGRUI_1 = 13,      // 斯柯达-晶锐-2011,2009,2008
	VSB_SKODA_JINGRUI_2 = 14,      // 斯柯达-晶锐-2014,2013,2012
	VSB_SKODA_JINGRUI_3 = 15,      // 斯柯达-晶锐-2014,2013,2012Sport版
	VSB_SKODA_SUPAI_1 = 16,      // 斯柯达-速派-2013
	VSB_SKODA_YEDI_1 = 17      // 斯柯达-野帝-2014,2013
}VSB_SKODA_CLASS;

//东风子品牌类型
typedef enum _VSB_DONGFENG_CLASS
{
	VSB_DONGFENG_OTHER = 0,   // 其他（保留）
	VSB_DONGFENG_JOYEARX5 = 1,   // 景逸X5
	VSB_DONGFENG_LINGZHI = 2,   // 菱智
	VSB_DONGFENG_JOYEARX3 = 3,   // 景逸X3
	VSB_DONGFENG_JOYEAR = 4,   // 景逸
	VSB_DONGFENG_FENGXINGCM7 = 5,   // 风行CM7
	VSB_DONGFENG_YUFENG = 6,   // 御风
	VSB_DONGFENG_FENGSHENA60 = 7,   // 风神A60
	VSB_DONGFENG_FENGSHENS30 = 8,   // 风神S30
	VSB_DONGFENG_FENGSHENH30CROSS = 9,   // 风神H30-CROSS
	VSB_DONGFENG_PICKUP = 10,  // 东风皮卡
	VSB_DONGFENG_ZHONGXINGMIANBAOCHE = 11,  // 东风中型面包车
	VSB_DONGFENG_XIAOXINGMIANBAOCHE = 12,  // 东风小型面包车
	VSB_DONGFENG_ZHONGXINGVAN = 13,  // 东风重型货车
	VSB_DONGFENG_QINGXINGXIANGSHIVAN = 14,  // 东风轻型厢式货车
	VSB_DONGFENG_QINGZHONGXINGVAN = 15,  // 东风轻中型普通货车
	VSB_DONGFENG_FENGSHENMERCURY = 16,  // 风神水星
	VSB_DONGFENG_SUCCE = 17,  // 帅客
	VSB_DONGFENG_ODIN = 18,  // 奥丁
	VSB_DONGFENG_YUMSUN = 19,  // 御轩
	VSB_DONGFENG_RUIQI = 20,  // 锐骐
	VSB_DONGFENG_FENGGUANG = 21,  // 风光
	VBR_DONGFENG_C35_1 = 22,   // 东风-C35-2013
	VBR_DONGFENG_K07_1 = 23,   // 东风-K07-2008
	VBR_DONGFENG_K07_2 = 24,   // 东风-K07-2010,2006
	VBR_DONGFENG_V21_1 = 25,   // 东风-V21-2011
	VBR_DONGFENG_JIALONG_1 = 26,   // 东风-东风嘉龙-载货车
	VBR_DONGFENG_XKFG_1 = 27,   // 东风-东风小康风光-2013
	VBR_DONGFENG_CV03_1 = 28,   // 东风-俊风CV03-2012
	VBR_DONGFENG_KAIPUTE_1 = 29,   // 东风-凯普特-C390
	VBR_DONGFENG_DUOLIKA_1 = 30,   // 东风-多利卡-S2800
	VBR_DONGFENG_DUOLIKA_2 = 31,   // 东风-多利卡-XL中卡
	VBR_DONGFENG_DUOLIKA_3 = 32,   // 东风-多利卡-中卡
	VBR_DONGFENG_TIANJIN_1 = 33,   // 东风-天锦-4X2载货车
	VBR_DONGFENG_TIANJIN_2 = 34,   // 东风-天锦-A款
	VBR_DONGFENG_XBW_1 = 35,   // 东风-小霸王-轻卡1
	VBR_DONGFENG_XBW_2 = 36,   // 东风-小霸王-轻卡2
	VBR_DONGFENG_MENGKA_1 = 37,   // 东风-梦卡-轻卡
	VBR_DONGFENG_FURUIKA_1 = 38,   // 东风-福瑞卡-轻卡1
	VBR_DONGFENG_RUIQI_1 = 39,   // 东风-锐骐皮卡-2013,2010,2009
	VBR_DONGFENG_A60_1 = 40,   // 东风风神-A60-2014,2012
	VBR_DONGFENG_H30_1 = 41,   // 东风风神-H30-Cross-2012,2011
	VBR_DONGFENG_H30_2 = 42,   // 东风风神-H30-Cross-2014,2013
	VBR_DONGFENG_H30_3 = 43,   // 东风风神-H30-2012
	VBR_DONGFENG_JINGYI_1 = 44,   // 东风风行-景逸-2014_2012LV,2011豪华型
	VBR_DONGFENG_JINGYI_2 = 45,   // 东风风行-景逸-2014_2012XL,2011,2010,2009,2008,2007
	VBR_DONGFENG_JINGYI_3 = 46,   // 东风风行-景逸X5-2014,2013
	VBR_DONGFENG_LINGZHI_1 = 47,   // 东风风行-菱智-2004
	VBR_DONGFENG_LINGZHI_2 = 48,   // 东风风行-菱智-2011,2008,2007
	VBR_DONGFENG_LINGZHI_3 = 49,   // 东风风行-菱智-2011Q3标准型,2010Q7
	VBR_DONGFENG_LINGZHI_4 = 50,   // 东风风行-菱智-2014_2013M3
	VBR_DONGFENG_LINGZHI_5 = 51   // 东风风行-菱智-2014_2013V3,2011M3_商用版_舒适型
}VSB_DONGFENG_CLASS;

//比亚迪子品牌类型
typedef enum _VSB_BYD_CLASS
{
	VSB_BYD_OTHER = 0,   // 其他（保留）
	VSB_BYD_F0 = 1,   // 比亚迪F0
	VSB_BYD_F3 = 2,   // 比亚迪F3
	VSB_BYD_F3R = 3,   // 比亚迪F3R
	VSB_BYD_F6 = 4,   // 比亚迪F6
	VSB_BYD_G3 = 5,   // 比亚迪G3
	VSB_BYD_G3R = 6,   // 比亚迪G3R
	VSB_BYD_G6 = 7,   // 比亚迪G6
	VSB_BYD_L3 = 8,   // 比亚迪L3
	VSB_BYD_M6 = 9,   // 比亚迪M6
	VSB_BYD_S6 = 10,  // 比亚迪S6
	VSB_BYD_SURUI = 11,  // 速锐
	VSB_BYD_FOLEL = 12,  // 秦川福莱尔
	VSB_BYD_SIRUI = 13,  // 思锐
	VSB_BYD_MT5 = 14,  // 比亚迪MT5(精灵)
	VSB_BYD_F0_1 = 15,        // 比亚迪-F0-2013,2012,2011,2010,2009,2008
	VSB_BYD_F3R_1 = 16,        // 比亚迪-F3R-2011,2009,2008,2007
	VSB_BYD_F6_1 = 17,        // 比亚迪-F6-2011,2009,2008
	VSB_BYD_G3R_1 = 18,        // 比亚迪-G3R-2011
	VSB_BYD_G6_1 = 19,        // 比亚迪-G6-2013,2012,2011
	VSB_BYD_L3_1 = 20,        // 比亚迪-L3-2013,2012,2011,2010
	VSB_BYD_M6_1 = 21,        // 比亚迪-M6-2013,2011,2010
	VSB_BYD_S6_1 = 22,        // 比亚迪-S6-2014,2013,2012,2011
	VSB_BYD_FULAIER_1 = 23,        // 比亚迪-福莱尔-2005豪华型
	VSB_BYD_SURUI_1 = 24        // 比亚迪-速锐-2014,2013,2012
}VSB_BYD_CLASS;

//铃木子品牌类型
typedef enum _VSB_SUZUKI_CLASS
{
	VSB_SUZUKI_OTHER = 0,   // 其他（保留）
	VSB_SUZUKI_ALTO = 1,   // 长安奥拓
	VSB_SUZUKI_SCROSS = 2,   // 锋驭
	VSB_SUZUKI_SWIFT = 3,   // 雨燕
	VSB_SUZUKI_SX4 = 4,   // 天语
	VSB_SUZUKI_LINGYANG = 5,   // 羚羊
	VSB_SUZUKI_BEIDOUXING = 6,   // 北斗星
	VSB_SUZUKI_LIANAA6 = 7,   // 利亚纳-A6
	VSB_SUZUKI_LANDY = 8,   // 浪迪
	VSB_SUZUKI_SPLASH = 9,   // 派喜
	VSB_SUZUKI_GRANDVITARA = 10,  // 超级维特拉
	VSB_SUZUKI_JIMNY = 11,  // 吉姆尼
	VSB_SUZUKI_KAZASHI = 12,  // 凯泽西
	VSB_SUZUKI_LIANA = 13,   // 利亚纳
	VSB_SUZUKI_LIANA_1 = 14,     // 铃木-利亚纳三厢-2012,2011,2010,2008,2007,2005
	VSB_SUZUKI_LIANA_2 = 15,     // 铃木-利亚纳两厢-2013,2012,2011
	VSB_SUZUKI_BEIDOUXING_1 = 16,     // 铃木-北斗星-2012,2011,2010,2009,2008,2007,2005,2004标准型
	VSB_SUZUKI_BEIDOUXING_2 = 17,     // 铃木-北斗星-2013,2012,2011,2010,2009,2008,2007,2005,2004,2003
	VSB_SUZUKI_BEIDOUXING_3 = 18,     // 铃木-北斗星-2013,2012,2011,2010,2009,2008,2007,2005,2004,2003适用型
	VSB_SUZUKI_BEIDOUXING_4 = 19,     // 铃木-北斗星-2013X5
	VSB_SUZUKI_JIMUNI_1 = 20,     // 铃木-吉姆尼-2011,2010,2009,2007
	VSB_SUZUKI_JIMUNI_2 = 21,     // 铃木-吉姆尼-2012
	VSB_SUZUKI_SX4_1 = 22,     // 铃木-天语SX4三厢-2008,2006
	VSB_SUZUKI_SX4_2 = 23,     // 铃木-天语SX4三厢-2010,2009
	VSB_SUZUKI_SX4_3 = 24,     // 铃木-天语SX4两厢-2011A,2009,2008,2007
	VSB_SUZUKI_SX4_4 = 25,     // 铃木-天语SX4两厢-2011B
	VSB_SUZUKI_SX4_5 = 26,     // 铃木-天语SX4尚悦-2013,2012,2011
	VSB_SUZUKI_ALTO_1 = 27,     // 铃木-奥拓-2006,2001,2000,1999,1993标准型
	VSB_SUZUKI_ALTO_2 = 28,     // 铃木-奥拓-2006,2004,2001,2000,1999,1993
	VSB_SUZUKI_ALTO_3 = 29,     // 铃木-奥拓-2013
	VSB_SUZUKI_ALTO_4 = 30,     // 铃木-奥拓-2014,2012,2011,2010,2009
	VSB_SUZUKI_SPLASH_1 = 31,     // 铃木-派喜-2013,2012,2011
	VSB_SUZUKI_LANDY_1 = 32,     // 铃木-浪迪-2011,2010,2007
	VSB_SUZUKI_LINGYANG_2 = 33,     // 铃木-羚羊-2006,2004,2003
	VSB_SUZUKI_LINGYANG_3 = 34,     // 铃木-羚羊-2009,2008,2007
	VSB_SUZUKI_LINGYANG_4 = 35,     // 铃木-羚羊-2011
	VSB_SUZUKI_LINGYANG_5 = 36,     // 铃木-羚羊-2012
	VSB_SUZUKI_GRANDVITARA_1 = 37,     // 铃木-超级维特拉-2011,2008,2007,2006
	VSB_SUZUKI_FENGYU_1 = 38,     // 铃木-锋驭-2014
	VSB_SUZUKI_SWIFT_1 = 39,     // 铃木-雨燕-2011_1.3L,2009,2008,2007,2005
	VSB_SUZUKI_SWIFT_2 = 40,     // 铃木-雨燕-2012,2011
	VSB_SUZUKI_KINGCHANG_1 = 41,     // 铃木-昌铃王-2004
	VSB_SUZUKI_LINGYANG_1 = 42     // 铃木-羚羊-2002
}VSB_SUZUKI_CLASS;

//五菱子品牌类型
typedef enum _VSB_SGMW_CLASS
{
	VSB_SGMW_OTHER = 0,   // 其他（保留）
	VSB_SGMW_HONGGUANG = 1,   // 五菱宏光
	VSB_SGMW_HONGGUANGS = 2,   // 五菱宏光S
	VSB_SGMW_ZHIGUANG = 3,   // 五菱之光
	VSB_SGMW_RONGGUANGS = 4,   // 五菱荣光S
	VSB_SGMW_RONGGUANG = 5,   // 五菱荣光
	VSB_SGMW_HONGTU = 6,   // 五菱鸿途
	VSB_SGMW_XINGWANG = 7,   // 五菱兴旺
	VSB_SGMW_YANGGUANG = 8,   // 五菱扬光
	VSB_SGMW_XIAOXUANFENG = 9,   // 五菱小旋风
	VSB_SGMW_WULINGZHIGUANG_1 = 10,       // 五菱-五菱之光-2010,2009立业
	VSB_SGMW_WULINGZHIGUANG_2 = 11,       // 五菱-五菱之光-2010短车身,基本型
	VSB_SGMW_WULINGZHIGUANG_3 = 12,       // 五菱-五菱之光-2010长车身,2008厢式,2007
	VSB_SGMW_XINGWANG_1 = 13,       // 五菱-兴旺面包车-2003
	VSB_SGMW_XINGWANG_2 = 14,       // 五菱-兴旺面包车-2009标准
	VSB_SGMW_XINGWANG_3 = 15,       // 五菱-兴旺面包车-2010,2009,2007,2006,2005,2004
	VSB_SGMW_HONNGUANG_1 = 16,       // 五菱-宏光-2013,2010
	VSB_SGMW_HONNGUANG_2 = 17,       // 五菱-宏光-2014,2013S
	VSB_SGMW_XIAOXUANFENG_1 = 18,       // 五菱-小旋风-2006
	VSB_SGMW_YANGGUANG_1 = 19,       // 五菱-扬光-2006,2005,2004
	VSB_SGMW_YANGGUANG_2 = 20,       // 五菱-扬光-2008,2007
	VSB_SGMW_YANGGUANG_3 = 21,       // 五菱-扬光-2009,2006,2005手动标准型
	VSB_SGMW_RONGGUANG_1 = 22,       // 五菱-荣光面包车-2012,2011,2008基本
	VSB_SGMW_RONGGUANG_2 = 23,       // 五菱-荣光面包车-2012,2011,2008标准
	VSB_SGMW_HONGTU_1 = 24        // 五菱-鸿途-2010,2009,2008,2007
}VSB_SGMW_CLASS;

//长安子品牌类型
typedef enum _VSB_CHANA_CLASS
{
	VSB_CHANA_OTHER = 0,   // 其他（保留）
	VSB_CHANA_HONOR = 1,   // 欧诺
	VSB_CHANA_XINGKA = 2,   // 长安星卡
	VSB_CHANA_ZHIXING = 3,   // 长安之星
	VSB_CHANA_PICKUP = 4,   // 长安神骐小卡(长安皮卡)
	VSB_CHANA_ZHIXING2 = 5,   // 长安之星2代
	VSB_CHANA_TAURUS = 6,   // 金牛星
	VSB_CHANA_XINGGUANG = 7,   // 长安星光
	VSB_CHANA_BENNI = 8,   // 奔奔
	VSB_CHANA_ALSVIN = 9,   // 悦翔
	VSB_CHANA_CX20 = 10,  // 长安CX20
	VSB_CHANA_CX30 = 11,  // 长安CX30
	VSB_CHANA_EADO = 12,  // 逸动
	VSB_CHANA_ZHIXINGS460 = 13,  // 长安之星S460
	VSB_CHANA_CM8 = 14,  // 长安CM8
	VSB_CHANA_XINBAO = 15,  // 新豹
	VSB_CHANA_XUNLONG = 16,  // 勋龙
	VSB_CHANA_YUNTONG = 17,  // 运通
	VSB_CHANA_LEIMENG = 18,  // 镭蒙
	VSB_CHANA_XINGYUN = 19,  // 长安星韵
	VSB_CHANA_OULIWEI = 20,  // 欧力威
	VSB_CHANA_EADOXT = 21,   // 致尚XT
	VSB_CHANA_XINGYUN_1 = 22,      // 长安商用-星韵-2004,2003,2000
	VSB_CHANA_OULIWEI_1 = 23,      // 长安商用-欧力威-2013
	VSB_CHANA_YUNTONG_1 = 24,      // 长安商用-运通-2004
	VSB_CHANA_TAURUS_1 = 25,      // 长安商用-金牛星-2013,2012,2011,2010
	VSB_CHANA_LEIMENG_1 = 26,      // 长安商用-镭蒙-2005,2003
	VSB_CHANA_ZHIXING_1 = 27,      // 长安商用-长安之星-2010,2009
	VSB_CHANA_ZHIXING_2 = 28,      // 长安商用-长安之星-2013
	VSB_CHANA_ZHIXING_3 = 29,      // 长安商用-长安之星2-2009,2008
	VSB_CHANA_ZHIXING_4 = 30,      // 长安商用-长安之星2-2012
	VSB_CHANA_ZHIXING_5 = 31,      // 长安商用-长安之星S460-2010,2009
	VSB_CHANA_ZHIXING_6 = 32,      // 长安商用-长安之星SC6350-2003
	VSB_CHANA_PICKUP_1 = 33,      // 长安商用-长安微货神骐-2013,2012
	VSB_CHANA_XINGGUANG_1 = 34,      // 长安商用-长安星光4500-2009,2007
	VSB_CHANA_XINGGUANG_2 = 35,      // 长安商用-长安星光4500-2012
	VSB_CHANA_HONOR_1 = 36      // 长安商用-长安欧诺-2014,2012
}VSB_CHANA_CLASS;

//长安轿车子品牌类型
typedef enum _VSB_EADO_CLASS
{
	VSB_EADO_OTHER = 0,       // 其他（保留）
	VSB_EADO_CS_1 = 1,       // 长安轿车-CS35-2014,2013,2012
	VSB_EADO_CX_1 = 2,       // 长安轿车-CX20-2011
	VSB_EADO_CX_2 = 3,       // 长安轿车-CX30两厢-2010
	VSB_EADO_BENBEN_1 = 4,       // 长安轿车-奔奔-2008,2007,2006
	VSB_EADO_BENBEN_2 = 5,       // 长安轿车-奔奔-2008经典型,2007运动型
	VSB_EADO_BENBEN_3 = 6,       // 长安轿车-奔奔-2010
	VSB_EADO_BENBEN_4 = 7,       // 长安轿车-奔奔MINI-2011,2010
	VSB_EADO_BENBEN_5 = 8,       // 长安轿车-奔奔MINI-2012
	VSB_EADO_YUEXIANG_1 = 9,       // 长安轿车-悦翔-2011,2010,2009
	VSB_EADO_YUEXIANG_2 = 10,       // 长安轿车-悦翔-2012
	VSB_EADO_YUEXIANG_3 = 11,       // 长安轿车-悦翔V3-2013,2012
	VSB_EADO_YUEXIANG_4 = 12,       // 长安轿车-悦翔V5-2012
	VSB_EADO_YIDONG_1 = 13        // 长安轿车-逸动-2014,2013,2012
}VSB_EADO_CLASS;

//金杯子品牌类型
typedef enum _VSB_JINBEI_CLASS
{
	VSB_JINBEI_OTHER = 0,   // 其他（保留）
	VSB_JINBEI_GRACE = 1,   // 金杯阁瑞斯
	VSB_JINBEI_HIACE = 2,   // 金杯海狮
	VSB_JINBEI_HAIXING = 3,   // 海星
	VSB_JINBEI_BADAO = 4,   // 金杯霸道
	VSB_JINBEI_LINGQI = 5,   // 领骐
	VSB_JINBEI_JINQI = 6,   // 金骐
	VSB_JINBEI_LINGCHI = 7,   // 领驰
	VSB_JINBEI_QIYUN = 8,   // 骐运
	VSB_JINBEI_ZHISHANG_1 = 9,       // 金杯-智尚S30-2014,2013,2012
	VSB_JINBEI_HAIXING_1 = 10,       // 金杯-海星-2012
	VSB_JINBEI_HAIXING_2 = 11,       // 金杯-海星-2012A7特惠型,2011
	VSB_JINBEI_HIACE_1 = 12,       // 金杯-海狮-2008
	VSB_JINBEI_HIACE_2 = 13,       // 金杯-海狮-2013,2011,2010
	VSB_JINBEI_HIACE_3 = 14,       // 金杯-海狮-2013豪华型,2011汽油,2008标准型
	VSB_JINBEI_JINDIAN_1 = 15,       // 金杯-金典-2009
	VSB_JINBEI_GRACE_1 = 16,       // 金杯-阁瑞斯MPV-2011,2008,2007
	VSB_JINBEI_GRACE_2 = 17,       // 金杯-阁瑞斯MPV-2011御领豪华型,2010,2009,2007标准9座
	VSB_JINBEI_BADAO_1 = 18       // 金杯-霸道SUV-2011,2008 

}VSB_JINBEI_CLASS;

//吉利子品牌类型
typedef enum _VSB_GEELY_CLASS
{
	VSB_GEELY_OTHER = 0,   // 其他（保留）
	VSB_GEELY_EC7 = 1,   // 吉利帝豪EC7
	VSB_GEELY_EC8 = 2,   // 吉利帝豪EC8                                                          
	VSB_GEELY_SC3 = 3,   // 吉利SC3
	VSB_GEELY_SC5RV = 4,   // 吉利SC5-RV
	VSB_GEELY_SC6 = 5,   // 吉利SC6
	VSB_GEELY_JINGYING = 6,   // 金鹰
	VSB_GEELY_JINGGANG = 7,   // 金刚
	VSB_GEELY_SX7 = 8,   // 吉利SX7
	VSB_GEELY_HAOQING = 9,   // 豪情
	VSB_GEELY_MEIRI = 10,  // 美日
	VSB_GEELY_YINGLUNSC7 = 11,  // 英伦SC7
	VSB_GEELY_PANDA = 12,  // 熊猫
	VSB_GEELY_YUANJING = 13,  // 远景
	VSB_GEELY_ZIYOUJIAN = 14   // 自由舰
}VSB_GEELY_CLASS;

//三菱子品牌类型
typedef enum _VSB_MITSUBISHI_CLASS
{
	VSB_MITSUBISHI_OTHER = 0,   // 其他（保留）
	VSB_MITSUBISHI_GALANT = 1,   // 戈蓝
	VSB_MITSUBISHI_ZINGER = 2,   // 君阁
	VSB_MITSUBISHI_LANCER = 3,   // 蓝瑟
	VSB_MITSUBISHI_LANCEREX = 4,   // 翼神
	VSB_MITSUBISHI_PAJERO = 5,   // 帕杰罗
	VSB_MITSUBISHI_PAJEROSPORT = 6,   // 帕杰罗-劲畅
	VSB_MITSUBISHI_JINGXUANASX = 7,   // 劲炫ASX
	VSB_MITSUBISHI_GRANDIS = 8,   // 三菱格蓝迪
	VSB_MITSUBISHI_OUTLANDER = 9,   // 欧蓝德
	VSB_MITSUBISHI_QINXINGYUEYE = 10,  // 三菱轻型越野
	VSB_MITSUBISHI_GTO = 11,  // 三菱GTO
	VSB_MITSUBISHI_SOVERAN = 12,  // 三菱菱绅
	VSB_MITSUBISHI_LIONVEL = 13,  // 三菱菱悦
	VSB_MITSUBISHI_HAFEISIMBO = 14,   // 哈飞赛马
	VSB_MITSUBISHI_LANCEREX_1 = 15,   // 三菱-三菱翼神-2012,2011,2010
	VSB_MITSUBISHI_JINGXUAN_1 = 16,   // 三菱-劲炫-2012,2011
	VSB_MITSUBISHI_ZINGER_1 = 17,   // 三菱-君阁-2011,2009
	VSB_MITSUBISHI_PAJERO_1 = 18,   // 三菱-帕杰罗-2004国产
	VSB_MITSUBISHI_PAJERO_2 = 19,   // 三菱-帕杰罗-2004进口
	VSB_MITSUBISHI_PAJERO_3 = 20,   // 三菱-帕杰罗-2010进口
	VSB_MITSUBISHI_PAJEROSPORT_1 = 21,   // 三菱-帕杰罗劲畅-2011
	VSB_MITSUBISHI_GALANT_1 = 22,   // 三菱-戈蓝-2009
	VSB_MITSUBISHI_GALANDI_1 = 23,   // 三菱-格蓝迪-2007
	VSB_MITSUBISHI_GALANDI_2 = 24,   // 三菱-格蓝迪-2010
	VSB_MITSUBISHI_OUTLANDER_1 = 25,   // 三菱-欧蓝德-2012,2011,2010
	VSB_MITSUBISHI_OUTLANDER_2 = 26,   // 三菱-欧蓝德-2013
	VSB_MITSUBISHI_LINGYUE_1 = 27,   // 三菱-菱悦-未知
	VSB_MITSUBISHI_LANCER_1 = 28   // 三菱-蓝瑟-2010
}VSB_MITSUBISHI_CLASS;

//雷克萨斯子品牌类型
typedef enum _VSB_LEXUS_CLASS
{
	VSB_LEXUS_OTHER = 0,   // 其他（保留）
	VSB_LEXUS_ES = 1,   // 雷克萨斯ES
	VSB_LEXUS_CT = 2,   // 雷克萨斯CT                                                          
	VSB_LEXUS_RX = 3,   // 雷克萨斯RX
	VSB_LEXUS_IS = 4,   // 雷克萨斯IS
	VSB_LEXUS_LX = 5,   // 雷克萨斯LX
	VSB_LEXUS_GS = 6,   // 雷克萨斯GS
	VSB_LEXUS_GX = 7,   // 雷克萨斯GX
	VSB_LEXUS_LS = 8,    // 雷克萨斯LS
	VSB_LEXUS_CT_1 = 9,   // 雷克萨斯-CT-2013,2012,2011
	VSB_LEXUS_ES_1 = 10,   // 雷克萨斯-ES-1994
	VSB_LEXUS_ES_2 = 11,   // 雷克萨斯-ES-2010,2009,2006
	VSB_LEXUS_ES_3 = 12,   // 雷克萨斯-ES-2013,2012
	VSB_LEXUS_GS_1 = 13,   // 雷克萨斯-GS-2011,2010,2009,2008,2005
	VSB_LEXUS_GX_1 = 14,   // 雷克萨斯-GX-2012,2010
	VSB_LEXUS_IS_1 = 15,   // 雷克萨斯-IS-2011
	VSB_LEXUS_LS_1 = 16,   // 雷克萨斯-LS-1994
	VSB_LEXUS_LS_2 = 17,   // 雷克萨斯-LS-2005,2004
	VSB_LEXUS_LS_3 = 18,   // 雷克萨斯-LS-2009,2007,2006
	VSB_LEXUS_LX_1 = 19,   // 雷克萨斯-LX-2013,2012
	VSB_LEXUS_RX_1 = 20,   // 雷克萨斯-RX-2011,2010,2009
	VSB_LEXUS_RX_2 = 21,   // 雷克萨斯-RX-2013,2012
	VSB_LEXUS_RX_3 = 22   // 雷克萨斯-RX-2007
}VSB_LEXUS_CLASS;

//荣威子品牌类型
typedef enum _VSB_ROEWE_CLASS
{
	VSB_ROEWE_OTHER = 0,   // 其他（保留）
	VSB_ROEWE_350 = 1,   // 荣威350
	VSB_ROEWE_550 = 2,   // 荣威550                                                          
	VSB_ROEWE_W5 = 3,   // 荣威W5
	VSB_ROEWE_950 = 4,   // 荣威950
	VSB_ROEWE_750 = 5,   // 荣威750
	VSB_ROEWE_350_1 = 6,   // 荣威-350-2011迅智版,2010
	VSB_ROEWE_350_2 = 7,   // 荣威-350-2014,2013,2012,2011
	VSB_ROEWE_550_1 = 8,   // 荣威-550-2012,2010,2009,2008
	VSB_ROEWE_750_1 = 9,   // 荣威-750-2009,2008,2007,2006
	VSB_ROEWE_750_2 = 10,  // 荣威-750-2012,2011
	VSB_ROEWE_950_1 = 11   // 荣威-950-2012
}VSB_ROEWE_CLASS;


//海马子品牌类型
typedef enum _VSB_HAIMA_CLASS
{
	VSB_HAIMA_OTHER = 0,   // 其他（保留）
	VSB_HAIMA_PREMARIN = 1,   // 普力马
	VSB_HAIMA_S7 = 2,   // 海马S7
	VSB_HAIMA_PRINCE = 3,   // 海马王子
	VSB_HAIMA_CUPID = 4,   // 海马2-丘比特
	VSB_HAIMA_HATCHBACK = 5,   // 海马3-欢动
	VSB_HAIMA_KNIGHT = 6,   // 骑士
	VSB_HAIMA_HAPPIN = 7,   // 海福星
	VSB_HAIMA_FAMILY = 8,   // 福美来
	VSB_HAIMA_M3 = 9,    // 海马M3
	VSB_HAIMA_CUPID_1 = 10,   // 海马-丘比特-2012,2011,2010
	VSB_HAIMA_PREMARIN_1 = 11,   // 海马-普力马-2007
	VSB_HAIMA_PREMARIN_2 = 12,   // 海马-普力马-2012,2010
	VSB_HAIMA_HATCHBACK_1 = 13,   // 海马-欢动-2010,2009
	VSB_HAIMA_HAPPIN_1 = 14,   // 海马-海福星-2010,2009,2008,2007,2004
	VSB_HAIMA_HAPPIN_2 = 15,   // 海马-海福星-2012,2011
	VSB_HAIMA_M3_1 = 16,   // 海马-海马3-2010,2008,2007
	VSB_HAIMA_FAMILY_1 = 17,   // 海马-福美来-2007,2006
	VSB_HAIMA_FAMILY_2 = 18,   // 海马-福美来-2010,2009,2008
	VSB_HAIMA_FAMILY_3 = 19,   // 海马-福美来-2011
	VSB_HAIMA_FAMILY_4 = 20,   // 海马-福美来-2014,2013,2012
	VSB_HAIMA_KNIGHT_1 = 21,   // 海马-骑士-2013_2012A,2011,2010
	VSB_HAIMA_KNIGHT_2 = 22,   // 海马-骑士-2013_2012B
	VSB_HAIMA_NEWHONGDA_1 = 23,   // 海马商用车-新鸿达-2009
	VSB_HAIMA_NEWHONDGA_2 = 24,   // 海马商用车-新鸿达-2012
	VSB_HAIMA_PRINCE_1 = 25,   // 海马商用车-海马王子-2010
	VSB_HAIMA_RONGDA_1 = 26   // 海马商用车-荣达-2012

}VSB_HAIMA_CLASS;

//长城子品牌类型
typedef enum _VSB_GREATWALL_CLASS
{
	VSB_GREATWALL_OTHER = 0,   // 其他（保留）
	VSB_GREATWALL_SING = 1,   // 赛影
	VSB_GREATWALL_SAIJUN = 2,   // 赛骏
	VSB_GREATWALL_HAVAL = 3,   // 哈弗
	VSB_GREATWALL_SAFE = 4,   // 赛弗
	VSB_GREATWALL_SAIKU = 5,   // 赛酷
	VSB_GREATWALL_SAILING = 6,   // 赛铃
	VSB_GREATWALL_KINGDEER = 7,   // 金迪尔
	VSB_GREATWALL_DEER = 8,   // 迪尔
	VSB_GREATWALL_WINGLE = 9,   // 风骏
	VSB_GREATWALL_COOLBEAR = 10,  // 酷熊
	VSB_GREATWALL_LINGAO = 11,  // 凌傲
	VSB_GREATWALL_CROSS = 12,  // 炫丽
	VSB_GREATWALL_GWPERI = 13,  // 精灵
	VSB_GREATWALL_COWRY = 14,  // 腾翼
	VSB_GREATWALL_M4 = 15,   // 长城M4
	VSB_GREATWALL_LINGAO_1 = 16,   // 长城-凌傲-2010
	VSB_GREATWALL_HAVAL_1 = 17,   // 长城-哈弗H3-2010,2009
	VSB_GREATWALL_HAVAL_2 = 18,   // 长城-哈弗H3-2012,2010,2009锐意版
	VSB_GREATWALL_HAVAL_3 = 19,   // 长城-哈弗H5-2012,2011,2010
	VSB_GREATWALL_HAVAL_4 = 20,   // 长城-哈弗H5-2012,2011,2010绿静豪华型
	VSB_GREATWALL_HAVAL_5 = 21,   // 长城-哈弗H5-2012舒适型
	VSB_GREATWALL_HAVAL_6 = 22,   // 长城-哈弗H5-2014,2013
	VSB_GREATWALL_HAVAL_8 = 23,   // 长城-哈弗H6-2014,2013升级版
	VSB_GREATWALL_HAVAL_9 = 24,   // 长城-哈弗M2-2010
	VSB_GREATWALL_HAVAL_10 = 25,   // 长城-哈弗M2-2013,2012
	VSB_GREATWALL_HAVAL_11 = 26,   // 长城-哈弗M4-2012
	VSB_GREATWALL_HAVAL_12 = 27,   // 长城-哈弗派-2011
	VSB_GREATWALL_CROSS_1 = 28,   // 长城-炫丽-2009,2008
	VSB_GREATWALL_CROSS_2 = 29,   // 长城-炫丽CROSS-2011,2009
	VSB_GREATWALL_JINGLING_1 = 30,   // 长城-精灵-未知
	VSB_GREATWALL_SING_1 = 31,   // 长城-赛影-2003
	VSB_GREATWALL_SAIKU_1 = 32,   // 长城-赛酷-2004
	VSB_GREATWALL_SAILING_1 = 33,   // 长城-赛铃-未知
	VSB_GREATWALL_DIER_1 = 34,   // 长城-迪尔-未知
	VSB_GREATWALL_COOLBEAR_1 = 35,   // 长城-酷熊-2010,2009
	VSB_GREATWALL_KINGDEER_1 = 36,   // 长城-金迪尔-2008,2007,2004,2003
	VSB_GREATWALL_GREATWALL_1 = 37,   // 长城-长城C20R-2013,2011
	VSB_GREATWALL_GREATWALL_2 = 38,   // 长城-长城C30-2010
	VSB_GREATWALL_GREATWALL_3 = 39,   // 长城-长城C30-2012
	VSB_GREATWALL_GREATWALL_4 = 40,   // 长城-长城C30-2013
	VSB_GREATWALL_GREATWALL_5 = 41,   // 长城-长城C50-2013,2012
	VSB_GREATWALL_GREATWALL_6 = 42,   // 长城-长城V80-2013,2012,2010,2009,2008
	VSB_GREATWALL_WINGLE_1 = 43,   // 长城-风骏3-2011,2010,2007,2006
	VSB_GREATWALL_WINGLE_2 = 44,   // 长城-风骏5-2014,2012,2011,2009 
	VSB_GREATWALL_HAVAL_7 = 45   // 长城-哈弗H6-2013,2012,2011
}VSB_GREATWALL_CLASS;

//道奇子品牌类型
typedef enum _VSB_DS_CLASS
{
	VSB_DS_OTHER = 0,          // 其他（保留）
	VSB_DS_KUBO_1 = 1,          // 道奇-酷搏-2011,2010,2009,2008
	VSB_DS_KUWEI_1 = 2,          // 道奇-酷威-2011,2010,2009
	VSB_DS_KUWEI_2 = 3           // 道奇-酷威-2013
}VSB_DS_CLASS;

//路虎子品牌类型
typedef enum _VSB_LANDROVER_CLASS
{
	VSB_LANDROVER_OTHER = 0,   // 其他（保留）
	VSB_LANDROVER_FAXIAN_1 = 1,   // 路虎-发现-2005,2004
	VSB_LANDROVER_FAXIAN_2 = 2,   // 路虎-发现-2013,2011,2010
	VSB_LANDROVER_LANSHENG_1 = 3,   // 路虎-揽胜-2012,2011,2010
	VSB_LANDROVER_LANSHENG_2 = 4,   // 路虎-揽胜极光-2014,2013,2012,2011
	VSB_LANDROVER_LANSHENG_3 = 5,   // 路虎-揽胜运动版-2013,2012,2011,2010
	VSB_LANDROVER_LANSHENG_4 = 6,   // 路虎-揽胜运动版-2013驭红限量版
	VSB_LANDROVER_SXZ_1 = 7   // 路虎-神行者2代-2014,2013,2011
}VSB_LANDROVER_CLASS;

//名爵子品牌类型
typedef enum _VSB_MG_CLASS
{
	VSB_MG_OTHER = 0,  // 其他（保留）
	VSB_MG_3SW_1 = 1,  // MG-MG-3SW-2009,2008
	VSB_MG_MG3_1 = 2,  // MG-MG3-2013,2012,2011
	VSB_MG_MG5_1 = 3,  // MG-MG5-2014,2013,2012
	VSB_MG_MG6_1 = 4,  // MG-MG6三厢-2012,2011
	VSB_MG_MG7_1 = 5,  // MG-MG7-2010,2009,2008,2007
}VSB_MG_CLASS;

//一汽子品牌类型
typedef enum _VSB_FAW_CLASS
{
	VSB_FAW_OTHER = 0,    // 其他（保留）
	VSB_FAW_501_1 = 1,    //一汽-501-轻卡
	VSB_FAW_N3_1 = 2,    //一汽-N3+两厢-2006
	VSB_FAW_N3_2 = 3,    //一汽-N3+两厢-2008
	VSB_FAW_JIABAO_1 = 4,    //一汽-佳宝货车-2011T50,T57
	VSB_FAW_JIABAO_2 = 5,    //一汽-佳宝面包车-2000
	VSB_FAW_JIABAO_3 = 6,    //一汽-佳宝面包车-2006
	VSB_FAW_JIABAO_4 = 7,    //一汽-佳宝面包车-2012,2011V50舒适版
	VSB_FAW_JIABAO_5 = 8,    //一汽-佳宝面包车-2012,2011V70
	VSB_FAW_JIABAO_6 = 9,    //一汽-佳宝面包车-2013,2012,2011V52实用型
	VSB_FAW_JIABAO_7 = 10,    //一汽-佳宝面包车-2014,2013V80
	VSB_FAW_XIALI_1 = 11,    //一汽-夏利-1999,1997
	VSB_FAW_XIALI_2 = 12,    //一汽-夏利2000-2003,2002
	VSB_FAW_XIALI_3 = 13,    //一汽-夏利A+-2011,2010,2006,2005
	VSB_FAW_XIALI_4 = 14,    //一汽-夏利N3-2012
	VSB_FAW_XIALI_5 = 15,    //一汽-夏利N5-2014,2013,2011,2010,2009
	VSB_FAW_XIALI_6 = 16,    //一汽-夏利N7-2013
	VSB_FAW_AOWEI_1 = 17,    //一汽-奥威J5P-2005,2004,2003
	VSB_FAW_AOWEI_2 = 18,    //一汽-奥威J5P-4X2复合型牵引车,自卸车
	VSB_FAW_AOWEI_3 = 19,    //一汽-奥威J5P-4X2牵引车,卸货车
	VSB_FAW_AOWEI_4 = 20,    //一汽-奥威J5P-6X6越野自卸车
	VSB_FAW_AOXING_1 = 21,    //一汽-奥星-2004
	VSB_FAW_WEILE_1 = 22,    //一汽-威乐-2004
	VSB_FAW_WEILE_2 = 23,    //一汽-威乐-2008,2007
	VSB_FAW_WEIZI_1 = 24,    //一汽-威姿-2004
	VSB_FAW_WEIZHI_1 = 25,    //一汽-威志V2-2012手动CROSS
	VSB_FAW_WEIZHI_2 = 26,    //一汽-威志V2-2012自动CROSS,2010
	VSB_FAW_WEIZHI_3 = 27,    //一汽-威志V5-2013,2012
	VSB_FAW_WEIZHI_4 = 28,    //一汽-威志三厢-2009,2008,2007
	VSB_FAW_WEIZHI_5 = 29,    //一汽-威志三厢-2011
	VSB_FAW_XIAOJIEFANG_1 = 30,    //一汽-小解放-90,109马力轻卡
	VSB_FAW_HANWEI_1 = 31,    //一汽-悍威J5M-4X4载货车
	VSB_FAW_HANWEI_2 = 32,    //一汽-悍威J5M-6X6牵引车,6X4自卸车
	VSB_FAW_HANWEI_3 = 33,    //一汽-悍威J5M-8X8自卸车
	VSB_FAW_XINDAWEI_1 = 34,    //一汽-新大威-2010
	VSB_FAW_XINHANWEI_1 = 35,    //一汽-新悍威-2011
	VSB_FAW_SENYA_1 = 36,    //一汽-森雅M80-2012,2011,2009
	VSB_FAW_TENGWEI_1 = 37,    //一汽-腾威L5M-重卡
	VSB_FAW_JIEFANG_1 = 38,    //一汽-解放J4R-A款
	VSB_FAW_JIEFANG_2 = 39,    //一汽-解放J4R-自卸车,牵引车
	VSB_FAW_JIEFANG_3 = 40,    //一汽-解放J6-2004
	VSB_FAW_JIEFANG_4 = 41,    //一汽-解放J6-重卡
	VSB_FAW_JIEFANG_5 = 42,    //一汽-解放J6L-中卡
	VSB_FAW_JIEFANG_6 = 43,    //一汽-解放L5-A款
	VSB_FAW_SAILONG_1 = 44,    //一汽-赛龙-中卡
	VSB_FAW_JUNWEI_1 = 45,    //一汽-骏威J5K-中卡
	VSB_FAW_B50_1 = 46,    //一汽-奔腾B50-2012,2011,2009
	VSB_FAW_B50_2 = 47    //一汽-奔腾B50-2013
}VSB_FAW_CLASS;


//上汽子品牌类型
typedef enum _VSB_SAICMOTOR_CLASS
{
	VSB_SAICMOTOR_OTHER = 0,    // 其他（保留）
	VSB_HONGYAN_JIESHI_1 = 1,    // 上汽依维柯红岩-杰狮-2012
	VSB_DATONG_V80_1 = 2     // 上汽大通-V80-2014,2013,2012,2011
}VSB_SAICMOTOR_CLASS;

//东南汽车子品牌类型
typedef enum _VSB_SOUEAST_CLASS
{
	VSB_SOUEAST_OTHER = 0,    // 其他（保留）
	VSB_SOUEAST_V3_1 = 1,    // 东南-V3菱悦-2011超值幸福版,2010,2009,2008
	VSB_SOUEAST_V3_2 = 2,    // 东南-V3菱悦-2012
	VSB_SOUEAST_V3_3 = 3,    // 东南-V3菱悦-2012旗舰版,2011,2010新风采版
	VSB_SOUEAST_V3_4 = 4,    // 东南-V3菱悦-2012风采版
	VSB_SOUEAST_V5_1 = 5,    // 东南-V5菱致-2014,2013,2012
	VSB_SOUEAST_XIWANG_1 = 6,    // 东南-希旺-2011,2010
	VSB_SOUEAST_DELIKA_1 = 7,    // 东南-得利卡-2003,2002
	VSB_SOUEAST_DELIKA_2 = 8,    // 东南-得利卡-2005
	VSB_SOUEAST_DELIKA_3 = 9,    // 东南-得利卡-2008
	VSB_SOUEAST_DELIKA_4 = 10,    // 东南-得利卡-2009
	VSB_SOUEAST_LINGSHUAI_1 = 11,    // 东南-菱帅-2005,2004GLXi
	VSB_SOUEAST_FULIKA_1 = 12,    // 东南-富利卡-2005
	VSB_SOUEAST_FULIKA_2 = 13    // 东南-富利卡-2007
}VSB_SOUEAST_CLASS;


//中兴汽车子品牌类型
typedef enum _VSB_ZTE_CLASS
{
	VSB_ZTE_OTHER = 0,        // 其他（保留）
	VSB_ZTE_WEIHU_1 = 1,        // 中兴-威虎-2012,2010
	VSB_ZTE_WEIHU_2 = 2,        // 中兴-威虎TUV-2010,2006
	VSB_ZTE_WUXIAN_1 = 3,        // 中兴-无限-2008
	VSB_ZTE_WUXIAN_2 = 4         // 中兴-无限-2012,2011,2010,2009
}VSB_ZTE_CLASS;


//中华汽车子品牌类型
typedef enum _VSB_ZHONGHUA_CLASS
{
	VSB_ZHONGHUA_OTHER = 0,    // 其他（保留）
	VSB_ZHONGHUA_H230_1 = 1,   // 中华-H230-2012
	VSB_ZHONGHUA_H320_1 = 2,   // 中华-H320-2012
	VSB_ZHONGHUA_H330_1 = 3,   // 中华-H330-2013
	VSB_ZHONGHUA_H530_1 = 4,   // 中华-H530-2012,2011
	VSB_ZHONGHUA_V5_1 = 5,   // 中华-V5-2012,2011
	VSB_ZHONGHUA_ZUNCHI_1 = 6,   // 中华-尊驰-2004
	VSB_ZHONGHUA_ZUNCHI_2 = 7,   // 中华-尊驰-2005,2003
	VSB_ZHONGHUA_KUBAO_1 = 8,   // 中华-酷宝-2007
	VSB_ZHONGHUA_JUNJIE_1 = 9,   // 中华-骏捷-2010,2009,2008,2007,2006
	VSB_ZHONGHUA_JUNJIE_2 = 10,   // 中华-骏捷-2012,2011
	VSB_ZHONGHUA_JUNJIECROSS_1 = 11,   // 中华-骏捷cross-2010,2009
	VSB_ZHONGHUA_JUNJIEFRV_1 = 12,   // 中华-骏捷FRV-2009,2008
	VSB_ZHONGHUA_JUNJIEFRV_2 = 13,   // 中华-骏捷FRV-2010
	VSB_ZHONGHUA_JUNJIEFSV_1 = 14,   // 中华-骏捷FSV-2009
	VSB_ZHONGHUA_JUNJIEFSV_2 = 15,   // 中华-骏捷FSV-2010
	VSB_ZHONGHUA_JUNJIEFSV_3 = 16   // 中华-骏捷FSV-2011
}VSB_ZHONGHUA_CLASS;


//中国重汽子品牌类型
typedef enum _VSB_CNHTC_CLASS
{
	VSB_CNHTC_OTHER = 0,    // 其他（保留）
	VSB_CNHTC_HOKA_2 = 1,      // 中国重汽-HOKA-牵引车,自卸车
	VSB_CNHTC_HOWO_1 = 2,      // 中国重汽-HOWO-A7
	VSB_CNHTC_HOWO_2 = 3,      // 中国重汽-HOWO-T7H
	VSB_CNHTC_HOWO_3 = 4,      // 中国重汽-HOWO-轻卡
	VSB_CNHTC_HOWO_4 = 5,      // 中国重汽-HOWO重卡-牵引车
	VSB_CNHTC_HOWO_5 = 6,      // 中国重汽-HOWO重卡-自卸车A
	VSB_CNHTC_HOWO_6 = 7,      // 中国重汽-HOWO重卡-自卸车B
	VSB_CNHTC_HOWO_7 = 8,      // 中国重汽-HOWO重卡-载货车A
	VSB_CNHTC_HOWO_8 = 9,      // 中国重汽-HOWO重卡-载货车C
	VSB_CNHTC_SITAIERWANG_1 = 10,      // 中国重汽-斯太尔王-牵引车A,载货车,搅拌车
	VSB_CNHTC_HAOHAN_1 = 11,      // 中国重汽-豪瀚-A款
	VSB_CNHTC_HAOYUN_1 = 12,      // 中国重汽-豪运-牵引车B,载货车,自卸车
	VSB_CNHTC_JINWANGZI_1 = 13,      // 中国重汽-金王子重卡-牵引车B
	VSB_CNHTC_HOKA_1 = 14      // 中国重汽-HOKA-H7
}VSB_CNHTC_CLASS;

//中通子品牌类型
typedef enum _VSB_ZHONGTONG_CLASS
{
	VSB_ZHONGTONG_OTHER = 0,  // 其他（保留）
	VSB_ZHONGTONG_KAICHI_1 = 1,  // 中通客车-凯驰A-A款
	VSB_ZHONGTONG_LINGYU_1 = 2,  // 中通客车-领御-A款
	VSB_ZHONGTONG_LINGXIU_1 = 3,  // 中通客车-领秀-A款
	VSB_ZHONGTONG_LINGHANG_1 = 4,  // 中通客车-领航-A款
	VSB_ZHONGTONG_SHIJI_1 = 5,  // 中通客车-世纪-A款
	VSB_ZHONGTONG_KAIXUAN_1 = 6,  // 中通客车-凯旋-A款
	VSB_ZHONGTONG_LINGYUN_1 = 7,  // 中通客车-领韵A-A款
	VSB_ZHONGTONG_YANGGUANG_1 = 8  // 中通客车-阳光-A款
}VSB_ZHONGTONG_CLASS;


//九龙子品牌类型
typedef enum _VSB_JIULONG_CLASS
{
	VSB_JIULONG_OTHER = 0,    // 其他（保留）
	VSB_JIULONG_JIULONGA5_1 = 1,    // 九龙-九龙A5-2011
}VSB_JIULONG_CLASS;

//众泰子品牌类型
typedef enum _VSB_ZOTYE_CLASS
{
	VSB_ZOTYE_OTHER = 0,       // 其他（保留）
	VSB_ZOTYE_2008_2 = 1,      // 众泰-2008-2011,2010,2008
	VSB_ZOTYE_5008_1 = 2,      // 众泰-5008-2013,2011,2010,2008
	VSB_ZOTYE_Z300_1 = 3,      // 众泰-Z300-2013,2012
	VSB_ZOTYE_2008_1 = 4      // 众泰-2008-2007
}VSB_ZOTYE_CLASS;

//依维柯子品牌类型
typedef enum _VSB_NAVECO_CLASS
{
	VSB_NAVECO_OTHER = 0,       // 其他（保留）
	VSB_NAVECO_Daily_1 = 1,     // 依维柯-Daily-2006,2004,2003
	VSB_NAVECO_Power_1 = 2,     // 依维柯-Power-Daily
	VSB_NAVECO_Turbo_1 = 3,     // 依维柯-Turbo-Daily-2014,2012,2011
	VSB_NAVECO_Venice_1 = 4,     // 依维柯-Venice-2011,2008
	VSB_NAVECO_BAODI_1 = 5,     // 依维柯-宝迪-2012,2009
	VSB_NAVECO_DEYIHUOCHE_1 = 6,     // 依维柯-得意货车-2011
	VSB_NAVECO_DULING_1 = 7     // 依维柯-都灵-2010,2009,2007
}VSB_NAVECO_CLASS;

//保时捷子品牌类型
typedef enum _VSB_PORSCHE_CLASS
{
	VSB_PORSCHE_OTHER = 0,    // 其他（保留）
	VBR_PORSCHE_PANAMERA_1 = 1,    // 保时捷-panamera-2013,2012,2010
	VBR_PORSCHE_CAYENNE_1 = 2,    // 保时捷-卡宴Cayenne-2014,2013,2011,2010
}VSB_PORSCHE_CLASS;


//克莱斯勒子品牌类型
typedef enum _VSB_CHRYSLER_CLASS
{
	VSB_CHRYSLER_OTHER = 0,    // 其他（保留）
	VSB_CHRYSLER_300C_1 = 1,   // 克莱斯勒-300C-2007,2006,2004
	VSB_CHRYSLER_PTMANBUZHE_1 = 2,   // 克莱斯勒-PT漫步者-2007
}VSB_CHRYSLER_CLASS;

//凯迪拉克子品牌类型
typedef enum _VSB_CADILLAC_CLASS
{
	VSB_CADILLAC_OTHER = 0,    // 其他（保留）
	VSB_CADILLAC_ATS_1 = 1,   // 凯迪拉克-ATS-2014
	VSB_CADILLAC_CTS_1 = 2,   // 凯迪拉克-CTS-2012
	VSB_CADILLAC_CTS_3 = 3,   // 凯迪拉克-CTS-2012精英运动型,2011,2010,2009,2008
	VSB_CADILLAC_SLS_1 = 4,   // 凯迪拉克-SLS赛威-2007,2006
	VSB_CADILLAC_SLS_2 = 5,   // 凯迪拉克-SLS赛威-2012,2011,2010
	VSB_CADILLAC_SRX_1 = 6,   // 凯迪拉克-SRX-2012,2011,2010,2009
	VSB_CADILLAC_CTS_2 = 7,   // 凯迪拉克-CTS-2012,2009CTS
	VSB_CADILLAC_KAILEIDE_1 = 8   // 凯迪拉克-凯雷德-2011,2010,2008,2007,2006
}VSB_CADILLAC_CLASS;


//凯马KAMA子品牌类型
typedef enum _VSB_KAMA_CLASS
{
	VSB_KAMA_OTHER = 0,       // 其他（保留）
	VSB_KAMA_QINGKA_2 = 1,       // 凯马KAMA-凯马-轻卡D
	VSB_KAMA_FULAIKA_1 = 2,       // 凯马KAMA-福来卡-轻卡A
	VSB_KAMA_JINYUNKA_1 = 3,       // 凯马KAMA-金运卡-轻卡
	VSB_KAMA_JUNWEIKA_1 = 4,       // 凯马KAMA-骏威卡车-2014,2011
	VSB_KAMA_QINGKA_1 = 5       // 凯马KAMA-凯马-轻卡C
}VSB_KAMA_CLASS;

//力帆子品牌类型
typedef enum _VSB_LIFAN_CLASS
{
	VSB_LIFAN_OTHER = 0,      // 其他（保留）
	VSB_LIFAN_320_1 = 1,      // 力帆-320-2012,2011,2009
	VSB_LIFAN_520_1 = 2,      // 力帆-520-2007,2006
	VSB_LIFAN_520_2 = 3,      // 力帆-520-2013,2011,2010,2008
	VSB_LIFAN_620_1 = 4,      // 力帆-620-2012,2010,2009,2008
	VSB_LIFAN_X60_1 = 5,      // 力帆-X60-2013,2012,2011
	VSB_LIFAN_FENGSHUN_1 = 6      // 力帆-丰顺-2011
}VSB_LIFAN_CLASS;


//北京子品牌类型
typedef enum _VSB_BEIJING_CLASS
{
	VSB_BEIJING_OTHER = 0,      // 其他（保留）
	VSB_BEIJING_E_1 = 1,    // 北京汽车-E系列两厢-2014,2013,2012
}VSB_BEIJING_CLASS;

//北奔重汽子品牌类型
typedef enum _VSB_BEIBEN_CLASS
{
	VSB_BEIBEN_OTHER = 0,      // 其他（保留）
	VSB_BEIBEN_NG80_1 = 1,     // 北奔重汽-NG80-重卡A
	VSB_BEIBEN_NG80_2 = 2,     // 北奔重汽-NG80-重卡B
	VSB_BEIBEN_NG80_3 = 3,     // 北奔重汽-NG80-重卡C
	VSB_BEIBEN_V3_1 = 4,     // 北奔重汽-北奔V3-V3H1
	VSB_BEIBEN_V3_2 = 5     // 北奔重汽-北奔V3-重卡A
}VSB_BEIBEN_CLASS;

//北方客车子品牌类型
typedef enum _VSB_BEIFANG_CLASS
{
	VSB_BEIFANG_OTHER = 0,      // 其他（保留）
	VSB_BEIFANG_A_1 = 1       // 北方客车-客车车型1-A款
}VSB_BEIFANG_CLASS;


//北汽制造子品牌类型
typedef enum _VSB_BAW_CLASS
{
	VSB_BAW_OTHER = 0,        // 其他（保留）
	VSB_BAW_YUSHENG007_1 = 1,        // 北汽制造-域胜007-2013,2011
	VSB_BAW_QILING_1 = 2,        // 北汽制造-旗铃-A款
	VSB_BAW_LUBA_1 = 3,        // 北汽制造-陆霸-2004
	VSB_BAW_QISHI_1 = 4         // 北汽制造-骑士-2009,2007
}VSB_BAW_CLASS;

//北汽威旺子品牌类型
typedef enum _VSB_BQWEIWANG_CLASS
{
	VSB_BQWEIWANG_OTHER = 0,  // 其他（保留）
	VSB_BQWEIWANG_205_1 = 1,  // 北汽威旺-205-2013
	VSB_BQWEIWANG_306_1 = 2   // 北汽威旺-306-2014,2013,2011
}VSB_BQWEIWANG_CLASS;


//华普子品牌类型
typedef enum _VSB_SMA_CLASS
{
	VSB_SMA_OTHER = 0,        // 其他（保留）
	VSB_SMA_HAIYU_1 = 1,        // 华普-海域-2007,2005,2004
	VSB_SMA_HAIYU_2 = 2,        // 华普-海域-2007海域MB
	VSB_SMA_HAISHANG_1 = 3,        // 华普-海尚-2008,2005
	VSB_SMA_HAIJING_1 = 5,        // 华普-海景-2010,2009
	VSB_SMA_HAIXUN_1 = 4,        // 华普-海迅-2005,2004飙风
	VSB_SMA_HAIXUN_2 = 6,        // 华普-海迅-2007,2006
}VSB_SMA_CLASS;

//华菱星马子品牌类型
typedef enum _VSB_XINGMA_CLASS
{
	VSB_XINGMA_OTHER = 0,        // 其他（保留）
	VSB_XINGMA_XINGKAIMA_1 = 1         // 华菱星马-星凯马-牵引车型1,载货车型1
}VSB_XINGMA_CLASS;

//双环子品牌类型
typedef enum _VSB_SHUANGHUAN_CLASS
{
	VSB_SHUANGHUAN_OTHER = 0,        // 其他（保留）
	VSB_SHUANGHUAN_SCEO_1 = 1,        // 双环-SCEO-2011,2009,2006,2005
}VSB_SHUANGHUAN_CLASS;

//吉普子品牌类型
typedef enum _VSB_JEEP_CLASS
{
	VSB_JEEP_OTHER = 0,       // 其他（保留）
	VSB_JEEP_DAQIENUOJI_1 = 1,       // 吉普-大切诺基(进口)-2014,2013,2012,2011
	VSB_JEEP_DAQIENUOJI_2 = 2,       // 吉普-大切诺基(进口)-2014舒享导航版
	VSB_JEEP_ZHINANZHE_1 = 3,       // 吉普-指南者-2010,2007
	VSB_JEEP_ZHINANZHE_2 = 4,       // 吉普-指南者-2014,2013,2012,2011
	VSB_JEEP_MUMAREN_1 = 5,       // 吉普-牧马人-2012使命召唤限量版,2011
	VSB_JEEP_MUMAREN_2 = 6,       // 吉普-牧马人-2014,2013,2012,2011,2010,2009,2008
	VSB_JEEP_ZIYOUKE = 7,       // 吉普-自由客-2014,2013,2012,2011
}VSB_JEEP_CLASS;

//启辰子品牌类型
typedef enum _VSB_VENUCIA_CLASS
{
	VSB_VENUCIA_OTHER = 0,       // 其他（保留）
	VSB_VENUCIA_D50_1 = 1        // 启辰-D50-2014,2013,2012
}VSB_VENUCIA_CLASS;

//哈飞子品牌类型
typedef enum _VSB_HAFEI_CLASS
{
	VSB_HAFEI_OTHER = 0,      // 其他（保留）
	VSB_HAFEI_XINMINYI_1 = 1,      // 哈飞-新民意货车-2010
	VSB_HAFEI_XINMINYI_2 = 2,      // 哈飞-新民意面包车-2012
	VSB_HAFEI_MINYI_1 = 3,      // 哈飞-民意货车-2006
	VSB_HAFEI_MINYI_2 = 4,      // 哈飞-民意面包车-2008
	VSB_HAFEI_SAIBAO_1 = 5,      // 哈飞-赛豹Ⅲ-2012
	VSB_HAFEI_SAIMA_1 = 6,      // 哈飞-赛马-2002
	VSB_HAFEI_SAIMA_2 = 7,      // 哈飞-赛马-2004,2003
	VSB_HAFEI_SAIMA_3 = 8,      // 哈飞-赛马-2009
	VSB_HAFEI_LUBAO_1 = 9,      // 哈飞-路宝-2004
	VSB_HAFEI_LUBAO_2 = 10,      // 哈飞-路宝-2008,2007
	VSB_HAFEI_LUBAO_3 = 11,      // 哈飞-路宝-2012
	VSB_HAFEI_LUZUNXIAOBAWANG_1 = 12,      // 哈飞-路尊小霸王-2011,2010
	VSB_HAFEI_RUIYI_1 = 13,      // 哈飞-锐意-2009
	VSB_HAFEI_JUNYI_1 = 14       // 哈飞-骏意-2012,2010
}VSB_HAFEI_CLASS;

//唐骏欧铃子品牌类型
typedef enum _VSB_TKING_CLASS
{
	VSB_TKING_OTHER = 0,      // 其他（保留）
	VSB_TKING_OUGUAN_1 = 1,      // 唐骏欧铃-欧冠-2011
	VSB_TKING_OUGUAN_2 = 2,      // 唐骏欧铃-欧冠-轻卡B
	VSB_TKING_OUTENG_1 = 3,      // 唐骏欧铃-欧腾-轻卡A
	VSB_TKING_FUXING_1 = 4,      // 唐骏欧铃-福星-2006
	VSB_TKING_QINGKAWANG_1 = 5,      // 唐骏欧铃-轻卡王-轻卡
	VSB_TKING_AFANDA_1 = 6,      // 唐骏欧铃-阿凡达-中重卡
	VSB_TKING_JUNQI_1 = 7       // 唐骏欧铃-骏麒-中重卡A
}VSB_TKING_CLASS;

//大宇子品牌类型
typedef enum _VSB_DAEWOO_CLASS
{
	VSB_DAEWOO_OTHER = 0,    // 其他（保留）
	VBR_DAEWOO_6960H3_1 = 1     // 大宇-6960H3-A款
}VSB_DAEWOO_CLASS;

//大运汽车子品牌类型
typedef enum _VSB_DAYUN_CLASS
{
	VSB_DAYUN_OTHER = 0,     // 其他（保留）
	VBR_DAYUN_ZHONGKA_1 = 1      // 大运汽车-重卡-A款
}VSB_DAYUN_CLASS;

//奔腾子品牌类型
typedef enum _VSB_BESTURN_CLASS
{
	VSB_BESTURN_OTHER = 0,   // 其他（保留）
	VSB_BESTURN_B70_1 = 1,    // 奔腾-B70-2009,2007,2006
	VSB_BESTURN_B70_2 = 2,    // 奔腾-B70-2011
	VSB_BESTURN_B70_3 = 3,    // 奔腾-B70-2011精英型,2010
	VSB_BESTURN_B70_4 = 4,    // 奔腾-B70-2012
	VSB_BESTURN_B90_1 = 5,    // 奔腾-B90-2012
	VSB_BESTURN_AOXING_1 = 6       // 一汽-奥星-2004
}VSB_BESTURN_CLASS;

//威麟子品牌类型
typedef enum _VSB_WEILIN_CLASS
{
	VSB_WEILIN_OTHER = 0,      // 其他（保留）
	VSB_WEILIN_H3_1 = 1,     // 威麟-H3-2011
	VSB_WEILIN_V5_1 = 2,     // 威麟-V5-2012,2009
	VSB_WEILIN_X5_1 = 3      // 威麟-X5-2012,2011,2010
}VSB_WEILIN_CLASS;

//宇通子品牌类型
typedef enum _VSB_YUTONG_CLASS
{
	VSB_YUTONG_OTHER = 0,     // 其他（保留）
	VSB_YUTONG_8XI_1 = 1,     // 宇通-8系-2012,2005
	VSB_YUTONG_KECHE_1 = 2,     // 宇通-客车车型10-2013,2010
	VSB_YUTONG_KECHE_3 = 3,     // 宇通-客车车型2-A款
	VSB_YUTONG_KECHE_4 = 4,     // 宇通-客车车型8-2004
	VSB_YUTONG_KECHE_5 = 5,     // 宇通-客车车型9-2014
	VSB_YUTONG_KECHE_2 = 6      // 宇通-客车车型12-A款
}VSB_YUTONG_CLASS;

//安凯子品牌类型
typedef enum _VSB_ANKAI_CLASS
{
	VSB_ANKAI_OTHER = 0,      // 其他（保留）
	VSB_ANKAI_KECHE_1 = 1,      // 安凯-客车车型1-A款
	VSB_ANKAI_KECHE_2 = 2       // 安凯-客车车型3-A款
}VSB_ANKAI_CLASS;

//宝骏子品牌类型
typedef enum _VSB_BAOJUN_CLASS
{
	VSB_BAOJUN_OTHER = 0,   // 其他（保留）
	VSB_BAOJUN_630_1 = 1      // 宝骏-宝骏630-2014,2013,2012,2011
}VSB_BAOJUN_CLASS;

//宾利子品牌类型
typedef enum _VSB_BINLI_CLASS
{
	VSB_BINLI_OTHER = 0,     // 其他（保留）
	VSB_BINLI_OULU_1 = 1      // 宾利-欧陆-2009,2008
}VSB_BINLI_CLASS;

//广汽传祺子品牌类型
typedef enum _VSB_TRUMPCHE_CLASS
{
	VSB_TRUMPCHE_OTHER = 0,   // 其他（保留）
	VSB_TRUMPCHE_GA5_1 = 1,   // 广汽传祺-GA5-2012,2011
	VSB_TRUMPCHE_GA5_2 = 3,   // 广汽传祺-GA5-2013,2012自动精英版
	VSB_TRUMPCHE_GS5_1 = 2    // 广汽传祺-GS5-2014,2013,2012
}VSB_TRUMPCHE_CLASS;

//广汽吉奥 子品牌类型
typedef enum _VSB_GONOW_CLASS
{
	VSB_GONOW_OTHER = 0,   // 其他（保留）
	VSB_GONOW_G3_1 = 1,      // 广汽吉奥-G3-2011
	VSB_GONOW_G5_1 = 2,      // 广汽吉奥-G5-2012,2011
	VSB_GONOW_SHUAIJIAN_1 = 4,      // 广汽吉奥-帅舰-2012,2009
	VSB_GONOW_XINGWANGM1_1 = 3,      // 广汽吉奥-星旺M1-2012
	VSB_GONOW_CAIYUN500_1 = 5      // 广汽吉奥-财运500-2010
}VSB_GONOW_CLASS;

//庆铃子品牌类型
typedef enum _VSB_ISUZU_CLASS
{
	VSB_ISUZU_OTHER = 0,   // 其他（保留）
	VSB_ISUZU_ZHONGXINGSHANGYONG_1 = 1,      // 庆铃-中型商用车-2011
	VSB_ISUZU_WUSHILINGPIKA_1 = 2,      // 庆铃-五十铃皮卡-2009
	VSB_ISUZU_WUSHILINGPIKA_2 = 3,      // 庆铃-五十铃皮卡-2014,2009
	VSB_ISUZU_JINGJIZHE_1 = 4      // 庆铃-竞技者-2004,2002
}VSB_ISUZU_CLASS;


//开瑞子品牌类型
typedef enum _VSB_KARRY_CLASS
{
	VSB_KARRY_OTHER = 0,   // 其他（保留）
	VSB_KARRY_YOU_2 = 1,      // 开瑞-优优-2013,2012
	VSB_KARRY_YOUJIN_1 = 2,      // 开瑞-优劲-2012,2011基本型,2010
	VSB_KARRY_YOUSHENG_1 = 3,      // 开瑞-优胜-2010
	VSB_KARRY_YOUSHENG_2 = 4,      // 开瑞-优胜-2012,2011
	VSB_KARRY_YOUYA = 5,      // 开瑞-优雅-2012,2011,2007
	VSB_KARRY_YOU_1 = 6      // 开瑞-优优-2011,2010,2009
}VSB_KARRY_CLASS;

//捷豹子品牌类型
typedef enum _VSB_GAGUAR_CLASS
{
	VSB_GAGUAR_OTHER = 0,   // 其他（保留）
	VSB_GAGUAR_XF_1 = 1,     // 捷豹-XF-2014,2013
	VSB_GAGUAR_XJ_1 = 2     // 捷豹-XJ-2014,2013,2012,2011,2010
}VSB_GAGUAR_CLASS;

//斯巴鲁子品牌类型
typedef enum _VSB_SUBARU_CLASS
{
	VSB_SUBARU_OTHER = 0,   // 其他（保留）
	VSB_SUBARU_AOHU_1 = 1,     // 斯巴鲁-傲虎-2012,2011,2010
	VSB_SUBARU_LISHI_1 = 2,     // 斯巴鲁-力狮轿车-2008,2006
	VSB_SUBARU_LISHI_2 = 3,     // 斯巴鲁-力狮轿车-2011,2010
	VSB_SUBARU_XV_1 = 4,     // 斯巴鲁-斯巴鲁XV-2014,2012
	VSB_SUBARU_SENLINREN_1 = 5,     // 斯巴鲁-森林人-2007,2006
	VSB_SUBARU_SENLINREN_2 = 6     // 斯巴鲁-森林人-2012,2011,2010,2009,2008
}VSB_SUBARU_CLASS;

//时代汽车子品牌类型
typedef enum _VSB_ERA_CLASS
{
	VSB_ERA_OTHER = 0,   // 其他（保留）
	VSB_ERA_XIAOKA_1 = 1,        // 时代汽车-小卡之星-小卡之星1,2,Q2
	VSB_ERA_XIAOKA_3 = 2,        // 时代汽车-小卡之星-小卡之星5
	VSB_ERA_XIAOKA_4 = 3,        // 时代汽车-小卡之星-福锐
	VSB_ERA_KANGRUI_1 = 4,        // 时代汽车-康瑞-康瑞H1
	VSB_ERA_KANGRUI_2 = 5,        // 时代汽车-康瑞-康瑞H3
	VSB_ERA_KANGRUI_3 = 6,        // 时代汽车-康瑞-康瑞K1,KQ1
	VSB_ERA_RUIWO_1 = 7,        // 时代汽车-瑞沃-RC1
	VSB_ERA_RUIWO_2 = 8,        // 时代汽车-瑞沃-RC2
	VSB_ERA_RUIWO_3 = 9,        // 时代汽车-瑞沃-瑞沃II轻卡A
	VSB_ERA_JINGANG = 10,        // 时代汽车-金刚-金刚568
	VSB_ERA_LINGHANG_1 = 11,        // 时代汽车-领航-领航2
	VSB_ERA_LINGHANG_2 = 12,        // 时代汽车-领航-领航3
	VSB_ERA_YULING_1 = 13,        // 时代汽车-驭菱-驭菱V1
	VSB_ERA_YULING_2 = 14,        // 时代汽车-驭菱-驭菱V5,VQ5
	VSB_ERA_YULING_3 = 15,        // 时代汽车-驭菱-驭菱VQ1,VQ2
	VSB_ERA_YULING_4 = 17,        // 时代汽车-驭菱-鸿运
	VSB_ERA_XIAOKA_2 = 17,        // 时代汽车-小卡之星-小卡之星3
}VSB_ERA_CLASS;

//昌河子品牌类型
typedef enum _VSB_CHANGHE_CLASS
{
	VSB_CHANGHE_OTHER = 0,  // 其他（保留）
	VSB_CHANGHE_CH6321_1 = 1,  // 昌河-CH6321-2000
	VSB_CHANGHE_DANSHUANGPAI_1 = 2,  // 昌河-昌河新单双排-1999
	VSB_CHANGHE_AIDIER_1 = 3,  // 昌河-爱迪尔-2004
	VSB_CHANGHE_AIDIER_2 = 4,  // 昌河-爱迪尔Ⅱ-2007,2006
	VSB_CHANGHE_FURUIDA_1 = 5   // 昌河-福瑞达面包车-2014,2013,2011,2009
}VSB_CHANGHE_CLASS;

//欧宝子品牌类型
typedef enum _VSB_OPEL_CLASS
{
	VSB_OPEL_OTHER = 0,    // 其他（保留）
	VSB_OPEL_YATE_1 = 1     // 欧宝-雅特-2010GTC全景风挡版,2007,2006
}VSB_OPEL_CLASS;

//永源子品牌类型
typedef enum _VSB_JONWAY_CLASS
{
	VSB_JONWAY_OTHER = 0,   // 其他（保留）
	VSB_JONWAY_A380_1 = 1    // 永源-A380-2010,2009,2008
}VSB_JONWAY_CLASS;

//江南子品牌类型
typedef enum _VSB_JIANGNAN_CLASS
{
	VSB_JIANGNAN_OTHER = 0,   // 其他（保留）
	VSB_JIANGNAN_TT_1 = 1    // 江南-江南TT-2011,2010,2004
}VSB_JIANGNAN_CLASS;

//吉利全球鹰子品牌类型
typedef enum _VSB_GLEAGLE_CLASS
{
	VSB_GLEAGLE_OTHER = 0,   // 其他（保留）
	VSB_GLEAGLE_EAGLE_GC7_1 = 1,   // 吉利全球鹰-GC7-2013,2012
	VSB_GLEAGLE_EAGLE_GX2_1 = 2,   // 吉利全球鹰-GX2-2012,2011
	VSB_GLEAGLE_EAGLE_GX7_1 = 3,   // 吉利全球鹰-GX7-2013,2012
	VSB_GLEAGLE_EAGLE_PANDA_1 = 4,   // 吉利全球鹰-熊猫-2013,2011,2010,2009
	VSB_GLEAGLE_EAGLE_ZIYOUJIAN_1 = 5,   // 吉利全球鹰-自由舰-2009精致标准型,2007
	VSB_GLEAGLE_EAGLE_ZIYOUJIAN_2 = 6,   // 吉利全球鹰-自由舰-2010,2009,2008,2006,2005
	VSB_GLEAGLE_EAGLE_ZIYOUJIAN_3 = 7,   // 吉利全球鹰-自由舰-2012,2011
	VSB_GLEAGLE_EAGLE_YUANJING_1 = 8,   // 吉利全球鹰-远景-2011,2010,2009,2008,2006
	VSB_GLEAGLE_EAGLE_YUANJING_2 = 9,   // 吉利全球鹰-远景-2013,2012
}VSB_GLEAGLE_CLASS;

//吉利帝豪子品牌类型
typedef enum _VSB_EMGRAND_CLASS
{
	VSB_EMGRAND_OTHER = 0,   // 其他（保留）
	VSB_EMGRAND_EC7_2 = 1,   // 吉利帝豪-EC7-2013
	VSB_EMGRAND_EC7_3 = 2,   // 吉利帝豪-EC7-RV
	VSB_EMGRAND_EC8_1 = 3,   // 吉利帝豪-EC8-2013,2011,2010
	VSB_EMGRAND_EC7_1 = 4    // 吉利帝豪-EC7-2012,2010,2009
}VSB_EMGRAND_CLASS;


//吉利英伦子品牌类型
typedef enum _VSB_ENGLON_CLASS
{
	VSB_ENGLON_OTHER = 0,    // 其他（保留）
	VSB_ENGLON_SC3_1 = 1,    // 吉利英伦-SC3-2012
	VSB_ENGLON_SC5_1 = 2,    // 吉利英伦-SC5-RV-2012
	VSB_ENGLON_SC6_1 = 3,    // 吉利英伦-SC6-2012
	VSB_ENGLON_SC7_1 = 4,    // 吉利英伦-SC7-2013,2012,2011,2010
	VSB_ENGLON_SX7_1 = 5,    // 吉利英伦-SX7-2014,2013
	VSB_ENGLON_JINGANG_1 = 6,    // 吉利英伦-金刚-2010,2007,2006
	VSB_ENGLON_JINYING_1 = 7     // 吉利英伦-金鹰-2011,2010,2008
}VSB_ENGLON_CLASS;


//江淮-子品牌类型
typedef enum _VSB_JAC_CLASS
{
	VSB_JAC_OTHER = 0,      // 其他（保留）
	VSB_JAC_TONGYUE_1 = 1,      // 江淮-同悦-2012,2010,2008
	VSB_JAC_HEYUE_1 = 2,      // 江淮-和悦-2012,2011,2010
	VSB_JAC_HEYUEA30_2 = 3,      // 江淮-和悦A30-2013
	VSB_JAC_HEYUERS_3 = 4,      // 江淮-和悦RS-2012,2011
	VSB_JAC_HAOYUN_1 = 5,      // 江淮-好运-轻卡1
	VSB_JAC_WEILING_2 = 6,      // 江淮-威铃-排半轻卡
	VSB_JAC_WEILING_3 = 7,      // 江淮-威铃-栏板载货车
	VSB_JAC_WEILING_4 = 8,      // 江淮-威铃-轻卡
	VSB_JAC_KECHE_1 = 9,      // 江淮-客车-A款
	VSB_JAC_BINYUE_1 = 10,      // 江淮-宾悦-2010,2008
	VSB_JAC_SHUAILING_2 = 11,      // 江淮-帅铃-轻卡
	VSB_JAC_KANGLING_1 = 12,      // 江淮-康铃-轻卡1
	VSB_JAC_KANGLING_2 = 13,      // 江淮-康铃-轻卡2
	VSB_JAC_YUEYUE_1 = 14,      // 江淮-悦悦-2013,2012,2011,2010
	VSB_JAC_XINGRUI_1 = 15,      // 江淮-星锐-2012,2011
	VSB_JAC_GEERFA_H_1 = 16,      // 江淮-格尔发H-栏板载货车
	VSB_JAC_GEERFA_K_2 = 17,      // 江淮-格尔发K-重卡1
	VSB_JAC_GEERFA_K_3 = 18,      // 江淮-格尔发K-重卡2
	VSB_JAC_GEERFA_M_4 = 19,      // 江淮-格尔发M-栏板载货车
	VSB_JAC_RUIFENG_1 = 20,      // 江淮-瑞风-2011,2009,2007手动
	VSB_JAC_RUIFENG_2 = 21,      // 江淮-瑞风-2013,2012,2011,2010,2007,2005
	VSB_JAC_RUIFENG_3 = 22,      // 江淮-瑞风M5-2012,2011
	VSB_JAC_RUIFENG_4 = 23,      // 江淮-瑞风S5-2013
	VSB_JAC_RUIYING_1 = 24,      // 江淮-瑞鹰-2009,2007
	VSB_JAC_RUIYING_2 = 25,      // 江淮-瑞鹰-2013,2012,2011
	VSB_JAC_JUNLING_2 = 26,      // 江淮-骏铃-窄体版,中体版
	VSB_JAC_WEILING_1 = 27,      // 江淮-威铃-厢式轻卡
	VSB_JAC_SHUAILING_1 = 28,      // 江淮-帅铃-五十铃
	VSB_JAC_RUILING_1 = 29,      // 江淮-瑞铃-2012
	VSB_JAC_JUNLING_1 = 30      // 江淮-骏铃-旗舰版
}VSB_JAC_CLASS;


//江铃子品牌类型
typedef enum _VSB_JMC_CLASS
{
	VSB_JMC_OTHER = 0,      // 其他（保留）
	VSB_JMC_KAIYUN_1 = 1,      // 江铃-凯运-102,109马力轻卡
	VSB_JMC_KAIYUN_2 = 2,      // 江铃-凯运-95马力轻卡
	VSB_JMC_YUHU_1 = 3,      // 江铃-域虎-2012
	VSB_JMC_BAODIAN_1 = 4,      // 江铃-宝典-2007
	VSB_JMC_BAODIAN_2 = 5,      // 江铃-宝典-2009标准型,2008
	VSB_JMC_BAODIAN_3 = 6,      // 江铃-宝典-2014,2012,2009豪华型
	VSB_JMC_BAOWEI_1 = 7,      // 江铃-宝威-2005
	VSB_JMC_BAOWEI_2 = 8,      // 江铃-宝威-2009
	VSB_JMC_QUANSHUN_1 = 9,      // 江铃-福特新世代全顺-2010,2008
	VSB_JMC_QUANSHUN_2 = 10,      // 江铃-经典全顺-2006
	VSB_JMC_QUANSHUN_3 = 11,      // 江铃-经典全顺-2013,2011,2010
	VSB_JMC_SHUNDA_1 = 12,      // 江铃-顺达-2004,2003
	VSB_JMC_SHUNDA_2 = 13,      // 江铃-顺达-2011,2010,2008
	VSB_JMC_YUSHENG_1 = 14,      // 江铃-驭胜-2013
	VSB_JMC_YUSHENG_2 = 15       // 江铃-驭胜-2013手动特装版,2012,2011
}VSB_JMC_CLASS;

// 沃尔沃子品牌类型
typedef enum _VSB_VOLVO_CLASS
{
	VSB_VOLVO_OTHER = 0,   // 其他（保留）
	VSB_VOLVO_C30_1 = 1,    // 沃尔沃-C30-2013,2012,2011,2010
	VSB_VOLVO_S40_1 = 2,    // 沃尔沃-S40-2012,2011,2010,2009,2008,2007
	VSB_VOLVO_S60_1 = 3,    // 沃尔沃-S60-2003
	VSB_VOLVO_S60_2 = 4,    // 沃尔沃-S60-2013,2012,2011
	VSB_VOLVO_S80L_1 = 5,    // 沃尔沃-S80L-2012,2011,2010,2009
	VSB_VOLVO_XC60_1 = 6,    // 沃尔沃-XC60-2013,2012,2011,2010,2009
	VSB_VOLVO_XC90_1 = 7     // 沃尔沃-XC90-2013,2012,2011,2008
}VSB_VOLVO_CLASS;

// 海格子品牌类型
typedef enum _VSB_HIGER_CLASS
{
	VSB_HIGER_OTHER = 0,   // 其他（保留）
	VSB_HIGER_H8_1 = 1,    // 海格-H8-A款
	VSB_HIGER_H92_1 = 2,    // 海格-H92-A款
	VSB_HIGER_V7_1 = 3,    // 海格-V7,V8-2006
	VSB_HIGER_KECHE_1 = 4,    // 海格-客车车型5-A款
	VSB_HIGER_LONGWEI_1 = 5,    // 海格-龙威-2012,2011
	VSB_HIGER_H7V_1 = 6     // 海格-海格H7V-2010
}VSB_HIGER_CLASS;

// 瑞麒子品牌类型
typedef enum _VSB_RUILIN_CLASS
{
	VSB_RUILIN_OTHER = 0,   // 其他（保留）
	VSB_RUILIN_G3_1 = 1,   // 瑞麒-G3-2012,2010
	VSB_RUILIN_G5_1 = 2,   // 瑞麒-G5-2012,2011,2010
	VSB_RUILIN_M1_1 = 3,   // 瑞麒-M1-2013,2011,2010,2009
	VSB_RUILIN_X1_1 = 4,   // 瑞麒-X1-2012A,2011,2010
	VSB_RUILIN_X1_2 = 5    // 瑞麒-X1-2012B
}VSB_RUILIN_CLASS;

// 申龙子品牌类型
typedef enum _VSB_SHENLONG_CLASS
{
	VSB_SHENLON_OTHER = 0,         // 其他（保留）
	VSB_SHENLONG_KECHE_1 = 1          //申龙客车-客车车型4-A款
}VSB_SHENLONG_CLASS;

// 福田子品牌类型
typedef enum _VSB_FOTON_CLASS
{
	VSB_FOTON_OTHER = 0,            // 其他（保留）
	VSB_FOTON_AOLING_1 = 1,            // 福田-奥铃-中卡
	VSB_FOTON_AOLING_2 = 2,            // 福田-奥铃-厢式货车
	VSB_FOTON_AOLING_3 = 3,            // 福田-奥铃-奥铃TX,CTX
	VSB_FOTON_OUMAN_1 = 4,            // 福田-欧曼-GTL6系B
	VSB_FOTON_OUMAN_2 = 5,            // 福田-欧曼-TX6系,9系
	VSB_FOTON_OUMAN_3 = 6,            // 福田-欧曼-欧曼重卡1
	VSB_FOTON_OUMAN_4 = 7,            // 福田-欧曼-雄狮6系,9系
	VSB_FOTON_OUHUI_1 = 8,            // 福田-欧辉客车-D款
	VSB_FOTON_OUMAKE_1 = 9,            // 福田-欧马可-3系
	VSB_FOTON_OUMAKE_2 = 10,            // 福田-欧马可-5系
	VSB_FOTON_SAPU_1 = 11,            // 福田-萨普-2011
	VSB_FOTON_SAPU_3 = 12,            // 福田-萨普-2011柴油共轨
	VSB_FOTON_MENGPAIKE_1 = 13,            // 福田-蒙派克-2013
	VSB_FOTON_MIDI_1 = 14,            // 福田-迷迪-2011,2009
	VSB_FOTON_FENGJING_1 = 15,            // 福田-风景系列-2012,2011,2009
	VSB_FOTON_SAPU_2 = 16            // 福田-萨普-2011四驱征服者Z7
}VSB_FOTON_CLASS;

//福迪子品牌类型
typedef enum _VSB_FODAY_CLASS
{
	VSB_FODAY_OTHER = 0,            // 其他（保留）
	VSB_FODAY_CHAOREN_1 = 1,            // 福迪-小超人皮卡-2009,2006
	VSB_FODAY_CHAOREN_2 = 2,            // 福迪-小超人皮卡-2011
	VSB_FODAY_TANSUOZHE_1 = 3,            // 福迪-探索者6-2013,2011,2010
	VSB_FODAY_TANSUOZHE_2 = 4,            // 福迪-探索者Ⅱ-2011,2010,2009
	VSB_FODAY_TANSUOZHE_3 = 5,            // 福迪-探索者Ⅲ-2011,2004
	VSB_FODAY_XIONGSHI_1 = 6             // 福迪-雄狮F16皮卡-2012
}VSB_FODAY_CLASS;

// 红旗子品牌类型
typedef enum _VSB_HONGQI_CLASS
{
	VSB_HONGQI_OTHER = 0,         // 其他（保留）
	VSB_HONGQI_MINGSHI_1 = 1           // 红旗-明仕-2007,2003,2001,2000,1999
}VSB_HONGQI_CLASS;


// 纳智捷 子品牌类型
typedef enum _VSB_LUXGEN_CLASS
{
	VSB_LUXGEN_OTHER = 0,         // 其他（保留）
	VSB_LUXGEN_DASEVEN_1 = 1          // 纳智捷-大7-SUV
}VSB_LUXGEN_CLASS;

// 夏利子品牌类型
typedef enum _VSB_XIALI_CLASS
{
	VSB_XIALI_OTHER = 0,         // 其他（保留）
	VSB_XIALI_QIBING_1 = 1,         // 美亚(夏利)-奇兵-2010
}VSB_XIALI_CLASS;

// 舒驰客车子品牌类型
typedef enum _VSB_SHUCHI_CLASS
{
	VSB_SHUCHI_OTHER = 0,         // 其他（保留）
	VSB_SHUCHI_A_1 = 1          // 舒驰客车-客车-A款
}VSB_SHUCHI_CLASS;

//英菲尼迪子品牌类型
typedef enum _VSB_INFINITI_CLASS
{
	VSB_INFINITI_OTHER = 0,         // 其他（保留）
	VSB_INFINITI_EX_1 = 1,         // 英菲尼迪-EX-2013,2011,2010,2009,2008
	VSB_INFINITI_FX_1 = 2,         // 英菲尼迪-FX-2007
	VSB_INFINITI_FX_2 = 3,         // 英菲尼迪-FX-2011,2010,2009
	VSB_INFINITI_FX_3 = 4,         // 英菲尼迪-FX-2013,2012FX35
	VSB_INFINITI_G_1 = 5,         // 英菲尼迪-G-2013,2010
	VSB_INFINITI_JX_1 = 6          // 英菲尼迪-JX-2013,2011
}VSB_INFINITI_CLASS;


// 莲花子品牌类型
typedef enum _VSB_LOTUS_CLASS
{
	VSB_LOTUS_OTHER = 0,            // 其他（保留）
	VSB_LOTUS_L3_1 = 1,            // 莲花-L3三厢-2010豪华型,2009
	VSB_LOTUS_L3_2 = 2             // 莲花-L5三厢-2012,2011
}VSB_LOTUS_CLASS;

//菲亚特子品牌类型
typedef enum _VSB_FIAT_CLASS
{
	VSB_FIAT_OTHER = 0,            // 其他（保留）
	VSB_FIAT_FEIYUE_1 = 1             // 菲亚特-菲跃-2014,2013,2012
}VSB_FIAT_CLASS;

//讴歌子品牌类型
typedef enum _VSB_OGA_CLASS
{
	VSB_OGA_OTHER = 0,              // 其他（保留）
	VSB_OGA_MDX_1 = 1,              // 讴歌-MDX-2010
	VSB_OGA_MDX_2 = 2               // 讴歌-MDX-2011
}VSB_OGA_CLASS;



// 跃进子品牌类型
typedef enum _VSB_YUEJIN_CLASS
{
	VSB_YUEJIN_OTHER = 0,           // 其他（保留）
	VSB_YUEJIN_SHUAIHU_1 = 1,           // 跃进-帅虎-H100,H300
	VSB_YUEJIN_CAISHEN_1 = 2,           // 跃进-财神-S100
	VSB_YUEJIN_CAISHEN_2 = 3,           // 跃进-财神-S300
	VSB_YUEJIN_CAISHEN_3 = 4            // 跃进-财神-S500
}VSB_YUEJIN_CLASS;

//野马子品牌类型
typedef enum _VSB_YEMA_CLASS
{
	VSB_YEMA_OTHER = 0,        // 其他（保留）
	VSB_YEMA_F99_1 = 1            // 野马-F99-2012,2011,2010,2009 
}VSB_YEMA_CLASS;

//金龙子品牌类型
typedef enum _VSB_SZKINGLONG_CLASS
{
	VSB_SZKINGLONG_OTHER = 0,        // 其他（保留）
	VSB_SZKINGLONG_BUS11_1 = 1,       // 金龙-客车车型11-A款
	VSB_SZKINGLONG_BUS12_1 = 2,       // 金龙-客车车型12-A款
	VSB_SZKINGLONG_BUS13_1 = 3,       // 金龙-客车车型13-A款
	VSB_SZKINGLONG_BUS14_1 = 4,       // 金龙-客车车型14-A款
	VSB_SZKINGLONG_BUS16_1 = 5,       // 金龙-客车车型16-A款
	VSB_SZKINGLONG_BUS18_1 = 6,       // 金龙-客车车型18-A款
	VSB_SZKINGLONG_BUS1_1 = 7,       // 金龙-客车车型1-A款
	VSB_SZKINGLONG_BUS20_1 = 8,       // 金龙-客车车型20-A款
	VSB_SZKINGLONG_BUS2_1 = 9,       // 金龙-客车车型2-A款
	VSB_SZKINGLONG_BUS5_1 = 10,       // 金龙-客车车型5-A款
	VSB_SZKINGLONG_BUS6_1 = 11,       // 金龙-客车车型6-A款
	VSB_SZKINGLONG_BUS9_1 = 12,       // 金龙-客车车型9-A款
	VSB_SZKINGLONG_BUS10_1 = 13,       // 金龙-客车车型10-A款
	VSB_SZKINGLONG_BUS15_1 = 14        // 金龙-客车车型15-A款
}VSB_SZKINGLONG_CLASS;

//长丰猎豹子品牌类型
typedef enum _VSB_CHANGFENG_CLASS
{
	VSB_CHANGFENG_OTHER = 0,        // 其他（保留）
	VSB_CHANGFENG_CS7_1 = 1,        // 长丰猎豹-CS7-2009
	VSB_CHANGFENG_QIBING_1 = 2,        // 长丰猎豹-奇兵-2010,2009
	VSB_CHANGFENG_LIEBAO_1 = 3,        // 长丰猎豹-猎豹CS6-2010,2008
	VSB_CHANGFENG_FULING_1 = 4,        // 长丰猎豹-福铃皮卡-A款
	VSB_CHANGFENG_FEIYANG_1 = 5,        // 长丰猎豹-飞扬皮卡-2010,2009,2005
	VSB_CHANGFENG_FEITENG_1 = 6,        // 长丰猎豹-飞腾-2010,2009,2006
	VSB_CHANGFENG_BLACKJINGANG_1 = 7,        // 长丰猎豹-黑金刚-2013,2010,2009,2008,2006
}VSB_CHANGFENG_CLASS;

//陆风子品牌类型
typedef enum _VSB_LUFENG_CLASS
{
	VSB_LUFENG_OTHER = 0,           // 其他（保留）
	VSB_LUFENG_X6_1 = 1,           // 陆风-X6-2005
	VSB_LUFENG_X6_2 = 2,           // 陆风-X6-2006
	VSB_LUFENG_X6_3 = 3,           // 陆风-X6-2011,2010,2008,2007
	VSB_LUFENG_LUFENGX5_1 = 4,           // 陆风-陆风X5-2013
	VSB_LUFENG_LUFENGX8_1 = 5,           // 陆风-陆风X8-2013,2012,2011,2009
	VSB_LUFENG_LUFENGX8_2 = 6,           // 陆风-陆风X8-2014,2012探索版
	VSB_LUFENG_FENGHUA_1 = 7,           // 陆风-风华-2008,2007
	VSB_LUFENG_X6_4 = 8,           // 陆风-X6-2011两驱
	VSB_LUFENG_FENGSHANG_1 = 9            // 陆风-风尚-2011,2006 
}VSB_LUFENG_CLASS;

//陕汽重卡子品牌类型
typedef enum _VSB_SHANQI_CLASS
{
	VSB_SHANQI_OTHER = 0,           // 其他（保留）
	VSB_SHANQI_AOLONG_1 = 1,           // 陕汽重卡-奥龙-重卡A
	VSB_SHANQI_AOLONG_2 = 2,           // 陕汽重卡-奥龙-重卡B
	VSB_SHANQI_DELONG_1 = 3,           // 陕汽重卡-德龙F2000-4X2牵引车
	VSB_SHANQI_DELONG_2 = 4,           // 陕汽重卡-德龙F3000-B款
	VSB_SHANQI_DELONG_3 = 5,           // 陕汽重卡-德龙M3000-重卡 
}VSB_SHANQI_CLASS;


//野马子品牌类型
typedef enum _VSB_RENAULT_CLASS
{
	VSB_RENAULT_OTHER = 0,          // 其他（保留）
	VSB_RENAULT_MEIGANNA_1 = 1,          // 雷诺-梅甘娜-2006
	VSB_RENAULT_KELEIAO_1 = 2,          // 雷诺-科雷傲-2010,2009
	VSB_RENAULT_KELEIAO_2 = 3,          // 雷诺-科雷傲-2013,2012
	VSB_RENAULT_SCENE_1 = 4,          // 雷诺-风景-2007
	VSB_RENAULT_FENGLANG_1 = 5,          // 雷诺-风朗-2011
	VSB_RENAULT_TAFEIKE_1 = 6           // 雷诺-塔菲克-2004    
}VSB_RENAULT_CLASS;

//黄海子品牌类型
typedef enum _VSB_HUANGHAI_CLASS
{
	VSB_HUANGHAI_OTHER = 0,         // 其他（保留）
	VSB_HUANGHAI_DACAISHEN_1 = 1,         // 黄海-大柴神-2013,2012
	VSB_HUANGHAI_DACAISHEN_2 = 2,         // 黄海-大柴神-2013,2012,2011,2010,2009柴油版
	VSB_HUANGHAI_BUS4_1 = 3,         // 黄海-客车车型4-2012,2011
	VSB_HUANGHAI_CHALLENGER_1 = 4,         // 黄海-挑战者-2011,2010,2009,2008
	VSB_HUANGHAI_AOLONGCUV_1 = 5,         // 黄海-翱龙CUV-2010,2009
	VSB_HUANGHAI_AOJUN_1 = 6,         // 黄海-傲骏-2009
	VSB_HUANGHAI_AOJUN_2 = 7,         // 黄海-傲骏-2010,2009
	VSB_HUANGHAI_QISHENGV3_1 = 8,         // 黄海-旗胜V3-2011
	VSB_HUANGHAI_LINGHANGZHE_1 = 9,         // 黄海-领航者-2007,2005
	VSB_HUANGHAI_FENGCHI_1 = 10         // 黄海-风驰-A款
}VSB_HUANGHAI_CLASS;

/********************车辆品牌子类型End*************************/

//车辆信息
typedef struct tagNET_DVR_VEHICLE_INFO_
{
	DWORD dwIndex;          //车辆序号
	BYTE  byVehicleType;    //车辆类型 0 表示其它车型，1 表示小型车，2 表示大型车 ,3表示行人触发 ,4表示二轮车触发 5表示三轮车触发(3.5Ver)
	BYTE  byColorDepth;        //车身颜色深浅
	BYTE  byColor;          //车身颜色,参考VCR_CLR_CLASS
							/*雷达异常状态：
							0~雷达正常，
							1~雷达故障
							2~雷达一直发送某一个相同速度值
							3~雷达送出数据为0
							4~雷达送出数据过大或者过小
							*/
	BYTE  byRadarState;
	WORD  wSpeed;           //单位km/h
	WORD  wLength;          //前一辆车的车身长度  
							/*违规类型，0-正常，1-低速，2-超速，3-逆行，4-闯红灯,5-压车道线,6-不按导向，7-路口滞留，
							8-机占非，9-违法变道，10-不按车道 11-违反禁令，12-路口停车，13-绿灯停车, 14-未礼让行人(违法代码1357),
							15-违章停车，16-违章掉头,17-占用应急车道,18-禁右,19-禁左,20-压黄线,21-未系安全带,22-行人闯红灯,23-加塞*/
	BYTE  byIllegalType;
	BYTE  byVehicleLogoRecog; //参考枚举类型 VLR_VEHICLE_CLASS
	BYTE  byVehicleSubLogoRecog; //车辆品牌子类型识别；参考VSB_VOLKSWAGEN_CLASS等子类型枚举。
	BYTE  byVehicleModel; //车辆子品牌年款，0-未知，参考"车辆子品牌年款.xlsx"
	BYTE  byCustomInfo[16];  //自定义信息
	WORD  wVehicleLogoRecog;  //车辆主品牌，参考"车辆主品牌.xlsx" (该字段兼容byVehicleLogoRecog);
	BYTE  byRes3[14];
}NET_DVR_VEHICLE_INFO, *LPNET_DVR_VEHICLE_INFO;
