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
#define MAX_LICENSE_LEN 16
#define SERIALNO_LEN		    48      //序列号长度
#define MACADDR_LEN			    6       //mac地址长度
#define NAME_LEN			    32      //用户名长度
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
}NET_ITS_PLATE_RESULT, *LPNET_ITS_PLATE_RESULT;

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
typedef BOOL(CALLBACK *MSGCallBack_V31)(LONG lCommand, NET_DVR_ALARMER* pAlarmer, char* pAlarmInfo, DWORD dwBufLen, void* pUser)

