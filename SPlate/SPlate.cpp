// SPlate.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "SPlate.h"
#include <process.h>
#include <tchar.h>
#include "jpeglib.h"

//Ӳ��¼������
NET_DVR_DEVICEINFO_V30 deviceInfo;
NET_DVR_PREVIEWINFO previewInfo;
HWND hRealVideoHanlder;
struNVRInfo nvrInfo;
LONG testBufferSize ;
LONG callBackNum;

TH_PlateIDCfg th_PlateIDCfg ;
//TH_PlateIDCfg th_PlateIDCfg_bak;
TH_PlateIDResult recogResult[6];
int nCarNum;
BITMAPINFOHEADER bitmapHeader;
TH_RECT th_RECT;
LONG nPort = -1;

int nAlgStatus = 0;
int nCurGetIndex = 0;
int nCurPutIndex = 0;
struCarInfoOut carInfoOut[MAX_CAR_COUNT];
struCarInfoOut tempCarOut;
struCarInfoOut_V2 carOutCache;
unsigned char *videoChan [MAX_VIDEO_CHANNEL_COUNT];
struAreaInfo areaInfo[MAX_AREA_COUNT];
struNozzleInfo nozzleInfo[MAX_NOZZLE_COUNT];
int nAreaCount = 0;
int nNozzleCount = 0;
int nVideoChanCount = 0;
int nLogLevel = 3;
int nCurCarCount = 0;
int nCurAreaIndex= 0;
char debugInfo[256] ;
int calc = 0;
NET_DVR_IPPARACFG_V40 struIPPARACFG;
bool isRecog = false;
int nSwitchCount = 10;
char *lastLicense[MAX_AREA_COUNT] ;
int nSwithFlag;
uintptr_t ThreadSwith = NULL;
bool bSwitchComplete = false;
int nframeCount;
char pBuffer[MAX_PIC_LENTH];

