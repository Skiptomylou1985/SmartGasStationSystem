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
#define COMM_ITS_PLATE_RESULT     0x3050  //�Զ�ץ�ĳ�����Ϣ�ϴ�


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
	BYTE	byVehicleState;              //����վ��ʶ 1��վ 2��վ
}NET_ITS_PLATE_RESULT, *LPNET_ITS_PLATE_RESULT;

typedef struct tagNET_ITS_TRANS_INFO
{
	int nPumpID;	              //��ǹID
	int nItemCode;			 //��Ʒ����
	float fTransVolume;		 //��������
	float fTransValue;		 //���׽��
	float fTransPrice;		 //���׵���
	char sStartTime[20];        //��ǹʱ��
	char sEndTime[20];		 //��ǹʱ��
	float fPumpOpenCounter;     //��ǹ����
	float fPumpCloseCounter;    //��ǹ����
}NET_ITS_TRANS_INFO, *LPNET_ITS_TRANS_INFO;


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
	VCA_BLUE_PLATE = 0,   //��ɫ����
	VCA_YELLOW_PLATE,      //��ɫ����
	VCA_WHITE_PLATE,       //��ɫ����
	VCA_BLACK_PLATE,       //��ɫ����
	VCA_GREEN_PLATE,       //��ɫ����
	VCA_BKAIR_PLATE,       //�񺽺�ɫ����
	VCA_OTHER = 0xff       //����
}VCA_PLATE_COLOR;

//��������
typedef enum _VCA_PLATE_TYPE_
{
	VCA_STANDARD92_PLATE = 0,    //��׼���ó������
	VCA_STANDARD02_PLATE,        //02ʽ���ó��� 
	VCA_WJPOLICE_PLATE,            //�侯�� 
	VCA_JINGCHE_PLATE,            //����
	STANDARD92_BACK_PLATE,         //���ó�˫��β��
	VCA_SHIGUAN_PLATE,          //ʹ�ݳ���
	VCA_NONGYONG_PLATE,         //ũ�ó�
	VCA_MOTO_PLATE              //Ħ�г�
}VCA_PLATE_TYPE;

//����ʶ����
typedef enum _VTR_RESULT
{
	VTR_RESULT_OTHER = 0,  //δ֪
	VTR_RESULT_BUS = 1,  //�ͳ�
	VTR_RESULT_TRUCK = 2,  //����
	VTR_RESULT_CAR = 3,  //�γ�
	VTR_RESULT_MINIBUS = 4,  //�����
	VTR_RESULT_SMALLTRUCK = 5,  //С����
	VTR_RESULT_HUMAN = 6,  //����
	VTR_RESULT_TUMBREL = 7,  //���ֳ�
	VTR_RESULT_TRIKE = 8,  //���ֳ�
	VTR_RESULT_SUV_MPV = 9,  //SUV/MPV
	VTR_RESULT_MEDIUM_BUS = 10,  //���Ϳͳ�
	VTR_RESULT_MOTOR_VEHICLE = 11, //������
	VTR_RESULT_NON_MOTOR_VEHICLE = 12,  //�ǻ�����
	VTR_RESULT_SMALLCAR = 13,   //С�ͽγ�
	VTR_RESULT_MICROCAR = 14,   //΢�ͽγ�
	VTR_RESULT_PICKUP = 15    //Ƥ����
}VTR_RESULT;


//������ɫ
typedef enum _VCR_CLR_CLASS
{
	VCR_CLR_UNSUPPORT = 0,      //��֧��
	VCR_CLR_WHITE = 1,   //��
	VCR_CLR_SILVER = 2,   //��
	VCR_CLR_GRAY = 3,      //��
	VCR_CLR_BLACK = 4,      //��
	VCR_CLR_RED = 5,      //��
	VCR_CLR_DARKBLUE = 6,      //����
	VCR_CLR_BLUE = 7,      //��
	VCR_CLR_YELLOW = 8,      //��
	VCR_CLR_GREEN = 9,      //��
	VCR_CLR_BROWN = 10,  //��
	VCR_CLR_PINK = 11,  //��
	VCR_CLR_PURPLE = 12,  //��
	VCR_CLR_DARKGRAY = 13,  //���
	VCR_CLR_CYAN = 14  //��ɫ
}VCR_CLR_CLASS;

//������������ 2013-11-04
typedef enum _VCA_OPERATE_TYPE_
{
	VCA_LICENSE_TYPE = 0x1,  //���ƺ���
	VCA_PLATECOLOR_TYPE = 0x2,  //������ɫ
	VCA_CARDNO_TYPE = 0x4,  //����
	VCA_PLATETYPE_TYPE = 0x8,  //��������
	VCA_LISTTYPE_TYPE = 0x10, //������������
	VCA_INDEX_TYPE = 0x20, //������ˮ�� 2014-02-25
	VCA_OPERATE_INDEX_TYPE = 0x40  //������ 2014-03-03
}VCA_OPERATE_TYPE;

typedef enum _VCA_ILLEGAL_TYPE_
{
	VCA_POSTPIC_TYPE = 0x1, //����ͼƬ
	VCA_LOWSPEED_TYPE = 0x2,  //����
	VCA_HIGHSPEED_TYPE = 0x4,  //����
	VCA_RETROGRADE_TYPE = 0x8,  //����
	VCA_RUSH_REDLIGHT_TYPE = 0x10,   //�����
	VCA_PRESS_LANE_TYPE = 0x20, //ѹ������
	VCA_VIOLATE_GUIDE_TYPE = 0x40,//��������
	VCA_ROAD_STRAND_TYPE = 0x80,//·������(�豸��֧��)
	VCA_VEHICLE_ILLEGAL_LANE_TYPE = 0x100,//��ռ��
	VCA_ILLEGAL_LANE_CHANGE_TYPE = 0x200,//Υ�����
	VCA_ILLEGAL_LANE_DRIVE_TYPE = 0x400,//��������
	VCA_VIOLATE_BAN_TYPE = 0x800,//Υ������
	VCA_CROSS_PARKING_TYPE = 0x1000,//·��ͣ��
	VCA_GREEN_PARKING_TYPE = 0x2000//�̵�ͣ��
}VCA_ILLEGAL_TYPE;

typedef enum _VCA_VEHICLE_TYPE_
{
	VCA_OTHER_TYPE = 0x1,  //��������
	VCA_SMALLCAR_TYPE = 0x2,  //С�ͳ�
	VCA_BIGCAR_TYPE = 0x4,  //���ͳ�
	VCA_BUS_TYPE = 0x8,  //�ͳ�
	VCA_TRUCK_TYPE = 0x10,  //����
	VCA_CAR_TYPE = 0x20,   //�γ�
	VCA_MINIBUS_TYPE = 0x40,   //�����
	VCA_SMALL_TRUCK_TYPE = 0x80  //С����
}VCA_VEHICLE_TYPE;

//����Ʒ��������
typedef enum _VLR_VEHICLE_CLASS
{
	VLR_OTHER = 0,    //����
	VLR_VOLKSWAGEN = 1,    //����
	VLR_BUICK = 2,    //���
	VLR_BMW = 3,    //����
	VLR_HONDA = 4,    //����
	VLR_PEUGEOT = 5,    //����
	VLR_TOYOTA = 6,    //����
	VLR_FORD = 7,    //����
	VLR_NISSAN = 8,    //�ղ�
	VLR_AUDI = 9,    //�µ�
	VLR_MAZDA = 10,   //���Դ�
	VLR_CHEVROLET = 11,   //ѩ����
	VLR_CITROEN = 12,   //ѩ����
	VLR_HYUNDAI = 13,   //�ִ�
	VLR_CHERY = 14,   //����
	VLR_KIA = 15,   //����
	VLR_ROEWE = 16,   //����
	VLR_MITSUBISHI = 17,   //����
	VLR_SKODA = 18,   //˹�´�
	VLR_GEELY = 19,   //����
	VLR_ZHONGHUA = 20,   //�л�
	VLR_VOLVO = 21,   //�ֶ���
	VLR_LEXUS = 22,   //�׿���˹
	VLR_FIAT = 23,   //������
	VLR_EMGRAND = 24,   //�ۺ�(����)
	VLR_DONGFENG = 25,   //����
	VLR_BYD = 26,   //���ǵ�
	VLR_SUZUKI = 27,   //��ľ
	VLR_JINBEI = 28,   //��
	VLR_HAIMA = 29,   //����
	VLR_SGMW = 30,   //����
	VLR_JAC = 31,   //����
	VLR_SUBARU = 32,   //˹��³
	VLR_ENGLON = 33,   //Ӣ��(����)
	VLR_GREATWALL = 34,   //����
	VLR_HAFEI = 35,   //����
	VLR_ISUZU = 36,   //��ʮ��(����)
	VLR_SOUEAST = 37,   //����
	VLR_CHANA = 38,   //����
	VLR_FOTON = 39,   //����
	VLR_XIALI = 40,   //����(һ��)
	VLR_BENZ = 41,   //����
	VLR_FAW = 42,   //һ��
	VLR_NAVECO = 43,   //��ά��
	VLR_LIFAN = 44,   //����
	VLR_BESTURN = 45,   //һ������(һ��)
	VLR_CROWN = 46,   //�ʹ�(����)
	VLR_RENAULT = 47,   //��ŵ
	VLR_JMC = 48,   //JMC(����)
	VLR_MG = 49,   //MG����
	VLR_KAMA = 50,   //����
	VLR_ZOTYE = 51,   //��̩
	VLR_CHANGHE = 52,   //����
	VLR_XMKINGLONG = 53,   //���Ž���(����)
	VLR_HUIZHONG = 54,   //�Ϻ�����(��������)
	VLR_SZKINGLONG = 55,   //���ݽ���
	VLR_HIGER = 56,   //����
	VLR_YUTONG = 57,   //��ͨ
	VLR_CNHTC = 58,   //�й�����
	VLR_BEIBEN = 59,   //�����ؿ�
	VLR_XINGMA = 60,   //��������
	VLR_YUEJIN = 61,   //Ծ��
	VLR_HUANGHAI = 62,   //�ƺ�
	VLR_OLDWALL = 63,   //�Ͽ��
	VLR_CHANACOMMERCIAL = 64,   //��������
	VLR_PORSCHE = 65,               // ��ʱ��
	VLR_CADILLAC = 66,               // ��������
	VLR_INFINITI = 67,               // Ӣ�����
	VLR_GLEAGLE = 68,               // ����ȫ��ӥ(����)
	VLR_JEEP = 69,               // JEEP(����)
	VLR_LANDROVER = 70,               // ·��
	VLR_CHANGFENG = 71,               // ����
	VLR_BENNI = 72,               // ��������(����)
	VLR_ERA = 73,               // ����ʱ��(ʱ��)
	VLR_TAURUS = 74,               // ������ţ��(��������)
	VLR_EADO = 75,               // �����ݶ�
	VLR_SHANQI = 76,               // ����
	VLR_HONGYAN = 77,               // ��������(������ά�º���)
	VLR_DRAGON = 78,               // ��������(��������)
	VLR_JACTEXT = 79,               // ����JAC (����)
	VLR_JACBUS = 80,               // �����ִ��ͳ� (����)
	VLR_ANKAI = 81,               // �����ͳ�
	VLR_SHENLONG = 82,               // �����ͳ�
	VLR_DAEWOO = 83,               // ����ͳ�
	VLR_WUZHENG = 84,               // ��������
	VLR_MAN = 85,               // MAN����
	VLR_ZHONGTONG = 86,               // ��ͨ�ͳ�
	VLR_BAOJUN = 87,               // ����
	VLR_BQWEIWANG = 88,               // ��������
	VLR_TRUMPCHE = 89,               // ����
	VLR_LUFENG = 90,               // ½��
	VLR_HMZHENGZHOU = 91,               // ����֣��
	VLR_BEIJING = 92,               // ��������
	VLR_ZHONGSHUN = 93,               // ��˳
	VLR_WEILIN = 94,               // ��������
	VLR_OPEL = 95,               // ŷ��
	VLR_KARRY = 96,               // ����
	VLR_SMA = 97,               // ��������
	VLR_SMATEXT = 98,               // ������������SMA
	VLR_YUWIN = 99,               // ����Ԧʤ
	VLR_MINI = 100,               // ����MINI
	VLR_MARK = 101,               // ����MARKX 
	VLR_HAVAL = 102,               // ����HAVAL
	VLR_OGA = 103,               // ک��
	VLR_VENUCIA = 104,               // ����
	VLR_BYD2 = 105,               // ���ǵ���ʽ2 (���ǵ�)
	VLR_SMART = 106,               // ����SMART
	VLR_BAW = 107,               // �����������쳧BAW
	VLR_LUXGEN = 108,               // ���ǽ�
	VLR_YEMA = 109,               // Ұ��
	VLR_ZTE = 110,               // ����
	VLR_EVERUS = 111,               // ����
	VLR_CHRYSLER = 112,               // ����˹��
	VLR_GONOW = 113,               // ��������
	VLR_SHJIANG = 114,               // �ɻ���
	VLR_RUILIN = 115,               // ����
	VLR_FORTA = 116,               // ����
	VLR_GAGUAR = 117,               // �ݱ�
	VLR_HEIBAO = 118,               // �ڱ�
	VLR_TKING = 119,               // �ƿ�
	VLR_TKINGTEXT = 120,               // �ƿ�����
	VLR_FODAY = 121,               // ����
	VLR_LOTUS = 122,               // ��������
	VLR_NANJUN = 123,               // �Ͽ�
	VLR_SHUANGHUAN = 124,               // ˫������
	VLR_SAIBAO = 125,               // ��������
	VLR_HAWTAI = 126,               // ��̩
	VLR_LIFO = 127,               // ��Դ�ɵ�
	VLR_JONWAY = 128,               // ��Դ����
	VLR_FULONGMA = 129,               // ������
	VLR_WEILI = 130,               // Ϋ��
	VLR_ANCHI = 131,               // ��������
	VLR_PAIXI = 132,               // ��ϲ
	VLR_HIGERTEXT = 133,               // ����HIGER����
	VLR_RIYECAR = 134,               // ������Ұ�Ῠ
	VLR_RIYETRUCK = 135,               // ������Ұ�ؿ�
	VLR_JIANGNAN = 136,               // ����
	VLR_OLDZOTYE = 137,               // �Ͽ���̩
	VLR_OLDXIALI = 138,               // �Ͽ�����
	VLR_NEWAOCHI = 139,               // �°³�
	VLR_CDW = 140,               // ��������
	VLR_CDWTEXT = 141,               // ������������
	VLR_CIIMO = 142,               // ����˼��
	VLR_CHANADS = 143,               // �����а���
	VLR_DS = 144,               // ����
	VLR_ROHENS = 145,               // �ִ��Ͷ�˹����
	VLR_YANTAI = 146,               // ��̨
	VLR_SHUANGLONG = 147,               // ˫��
	VLR_FENGLING = 148,               // ʱ������
	VLR_XINKAI = 149,               // �¿�
	VLR_GMC = 150,               // GMC
	VLR_DATONG = 151,               // ������ͨ
	VLR_BQYINXIANG = 152,               // ��������
	VLR_NEWCHERY = 153,               // ������
	VLR_MUDAN = 154,               // ĵ��
	VLR_DAYUN = 155,               // ��������
	VLR_DONGWO = 156,               // ��������
	VLR_UNION = 157,               // ��������
	VLR_CHUNZHOU = 158,               // ���޿ͳ�
	VLR_SANY = 159,               // ��һ�ع�
	VLR_YAXING = 160,               // ���ǿͳ�
	VLR_HENGTONG = 161,               // ��ͨ�ͳ�
	VLR_SHAOLIN = 162,               // ���ֿͳ�
	VLR_YOUNG = 163,               // ����ͳ�
	VLR_STOM = 164,               // ʮͨ
	VLR_SANHUAN = 165,               // ����
	VLR_XUGONG = 166,               // �칤
	VLR_BEIFANG = 167,               // ��������
	VLR_JIANGHUAN = 168,               // ��������
	VLR_BJFARM = 169,               // ����ũ��
	VLR_NEWDADI = 170,               // �´������
	VLR_SUNWIN = 171,               // ���ֿͳ�
	VLR_YINGTIAN = 172,               // Ӣ��
	VLR_QINGQI = 173,               // ����
	VLR_CHUFENG = 174,               // ��������
	VLR_SCANIA = 175,               // ˹������
	VLR_JIULONG = 176,               // �����ͳ�
	VLR_YOUYI = 177,               // ����ͳ�
	VLR_SHANGRAO = 178,               // ���Ŀͳ�
	VLR_JIJIANG = 179,               // ����
	VLR_YANGZI = 180,               // ���ӿͳ�
	VLR_XIWO = 181,               // ���ֿͳ�
	VLR_CHANGJIANG = 182,               // �����ͳ�
	VLR_WUYI = 183,               // ����
	VLR_CHENGDU = 184,               // �ɶ��ͳ�
	VLR_TIANMA = 185,               // ����
	VLR_BAOLONG = 186,               // ����
	VLR_NEWYATU = 187,               // ����;
	VLR_BARUI = 188,               // ���ǰ���
	VLR_GUANZHI = 189,               // ����
	VLR_XIYATE = 190,               // ������
	VLR_BINLI = 191,               // ����
	VLR_DADI = 192,               // ���
	VLR_FUQI = 193,               // ����
	VLR_HANGTIAN = 194,               // ��������
	VLR_HENGTIAN = 195,               // ��������
	VLR_JMCCAR = 196,               // ��������
	VLR_KAERSEN = 197,               // ����ɭ����
	VLR_KAWEI = 198,               // ��������
	VLR_LANBOJINI = 199,               // ��������
	VLR_MASHALADI = 200,               // ��ɯ����
	VLR_SHUCHI = 201,               // ��ۿͳ�
	VLR_SHILI = 202,               // ʵ���ͳ�
	VLR_HUABEI = 203,               // �пͻ���
	VLR_YIZHENG = 204,               // ��������
	VLR_CHUNLAN = 205,               // ��������
	VLR_DAFA = 206,               // ������
	VLR_SHENYE = 207,               // ��Ұ����
	VLR_FALALI = 208,               // ����������
	VLR_FUXING = 209,               // ��������
	VLR_ANYUAN = 210,               // ��Դ�ͳ�
	VLR_JINGHUA = 211,               // �����ͳ�
	VLR_TAIHU = 212,               // ̫���ͳ�
	VLR_WUZHOULONG = 213,               // ������
	VLR_CHANGLONG = 214,               // ��¡�ͳ�
	VLR_YUEXI = 215,               // �����ͳ�
	VLR_SHENMA = 216,               // ����ͳ�
	VLR_LUSHAN = 217,               // ®ɽ��
	VLR_WANFENG = 218,               // �����
	VLR_GZYUNBAO = 219,               // �����Ʊ�
	VLR_ZHONGDA = 220,               // �д�����
	VLR_THREEWHEEL = 221,               // ���ֳ�
	VLR_TWOWHEEL = 222,               // ���ֳ�
	VLR_JBC = 223,              // ��JBC
	VLR_YZJIANG = 224,               // ���ӽ��ͳ�
	VLR_CNJ = 225,               // �Ͽ�CNJ
	VLR_FORLAND = 226,               // ����ʱ������
	VLR_FARMCAR = 227,               // ũ�ó�
	VLR_DONGFANGHONG = 228,               // ������
	VLR_STEYR = 229,               // ˹̫������
	VLR_HONGQI = 230,               // ����
	VLR_USER1 = 231,   //�û�1
	VLR_USER2 = 232,   //�û�2
	VLR_USER3 = 233,   //�û�3
	VLR_USER4 = 234,   //�û�4
	VLR_USER5 = 235,   //�û�5
	VLR_USER6 = 236,   //�û�6
	VLR_USER7 = 237,   //�û�7
	VLR_USER8 = 238    //�û�8
}VLR_VEHICLE_CLASS;

