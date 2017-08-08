// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SPLATE_XJ_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SPLATE_XJ_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef SPLATE_XJ_EXPORTS
#define SPLATE_API __declspec(dllexport)
#else
#define SPLATE_API __declspec(dllimport)
#endif
#pragma comment(lib,"ws2_32.lib")
#include "log.h"
#include <WINSOCK2.H>
#include "cJSON.h"
// �����Ǵ� SPlate_xj.dll ������

//#define  MAX_LOGFILE_LENTH 10*1024*1024
#define MAX_FILE_SIZE (50*1024*1024) 
#define MAX_PIC_LENTH (10*1024*1024)
#define MAX_CAR_COUNT 10  //�����������
#define MAX_VIDEO_CHANNEL_COUNT 16  //���ͨ����
#define MAX_AREA_COUNT 64    //���ʶ������
#define MAX_NOZZLE_COUNT 32  //�����ǹ��


#define SUCCESS 0             //�ɹ�
#define FAIL    -1            //ʧ��
#define INVALID_METHOD -100   //��֧�ֵķ���
#define INVALID_VIDEO_COUNT  -1//���������Ƶͨ����
#define INVALID_AREA_COUNT -3 //������ǹ��
#define INVALID_CAR_COUNT -2  //��������
#define INVALID_LENTH -4      //���볤�ȴ���  
#define INVALID_NOZZLE_COUNT -5  //������ǹ��
//int WM_CARDATA = RegisterWindowMessage(_T("CARDATA"));
int WM_CARDATA = ::RegisterWindowMessageA("CARDATA");
int WM_VIDEOCAR = ::RegisterWindowMessageA("VIDEOCAR");
int WM_AREACAR = ::RegisterWindowMessageA("AREACAR");

typedef struct TH_RECT
{
	int left;
	int top;
	int right;
	int bottom;
}TH_RECT;
typedef struct tagStationIOInfo
{
	char plateNo[15];
	char plateColor[10];
	int nImageWidth;
	int nImageHeight;
	TH_RECT rect;
	char carBrand[20];
	char subCarBrand[20];
	char moveStatus[5];
	char imagePath[50];
	char token[50];
	char cameraCode[30];
	char cameraType[5];
	char stationCode[30];
	char timestamp[20];
	char detectionArea[20];
	char remark[100];
}StationIOInfo;
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
	int videoLaneNo;  //��Ƶͨ���е�ʶ������
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
extern "C" SPLATE_API int SP_Capture(int nozzleNo, struMultiCarInfoOut *carInfo);

