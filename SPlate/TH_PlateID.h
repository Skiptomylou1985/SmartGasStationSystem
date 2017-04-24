// ***************************************************************
//  TH_PlateID.h   version:  4.0     date: 2010.4.12
//  -------------------------------------------------------------
//  �廪��ѧ����ͼ����Ϣ�����о��ҡ���Ȩ���С�
//  -------------------------------------------------------------
//  Center for Intelligent Image and Document Information Processing
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//   Author: Liu CS, Zhou J
// ***************************************************************
//		Revision history:
//			2010.4.12: v4.0, TH_PlateID����ʶ��SDK�Ľӿ�
// ***************************************************************
//��½����ʶ���㷨ͷ�ļ�  32λ  
#ifndef __TH_PLATEID_H_INCLUDE__
#define __TH_PLATEID_H_INCLUDE__

#if !defined(WIN32) && !defined(__stdcall)
#define __stdcall
#endif

#include "TH_ErrorDef.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


//������ɫ
#define LC_UNKNOWN  0	// δ֪
#define LC_BLUE   1		// ��ɫ
#define LC_YELLOW 2		// ��ɫ
#define LC_WHITE  3		// ��ɫ
#define LC_BLACK  4		// ��ɫ
#define LC_GREEN  5		// ��ɫ
	
//��������
#define LT_UNKNOWN  0   //δ֪����
#define LT_BLUE     1   //����
#define LT_BLACK    2   //����
#define LT_YELLOW   3   //���Ż���
#define LT_YELLOW2  4   //˫�Ż��ƣ���β�ƣ�ũ�ó���
#define LT_POLICE   5   //��������
#define LT_ARMPOL   6   //�侯����
#define LT_INDIVI   7   //���Ի�����
#define LT_ARMY     8   //���ž���
#define LT_ARMY2    9   //˫�ž���
#define LT_EMBASSY  10  //ʹ����
#define LT_HONGKONG 11  //�����
#define LT_TRACTOR  12  //������
#define LT_MACAU    13  //������
#define LT_CHANGNEI 14  //������
#define LT_MINHANG  15  //����

//����������
#define LGRAY_DARK	0	//��
#define LGRAY_LIGHT	1	//ǳ

//������ɫ
#define LCOLOUR_WHITE	0	//��	
#define LCOLOUR_SILVER	1	//��(��)
#define LCOLOUR_YELLOW	2	//��
#define LCOLOUR_PINK	3	//��
#define LCOLOUR_RED		4	//��
#define LCOLOUR_GREEN	5	//��
#define LCOLOUR_BLUE	6	//��
#define LCOLOUR_BROWN	7	//�� 
#define LCOLOUR_BLACK	8	//��


//�˶�����
#define DIRECTION_UNKNOWN	0
#define DIRECTION_LEFT	1
#define DIRECTION_RIGHT	2
#define DIRECTION_UP	3
#define DIRECTION_DOWN	4

//ͼ���ʽ��TH_SetImageFormat������cImageFormat������
#define ImageFormatRGB		0			//RGBRGBRGB...
#define ImageFormatBGR		1			//BGRBGRBGR...
#define ImageFormatYUV422	2			//YYYY...UU...VV..	(YV16)
#define ImageFormatYUV420COMPASS 3		//YYYY...UV...		(NV12)
#define ImageFormatYUV420	4			//YYYY...U...V...	(YU12)
#define ImageFormatUYVY	    5			//UYVYUYVYUYVY...	(UYVY)
#define ImageFormatNV21		6			//YYYY...VU...		(NV21)
#define ImageFormatYV12		7			//YYYY...V...U		(YV12)
#define ImageFormatNV16     8           //YYYY...UVUV...    (NV16��YUV422SP) UV�з���������з��򲻱� 