/********************����Ʒ��������Begin*************************/
//������Ʒ������
typedef enum _VSB_VOLKSWAGEN_CLASS
{
	VSB_VOLKSWAGEN_OTHER = 0,   // ������������
	VSB_VOLKSWAGEN_LAVIDA = 1,   // ����
	VSB_VOLKSWAGEN_CROSSLAVIDA = 2,   // �ʾ�
	VSB_VOLKSWAGEN_TIGUAN = 3,   // ;��
	VSB_VOLKSWAGEN_TOURAN = 4,   // ;��
	VSB_VOLKSWAGEN_SANTANA = 5,   // ɣ����
	VSB_VOLKSWAGEN_SANTANA2000 = 6,   // ɣ����2000
	VSB_VOLKSWAGEN_SANTANA3000 = 7,   // ɣ����3000
	VSB_VOLKSWAGEN_VISTA = 8,   // ɣ����-־��
	VSB_VOLKSWAGEN_PASSAT = 9,   // ������
	VSB_VOLKSWAGEN_PASSATLINGYU = 10,  // ������-��Ԧ
	VSB_VOLKSWAGEN_POLO = 11,  // ����
	VSB_VOLKSWAGEN_POLOCROSS = 12,  // ����-�˶���
	VSB_VOLKSWAGEN_POLOGTI = 13,  // ����-GTI
	VSB_VOLKSWAGEN_SAGITAR = 14,  // ����
	VSB_VOLKSWAGEN_MAGOTAN = 15,  // ����
	VSB_VOLKSWAGEN_JETTA = 16,  // �ݴ�
	VSB_VOLKSWAGEN_BORA = 17,  // ����
	VSB_VOLKSWAGEN_NEWGOLF = 18,  // �¸߶���
	VSB_VOLKSWAGEN_GOLFGTI = 19,  // �߶���-GTI
	VSB_VOLKSWAGEN_GOL = 20,  // �߶�
	VSB_VOLKSWAGEN_CADDY = 21,  // ����
	VSB_VOLKSWAGEN_PHAETON = 22,  // ����
	VSB_VOLKSWAGEN_TOUREG = 23,  // ;��
	VSB_VOLKSWAGEN_SCIROCCO = 24,  // �п�
	VSB_VOLKSWAGEN_BEETLE = 25,  // �׿ǳ�
	VSB_VOLKSWAGEN_SHARAN = 26,  // ����
	VSB_VOLKSWAGEN_MULTIVAN = 27,  // ������
	VSB_VOLKSWAGEN_CARBONCOPY = 28,  // һ������-CC
	VSB_VOLKSWAGEN_VISTACHANGDA = 29,  // ɣ����־��-����
	VSB_VOLKSWAGEN_BORASPORTLINE = 30,   // ����-SPORTLINE
	VSR_VOLKSWAGEN_CC_1 = 31,   //����-CC-2012,2011,2010
	VSR_VOLKSWAGEN_Cross_POLO_1 = 32,   //����-Cross-POLO-2010,2007
	VSR_VOLKSWAGEN_Cross_POLO_2 = 33,   //����-Cross-POLO-2014,2012
	VSR_VOLKSWAGEN_MULTIVAN_1 = 34,   //����-Multivan-2014,2012,2011
	VSR_VOLKSWAGEN_POLO_1 = 35,   //����-POLO-2006,2005,2004,2003,2002
	VSR_VOLKSWAGEN_POLO_2 = 36,   //����-POLO-2013,2012,2011
	VSR_VOLKSWAGEN_POLO_JINQU_1 = 37,   //����-POLO��ȡ-2009,2008,2007,2006
	VSR_VOLKSWAGEN_POLO_JINQU_2 = 38,   //����-POLO��ȡ-2011
	VSR_VOLKSWAGEN_Tiguan_1 = 39,   //����-Tiguan-2011,2009
	VSR_VOLKSWAGEN_Tiguan_2 = 40,   //����-Tiguan-2014,2013,2012
	VSR_VOLKSWAGEN_XIALANG_1 = 41,   //����-����-2013,2012
	VSR_VOLKSWAGEN_BAOLAI_1 = 42,   //����-����-2005,2004
	VSR_VOLKSWAGEN_BAOLAI_2 = 43,   //����-����-2006
	VSR_VOLKSWAGEN_BAOLAI_3 = 44,   //����-����-2012,2011,2010,2009,2008
	VSR_VOLKSWAGEN_BAOLAI_4 = 45,   //����-����-2014,2013
	VSR_VOLKSWAGEN_SHANGKU_1 = 46,   //����-�п�-2014,2013
	VSR_VOLKSWAGEN_PASATE_1 = 47,   //����-������-2003����,2001��Ԧ
	VSR_VOLKSWAGEN_PASATE_2 = 48,   //����-������-2007,2006,2005��Ԧ
	VSR_VOLKSWAGEN_PASATE_3 = 49,   //����-������-2009,2008,2007,2005,2004,2003,2001,2000
	VSR_VOLKSWAGEN_PASATE_4 = 50,   //����-������-2011,2009��Ԧ
	VSR_VOLKSWAGEN_PASATE_5 = 51,   //����-������-2014,2013,2012,2011
	VSR_VOLKSWAGEN_JIEDA_1 = 52,   //����-�ݴ�-2005CIF���,2002
	VSR_VOLKSWAGEN_JIEDA_2 = 53,   //����-�ݴ�-2009,2008,2006,2005,2004
	VSR_VOLKSWAGEN_JIEDA_3 = 54,   //����-�ݴ�-2012,2010
	VSR_VOLKSWAGEN_JIEDA_4 = 55,   //����-�ݴ�-2013
	VSR_VOLKSWAGEN_LANGYI_1 = 56,   //����-����-2012,2011,2010,2009,2008
	VSR_VOLKSWAGEN_LANGYI_2 = 57,   //����-����-2013
	VSR_VOLKSWAGEN_SANGTANA_1 = 58,   //����-ɣ����-2007,2002,2000,1999,1995
	VSR_VOLKSWAGEN_SANGTANA_2 = 59,   //����-ɣ����-2014,2013
	VSR_VOLKSWAGEN_SANGTANA_3 = 60,   //����-ɣ����2000-2003,2001,2000,1999,1998,1996
	VSR_VOLKSWAGEN_SANGTANA_4 = 61,   //����-ɣ����3000-2007,2006,2005,2004,2003
	VSR_VOLKSWAGEN_SANGTANAZHIJUN_1 = 62,   //����-ɣ����־��(vista)-2011,2010,2009,2008
	VSR_VOLKSWAGEN_SANGTANAZHIJUN_2 = 63,   //����-ɣ����־��(vista)-2006
	VSR_VOLKSWAGEN_JIAKECHONG_1 = 64,   //����-�׿ǳ�-2010,2009,2008,2007,2006,2005
	VSR_VOLKSWAGEN_JIAKECHONG_2 = 65,   //����-�׿ǳ�-2014,2013
	VSR_VOLKSWAGEN_HUITENG_2 = 66,   //����-����-2010,2009,2007,2006
	VSR_VOLKSWAGEN_MAITENG_1 = 67,   //����-����-2011,2010,2009,2008,2007
	VSR_VOLKSWAGEN_MAITENG_2 = 68,   //����-����-2013,2012
	VSR_VOLKSWAGEN_TUAN_3 = 69,   //����-;��-2006,2005,2004
	VSR_VOLKSWAGEN_TUAN_1 = 70,   //����-;��-2010,2009,2008
	VSR_VOLKSWAGEN_TUAN_2 = 71,   //����-;��-2013,2012,2011
	VSR_VOLKSWAGEN_TUGUAN_1 = 72,   //����-;��-2012,2011,2010
	VSR_VOLKSWAGEN_TURUI_1 = 73,   //����-;��-2006,2005,2003
	VSR_VOLKSWAGEN_TURUI_2 = 74,   //����-;��-2014,2013,2012,2011
	VSR_VOLKSWAGEN_SUTENG_1 = 75,   //����-����-2010,2009,2007,2006
	VSR_VOLKSWAGEN_SUTENG_2 = 76,   //����-����-2011
	VSR_VOLKSWAGEN_SUTENG_3 = 77,   //����-����-2014,2013,2012
	VSR_VOLKSWAGEN_GAOERFU_1 = 78,   //����-�߶���-2008,2007,2006,2005,2004,2003
	VSR_VOLKSWAGEN_GAOERFU_2 = 79,   //����-�߶���-2012,2011����,2012,2011,2010
	VSR_VOLKSWAGEN_GAOERFU_3 = 80,   //����-�߶���GTI-2013,2012,2011,2010
	VSR_VOLKSWAGEN_LANGYI_3 = 81,   //����-����-2014
	VSR_VOLKSWAGEN_HUITENG_1 = 82   //����-����-2004
} VSB_VOLKSWAGEN_CLASS;

//�����Ʒ������
typedef enum _VBR_BUICK_CLASS
{
	VBR_BUICK_OTHER = 0,   // ������������
	VBR_BUICK_ENCORE = 1,   // ������
	VBR_BUICK_GL8 = 2,   // GL8
	VBR_BUICK_LEGAL = 3,   // ����
	VBR_BUICK_LACROSS = 4,   // ��Խ
	VBR_BUICK_EXCELLE = 5,   // ��Խ
	VBR_BUICK_EXCELLEGT = 6,   // Ӣ��GT
	VBR_BUICK_WXCELLEXT = 7,   // Ӣ��XT
	VBR_BUICK_ENCLAVE = 8,   // ������
	VBR_BUICK_ROYAUM = 9,   // ����
	VBR_BUICK_SAIL = 10,  // �����ŷ
	VBR_BUICK_EXCELLEHRV = 11,  // ��ԽHRV
	VBR_BUICK_PARKAVENUE = 12,  // ������
	VBR_BUICK_CENTURY = 13,   // ������
	VBR_BUICK_GL8_1 = 14,   // ���-GL8-2004,2003
	VBR_BUICK_GL8_2 = 15,   // ���-GL8-2007,2006,2005
	VBR_BUICK_GL8_3 = 16,   // ���-GL8-2010_2008_2006_2005½��
	VBR_BUICK_GL8_4 = 17,   // ���-GL8-2014,2013,2012,2011
	VBR_BUICK_GL8_5 = 18,   // ���-GL8-2014_2013_2011������
	VBR_BUICK_ENCORE_1 = 19,   // ���-������-2014,2013
	VBR_BUICK_ENCLAVE_1 = 20,   // ���-������-2013,2010,2009
	VBR_BUICK_LEGAL_1 = 21,   // ���-����-2001,2000,1999
	VBR_BUICK_LEGAL_2 = 22,   // ���-����-2008,2006,2005,2004,2002
	VBR_BUICK_LEGAL_3 = 23,   // ���-����-2013,2012,2011,2010,2009
	VBR_BUICK_LEGAL_4 = 24,   // ���-����-2013_2012_2011�˶���
	VBR_BUICK_LEGAL_5 = 25,   // ���-����-2014
	VBR_BUICK_LEGAL_6 = 26,   // ���-����-2014�˶���
	VBR_BUICK_LACROSS_1 = 27,   // ���-��Խ-2008,2007,2006
	VBR_BUICK_LACROSS_2 = 28,   // ���-��Խ-2012,2011,2010,2009
	VBR_BUICK_LACROSS_3 = 29,   // ���-��Խ-2013
	VBR_BUICK_EXCELLE_1 = 30,   // ���-��Խ-2006,2005,2004
	VBR_BUICK_EXCELLE_2 = 31,   // ���-��Խ-2008_2006_2005_2004HRV
	VBR_BUICK_EXCELLE_3 = 32,   // ���-��Խ-2011,2009,2008
	VBR_BUICK_EXCELLE_4 = 33,   // ���-��Խ-2013
	VBR_BUICK_PARKAVENUE_1 = 34,   // ���-������-2011,2010,2009,2008,2007
	VBR_BUICK_SAIL_1 = 35,   // ���-��ŷ-2004,2003
	VBR_BUICK_EXCELLEGT_1 = 36,   // ���-Ӣ��GT-2013,2012,2011,2010
	VBR_BUICK_WXCELLEXT_1 = 37,   // ���-Ӣ��XT-2014,2013,2012,2010
	VBR_BUICK_CENTURY_1 = 38,   // ���-������-2000
	VBR_BUICK_RONGYU_1 = 39   // ���-����-2005,2004
}VBR_BUICK_CLASS;

//������Ʒ������
typedef enum _VSB_BMW_CLASS
{
	VSB_BMW_OTHER = 0,   // ������������
	VSB_BMW_3SERIES = 1,   // ����3ϵ
	VSB_BMW_5SERIES = 2,   // ����5ϵ
	VSB_BMW_X1 = 3,   // ����X1
	VSB_BMW_1SERIES = 4,   // ����1ϵ
	VSB_BMW_7SERIES = 5,   // ����7ϵ
	VSB_BMW_X3 = 6,   // ����X3
	VSB_BMW_X5 = 7,   // ����X5
	VSB_BMW_X6 = 8,   // ����X6
	VSB_BMW_Z4 = 9,   // ����Z4
	VSB_BMW_MINI = 10,  // ����
	VSB_BMW_6SERIES = 11,   //����6ϵ
	VSB_BMW_YIXI_1 = 12,     // ����-1ϵ-2011,2010,2008,2007
	VSB_BMW_YIXI_2 = 13,     // ����-1ϵ-2013,2012
	VSB_BMW_SANXI_1 = 14,     // ����-3ϵ-2004
	VSB_BMW_SANXI_2 = 15,     // ����-3ϵ-2007,2005
	VSB_BMW_SANXI_3 = 16,     // ����-3ϵ-2012,2011,2010,2009
	VSB_BMW_SANXI_4 = 17,     // ����-3ϵ-2014,2013
	VSB_BMW_WUXI_1 = 18,     // ����-5ϵ-2010,2009,2008
	VSB_BMW_WUXI_2 = 19,     // ����-5ϵ-2013,2012,2011
	VSB_BMW_LIUXI_1 = 20,     // ����-6ϵ-δ֪
	VSB_BMW_QIXI_1 = 21,     // ����-7ϵ-2011,2010,2009
	VSB_BMW_QIXI_2 = 22,     // ����-7ϵ-2013
	VSB_BMW_X1_1 = 23,     // ����-X1-2012,2010
	VSB_BMW_X1_2 = 24,     // ����-X1-2014,2013
	VSB_BMW_X3_1 = 25,     // ����-X3-2009,2008,2006
	VSB_BMW_X3_2 = 26,     // ����-X3-2013,2012,2011
	VSB_BMW_X5_1 = 27,     // ����-X5-2010,2009,2008
	VSB_BMW_X5_2 = 28,     // ����-X5-2013,2012,2011
	VSB_BMW_X5_3 = 29,     // ����-X5-2013�˶���
	VSB_BMW_X6_1 = 30,     // ����-X6-2013,2012,2011,2009,2008
	VSB_BMW_Z4_1 = 31     // ����-Z4-2004
}VSB_BMW_CLASS;

//������Ʒ������
typedef enum _VSB_HONDA_CLASS
{
	VSB_HONDA_OTHER = 0,   // ������������
	VSB_HONDA_CRV = 1,   // ����CR-V(˼��)
	VSB_HONDA_JADE = 2,   // �ܵ�
	VSB_HONDA_CIVIC = 3,   // ˼��
	VSB_HONDA_SPIRIOR = 4,   // ˼���
	VSB_HONDA_CIIMO = 5,   // ˼��
	VSB_HONDA_ELYSION = 6,   // ������
	VSB_HONDA_OBYSSEY = 7,   // ������
	VSB_HONDA_FIT = 8,   // �ɶ�
	VSB_HONDA_NEWCITY = 9,   // �淶
	VSB_HONDA_CROSSTOUR = 10,  // ��ʫͼ
	VSB_HONDA_CRIDER = 11,  // ����
	VSB_HONDA_ACCORD = 12,  // �Ÿ�
	VSB_HONDA_CITY = 13,  // ˼��
	VSB_HONDA_ANTILOCK = 14,  // ���µ�
	VSB_HONDA_CRZ = 15,   // ����CR-Z
	VSB_HONDA_CRV_1 = 16,   // ����-CR-V-2004
	VSB_HONDA_CRV_2 = 17,   // ����-CR-V-2005
	VSB_HONDA_CRV_3 = 18,   // ����-CR-V-2008,2007
	VSB_HONDA_CRV_4 = 19,   // ����-CR-V-2010
	VSB_HONDA_CRV_5 = 20,   // ����-CR-V-2013,2012
	VSB_HONDA_CRIDER_1 = 21,   // ����-����-2014,2013
	VSB_HONDA_OBYSSEY_1 = 22,   // ����-�µ���-2002
	VSB_HONDA_OBYSSEY_2 = 23,   // ����-�µ���-2006,2005,2004
	VSB_HONDA_OBYSSEY_3 = 24,   // ����-�µ���-2008,2007
	VSB_HONDA_OBYSSEY_4 = 25,   // ����-�µ���-2011������
	VSB_HONDA_CIVIC_1 = 26,   // ����-˼��-2007
	VSB_HONDA_CIVIC_5 = 27,   // ����-˼��-1996
	VSB_HONDA_CIVIC_2 = 28,   // ����-˼��-2008,2006
	VSB_HONDA_CIVIC_3 = 29,   // ����-˼��-2009
	VSB_HONDA_CIVIC_4 = 30,   // ����-˼��-2013,2012,2011
	VSB_HONDA_CITY_1 = 31,   // ����-˼��-2008,2007,2006
	VSB_HONDA_SPIRIOR_1 = 32,   // ����-˼���-2009
	VSB_HONDA_SIMING_1 = 33,   // ����-˼��-2012
	VSB_HONDA_JIEDE_1 = 34,   // ����-�ܵ�-2013
	VSB_HONDA_CROSSTOUR_1 = 35,   // ����-��ʫͼ-2013,2012,2010
	VSB_HONDA_AILISHEN_1 = 36,   // ����-������-2012
	VSB_HONDA_NEWCITY_1 = 37,   // ����-�淶-2009
	VSB_HONDA_NEWCITY_2 = 38,   // ����-�淶-2011
	VSB_HONDA_NEWCITY_3 = 39,   // ����-�淶-2014,2012
	VSB_HONDA_ACCORD_1 = 40,   // ����-�Ÿ�-1996
	VSB_HONDA_ACCORD_2 = 41,   // ����-�Ÿ�-1999
	VSB_HONDA_ACCORD_3 = 42,   // ����-�Ÿ�-2001
	VSB_HONDA_ACCORD_4 = 43,   // ����-�Ÿ�-2003
	VSB_HONDA_ACCORD_5 = 44,   // ����-�Ÿ�-2008
	VSB_HONDA_ACCORD_6 = 45,   // ����-�Ÿ�-2010
	VSB_HONDA_ACCORD_7 = 46,   // ����-�Ÿ�-2011
	VSB_HONDA_ACCORD_8 = 47,   // ����-�Ÿ�-2012
	VSB_HONDA_ACCORD_9 = 48,   // ����-�Ÿ�-2013
	VSB_HONDA_ACCORD_10 = 49,   // ����-�Ÿ�-2014
	VSB_HONDA_FIT_1 = 50,   // ����-�ɶ�-2004
	VSB_HONDA_FIT_2 = 51,   // ����-�ɶ�-2004����
	VSB_HONDA_FIT_3 = 52,   // ����-�ɶ�-2005
	VSB_HONDA_FIT_4 = 53,   // ����-�ɶ�-2007
	VSB_HONDA_FIT_5 = 54,   // ����-�ɶ�-2008
	VSB_HONDA_FIT_6 = 55   // ����-�ɶ�-2013,2011
}VSB_HONDA_CLASS;

//������Ʒ������
typedef enum _VSB_PEUGEOT_CLASS
{
	VSB_PEUGEOT_OTHER = 0,   // ������������
	VSB_PEUGEOT_2008 = 1,   // ����2008
	VSB_PEUGEOT_207 = 2,   // ����207
	VSB_PEUGEOT_SENNA = 3,   // ����
	VSB_PEUGEOT_3008 = 4,   // ����3008
	VSB_PEUGEOT_301 = 5,   // ����301
	VSB_PEUGEOT_307 = 6,   // ����307
	VSB_PEUGEOT_308 = 7,   // ����308
	VSB_PEUGEOT_408 = 8,   // ����408
	VSB_PEUGEOT_508 = 9,   // ����508
	VSB_PEUGEOT_206 = 10,  // ����206
	VSB_PEUGEOT_407 = 11,   // ����407
	VSB_PEUGEOT_206_1 = 12, // ����-206-δ֪
	VSB_PEUGEOT_207_1 = 13, // ����-207����-2011,2010,2009
	VSB_PEUGEOT_207_2 = 14, // ����-207����-2013
	VSB_PEUGEOT_3008_1 = 15, // ����-3008-2014,2013
	VSB_PEUGEOT_301_1 = 16, // ����-301-δ֪
	VSB_PEUGEOT_307_1 = 17, // ����-307����-2007,2006,2005,2004
	VSB_PEUGEOT_307_2 = 18, // ����-307����-2010,2009,2008
	VSB_PEUGEOT_307_3 = 19, // ����-307����-2013_2012_2011CROSS
	VSB_PEUGEOT_308_1 = 20, // ����-308-2014,2013,2012
	VSB_PEUGEOT_407_1 = 21, // ����-407-δ֪
	VSB_PEUGEOT_408_1 = 22, // ����-408-2012,2011,2010
	VSB_PEUGEOT_408_2 = 23, // ����-408-2013
	VSB_PEUGEOT_508_1 = 24, // ����-508-2014,2013,2012,2011
	VSB_PEUGEOT_207_3 = 25, // ����-207����-2011,2010,2009
	VSB_PEUGEOT_307_4 = 26 // ����-307����-2013,2012,2010,2009,2008

}VSB_PEUGEOT_CLASS;

//������Ʒ������
typedef enum _VSB_TOYOTA_CLASS
{
	VSB_TOYOTA_OTHER = 0,   // ������������
	VSB_TOYOTA_HIGHLANDER = 1,   // ������
	VSB_TOYOTA_CAMRY = 2,   // ������
	VSB_TOYOTA_YARIS = 3,   // ����ʿ
	VSB_TOYOTA_YARISL = 4,   // YARIS L����
	VSB_TOYOTA_VERSO = 5,   // ����
	VSB_TOYOTA_HUAGUAN = 6,   // ����
	VSB_TOYOTA_CROWN = 7,   // �ʹ�
	VSB_TOYOTA_COROLLA = 8,   // ������
	VSB_TOYOTA_COSTER = 9,   // ��˹��
	VSB_TOYOTA_PRADO = 10,  // ������
	VSB_TOYOTA_PRIUS = 11,  // ����˹
	VSB_TOYOTA_RAV4 = 12,  // ����RAV4
	VSB_TOYOTA_REZI = 13,  // ��־
	VSB_TOYOTA_VIOS = 14,  // ����
	VSB_TOYOTA_PREVIA = 15,  // ����ά��
	VSB_TOYOTA_HIACE = 16,  // ��ʨ
	VSB_TOYOTA_86 = 17,  // ����86
	VSB_TOYOTA_SPEQUOIA = 18,  // ��ɼ
	VSB_TOYOTA_LANDCRUISER = 19,  // ½��Ѳ��(���¿�·��)
	VSB_TOYOTA_SIENNA = 20,  // ����
	VSB_TOYOTA_CAMRYHYBRID = 21,  // ������-HYBRID
	VSB_TOYOTA_GRACE = 22,  // ����˹
	VSB_TOYOTA_ALPHARD = 23,   // ������
	VSB_TOYOTA_RAV4_1 = 24,   // ����-RAV4-2012�ֶ������,2011,2010,2009
	VSB_TOYOTA_RAV4_2 = 25,   // ����-RAV4-2013
	VSB_TOYOTA_86_1 = 26,   // ����-����86-δ֪
	VSB_TOYOTA_JIAMEI_2 = 27,   // ����-����-2001,2000,1999,1998
	VSB_TOYOTA_JIAMEI_3 = 28,   // ����-����-2004,2003,2002
	VSB_TOYOTA_LANDEKLZ_1 = 29,   // ����-���¿�·��-2011�ж���,2010,2007
	VSB_TOYOTA_KAIMEIRUI_1 = 30,   // ����-������-2008,2007,2006
	VSB_TOYOTA_KAIMEIRUI_2 = 31,   // ����-������-2012����
	VSB_TOYOTA_KAIMEIRUI_3 = 32,   // ����-������-2012�����,2011,2010,2009
	VSB_TOYOTA_KAIMEIRUI_4 = 33,   // ����-������-2013,2012
	VSB_TOYOTA_KAIMEIRUI_5 = 34,   // ����-������-2013�����
	VSB_TOYOTA_KAIMEIRUI_6 = 35,   // ����-������-2014,2012����
	VSB_TOYOTA_KALUOLA_1 = 36,   // ����-������-2010,2009,2008,2007,2006
	VSB_TOYOTA_KALUOLA_2 = 37,   // ����-������-2013,2012,2011
	VSB_TOYOTA_AIERFA_1 = 38,   // ����-������-2011,2010
	VSB_TOYOTA_AIERFA_2 = 39,   // ����-������-2013,2012
	VSB_TOYOTA_WEICHI_1 = 40,   // ����-����-2004,2003
	VSB_TOYOTA_WEICHI_2 = 41,   // ����-����-2007,2006,2005
	VSB_TOYOTA_WEICHI_3 = 42,   // ����-����-2009,2008
	VSB_TOYOTA_WEICHI_4 = 43,   // ����-����-2013,2012,2011,2010
	VSB_TOYOTA_WEICHI_5 = 44,   // ����-����-2014
	VSB_TOYOTA_PULADUO_1 = 45,   // ����-������-2007,2006,2005,2004
	VSB_TOYOTA_PULADUO_2 = 46,   // ����-������-2010
	VSB_TOYOTA_PULADUO_3 = 47,   // ����-������-2014
	VSB_TOYOTA_PURUIWEIYA_1 = 48,   // ����-����ά��-2004
	VSB_TOYOTA_PURUIWEIYA_4 = 49,   // ����-����ά��-2005
	VSB_TOYOTA_PURUIWEIYA_2 = 50,   // ����-����ά��-2006
	VSB_TOYOTA_PURUIWEIYA_3 = 51,   // ����-����ά��-2012,2010,2008,2007
	VSB_TOYOTA_KESIDA_1 = 52,   // ����-��˹��-2007
	VSB_TOYOTA_KESIDA_2 = 53,   // ����-��˹��-2011
	VSB_TOYOTA_HANLANDA_1 = 54,   // ����-������-2011,2009
	VSB_TOYOTA_HANLANDA_2 = 55,   // ����-������-2012
	VSB_TOYOTA_HANLANDA_3 = 56,   // ����-������-2013
	VSB_TOYOTA_HAISHI_1 = 57,   // ����-��ʨ-2001
	VSB_TOYOTA_HUANGGUAN_1 = 58,   // ����-�ʹ�-1999
	VSB_TOYOTA_HUANGGUAN_2 = 59,   // ����-�ʹ�-2009,2008,2007,2006,2005
	VSB_TOYOTA_HUANGGUAN_3 = 60,   // ����-�ʹ�-2010
	VSB_TOYOTA_HUANGGUAN_4 = 61,   // ����-�ʹ�-2012,2011
	VSB_TOYOTA_HONGSHAN_1 = 62,   // ����-��ɼ-δ֪
	VSB_TOYOTA_HUAGUAN_1 = 63,   // ����-����-2006,2005,2004
	VSB_TOYOTA_HUAGUAN_2 = 64,   // ����-����-2009,2008,2007
	VSB_TOYOTA_HUAGUAN_3 = 65,   // ����-����-2011,2010
	VSB_TOYOTA_YIZHI_1 = 66,   // ����-����-2014,2012,2011
	VSB_TOYOTA_RUIZHI_1 = 67,   // ����-��־-2006,2005
	VSB_TOYOTA_RUIZHI_2 = 68,   // ����-��־-2009,2008,2007
	VSB_TOYOTA_RUIZHI_3 = 69,   // ����-��־-2010��Ȱ�
	VSB_TOYOTA_RUIZHI_4 = 70,   // ����-��־-2012,2010
	VSB_TOYOTA_LUDIXUNYANG_1 = 71,   // ����-½��Ѳ��-δ֪
	VSB_TOYOTA_YALISHI_1 = 72,   // ����-����ʿ-2009,2008,2007
	VSB_TOYOTA_YALISHI_2 = 73,   // ����-����ʿ-2012,2011,2010
	VSB_TOYOTA_RAV4_3 = 74,   // ����-RAV4-2013����,��Ӣ,���,2012
	VSB_TOYOTA_YARiSL_1 = 75,   // ����-YARiS-L
	VSB_TOYOTA_JIAMEI_1 = 76,   // ����-����-1996
	VSB_TOYOTA_PLATZ_1 = 77,   // ����-PLATZ-1999
	VSB_TOYOTA_LANDEKLZ_2 = 78   // ����-���¿�·��-2014,2012�ж���,2012
}VSB_TOYOTA_CLASS;

