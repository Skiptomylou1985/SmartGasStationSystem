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
#include "TH_ErrorDef.h"
#include "TH_PlateID.h"
#include "DataType.h"
#include "HCNetSDK.h"
#include "plaympeg4.h"
#include "log.h"


//#define  MAX_LOGFILE_LENTH 10*1024*1024
#define MAX_FILE_SIZE (10*1024*1024) 
#define MAX_PIC_LENTH (10*1024*1024)
#define MAX_CAR_COUNT 10  //缓存最大车辆数
#define MAX_VIDEO_CHANNEL_COUNT 16  //最多通道数
#define MAX_AREA_COUNT 32    //最大油枪数


#define SUCCESS 0             //成功
#define FAIL    -1            //失败
#define INVALID_VIDEO_COUNT  -1//超过最大视频通道数
#define INVALID_AREA_COUNT -3 //错误油枪数
#define INVALID_CAR_COUNT -2  //错误车辆数
#define INVALID_LENTH -4      //输入长度错误
//int WM_CARDATA = RegisterWindowMessage(_T("CARDATA"));
int WM_CARDATA = ::RegisterWindowMessageA("CAR");
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
typedef struct tagVideoChanInfo
{
	char *NvrIP;
	LONG nChannel;
};
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
	char pic[MAX_PIC_LENTH];
	
} struCarInfoOut;



typedef struct
{
	int areaNo;
	LONG videoChanNo;
	TH_RECT th_rect;
	int areaFlag;
} struAreaInfo;
int SwithNextArea(void);
bool YV12_to_RGB24(unsigned char* pYV12, unsigned char* pRGB24, int iWidth, int iHeight);
void CALLBACK DecCBFun(long nPort, char *pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2);
void CALLBACK RealDataCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);
extern "C" SPLATE_API int SP_InitRunParam(BYTE *pChan,int lenth);
extern "C" SPLATE_API int SP_InitNVR(char *IpAddress,LONG nPort,char *sAdmin,char *sPassword);
extern "C" SPLATE_API int SP_GetNvrCfg(NET_DVR_IPPARACFG_V40 *nvrCfg,int &lenth);
extern "C" SPLATE_API int SP_Close();
extern "C" SPLATE_API int SP_PreviewInfo(NET_DVR_PREVIEWINFO *preInfo,int lenth);
extern "C" SPLATE_API int SP_BeginRecog(HWND hPlayHandle);
extern "C" SPLATE_API int SP_InitAlg(TH_PlateIDCfg *th_plateIDCfg,int lenth);
extern "C" SPLATE_API int SP_TestAPI();
extern "C" SPLATE_API int SP_GetCarCount();
extern "C" SPLATE_API int SP_GetFirstCarInfo(struCarInfoOut *carinfo,int &lenth);
extern "C" SPLATE_API int SP_GetCarInfo(struCarInfoOut *carinfo,int carCount,int &lenth);
extern "C" SPLATE_API int SP_GetNvrStatus();
extern "C" SPLATE_API int SP_SetLogLevel(int loglevel);
extern "C" SPLATE_API int SP_SetSwitchCount(int frameCount);
extern "C" SPLATE_API int SP_Snap(int videoChan, char *lic, unsigned char * picBuffer, int &picLenth);
extern "C" SPLATE_API int SP_Capture(int videoChan, struCarInfoOut *carinfo);
extern "C" SPLATE_API int SP_DecJpeg(const unsigned char * pJpegPic, int nJpegLenth, char *license);