void _stdcall ThreadKeepSwitch()
{
	while (isRecog)
	{
		nSwithFlag++;
		if (nSwithFlag >60)
		{
			nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, RealDataCallBack, nullptr);
			write_log_file("Error.txt", MAX_FILE_SIZE, "������Ƶ�л�", strlen("������Ƶ�л�"), 1);
			nSwithFlag = 0;
		}
		Sleep(1000);
	}
}
SPLATE_API int SP_InitRunParam(unsigned char *pArea, int lenth)
{
	memset(&tempCarOut, 0, sizeof(tempCarOut));
	if (lenth > MAX_AREA_COUNT)
	{
		return INVALID_AREA_COUNT;
	}
	memcpy(areaInfo, pArea, lenth*sizeof(struAreaInfo));
	nAreaCount = lenth;
	for (int i = 0; i < nAreaCount; i++)
	{
		lastLicense[i] = (char *)malloc(16);
		areaInfo[i].videoChanNo += struIPPARACFG.dwStartDChan;

		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "index��");
		_itoa(i, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "AreaID��");
		_itoa(areaInfo[i].areaNo, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " video��");
		_itoa(areaInfo[i].videoChanNo, debugInfo + strlen(debugInfo), 10);
		write_log_file("license.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		
	}
	return SUCCESS;
}
SPLATE_API int SP_InitRunParam_V2(BYTE *pNozzleInfo, int lenth)
{
	memset(&tempCarOut, 0, sizeof(tempCarOut));
	if (lenth > MAX_AREA_COUNT)
	{
		return INVALID_AREA_COUNT;
	}
	memcpy(nozzleInfo, pNozzleInfo, lenth * sizeof(struNozzleInfo));
	nNozzleCount = lenth;
	for (int i = 0; i < nAreaCount; i++)
	{
		nozzleInfo[i].videoChan += struIPPARACFG.dwStartDChan;

		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "index��");
		_itoa(i, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "nozzleNo��");
		_itoa(nozzleInfo[i].nozzleNo, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "areaCount��");
		_itoa(nozzleInfo[i].areaCount, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " video��");
		_itoa(nozzleInfo[i].videoChan, debugInfo + strlen(debugInfo), 10);
		write_log_file("license.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);

	}
	return SUCCESS;
}
SPLATE_API int SP_InitNVR(char *IpAddress, LONG nPort, char *sAdmin, char *sPassword)
{
	
	bool ret = NET_DVR_Init();
	NET_DVR_SetConnectTime(2000, 1); 
	NET_DVR_SetReconnect(10000, true);
	if (!ret)
	{
		return NET_DVR_GetLastError();
	}
	nvrInfo.IpAddress = IpAddress;
	nvrInfo.sAdmin = sAdmin;
	nvrInfo.sPassword = sPassword;
	nvrInfo.nPort = nPort;
	nvrInfo.m_lServerID = NET_DVR_Login_V30(nvrInfo.IpAddress, nvrInfo.nPort, nvrInfo.sAdmin, nvrInfo.sPassword, &deviceInfo);
	//NET_DVR_GET_IPPARACFG(nvrInfo.m_lServerID, NET_DVR_GET_IPPARACFG_V40,0,)
	if (nvrInfo.m_lServerID < 0)
	{
		return NET_DVR_GetLastError();
	}
	DWORD dwReturn = 0;
	NET_DVR_GetDVRConfig(nvrInfo.m_lServerID, NET_DVR_GET_IPPARACFG_V40, 0, &struIPPARACFG, sizeof(struIPPARACFG), &dwReturn);
	return SUCCESS;
}
SPLATE_API int SP_GetNvrCfg(NET_DVR_IPPARACFG_V40 *nvrCfg,int &lenth)
{
	lenth = sizeof(struIPPARACFG);
	memcpy(nvrCfg, &struIPPARACFG, sizeof(struIPPARACFG));
	return 0;
}
SPLATE_API int SP_Close()
{
	isRecog = false;

	if (nvrInfo.m_lServerID > 0)
	{
		NET_DVR_Logout(nvrInfo.m_lServerID);
		NET_DVR_Cleanup();
	}
	TH_UninitPlateIDSDK(&th_PlateIDCfg);
	 
	return SUCCESS;
}
SPLATE_API int SP_PreviewInfo(NET_DVR_PREVIEWINFO *preInfo, int lenth)
{
	memcpy(&previewInfo, preInfo, lenth);
	//previewInfo.lChannel = nozzleInfo[nCurNozzleIndex].videoChanNo;
	HWND pUser = nullptr;//�û�����
	if (nvrInfo.m_lPlayHandle > -1)
	{
		NET_DVR_StopRealPlay(nvrInfo.m_lPlayHandle);
	}
	nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, NULL, pUser);
	if (nvrInfo.m_lPlayHandle < 0)
	{
		return NET_DVR_GetLastError();
	}
	return nvrInfo.m_lPlayHandle;
}
SPLATE_API int SP_BeginRecog(HWND hPlayHandle)
{
	//TODO ��ʱ����
	return 0;
	isRecog = true;
	//ThreadSwith = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadKeepSwitch, NULL, 0, NULL);
	previewInfo.hPlayWnd = nullptr;
	previewInfo.lChannel = areaInfo[nCurAreaIndex].videoChanNo;
	if (hPlayHandle != NULL)
	{
		previewInfo.hPlayWnd = hPlayHandle;
	}
	previewInfo.dwStreamType = 0;//�������ͣ�0-��������1-��������2-����3��3-����4���Դ�����
	previewInfo.dwLinkMode = 0;//���ӷ�ʽ��0- TCP��ʽ��1- UDP��ʽ��2- �ಥ��ʽ��3- RTP��ʽ��4-RTP/RTSP��5-RSTP/HTTP 
	previewInfo.bBlocked = false; //0- ������ȡ����1- ����ȡ��
	previewInfo.dwDisplayBufNum = 15;
	HWND pUser = nullptr;//�û�����
	nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, RealDataCallBack, pUser);
	
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "NET_DVR_RealPlay_V40 return value:");
	_itoa(nvrInfo.m_lPlayHandle, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo+strlen(debugInfo), " ͨ����:");
	_itoa(areaInfo[nCurAreaIndex].videoChanNo, debugInfo + strlen(debugInfo), 10);
	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),3);
	if (nvrInfo.m_lPlayHandle < 0)
	{
		return NET_DVR_GetLastError();
	}
	return nvrInfo.m_lPlayHandle;

}
SPLATE_API int SP_InitAlg(TH_PlateIDCfg *th_plateIDCfg, int lenth)
{
	write_log_file("Debug.txt", MAX_FILE_SIZE, "begin initAlg", strlen("begin initAlg"), 3);
	if (lenth != sizeof(TH_PlateIDCfg))
	{
		return INVALID_LENTH;
	}
	memcpy(&th_PlateIDCfg, th_plateIDCfg, lenth);
	nAlgStatus = TH_InitPlateIDSDK(&th_PlateIDCfg);
	write_log_file("Debug.txt", MAX_FILE_SIZE, "TH_InitPlateIDSDK", strlen("TH_InitPlateIDSDK"), 3);
	TH_SetImageFormat(ImageFormatYV12, false, false, &th_PlateIDCfg);
	TH_SetRecogThreshold(5, 2, &th_PlateIDCfg);//������ֵ 
	write_log_file("Debug.txt", MAX_FILE_SIZE, "TH_SetRecogThreshold", strlen("TH_SetRecogThreshold"), 3);
	return nAlgStatus;
}
SPLATE_API int SP_GetCarCount()
{
	return nCurCarCount;
}
SPLATE_API int SP_GetFirstCarInfo(struCarInfoOut *carinfo, int &lenth)
{
	if (nCurCarCount > 0)
	{
		lenth = sizeof(struCarInfoOut);
		memcpy(carinfo, &carInfoOut[nCurGetIndex], sizeof(struCarInfoOut));
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "��λ����ȡ���ƣ�");
		strcpy(debugInfo + strlen(debugInfo), carInfoOut[nCurGetIndex].license);
		strcpy(debugInfo + strlen(debugInfo), "ʶ�����ţ�");
		_itoa(carInfoOut[nCurGetIndex].nAreaNo, debugInfo + strlen(debugInfo), 10);
		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		nCurCarCount--;
		if (++nCurGetIndex == MAX_CAR_COUNT)
			nCurGetIndex = 0;
		return SUCCESS;
	}
	return FAIL;
}
SPLATE_API int SP_GetCarInfo(struCarInfoOut *carinfo, int carCount,int &lenth)
{
	if (carCount > nCurCarCount || carCount <= 0)
		return INVALID_CAR_COUNT;
	int size = sizeof(struCarInfoOut);
	for (int i = 0;i<carCount;i++)
	{
		memcpy(carinfo + size*i, &carInfoOut[nCurGetIndex], size);
		nCurCarCount--;
		if (++nCurGetIndex == MAX_CAR_COUNT)
			nCurGetIndex = 0;
	}
	lenth = carCount*size;
	return SUCCESS;
}
SPLATE_API int SP_GetNvrStatus()
{
	return nvrInfo.m_lServerID;
}