//������Ʒ������
typedef enum _VSB_FORD_CLASS
{
	VSB_FORD_OTHER = 0,   // ������������
	VSB_FORD_FOCUS = 1,   // ����˹
	VSB_FORD_FIESTA = 2,   // ���껪
	VSB_FORD_SMAX = 3,   // ���˹
	VSB_FORD_MONDEO = 4,   // �ɵ�ŷ
	VSB_FORD_ECOSPORT = 5,   // ��
	VSB_FORD_ESCAPE = 6,   // ��
	VSB_FORD_ZHISHENG = 7,   // ��ʤ
	VSB_FORD_ESCORT = 8,   // ���˹
	VSB_FORD_EXPLORER = 9,   // ����̽����
	VSB_FORD_EDGE = 10,  // ���
	VSB_FORD_TRANSIT = 11,   // ȫ˳
	VSB_FORD_QUANSHUN_1 = 12,    // ����-ȫ˳-δ֪
	VSB_FORD_JIANIANHUA_1 = 13,    // ����-���껪����-2006,2005,2004
	VSB_FORD_JIANIANHUA_2 = 14,    // ����-���껪����-2011,2010,2009
	VSB_FORD_JIANIANHUA_3 = 15,    // ����-���껪����-2013
	VSB_FORD_JIANIANHUA_4 = 16,    // ����-���껪����-2012
	VSB_FORD_TANXIANZHE_1 = 17,    // ����-̽����-2013,2011
	VSB_FORD_FOCUS_1 = 18,    // ����-����˹����-2005
	VSB_FORD_FOCUS_2 = 19,    // ����-����˹����-2005������
	VSB_FORD_FOCUS_3 = 20,    // ����-����˹����-2008,2007,2006
	VSB_FORD_FOCUS_4 = 21,    // ����-����˹����-2013,2012����,2011,2009
	VSB_FORD_FOCUS_5 = 22,    // ����-����˹����-2012
	VSB_FORD_FOCUS_6 = 23,    // ����-����˹����-2012����,ʱ��,2011,2010,2009,2008
	VSB_FORD_YIBO_1 = 24,    // ����-��-2013
	VSB_FORD_YIHU_1 = 25,    // ����-��-2013
	VSB_FORD_MENGDIOU_1 = 26,    // ����-�ɵ�ŷ-2003
	VSB_FORD_MENGDIOU_2 = 27,    // ����-�ɵ�ŷ-2005,2004
	VSB_FORD_MENGDIOU_3 = 28,    // ����-�ɵ�ŷ-2006
	VSB_FORD_MENGDIOU_4 = 29,    // ����-�ɵ�ŷ-2013
	VSB_FORD_MENGDIOU_5 = 30,    // ����-�ɵ�ŷ-��ʤ-2010,2008,2007
	VSB_FORD_MENGDIOU_6 = 31,    // ����-�ɵ�ŷ-��ʤ-2011
	VSB_FORD_RUIJIE_1 = 32,    // ����-���-2012,2011
	VSB_FORD_MAIKESI_1 = 33    // ����-���˹-2008,2007
}VSB_FORD_CLASS;

//�ղ���Ʒ������
typedef enum _VSB_NISSAN_CLASS
{
	VSB_NISSAN_OTHER = 0,   // ������������
	VSB_NISSAN_XTRAIL = 1,   // �濥
	VSB_NISSAN_MURANO = 2,   // ¥��
	VSB_NISSAN_LIVINA = 3,   // ����
	VSB_NISSAN_MARCH = 4,   // ���
	VSB_NISSAN_TIIDA = 5,   // ���
	VSB_NISSAN_TEANA = 6,   // ����
	VSB_NISSAN_QASHQAI = 7,   // �п�
	VSB_NISSAN_SYLPHY = 8,   // ����
	VSB_NISSAN_SUNNY = 9,   // ����
	VSB_NISSAN_D22PICKUP = 10,  // D22Ƥ��
	VSB_NISSAN_D22VAN = 11,  // D22��ʽ��
	VSB_NISSAN_CABSTAR = 12,  // ����˹��
	VSB_NISSAN_HV200 = 13,  // NV200
	VSB_NISSAN_PALADIN = 14,  // ������
	VSB_NISSAN_YIDA = 15,  // �ô�
	VSB_NISSAN_DUCK = 16,  // ����
	VSB_NISSAN_CEFIRO = 17,  // ���
	VSB_NISSAN_FENGSHENBLUEBIRD = 18,  // ��������
	VSB_NISSAN_FENGSHENSUNNY = 19,  // ��������
	VSB_NISSAN_SUCCE = 20,  // ˧��
	VSB_NISSAN_FUGA = 21,  // ����
	VSB_NISSAN_BLUEBIRD4 = 22,  // ����4��
	VSB_NISSAN_VENUCIA = 23,  // ����
	VSB_NISSAN_QUEST = 24,  // ��ʿ
	VSB_NISSAN_GENISS = 25,   // ����
	VSB_NISSAN_NV200_1 = 26,  // �ղ�-NV200-2013,2012,2011,2010
	VSB_NISSAN_TIANLAI_1 = 27,  // �ղ�-����-2005,2004
	VSB_NISSAN_TIANLAI_2 = 28,  // �ղ�-����-2007,2006
	VSB_NISSAN_TIANLAI_3 = 29,  // �ղ�-����-2010,2008
	VSB_NISSAN_TIANLAI_4 = 30,  // �ղ�-����-2012,2011
	VSB_NISSAN_TIANLAI_5 = 31,  // �ղ�-����-2012�ư�ȫ��,2011����
	VSB_NISSAN_TIANLAI_6 = 32,  // �ղ�-����-2014,2013
	VSB_NISSAN_QIJUN_1 = 33,  // �ղ�-�濥-2010,2008
	VSB_NISSAN_QIJUN_2 = 34,  // �ղ�-�濥-2012,2011����
	VSB_NISSAN_PALADING_1 = 35,  // �ղ�-������-2013,2011,2006,2004
	VSB_NISSAN_LOULAN_1 = 36,  // �ղ�-¥��-2013,2011
	VSB_NISSAN_LOULAN_2 = 37,  // �ղ�-���-2010
	VSB_NISSAN_LANNIAO_1 = 38,  // �ղ�-����-2002
	VSB_NISSAN_LANNIAO_2 = 39,  // �ղ�-����-2003
	VSB_NISSAN_LANNIAO_3 = 40,  // �ղ�-����-2004
	VSB_NISSAN_GUISHI_1 = 41,  // �ղ�-��ʿ-2005
	VSB_NISSAN_XUANYI_1 = 42,  // �ղ�-����-2006
	VSB_NISSAN_XUANYI_2 = 43,  // �ղ�-����-2012����,2009,2007
	VSB_NISSAN_XUANYI_3 = 44,  // �ղ�-����-2014,2012
	VSB_NISSAN_XIAOKE_1 = 45,  // �ղ�-�п�-2009,2008
	VSB_NISSAN_XIAOKE_2 = 46,  // �ղ�-�п�-2013,2012,2011
	VSB_NISSAN_SUNNY_3 = 47,  // �ղ�-����-2004
	VSB_NISSAN_SUNNY_1 = 48,  // �ղ�-����-2006,2005
	VSB_NISSAN_SUNNY_2 = 49,  // �ղ�-����-2012,2011
	VSB_NISSAN_YIDA_1 = 50,  // �ղ�-�ô�-2008,2006,2005
	VSB_NISSAN_YIDA_2 = 51,  // �ղ�-�ô�-δ֪
	VSB_NISSAN_FENGDU_1 = 52,  // �ղ�-���-δ֪
	VSB_NISSAN_FENGYA_1 = 53,  // �ղ�-����-δ֪
	VSB_NISSAN_LIWEI_1 = 54,  // �ղ�-����-2008,2007
	VSB_NISSAN_LIWEI_2 = 55,  // �ղ�-����-2009
	VSB_NISSAN_LIWEI_3 = 56,  // �ղ�-����-2010
	VSB_NISSAN_LIWEI_4 = 57,  // �ղ�-����-2011,2010����,2008������
	VSB_NISSAN_JUNYI_1 = 58,  // �ղ�-����-2006
	VSB_NISSAN_QIDA_1 = 59,  // �ղ�-���-2006,2005
	VSB_NISSAN_QIDA_2 = 60,  // �ղ�-���-2009,2008
	VSB_NISSAN_QIDA_3 = 61,  // �ղ�-���-2013,2012,2011
	VSB_NISSAN_RUIQI_1 = 62   // �ղ�-����Ƥ��-2009������
}VSB_NISSAN_CLASS;

//�µ���Ʒ������
typedef enum _VSB_AUDI_CLASS
{
	VSB_AUDI_OTHER = 0,   // ������������
	VSB_AUDI_A3 = 1,   // �µ�A3
	VSB_AUDI_A4L = 2,   // �µ�A4L
	VSB_AUDI_A6L = 3,   // �µ�A6L
	VSB_AUDI_Q3 = 4,   // �µ�Q3
	VSB_AUDI_Q5 = 5,   // �µ�Q5
	VSB_AUDI_A1 = 6,   // �µ�A1
	VSB_AUDI_A4 = 7,   // �µ�A4
	VSB_AUDI_A5 = 8,   // �µ�A5
	VSB_AUDI_A6 = 9,   // �µ�A6
	VSB_AUDI_A7 = 10,  // �µ�A7
	VSB_AUDI_A8L = 11,  // �µ�A8L
	VSB_AUDI_Q7 = 12,  // �µ�Q7
	VSB_AUDI_S5 = 13,  // �µ�S5
	VSB_AUDI_TT = 14,  // �µ�TT
	VSB_AUDI_100 = 15,  // �µ�100
	VSB_AUDI_200 = 16,  // �µ�200
	VSB_AUDI_S7 = 17,  // �µ�S7
	VSB_AUDI_S8 = 18,  // �µ�S8
	VSB_AUDI_100_1 = 19,   // �µ�-100-δ֪
	VSB_AUDI_200_1 = 20,   // �µ�-200-δ֪
	VSB_AUDI_A1_1 = 21,   // �µ�-A1-2014,2013,2012
	VSB_AUDI_A3_1 = 22,   // �µ�-A3-2013,2010���ʰ�
	VSB_AUDI_A3_2 = 23,   // �µ�-A3-2013������,2011,2010
	VSB_AUDI_A4_1 = 24,   // �µ�-A4-2005����,2000���ڰ�
	VSB_AUDI_A4_2 = 25,   // �µ�-A4-2007,2006����,2004����
	VSB_AUDI_A4L_1 = 26,   // �µ�-A4L-2013
	VSB_AUDI_A5_1 = 27,   // �µ�-A5-2011,2010
	VSB_AUDI_A6_1 = 28,   // �µ�-A6-1996,1995,1991
	VSB_AUDI_A6L_1 = 29,   // �µ�-A6L-2008,2007,2006,2005
	VSB_AUDI_A6L_2 = 30,   // �µ�-A6L-2011,2010,2009
	VSB_AUDI_A6L_3 = 31,   // �µ�-A6L-2014,2013,2012
	VSB_AUDI_A7_1 = 32,   // �µ�-A7-2014,2013��ȡ��,2012,2011
	VSB_AUDI_A8L_1 = 33,   // �µ�-A8L-2006
	VSB_AUDI_A8L_2 = 34,   // �µ�-A8L-2009,2008
	VSB_AUDI_A8L_3 = 35,   // �µ�-A8L-2011
	VSB_AUDI_A8L_4 = 36,   // �µ�-A8L-2013,2012
	VSB_AUDI_Q3_1 = 37,   // �µ�-Q3-2014,2013,2012
	VSB_AUDI_Q5_1 = 38,   // �µ�-Q5-2012,2010�˶� 
	VSB_AUDI_Q5_2 = 39,   // �µ�-Q5-2012������,2010ԽҰ��
	VSB_AUDI_Q5_3 = 40,   // �µ�-Q5-2012��ȡ��,2011,2010,2009
	VSB_AUDI_Q5_4 = 41,   // �µ�-Q5-2013
	VSB_AUDI_Q7_1 = 42,   // �µ�-Q7-2007
	VSB_AUDI_Q7_2 = 43,   // �µ�-Q7-2014,2013
	VSB_AUDI_S7_1 = 44,   // �µ�-S7-2013
	VSB_AUDI_S8_1 = 45,   // �µ�-S8-2013
	VSB_AUDI_TT_2 = 46,   // �µ�-TT-2010,2008,2007
	VSB_AUDI_TT_3 = 47,   // �µ�-TT-2012,2011
	VSB_AUDI_TT_4 = 48,   // �µ�-TT-2013,2013,2011TTS
	VSB_AUDI_TT_1 = 49   // �µ�-TT-2008TTS
}VSB_AUDI_CLASS;

//���Դ���Ʒ������
typedef enum _VSB_MAZDA_CLASS
{
	VSB_MAZDA_OTHER = 0,   // ������������
	VSB_MAZDA_CX5 = 1,   // ���Դ�CX5
	VSB_MAZDA_2 = 2,   // ���Դ�2
	VSB_MAZDA_3 = 3,   // ���Դ�3
	VSB_MAZDA_6 = 4,   // ���Դ�6
	VSB_MAZDA_8 = 5,   // ���Դ�8
	VSB_MAZDA_COREWING = 6,   // ���
	VSB_MAZDA_CX7 = 7,   // ���Դ�CX7
	VSB_MAZDA_X5 = 8,   // ���Դ�X5
	VSB_MAZDA_5 = 9,   // ���Դ�5
	VSB_MAZDA_PREMACY = 10,  // �Ͽ�������
	VSB_MAZDA_MPV = 11,   // ���Դ�MPV
	VSB_MAZDA_CX5_1 = 12,   // ���Դ�-CX-5-2014,2013,2012����
	VSB_MAZDA_CX7_1 = 13,   // ���Դ�-CX-7-2014,2013,2011,2010
	VSB_MAZDA_2_1 = 14,   // ���Դ�-Mazda2����-2011,2009,2008,2007A
	VSB_MAZDA_3_1 = 15,   // ���Դ�-Mazda3����-2004,2002
	VSB_MAZDA_3_2 = 16,   // ���Դ�-Mazda3����-2009,2007
	VSB_MAZDA_3_3 = 17,   // ���Դ�-Mazda3����-2012,2010
	VSB_MAZDA_3_4 = 18,   // ���Դ�-Mazda3�ǳ�����-2013,2012
	VSB_MAZDA_5_1 = 19,   // ���Դ�-Mazda5-2010,2008,2007
	VSB_MAZDA_5_2 = 20,   // ���Դ�-Mazda5-2013,2012,2011
	VSB_MAZDA_6_2 = 21,   // ���Դ�-Mazda6-2006
	VSB_MAZDA_6_3 = 22,   // ���Դ�-Mazda6-2007
	VSB_MAZDA_8_1 = 23,   // ���Դ�-Mazda8-2013,2011,2010
	VSB_MAZDA_PREMACY_1 = 24,   // ���Դ�-������-2003
	VSB_MAZDA_PREMACY_2 = 25,   // ���Դ�-������-2006,2005,2004
	VSB_MAZDA_COREWING_1 = 26,   // ���Դ�-���-2012,2011,2010,2009
	VSB_MAZDA_COREWING_2 = 27,   // ���Դ�-������-2011,2010
	VSB_MAZDA_COREWING_3 = 28,   // ���Դ�-������-2012
	VSB_MAZDA_2_2 = 29,   // ���Դ�-Mazda2����(����)-2011,2010,2008
	VSB_MAZDA_6_1 = 30,   // ���Դ�-Mazda6-2004
	VSB_MAZDA_6_4 = 31   // ���Դ�-Mazda6-2014,2013,2012,2011,2010
}VSB_MAZDA_CLASS;

//ѩ������Ʒ������
typedef enum _VSB_CHEVROLET_CLASS
{
	VSB_CHEVROLET_OTHER = 0,   // ������������
	VSB_CHEVROLET_NEWAVEO = 1,   // ��Ψŷ
	VSB_CHEVROLET_EPICA = 2,   // ����
	VSB_CHEVROLET_CRUZE = 3,   // ��³��
	VSB_CHEVROLET_CAPTIVA = 4,   // ������
	VSB_CHEVROLET_MALIBU = 5,   // ����
	VSB_CHEVROLET_SAIL = 6,   // ��ŷ
	VSB_CHEVROLET_CAMARO = 7,   // ������
	VSB_CHEVROLET_LECHENG = 8,   // �ֳ�
	VSB_CHEVROLET_LOVA = 9,   // �ַ�
	VSB_CHEVROLET_OLDAVEO = 10,  // �ֳ�-�ϿΨŷ
	VSB_CHEVROLET_SPARK = 11,  // �ֳ�
	VSB_CHEVROLET_SAILSRV = 12,   // ��ŷSRV
	VSB_CHEVROLET_LOVA_1 = 13,   // ѩ����-�ַ�-2009,2008,2007,2006
	VSB_CHEVROLET_LOVA_2 = 14,   // ѩ����-�ַ�-2010
	VSB_CHEVROLET_SPARK_1 = 15,   // ѩ����-�ֳ�-2010,2009,2006,2005,2004
	VSB_CHEVROLET_SPARK_2 = 16,   // ѩ����-�ֳ�-2010�˶���
	VSB_CHEVROLET_OLDAVEO_1 = 17,   // ѩ����-�ֳ�-2005
	VSB_CHEVROLET_OLDAVEO_2 = 18,   // ѩ����-�ֳ�-2010,2009,2008
	VSB_CHEVROLET_EPICA_1 = 19,   // ѩ����-����-2005
	VSB_CHEVROLET_EPICA_3 = 20,   // ѩ����-����-2012,2011,2010
	VSB_CHEVROLET_EPICA_4 = 21,   // ѩ����-����-2012,2011,2010�����
	VSB_CHEVROLET_EPICA_5 = 22,   // ѩ����-����-2013
	VSB_CHEVROLET_NEWAVEO_1 = 23,   // ѩ����-��Ψŷ����-2013,2012,2011
	VSB_CHEVROLET_CAPTIVA_1 = 24,   // ѩ����-������-2010,2008
	VSB_CHEVROLET_CAPTIVA_2 = 25,   // ѩ����-������-2014,2013,2012,2011
	VSB_CHEVROLET_KEMAILUO_1 = 26,   // ѩ����-������-2012,2011
	VSB_CHEVROLET_CRUZE_1 = 27,   // ѩ����-��³��-2014,2013,2012,2011,2010,2009
	VSB_CHEVROLET_SAIL_1 = 28,   // ѩ����-��ŷ����-2005
	VSB_CHEVROLET_SAIL_2 = 29,   // ѩ����-��ŷ����-2013,2011,2010
	VSB_CHEVROLET_MALIBU_1 = 30,   // ѩ����-����-2014,2013,2012
	VSB_CHEVROLET_EPICA_2 = 31   // ѩ����-����-2009,2008,2007
}VSB_CHEVROLET_CLASS;

