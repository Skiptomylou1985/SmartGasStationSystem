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
#define FILE_MAX_SIZE (10*1024*1024) 
#define PIC_MAX_LENTH (10*1024*1024)
#define MAX_CAR_COUNT 10  //�����������
#define MAX_VIDEO_CHANNEL_COUNT 16  //���ͨ����


#define SUCCESS 0             //�ɹ�
#define FAIL    -1            //ʧ��
#define INVALID_VIDEO_COUNT  -1//���������Ƶͨ����
#define INVALID_CAR_COUNT -2  //��������
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
}NVRInfo;
typedef struct tagVideoChanInfo
{
	char *NvrIP;
	LONG nChannel;
};
typedef struct
{
	char license[16];	// �����ַ���
	char color[8];		// ������ɫ
	int nColor;			// ������ɫ
	int nType;			// ��������
	int nConfidence;	// ���ƿ��Ŷ�
	int nCarColor;		//������ɫ
	int nCarLogo;         //��������
	int nCarType;			//�������ͣ�������
	int nVideoChannel;  //ʶ��ͼƬͨ��
	int nPicType;       //ͼƬ����
	int nPicLenth;
	char pic[PIC_MAX_LENTH];
	
} CarInfoOut;
bool YV12_to_RGB24(unsigned char* pYV12, unsigned char* pRGB24, int iWidth, int iHeight);
void CALLBACK DecCBFun(long nPort, char *pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2);
void CALLBACK RealDataCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser);
extern "C" SPLATE_API int SP_InitRunParam(BYTE *pChan,int lenth);
extern "C" SPLATE_API int SP_InitNVR(char *IpAddress,LONG nPort,char *sAdmin,char *sPassword);
extern "C" SPLATE_API int SP_PreviewInfo(NET_DVR_PREVIEWINFO *preInfo);
extern "C" SPLATE_API int SP_InitAlg(TH_PlateIDCfg *th_plateIDCfg);
extern "C" SPLATE_API int SP_TestAPI();
extern "C" SPLATE_API int SP_GetCarCount();
extern "C" SPLATE_API int SP_GetFirstCarInfo(CarInfoOut *carinfo);
extern "C" SPLATE_API int SP_GetCarInfo(CarInfoOut *carinfo,int carCount);
extern "C" SPLATE_API int SP_GetNvrStatus();