//��������֧�����ö���
//��TH_SetEnabledPlateFormat������dFormat������
#define PARAM_INDIVIDUAL_ON          0		// ���Ի����ƿ���
#define PARAM_INDIVIDUAL_OFF         1		// ���Ի����ƹر�
#define PARAM_TWOROWYELLOW_ON	     2		// ˫���ɫ���ƿ���
#define PARAM_TWOROWYELLOW_OFF	     3		// ˫���ɫ���ƹر�
#define PARAM_ARMPOLICE_ON           4		// �����侯���ƿ���
#define PARAM_ARMPOLICE_OFF          5		// �����侯���ƹر�
#define PARAM_TWOROWARMY_ON          6		// ˫����ӳ��ƿ���
#define PARAM_TWOROWARMY_OFF         7		// ˫����ӳ��ƹر�
#define PARAM_TRACTOR_ON			 8		// ũ�ó����ƿ���
#define PARAM_TRACTOR_OFF			 9		// ũ�ó����ƹر�
#define PARAM_ONLY_TWOROWYELLOW_ON   10		// ֻʶ��˫����ƿ���
#define PARAM_ONLY_TWOROWYELLOW_OFF  11		// ֻʶ��˫����ƹر�
#define PARAM_EMBASSY_ON			 12		// ʹ�ݳ��ƿ���
#define PARAM_EMBASSY_OFF			 13		// ʹ�ݳ��ƹر�
#define PARAM_ONLY_LOCATION_ON		 14		// ֻ��λ���ƿ���
#define PARAM_ONLY_LOCATION_OFF		 15		// ֻ��λ���ƹر�
#define PARAM_ARMPOLICE2_ON			 16		// ˫���侯���ƿ���
#define PARAM_ARMPOLICE2_OFF		 17		// ˫���侯���ƹر�
#define PARAM_CHANGNEI_ON			 18		// ���ڳ��ƿ���
#define PARAM_CHANGNEI_OFF			 19		// ���ڳ��ƹر�
#define PARAM_MINHANG_ON			 20		// �񺽳��ƿ���
#define PARAM_MINHANG_OFF			 21		// �񺽳��ƹر�


#define RECOG_STAGE_ALL			0		// �޴���
#define RECOG_STAGE_FINDPLATE	1		// û���ҵ�����
#define RECOG_STAGE_PLATESCORE_ZERO	2	// ��������ֵ(0��)
#define RECOG_STAGE_PLATESCORE_LOW	3	// ��������ֵ(������)
#define RECOG_STAGE_RECOGSCORE_ZERO	4	// ����ʶ�����(0��)
#define RECOG_STAGE_RECOGSCORE_LOW	5	// ����ʶ�����(������)

	
//��������
#define CarLogo_UNKNOWN       0    //δ֪
#define CarLogo_AUDI          1    //�µ�
#define CarLogo_BMW           2    //����
#define CarLogo_BENZ          3    //����
#define CarLogo_HONDA         4    //����
#define CarLogo_PEUGEOT       5    //��־
#define CarLogo_BUICK         6    //���
#define CarLogo_DASAUTO       7    //����
#define CarLogo_TOYOTA        8    //����
#define CarLogo_FORD          9    //����
#define CarLogo_SUZUKI        10   //��ľ
#define CarLogo_MAZDA         11   //���Դ�
#define CarLogo_KIA           12   //����
#define CarLogo_NISSAN        13   //�ղ���ɣ
#define CarLogo_HYUNDAI       14   //�ִ�
#define CarLogo_CHEVROLET     15   //ѩ����
#define CarLogo_CITROEN       16   //ѩ����

#define CarLogo_QIRUI         17   //����
#define CarLogo_WULING        18   //����
#define CarLogo_DONGFENG      19   //����
#define CarLogo_JIANGHUAI     20   //����
#define CarLogo_BEIQI         21   //����
#define CarLogo_CHANGAN       22   //����
#define CarLogo_AOCHI         23   //�³�
#define CarLogo_SHAOLING      24   //����
#define CarLogo_SHANQI        25   //����
#define CarLogo_SANLING       26   //����
#define CarLogo_JILI          27   //����
#define CarLogo_HAOWO         28   //����
#define CarLogo_HAIMA         29   //����
#define CarLogo_HAFEI         30   //����
#define CarLogo_CHANGCHENG    31   //����
#define CarLogo_FUTIAN        32   //����
#define CarLogo_NANJUN        33   //�Ͽ�
#define CarLogo_LIUQI         34   //����

// ��������
#define CARTYPE_UNKNOWN		0	// δ֪
#define CARTYPE_SALOON		1	// �γ�
#define CARTYPE_VAN			2	// �����

typedef struct TH_RECT
{
	int left;
	int top;
	int right;
	int bottom;
}TH_RECT;


typedef struct TH_PlateIDCfg
{
	int nMinPlateWidth;					// ������С���ƿ�ȣ�������Ϊ��λ
	int nMaxPlateWidth;					// ��������ƿ�ȣ�������Ϊ��λ
	
	int nMaxImageWidth;					// ���ͼ����
	int nMaxImageHeight;				// ���ͼ��߶�

	unsigned char bVertCompress;		// �Ƿ�ֱ����ѹ��1����ʶ��
	unsigned char bIsFieldImage;		// �Ƿ��ǳ�ͼ��
	unsigned char bOutputSingleFrame;	// �Ƿ���Ƶͼ����ͬһ�����Ķ��ͼ��ֻ���һ�ν��		
	unsigned char bMovingImage;			//   0�� ͼ��ģʽ 1�� ��Ƶģʽ

	unsigned char bIsNight;        //ģʽ  0 ������ģʽ   1��ҹ��ģʽ   
	unsigned char nImageFormat;    //ͼ��ĸ�ʽ   
									// 0��ImageFormatRGB			
									// 1��ImageFormatBGR			
									// 2��ImageFormatYUV422		
									// 3��ImageFormatYUV420COMPASS 3	
									// 4��ImageFormatYUV420	
									// 5��ImageFormatUYVY		
									// 6��ImageFormatNV21		
									// 7��ImageFormatYV12		
									// 8��ImageFormatNV16    

	

	unsigned char *pFastMemory;		// DSP�ȵ�Ƭ���ڴ棬��ʱ�����������ʹ����Щ�ڴ�
	int nFastMemorySize;				// DSP�ȵ�Ƭ���ڴ��ڴ�Ĵ�С

	unsigned char *pMemory;				// ��ͨ�ڴ�ĵ�ַ���ڽ����ڴ���������ڴ�й©������
	int nMemorySize;					// ��ͨ�ڴ�Ĵ�С

	int (*DMA_DataCopy)(void *dst, void *src,int nSize);
	int (*Check_DMA_Finished)();

	int nLastError;			// ���ڴ��ݴ�����Ϣ
							// 0: �޴���
							// 1: FindPlate(û���ҵ�����)
							// 2: ��������ֵ(0��)
							// 3: ��������ֵ(������)
							// 4: ����ʶ�����(0��)
	                        // 5: ����ʶ�����(������)
	int nErrorModelSN;		// �����ģ����
	unsigned char nOrderOpt;			//���˳��ѡ�� 0-���Ŷ� 1-���϶��� 2-���¶���
	unsigned char bLeanCorrection;		// �Ƿ�����б�������ܣ�Ĭ�Ͽ��� 0���رս���  1����������  
	unsigned char bMovingOutputOpt;   	// 0���ڲ�����+�ⲿ��ȡ 1���ⲿ��ȡ	
	unsigned char nImproveSpeed;        // 0: ʶ�������� 1:ʶ���ٶ�����
	unsigned char bCarLogo;             // 0: ����⳵�� 1: ��⳵��
	unsigned char bLotDetect;			// 0: ����⳵λ 1: ��⳵λ
	unsigned char bShadow;              // 0: �������Ӱ�ĳ��� 1���������Ӱ�ĳ��ƣ�Ĭ�Ͽ���
	unsigned char bUTF8;				// 0: ����GBK,1:����UTF-8
	unsigned char bShieldRailing;		// 0: �������˸��ţ� 1:���������˸���
	unsigned char bCarModel;			// 0: ��ʶ���ͣ� 1: ʶ����
	char reserved[110];					// WIN_X86
	//char reserved[110+128];				// WIN_X64

}TH_PlateIDCfg;