//ѩ������Ʒ������
typedef enum _VSB_CITROEN_CLASS
{
	VSB_CITROEN_OTHER = 0,   // ������������
	VSB_CITROEN_C2 = 1,   // ѩ����C2
	VSB_CITROEN_C4L = 2,   // ѩ����C4L
	VSB_CITROEN_C5 = 3,   // ѩ����C5
	VSB_CITROEN_ELYSEE = 4,   // ����������
	VSB_CITROEN_CQUATRELIANGXIANG = 5,   // ��������
	VSB_CITROEN_CQUATRESANXIANG = 6,   // ��������
	VSB_CITROEN_SAEAPICASSO = 7,   // ����-�ϼ���
	VSB_CITROEN_PICASSO = 8,   // �ϼ���
	VSB_CITROEN_CTRIOMPHE = 9,   // ����
	VSB_CITROEN_XSARA = 10,  // ����  
	VSB_CITROEN_SHENLONGFUKANG = 11,  // ��������
	VSB_CITROEN_CHANGANDS = 12,   // ����DS
	VSB_CITROEN_C2_1 = 13,   // ѩ����-C2-2012,2010,2008,2007,2006
	VSB_CITROEN_C4L_1 = 14,   // ѩ����-C4L-2014,2013
	VSB_CITROEN_C4PICASSO_1 = 15,   // ѩ����-C4�ϼ���-2009���ʰ�
	VSB_CITROEN_C5_1 = 16,   // ѩ����-C5-2012,2011,2010
	VSB_CITROEN_CQUATRESANXIANG_1 = 17,   // ѩ����-��������-2013,2012
	VSB_CITROEN_CQUATRELIANGXIANG_1 = 18,   // ѩ����-��������-2011,2010,2009,2008
	VSB_CITROEN_CTRIOMPHE_1 = 19,   // ѩ����-����-2010,2009,2008,2006
	VSB_CITROEN_FUKANG_1 = 20,   // ѩ����-����-2006,2005,2004,2003,2002
	VSB_CITROEN_ELYSEE_1 = 21,   // ѩ����-����������-2006,2005,2004,2003,2002
	VSB_CITROEN_ELYSEE_2 = 22,   // ѩ����-����������-2013,2012,2011,2010,2009,2008,2007
	VSB_CITROEN_SAEAPICASSO_1 = 23    // ѩ����-����-�ϼ���-2014 
}VSB_CITROEN_CLASS;

//�ִ���Ʒ������
typedef enum _VSB_HYUNDAI_CLASS
{
	VSB_HYUNDAI_OTHER = 0,   // ������������
	VSB_HYUNDAI_IX35 = 1,   // �ִ�IX35
	VSB_HYUNDAI_LANGDONG = 2,   // �ʶ�
	VSB_HYUNDAI_MOINCA = 3,   // ��Ԧ
	VSB_HYUNDAI_SHENGDA = 4,   // ʤ��
	VSB_HYUNDAI_VERNA = 5,   // ����
	VSB_HYUNDAI_RUIYI = 6,   // ����
	VSB_HYUNDAI_SONATAEIGHT = 7,   // ��������
	VSB_HYUNDAI_TUCSON = 8,   // ;ʤ
	VSB_HYUNDAI_YUEDONG = 9,   // �ö�
	VSB_HYUNDAI_ELANTRA = 10,  // ������
	VSB_HYUNDAI_GRANDSANTAFE = 11,  // ����
	VSB_HYUNDAI_COUPE = 12,  // ����
	VSB_HYUNDAI_MATRIX = 13,  // ����
	VSB_HYUNDAI_ACCENT = 14,  // ������
	VSB_HYUNDAI_IX30 = 15,  // �ִ�IX30
	VSB_HYUNDAI_SONATA = 16,  // ������
	VSB_HYUNDAI_REFINE = 17,  // �ִ��������
	VSB_HYUNDAI_MISTRA = 18,  // ��ͼ
	VSB_HYUNDAI_SONATAYUFENG = 19,  // ������-����
	VSB_HYUNDAI_SANTAFE = 20,  // �ִ�ʥ���
	VSB_HYUNDAI_HUIYI = 21,   // ���ڻ���
	VSB_HYUNDAI_I30_1 = 22,   // �ִ�-i30-2010,2009
	VSB_HYUNDAI_IX35_1 = 23,   // �ִ�-ix35-2012,2011,2010
	VSB_HYUNDAI_YILANTE_1 = 24,   // �ִ�-������-2006,2005,2004
	VSB_HYUNDAI_YILANTE_2 = 25,   // �ִ�-������-2007����
	VSB_HYUNDAI_YILANTE_3 = 26,   // �ִ�-������-2011
	VSB_HYUNDAI_SHENGDA_1 = 27,   // �ִ�-ȫ��ʤ��-2013,2012
	VSB_HYUNDAI_MINGTU_1 = 28,   // �ִ�-��ͼ-2014,2013
	VSB_HYUNDAI_MINGYU_1 = 29,   // �ִ�-��Ԧ-2013,2011,2009
	VSB_HYUNDAI_SHENGDAFEI_1 = 30,   // �ִ�-ʥ���-δ֪
	VSB_HYUNDAI_YUXIANG_1 = 31,   // �ִ�-����-2005���ʰ�
	VSB_HYUNDAI_YUXIANG_2 = 32,   // �ִ�-����-2006,2005
	VSB_HYUNDAI_YUEDONG_1 = 33,   // �ִ�-�ö�-2010,2009,2008
	VSB_HYUNDAI_YUEDONG_2 = 34,   // �ִ�-�ö�-2012,2011
	VSB_HYUNDAI_SHENGDA_2 = 35,   // �ִ�-��ʤ��-2009,2006
	VSB_HYUNDAI_SHENGDA_3 = 36,   // �ִ�-��ʤ��-2012,2011,2010
	VSB_HYUNDAI_LANGDONG_1 = 37,   // �ִ�-�ʶ�-2013,2012
	VSB_HYUNDAI_GERUI_1 = 38,   // �ִ�-����-δ֪
	VSB_HYUNDAI_RUIYI_1 = 39,   // �ִ�-����-2014
	VSB_HYUNDAI_RUINA_1 = 40,   // �ִ�-��������-2013,2010
	VSB_HYUNDAI_RUINA_2 = 41,   // �ִ�-��������-2014,2013,2011
	VSB_HYUNDAI_RUIFENG_1 = 42,   // �ִ�-���-δ֪
	VSB_HYUNDAI_SUONATA_1 = 43,   // �ִ�-������-2008,2007,2006,2004,2003��׼��
	VSB_HYUNDAI_SUONATA_2 = 44,   // �ִ�-������-2010,2009,2008,2006,2004
	VSB_HYUNDAI_SOUNATA_3 = 45,   // �ִ�-��������-2011,2010
	VSB_HYUNDAI_WEILAKESI_1 = 46,   // �ִ�-ά����˹-2012,2010,2008,2007
	VSB_HYUNDAI_MEIJIA_1 = 47,   // �ִ�-����-δ֪
	VSB_HYUNDAI_JINKOUHUIYI_1 = 48,   // �ִ�-���ڻ���-δ֪
	VSB_HYUNDAI_TUSHENG_1 = 49,   // �ִ�-;ʤ-2005
	VSB_HYUNDAI_TUSHENG_2 = 50,   // �ִ�-;ʤ-2011,2009,2008,2006
	VSB_HYUNDAI_TUSHENG_3 = 51,   // �ִ�-;ʤ-2013
	VSB_HYUNDAI_KUPAI_1 = 52,   // �ִ�-����-δ֪
	VSB_HYUNDAI_YASHENTE_1 = 53,   // �ִ�-������-2008,2006
	VSB_HYUNDAI_YASHENTE_2 = 54,   // �ִ�-������-2011
	VSB_HYUNDAI_LINGXIANG_1 = 55,   // �ִ�-����-2009,2008
	VSB_HYUNDAI_FEISI_1 = 56    // �ִ�-��˼-2011
}VSB_HYUNDAI_CLASS;

//������Ʒ������
typedef enum _VSB_CHERY_CLASS
{
	VSB_CHERY_OTHER = 0,   // ������������
	VSB_CHERY_A1 = 1,   // ����A1
	VSB_CHERY_A3 = 2,   // ����A3
	VSB_CHERY_EASTAR = 3,   // ����֮��
	VSB_CHERY_FULWIN = 4,   // ����
	VSB_CHERY_QQ = 5,   // ����QQ
	VSB_CHERY_E5 = 6,   // ����E5
	VSB_CHERY_COWIN = 7,   // ����
	VSB_CHERY_TIGGO = 8,   // ��
	VSB_CHERY_A5 = 9,   // ����A5
	VSB_CHERY_S16 = 10,  // ����S16
	VSB_CHERY_YOUYA = 11,  // ����
	VSB_CHERY_V5 = 12,  // ����V5
	VSB_CHERY_E3 = 13,   // ����E3
	VSB_CHERY_A1_1 = 14,     // ����-A1-2011,2008,2007
	VSB_CHERY_A3LIANGXIANG_1 = 15,     // ����-A3����-2012,2010,2009
	VSB_CHERY_A5_1 = 16,     // ����-A5-2009,2007,2006
	VSB_CHERY_QQ_1 = 17,     // ����-QQ-2006,2005,2004
	VSB_CHERY_QQ_2 = 18,     // ����-QQ-2010,2007,2006
	VSB_CHERY_QQ_3 = 19,     // ����-QQ-2012,2011,2010,2009,2007
	VSB_CHERY_QQ_4 = 20,     // ����-QQ-2012�˶���
	VSB_CHERY_QQ_5 = 21,     // ����-QQ-2013
	VSB_CHERY_DONGFANGZHIZI_1 = 22,     // ����-����֮��-2005,2004,2003
	VSB_CHERY_DONGFANGZHIZI_2 = 23,     // ����-����֮��-2007,2006
	VSB_CHERY_DONGFANGZHIZI_3 = 24,     // ����-����֮��CROSS-2009,2008,2007
	VSB_CHERY_YOUYA_1 = 25,     // ����-����-δ֪
	VSB_CHERY_E3_1 = 26,     // ����-����E3-2013
	VSB_CHERY_E5_1 = 27,     // ����-����E5-2014,2012,2011
	VSB_CHERY_QIYUN1_1 = 28,     // ����-����1-2010
	VSB_CHERY_QIYUN1_2 = 29,     // ����-����1-2012
	VSB_CHERY_QIYUN_1 = 30,     // ����-����-2004
	VSB_CHERY_QIYUN_2 = 31,     // ����-����-2009,2008,2007,2006
	VSB_CHERY_QIYUN2_1 = 32,     // ����-����2-2012
	VSB_CHERY_QIYUN2_2 = 33,     // ����-����2-2012������,2010
	VSB_CHERY_QIYUN3_1 = 34,     // ����-����3-2010
	VSB_CHERY_RUIHU_1 = 35,     // ����-��-2007,2006,2005
	VSB_CHERY_RUIHU_2 = 36,     // ����-��-2009,2007
	VSB_CHERY_RUIHU_3 = 37,     // ����-��-2012,2011
	VSB_CHERY_RUIHU_4 = 38,     // ����-��-2013,2012�Զ�DVVT������
	VSB_CHERY_RUIHU_5 = 39,     // ����-��-2013��Ӣ�������,2012��Ӣ��������
	VSB_CHERY_FENGYUN2SANXIANG_1 = 40,     // ����-����2����-2010
	VSB_CHERY_AIRUIZE7_1 = 41     // ����-������7-2014,2013
}VSB_CHERY_CLASS;

//������Ʒ������
typedef enum _VSB_KIA_CLASS
{
	VSB_KIA_OTHER = 0,   // ������������
	VSB_KIA_K2 = 1,   // ����K2
	VSB_KIA_K3 = 2,   // ����K3
	VSB_KIA_K5 = 3,   // ����K5
	VSB_KIA_RIO = 4,   // ��ŷ
	VSB_KIA_CERATO = 5,   // ����ͼ
	VSB_KIA_SPORTAGER = 6,   // ʨ��
	VSB_KIA_SOUL = 7,   // ���
	VSB_KIA_ZHIPAO = 8,   // ����
	VSB_KIA_CARENS = 9,   // ����
	VSB_KIA_CARNIVAL = 10,  // �λ�
	VSB_KIA_OPTIMA = 11,  // Զ��
	VSB_KIA_OPIRUS = 12,  // ŷ����˹
	VSB_KIA_MAXIMA = 13,  // ǧ����
	VSB_KIA_FORTE = 14,  // �����
	VSB_KIA_SORENTO = 15,  // ������
	VSB_KIA_K2_1 = 16,   // ����-K2-2013,2012,2011
	VSB_KIA_K3_1 = 17,   // ����-K3-2012
	VSB_KIA_K5_1 = 18,   // ����-K5-2012,2011
	VSB_KIA_RUIOU_1 = 19,   // ����-RIO��ŷ-2009,2007
	VSB_KIA_QIANLIMA_1 = 20,   // ����-ǧ����-2004
	VSB_KIA_QIANLIMA_2 = 21,   // ����-ǧ����-2006,2005
	VSB_KIA_JIAHUA_1 = 22,   // ����-�λ�-δ֪
	VSB_KIA_XINJIALE_1 = 23,   // ����-�¼���-2011
	VSB_KIA_ZHIPAO_1 = 24,   // ����-����-2014,2012,2011,2010
	VSB_KIA_SHIPAO_1 = 25,  // ����-ʨ��-2008,2007,2005
	VSB_KIA_SHIPAO_2 = 26,  // ����-ʨ��-2011,2009
	VSB_KIA_SHIPAO_3 = 27,  // ����-ʨ��-2012
	VSB_KIA_SHIPAO_4 = 28,  // ����-ʨ��-2013
	VSB_KIA_FURUIDI_1 = 29,  // ����-�����-2012,2011,2009
	VSB_KIA_FURUIDI_2 = 30,  // ����-�����-2014
	VSB_KIA_XIUER_1 = 31,  // ����-���-2012,2010
	VSB_KIA_SUOLANTUO_1 = 32,  // ����-������-2006
	VSB_KIA_SUOLANTUO_2 = 33,  // ����-������-2012,2010,2009
	VSB_KIA_SAILATU_1 = 34,  // ����-����ͼ-2006,2005
	VSB_KIA_SAILATU_2 = 35,  // ����-����ͼ-2007
	VSB_KIA_SAILATU_3 = 36,  // ����-����ͼ-2012,2010GLS
	VSB_KIA_YUANJIAN_1 = 37   // ����-Զ��-δ֪
}VSB_KIA_CLASS;

//������Ʒ������
typedef enum _VSB_BENZ_CLASS
{
	VSB_BENZ_OTHER = 0,   // ������������
	VSB_BENZ_C = 1,   // ����C��
	VSB_BENZ_E = 2,   // ����E��
	VSB_BENZ_GLK = 3,   // ����GLK��
	VSB_BENZ_WEITING = 4,   // ����-PINYIN
	VSB_BENZ_SPRINTER = 5,   // ����
	VSB_BENZ_VIANO = 6,   // Ψ��ŵ
	VSB_BENZ_M = 7,   // ����Mϵ
	VSB_BENZ_CLK = 8,   // ����CLKϵ
	VSB_BENZ_G = 9,   // ����Gϵ
	VSB_BENZ_GL = 10,  // ����GLϵ
	VSB_BENZ_R = 11,  // ����Rϵ
	VSB_BENZ_S = 12,  // ����Sϵ
	VSB_BENZ_A = 13,  // ����Aϵ
	VSB_BENZ_SMART = 14,  // ˹����(����)
	VSB_BENZ_B = 15,  // ����Bϵ
	VSB_BENZ_SLK = 16,  // ����SLKϵ
	VSB_BENZ_MB100 = 17,  // ����MB100
	VSB_BENZ_VITO = 18,  // ����
	VSB_BENZ_CLS = 19,  // ����CLSϵ
	VSB_BENZ_SL = 20,   // ����SLϵ
	VSB_BENZ_AJI_1 = 21,   // ����-A��-2011,2009
	VSB_BENZ_AJI_2 = 22,   // ����-A��-2013
	VSB_BENZ_BJI_1 = 23,   // ����-B��-2010,2009
	VSB_BENZ_CJI_1 = 24,   // ����-C��-2010,2008,2007ʱ����
	VSB_BENZ_CJI_2 = 25,   // ����-C��-2013,2011,CGI
	VSB_BENZ_CJI_3 = 26,   // ����-C��-2013,2011ʱ����
	VSB_BENZ_EJI_1 = 27,   // ����-E��-2002
	VSB_BENZ_EJI_2 = 28,   // ����-E��-2007,2006
	VSB_BENZ_EJI_3 = 29,   // ����-E��-2013,2012,2011,2010,2009
	VSB_BENZ_EJI_4 = 30,   // ����-E��-2013,2012,2011,2010,2009ʱ����
	VSB_BENZ_GLKJI_1 = 31,   // ����-GLK��-2012,2011
	VSB_BENZ_GLKJI_2 = 32,   // ����-GLK��-2012,2011������,2008
	VSB_BENZ_GLKJI_3 = 33,   // ����-GLK��-2014,2013
	VSB_BENZ_GLJI_1 = 34,   // ����-GL��-2011
	VSB_BENZ_GLJI_2 = 35,   // ����-GL��-2011�����,2010
	VSB_BENZ_GLJI_3 = 36,   // ����-GL��-2012,2010������
	VSB_BENZ_GJI_1 = 37,   // ����-G��-2013,2010,2009
	VSB_BENZ_MB100_1 = 38,   // ����-MB100-2000
	VSB_BENZ_MLJI_1 = 39,   // ����-ML��-2006,2005
	VSB_BENZ_MLJI_2 = 40,   // ����-ML��-2010,2008
	VSB_BENZ_MLJI_3 = 41,   // ����-ML��-2014,2012
	VSB_BENZ_RJI_1 = 42,   // ����-R��-2006
	VSB_BENZ_RJI_2 = 43,   // ����-R��-2007
	VSB_BENZ_RJI_3 = 44,   // ����-R��-2014,2011,2010,2009
	VSB_BENZ_SLKJI_2 = 45,   // ����-SLK��-2006,2004
	VSB_BENZ_SLKJI_3 = 46,   // ����-SLK��-2010,2009
	VSB_BENZ_SLKJI_1 = 47,   // ����-SLK��-2011
	VSB_BENZ_SJI_1 = 48,   // ����-S��-2004
	VSB_BENZ_SJI_2 = 49,   // ����-S��-2009_Hybrid,2008,2006
	VSB_BENZ_SJI_3 = 50,   // ����-S��-2009,2008������
	VSB_BENZ_SJI_4 = 51,   // ����-S��-2012,2011,2010
	VSB_BENZ_LINGTE_1 = 52,   // ����-����-2013,2012,2011
	VSB_BENZ_WEIYANUO_1 = 53,   // ����-Ψ��ŵ-2010,2006,2004
	VSB_BENZ_WEIYANUO_2 = 54,   // ����-Ψ��ŵ-2014,2013,2012,2011
	VSB_BENZ_WEITING_1 = 55,   // ����-����-2013,2011,2010
	VSB_BENZ_KECHE_1 = 56    // ����-�ͳ�����1-A��
}VSB_BENZ_CLASS;

//˹�´���Ʒ������
typedef enum _VSB_SKODA_CLASS
{
	VSB_SKODA_OTHER = 0,   // ������������
	VSB_SKODA_HAORUI = 1,   // ���
	VSB_SKODA_FABIA = 2,   // ����
	VSB_SKODA_OCTAVIA = 3,   // ����
	VSB_SKODA_SUPERB = 4,   // ����
	VSB_SKODA_SPACEBACK = 5,   // 꿶�
	VSB_SKODA_RAPID = 6,   // ���
	VSB_SKODA_YETI = 7,    // Ұ��
	VSB_SKODA_HAORUI_1 = 8,      // ˹�´�-���-2013,2012,2010,2009
	VSB_SKODA_MINGRUI_1 = 9,      // ˹�´�-����-2009,2008,2007
	VSB_SKODA_MINGRUI_2 = 10,      // ˹�´�-����-2014,2013,2012,2011,2010
	VSB_SKODA_MINGRUI_3 = 11,      // ˹�´�-����RS-2010
	VSB_SKODA_XINRUI_1 = 12,      // ˹�´�-���-2013��ѡ��
	VSB_SKODA_JINGRUI_1 = 13,      // ˹�´�-����-2011,2009,2008
	VSB_SKODA_JINGRUI_2 = 14,      // ˹�´�-����-2014,2013,2012
	VSB_SKODA_JINGRUI_3 = 15,      // ˹�´�-����-2014,2013,2012Sport��
	VSB_SKODA_SUPAI_1 = 16,      // ˹�´�-����-2013
	VSB_SKODA_YEDI_1 = 17      // ˹�´�-Ұ��-2014,2013
}VSB_SKODA_CLASS;

//������Ʒ������
typedef enum _VSB_DONGFENG_CLASS
{
	VSB_DONGFENG_OTHER = 0,   // ������������
	VSB_DONGFENG_JOYEARX5 = 1,   // ����X5
	VSB_DONGFENG_LINGZHI = 2,   // ����
	VSB_DONGFENG_JOYEARX3 = 3,   // ����X3
	VSB_DONGFENG_JOYEAR = 4,   // ����
	VSB_DONGFENG_FENGXINGCM7 = 5,   // ����CM7
	VSB_DONGFENG_YUFENG = 6,   // ����
	VSB_DONGFENG_FENGSHENA60 = 7,   // ����A60
	VSB_DONGFENG_FENGSHENS30 = 8,   // ����S30
	VSB_DONGFENG_FENGSHENH30CROSS = 9,   // ����H30-CROSS
	VSB_DONGFENG_PICKUP = 10,  // ����Ƥ��
	VSB_DONGFENG_ZHONGXINGMIANBAOCHE = 11,  // �������������
	VSB_DONGFENG_XIAOXINGMIANBAOCHE = 12,  // ����С�������
	VSB_DONGFENG_ZHONGXINGVAN = 13,  // �������ͻ���
	VSB_DONGFENG_QINGXINGXIANGSHIVAN = 14,  // ����������ʽ����
	VSB_DONGFENG_QINGZHONGXINGVAN = 15,  // ������������ͨ����
	VSB_DONGFENG_FENGSHENMERCURY = 16,  // ����ˮ��
	VSB_DONGFENG_SUCCE = 17,  // ˧��
	VSB_DONGFENG_ODIN = 18,  // �¶�
	VSB_DONGFENG_YUMSUN = 19,  // ����
	VSB_DONGFENG_RUIQI = 20,  // ����
	VSB_DONGFENG_FENGGUANG = 21,  // ���
	VBR_DONGFENG_C35_1 = 22,   // ����-C35-2013
	VBR_DONGFENG_K07_1 = 23,   // ����-K07-2008
	VBR_DONGFENG_K07_2 = 24,   // ����-K07-2010,2006
	VBR_DONGFENG_V21_1 = 25,   // ����-V21-2011
	VBR_DONGFENG_JIALONG_1 = 26,   // ����-�������-�ػ���
	VBR_DONGFENG_XKFG_1 = 27,   // ����-����С�����-2013
	VBR_DONGFENG_CV03_1 = 28,   // ����-����CV03-2012
	VBR_DONGFENG_KAIPUTE_1 = 29,   // ����-������-C390
	VBR_DONGFENG_DUOLIKA_1 = 30,   // ����-������-S2800
	VBR_DONGFENG_DUOLIKA_2 = 31,   // ����-������-XL�п�
	VBR_DONGFENG_DUOLIKA_3 = 32,   // ����-������-�п�
	VBR_DONGFENG_TIANJIN_1 = 33,   // ����-���-4X2�ػ���
	VBR_DONGFENG_TIANJIN_2 = 34,   // ����-���-A��
	VBR_DONGFENG_XBW_1 = 35,   // ����-С����-�Ῠ1
	VBR_DONGFENG_XBW_2 = 36,   // ����-С����-�Ῠ2
	VBR_DONGFENG_MENGKA_1 = 37,   // ����-�ο�-�Ῠ
	VBR_DONGFENG_FURUIKA_1 = 38,   // ����-����-�Ῠ1
	VBR_DONGFENG_RUIQI_1 = 39,   // ����-����Ƥ��-2013,2010,2009
	VBR_DONGFENG_A60_1 = 40,   // �������-A60-2014,2012
	VBR_DONGFENG_H30_1 = 41,   // �������-H30-Cross-2012,2011
	VBR_DONGFENG_H30_2 = 42,   // �������-H30-Cross-2014,2013
	VBR_DONGFENG_H30_3 = 43,   // �������-H30-2012
	VBR_DONGFENG_JINGYI_1 = 44,   // �������-����-2014_2012LV,2011������
	VBR_DONGFENG_JINGYI_2 = 45,   // �������-����-2014_2012XL,2011,2010,2009,2008,2007
	VBR_DONGFENG_JINGYI_3 = 46,   // �������-����X5-2014,2013
	VBR_DONGFENG_LINGZHI_1 = 47,   // �������-����-2004
	VBR_DONGFENG_LINGZHI_2 = 48,   // �������-����-2011,2008,2007
	VBR_DONGFENG_LINGZHI_3 = 49,   // �������-����-2011Q3��׼��,2010Q7
	VBR_DONGFENG_LINGZHI_4 = 50,   // �������-����-2014_2013M3
	VBR_DONGFENG_LINGZHI_5 = 51   // �������-����-2014_2013V3,2011M3_���ð�_������
}VSB_DONGFENG_CLASS;