SPLATE_API int SP_SetLogLevel(int loglevel)
{
	nLogLevel = loglevel;
	set_log_level(loglevel);
	return SUCCESS;
}
SPLATE_API int SP_SetSwitchCount(int frameCount)
{
	nSwitchCount = frameCount;
	return SUCCESS;
}
SPLATE_API int SP_Snap(int videoChan, char *lic,unsigned char * picBuffer,int &picLenth)
{
	
	int picSize = 10 * 1024 * 1024;
	char *pBufer = (char *)malloc(picSize);
	NET_DVR_JPEGPARA jpegPara;
	jpegPara.wPicQuality = 0;
	jpegPara.wPicSize = 0xFF; //��ǰ�����ֱ��ʣ�
	DWORD x = 0;
	LPDWORD retPicSize  = &x;
	write_log_file("snap.txt", MAX_FILE_SIZE, "begin", 5, 3);
	NET_DVR_CaptureJPEGPicture_NEW(nvrInfo.m_lServerID, videoChan, &jpegPara, pBufer, picSize, retPicSize);
	int lenth = *retPicSize;

	memcpy(picBuffer,pBufer, lenth);
	picLenth = lenth;
	write_log_file("snap.txt", MAX_FILE_SIZE, "step 2", 1, 3);
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "ͼƬ����:");
	_itoa(lenth, debugInfo + strlen(debugInfo), 10);
	write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);

	unsigned char *p = (unsigned char *)pBufer;
	const unsigned char *pp = (const unsigned char *)p;
	char *license = (char *)malloc(16);
	SP_DecJpeg(pp, *retPicSize, license);
	memcpy(lic, license, 16);
	free(pBufer);
	return 0;
}
SPLATE_API int SP_DecJpeg(const unsigned char * pJpegPic,int nJpegLenth,char *license)
{
	/*FILE *input_file;
	input_file = fopen("C:\\lic.jpg", "rb");*/

	struct jpeg_decompress_struct cinfo;//JPEGͼ���ڽ�������У�ʹ��jpeg_decompress_struct���͵Ľṹ������ʾ��ͼ���������Ϣ���洢�ڽṹ����
	struct jpeg_error_mgr jerr;//����һ����׼�Ĵ���ṹ�壬һ��������ִ���ͻ����exit()�����˳�����

	cinfo.err = jpeg_std_error(&jerr);//�󶨴�����ṹ����
	jpeg_create_decompress(&cinfo);//��ʼ��cinfo�ṹ
	//jpeg_stdio_src(&cinfo, input_file);
	write_log_file("snap.txt", MAX_FILE_SIZE, "3", 1, 3);
	jpeg_mem_src(&cinfo, pJpegPic, nJpegLenth);//ָ����ѹ������Դ
	jpeg_read_header(&cinfo, TRUE);//��ȡ�ļ���Ϣ
	jpeg_start_decompress(&cinfo);//��ʼ��ѹ��
	write_log_file("snap.txt", MAX_FILE_SIZE, "4", 1, 3);
	unsigned long width = cinfo.output_width;//ͼ����
	unsigned long height = cinfo.output_height;//ͼ��߶�
	unsigned short depth = cinfo.output_components;//ͼ�����
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "ͼƬ���:");
	_itoa(width, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), "ͼƬ�߶�:");
	_itoa(height, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), "ͼƬ���:");
	_itoa(depth, debugInfo + strlen(debugInfo), 10);
	write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	unsigned char *src_buff;//���ڴ�ȡ����֮���λͼ����(RGB��ʽ)
	src_buff = (unsigned char *)malloc(width * height * depth);//����λͼ���ݿռ�
	memset(src_buff, 0, sizeof(unsigned char) * width * height * depth);//��0

	//JSAMPARRAY buffer[1];//���ڴ�ȡһ������
	//JSAMPARRAY buffer = (JSAMPARRAY)malloc(width*depth);
	JSAMPARRAY buffer;
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width*depth, 1);//����һ�����ݿռ�
	//unsigned char * buffer = (unsigned char *)malloc(width*depth);
	write_log_file("snap.txt", MAX_FILE_SIZE, "5", 1, 3);
	unsigned char *point = src_buff;
	while (cinfo.output_scanline < height)//���ж�ȡλͼ����
	{
		jpeg_read_scanlines(&cinfo, buffer, 1);    //��ȡһ��jpgͼ�����ݵ�buffer
		memcpy(point, *buffer, width*depth);    //��buffer�е��������и�src_buff
		point += width * depth;            //ָ��ƫ��һ��
	}
	
	TH_SetImageFormat(ImageFormatRGB, false, false, &th_PlateIDCfg);
	int nCarNum = 1;
	const unsigned char * pp = (const unsigned char *)src_buff;

	th_RECT.left = 180;
	th_RECT.top = 350;
	th_RECT.right = 380;
	th_RECT.bottom = 450;
	TH_RecogImage(pp, width, height, recogResult, &nCarNum,nullptr, &th_PlateIDCfg);
	if (nCarNum > 0)
	{
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "����:");
		memcpy(debugInfo+strlen(debugInfo), recogResult[0].license,strlen(recogResult[0].license));
		write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		//write_log_file("snap.txt", MAX_FILE_SIZE, "get license", strlen("get license"), 3);
		memcpy(license, &recogResult[0].license, strlen(recogResult[0].license));
	}
	write_log_file("snap.txt", MAX_FILE_SIZE, "6", 1, 3);
	jpeg_finish_decompress(&cinfo);//��ѹ�����
	jpeg_destroy_decompress(&cinfo);// �ͷ���Դ
	free(src_buff);//�ͷ���Դ
	//fclose(input_file);
	write_log_file("snap.txt", MAX_FILE_SIZE, "7", 1, 3);
	return 0;
}
SPLATE_API int SP_Capture(int areaNo, struCarInfoOut *carinfo)
{
	int index = -1;
	for (int i = 0 ;i<nAreaCount;i++)
	{
		if (areaNo == areaInfo[i].areaNo)
		{
			index = i;
			break;
		}
	}
	if (index < 0)
	{
		return -1;
	}
	NET_DVR_JPEGPARA jpegPara;
	jpegPara.wPicQuality = 0;
	jpegPara.wPicSize = 0xFF; //��ǰ�����ֱ��ʣ�
	DWORD x = 0;
	LPDWORD retPicSize = &x;
	write_log_file("snap.txt", MAX_FILE_SIZE, "begin", 5, 3);
	NET_DVR_CaptureJPEGPicture_NEW(nvrInfo.m_lServerID, areaInfo[index].videoChanNo, &jpegPara, pBuffer, MAX_PIC_LENTH, retPicSize);
	int lenth = *retPicSize;
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "ͼƬ����:");
	_itoa(lenth, debugInfo + strlen(debugInfo), 10);
	write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	char *p1 = pBuffer;
	unsigned char *p = (unsigned char *)p1;
	const unsigned char *pp = (const unsigned char *)p;

	struct jpeg_decompress_struct cinfo;//JPEGͼ���ڽ�������У�ʹ��jpeg_decompress_struct���͵Ľṹ������ʾ��ͼ���������Ϣ���洢�ڽṹ����
	struct jpeg_error_mgr jerr;//����һ����׼�Ĵ���ṹ�壬һ��������ִ���ͻ����exit()�����˳�����

	cinfo.err = jpeg_std_error(&jerr);//�󶨴�����ṹ����
	jpeg_create_decompress(&cinfo);//��ʼ��cinfo�ṹ
								   //jpeg_stdio_src()
	jpeg_mem_src(&cinfo, pp, lenth);//ָ����ѹ������Դ
	jpeg_read_header(&cinfo, TRUE);//��ȡ�ļ���Ϣ
	jpeg_start_decompress(&cinfo);//��ʼ��ѹ��
	unsigned long width = cinfo.output_width;//ͼ����
	unsigned long height = cinfo.output_height;//ͼ��߶�
	unsigned short depth = cinfo.output_components;//ͼ�����
	//memset(debugInfo, 0, sizeof(debugInfo));
	//strcpy(debugInfo, "ͼƬ��С:");
	//_itoa(lenth, debugInfo + strlen(debugInfo), 10);
	//strcpy(debugInfo, "ͼƬ���:");
	//_itoa(width, debugInfo + strlen(debugInfo), 10);
	//strcpy(debugInfo, "ͼƬ�߶�:");
	//_itoa(height, debugInfo + strlen(debugInfo), 10);
	//strcpy(debugInfo, "ͼƬ���:");
	//_itoa(depth, debugInfo + strlen(debugInfo), 10);
	//write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	unsigned char *src_buff;//���ڴ�ȡ����֮���λͼ����(RGB��ʽ)
	src_buff = (unsigned char *)malloc(width * height * depth);//����λͼ���ݿռ�
	memset(src_buff, 0, sizeof(unsigned char) * width * height * depth);//��0

																		//JSAMPARRAY buffer[1];//���ڴ�ȡһ������
																		//JSAMPARRAY buffer = (JSAMPARRAY)malloc(width*depth);
	JSAMPARRAY buffer;
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width*depth, 1);//����һ�����ݿռ�
				
	unsigned char *point = src_buff;
	while (cinfo.output_scanline < height)//���ж�ȡλͼ����
	{
		jpeg_read_scanlines(&cinfo, buffer, 1);    //��ȡһ��jpgͼ�����ݵ�buffer
		memcpy(point, *buffer, width*depth);    //��buffer�е��������и�src_buff
		point += width * depth;            //ָ��ƫ��һ��
	}

	TH_SetImageFormat(ImageFormatRGB, false, false, &th_PlateIDCfg);
	int nCarNum = 1;
	const unsigned char * src = (const unsigned char *)src_buff;
	TH_RecogImage(src, width, height, recogResult, &nCarNum, &areaInfo[index].th_rect, &th_PlateIDCfg);
	if (nCarNum > 0)
	{
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "����:");
		memcpy(debugInfo + strlen(debugInfo), recogResult[0].license, strlen(recogResult[0].license));
		write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		memset(&tempCarOut, 0, sizeof(tempCarOut));
		memcpy(tempCarOut.license, recogResult[0].license, strlen(recogResult[0].license));
		memcpy(tempCarOut.color, recogResult[0].color, 8);
		memcpy(tempCarOut.pic, pBuffer, lenth);
		tempCarOut.nCarColor = recogResult[0].nCarColor;
		tempCarOut.nCarLogo = recogResult[0].nCarLogo;
		tempCarOut.nSubCarLogo = recogResult[0].nCarType;
		tempCarOut.nCarModel = recogResult[0].nCarModel;
		tempCarOut.nColor = recogResult[0].nColor;
		tempCarOut.nConfidence = recogResult[0].nConfidence;
		tempCarOut.nPicLenth = lenth;
		tempCarOut.nVideoChannel = areaInfo[index].videoChanNo;
		tempCarOut.nAreaNo = areaNo;
		tempCarOut.nPicType = 0;
		tempCarOut.nType = recogResult[0].nType;
		tempCarOut.nPicWidth = width;
		tempCarOut.nPicHeight = height;
		memcpy(carinfo, &tempCarOut, sizeof(tempCarOut));
	}
	jpeg_finish_decompress(&cinfo);//��ѹ�����
	jpeg_destroy_decompress(&cinfo);// �ͷ���Դ
	free(src_buff);//�ͷ���Դ
	return 0;

}
SPLATE_API int SP_Capture_V2(int nozzleNo, struCarInfoOut_V2 *carInfo)
{
	int nLicCount = 0;
	int index = -1;
	for (int i =0;i<nNozzleCount;i++)
	{
		if (nozzleNo == nozzleInfo[i].nozzleNo)
		{
			index = i;
			break;
		}
	}
	if (index < 0)
	{
		return -1;
	}
	NET_DVR_JPEGPARA jpegPara;
	jpegPara.wPicQuality = 0;
	jpegPara.wPicSize = 0xFF; //��ǰ�����ֱ��ʣ�
	DWORD x = 0;
	LPDWORD retPicSize = &x;
	write_log_file("snap.txt", MAX_FILE_SIZE, "begin", 5, 3);
	NET_DVR_CaptureJPEGPicture_NEW(nvrInfo.m_lServerID, nozzleInfo[index].videoChan, &jpegPara, pBuffer, MAX_PIC_LENTH, retPicSize);
	int lenth = *retPicSize;
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "ͼƬ����:");
	_itoa(lenth, debugInfo + strlen(debugInfo), 10);
	write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	char *p1 = pBuffer;
	unsigned char *p = (unsigned char *)p1;
	const unsigned char *pp = (const unsigned char *)p;

	struct jpeg_decompress_struct cinfo;//JPEGͼ���ڽ�������У�ʹ��jpeg_decompress_struct���͵Ľṹ������ʾ��ͼ���������Ϣ���洢�ڽṹ����
	struct jpeg_error_mgr jerr;//����һ����׼�Ĵ���ṹ�壬һ��������ִ���ͻ����exit()�����˳�����

	cinfo.err = jpeg_std_error(&jerr);//�󶨴�����ṹ����
	jpeg_create_decompress(&cinfo);//��ʼ��cinfo�ṹ
								   //jpeg_stdio_src()
	jpeg_mem_src(&cinfo, pp, lenth);//ָ����ѹ������Դ
	jpeg_read_header(&cinfo, TRUE);//��ȡ�ļ���Ϣ
	jpeg_start_decompress(&cinfo);//��ʼ��ѹ��
	unsigned long width = cinfo.output_width;//ͼ����
	unsigned long height = cinfo.output_height;//ͼ��߶�
	unsigned short depth = cinfo.output_components;//ͼ�����
												  
	unsigned char *src_buff;//���ڴ�ȡ����֮���λͼ����(RGB��ʽ)
	src_buff = (unsigned char *)malloc(width * height * depth);//����λͼ���ݿռ�
	memset(src_buff, 0, sizeof(unsigned char) * width * height * depth);//��0

																		//JSAMPARRAY buffer[1];//���ڴ�ȡһ������
																		//JSAMPARRAY buffer = (JSAMPARRAY)malloc(width*depth);
	JSAMPARRAY buffer;
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width*depth, 1);//����һ�����ݿռ�

	unsigned char *point = src_buff;
	while (cinfo.output_scanline < height)//���ж�ȡλͼ����
	{
		jpeg_read_scanlines(&cinfo, buffer, 1);    //��ȡһ��jpgͼ�����ݵ�buffer
		memcpy(point, *buffer, width*depth);    //��buffer�е��������и�src_buff
		point += width * depth;            //ָ��ƫ��һ��
	}
	memset(&carOutCache, 0, sizeof(carOutCache));
	carOutCache.nPicHeight = height;
	carOutCache.nPicType = 0;
	carOutCache.nPicWidth = width;
	carOutCache.nVideoChannel = nozzleInfo[index].videoChan;
	memcpy(carOutCache.pic, pBuffer, lenth);

	int licIndex = 0;
	TH_SetImageFormat(ImageFormatRGB, false, false, &th_PlateIDCfg);
	int nCarNum = 2;
	const unsigned char * src = (const unsigned char *)src_buff;
	for (int i = 0;i<nozzleInfo[index].areaCount;i++)
	{
		TH_RecogImage(src, width, height, recogResult, &nCarNum, &nozzleInfo[index].areas[i].th_rect, &th_PlateIDCfg);
		if (nCarNum > 0)
		{
			carOutCache.nLicenseCount += nCarNum;
			for (int j = 0; j < nCarNum; j++)
			{
				memset(debugInfo, 0, sizeof(debugInfo));
				strcpy(debugInfo, "����:");
				memcpy(debugInfo + strlen(debugInfo), recogResult[j].license, strlen(recogResult[j].license));
				write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
				
				memcpy(carOutCache.license[licIndex +j].license, recogResult[j].license, strlen(recogResult[j].license));
				memcpy(carOutCache.license[licIndex + j].color, recogResult[j].color, 8);
				carOutCache.license[licIndex + j].nCarColor = recogResult[j].nCarColor;
				carOutCache.license[licIndex + j].nCarLogo = recogResult[j].nCarLogo;
				carOutCache.license[licIndex + j].nSubCarLogo = recogResult[j].nCarType;
				carOutCache.license[licIndex + j].nCarModel = recogResult[j].nCarModel;
				carOutCache.license[licIndex + j].nColor = recogResult[j].nColor;
				carOutCache.license[licIndex + j].nConfidence = recogResult[j].nConfidence;
				carOutCache.license[licIndex + j].nAreaNo = nozzleInfo[index].areas[i].areaNo;
				carOutCache.license[licIndex + j].nType = recogResult[j].nType;
			}
			licIndex += nCarNum;
		}
	}
	memcpy(carInfo, &carOutCache, sizeof(carOutCache));
	jpeg_finish_decompress(&cinfo);//��ѹ�����
	jpeg_destroy_decompress(&cinfo);// �ͷ���Դ
	free(src_buff);//�ͷ���Դ
	return 0;
}
SPLATE_API int SP_TestAPI()
{
	PostMessage(HWND_BROADCAST, WM_CARDATA, 0, 0);
	return 0;
}