// ȱʡ����ʶ��SDK����
#if 1
const TH_PlateIDCfg c_defConfig = {80, 200, /* Min and Max Plate Width */ 
	720, 576, /* Max Image Width and Height*/ 
	0, /*vert compress*/ 0, /* Field Image? */0, /* output single*/  0/*Moving */,
	0 /* Night? */ , ImageFormatBGR,
	NULL, 0, 
	NULL,0, 
	NULL, NULL,
	0,0,0,0,0,0,0,0,0,0,0,0};
#endif

typedef struct TH_PlateIDResult 
{
	char license[16];	// �����ַ���
	char color[8];		// ������ɫ

	int nColor;			// ������ɫ
	int nType;			// ��������
	int nConfidence;	// ���ƿ��Ŷ�
	int nBright;		// ��������
	int nDirection;		// �����˶�����0 unknown, 1 left, 2 right, 3 up, 4 down 
	
	TH_RECT rcLocation;				// ��������
	const unsigned char *pbyBits;	/* ��ʶ������Ӧ��ͼƬ�Ļ�����, ֻ�е� bOutputSingleFrame = true ʱ����ָ�����Ч��
									�´�ʶ��󣬸û��������ݱ����ǡ����ó��������ͷŸû�������
									��������С���ڴ��ݽ�����ͼƬ���ݵĳ���*/
	int nTime;						// ʶ���ʱ
	unsigned char nCarBright;		//��������
	unsigned char nCarColor;		//������ɫ
	unsigned char nCarLogo;         //��������
	unsigned char nCarType;			//�������ͣ�������
	unsigned char *pbyPlateBin;     //���ƶ�ֵ���������bit�洢��
	unsigned short nBinPlateWidth;  //��ֵ������г��ƿ��
	unsigned short nBinPlateHeight; //��ֵ������г��Ƹ߶�
	char reserved[70];				//����
	TH_RECT rcLogoLocation;			// ��������
	unsigned short nCarModel;		// ��������
	unsigned short nCarModelConfidence;		//���Ϳ��Ŷ�	
}TH_PlateIDResult;


/************************************************************************/
/* TH_InitPlateIDSDK: ��ʼ������ʶ��SDK����ʹ�ø�SDK�Ĺ���ǰ			*/
/*			�����ҽ������һ�θú���									*/
/*		Parameters:														*/
/*			pPlateConfig[in]: ����ʶ��SDK������							*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_InitPlateIDSDK(TH_PlateIDCfg *pPlateConfig);

/************************************************************************/
/* TH_UninitPlateIDSDK: �ͷų���ʶ��SDK����ʹ�ø�SDK�Ĺ��ܺ�			*/
/*			�����ҽ������һ�θú��������ͷ��ڴ档						*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_UninitPlateIDSDK(TH_PlateIDCfg *pPlateCfg);

/************************************************************************/
/* TH_RecogImage: ʶ���ڴ��г���ͼ��(���ʶ�𵽵Ķ�����)	*/
/*		Parameters:														*/
/*			pbyBits[in]: ָ���ڴ�ͼ�����ݵ�ָ�룬3���ֽڱ�ʾ1������		*/
/*			nWidth[in]: ͼ��Ŀ��										*/
/*			nHeight[in]: ͼ��ĸ߶�										*/
/*			pResult[out]: ����ʶ��������, ���÷�����pResult[nResultNum]�ڴ�*/
/*			nResultNum[in,out]: in ����ѡ���Ƹ�����out ʶ����ĳ��Ƹ���*/
/*			prcRange[in]: ָ��ʶ��Χ									*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_RecogImage(const unsigned char *pbyBits, int nWidth, int nHeight, TH_PlateIDResult *pResult,
	int *nResultNum, const TH_RECT *prcRange, TH_PlateIDCfg *pPlateConfig);

/************************************************************************/
/* TH_EvaluateCarColor: ʶ�𳵵���ɫ									*/
/*		Parameters:														*/
/*			pbyBits[in]: ָ���ڴ�ͼ�����ݵ�ָ�룬3���ֽڱ�ʾ1������		*/
/*			nWidth[in]: ͼ��Ŀ��										*/
/*			nHeight[in]: ͼ��ĸ߶�										*/
/*			pResult[out]: ����ʶ��������, ���÷�����pResult[nResultNum]�ڴ�*/
/*			nResultNum[in,out]: in ����ѡ���Ƹ�����out ʶ����ĳ��Ƹ���*/
/*			prcRange[in]: ָ��ʶ��Χ									*/
/*		Return Value: int(ERR_Code)										*/
/*		TH_EvaluateCarColor����TH_RecogImage֮����ã����ֲ�������		*/
/************************************************************************/
int __stdcall TH_EvaluateCarColor(const unsigned char *pbyBits, int nWidth, int nHeight, TH_PlateIDResult *pResult,
	int *nResultNum, const TH_RECT *prcRange, TH_PlateIDCfg *pPlateConfig);