//���ǵ���Ʒ������
typedef enum _VSB_BYD_CLASS
{
	VSB_BYD_OTHER = 0,   // ������������
	VSB_BYD_F0 = 1,   // ���ǵ�F0
	VSB_BYD_F3 = 2,   // ���ǵ�F3
	VSB_BYD_F3R = 3,   // ���ǵ�F3R
	VSB_BYD_F6 = 4,   // ���ǵ�F6
	VSB_BYD_G3 = 5,   // ���ǵ�G3
	VSB_BYD_G3R = 6,   // ���ǵ�G3R
	VSB_BYD_G6 = 7,   // ���ǵ�G6
	VSB_BYD_L3 = 8,   // ���ǵ�L3
	VSB_BYD_M6 = 9,   // ���ǵ�M6
	VSB_BYD_S6 = 10,  // ���ǵ�S6
	VSB_BYD_SURUI = 11,  // ����
	VSB_BYD_FOLEL = 12,  // �ش�������
	VSB_BYD_SIRUI = 13,  // ˼��
	VSB_BYD_MT5 = 14,  // ���ǵ�MT5(����)
	VSB_BYD_F0_1 = 15,        // ���ǵ�-F0-2013,2012,2011,2010,2009,2008
	VSB_BYD_F3R_1 = 16,        // ���ǵ�-F3R-2011,2009,2008,2007
	VSB_BYD_F6_1 = 17,        // ���ǵ�-F6-2011,2009,2008
	VSB_BYD_G3R_1 = 18,        // ���ǵ�-G3R-2011
	VSB_BYD_G6_1 = 19,        // ���ǵ�-G6-2013,2012,2011
	VSB_BYD_L3_1 = 20,        // ���ǵ�-L3-2013,2012,2011,2010
	VSB_BYD_M6_1 = 21,        // ���ǵ�-M6-2013,2011,2010
	VSB_BYD_S6_1 = 22,        // ���ǵ�-S6-2014,2013,2012,2011
	VSB_BYD_FULAIER_1 = 23,        // ���ǵ�-������-2005������
	VSB_BYD_SURUI_1 = 24        // ���ǵ�-����-2014,2013,2012
}VSB_BYD_CLASS;

//��ľ��Ʒ������
typedef enum _VSB_SUZUKI_CLASS
{
	VSB_SUZUKI_OTHER = 0,   // ������������
	VSB_SUZUKI_ALTO = 1,   // ��������
	VSB_SUZUKI_SCROSS = 2,   // ��Ԧ
	VSB_SUZUKI_SWIFT = 3,   // ����
	VSB_SUZUKI_SX4 = 4,   // ����
	VSB_SUZUKI_LINGYANG = 5,   // ����
	VSB_SUZUKI_BEIDOUXING = 6,   // ������
	VSB_SUZUKI_LIANAA6 = 7,   // ������-A6
	VSB_SUZUKI_LANDY = 8,   // �˵�
	VSB_SUZUKI_SPLASH = 9,   // ��ϲ
	VSB_SUZUKI_GRANDVITARA = 10,  // ����ά����
	VSB_SUZUKI_JIMNY = 11,  // ��ķ��
	VSB_SUZUKI_KAZASHI = 12,  // ������
	VSB_SUZUKI_LIANA = 13,   // ������
	VSB_SUZUKI_LIANA_1 = 14,     // ��ľ-����������-2012,2011,2010,2008,2007,2005
	VSB_SUZUKI_LIANA_2 = 15,     // ��ľ-����������-2013,2012,2011
	VSB_SUZUKI_BEIDOUXING_1 = 16,     // ��ľ-������-2012,2011,2010,2009,2008,2007,2005,2004��׼��
	VSB_SUZUKI_BEIDOUXING_2 = 17,     // ��ľ-������-2013,2012,2011,2010,2009,2008,2007,2005,2004,2003
	VSB_SUZUKI_BEIDOUXING_3 = 18,     // ��ľ-������-2013,2012,2011,2010,2009,2008,2007,2005,2004,2003������
	VSB_SUZUKI_BEIDOUXING_4 = 19,     // ��ľ-������-2013X5
	VSB_SUZUKI_JIMUNI_1 = 20,     // ��ľ-��ķ��-2011,2010,2009,2007
	VSB_SUZUKI_JIMUNI_2 = 21,     // ��ľ-��ķ��-2012
	VSB_SUZUKI_SX4_1 = 22,     // ��ľ-����SX4����-2008,2006
	VSB_SUZUKI_SX4_2 = 23,     // ��ľ-����SX4����-2010,2009
	VSB_SUZUKI_SX4_3 = 24,     // ��ľ-����SX4����-2011A,2009,2008,2007
	VSB_SUZUKI_SX4_4 = 25,     // ��ľ-����SX4����-2011B
	VSB_SUZUKI_SX4_5 = 26,     // ��ľ-����SX4����-2013,2012,2011
	VSB_SUZUKI_ALTO_1 = 27,     // ��ľ-����-2006,2001,2000,1999,1993��׼��
	VSB_SUZUKI_ALTO_2 = 28,     // ��ľ-����-2006,2004,2001,2000,1999,1993
	VSB_SUZUKI_ALTO_3 = 29,     // ��ľ-����-2013
	VSB_SUZUKI_ALTO_4 = 30,     // ��ľ-����-2014,2012,2011,2010,2009
	VSB_SUZUKI_SPLASH_1 = 31,     // ��ľ-��ϲ-2013,2012,2011
	VSB_SUZUKI_LANDY_1 = 32,     // ��ľ-�˵�-2011,2010,2007
	VSB_SUZUKI_LINGYANG_2 = 33,     // ��ľ-����-2006,2004,2003
	VSB_SUZUKI_LINGYANG_3 = 34,     // ��ľ-����-2009,2008,2007
	VSB_SUZUKI_LINGYANG_4 = 35,     // ��ľ-����-2011
	VSB_SUZUKI_LINGYANG_5 = 36,     // ��ľ-����-2012
	VSB_SUZUKI_GRANDVITARA_1 = 37,     // ��ľ-����ά����-2011,2008,2007,2006
	VSB_SUZUKI_FENGYU_1 = 38,     // ��ľ-��Ԧ-2014
	VSB_SUZUKI_SWIFT_1 = 39,     // ��ľ-����-2011_1.3L,2009,2008,2007,2005
	VSB_SUZUKI_SWIFT_2 = 40,     // ��ľ-����-2012,2011
	VSB_SUZUKI_KINGCHANG_1 = 41,     // ��ľ-������-2004
	VSB_SUZUKI_LINGYANG_1 = 42     // ��ľ-����-2002
}VSB_SUZUKI_CLASS;

//������Ʒ������
typedef enum _VSB_SGMW_CLASS
{
	VSB_SGMW_OTHER = 0,   // ������������
	VSB_SGMW_HONGGUANG = 1,   // ������
	VSB_SGMW_HONGGUANGS = 2,   // ������S
	VSB_SGMW_ZHIGUANG = 3,   // ����֮��
	VSB_SGMW_RONGGUANGS = 4,   // �����ٹ�S
	VSB_SGMW_RONGGUANG = 5,   // �����ٹ�
	VSB_SGMW_HONGTU = 6,   // �����;
	VSB_SGMW_XINGWANG = 7,   // ��������
	VSB_SGMW_YANGGUANG = 8,   // �������
	VSB_SGMW_XIAOXUANFENG = 9,   // ����С����
	VSB_SGMW_WULINGZHIGUANG_1 = 10,       // ����-����֮��-2010,2009��ҵ
	VSB_SGMW_WULINGZHIGUANG_2 = 11,       // ����-����֮��-2010�̳���,������
	VSB_SGMW_WULINGZHIGUANG_3 = 12,       // ����-����֮��-2010������,2008��ʽ,2007
	VSB_SGMW_XINGWANG_1 = 13,       // ����-���������-2003
	VSB_SGMW_XINGWANG_2 = 14,       // ����-���������-2009��׼
	VSB_SGMW_XINGWANG_3 = 15,       // ����-���������-2010,2009,2007,2006,2005,2004
	VSB_SGMW_HONNGUANG_1 = 16,       // ����-���-2013,2010
	VSB_SGMW_HONNGUANG_2 = 17,       // ����-���-2014,2013S
	VSB_SGMW_XIAOXUANFENG_1 = 18,       // ����-С����-2006
	VSB_SGMW_YANGGUANG_1 = 19,       // ����-���-2006,2005,2004
	VSB_SGMW_YANGGUANG_2 = 20,       // ����-���-2008,2007
	VSB_SGMW_YANGGUANG_3 = 21,       // ����-���-2009,2006,2005�ֶ���׼��
	VSB_SGMW_RONGGUANG_1 = 22,       // ����-�ٹ������-2012,2011,2008����
	VSB_SGMW_RONGGUANG_2 = 23,       // ����-�ٹ������-2012,2011,2008��׼
	VSB_SGMW_HONGTU_1 = 24        // ����-��;-2010,2009,2008,2007
}VSB_SGMW_CLASS;

//������Ʒ������
typedef enum _VSB_CHANA_CLASS
{
	VSB_CHANA_OTHER = 0,   // ������������
	VSB_CHANA_HONOR = 1,   // ŷŵ
	VSB_CHANA_XINGKA = 2,   // �����ǿ�
	VSB_CHANA_ZHIXING = 3,   // ����֮��
	VSB_CHANA_PICKUP = 4,   // ��������С��(����Ƥ��)
	VSB_CHANA_ZHIXING2 = 5,   // ����֮��2��
	VSB_CHANA_TAURUS = 6,   // ��ţ��
	VSB_CHANA_XINGGUANG = 7,   // �����ǹ�
	VSB_CHANA_BENNI = 8,   // ����
	VSB_CHANA_ALSVIN = 9,   // ����
	VSB_CHANA_CX20 = 10,  // ����CX20
	VSB_CHANA_CX30 = 11,  // ����CX30
	VSB_CHANA_EADO = 12,  // �ݶ�
	VSB_CHANA_ZHIXINGS460 = 13,  // ����֮��S460
	VSB_CHANA_CM8 = 14,  // ����CM8
	VSB_CHANA_XINBAO = 15,  // �±�
	VSB_CHANA_XUNLONG = 16,  // ѫ��
	VSB_CHANA_YUNTONG = 17,  // ��ͨ
	VSB_CHANA_LEIMENG = 18,  // ����
	VSB_CHANA_XINGYUN = 19,  // ��������
	VSB_CHANA_OULIWEI = 20,  // ŷ����
	VSB_CHANA_EADOXT = 21,   // ����XT
	VSB_CHANA_XINGYUN_1 = 22,      // ��������-����-2004,2003,2000
	VSB_CHANA_OULIWEI_1 = 23,      // ��������-ŷ����-2013
	VSB_CHANA_YUNTONG_1 = 24,      // ��������-��ͨ-2004
	VSB_CHANA_TAURUS_1 = 25,      // ��������-��ţ��-2013,2012,2011,2010
	VSB_CHANA_LEIMENG_1 = 26,      // ��������-����-2005,2003
	VSB_CHANA_ZHIXING_1 = 27,      // ��������-����֮��-2010,2009
	VSB_CHANA_ZHIXING_2 = 28,      // ��������-����֮��-2013
	VSB_CHANA_ZHIXING_3 = 29,      // ��������-����֮��2-2009,2008
	VSB_CHANA_ZHIXING_4 = 30,      // ��������-����֮��2-2012
	VSB_CHANA_ZHIXING_5 = 31,      // ��������-����֮��S460-2010,2009
	VSB_CHANA_ZHIXING_6 = 32,      // ��������-����֮��SC6350-2003
	VSB_CHANA_PICKUP_1 = 33,      // ��������-����΢������-2013,2012
	VSB_CHANA_XINGGUANG_1 = 34,      // ��������-�����ǹ�4500-2009,2007
	VSB_CHANA_XINGGUANG_2 = 35,      // ��������-�����ǹ�4500-2012
	VSB_CHANA_HONOR_1 = 36      // ��������-����ŷŵ-2014,2012
}VSB_CHANA_CLASS;

//�����γ���Ʒ������
typedef enum _VSB_EADO_CLASS
{
	VSB_EADO_OTHER = 0,       // ������������
	VSB_EADO_CS_1 = 1,       // �����γ�-CS35-2014,2013,2012
	VSB_EADO_CX_1 = 2,       // �����γ�-CX20-2011
	VSB_EADO_CX_2 = 3,       // �����γ�-CX30����-2010
	VSB_EADO_BENBEN_1 = 4,       // �����γ�-����-2008,2007,2006
	VSB_EADO_BENBEN_2 = 5,       // �����γ�-����-2008������,2007�˶���
	VSB_EADO_BENBEN_3 = 6,       // �����γ�-����-2010
	VSB_EADO_BENBEN_4 = 7,       // �����γ�-����MINI-2011,2010
	VSB_EADO_BENBEN_5 = 8,       // �����γ�-����MINI-2012
	VSB_EADO_YUEXIANG_1 = 9,       // �����γ�-����-2011,2010,2009
	VSB_EADO_YUEXIANG_2 = 10,       // �����γ�-����-2012
	VSB_EADO_YUEXIANG_3 = 11,       // �����γ�-����V3-2013,2012
	VSB_EADO_YUEXIANG_4 = 12,       // �����γ�-����V5-2012
	VSB_EADO_YIDONG_1 = 13        // �����γ�-�ݶ�-2014,2013,2012
}VSB_EADO_CLASS;

//����Ʒ������
typedef enum _VSB_JINBEI_CLASS
{
	VSB_JINBEI_OTHER = 0,   // ������������
	VSB_JINBEI_GRACE = 1,   // �𱭸���˹
	VSB_JINBEI_HIACE = 2,   // �𱭺�ʨ
	VSB_JINBEI_HAIXING = 3,   // ����
	VSB_JINBEI_BADAO = 4,   // �𱭰Ե�
	VSB_JINBEI_LINGQI = 5,   // ����
	VSB_JINBEI_JINQI = 6,   // ����
	VSB_JINBEI_LINGCHI = 7,   // ���
	VSB_JINBEI_QIYUN = 8,   // ����
	VSB_JINBEI_ZHISHANG_1 = 9,       // ��-����S30-2014,2013,2012
	VSB_JINBEI_HAIXING_1 = 10,       // ��-����-2012
	VSB_JINBEI_HAIXING_2 = 11,       // ��-����-2012A7�ػ���,2011
	VSB_JINBEI_HIACE_1 = 12,       // ��-��ʨ-2008
	VSB_JINBEI_HIACE_2 = 13,       // ��-��ʨ-2013,2011,2010
	VSB_JINBEI_HIACE_3 = 14,       // ��-��ʨ-2013������,2011����,2008��׼��
	VSB_JINBEI_JINDIAN_1 = 15,       // ��-���-2009
	VSB_JINBEI_GRACE_1 = 16,       // ��-����˹MPV-2011,2008,2007
	VSB_JINBEI_GRACE_2 = 17,       // ��-����˹MPV-2011���������,2010,2009,2007��׼9��
	VSB_JINBEI_BADAO_1 = 18       // ��-�Ե�SUV-2011,2008 

}VSB_JINBEI_CLASS;

//������Ʒ������
typedef enum _VSB_GEELY_CLASS
{
	VSB_GEELY_OTHER = 0,   // ������������
	VSB_GEELY_EC7 = 1,   // �����ۺ�EC7
	VSB_GEELY_EC8 = 2,   // �����ۺ�EC8                                                          
	VSB_GEELY_SC3 = 3,   // ����SC3
	VSB_GEELY_SC5RV = 4,   // ����SC5-RV
	VSB_GEELY_SC6 = 5,   // ����SC6
	VSB_GEELY_JINGYING = 6,   // ��ӥ
	VSB_GEELY_JINGGANG = 7,   // ���
	VSB_GEELY_SX7 = 8,   // ����SX7
	VSB_GEELY_HAOQING = 9,   // ����
	VSB_GEELY_MEIRI = 10,  // ����
	VSB_GEELY_YINGLUNSC7 = 11,  // Ӣ��SC7
	VSB_GEELY_PANDA = 12,  // ��è
	VSB_GEELY_YUANJING = 13,  // Զ��
	VSB_GEELY_ZIYOUJIAN = 14   // ���ɽ�
}VSB_GEELY_CLASS;

//������Ʒ������
typedef enum _VSB_MITSUBISHI_CLASS
{
	VSB_MITSUBISHI_OTHER = 0,   // ������������
	VSB_MITSUBISHI_GALANT = 1,   // ����
	VSB_MITSUBISHI_ZINGER = 2,   // ����
	VSB_MITSUBISHI_LANCER = 3,   // ��ɪ
	VSB_MITSUBISHI_LANCEREX = 4,   // ����
	VSB_MITSUBISHI_PAJERO = 5,   // ������
	VSB_MITSUBISHI_PAJEROSPORT = 6,   // ������-����
	VSB_MITSUBISHI_JINGXUANASX = 7,   // ����ASX
	VSB_MITSUBISHI_GRANDIS = 8,   // ���������
	VSB_MITSUBISHI_OUTLANDER = 9,   // ŷ����
	VSB_MITSUBISHI_QINXINGYUEYE = 10,  // ��������ԽҰ
	VSB_MITSUBISHI_GTO = 11,  // ����GTO
	VSB_MITSUBISHI_SOVERAN = 12,  // ��������
	VSB_MITSUBISHI_LIONVEL = 13,  // ��������
	VSB_MITSUBISHI_HAFEISIMBO = 14,   // ��������
	VSB_MITSUBISHI_LANCEREX_1 = 15,   // ����-��������-2012,2011,2010
	VSB_MITSUBISHI_JINGXUAN_1 = 16,   // ����-����-2012,2011
	VSB_MITSUBISHI_ZINGER_1 = 17,   // ����-����-2011,2009
	VSB_MITSUBISHI_PAJERO_1 = 18,   // ����-������-2004����
	VSB_MITSUBISHI_PAJERO_2 = 19,   // ����-������-2004����
	VSB_MITSUBISHI_PAJERO_3 = 20,   // ����-������-2010����
	VSB_MITSUBISHI_PAJEROSPORT_1 = 21,   // ����-�����޾���-2011
	VSB_MITSUBISHI_GALANT_1 = 22,   // ����-����-2009
	VSB_MITSUBISHI_GALANDI_1 = 23,   // ����-������-2007
	VSB_MITSUBISHI_GALANDI_2 = 24,   // ����-������-2010
	VSB_MITSUBISHI_OUTLANDER_1 = 25,   // ����-ŷ����-2012,2011,2010
	VSB_MITSUBISHI_OUTLANDER_2 = 26,   // ����-ŷ����-2013
	VSB_MITSUBISHI_LINGYUE_1 = 27,   // ����-����-δ֪
	VSB_MITSUBISHI_LANCER_1 = 28   // ����-��ɪ-2010
}VSB_MITSUBISHI_CLASS;

//�׿���˹��Ʒ������
typedef enum _VSB_LEXUS_CLASS
{
	VSB_LEXUS_OTHER = 0,   // ������������
	VSB_LEXUS_ES = 1,   // �׿���˹ES
	VSB_LEXUS_CT = 2,   // �׿���˹CT                                                          
	VSB_LEXUS_RX = 3,   // �׿���˹RX
	VSB_LEXUS_IS = 4,   // �׿���˹IS
	VSB_LEXUS_LX = 5,   // �׿���˹LX
	VSB_LEXUS_GS = 6,   // �׿���˹GS
	VSB_LEXUS_GX = 7,   // �׿���˹GX
	VSB_LEXUS_LS = 8,    // �׿���˹LS
	VSB_LEXUS_CT_1 = 9,   // �׿���˹-CT-2013,2012,2011
	VSB_LEXUS_ES_1 = 10,   // �׿���˹-ES-1994
	VSB_LEXUS_ES_2 = 11,   // �׿���˹-ES-2010,2009,2006
	VSB_LEXUS_ES_3 = 12,   // �׿���˹-ES-2013,2012
	VSB_LEXUS_GS_1 = 13,   // �׿���˹-GS-2011,2010,2009,2008,2005
	VSB_LEXUS_GX_1 = 14,   // �׿���˹-GX-2012,2010
	VSB_LEXUS_IS_1 = 15,   // �׿���˹-IS-2011
	VSB_LEXUS_LS_1 = 16,   // �׿���˹-LS-1994
	VSB_LEXUS_LS_2 = 17,   // �׿���˹-LS-2005,2004
	VSB_LEXUS_LS_3 = 18,   // �׿���˹-LS-2009,2007,2006
	VSB_LEXUS_LX_1 = 19,   // �׿���˹-LX-2013,2012
	VSB_LEXUS_RX_1 = 20,   // �׿���˹-RX-2011,2010,2009
	VSB_LEXUS_RX_2 = 21,   // �׿���˹-RX-2013,2012
	VSB_LEXUS_RX_3 = 22   // �׿���˹-RX-2007
}VSB_LEXUS_CLASS;

