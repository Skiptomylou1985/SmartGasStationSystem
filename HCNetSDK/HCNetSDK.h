// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� HCNETSDK_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// HCNETSDK_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef HCNETSDK_EXPORTS
#define HCNETSDK_API __declspec(dllexport)
#else
#define HCNETSDK_API __declspec(dllimport)
#endif
#define MAX_LICENSE_LEN 16
#define SERIALNO_LEN		    48      //���кų���
#define MACADDR_LEN			    6       //mac��ַ����
#define NAME_LEN			    32      //�û�������
typedef struct tagNET_DVR_MANUALSNAP
{
	BYTE   byPumpID;//��ǹ�� ��0-����Ч����
	BYTE   byPumpStatus;//��ǹ״̬ ��0-����Ч��1-������2-��ʼ���ͣ�3-��ǹ��   		
}NET_DVR_MANUALSNAP, *LPNET_DVR_MANUALSNAP;
typedef struct tagNET_ITS_PLATE_RESULT
{
	char sLicense[MAX_LICENSE_LEN];		//���ƺ���
	BYTE byPlateColor;					//������ɫ
	BYTE byColor;						///����ɫ
	WORD wVehicleLogoRecog;				///��Ʒ��
	WORD	wVehicleSubLogoRecog;			///��Ʒ��
	BYTE	byVehicleShape;					///����
}NET_ITS_PLATE_RESULT, *LPNET_ITS_PLATE_RESULT;

//�ֶ�ץ�Ĵ����ṹ��:
typedef struct tagNET_DVR_PLATE_RESULT
{
	char sLicense[MAX_LICENSE_LEN];		//���ƺ���
	BYTE byPlateColor;					//������ɫ
	BYTE byColor;							///����ɫ
	WORD wVehicleLogoRecog;				///��Ʒ��
	WORD wVehicleSubLogoRecog;				///��Ʒ��
	BYTE byVehicleShape;					///����
	BYTE byPumpID;						///��ǹID
	BYTE byPumpStatus;					///��ǹ״̬
}NET_DVR_PLATE_RESULT, *LPNET_DVR_PLATE_RESULT;
//�����豸��Ϣ
typedef struct
{
	BYTE byUserIDValid;                 /* userid�Ƿ���Ч 0-��Ч��1-��Ч */
	BYTE bySerialValid;                 /* ���к��Ƿ���Ч 0-��Ч��1-��Ч */
	BYTE byVersionValid;                /* �汾���Ƿ���Ч 0-��Ч��1-��Ч */
	BYTE byDeviceNameValid;             /* �豸�����Ƿ���Ч 0-��Ч��1-��Ч */
	BYTE byMacAddrValid;                /* MAC��ַ�Ƿ���Ч 0-��Ч��1-��Ч */
	BYTE byLinkPortValid;               /* login�˿��Ƿ���Ч 0-��Ч��1-��Ч */
	BYTE byDeviceIPValid;               /* �豸IP�Ƿ���Ч 0-��Ч��1-��Ч */
	BYTE bySocketIPValid;               /* socket ip�Ƿ���Ч 0-��Ч��1-��Ч */
	LONG lUserID;                       /* NET_DVR_Login()����ֵ, ����ʱ��Ч */
	BYTE sSerialNumber[SERIALNO_LEN];    /* ���к� */
	DWORD dwDeviceVersion;                /* �汾��Ϣ ��16λ��ʾ���汾����16λ��ʾ�ΰ汾*/
	char sDeviceName[NAME_LEN];            /* �豸���� */
	BYTE byMacAddr[MACADDR_LEN];        /* MAC��ַ */
	WORD wLinkPort;                     /* link port */
	char sDeviceIP[128];                /* IP��ַ */
	char sSocketIP[128];                /* ���������ϴ�ʱ��socket IP��ַ */
	BYTE byIpProtocol;                  /* IpЭ�� 0-IPV4, 1-IPV6 */
	BYTE byRes2[11];
}NET_DVR_ALARMER, *LPNET_DVR_ALARMER;
typedef BOOL(CALLBACK *MSGCallBack_V31)(LONG lCommand, NET_DVR_ALARMER* pAlarmer, char* pAlarmInfo, DWORD dwBufLen, void* pUser)