/************************************************************************/
/* TH_SetImageFormat: ����ͼ���ʽ										*/
/*		Parameters:														*/
/*			cImageFormat[in]: ͼ���ʽ									*/
/*			bVertFlip[in]: �Ƿ�ߵ�										*/
/*			bDwordAligned[in]: �Ƿ�4�ֽڶ���							*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetImageFormat( unsigned char cImageFormat, unsigned char bVertFlip, unsigned char bDwordAligned, TH_PlateIDCfg *pPlateConfig );

/************************************************************************/
/* TH_SetEnabledPlateFormat: ����֧�ֵĳ�������							*/
/*		Parameters:														*/
/*			dFormat[in]: �������Ϳ��أ�����PARAM_INDIVIDUAL_ON			*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetEnabledPlateFormat(unsigned int dFormat, TH_PlateIDCfg *pPlateConfig);

/************************************************************************/
/* TH_SetProvinceOrder: ����ʡ���ַ���									*/
/*		Parameters:														*/
/*			szProvince[in]: Ĭ��ʡ���ַ���������"����"�����֧��8��ʡ��*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetProvinceOrder( char* szProvince, TH_PlateIDCfg *pPlateConfig);

/************************************************************************/
/* TH_SetRecogThreshold: ����ʶ����ֵ									*/
/*		Parameters:														*/
/*			nPlateLocate_Th[in]: 0 - 9		--   7: Ĭ����ֵ			*/
/*					nOCR_Th[in]: 0 - 9		--   5: Ĭ����ֵ			*/
/*				0: ����ɵ���ֵ											*/
/*				9:���ϸ����ֵ											*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetRecogThreshold( unsigned char nPlateLocate_Th, unsigned char nOCR_Th, TH_PlateIDCfg *pPlateCfg);

//��鹤����������С��ʣ���ڴ棬������ָ���������Ҫ���Ӹ����ĳ�ʼ�ڴ�
int __stdcall TH_CheckMinFreeMemory( int *pnMinFreeSRAM, int *pnMinFreeSDRAM, TH_PlateIDCfg *pPlateCfg);

/************************************************************************/
/* ����: ��ȡ�汾��														*/
/*		Parameters����													*/
/*		����ֵ: �ַ��� ��ʽ�����汾��.���汾��.�޶���.�����			*/
/*				�����ͷŸ�ָ�롣										*/
/************************************************************************/
const char * __stdcall TH_GetVersion();

/************************************************************************/
/* ����: ��ȡ������ID, ������ID��8�ֽ�ΨһID��							*/
/*		���ô˺���ǰ��Ҫ����TH_InitPlateIDSDK							*/
/*		Parameters������ΨһIDʱ��ID1��ǰ4�ֽ�,ID2�Ǻ����ֽ�			*/
/*		����ֵ: 0-��ΨһID												*/
/*				1-��ΨһID												*/
/************************************************************************/
int __stdcall TH_GetKeyID(unsigned int* ID1, unsigned int* ID2);