//������Ʒ������
typedef enum _VSB_ROEWE_CLASS
{
	VSB_ROEWE_OTHER = 0,   // ������������
	VSB_ROEWE_350 = 1,   // ����350
	VSB_ROEWE_550 = 2,   // ����550                                                          
	VSB_ROEWE_W5 = 3,   // ����W5
	VSB_ROEWE_950 = 4,   // ����950
	VSB_ROEWE_750 = 5,   // ����750
	VSB_ROEWE_350_1 = 6,   // ����-350-2011Ѹ�ǰ�,2010
	VSB_ROEWE_350_2 = 7,   // ����-350-2014,2013,2012,2011
	VSB_ROEWE_550_1 = 8,   // ����-550-2012,2010,2009,2008
	VSB_ROEWE_750_1 = 9,   // ����-750-2009,2008,2007,2006
	VSB_ROEWE_750_2 = 10,  // ����-750-2012,2011
	VSB_ROEWE_950_1 = 11   // ����-950-2012
}VSB_ROEWE_CLASS;


//������Ʒ������
typedef enum _VSB_HAIMA_CLASS
{
	VSB_HAIMA_OTHER = 0,   // ������������
	VSB_HAIMA_PREMARIN = 1,   // ������
	VSB_HAIMA_S7 = 2,   // ����S7
	VSB_HAIMA_PRINCE = 3,   // ��������
	VSB_HAIMA_CUPID = 4,   // ����2-�����
	VSB_HAIMA_HATCHBACK = 5,   // ����3-����
	VSB_HAIMA_KNIGHT = 6,   // ��ʿ
	VSB_HAIMA_HAPPIN = 7,   // ������
	VSB_HAIMA_FAMILY = 8,   // ������
	VSB_HAIMA_M3 = 9,    // ����M3
	VSB_HAIMA_CUPID_1 = 10,   // ����-�����-2012,2011,2010
	VSB_HAIMA_PREMARIN_1 = 11,   // ����-������-2007
	VSB_HAIMA_PREMARIN_2 = 12,   // ����-������-2012,2010
	VSB_HAIMA_HATCHBACK_1 = 13,   // ����-����-2010,2009
	VSB_HAIMA_HAPPIN_1 = 14,   // ����-������-2010,2009,2008,2007,2004
	VSB_HAIMA_HAPPIN_2 = 15,   // ����-������-2012,2011
	VSB_HAIMA_M3_1 = 16,   // ����-����3-2010,2008,2007
	VSB_HAIMA_FAMILY_1 = 17,   // ����-������-2007,2006
	VSB_HAIMA_FAMILY_2 = 18,   // ����-������-2010,2009,2008
	VSB_HAIMA_FAMILY_3 = 19,   // ����-������-2011
	VSB_HAIMA_FAMILY_4 = 20,   // ����-������-2014,2013,2012
	VSB_HAIMA_KNIGHT_1 = 21,   // ����-��ʿ-2013_2012A,2011,2010
	VSB_HAIMA_KNIGHT_2 = 22,   // ����-��ʿ-2013_2012B
	VSB_HAIMA_NEWHONGDA_1 = 23,   // �������ó�-�º��-2009
	VSB_HAIMA_NEWHONDGA_2 = 24,   // �������ó�-�º��-2012
	VSB_HAIMA_PRINCE_1 = 25,   // �������ó�-��������-2010
	VSB_HAIMA_RONGDA_1 = 26   // �������ó�-�ٴ�-2012

}VSB_HAIMA_CLASS;

//������Ʒ������
typedef enum _VSB_GREATWALL_CLASS
{
	VSB_GREATWALL_OTHER = 0,   // ������������
	VSB_GREATWALL_SING = 1,   // ��Ӱ
	VSB_GREATWALL_SAIJUN = 2,   // ����
	VSB_GREATWALL_HAVAL = 3,   // ����
	VSB_GREATWALL_SAFE = 4,   // ����
	VSB_GREATWALL_SAIKU = 5,   // ����
	VSB_GREATWALL_SAILING = 6,   // ����
	VSB_GREATWALL_KINGDEER = 7,   // ��϶�
	VSB_GREATWALL_DEER = 8,   // �϶�
	VSB_GREATWALL_WINGLE = 9,   // �翥
	VSB_GREATWALL_COOLBEAR = 10,  // ����
	VSB_GREATWALL_LINGAO = 11,  // ���
	VSB_GREATWALL_CROSS = 12,  // ����
	VSB_GREATWALL_GWPERI = 13,  // ����
	VSB_GREATWALL_COWRY = 14,  // ����
	VSB_GREATWALL_M4 = 15,   // ����M4
	VSB_GREATWALL_LINGAO_1 = 16,   // ����-���-2010
	VSB_GREATWALL_HAVAL_1 = 17,   // ����-����H3-2010,2009
	VSB_GREATWALL_HAVAL_2 = 18,   // ����-����H3-2012,2010,2009�����
	VSB_GREATWALL_HAVAL_3 = 19,   // ����-����H5-2012,2011,2010
	VSB_GREATWALL_HAVAL_4 = 20,   // ����-����H5-2012,2011,2010�̾�������
	VSB_GREATWALL_HAVAL_5 = 21,   // ����-����H5-2012������
	VSB_GREATWALL_HAVAL_6 = 22,   // ����-����H5-2014,2013
	VSB_GREATWALL_HAVAL_8 = 23,   // ����-����H6-2014,2013������
	VSB_GREATWALL_HAVAL_9 = 24,   // ����-����M2-2010
	VSB_GREATWALL_HAVAL_10 = 25,   // ����-����M2-2013,2012
	VSB_GREATWALL_HAVAL_11 = 26,   // ����-����M4-2012
	VSB_GREATWALL_HAVAL_12 = 27,   // ����-������-2011
	VSB_GREATWALL_CROSS_1 = 28,   // ����-����-2009,2008
	VSB_GREATWALL_CROSS_2 = 29,   // ����-����CROSS-2011,2009
	VSB_GREATWALL_JINGLING_1 = 30,   // ����-����-δ֪
	VSB_GREATWALL_SING_1 = 31,   // ����-��Ӱ-2003
	VSB_GREATWALL_SAIKU_1 = 32,   // ����-����-2004
	VSB_GREATWALL_SAILING_1 = 33,   // ����-����-δ֪
	VSB_GREATWALL_DIER_1 = 34,   // ����-�϶�-δ֪
	VSB_GREATWALL_COOLBEAR_1 = 35,   // ����-����-2010,2009
	VSB_GREATWALL_KINGDEER_1 = 36,   // ����-��϶�-2008,2007,2004,2003
	VSB_GREATWALL_GREATWALL_1 = 37,   // ����-����C20R-2013,2011
	VSB_GREATWALL_GREATWALL_2 = 38,   // ����-����C30-2010
	VSB_GREATWALL_GREATWALL_3 = 39,   // ����-����C30-2012
	VSB_GREATWALL_GREATWALL_4 = 40,   // ����-����C30-2013
	VSB_GREATWALL_GREATWALL_5 = 41,   // ����-����C50-2013,2012
	VSB_GREATWALL_GREATWALL_6 = 42,   // ����-����V80-2013,2012,2010,2009,2008
	VSB_GREATWALL_WINGLE_1 = 43,   // ����-�翥3-2011,2010,2007,2006
	VSB_GREATWALL_WINGLE_2 = 44,   // ����-�翥5-2014,2012,2011,2009 
	VSB_GREATWALL_HAVAL_7 = 45   // ����-����H6-2013,2012,2011
}VSB_GREATWALL_CLASS;

//������Ʒ������
typedef enum _VSB_DS_CLASS
{
	VSB_DS_OTHER = 0,          // ������������
	VSB_DS_KUBO_1 = 1,          // ����-�Ძ-2011,2010,2009,2008
	VSB_DS_KUWEI_1 = 2,          // ����-����-2011,2010,2009
	VSB_DS_KUWEI_2 = 3           // ����-����-2013
}VSB_DS_CLASS;

//·����Ʒ������
typedef enum _VSB_LANDROVER_CLASS
{
	VSB_LANDROVER_OTHER = 0,   // ������������
	VSB_LANDROVER_FAXIAN_1 = 1,   // ·��-����-2005,2004
	VSB_LANDROVER_FAXIAN_2 = 2,   // ·��-����-2013,2011,2010
	VSB_LANDROVER_LANSHENG_1 = 3,   // ·��-��ʤ-2012,2011,2010
	VSB_LANDROVER_LANSHENG_2 = 4,   // ·��-��ʤ����-2014,2013,2012,2011
	VSB_LANDROVER_LANSHENG_3 = 5,   // ·��-��ʤ�˶���-2013,2012,2011,2010
	VSB_LANDROVER_LANSHENG_4 = 6,   // ·��-��ʤ�˶���-2013Ԧ��������
	VSB_LANDROVER_SXZ_1 = 7   // ·��-������2��-2014,2013,2011
}VSB_LANDROVER_CLASS;

//������Ʒ������
typedef enum _VSB_MG_CLASS
{
	VSB_MG_OTHER = 0,  // ������������
	VSB_MG_3SW_1 = 1,  // MG-MG-3SW-2009,2008
	VSB_MG_MG3_1 = 2,  // MG-MG3-2013,2012,2011
	VSB_MG_MG5_1 = 3,  // MG-MG5-2014,2013,2012
	VSB_MG_MG6_1 = 4,  // MG-MG6����-2012,2011
	VSB_MG_MG7_1 = 5,  // MG-MG7-2010,2009,2008,2007
}VSB_MG_CLASS;

//һ����Ʒ������
typedef enum _VSB_FAW_CLASS
{
	VSB_FAW_OTHER = 0,    // ������������
	VSB_FAW_501_1 = 1,    //һ��-501-�Ῠ
	VSB_FAW_N3_1 = 2,    //һ��-N3+����-2006
	VSB_FAW_N3_2 = 3,    //һ��-N3+����-2008
	VSB_FAW_JIABAO_1 = 4,    //һ��-�ѱ�����-2011T50,T57
	VSB_FAW_JIABAO_2 = 5,    //һ��-�ѱ������-2000
	VSB_FAW_JIABAO_3 = 6,    //һ��-�ѱ������-2006
	VSB_FAW_JIABAO_4 = 7,    //һ��-�ѱ������-2012,2011V50���ʰ�
	VSB_FAW_JIABAO_5 = 8,    //һ��-�ѱ������-2012,2011V70
	VSB_FAW_JIABAO_6 = 9,    //һ��-�ѱ������-2013,2012,2011V52ʵ����
	VSB_FAW_JIABAO_7 = 10,    //һ��-�ѱ������-2014,2013V80
	VSB_FAW_XIALI_1 = 11,    //һ��-����-1999,1997
	VSB_FAW_XIALI_2 = 12,    //һ��-����2000-2003,2002
	VSB_FAW_XIALI_3 = 13,    //һ��-����A+-2011,2010,2006,2005
	VSB_FAW_XIALI_4 = 14,    //һ��-����N3-2012
	VSB_FAW_XIALI_5 = 15,    //һ��-����N5-2014,2013,2011,2010,2009
	VSB_FAW_XIALI_6 = 16,    //һ��-����N7-2013
	VSB_FAW_AOWEI_1 = 17,    //һ��-����J5P-2005,2004,2003
	VSB_FAW_AOWEI_2 = 18,    //һ��-����J5P-4X2������ǣ����,��ж��
	VSB_FAW_AOWEI_3 = 19,    //һ��-����J5P-4X2ǣ����,ж����
	VSB_FAW_AOWEI_4 = 20,    //һ��-����J5P-6X6ԽҰ��ж��
	VSB_FAW_AOXING_1 = 21,    //һ��-����-2004
	VSB_FAW_WEILE_1 = 22,    //һ��-����-2004
	VSB_FAW_WEILE_2 = 23,    //һ��-����-2008,2007
	VSB_FAW_WEIZI_1 = 24,    //һ��-����-2004
	VSB_FAW_WEIZHI_1 = 25,    //һ��-��־V2-2012�ֶ�CROSS
	VSB_FAW_WEIZHI_2 = 26,    //һ��-��־V2-2012�Զ�CROSS,2010
	VSB_FAW_WEIZHI_3 = 27,    //һ��-��־V5-2013,2012
	VSB_FAW_WEIZHI_4 = 28,    //һ��-��־����-2009,2008,2007
	VSB_FAW_WEIZHI_5 = 29,    //һ��-��־����-2011
	VSB_FAW_XIAOJIEFANG_1 = 30,    //һ��-С���-90,109�����Ῠ
	VSB_FAW_HANWEI_1 = 31,    //һ��-����J5M-4X4�ػ���
	VSB_FAW_HANWEI_2 = 32,    //һ��-����J5M-6X6ǣ����,6X4��ж��
	VSB_FAW_HANWEI_3 = 33,    //һ��-����J5M-8X8��ж��
	VSB_FAW_XINDAWEI_1 = 34,    //һ��-�´���-2010
	VSB_FAW_XINHANWEI_1 = 35,    //һ��-�º���-2011
	VSB_FAW_SENYA_1 = 36,    //һ��-ɭ��M80-2012,2011,2009
	VSB_FAW_TENGWEI_1 = 37,    //һ��-����L5M-�ؿ�
	VSB_FAW_JIEFANG_1 = 38,    //һ��-���J4R-A��
	VSB_FAW_JIEFANG_2 = 39,    //һ��-���J4R-��ж��,ǣ����
	VSB_FAW_JIEFANG_3 = 40,    //һ��-���J6-2004
	VSB_FAW_JIEFANG_4 = 41,    //һ��-���J6-�ؿ�
	VSB_FAW_JIEFANG_5 = 42,    //һ��-���J6L-�п�
	VSB_FAW_JIEFANG_6 = 43,    //һ��-���L5-A��
	VSB_FAW_SAILONG_1 = 44,    //һ��-����-�п�
	VSB_FAW_JUNWEI_1 = 45,    //һ��-����J5K-�п�
	VSB_FAW_B50_1 = 46,    //һ��-����B50-2012,2011,2009
	VSB_FAW_B50_2 = 47    //һ��-����B50-2013
}VSB_FAW_CLASS;


//������Ʒ������
typedef enum _VSB_SAICMOTOR_CLASS
{
	VSB_SAICMOTOR_OTHER = 0,    // ������������
	VSB_HONGYAN_JIESHI_1 = 1,    // ������ά�º���-��ʨ-2012
	VSB_DATONG_V80_1 = 2     // ������ͨ-V80-2014,2013,2012,2011
}VSB_SAICMOTOR_CLASS;

//����������Ʒ������
typedef enum _VSB_SOUEAST_CLASS
{
	VSB_SOUEAST_OTHER = 0,    // ������������
	VSB_SOUEAST_V3_1 = 1,    // ����-V3����-2011��ֵ�Ҹ���,2010,2009,2008
	VSB_SOUEAST_V3_2 = 2,    // ����-V3����-2012
	VSB_SOUEAST_V3_3 = 3,    // ����-V3����-2012�콢��,2011,2010�·�ɰ�
	VSB_SOUEAST_V3_4 = 4,    // ����-V3����-2012��ɰ�
	VSB_SOUEAST_V5_1 = 5,    // ����-V5����-2014,2013,2012
	VSB_SOUEAST_XIWANG_1 = 6,    // ����-ϣ��-2011,2010
	VSB_SOUEAST_DELIKA_1 = 7,    // ����-������-2003,2002
	VSB_SOUEAST_DELIKA_2 = 8,    // ����-������-2005
	VSB_SOUEAST_DELIKA_3 = 9,    // ����-������-2008
	VSB_SOUEAST_DELIKA_4 = 10,    // ����-������-2009
	VSB_SOUEAST_LINGSHUAI_1 = 11,    // ����-��˧-2005,2004GLXi
	VSB_SOUEAST_FULIKA_1 = 12,    // ����-������-2005
	VSB_SOUEAST_FULIKA_2 = 13    // ����-������-2007
}VSB_SOUEAST_CLASS;


//����������Ʒ������
typedef enum _VSB_ZTE_CLASS
{
	VSB_ZTE_OTHER = 0,        // ������������
	VSB_ZTE_WEIHU_1 = 1,        // ����-����-2012,2010
	VSB_ZTE_WEIHU_2 = 2,        // ����-����TUV-2010,2006
	VSB_ZTE_WUXIAN_1 = 3,        // ����-����-2008
	VSB_ZTE_WUXIAN_2 = 4         // ����-����-2012,2011,2010,2009
}VSB_ZTE_CLASS;


//�л�������Ʒ������
typedef enum _VSB_ZHONGHUA_CLASS
{
	VSB_ZHONGHUA_OTHER = 0,    // ������������
	VSB_ZHONGHUA_H230_1 = 1,   // �л�-H230-2012
	VSB_ZHONGHUA_H320_1 = 2,   // �л�-H320-2012
	VSB_ZHONGHUA_H330_1 = 3,   // �л�-H330-2013
	VSB_ZHONGHUA_H530_1 = 4,   // �л�-H530-2012,2011
	VSB_ZHONGHUA_V5_1 = 5,   // �л�-V5-2012,2011
	VSB_ZHONGHUA_ZUNCHI_1 = 6,   // �л�-���-2004
	VSB_ZHONGHUA_ZUNCHI_2 = 7,   // �л�-���-2005,2003
	VSB_ZHONGHUA_KUBAO_1 = 8,   // �л�-�ᱦ-2007
	VSB_ZHONGHUA_JUNJIE_1 = 9,   // �л�-����-2010,2009,2008,2007,2006
	VSB_ZHONGHUA_JUNJIE_2 = 10,   // �л�-����-2012,2011
	VSB_ZHONGHUA_JUNJIECROSS_1 = 11,   // �л�-����cross-2010,2009
	VSB_ZHONGHUA_JUNJIEFRV_1 = 12,   // �л�-����FRV-2009,2008
	VSB_ZHONGHUA_JUNJIEFRV_2 = 13,   // �л�-����FRV-2010
	VSB_ZHONGHUA_JUNJIEFSV_1 = 14,   // �л�-����FSV-2009
	VSB_ZHONGHUA_JUNJIEFSV_2 = 15,   // �л�-����FSV-2010
	VSB_ZHONGHUA_JUNJIEFSV_3 = 16   // �л�-����FSV-2011
}VSB_ZHONGHUA_CLASS;


//�й�������Ʒ������
typedef enum _VSB_CNHTC_CLASS
{
	VSB_CNHTC_OTHER = 0,    // ������������
	VSB_CNHTC_HOKA_2 = 1,      // �й�����-HOKA-ǣ����,��ж��
	VSB_CNHTC_HOWO_1 = 2,      // �й�����-HOWO-A7
	VSB_CNHTC_HOWO_2 = 3,      // �й�����-HOWO-T7H
	VSB_CNHTC_HOWO_3 = 4,      // �й�����-HOWO-�Ῠ
	VSB_CNHTC_HOWO_4 = 5,      // �й�����-HOWO�ؿ�-ǣ����
	VSB_CNHTC_HOWO_5 = 6,      // �й�����-HOWO�ؿ�-��ж��A
	VSB_CNHTC_HOWO_6 = 7,      // �й�����-HOWO�ؿ�-��ж��B
	VSB_CNHTC_HOWO_7 = 8,      // �й�����-HOWO�ؿ�-�ػ���A
	VSB_CNHTC_HOWO_8 = 9,      // �й�����-HOWO�ؿ�-�ػ���C
	VSB_CNHTC_SITAIERWANG_1 = 10,      // �й�����-˹̫����-ǣ����A,�ػ���,���賵
	VSB_CNHTC_HAOHAN_1 = 11,      // �й�����-���-A��
	VSB_CNHTC_HAOYUN_1 = 12,      // �й�����-����-ǣ����B,�ػ���,��ж��
	VSB_CNHTC_JINWANGZI_1 = 13,      // �й�����-�������ؿ�-ǣ����B
	VSB_CNHTC_HOKA_1 = 14      // �й�����-HOKA-H7
}VSB_CNHTC_CLASS;

//��ͨ��Ʒ������
typedef enum _VSB_ZHONGTONG_CLASS
{
	VSB_ZHONGTONG_OTHER = 0,  // ������������
	VSB_ZHONGTONG_KAICHI_1 = 1,  // ��ͨ�ͳ�-����A-A��
	VSB_ZHONGTONG_LINGYU_1 = 2,  // ��ͨ�ͳ�-����-A��
	VSB_ZHONGTONG_LINGXIU_1 = 3,  // ��ͨ�ͳ�-����-A��
	VSB_ZHONGTONG_LINGHANG_1 = 4,  // ��ͨ�ͳ�-�캽-A��
	VSB_ZHONGTONG_SHIJI_1 = 5,  // ��ͨ�ͳ�-����-A��
	VSB_ZHONGTONG_KAIXUAN_1 = 6,  // ��ͨ�ͳ�-����-A��
	VSB_ZHONGTONG_LINGYUN_1 = 7,  // ��ͨ�ͳ�-����A-A��
	VSB_ZHONGTONG_YANGGUANG_1 = 8  // ��ͨ�ͳ�-����-A��
}VSB_ZHONGTONG_CLASS;


//������Ʒ������
typedef enum _VSB_JIULONG_CLASS
{
	VSB_JIULONG_OTHER = 0,    // ������������
	VSB_JIULONG_JIULONGA5_1 = 1,    // ����-����A5-2011
}VSB_JIULONG_CLASS;

//��̩��Ʒ������
typedef enum _VSB_ZOTYE_CLASS
{
	VSB_ZOTYE_OTHER = 0,       // ������������
	VSB_ZOTYE_2008_2 = 1,      // ��̩-2008-2011,2010,2008
	VSB_ZOTYE_5008_1 = 2,      // ��̩-5008-2013,2011,2010,2008
	VSB_ZOTYE_Z300_1 = 3,      // ��̩-Z300-2013,2012
	VSB_ZOTYE_2008_1 = 4      // ��̩-2008-2007
}VSB_ZOTYE_CLASS;

//��ά����Ʒ������
typedef enum _VSB_NAVECO_CLASS
{
	VSB_NAVECO_OTHER = 0,       // ������������
	VSB_NAVECO_Daily_1 = 1,     // ��ά��-Daily-2006,2004,2003
	VSB_NAVECO_Power_1 = 2,     // ��ά��-Power-Daily
	VSB_NAVECO_Turbo_1 = 3,     // ��ά��-Turbo-Daily-2014,2012,2011
	VSB_NAVECO_Venice_1 = 4,     // ��ά��-Venice-2011,2008
	VSB_NAVECO_BAODI_1 = 5,     // ��ά��-����-2012,2009
	VSB_NAVECO_DEYIHUOCHE_1 = 6,     // ��ά��-�������-2011
	VSB_NAVECO_DULING_1 = 7     // ��ά��-����-2010,2009,2007
}VSB_NAVECO_CLASS;

//��ʱ����Ʒ������
typedef enum _VSB_PORSCHE_CLASS
{
	VSB_PORSCHE_OTHER = 0,    // ������������
	VBR_PORSCHE_PANAMERA_1 = 1,    // ��ʱ��-panamera-2013,2012,2010
	VBR_PORSCHE_CAYENNE_1 = 2,    // ��ʱ��-����Cayenne-2014,2013,2011,2010
}VSB_PORSCHE_CLASS;