int SwithNextArea(void)
{
	nSwithFlag = 0;
	DWORD pUser = 0;
	
	int tempIndex = nCurAreaIndex;
	int next = nCurAreaIndex + 1;
	if (next == nAreaCount)
		next = 0;
	/*if (++nCurAreaIndex == nAreaCount)
		nCurAreaIndex = 0;*/
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "NowAreaID��");
	_itoa(areaInfo[tempIndex].areaNo, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), " video��");
	_itoa(areaInfo[tempIndex].videoChanNo, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), " NextAreaID:");
	_itoa(areaInfo[next].areaNo, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), " video��");
	_itoa(areaInfo[next].videoChanNo, debugInfo + strlen(debugInfo), 10);
	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),3);
	if (areaInfo[tempIndex].videoChanNo == areaInfo[next].videoChanNo)
	{
		bSwitchComplete = true;
		nCurAreaIndex = next;
		write_log_file("Debug.txt", MAX_FILE_SIZE, "do not switch", 13,3);
		return 0;
	}
	else
	{
		write_log_file("Debug.txt", MAX_FILE_SIZE, "begin switch", 12,3);
		
		//�ͷ�ʶ���
		//TH_UninitPlateIDSDK(&th_PlateIDCfg);
		
		write_log_file("Debug.txt", MAX_FILE_SIZE, "begin change channel", 20,3);
		//ֹͣԤ��
		//NET_DVR_StopRealPlay(nvrInfo.m_lPlayHandle);
		write_log_file("Debug.txt", MAX_FILE_SIZE, "Stoped RealPlay", 15,3);
		previewInfo.lChannel = areaInfo[next].videoChanNo;
		nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, RealDataCallBack, nullptr);
		nCurAreaIndex = next;
		write_log_file("Debug.txt", MAX_FILE_SIZE, "end switch", 10,3);
	}
	return 0;

}

