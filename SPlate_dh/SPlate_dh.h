#pragma once
// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 SPLATE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// SPLATE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef SPLATE_EXPORTS
#define SPLATE_API __declspec(dllexport)
#else
#define SPLATE_API  __declspec(dllimport)
#endif
#include "log.h"
#include "cmu_sdk.h"
#include "dmu_sdk.h"
#include "vtdu_sdk.h"
#include "player.h"
//#define  MAX_LOGFILE_LENTH 10*1024*1024
#define MAX_FILE_SIZE (10*1024*1024) 
#define MAX_PIC_LENTH (10*1024*1024)
#define MAX_CAR_COUNT 10  //缓存最大车辆数
#define MAX_VIDEO_CHANNEL_COUNT 16  //最多通道数
#define MAX_AREA_COUNT 32    //最大识别区数
#define MAX_NOZZLE_COUNT 32  //最多油枪数
#define MAX_OUTXML_LENTH 500;


#define SUCCESS 0             //成功
#define FAIL    -1            //失败
#define INVALID_VIDEO_COUNT  -1//超过最大视频通道数
#define INVALID_AREA_COUNT -3 //错误油枪数
#define INVALID_CAR_COUNT -2  //错误车辆数
#define INVALID_LENTH -4      //输入长度错误  
#define INVALID_NOZZLE_COUNT -5  //错误油枪数
//int WM_CARDATA = RegisterWindowMessage(_T("CARDATA"));
int WM_CARDATA = ::RegisterWindowMessageA("CARDATA");
int WM_VIDEOCAR = ::RegisterWindowMessageA("VIDEOCAR");
int WM_AREACAR = ::RegisterWindowMessageA("AREACAR");

typedef struct tagCMUInfo
{
	LONG cmuHandle;
	LONG userID;
	LONG domID;
}struCMUInfo;
typedef struct tagDMUInfo
{
	int domID;
	int svrID;
	int accNum;  //接入能力
	int adapNum; //转发能力
	char *ipInfo;
}struDMUInfo;
typedef struct tagPlayInfo
{
	LONG nPort;
	LONG lPlayHandle;
	int nVideoChan;
	//NET_DVR_PREVIEWINFO previewInfo;
}struPlayInfo;
typedef struct tagNVRInfo
{
	char *IpAddress;
	char *sAdmin;
	char *sPassword;
	LONG nPort;
	unsigned char nChanelNum;
	unsigned char ConnectStatus;
	LONG m_lServerID;
	LONG m_lAlarmHandle;
	LONG m_lPlayHandle;
	BOOLEAN m_bLocalRecord;
}struNVRInfo;

typedef struct
{
	char license[16];	// 车牌字符串
	char color[8];		// 车牌颜色
	int nColor;			// 车牌颜色
	int nType;			// 车牌类型
	int nConfidence;	// 整牌可信度
	int nCarColor;		//车的颜色
	int nCarLogo;         //车辆品牌
	int nSubCarLogo;      //车辆子品牌
	int nCarModel;			//车辆类型
	int nVideoChannel;  //识别图片通道
	int nAreaNo;      //识别区号
	int nPicType;       //图片类型
	int nPicWidth;
	int nPicHeight;
	int nPicLenth;
	//char pic[MAX_PIC_LENTH];

} struSingleCarInfoOut;

typedef struct
{
	char license[16];	// 车牌字符串
	char color[8];		// 车牌颜色
	int nColor;			// 车牌颜色
	int nType;			// 车牌类型
	int nConfidence;	// 整牌可信度
	int nCarColor;		//车的颜色
	int nCarLogo;         //车辆品牌
	int nSubCarLogo;      //车辆子品牌
	int nCarModel;			//车辆类型
	int nAreaNo;      //
} struLicense;
typedef struct
{
	int nLicenseCount;
	int nVideoChannel;  //识别图片通道
	int nPicType;       //图片类型
	int nPicWidth;
	int nPicHeight;
	int nPicLenth;
	struLicense license[8];
	char pic[MAX_PIC_LENTH];
} struMultiCarInfoOut;

typedef struct TH_RECT
{
	int left;
	int top;
	int right;
	int bottom;
}TH_RECT;
typedef struct
{
	int areaNo;
	LONG videoChanNo;
	TH_RECT th_rect;
	int videoLaneNo;  //视频通道中的识别区号
} struAreaInfo;
typedef struct
{
	int nozzleNo;
	int videoChan;
	int areaCount;
	struAreaInfo areas[8];
}struNozzleInfo;
typedef struct tagVideoChanInfo
{
	int nChanNo;
	int nVideoType;  //1，油岛，0入口，99出口 
	int nAreaCount;
	struAreaInfo areas[8];
}struVideoInfo;
extern "C" SPLATE_API int SP_InitRunParam(BYTE *pChan, int areaCount);
extern "C" SPLATE_API int SP_InitRunParam_Nozzle(unsigned char *pNozzleInfo, int nozzleCount);
extern "C" SPLATE_API int SP_InitRunParam_Video(unsigned char *pVideoInfo, int videoCount);
extern "C" SPLATE_API int SP_InitNVR(char *IpAddress, LONG nPort, char *sAdmin, char *sPassword);
extern "C" SPLATE_API int SP_GetNvrCfg(BYTE *nvrCfg, int &lenth);
extern "C" SPLATE_API int SP_Close();
extern "C" SPLATE_API int SP_PreviewInfo(BYTE *preInfo, int lenth);
extern "C" SPLATE_API int SP_StopPreview(LONG lplayHandle);
extern "C" SPLATE_API int SP_BeginRecog();
extern "C" SPLATE_API int SP_InitAlg(BYTE *th_plateIDCfg, int lenth);
extern "C" SPLATE_API int SP_TestAPI();
extern "C" SPLATE_API int SP_GetCarCount();
extern "C" SPLATE_API int SP_GetFirstCarInfo(struSingleCarInfoOut *carinfo, int &lenth);
extern "C" SPLATE_API int SP_GetCarInfo(struSingleCarInfoOut *carinfo, int carCount, int &lenth);
extern "C" SPLATE_API int SP_GetAreaCarInfo(struSingleCarInfoOut *carinfo, int areaNo);
extern "C" SPLATE_API int SP_GetNvrStatus();
extern "C" SPLATE_API int SP_SetLogLevel(int loglevel);
extern "C" SPLATE_API int SP_SetSwitchCount(int frameCount);
extern "C" SPLATE_API int SP_Snap(int videoChan, char *lic, unsigned char * picBuffer, int &picLenth);
extern "C" SPLATE_API int SP_Capture(int areaNo, struSingleCarInfoOut *carinfo);
extern "C" SPLATE_API int SP_Capture_V2(int nozzleNo, struMultiCarInfoOut *carInfo);
extern "C" SPLATE_API int SP_DecJpeg(const unsigned char * pJpegPic, int nJpegLenth, char *license);
extern "C" SPLATE_API int SP_InitNVR_HKCN(char *IpAddress, LONG nPort, char *sAdmin, char *sPassword);