//����˹����Ʒ������
typedef enum _VSB_CHRYSLER_CLASS
{
	VSB_CHRYSLER_OTHER = 0,    // ������������
	VSB_CHRYSLER_300C_1 = 1,   // ����˹��-300C-2007,2006,2004
	VSB_CHRYSLER_PTMANBUZHE_1 = 2,   // ����˹��-PT������-2007
}VSB_CHRYSLER_CLASS;

//����������Ʒ������
typedef enum _VSB_CADILLAC_CLASS
{
	VSB_CADILLAC_OTHER = 0,    // ������������
	VSB_CADILLAC_ATS_1 = 1,   // ��������-ATS-2014
	VSB_CADILLAC_CTS_1 = 2,   // ��������-CTS-2012
	VSB_CADILLAC_CTS_3 = 3,   // ��������-CTS-2012��Ӣ�˶���,2011,2010,2009,2008
	VSB_CADILLAC_SLS_1 = 4,   // ��������-SLS����-2007,2006
	VSB_CADILLAC_SLS_2 = 5,   // ��������-SLS����-2012,2011,2010
	VSB_CADILLAC_SRX_1 = 6,   // ��������-SRX-2012,2011,2010,2009
	VSB_CADILLAC_CTS_2 = 7,   // ��������-CTS-2012,2009CTS
	VSB_CADILLAC_KAILEIDE_1 = 8   // ��������-���׵�-2011,2010,2008,2007,2006
}VSB_CADILLAC_CLASS;


//����KAMA��Ʒ������
typedef enum _VSB_KAMA_CLASS
{
	VSB_KAMA_OTHER = 0,       // ������������
	VSB_KAMA_QINGKA_2 = 1,       // ����KAMA-����-�ῨD
	VSB_KAMA_FULAIKA_1 = 2,       // ����KAMA-������-�ῨA
	VSB_KAMA_JINYUNKA_1 = 3,       // ����KAMA-���˿�-�Ῠ
	VSB_KAMA_JUNWEIKA_1 = 4,       // ����KAMA-��������-2014,2011
	VSB_KAMA_QINGKA_1 = 5       // ����KAMA-����-�ῨC
}VSB_KAMA_CLASS;

//������Ʒ������
typedef enum _VSB_LIFAN_CLASS
{
	VSB_LIFAN_OTHER = 0,      // ������������
	VSB_LIFAN_320_1 = 1,      // ����-320-2012,2011,2009
	VSB_LIFAN_520_1 = 2,      // ����-520-2007,2006
	VSB_LIFAN_520_2 = 3,      // ����-520-2013,2011,2010,2008
	VSB_LIFAN_620_1 = 4,      // ����-620-2012,2010,2009,2008
	VSB_LIFAN_X60_1 = 5,      // ����-X60-2013,2012,2011
	VSB_LIFAN_FENGSHUN_1 = 6      // ����-��˳-2011
}VSB_LIFAN_CLASS;


//������Ʒ������
typedef enum _VSB_BEIJING_CLASS
{
	VSB_BEIJING_OTHER = 0,      // ������������
	VSB_BEIJING_E_1 = 1,    // ��������-Eϵ������-2014,2013,2012
}VSB_BEIJING_CLASS;

//����������Ʒ������
typedef enum _VSB_BEIBEN_CLASS
{
	VSB_BEIBEN_OTHER = 0,      // ������������
	VSB_BEIBEN_NG80_1 = 1,     // ��������-NG80-�ؿ�A
	VSB_BEIBEN_NG80_2 = 2,     // ��������-NG80-�ؿ�B
	VSB_BEIBEN_NG80_3 = 3,     // ��������-NG80-�ؿ�C
	VSB_BEIBEN_V3_1 = 4,     // ��������-����V3-V3H1
	VSB_BEIBEN_V3_2 = 5     // ��������-����V3-�ؿ�A
}VSB_BEIBEN_CLASS;

//�����ͳ���Ʒ������
typedef enum _VSB_BEIFANG_CLASS
{
	VSB_BEIFANG_OTHER = 0,      // ������������
	VSB_BEIFANG_A_1 = 1       // �����ͳ�-�ͳ�����1-A��
}VSB_BEIFANG_CLASS;


//����������Ʒ������
typedef enum _VSB_BAW_CLASS
{
	VSB_BAW_OTHER = 0,        // ������������
	VSB_BAW_YUSHENG007_1 = 1,        // ��������-��ʤ007-2013,2011
	VSB_BAW_QILING_1 = 2,        // ��������-����-A��
	VSB_BAW_LUBA_1 = 3,        // ��������-½��-2004
	VSB_BAW_QISHI_1 = 4         // ��������-��ʿ-2009,2007
}VSB_BAW_CLASS;

//����������Ʒ������
typedef enum _VSB_BQWEIWANG_CLASS
{
	VSB_BQWEIWANG_OTHER = 0,  // ������������
	VSB_BQWEIWANG_205_1 = 1,  // ��������-205-2013
	VSB_BQWEIWANG_306_1 = 2   // ��������-306-2014,2013,2011
}VSB_BQWEIWANG_CLASS;


//������Ʒ������
typedef enum _VSB_SMA_CLASS
{
	VSB_SMA_OTHER = 0,        // ������������
	VSB_SMA_HAIYU_1 = 1,        // ����-����-2007,2005,2004
	VSB_SMA_HAIYU_2 = 2,        // ����-����-2007����MB
	VSB_SMA_HAISHANG_1 = 3,        // ����-����-2008,2005
	VSB_SMA_HAIJING_1 = 5,        // ����-����-2010,2009
	VSB_SMA_HAIXUN_1 = 4,        // ����-��Ѹ-2005,2004쭷�
	VSB_SMA_HAIXUN_2 = 6,        // ����-��Ѹ-2007,2006
}VSB_SMA_CLASS;

//����������Ʒ������
typedef enum _VSB_XINGMA_CLASS
{
	VSB_XINGMA_OTHER = 0,        // ������������
	VSB_XINGMA_XINGKAIMA_1 = 1         // ��������-�ǿ���-ǣ������1,�ػ�����1
}VSB_XINGMA_CLASS;

//˫����Ʒ������
typedef enum _VSB_SHUANGHUAN_CLASS
{
	VSB_SHUANGHUAN_OTHER = 0,        // ������������
	VSB_SHUANGHUAN_SCEO_1 = 1,        // ˫��-SCEO-2011,2009,2006,2005
}VSB_SHUANGHUAN_CLASS;

//������Ʒ������
typedef enum _VSB_JEEP_CLASS
{
	VSB_JEEP_OTHER = 0,       // ������������
	VSB_JEEP_DAQIENUOJI_1 = 1,       // ����-����ŵ��(����)-2014,2013,2012,2011
	VSB_JEEP_DAQIENUOJI_2 = 2,       // ����-����ŵ��(����)-2014��������
	VSB_JEEP_ZHINANZHE_1 = 3,       // ����-ָ����-2010,2007
	VSB_JEEP_ZHINANZHE_2 = 4,       // ����-ָ����-2014,2013,2012,2011
	VSB_JEEP_MUMAREN_1 = 5,       // ����-������-2012ʹ���ٻ�������,2011
	VSB_JEEP_MUMAREN_2 = 6,       // ����-������-2014,2013,2012,2011,2010,2009,2008
	VSB_JEEP_ZIYOUKE = 7,       // ����-���ɿ�-2014,2013,2012,2011
}VSB_JEEP_CLASS;

//������Ʒ������
typedef enum _VSB_VENUCIA_CLASS
{
	VSB_VENUCIA_OTHER = 0,       // ������������
	VSB_VENUCIA_D50_1 = 1        // ����-D50-2014,2013,2012
}VSB_VENUCIA_CLASS;

//������Ʒ������
typedef enum _VSB_HAFEI_CLASS
{
	VSB_HAFEI_OTHER = 0,      // ������������
	VSB_HAFEI_XINMINYI_1 = 1,      // ����-���������-2010
	VSB_HAFEI_XINMINYI_2 = 2,      // ����-�����������-2012
	VSB_HAFEI_MINYI_1 = 3,      // ����-�������-2006
	VSB_HAFEI_MINYI_2 = 4,      // ����-���������-2008
	VSB_HAFEI_SAIBAO_1 = 5,      // ����-������-2012
	VSB_HAFEI_SAIMA_1 = 6,      // ����-����-2002
	VSB_HAFEI_SAIMA_2 = 7,      // ����-����-2004,2003
	VSB_HAFEI_SAIMA_3 = 8,      // ����-����-2009
	VSB_HAFEI_LUBAO_1 = 9,      // ����-·��-2004
	VSB_HAFEI_LUBAO_2 = 10,      // ����-·��-2008,2007
	VSB_HAFEI_LUBAO_3 = 11,      // ����-·��-2012
	VSB_HAFEI_LUZUNXIAOBAWANG_1 = 12,      // ����-·��С����-2011,2010
	VSB_HAFEI_RUIYI_1 = 13,      // ����-����-2009
	VSB_HAFEI_JUNYI_1 = 14       // ����-����-2012,2010
}VSB_HAFEI_CLASS;

//�ƿ�ŷ����Ʒ������
typedef enum _VSB_TKING_CLASS
{
	VSB_TKING_OTHER = 0,      // ������������
	VSB_TKING_OUGUAN_1 = 1,      // �ƿ�ŷ��-ŷ��-2011
	VSB_TKING_OUGUAN_2 = 2,      // �ƿ�ŷ��-ŷ��-�ῨB
	VSB_TKING_OUTENG_1 = 3,      // �ƿ�ŷ��-ŷ��-�ῨA
	VSB_TKING_FUXING_1 = 4,      // �ƿ�ŷ��-����-2006
	VSB_TKING_QINGKAWANG_1 = 5,      // �ƿ�ŷ��-�Ῠ��-�Ῠ
	VSB_TKING_AFANDA_1 = 6,      // �ƿ�ŷ��-������-���ؿ�
	VSB_TKING_JUNQI_1 = 7       // �ƿ�ŷ��-����-���ؿ�A
}VSB_TKING_CLASS;

//������Ʒ������
typedef enum _VSB_DAEWOO_CLASS
{
	VSB_DAEWOO_OTHER = 0,    // ������������
	VBR_DAEWOO_6960H3_1 = 1     // ����-6960H3-A��
}VSB_DAEWOO_CLASS;

//����������Ʒ������
typedef enum _VSB_DAYUN_CLASS
{
	VSB_DAYUN_OTHER = 0,     // ������������
	VBR_DAYUN_ZHONGKA_1 = 1      // ��������-�ؿ�-A��
}VSB_DAYUN_CLASS;

//������Ʒ������
typedef enum _VSB_BESTURN_CLASS
{
	VSB_BESTURN_OTHER = 0,   // ������������
	VSB_BESTURN_B70_1 = 1,    // ����-B70-2009,2007,2006
	VSB_BESTURN_B70_2 = 2,    // ����-B70-2011
	VSB_BESTURN_B70_3 = 3,    // ����-B70-2011��Ӣ��,2010
	VSB_BESTURN_B70_4 = 4,    // ����-B70-2012
	VSB_BESTURN_B90_1 = 5,    // ����-B90-2012
	VSB_BESTURN_AOXING_1 = 6       // һ��-����-2004
}VSB_BESTURN_CLASS;

//������Ʒ������
typedef enum _VSB_WEILIN_CLASS
{
	VSB_WEILIN_OTHER = 0,      // ������������
	VSB_WEILIN_H3_1 = 1,     // ����-H3-2011
	VSB_WEILIN_V5_1 = 2,     // ����-V5-2012,2009
	VSB_WEILIN_X5_1 = 3      // ����-X5-2012,2011,2010
}VSB_WEILIN_CLASS;

//��ͨ��Ʒ������
typedef enum _VSB_YUTONG_CLASS
{
	VSB_YUTONG_OTHER = 0,     // ������������
	VSB_YUTONG_8XI_1 = 1,     // ��ͨ-8ϵ-2012,2005
	VSB_YUTONG_KECHE_1 = 2,     // ��ͨ-�ͳ�����10-2013,2010
	VSB_YUTONG_KECHE_3 = 3,     // ��ͨ-�ͳ�����2-A��
	VSB_YUTONG_KECHE_4 = 4,     // ��ͨ-�ͳ�����8-2004
	VSB_YUTONG_KECHE_5 = 5,     // ��ͨ-�ͳ�����9-2014
	VSB_YUTONG_KECHE_2 = 6      // ��ͨ-�ͳ�����12-A��
}VSB_YUTONG_CLASS;

//������Ʒ������
typedef enum _VSB_ANKAI_CLASS
{
	VSB_ANKAI_OTHER = 0,      // ������������
	VSB_ANKAI_KECHE_1 = 1,      // ����-�ͳ�����1-A��
	VSB_ANKAI_KECHE_2 = 2       // ����-�ͳ�����3-A��
}VSB_ANKAI_CLASS;

//������Ʒ������
typedef enum _VSB_BAOJUN_CLASS
{
	VSB_BAOJUN_OTHER = 0,   // ������������
	VSB_BAOJUN_630_1 = 1      // ����-����630-2014,2013,2012,2011
}VSB_BAOJUN_CLASS;

//������Ʒ������
typedef enum _VSB_BINLI_CLASS
{
	VSB_BINLI_OTHER = 0,     // ������������
	VSB_BINLI_OULU_1 = 1      // ����-ŷ½-2009,2008
}VSB_BINLI_CLASS;

//����������Ʒ������
typedef enum _VSB_TRUMPCHE_CLASS
{
	VSB_TRUMPCHE_OTHER = 0,   // ������������
	VSB_TRUMPCHE_GA5_1 = 1,   // ��������-GA5-2012,2011
	VSB_TRUMPCHE_GA5_2 = 3,   // ��������-GA5-2013,2012�Զ���Ӣ��
	VSB_TRUMPCHE_GS5_1 = 2    // ��������-GS5-2014,2013,2012
}VSB_TRUMPCHE_CLASS;

//�������� ��Ʒ������
typedef enum _VSB_GONOW_CLASS
{
	VSB_GONOW_OTHER = 0,   // ������������
	VSB_GONOW_G3_1 = 1,      // ��������-G3-2011
	VSB_GONOW_G5_1 = 2,      // ��������-G5-2012,2011
	VSB_GONOW_SHUAIJIAN_1 = 4,      // ��������-˧��-2012,2009
	VSB_GONOW_XINGWANGM1_1 = 3,      // ��������-����M1-2012
	VSB_GONOW_CAIYUN500_1 = 5      // ��������-����500-2010
}VSB_GONOW_CLASS;

//������Ʒ������
typedef enum _VSB_ISUZU_CLASS
{
	VSB_ISUZU_OTHER = 0,   // ������������
	VSB_ISUZU_ZHONGXINGSHANGYONG_1 = 1,      // ����-�������ó�-2011
	VSB_ISUZU_WUSHILINGPIKA_1 = 2,      // ����-��ʮ��Ƥ��-2009
	VSB_ISUZU_WUSHILINGPIKA_2 = 3,      // ����-��ʮ��Ƥ��-2014,2009
	VSB_ISUZU_JINGJIZHE_1 = 4      // ����-������-2004,2002
}VSB_ISUZU_CLASS;


//������Ʒ������
typedef enum _VSB_KARRY_CLASS
{
	VSB_KARRY_OTHER = 0,   // ������������
	VSB_KARRY_YOU_2 = 1,      // ����-����-2013,2012
	VSB_KARRY_YOUJIN_1 = 2,      // ����-�ž�-2012,2011������,2010
	VSB_KARRY_YOUSHENG_1 = 3,      // ����-��ʤ-2010
	VSB_KARRY_YOUSHENG_2 = 4,      // ����-��ʤ-2012,2011
	VSB_KARRY_YOUYA = 5,      // ����-����-2012,2011,2007
	VSB_KARRY_YOU_1 = 6      // ����-����-2011,2010,2009
}VSB_KARRY_CLASS;

//�ݱ���Ʒ������
typedef enum _VSB_GAGUAR_CLASS
{
	VSB_GAGUAR_OTHER = 0,   // ������������
	VSB_GAGUAR_XF_1 = 1,     // �ݱ�-XF-2014,2013
	VSB_GAGUAR_XJ_1 = 2     // �ݱ�-XJ-2014,2013,2012,2011,2010
}VSB_GAGUAR_CLASS;

//˹��³��Ʒ������
typedef enum _VSB_SUBARU_CLASS
{
	VSB_SUBARU_OTHER = 0,   // ������������
	VSB_SUBARU_AOHU_1 = 1,     // ˹��³-����-2012,2011,2010
	VSB_SUBARU_LISHI_1 = 2,     // ˹��³-��ʨ�γ�-2008,2006
	VSB_SUBARU_LISHI_2 = 3,     // ˹��³-��ʨ�γ�-2011,2010
	VSB_SUBARU_XV_1 = 4,     // ˹��³-˹��³XV-2014,2012
	VSB_SUBARU_SENLINREN_1 = 5,     // ˹��³-ɭ����-2007,2006
	VSB_SUBARU_SENLINREN_2 = 6     // ˹��³-ɭ����-2012,2011,2010,2009,2008
}VSB_SUBARU_CLASS;

//ʱ��������Ʒ������
typedef enum _VSB_ERA_CLASS
{
	VSB_ERA_OTHER = 0,   // ������������
	VSB_ERA_XIAOKA_1 = 1,        // ʱ������-С��֮��-С��֮��1,2,Q2
	VSB_ERA_XIAOKA_3 = 2,        // ʱ������-С��֮��-С��֮��5
	VSB_ERA_XIAOKA_4 = 3,        // ʱ������-С��֮��-����
	VSB_ERA_KANGRUI_1 = 4,        // ʱ������-����-����H1
	VSB_ERA_KANGRUI_2 = 5,        // ʱ������-����-����H3
	VSB_ERA_KANGRUI_3 = 6,        // ʱ������-����-����K1,KQ1
	VSB_ERA_RUIWO_1 = 7,        // ʱ������-����-RC1
	VSB_ERA_RUIWO_2 = 8,        // ʱ������-����-RC2
	VSB_ERA_RUIWO_3 = 9,        // ʱ������-����-����II�ῨA
	VSB_ERA_JINGANG = 10,        // ʱ������-���-���568
	VSB_ERA_LINGHANG_1 = 11,        // ʱ������-�캽-�캽2
	VSB_ERA_LINGHANG_2 = 12,        // ʱ������-�캽-�캽3
	VSB_ERA_YULING_1 = 13,        // ʱ������-Ԧ��-Ԧ��V1
	VSB_ERA_YULING_2 = 14,        // ʱ������-Ԧ��-Ԧ��V5,VQ5
	VSB_ERA_YULING_3 = 15,        // ʱ������-Ԧ��-Ԧ��VQ1,VQ2
	VSB_ERA_YULING_4 = 17,        // ʱ������-Ԧ��-����
	VSB_ERA_XIAOKA_2 = 17,        // ʱ������-С��֮��-С��֮��3
}VSB_ERA_CLASS;

//������Ʒ������
typedef enum _VSB_CHANGHE_CLASS
{
	VSB_CHANGHE_OTHER = 0,  // ������������
	VSB_CHANGHE_CH6321_1 = 1,  // ����-CH6321-2000
	VSB_CHANGHE_DANSHUANGPAI_1 = 2,  // ����-�����µ�˫��-1999
	VSB_CHANGHE_AIDIER_1 = 3,  // ����-���϶�-2004
	VSB_CHANGHE_AIDIER_2 = 4,  // ����-���϶���-2007,2006
	VSB_CHANGHE_FURUIDA_1 = 5   // ����-����������-2014,2013,2011,2009
}VSB_CHANGHE_CLASS;

//ŷ����Ʒ������
typedef enum _VSB_OPEL_CLASS
{
	VSB_OPEL_OTHER = 0,    // ������������
	VSB_OPEL_YATE_1 = 1     // ŷ��-����-2010GTCȫ���絲��,2007,2006
}VSB_OPEL_CLASS;

//��Դ��Ʒ������
typedef enum _VSB_JONWAY_CLASS
{
	VSB_JONWAY_OTHER = 0,   // ������������
	VSB_JONWAY_A380_1 = 1    // ��Դ-A380-2010,2009,2008
}VSB_JONWAY_CLASS;

//������Ʒ������
typedef enum _VSB_JIANGNAN_CLASS
{
	VSB_JIANGNAN_OTHER = 0,   // ������������
	VSB_JIANGNAN_TT_1 = 1    // ����-����TT-2011,2010,2004
}VSB_JIANGNAN_CLASS;

//����ȫ��ӥ��Ʒ������
typedef enum _VSB_GLEAGLE_CLASS
{
	VSB_GLEAGLE_OTHER = 0,   // ������������
	VSB_GLEAGLE_EAGLE_GC7_1 = 1,   // ����ȫ��ӥ-GC7-2013,2012
	VSB_GLEAGLE_EAGLE_GX2_1 = 2,   // ����ȫ��ӥ-GX2-2012,2011
	VSB_GLEAGLE_EAGLE_GX7_1 = 3,   // ����ȫ��ӥ-GX7-2013,2012
	VSB_GLEAGLE_EAGLE_PANDA_1 = 4,   // ����ȫ��ӥ-��è-2013,2011,2010,2009
	VSB_GLEAGLE_EAGLE_ZIYOUJIAN_1 = 5,   // ����ȫ��ӥ-���ɽ�-2009���±�׼��,2007
	VSB_GLEAGLE_EAGLE_ZIYOUJIAN_2 = 6,   // ����ȫ��ӥ-���ɽ�-2010,2009,2008,2006,2005
	VSB_GLEAGLE_EAGLE_ZIYOUJIAN_3 = 7,   // ����ȫ��ӥ-���ɽ�-2012,2011
	VSB_GLEAGLE_EAGLE_YUANJING_1 = 8,   // ����ȫ��ӥ-Զ��-2011,2010,2009,2008,2006
	VSB_GLEAGLE_EAGLE_YUANJING_2 = 9,   // ����ȫ��ӥ-Զ��-2013,2012
}VSB_GLEAGLE_CLASS;

//�����ۺ���Ʒ������
typedef enum _VSB_EMGRAND_CLASS
{
	VSB_EMGRAND_OTHER = 0,   // ������������
	VSB_EMGRAND_EC7_2 = 1,   // �����ۺ�-EC7-2013
	VSB_EMGRAND_EC7_3 = 2,   // �����ۺ�-EC7-RV
	VSB_EMGRAND_EC8_1 = 3,   // �����ۺ�-EC8-2013,2011,2010
	VSB_EMGRAND_EC7_1 = 4    // �����ۺ�-EC7-2012,2010,2009
}VSB_EMGRAND_CLASS;


