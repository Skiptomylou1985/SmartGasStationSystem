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

#include <WINSOCK2.H>

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
typedef struct
{
	BYTE sSerialNumber[SERIALNO_LEN];  //���к�
	BYTE byAlarmInPortNum;                //�����������
	BYTE byAlarmOutPortNum;                //�����������
	BYTE byDiskNum;                    //Ӳ�̸���
	BYTE byDVRType;                    //�豸����, 1:DVR 2:ATM DVR 3:DVS ......
	BYTE byChanNum;                    //ģ��ͨ������
	BYTE byStartChan;                    //��ʼͨ����,����DVS-1,DVR - 1
	BYTE byAudioChanNum;                //����ͨ����
	BYTE byIPChanNum;                    //�������ͨ����������λ  
	BYTE byZeroChanNum;            //��ͨ��������� //2010-01-16
	BYTE byMainProto;            //����������Э������ 0-private, 1-rtsp,2-ͬʱ֧��private��rtsp
	BYTE bySubProto;                //����������Э������0-private, 1-rtsp,2-ͬʱ֧��private��rtsp
	BYTE bySupport;        //������λ����Ϊ0��ʾ��֧�֣�1��ʾ֧�֣�
						   //bySupport & 0x1, ��ʾ�Ƿ�֧����������
						   //bySupport & 0x2, ��ʾ�Ƿ�֧�ֱ���
						   //bySupport & 0x4, ��ʾ�Ƿ�֧��ѹ������������ȡ
						   //bySupport & 0x8, ��ʾ�Ƿ�֧�ֶ�����
						   //bySupport & 0x10, ��ʾ֧��Զ��SADP
						   //bySupport & 0x20, ��ʾ֧��Raid������
						   //bySupport & 0x40, ��ʾ֧��IPSAN Ŀ¼����
						   //bySupport & 0x80, ��ʾ֧��rtp over rtsp
	BYTE bySupport1;        // ���������䣬λ����Ϊ0��ʾ��֧�֣�1��ʾ֧��
							//bySupport1 & 0x1, ��ʾ�Ƿ�֧��snmp v30
							//bySupport1 & 0x2, ֧�����ֻطź�����
							//bySupport1 & 0x4, �Ƿ�֧�ֲ������ȼ�    
							//bySupport1 & 0x8, �����豸�Ƿ�֧�ֲ���ʱ�����չ
							//bySupport1 & 0x10, ��ʾ�Ƿ�֧�ֶ������������33����
							//bySupport1 & 0x20, ��ʾ�Ƿ�֧��rtsp over http    
							//bySupport1 & 0x80, ��ʾ�Ƿ�֧�ֳ����±�����Ϣ2012-9-28, �һ���ʾ�Ƿ�֧��NET_DVR_IPPARACFG_V40�ṹ��
	BYTE bySupport2; /*������λ����Ϊ0��ʾ��֧�֣���0��ʾ֧��
					 bySupport2 & 0x1, ��ʾ�������Ƿ�֧��ͨ��URLȡ������
					 bySupport2 & 0x2,  ��ʾ֧��FTPV40
					 bySupport2 & 0x4,  ��ʾ֧��ANR
					 bySupport2 & 0x8,  ��ʾ֧��CCD��ͨ����������
					 bySupport2 & 0x10,  ��ʾ֧�ֲ��������ش���Ϣ����֧��ץ�Ļ����� ���ϱ����ṹ��
					 bySupport2 & 0x20,  ��ʾ�Ƿ�֧�ֵ�����ȡ�豸״̬����
					 bySupport2 & 0x40,  ��ʾ�Ƿ������������豸*/
	WORD wDevType;              //�豸�ͺ�
	BYTE bySupport3; //��������չ��λ����Ϊ0��ʾ��֧�֣�1��ʾ֧��
					 //bySupport3 & 0x1, ��ʾ�Ƿ������
					 // bySupport3 & 0x4 ��ʾ֧�ְ������ã� ������� ͨ��ͼ��������������������IP�������롢������������
					 // �û��������豸����״̬��JPEGץͼ����ʱ��ʱ��ץͼ��Ӳ��������� 
					 //bySupport3 & 0x8Ϊ1 ��ʾ֧��ʹ��TCPԤ����UDPԤ�����ಥԤ���е�"��ʱԤ��"�ֶ���������ʱԤ������������ʹ�����ַ�ʽ������ʱԤ����������bySupport3 & 0x8Ϊ0ʱ����ʹ�� "˽����ʱԤ��"Э�顣
					 //bySupport3 & 0x10 ��ʾ֧��"��ȡ����������Ҫ״̬��V40��"��
					 //bySupport3 & 0x20 ��ʾ�Ƿ�֧��ͨ��DDNS��������ȡ��

	BYTE byMultiStreamProto;//�Ƿ�֧�ֶ�����,��λ��ʾ,0-��֧��,1-֧��,bit1-����3,bit2-����4,bit7-��������bit-8������
	BYTE byStartDChan;        //��ʼ����ͨ����,0��ʾ��Ч
	BYTE byStartDTalkChan;    //��ʼ���ֶԽ�ͨ���ţ�������ģ��Խ�ͨ���ţ�0��ʾ��Ч
	BYTE byHighDChanNum;        //����ͨ����������λ
	BYTE bySupport4;        //��������չ��λ����Ϊ0��ʾ��֧�֣�1��ʾ֧��
							//bySupport4 & 0x4��ʾ�Ƿ�֧��ƴ��ͳһ�ӿ�
							// bySupport4 & 0x80 ֧���豸�ϴ����ı���ʹ�ܡ���ʾ�жϵ��ýӿ��� NET_DVR_PDC_RULE_CFG_V42���� NET_DVR_PDC_RULE_CFG_V41
	BYTE byLanguageType;// ֧����������,��λ��ʾ,ÿһλ0-��֧��,1-֧��  
						//  byLanguageType ����0 ��ʾ ���豸
						//  byLanguageType & 0x1��ʾ֧������
						//  byLanguageType & 0x2��ʾ֧��Ӣ��
	BYTE byVoiceInChanNum;   //��Ƶ����ͨ���� 
	BYTE byStartVoiceInChanNo; //��Ƶ������ʼͨ���� 0��ʾ��Ч
	BYTE  bySupport5;  //��λ��ʾ,0-��֧��,1-֧��,bit0-֧�ֶ�����
					   //bySupport5 &0x01��ʾ֧��wEventTypeEx ,����dwEventType ���¼����ͣ�֧����Ϊ�¼���չ��--��ռס����ֹ��ͻ
					   //bySupport5 &0x04��ʾ�Ƿ�֧��ʹ����չ�ĳ���ģʽ�ӿ�
					   /*
					   bySupport5 &0x08 �豸���ظ�ֵ��ʾ�Ƿ�֧�ּƻ�¼������V40�ӿ�Э��(DVR_SET_RECORDCFG_V40/ DVR_GET_RECORDCFG_V40)(�ڸ�Э�����豸֧����������13������)
					   ֮ǰ�Ĳ��ַ������豸��֧��¼������13��������¼������13�������֧�֣�ͳһת����¼������3���ݴ���SDKͨ������̽�⴦��)
					   */
	BYTE  bySupport6;   //��������λ��ʾ��0-��֧��,1-֧��
						//bySupport6 0x1  ��ʾ�豸�Ƿ�֧��ѹ�� 
						//bySupport6 0x2 ��ʾ�Ƿ�֧����ID��ʽ��������Դ��չ���DVR_SET_STREAM_SRC_INFO_V40
						//bySupport6 0x4 ��ʾ�Ƿ�֧���¼�����V40�ӿ�
						//bySupport6 0x8 ��ʾ�Ƿ�֧����չ���������������
						//bySupport6 0x40��ʾͼƬ��ѯ���V40��չ
	BYTE  byMirrorChanNum;    //����ͨ��������<¼�����������ڱ�ʾ����ͨ��>
	WORD wStartMirrorChanNo;  //��ʼ����ͨ����
	BYTE bySupport7;   //����,��λ��ʾ,0-��֧��,1-֧��
					   // bySupport7 & 0x1  ��ʾ�豸�Ƿ�֧�� INTER_VCA_RULECFG_V42 ��չ
					   // bySupport7 & 0x2  ��ʾ�豸�Ƿ�֧�� IPC HVT ģʽ��չ
					   // bySupport7 & 0x04  ��ʾ�豸�Ƿ�֧�� ��������ʱ��
					   // bySupport7 & 0x08  ��ʾ������̨PTZλ��ʱ���Ƿ�֧�ִ�ͨ����
					   // bySupport7 & 0x10  ��ʾ�豸�Ƿ�֧��˫ϵͳ��������
					   // bySupport7 & 0x20  ��ʾ�豸�Ƿ�֧�� OSD�ַ����� V50
					   // bySupport7 & 0x40  ��ʾ�豸�Ƿ�֧�� ���Ӹ��٣����������
					   // bySupport7 & 0x80  ��ʾ�豸�Ƿ�֧�� ���ļ���
	BYTE  byRes2;        //����
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
	NET_DVR_MANUALSNAP const* lpInter,
	LPNET_DVR_PLATE_RESULT lpOuter
);
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
extern "C" HCNETSDK_API void NET_DVR_TestAPI();
void _stdcall ThreadFuncRecv(LPVOID lpParam);
SOCKET getSocketConnect(char *hostIP, int port);