void CALLBACK DecCBFun(long nPort, char *pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2)
{
	//write_log_file("DecCBFun.txt", MAX_FILE_SIZE, "DecCBFun IN", strlen("DecCBFun IN"), 3);
	/*if (!bSwitchComplete)
	{
		write_log_file("Debug.txt", MAX_FILE_SIZE, "in DecCBFun switch not done", strlen("in DecCBFun switch not done"), 3);
		return;
	}*/
	if (nLogLevel >= 4)
	{
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "���");
		_itoa(pFrameInfo->nWidth, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " �߶�");
		_itoa(pFrameInfo->nHeight, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " ��Ƶ��ʽ");
		_itoa(pFrameInfo->nType, debugInfo + strlen(debugInfo), 10);
		write_log_file("Callback.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),4);
	}
	long lFrameType = pFrameInfo->nType;
	
	if (lFrameType == T_YV12)
	{
		memset(&recogResult, 0, sizeof(recogResult));
		nCarNum = 1;
		unsigned char * p = (unsigned char *)pBuf;
		const unsigned char *pp = (const unsigned char *)p;
		//TH_PlateIDResult recogResult[6];
		write_log_file("Debug.txt", MAX_FILE_SIZE, "begin recog", strlen("begin recog"), 3);
		int ret = TH_RecogImage(pp, pFrameInfo->nWidth, pFrameInfo->nHeight, recogResult, &nCarNum, &areaInfo[nCurAreaIndex].th_rect, &th_PlateIDCfg);
		
		if (nCarNum > 0)
		{
			for (int i =0;i<nCarNum;i++)
			{
				if (strlen(recogResult[i].license) < 5 )
				{
					continue;
				}
				memset(debugInfo, 0, sizeof(debugInfo));
				strcpy(debugInfo, "��ǰʶ������");
				memcpy(debugInfo+strlen(debugInfo), recogResult[i].license, strlen(recogResult[i].license));
				strcpy(debugInfo + strlen(debugInfo), "��ǰʶ������");
				_itoa(areaInfo[nCurAreaIndex].areaNo, debugInfo + strlen(debugInfo), 10);
				strcpy(debugInfo + strlen(debugInfo), "  ʶ�����½Ǳ꣺");
				_itoa(nCurAreaIndex, debugInfo + strlen(debugInfo), 10);
				strcpy(debugInfo + strlen(debugInfo), "  �������Ŷȣ�");
				_itoa(recogResult[i].nConfidence, debugInfo + strlen(debugInfo), 10);
				write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),3);

				if (recogResult[i].nConfidence > tempCarOut.nConfidence &&recogResult[i].nConfidence >75
					&& strcmp(recogResult[i].license,tempCarOut.license) != 0)
				{
					write_log_file("Debug.txt", MAX_FILE_SIZE, "replace result", strlen("replace result"), 3);
					//memcpy(lastLicense[nCurAreaIndex], recogResult[i].license, strlen(recogResult[i].license));
					memcpy(tempCarOut.license, recogResult[i].license, strlen(recogResult[i].license));
					memcpy(tempCarOut.color, recogResult[i].color, 8);
					memcpy(tempCarOut.pic, pBuf, nSize);
					tempCarOut.nCarColor = recogResult[i].nCarColor;
					tempCarOut.nCarLogo = recogResult[i].nCarLogo;
					tempCarOut.nSubCarLogo = recogResult[i].nCarType;
					tempCarOut.nCarModel = recogResult[i].nCarModel;
					tempCarOut.nColor = recogResult[i].nColor;
					tempCarOut.nConfidence = recogResult[i].nConfidence;
					tempCarOut.nPicLenth = nSize;
					tempCarOut.nVideoChannel = areaInfo[nCurAreaIndex].videoChanNo;
					tempCarOut.nAreaNo = areaInfo[nCurAreaIndex].areaNo;
					tempCarOut.nPicType = T_YV12;
					tempCarOut.nType = recogResult[i].nType;
					tempCarOut.nPicWidth = pFrameInfo->nWidth;
					tempCarOut.nPicHeight = pFrameInfo->nHeight;
				}
			}
			
		}
		calc++;
		if (calc > nSwitchCount)
		{
			bSwitchComplete = false;
			calc = 0;
			if (tempCarOut.nConfidence > 75 && strcmp(lastLicense[nCurAreaIndex], tempCarOut.license) != 0)
			//if (tempCarOut.nConfidence > 75)
			{
				memcpy(lastLicense[nCurAreaIndex], tempCarOut.license, strlen(tempCarOut.license));
				memcpy(&carInfoOut[nCurPutIndex], &tempCarOut, sizeof(tempCarOut));
				write_log_file("Debug.txt", MAX_FILE_SIZE, "post license massage", strlen("post license massage"), 3);
				PostMessage(HWND_BROADCAST, WM_CARDATA, 0, 0);
				write_log_file("Debug.txt", MAX_FILE_SIZE, "post license massage done", strlen("post license massage done"), 3);
				if (++nCurPutIndex == MAX_CAR_COUNT)
					nCurPutIndex = 0;
				
				if (++nCurCarCount > MAX_CAR_COUNT)
				{
					nCurCarCount = 0;
					write_log_file("Error.txt", MAX_FILE_SIZE, "δ��ȡ�����������г��ȣ�������0", strlen("δ��ȡ�����������г��ȣ�������0"), 1);
				}
			}
			memset(&tempCarOut, 0, sizeof(tempCarOut));
			SwithNextArea();
		}
	}
	else
	{
		write_log_file("Error.txt", MAX_FILE_SIZE, "error midea type", 16,1);
	}
	

}
void CALLBACK RealDataCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{
	DWORD dRet;
	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:    //ϵͳͷ
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "RealDataCallBack-> NET_DVR_SYSHEAD dwBufSize:");
		_itoa(dwBufSize, debugInfo + strlen(debugInfo), 10);
		write_log_file("Callback.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),4);
		if (nPort < 0)
		{
			if (!PlayM4_GetPort(&nPort)) //��ȡ���ſ�δʹ�õ�ͨ����
			{
				break;
			}
		}
		//nPort = -1;
		
		if (dwBufSize > 0)
		{
			
			bSwitchComplete = true;
			if (!PlayM4_OpenStream(nPort, pBuffer, dwBufSize, 1024 * 1024))
			{
				dRet = PlayM4_GetLastError(nPort);
				break;
			}
			//���ý���ص����� ֻ���벻��ʾ
			if (!PlayM4_SetDecCallBack(nPort, DecCBFun))
			{
				dRet = PlayM4_GetLastError(nPort);
				break;
			}



			//����Ƶ����
			if (!PlayM4_Play(nPort, nullptr))
			{
				dRet = PlayM4_GetLastError(nPort);
				break;
			}
			//bSwitchComplete = true;

		}

		break;

	case NET_DVR_STREAMDATA:   //��������
		
		if (nLogLevel >= 4)
		{
			memset(debugInfo, 0, sizeof(debugInfo));
			strcpy(debugInfo, "RealDataCallBack-> NET_DVR_STREAMDATA dwBufSize:");
			_itoa(dwBufSize, debugInfo + strlen(debugInfo), 10);
			write_log_file("Callback.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),4);
		}
		if (dwBufSize > 0 && nPort != -1 && bSwitchComplete)
		{
			write_log_file("RealDataCallBack.txt", MAX_FILE_SIZE, "in", 2, 3);
			if (nLogLevel >= 4)
			{
				memset(debugInfo, 0, sizeof(debugInfo));
				strcpy(debugInfo, "RealDataCallBack-> PlayM4_InputData");
				write_log_file("Callback.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),4);
			}
			BOOL inData = PlayM4_InputData(nPort, pBuffer, dwBufSize);
		
			//write_log_file("play.txt", MAX_FILE_SIZE, "1", 1, 3);
			while (!inData)
			{
				Sleep(10);
				inData = PlayM4_InputData(nPort, pBuffer, dwBufSize);
				//write_log_file("play.txt", MAX_FILE_SIZE, "2", 1, 3);
			}
			//if (++nframeCount > nSwitchCount)
			//{
			//	nframeCount = 0;
			//	bSwitchComplete = false;
			//	if (tempCarOut.nConfidence > 75 && strcmp(lastLicense[nCurAreaIndex], tempCarOut.license) != 0)
			//		//if (tempCarOut.nConfidence > 75)
			//	{
			//		memcpy(lastLicense[nCurAreaIndex], tempCarOut.license, strlen(tempCarOut.license));
			//		memcpy(&carInfoOut[nCurPutIndex], &tempCarOut, sizeof(tempCarOut));
			//		write_log_file("Debug.txt", MAX_FILE_SIZE, "post license massage", strlen("post license massage"), 3);
			//		PostMessage(HWND_BROADCAST, WM_CARDATA, 0, 0);
			//		write_log_file("Debug.txt", MAX_FILE_SIZE, "post license massage done", strlen("post license massage done"), 3);
			//		if (++nCurPutIndex == MAX_CAR_COUNT)
			//			nCurPutIndex = 0;

			//		if (++nCurCarCount > MAX_CAR_COUNT)
			//		{
			//			nCurCarCount = 0;
			//			write_log_file("Error.txt", MAX_FILE_SIZE, "δ��ȡ�����������г��ȣ�������0", strlen("δ��ȡ�����������г��ȣ�������0"), 1);
			//		}
			//	}
			//	memset(&tempCarOut, 0, sizeof(tempCarOut));
			//	SwithNextArea();
			//}
		}
		break;
	}
	
}