//����Ӣ����Ʒ������
typedef enum _VSB_ENGLON_CLASS
{
	VSB_ENGLON_OTHER = 0,    // ������������
	VSB_ENGLON_SC3_1 = 1,    // ����Ӣ��-SC3-2012
	VSB_ENGLON_SC5_1 = 2,    // ����Ӣ��-SC5-RV-2012
	VSB_ENGLON_SC6_1 = 3,    // ����Ӣ��-SC6-2012
	VSB_ENGLON_SC7_1 = 4,    // ����Ӣ��-SC7-2013,2012,2011,2010
	VSB_ENGLON_SX7_1 = 5,    // ����Ӣ��-SX7-2014,2013
	VSB_ENGLON_JINGANG_1 = 6,    // ����Ӣ��-���-2010,2007,2006
	VSB_ENGLON_JINYING_1 = 7     // ����Ӣ��-��ӥ-2011,2010,2008
}VSB_ENGLON_CLASS;


//����-��Ʒ������
typedef enum _VSB_JAC_CLASS
{
	VSB_JAC_OTHER = 0,      // ������������
	VSB_JAC_TONGYUE_1 = 1,      // ����-ͬ��-2012,2010,2008
	VSB_JAC_HEYUE_1 = 2,      // ����-����-2012,2011,2010
	VSB_JAC_HEYUEA30_2 = 3,      // ����-����A30-2013
	VSB_JAC_HEYUERS_3 = 4,      // ����-����RS-2012,2011
	VSB_JAC_HAOYUN_1 = 5,      // ����-����-�Ῠ1
	VSB_JAC_WEILING_2 = 6,      // ����-����-�Ű��Ῠ
	VSB_JAC_WEILING_3 = 7,      // ����-����-�����ػ���
	VSB_JAC_WEILING_4 = 8,      // ����-����-�Ῠ
	VSB_JAC_KECHE_1 = 9,      // ����-�ͳ�-A��
	VSB_JAC_BINYUE_1 = 10,      // ����-����-2010,2008
	VSB_JAC_SHUAILING_2 = 11,      // ����-˧��-�Ῠ
	VSB_JAC_KANGLING_1 = 12,      // ����-����-�Ῠ1
	VSB_JAC_KANGLING_2 = 13,      // ����-����-�Ῠ2
	VSB_JAC_YUEYUE_1 = 14,      // ����-����-2013,2012,2011,2010
	VSB_JAC_XINGRUI_1 = 15,      // ����-����-2012,2011
	VSB_JAC_GEERFA_H_1 = 16,      // ����-�����H-�����ػ���
	VSB_JAC_GEERFA_K_2 = 17,      // ����-�����K-�ؿ�1
	VSB_JAC_GEERFA_K_3 = 18,      // ����-�����K-�ؿ�2
	VSB_JAC_GEERFA_M_4 = 19,      // ����-�����M-�����ػ���
	VSB_JAC_RUIFENG_1 = 20,      // ����-���-2011,2009,2007�ֶ�
	VSB_JAC_RUIFENG_2 = 21,      // ����-���-2013,2012,2011,2010,2007,2005
	VSB_JAC_RUIFENG_3 = 22,      // ����-���M5-2012,2011
	VSB_JAC_RUIFENG_4 = 23,      // ����-���S5-2013
	VSB_JAC_RUIYING_1 = 24,      // ����-��ӥ-2009,2007
	VSB_JAC_RUIYING_2 = 25,      // ����-��ӥ-2013,2012,2011
	VSB_JAC_JUNLING_2 = 26,      // ����-����-խ���,�����
	VSB_JAC_WEILING_1 = 27,      // ����-����-��ʽ�Ῠ
	VSB_JAC_SHUAILING_1 = 28,      // ����-˧��-��ʮ��
	VSB_JAC_RUILING_1 = 29,      // ����-����-2012
	VSB_JAC_JUNLING_1 = 30      // ����-����-�콢��
}VSB_JAC_CLASS;


//������Ʒ������
typedef enum _VSB_JMC_CLASS
{
	VSB_JMC_OTHER = 0,      // ������������
	VSB_JMC_KAIYUN_1 = 1,      // ����-����-102,109�����Ῠ
	VSB_JMC_KAIYUN_2 = 2,      // ����-����-95�����Ῠ
	VSB_JMC_YUHU_1 = 3,      // ����-��-2012
	VSB_JMC_BAODIAN_1 = 4,      // ����-����-2007
	VSB_JMC_BAODIAN_2 = 5,      // ����-����-2009��׼��,2008
	VSB_JMC_BAODIAN_3 = 6,      // ����-����-2014,2012,2009������
	VSB_JMC_BAOWEI_1 = 7,      // ����-����-2005
	VSB_JMC_BAOWEI_2 = 8,      // ����-����-2009
	VSB_JMC_QUANSHUN_1 = 9,      // ����-����������ȫ˳-2010,2008
	VSB_JMC_QUANSHUN_2 = 10,      // ����-����ȫ˳-2006
	VSB_JMC_QUANSHUN_3 = 11,      // ����-����ȫ˳-2013,2011,2010
	VSB_JMC_SHUNDA_1 = 12,      // ����-˳��-2004,2003
	VSB_JMC_SHUNDA_2 = 13,      // ����-˳��-2011,2010,2008
	VSB_JMC_YUSHENG_1 = 14,      // ����-Ԧʤ-2013
	VSB_JMC_YUSHENG_2 = 15       // ����-Ԧʤ-2013�ֶ���װ��,2012,2011
}VSB_JMC_CLASS;

// �ֶ�����Ʒ������
typedef enum _VSB_VOLVO_CLASS
{
	VSB_VOLVO_OTHER = 0,   // ������������
	VSB_VOLVO_C30_1 = 1,    // �ֶ���-C30-2013,2012,2011,2010
	VSB_VOLVO_S40_1 = 2,    // �ֶ���-S40-2012,2011,2010,2009,2008,2007
	VSB_VOLVO_S60_1 = 3,    // �ֶ���-S60-2003
	VSB_VOLVO_S60_2 = 4,    // �ֶ���-S60-2013,2012,2011
	VSB_VOLVO_S80L_1 = 5,    // �ֶ���-S80L-2012,2011,2010,2009
	VSB_VOLVO_XC60_1 = 6,    // �ֶ���-XC60-2013,2012,2011,2010,2009
	VSB_VOLVO_XC90_1 = 7     // �ֶ���-XC90-2013,2012,2011,2008
}VSB_VOLVO_CLASS;

// ������Ʒ������
typedef enum _VSB_HIGER_CLASS
{
	VSB_HIGER_OTHER = 0,   // ������������
	VSB_HIGER_H8_1 = 1,    // ����-H8-A��
	VSB_HIGER_H92_1 = 2,    // ����-H92-A��
	VSB_HIGER_V7_1 = 3,    // ����-V7,V8-2006
	VSB_HIGER_KECHE_1 = 4,    // ����-�ͳ�����5-A��
	VSB_HIGER_LONGWEI_1 = 5,    // ����-����-2012,2011
	VSB_HIGER_H7V_1 = 6     // ����-����H7V-2010
}VSB_HIGER_CLASS;

// ������Ʒ������
typedef enum _VSB_RUILIN_CLASS
{
	VSB_RUILIN_OTHER = 0,   // ������������
	VSB_RUILIN_G3_1 = 1,   // ����-G3-2012,2010
	VSB_RUILIN_G5_1 = 2,   // ����-G5-2012,2011,2010
	VSB_RUILIN_M1_1 = 3,   // ����-M1-2013,2011,2010,2009
	VSB_RUILIN_X1_1 = 4,   // ����-X1-2012A,2011,2010
	VSB_RUILIN_X1_2 = 5    // ����-X1-2012B
}VSB_RUILIN_CLASS;

// ������Ʒ������
typedef enum _VSB_SHENLONG_CLASS
{
	VSB_SHENLON_OTHER = 0,         // ������������
	VSB_SHENLONG_KECHE_1 = 1          //�����ͳ�-�ͳ�����4-A��
}VSB_SHENLONG_CLASS;

// ������Ʒ������
typedef enum _VSB_FOTON_CLASS
{
	VSB_FOTON_OTHER = 0,            // ������������
	VSB_FOTON_AOLING_1 = 1,            // ����-����-�п�
	VSB_FOTON_AOLING_2 = 2,            // ����-����-��ʽ����
	VSB_FOTON_AOLING_3 = 3,            // ����-����-����TX,CTX
	VSB_FOTON_OUMAN_1 = 4,            // ����-ŷ��-GTL6ϵB
	VSB_FOTON_OUMAN_2 = 5,            // ����-ŷ��-TX6ϵ,9ϵ
	VSB_FOTON_OUMAN_3 = 6,            // ����-ŷ��-ŷ���ؿ�1
	VSB_FOTON_OUMAN_4 = 7,            // ����-ŷ��-��ʨ6ϵ,9ϵ
	VSB_FOTON_OUHUI_1 = 8,            // ����-ŷ�Կͳ�-D��
	VSB_FOTON_OUMAKE_1 = 9,            // ����-ŷ���-3ϵ
	VSB_FOTON_OUMAKE_2 = 10,            // ����-ŷ���-5ϵ
	VSB_FOTON_SAPU_1 = 11,            // ����-����-2011
	VSB_FOTON_SAPU_3 = 12,            // ����-����-2011���͹���
	VSB_FOTON_MENGPAIKE_1 = 13,            // ����-���ɿ�-2013
	VSB_FOTON_MIDI_1 = 14,            // ����-�Ե�-2011,2009
	VSB_FOTON_FENGJING_1 = 15,            // ����-�羰ϵ��-2012,2011,2009
	VSB_FOTON_SAPU_2 = 16            // ����-����-2011����������Z7
}VSB_FOTON_CLASS;

//������Ʒ������
typedef enum _VSB_FODAY_CLASS
{
	VSB_FODAY_OTHER = 0,            // ������������
	VSB_FODAY_CHAOREN_1 = 1,            // ����-С����Ƥ��-2009,2006
	VSB_FODAY_CHAOREN_2 = 2,            // ����-С����Ƥ��-2011
	VSB_FODAY_TANSUOZHE_1 = 3,            // ����-̽����6-2013,2011,2010
	VSB_FODAY_TANSUOZHE_2 = 4,            // ����-̽���ߢ�-2011,2010,2009
	VSB_FODAY_TANSUOZHE_3 = 5,            // ����-̽���ߢ�-2011,2004
	VSB_FODAY_XIONGSHI_1 = 6             // ����-��ʨF16Ƥ��-2012
}VSB_FODAY_CLASS;

// ������Ʒ������
typedef enum _VSB_HONGQI_CLASS
{
	VSB_HONGQI_OTHER = 0,         // ������������
	VSB_HONGQI_MINGSHI_1 = 1           // ����-����-2007,2003,2001,2000,1999
}VSB_HONGQI_CLASS;


// ���ǽ� ��Ʒ������
typedef enum _VSB_LUXGEN_CLASS
{
	VSB_LUXGEN_OTHER = 0,         // ������������
	VSB_LUXGEN_DASEVEN_1 = 1          // ���ǽ�-��7-SUV
}VSB_LUXGEN_CLASS;

// ������Ʒ������
typedef enum _VSB_XIALI_CLASS
{
	VSB_XIALI_OTHER = 0,         // ������������
	VSB_XIALI_QIBING_1 = 1,         // ����(����)-���-2010
}VSB_XIALI_CLASS;

// ��ۿͳ���Ʒ������
typedef enum _VSB_SHUCHI_CLASS
{
	VSB_SHUCHI_OTHER = 0,         // ������������
	VSB_SHUCHI_A_1 = 1          // ��ۿͳ�-�ͳ�-A��
}VSB_SHUCHI_CLASS;

//Ӣ�������Ʒ������
typedef enum _VSB_INFINITI_CLASS
{
	VSB_INFINITI_OTHER = 0,         // ������������
	VSB_INFINITI_EX_1 = 1,         // Ӣ�����-EX-2013,2011,2010,2009,2008
	VSB_INFINITI_FX_1 = 2,         // Ӣ�����-FX-2007
	VSB_INFINITI_FX_2 = 3,         // Ӣ�����-FX-2011,2010,2009
	VSB_INFINITI_FX_3 = 4,         // Ӣ�����-FX-2013,2012FX35
	VSB_INFINITI_G_1 = 5,         // Ӣ�����-G-2013,2010
	VSB_INFINITI_JX_1 = 6          // Ӣ�����-JX-2013,2011
}VSB_INFINITI_CLASS;


// ������Ʒ������
typedef enum _VSB_LOTUS_CLASS
{
	VSB_LOTUS_OTHER = 0,            // ������������
	VSB_LOTUS_L3_1 = 1,            // ����-L3����-2010������,2009
	VSB_LOTUS_L3_2 = 2             // ����-L5����-2012,2011
}VSB_LOTUS_CLASS;

//��������Ʒ������
typedef enum _VSB_FIAT_CLASS
{
	VSB_FIAT_OTHER = 0,            // ������������
	VSB_FIAT_FEIYUE_1 = 1             // ������-��Ծ-2014,2013,2012
}VSB_FIAT_CLASS;

//ک����Ʒ������
typedef enum _VSB_OGA_CLASS
{
	VSB_OGA_OTHER = 0,              // ������������
	VSB_OGA_MDX_1 = 1,              // ک��-MDX-2010
	VSB_OGA_MDX_2 = 2               // ک��-MDX-2011
}VSB_OGA_CLASS;



// Ծ����Ʒ������
typedef enum _VSB_YUEJIN_CLASS
{
	VSB_YUEJIN_OTHER = 0,           // ������������
	VSB_YUEJIN_SHUAIHU_1 = 1,           // Ծ��-˧��-H100,H300
	VSB_YUEJIN_CAISHEN_1 = 2,           // Ծ��-����-S100
	VSB_YUEJIN_CAISHEN_2 = 3,           // Ծ��-����-S300
	VSB_YUEJIN_CAISHEN_3 = 4            // Ծ��-����-S500
}VSB_YUEJIN_CLASS;

//Ұ����Ʒ������
typedef enum _VSB_YEMA_CLASS
{
	VSB_YEMA_OTHER = 0,        // ������������
	VSB_YEMA_F99_1 = 1            // Ұ��-F99-2012,2011,2010,2009 
}VSB_YEMA_CLASS;

//������Ʒ������
typedef enum _VSB_SZKINGLONG_CLASS
{
	VSB_SZKINGLONG_OTHER = 0,        // ������������
	VSB_SZKINGLONG_BUS11_1 = 1,       // ����-�ͳ�����11-A��
	VSB_SZKINGLONG_BUS12_1 = 2,       // ����-�ͳ�����12-A��
	VSB_SZKINGLONG_BUS13_1 = 3,       // ����-�ͳ�����13-A��
	VSB_SZKINGLONG_BUS14_1 = 4,       // ����-�ͳ�����14-A��
	VSB_SZKINGLONG_BUS16_1 = 5,       // ����-�ͳ�����16-A��
	VSB_SZKINGLONG_BUS18_1 = 6,       // ����-�ͳ�����18-A��
	VSB_SZKINGLONG_BUS1_1 = 7,       // ����-�ͳ�����1-A��
	VSB_SZKINGLONG_BUS20_1 = 8,       // ����-�ͳ�����20-A��
	VSB_SZKINGLONG_BUS2_1 = 9,       // ����-�ͳ�����2-A��
	VSB_SZKINGLONG_BUS5_1 = 10,       // ����-�ͳ�����5-A��
	VSB_SZKINGLONG_BUS6_1 = 11,       // ����-�ͳ�����6-A��
	VSB_SZKINGLONG_BUS9_1 = 12,       // ����-�ͳ�����9-A��
	VSB_SZKINGLONG_BUS10_1 = 13,       // ����-�ͳ�����10-A��
	VSB_SZKINGLONG_BUS15_1 = 14        // ����-�ͳ�����15-A��
}VSB_SZKINGLONG_CLASS;

//�����Ա���Ʒ������
typedef enum _VSB_CHANGFENG_CLASS
{
	VSB_CHANGFENG_OTHER = 0,        // ������������
	VSB_CHANGFENG_CS7_1 = 1,        // �����Ա�-CS7-2009
	VSB_CHANGFENG_QIBING_1 = 2,        // �����Ա�-���-2010,2009
	VSB_CHANGFENG_LIEBAO_1 = 3,        // �����Ա�-�Ա�CS6-2010,2008
	VSB_CHANGFENG_FULING_1 = 4,        // �����Ա�-����Ƥ��-A��
	VSB_CHANGFENG_FEIYANG_1 = 5,        // �����Ա�-����Ƥ��-2010,2009,2005
	VSB_CHANGFENG_FEITENG_1 = 6,        // �����Ա�-����-2010,2009,2006
	VSB_CHANGFENG_BLACKJINGANG_1 = 7,        // �����Ա�-�ڽ��-2013,2010,2009,2008,2006
}VSB_CHANGFENG_CLASS;

//½����Ʒ������
typedef enum _VSB_LUFENG_CLASS
{
	VSB_LUFENG_OTHER = 0,           // ������������
	VSB_LUFENG_X6_1 = 1,           // ½��-X6-2005
	VSB_LUFENG_X6_2 = 2,           // ½��-X6-2006
	VSB_LUFENG_X6_3 = 3,           // ½��-X6-2011,2010,2008,2007
	VSB_LUFENG_LUFENGX5_1 = 4,           // ½��-½��X5-2013
	VSB_LUFENG_LUFENGX8_1 = 5,           // ½��-½��X8-2013,2012,2011,2009
	VSB_LUFENG_LUFENGX8_2 = 6,           // ½��-½��X8-2014,2012̽����
	VSB_LUFENG_FENGHUA_1 = 7,           // ½��-�绪-2008,2007
	VSB_LUFENG_X6_4 = 8,           // ½��-X6-2011����
	VSB_LUFENG_FENGSHANG_1 = 9            // ½��-����-2011,2006 
}VSB_LUFENG_CLASS;

//�����ؿ���Ʒ������
typedef enum _VSB_SHANQI_CLASS
{
	VSB_SHANQI_OTHER = 0,           // ������������
	VSB_SHANQI_AOLONG_1 = 1,           // �����ؿ�-����-�ؿ�A
	VSB_SHANQI_AOLONG_2 = 2,           // �����ؿ�-����-�ؿ�B
	VSB_SHANQI_DELONG_1 = 3,           // �����ؿ�-����F2000-4X2ǣ����
	VSB_SHANQI_DELONG_2 = 4,           // �����ؿ�-����F3000-B��
	VSB_SHANQI_DELONG_3 = 5,           // �����ؿ�-����M3000-�ؿ� 
}VSB_SHANQI_CLASS;


//Ұ����Ʒ������
typedef enum _VSB_RENAULT_CLASS
{
	VSB_RENAULT_OTHER = 0,          // ������������
	VSB_RENAULT_MEIGANNA_1 = 1,          // ��ŵ-÷����-2006
	VSB_RENAULT_KELEIAO_1 = 2,          // ��ŵ-���װ�-2010,2009
	VSB_RENAULT_KELEIAO_2 = 3,          // ��ŵ-���װ�-2013,2012
	VSB_RENAULT_SCENE_1 = 4,          // ��ŵ-�羰-2007
	VSB_RENAULT_FENGLANG_1 = 5,          // ��ŵ-����-2011
	VSB_RENAULT_TAFEIKE_1 = 6           // ��ŵ-���ƿ�-2004    
}VSB_RENAULT_CLASS;

//�ƺ���Ʒ������
typedef enum _VSB_HUANGHAI_CLASS
{
	VSB_HUANGHAI_OTHER = 0,         // ������������
	VSB_HUANGHAI_DACAISHEN_1 = 1,         // �ƺ�-�����-2013,2012
	VSB_HUANGHAI_DACAISHEN_2 = 2,         // �ƺ�-�����-2013,2012,2011,2010,2009���Ͱ�
	VSB_HUANGHAI_BUS4_1 = 3,         // �ƺ�-�ͳ�����4-2012,2011
	VSB_HUANGHAI_CHALLENGER_1 = 4,         // �ƺ�-��ս��-2011,2010,2009,2008
	VSB_HUANGHAI_AOLONGCUV_1 = 5,         // �ƺ�-����CUV-2010,2009
	VSB_HUANGHAI_AOJUN_1 = 6,         // �ƺ�-����-2009
	VSB_HUANGHAI_AOJUN_2 = 7,         // �ƺ�-����-2010,2009
	VSB_HUANGHAI_QISHENGV3_1 = 8,         // �ƺ�-��ʤV3-2011
	VSB_HUANGHAI_LINGHANGZHE_1 = 9,         // �ƺ�-�캽��-2007,2005
	VSB_HUANGHAI_FENGCHI_1 = 10         // �ƺ�-���-A��
}VSB_HUANGHAI_CLASS;

/********************����Ʒ��������End*************************/

//������Ϣ
typedef struct tagNET_DVR_VEHICLE_INFO_
{
	DWORD dwIndex;          //�������
	BYTE  byVehicleType;    //�������� 0 ��ʾ�������ͣ�1 ��ʾС�ͳ���2 ��ʾ���ͳ� ,3��ʾ���˴��� ,4��ʾ���ֳ����� 5��ʾ���ֳ�����(3.5Ver)
	BYTE  byColorDepth;        //������ɫ��ǳ
	BYTE  byColor;          //������ɫ,�ο�VCR_CLR_CLASS
							/*�״��쳣״̬��
							0~�״�������
							1~�״����
							2~�״�һֱ����ĳһ����ͬ�ٶ�ֵ
							3~�״��ͳ�����Ϊ0
							4~�״��ͳ����ݹ�����߹�С
							*/
	BYTE  byRadarState;
	WORD  wSpeed;           //��λkm/h
	WORD  wLength;          //ǰһ�����ĳ�����  
							/*Υ�����ͣ�0-������1-���٣�2-���٣�3-���У�4-�����,5-ѹ������,6-��������7-·��������
							8-��ռ�ǣ�9-Υ�������10-�������� 11-Υ�����12-·��ͣ����13-�̵�ͣ��, 14-δ��������(Υ������1357),
							15-Υ��ͣ����16-Υ�µ�ͷ,17-ռ��Ӧ������,18-����,19-����,20-ѹ����,21-δϵ��ȫ��,22-���˴����,23-����*/
	BYTE  byIllegalType;
	BYTE  byVehicleLogoRecog; //�ο�ö������ VLR_VEHICLE_CLASS
	BYTE  byVehicleSubLogoRecog; //����Ʒ��������ʶ�𣻲ο�VSB_VOLKSWAGEN_CLASS��������ö�١�
	BYTE  byVehicleModel; //������Ʒ����0-δ֪���ο�"������Ʒ�����.xlsx"
	BYTE  byCustomInfo[16];  //�Զ�����Ϣ
	WORD  wVehicleLogoRecog;  //������Ʒ�ƣ��ο�"������Ʒ��.xlsx" (���ֶμ���byVehicleLogoRecog);
	BYTE  byRes3[14];
}NET_DVR_VEHICLE_INFO, *LPNET_DVR_VEHICLE_INFO;