/************************************************************************/
/* ����: ��ȡ������·����Ϣ��											*/
/*		ʹ��TH_InitPlateIDSDKǰ���ô˺���								*/
/*		Parameters��nMaxThread[out]:									*/
/*		����ֵ:  int(ERR_Code)											*/
/************************************************************************/
int __stdcall TH_GetKeyMaxThread(int* nMaxThread);


/************************************************************************/
/* ����: ���õ�ǰʶ��ĶԱȶ���ֵ										*/
/*		Parameters��nContrast[int]:										*/
/*		�Աȶ�ָ�� nContrast[in]: 0 - 9									*/
/*		��ģ��ʱ��Ϊ1;������ʱ��Ϊ9;�Զ�̽����Ϊ0;Ĭ��ֵΪ0				*/
/*		����ֵ:  int(ERR_Code)											*/
/************************************************************************/
int __stdcall TH_SetContrast( unsigned char nContrast, TH_PlateIDCfg *pPlateCfg );
																			


/************************************************************************/
/* TH_SetEnableCarTypeClassify: �����Ƿ��������б�					*/
/*		Parameters:														*/
/*			bCarTypeClass[in]: true:���ͷ���;							*/
/*								false:�����г��ͷ���					*/
/*		Return Value: int(ERR_Code)										*/
/*		֧�ָ�ʽ: ImageFormatBGR, ImageFormatRGB,ImageFormatYUV422,
				ImageFormatUYVY,ImageFormatNV21*/
/************************************************************************/
int __stdcall TH_SetEnableCarTypeClassify( unsigned char bCarTypeClass, TH_PlateIDCfg *pPlateCfg);


/************************************************************************/
/* TH_SetEnableCarLogo: �����Ƿ񳵱�ʶ��								*/
/*		Parameters:														*/
/*			bCarLogo[in]: true:����ʶ��;								*/
/*								false:�����г���ʶ��					*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetEnableCarLogo( unsigned char bCarLogo, TH_PlateIDCfg *pPlateCfg);

/************************************************************************/
/* TH_SetEnableCarWidth: �����Ƿ�����������							*/
/*		Parameters:														*/
/*			bCarLogo[in]: true:�����������;							*/
/*							false:�������������						*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetEnableCarWidth( unsigned char bCarWidth, TH_PlateIDCfg *pPlateCfg);

int __stdcall TH_SetReserveInfo(unsigned char* pSN);

// TH_SetDayNightMode: V4.3.13.0�Ժ�����ʵ�����壬Ϊ��֤�����Ա����˺���
int __stdcall TH_SetDayNightMode( unsigned char bIsNight, TH_PlateIDCfg *pPlateConfig);

/************************************************************************/
/* TH_SetVideoModeOutPutPosRatio: ������Ƶģʽ�������λ��ϵ��				*/
/*		Parameters:														*/
/*			ratio[in]: (0.1, 0.9);										*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetVideoModeOutPutPosRatio(float ratio);

/************************************************************************/
/* TH_GetVehicleModelName: ��������ַ������ڵ���TH_RecogImage����øú���*/
/*		Parameters:														*/
/*			nModel[in]: ��������ֵ��TH_PlateIDResult�ṹ���е�nCarModel;*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
const char *  __stdcall TH_GetVehicleModelName(int nModel);

/************************************************************************/
/* TH_SetEnableLeanCorrection: �����Ƿ����бУ��								*/
/*		Parameters:														*/
/*			bLeanCorrection[in]: true:����бУ��;								*/
/*								 false:�ر���бУ��					*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetEnableLeanCorrection( unsigned char bLeanCorrection, TH_PlateIDCfg *pPlateCfg);

/************************************************************************/
/* TH_SetEnableShadow: �����Ƿ��������ʶ��								*/
/*		Parameters:														*/
/*			bShadow[in]: true:��������;								*/
/*						 false:�ر�������					*/
/*		Return Value: int(ERR_Code)										*/
/************************************************************************/
int __stdcall TH_SetEnableShadow( unsigned char bShadow, TH_PlateIDCfg *pPlateCfg);

#ifdef __cplusplus
}
#endif

#endif	//	__TH_PLATEID_H_INCLUDE__
