// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SPLATE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SPLATE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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
#define MAX_CAR_COUNT 10  //�����������
#define MAX_VIDEO_CHANNEL_COUNT 16  //���ͨ����
#define MAX_AREA_COUNT 32    //���ʶ������
#define MAX_NOZZLE_COUNT 32  //�����ǹ��


#define SUCCESS 0             //�ɹ�
#define FAIL    -1            //ʧ��
#define INVALID_VIDEO_COUNT  -1//���������Ƶͨ����
#define INVALID_AREA_COUNT -3 //������ǹ��
#define INVALID_CAR_COUNT -2  //��������
#define INVALID_LENTH -4      //���볤�ȴ���  
#define INVALID_NOZZLE_COUNT -5  //������ǹ��
//int WM_CARDATA = RegisterWindowMessage(_T("CARDATA"));
int WM_CARDATA = ::RegisterWindowMessageA("CARDATA");
int WM_VIDEOCAR = ::RegisterWindowMessageA("VIDEOCAR");
int WM_AREACAR = ::RegisterWindowMessageA("AREACAR");
typedef struct tagPlayInfo
{
	LONG nPort;
	LONG lPlayHandle;
	int nVideoChan;
	NET_DVR_PREVIEWINFO previewInfo;
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
	char license[16];	// �����ַ���
	char color[8];		// ������ɫ
	int nColor;			// ������ɫ
	int nType;			// ��������
	int nConfidence;	// ���ƿ��Ŷ�
	int nCarColor;		//������ɫ
	int nCarLogo;         //����Ʒ��
	int nSubCarLogo;      //������Ʒ��
	int nCarModel;			//��������
	int nVideoChannel;  //ʶ��ͼƬͨ��
	int nAreaNo;      //ʶ������
	int nPicType;       //ͼƬ����
	int nPicWidth;
	int nPicHeight;
	int nPicLenth;
	//char pic[MAX_PIC_LENTH];
	
} struSingleCarInfoOut;

typedef struct
{
	char license[16];	// �����ַ���
	char color[8];		// ������ɫ
	int nColor;			// ������ɫ
	int nType;			// ��������
	int nConfidence;	// ���ƿ��Ŷ�
	int nCarColor;		//������ɫ
	int nCarLogo;         //����Ʒ��
	int nSubCarLogo;      //������Ʒ��
	int nCarModel;			//��������
	int nAreaNo;      //
} struLicense;
typedef struct
{
	int nLicenseCount;
	int nVideoChannel;  //ʶ��ͼƬͨ��
	int nPicType;       //ͼƬ����
	int nPicWidth;
	int nPicHeight;
	int nPicLenth;
	struLicense license[8];
	char pic[MAX_PIC_LENTH];
} struMultiCarInfoOut;


typedef struct
{
	int areaNo;
	LONG videoChanNo;
	TH_RECT th_rect;
	int areaFlag;
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
	int nVideoType;  //1���͵���0��ڣ�99���� 
	int nAreaCount;
	struAreaInfo areas[8];
}struVideoInfo;
int SwithNextArea(void);
bool YV12_to_RGB24(unsigned char* pYV12, unsigned char* pRGB24, int iWidth, int iHeight);
void CALLBACK DecCBFun(long nPort, char *pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2);
void CALLBACK RealDataCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);
void CALLBACK PlateDataCallBack(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void *pUser);
void CALLBACK RealDataCallBack_MultiChan(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);
void CALLBACK DecCBFun_MultiChan(long nPort, char *pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2);

extern "C" SPLATE_API int SP_InitRunParam(BYTE *pChan,int areaCount);
extern "C" SPLATE_API int SP_InitRunParam_Nozzle(unsigned char *pNozzleInfo, int nozzleCount);
extern "C" SPLATE_API int SP_InitRunParam_Video(unsigned char *pVideoInfo, int videoCount);
extern "C" SPLATE_API int SP_InitNVR(char *IpAddress,LONG nPort,char *sAdmin,char *sPassword);
extern "C" SPLATE_API int SP_GetNvrCfg(NET_DVR_IPPARACFG_V40 *nvrCfg,int &lenth);
extern "C" SPLATE_API int SP_Close();
extern "C" SPLATE_API int SP_PreviewInfo(NET_DVR_PREVIEWINFO *preInfo,int lenth);
extern "C" SPLATE_API int SP_StopPreview(LONG lplayHandle);
extern "C" SPLATE_API int SP_BeginRecog();
extern "C" SPLATE_API int SP_InitAlg(TH_PlateIDCfg *th_plateIDCfg,int lenth);
extern "C" SPLATE_API int SP_TestAPI();
extern "C" SPLATE_API int SP_GetCarCount();
extern "C" SPLATE_API int SP_GetFirstCarInfo(struSingleCarInfoOut *carinfo,int &lenth);
extern "C" SPLATE_API int SP_GetCarInfo(struSingleCarInfoOut *carinfo,int carCount,int &lenth);
extern "C" SPLATE_API int SP_GetAreaCarInfo(struSingleCarInfoOut *carinfo, int areaNo);
extern "C" SPLATE_API int SP_GetNvrStatus();
extern "C" SPLATE_API int SP_SetLogLevel(int loglevel);
extern "C" SPLATE_API int SP_SetSwitchCount(int frameCount);
extern "C" SPLATE_API int SP_Snap(int videoChan, char *lic, unsigned char * picBuffer, int &picLenth);
extern "C" SPLATE_API int SP_Capture(int areaNo, struSingleCarInfoOut *carinfo);
extern "C" SPLATE_API int SP_Capture_V2(int nozzleNo, struMultiCarInfoOut *carInfo);
extern "C" SPLATE_API int SP_DecJpeg(const unsigned char * pJpegPic, int nJpegLenth, char *license);
extern "C" SPLATE_API int SP_InitNVR_HKCN(char *IpAddress, LONG nPort, char *sAdmin, char *sPassword);







