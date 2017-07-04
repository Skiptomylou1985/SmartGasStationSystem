// SPlate.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "SPlate.h"
#include <process.h>
#include <tchar.h>
#include "jpeglib.h"

//硬盘录像机相关
NET_DVR_DEVICEINFO_V30 deviceInfo;
NET_DVR_PREVIEWINFO previewInfo;
struNVRInfo nvrInfo;
LONG testBufferSize ;
LONG callBackNum;
NET_DVR_USER_LOGIN_INFO loginInfo_hkcn;
NET_DVR_DEVICEINFO_V40 deviceInfo_hkcn;
NET_ITS_PLATE_RESULT struItsPlateResult;
TH_PlateIDCfg th_PlateIDCfg ;
//TH_PlateIDCfg th_PlateIDCfg_bak;
TH_PlateIDResult recogResult[6];
int nCarNum;
LONG nPort = -1;


int nAlgStatus = 0;
int nCurGetIndex = 0;
int nCurPutIndex = 0;
struSingleCarInfoOut carInfoOut[MAX_CAR_COUNT];
struSingleCarInfoOut tempCarOut;
struMultiCarInfoOut carOutCache;
unsigned char *videoChan [MAX_VIDEO_CHANNEL_COUNT];
TH_PlateIDCfg th_PlateCfg[MAX_VIDEO_CHANNEL_COUNT];
struPlayInfo playInfo[MAX_VIDEO_CHANNEL_COUNT];
struAreaInfo areaInfo[MAX_AREA_COUNT];
struNozzleInfo nozzleInfo[MAX_NOZZLE_COUNT];
struVideoInfo videoInfo[MAX_VIDEO_CHANNEL_COUNT];
struSingleCarInfoOut areaCar[MAX_AREA_COUNT];
int nAreaCount = 0;
int nNozzleCount = 0;
int nVideoChanCount = 0;
int nLogLevel = 3;
int nCurCarCount = 0;
int nCurAreaIndex= 0;
int nDefaultStratChan = 33;
int nDefaultImageWidth = 1920;
int nDefaultImageHeight = 1080;
char debugInfo[256] ;
char debugInfoThread[256];
char logFileName[32];
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
			write_log_file("Error.txt", MAX_FILE_SIZE, "重启视频切换", strlen("重启视频切换"), 1);
			nSwithFlag = 0;
		}
		Sleep(1000);
	}
}
SPLATE_API int SP_InitRunParam(unsigned char *pArea, int areaCount)
{
	memset(&tempCarOut, 0, sizeof(tempCarOut));
	if (areaCount > MAX_AREA_COUNT)
	{
		return INVALID_AREA_COUNT;
	}
	memcpy(areaInfo, pArea, areaCount *sizeof(struAreaInfo));
	nAreaCount = areaCount;
	for (int i = 0; i < nAreaCount; i++)
	{
		lastLicense[i] = (char *)malloc(16);
		areaInfo[i].videoChanNo += 33;

		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "index：");
		_itoa(i, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "AreaID：");
		_itoa(areaInfo[i].areaNo, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " video：");
		_itoa(areaInfo[i].videoChanNo, debugInfo + strlen(debugInfo), 10);
		write_log_file("license.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		
	}
	return SUCCESS;
}
SPLATE_API int SP_InitRunParam_Nozzle(unsigned char *pNozzleInfo, int nozzleCount)
{
	memset(&tempCarOut, 0, sizeof(tempCarOut));
	if (nozzleCount > MAX_NOZZLE_COUNT)
	{
		return INVALID_NOZZLE_COUNT;
	}
	memcpy(nozzleInfo, pNozzleInfo, nozzleCount * sizeof(struNozzleInfo));
	nNozzleCount = nozzleCount;
	for (int i = 0; i < nNozzleCount; i++)
	{
		nozzleInfo[i].videoChan += struIPPARACFG.dwStartDChan;

		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "index：");
		_itoa(i, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "nozzleNo：");
		_itoa(nozzleInfo[i].nozzleNo, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "areaCount：");
		_itoa(nozzleInfo[i].areaCount, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " video：");
		_itoa(nozzleInfo[i].videoChan, debugInfo + strlen(debugInfo), 10);
		write_log_file("license.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);

	}
	return SUCCESS;
}
SPLATE_API int SP_InitRunParam_Video(unsigned char *pVideoInfo, int videoCount)
{
	if (videoCount > MAX_VIDEO_CHANNEL_COUNT)
	{
		return INVALID_VIDEO_COUNT;
	}
	memcpy(videoInfo, pVideoInfo, videoCount * sizeof(struVideoInfo));
	nVideoChanCount = videoCount;
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "SP_InitRunParam_Video  ");
	strcpy(debugInfo + strlen(debugInfo), "videoCount：");
	_itoa(videoCount, debugInfo + strlen(debugInfo), 10);
	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	for (int i = 0; i < nVideoChanCount; i++)
	{
		videoInfo[i].nChanNo += nDefaultStratChan;


		th_PlateCfg[i].bMovingImage = 1;
		th_PlateCfg[i].bOutputSingleFrame = 1;
		th_PlateCfg[i].nFastMemorySize = 16000;
		th_PlateCfg[i].pFastMemory = (unsigned char *)malloc(16000);
		th_PlateCfg[i].nMemorySize = 100000000;
		th_PlateCfg[i].pMemory = (unsigned char *)malloc(100000000);
		th_PlateCfg[i].nMaxPlateWidth = 400;
		th_PlateCfg[i].nMinPlateWidth = 60;
		th_PlateCfg[i].bUTF8 = 0;
		th_PlateCfg[i].bShadow = 1;
		th_PlateCfg[i].bCarLogo = 1;
		th_PlateCfg[i].bLeanCorrection = 1;
		th_PlateCfg[i].bCarModel = 1;
		th_PlateCfg[i].nMaxImageWidth = nDefaultImageWidth;
		th_PlateCfg[i].nMaxImageHeight = nDefaultImageHeight;

		

		playInfo[i].nPort = -1;
		playInfo[i].nVideoChan = videoInfo[i].nChanNo;
		playInfo[i].previewInfo.dwDisplayBufNum = 15;
		playInfo[i].previewInfo.bBlocked = false;
		playInfo[i].previewInfo.dwLinkMode = 0;
		playInfo[i].previewInfo.lChannel = videoInfo[i].nChanNo;


		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo + strlen(debugInfo), "videoNo：");
		_itoa(videoInfo[i].nChanNo, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " videoType：");
		_itoa(videoInfo[i].nVideoType, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " AreaCount：");
		_itoa(videoInfo[i].nAreaCount, debugInfo + strlen(debugInfo), 10);
		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
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
	nDefaultStratChan = struIPPARACFG.dwStartDChan;
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
	HWND pUser = nullptr;//用户数据
	//if (nvrInfo.m_lPlayHandle > -1)
	//{
	//	NET_DVR_StopRealPlay(nvrInfo.m_lPlayHandle);
	//}
	LONG lplayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, NULL, pUser);
	if (lplayHandle < 0)
	{
		return NET_DVR_GetLastError();
	}
	return lplayHandle;
}
//SPLATE_API int SP_BeginRecog(HWND hPlayHandle)
//{
//	isRecog = true;
//	//ThreadSwith = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadKeepSwitch, NULL, 0, NULL);
//	previewInfo.hPlayWnd = nullptr;
//	previewInfo.lChannel = areaInfo[nCurAreaIndex].videoChanNo;
//	if (hPlayHandle != NULL)
//	{
//		previewInfo.hPlayWnd = hPlayHandle;
//	}
//	previewInfo.dwStreamType = 0;//码流类型：0-主码流，1-子码流，2-码流3，3-码流4，以此类推
//	previewInfo.dwLinkMode = 0;//连接方式：0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP 
//	previewInfo.bBlocked = false; //0- 非阻塞取流，1- 阻塞取流
//	previewInfo.dwDisplayBufNum = 15;
//	HWND pUser = nullptr;//用户数据
//	nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, RealDataCallBack, pUser);
//	
//	memset(debugInfo, 0, sizeof(debugInfo));
//	strcpy(debugInfo, "NET_DVR_RealPlay_V40 return value:");
//	_itoa(nvrInfo.m_lPlayHandle, debugInfo + strlen(debugInfo), 10);
//	strcpy(debugInfo+strlen(debugInfo), " 通道号:");
//	_itoa(areaInfo[nCurAreaIndex].videoChanNo, debugInfo + strlen(debugInfo), 10);
//	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),3);
//	if (nvrInfo.m_lPlayHandle < 0)
//	{
//		return NET_DVR_GetLastError();
//	}
//	return nvrInfo.m_lPlayHandle;
//
//}
SPLATE_API int SP_BeginRecog()
{
	for (int i=0;i<nVideoChanCount;i++)
	{
		playInfo[i].lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &playInfo[i].previewInfo, RealDataCallBack_MultiChan, nullptr);
	}
	return SUCCESS;
}
SPLATE_API int SP_InitAlg(TH_PlateIDCfg *th_plateIDCfg, int lenth)
{
	for (int i = 0; i < nVideoChanCount; i++)
	{
		int ret = TH_InitPlateIDSDK(&th_PlateCfg[i]);
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "初始化算法序号:");
		_itoa(i, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " 返回值:");
		_itoa(ret, debugInfo + strlen(debugInfo), 10);
		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		TH_SetImageFormat(ImageFormatYV12, false, false, &th_PlateCfg[i]);
		TH_SetRecogThreshold(5, 2, &th_PlateCfg[i]);//设置阈值
		
	}
	
	write_log_file("Debug.txt", MAX_FILE_SIZE, "begin initAlg", strlen("begin initAlg"), 3);
	if (lenth != sizeof(TH_PlateIDCfg))
	{
		return INVALID_LENTH;
	}
	memcpy(&th_PlateIDCfg, th_plateIDCfg, lenth);
	nAlgStatus = TH_InitPlateIDSDK(&th_PlateIDCfg);
	if (nAlgStatus == 0)
	{
		write_log_file("Debug.txt", MAX_FILE_SIZE, "TH_InitPlateIDSDK", strlen("TH_InitPlateIDSDK"), 3);
		TH_SetImageFormat(ImageFormatYV12, false, false, &th_PlateIDCfg);
		//TH_SetProvinceOrder("陕", &th_PlateIDCfg);
		TH_SetRecogThreshold(5, 2, &th_PlateIDCfg);//设置阈值 
		//int maxThread = 0;
		//TH_GetKeyMaxThread(&maxThread);
		//memset(debugInfo, 0, sizeof(debugInfo));
		//strcpy(debugInfo, "识别最多路数:");
		//_itoa(maxThread, debugInfo + strlen(debugInfo), 10);
		//write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		write_log_file("Debug.txt", MAX_FILE_SIZE, "TH_SetRecogThreshold", strlen("TH_SetRecogThreshold"), 3);
	}
	else
	{
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "算法初始化失败，返回值:");
		_itoa(nAlgStatus, debugInfo + strlen(debugInfo), 10);
		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		
	}
	
	return nAlgStatus;
}
SPLATE_API int SP_GetCarCount()
{
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "SP_GetCarCount：");
	_itoa(nCurCarCount, debugInfo + strlen(debugInfo), 10);
	write_log_file("PlateDataCallBack.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	return nCurCarCount;
}
SPLATE_API int SP_GetFirstCarInfo(struSingleCarInfoOut *carinfo, int &lenth)
{
	if (nCurCarCount > 0)
	{
		lenth = sizeof(struSingleCarInfoOut);
		memcpy(carinfo, &carInfoOut[nCurGetIndex], sizeof(struSingleCarInfoOut));
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "上位机提取车牌：");
		strcpy(debugInfo + strlen(debugInfo), carInfoOut[nCurGetIndex].license);
		strcpy(debugInfo + strlen(debugInfo), "识别区号：");
		_itoa(carInfoOut[nCurGetIndex].nAreaNo, debugInfo + strlen(debugInfo), 10);
		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		nCurCarCount--;
		if (++nCurGetIndex == MAX_CAR_COUNT)
			nCurGetIndex = 0;
		return SUCCESS;
	}
	return FAIL;
}
SPLATE_API int SP_GetAreaCarInfo(struSingleCarInfoOut *carinfo, int areaNo)
{
	if (areaNo > 0 && areaNo <= MAX_AREA_COUNT)
	{
		memcpy(carinfo, &areaCar[areaNo - 1], sizeof(struSingleCarInfoOut));
		areaCar[areaNo - 1].nConfidence = 0;
		memset(areaCar[areaNo - 1].license, 0, 16);
	}
	else
		return INVALID_AREA_COUNT;
	
}
SPLATE_API int SP_GetCarInfo(struSingleCarInfoOut *carinfo, int carCount,int &lenth)
{
	if (carCount > nCurCarCount || carCount <= 0)
		return INVALID_CAR_COUNT;
	int size = sizeof(struSingleCarInfoOut);
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
	jpegPara.wPicSize = 0xFF; //当前码流分辨率；
	DWORD x = 0;
	LPDWORD retPicSize  = &x;
	write_log_file("snap.txt", MAX_FILE_SIZE, "begin", 5, 3);
	NET_DVR_CaptureJPEGPicture_NEW(nvrInfo.m_lServerID, videoChan, &jpegPara, pBufer, picSize, retPicSize);
	int lenth = *retPicSize;

	memcpy(picBuffer,pBufer, lenth);
	picLenth = lenth;
	write_log_file("snap.txt", MAX_FILE_SIZE, "step 2", 1, 3);
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "图片长度:");
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

	struct jpeg_decompress_struct cinfo;//JPEG图像在解码过程中，使用jpeg_decompress_struct类型的结构体来表示，图像的所有信息都存储在结构体中
	struct jpeg_error_mgr jerr;//定义一个标准的错误结构体，一旦程序出现错误就会调用exit()函数退出进程

	cinfo.err = jpeg_std_error(&jerr);//绑定错误处理结构对象
	jpeg_create_decompress(&cinfo);//初始化cinfo结构
	//jpeg_stdio_src(&cinfo, input_file);
	write_log_file("snap.txt", MAX_FILE_SIZE, "3", 1, 3);
	jpeg_mem_src(&cinfo, pJpegPic, nJpegLenth);//指定解压缩数据源
	jpeg_read_header(&cinfo, TRUE);//获取文件信息
	jpeg_start_decompress(&cinfo);//开始解压缩
	write_log_file("snap.txt", MAX_FILE_SIZE, "4", 1, 3);
	unsigned long width = cinfo.output_width;//图像宽度
	unsigned long height = cinfo.output_height;//图像高度
	unsigned short depth = cinfo.output_components;//图像深度
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "图片宽度:");
	_itoa(width, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), "图片高度:");
	_itoa(height, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), "图片深度:");
	_itoa(depth, debugInfo + strlen(debugInfo), 10);
	write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	unsigned char *src_buff;//用于存取解码之后的位图数据(RGB格式)
	src_buff = (unsigned char *)malloc(width * height * depth);//分配位图数据空间
	memset(src_buff, 0, sizeof(unsigned char) * width * height * depth);//清0

	//JSAMPARRAY buffer[1];//用于存取一行数据
	//JSAMPARRAY buffer = (JSAMPARRAY)malloc(width*depth);
	JSAMPARRAY buffer;
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width*depth, 1);//分配一行数据空间
	//unsigned char * buffer = (unsigned char *)malloc(width*depth);
	write_log_file("snap.txt", MAX_FILE_SIZE, "5", 1, 3);
	unsigned char *point = src_buff;
	while (cinfo.output_scanline < height)//逐行读取位图数据
	{
		jpeg_read_scanlines(&cinfo, buffer, 1);    //读取一行jpg图像数据到buffer
		memcpy(point, *buffer, width*depth);    //将buffer中的数据逐行给src_buff
		point += width * depth;            //指针偏移一行
	}
	
	TH_SetImageFormat(ImageFormatRGB, false, false, &th_PlateIDCfg);
	int nCarNum = 1;
	const unsigned char * pp = (const unsigned char *)src_buff;


	TH_RecogImage(pp, width, height, recogResult, &nCarNum,nullptr, &th_PlateIDCfg);
	if (nCarNum > 0)
	{
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "车牌:");
		memcpy(debugInfo+strlen(debugInfo), recogResult[0].license,strlen(recogResult[0].license));
		write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		//write_log_file("snap.txt", MAX_FILE_SIZE, "get license", strlen("get license"), 3);
		memcpy(license, &recogResult[0].license, strlen(recogResult[0].license));
	}
	write_log_file("snap.txt", MAX_FILE_SIZE, "6", 1, 3);
	jpeg_finish_decompress(&cinfo);//解压缩完毕
	jpeg_destroy_decompress(&cinfo);// 释放资源
	free(src_buff);//释放资源
	//fclose(input_file);
	write_log_file("snap.txt", MAX_FILE_SIZE, "7", 1, 3);
	return 0;
}
SPLATE_API int SP_Capture(int areaNo, struSingleCarInfoOut *carinfo)
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
	jpegPara.wPicSize = 0xFF; //当前码流分辨率；
	DWORD x = 0;
	LPDWORD retPicSize = &x;
	write_log_file("snap.txt", MAX_FILE_SIZE, "begin", 5, 3);
	NET_DVR_CaptureJPEGPicture_NEW(nvrInfo.m_lServerID, areaInfo[index].videoChanNo, &jpegPara, pBuffer, MAX_PIC_LENTH, retPicSize);
	int lenth = *retPicSize;

	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "图片长度:");
	_itoa(lenth, debugInfo + strlen(debugInfo), 10);
	write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	if (lenth < 1000)
	{
		return -2;
	}
	char *p1 = pBuffer;
	unsigned char *p = (unsigned char *)p1;
	const unsigned char *pp = (const unsigned char *)p;

	struct jpeg_decompress_struct cinfo;//JPEG图像在解码过程中，使用jpeg_decompress_struct类型的结构体来表示，图像的所有信息都存储在结构体中
	struct jpeg_error_mgr jerr;//定义一个标准的错误结构体，一旦程序出现错误就会调用exit()函数退出进程

	cinfo.err = jpeg_std_error(&jerr);//绑定错误处理结构对象
	jpeg_create_decompress(&cinfo);//初始化cinfo结构
								   //jpeg_stdio_src()
	jpeg_mem_src(&cinfo, pp, lenth);//指定解压缩数据源
	jpeg_read_header(&cinfo, TRUE);//获取文件信息
	jpeg_start_decompress(&cinfo);//开始解压缩
	unsigned long width = cinfo.output_width;//图像宽度
	unsigned long height = cinfo.output_height;//图像高度
	unsigned short depth = cinfo.output_components;//图像深度
	//memset(debugInfo, 0, sizeof(debugInfo));
	//strcpy(debugInfo, "图片大小:");
	//_itoa(lenth, debugInfo + strlen(debugInfo), 10);
	//strcpy(debugInfo, "图片宽度:");
	//_itoa(width, debugInfo + strlen(debugInfo), 10);
	//strcpy(debugInfo, "图片高度:");
	//_itoa(height, debugInfo + strlen(debugInfo), 10);
	//strcpy(debugInfo, "图片深度:");
	//_itoa(depth, debugInfo + strlen(debugInfo), 10);
	//write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	unsigned char *src_buff;//用于存取解码之后的位图数据(RGB格式)
	src_buff = (unsigned char *)malloc(width * height * depth);//分配位图数据空间
	memset(src_buff, 0, sizeof(unsigned char) * width * height * depth);//清0

																		//JSAMPARRAY buffer[1];//用于存取一行数据
																		//JSAMPARRAY buffer = (JSAMPARRAY)malloc(width*depth);
	JSAMPARRAY buffer;
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width*depth, 1);//分配一行数据空间
				
	unsigned char *point = src_buff;
	while (cinfo.output_scanline < height)//逐行读取位图数据
	{
		jpeg_read_scanlines(&cinfo, buffer, 1);    //读取一行jpg图像数据到buffer
		memcpy(point, *buffer, width*depth);    //将buffer中的数据逐行给src_buff
		point += width * depth;            //指针偏移一行
	}

	TH_SetImageFormat(ImageFormatRGB, false, false, &th_PlateIDCfg);
	int nCarNum = 1;
	const unsigned char * src = (const unsigned char *)src_buff;
	TH_RecogImage(src, width, height, recogResult, &nCarNum, &areaInfo[index].th_rect, &th_PlateIDCfg);
	if (nCarNum > 0)
	{
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "车牌:");
		memcpy(debugInfo + strlen(debugInfo), recogResult[0].license, strlen(recogResult[0].license));
		write_log_file("snap.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		memset(&tempCarOut, 0, sizeof(tempCarOut));
		memcpy(tempCarOut.license, recogResult[0].license, strlen(recogResult[0].license));
		memcpy(tempCarOut.color, recogResult[0].color, 8);
//		memcpy(tempCarOut.pic, pBuffer, lenth);
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
	jpeg_finish_decompress(&cinfo);//解压缩完毕
	jpeg_destroy_decompress(&cinfo);// 释放资源
	free(src_buff);//释放资源
	return 0;

}
SPLATE_API int SP_Capture_V2(int nozzleNo, struMultiCarInfoOut *carInfo)
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
	jpegPara.wPicSize = 0xFF; //当前码流分辨率；
	DWORD x = 0;
	LPDWORD retPicSize = &x;
	write_log_file("snap.txt", MAX_FILE_SIZE, "begin", 5, 3);
	NET_DVR_CaptureJPEGPicture_NEW(nvrInfo.m_lServerID, nozzleInfo[index].videoChan, &jpegPara, pBuffer, MAX_PIC_LENTH, retPicSize);
	int lenth = *retPicSize;
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "抓拍通道:");
	_itoa(nozzleInfo[index].videoChan, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), "图片长度:");
	_itoa(lenth, debugInfo + strlen(debugInfo), 10);
	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	if (lenth < 1000)
	{
		return -2;
	}
	char *p1 = pBuffer;
	unsigned char *p = (unsigned char *)p1;
	const unsigned char *pp = (const unsigned char *)p;

	struct jpeg_decompress_struct cinfo;//JPEG图像在解码过程中，使用jpeg_decompress_struct类型的结构体来表示，图像的所有信息都存储在结构体中
	struct jpeg_error_mgr jerr;//定义一个标准的错误结构体，一旦程序出现错误就会调用exit()函数退出进程

	cinfo.err = jpeg_std_error(&jerr);//绑定错误处理结构对象
	jpeg_create_decompress(&cinfo);//初始化cinfo结构
								   //jpeg_stdio_src()
	jpeg_mem_src(&cinfo, pp, lenth);//指定解压缩数据源
	jpeg_read_header(&cinfo, TRUE);//获取文件信息
	jpeg_start_decompress(&cinfo);//开始解压缩
	unsigned long width = cinfo.output_width;//图像宽度
	unsigned long height = cinfo.output_height;//图像高度
	unsigned short depth = cinfo.output_components;//图像深度
												  
	unsigned char *src_buff;//用于存取解码之后的位图数据(RGB格式)
	src_buff = (unsigned char *)malloc(width * height * depth);//分配位图数据空间
	memset(src_buff, 0, sizeof(unsigned char) * width * height * depth);//清0

																		//JSAMPARRAY buffer[1];//用于存取一行数据
																		//JSAMPARRAY buffer = (JSAMPARRAY)malloc(width*depth);
	JSAMPARRAY buffer;
	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width*depth, 1);//分配一行数据空间

	unsigned char *point = src_buff;
	while (cinfo.output_scanline < height)//逐行读取位图数据
	{
		jpeg_read_scanlines(&cinfo, buffer, 1);    //读取一行jpg图像数据到buffer
		memcpy(point, *buffer, width*depth);    //将buffer中的数据逐行给src_buff
		point += width * depth;            //指针偏移一行
	}
	write_log_file("snap.txt", MAX_FILE_SIZE, "转码完毕", strlen("转码完毕"), 3);

	memset(&carOutCache, 0, sizeof(carOutCache));
	carOutCache.nPicHeight = height;
	carOutCache.nPicType = 0;
	carOutCache.nPicWidth = width;
	carOutCache.nVideoChannel = nozzleInfo[index].videoChan;
	memcpy(carOutCache.pic, pBuffer, lenth);

	int licIndex = 0;
	TH_SetImageFormat(ImageFormatRGB, false, false, &th_PlateIDCfg);
	int nCarNum = 1;
	const unsigned char * src = (const unsigned char *)src_buff;
	for (int i = 0;i<nozzleInfo[index].areaCount;i++)
	{
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "识别区:");
		_itoa(nozzleInfo[index].areas[i].areaNo, debugInfo + strlen(debugInfo), 10);
		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		nCarNum = 1;
		TH_RecogImage(src, width, height, recogResult, &nCarNum, &nozzleInfo[index].areas[i].th_rect, &th_PlateIDCfg);

		if (nCarNum > 0)
		{
			
			
			for (int j = 0; j < nCarNum; j++)
			{
				memset(debugInfo, 0, sizeof(debugInfo));
				strcpy(debugInfo, "车牌:");
				memcpy(debugInfo + strlen(debugInfo), recogResult[j].license, strlen(recogResult[j].license));
				write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
				
				if (strlen(recogResult[j].license) < 5 || recogResult[j].nConfidence < 70)
				{
					write_log_file("Debug.txt", MAX_FILE_SIZE, "无效车牌", strlen("无效车牌"), 3);
					continue;
				}
				memcpy(carOutCache.license[licIndex].license, recogResult[j].license, strlen(recogResult[j].license));
				memcpy(carOutCache.license[licIndex].color, recogResult[j].color, 8);
				carOutCache.license[licIndex].nCarColor = recogResult[j].nCarColor;
				carOutCache.license[licIndex].nCarLogo = recogResult[j].nCarLogo;
				carOutCache.license[licIndex].nSubCarLogo = recogResult[j].nCarType;
				carOutCache.license[licIndex].nCarModel = recogResult[j].nCarModel;
				carOutCache.license[licIndex].nColor = recogResult[j].nColor;
				carOutCache.license[licIndex].nConfidence = recogResult[j].nConfidence;
				carOutCache.license[licIndex].nAreaNo = nozzleInfo[index].areas[i].areaNo;
				carOutCache.license[licIndex].nType = recogResult[j].nType;
				carOutCache.nLicenseCount += 1;
				licIndex += 1;
			}
			
		}
	}
	
	memcpy(carInfo, &carOutCache, sizeof(carOutCache));
	jpeg_finish_decompress(&cinfo);//解压缩完毕
	jpeg_destroy_decompress(&cinfo);// 释放资源
	free(src_buff);//释放资源
	return 0;
}
SPLATE_API int SP_TestAPI()
{
	PostMessage(HWND_BROADCAST, WM_AREACAR, 1, 2);
	return 0;
}

//海康超脑NVR相关接口
SPLATE_API int SP_InitNVR_HKCN(char *IpAddress, LONG nPort, char *sAdmin, char *sPassword)
{
	bool ret = NET_DVR_Init();
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);
	if (!ret)
	{
		return NET_DVR_GetLastError();
	}
	memcpy(&loginInfo_hkcn.sDeviceAddress, IpAddress, strlen(IpAddress));
	memcpy(&loginInfo_hkcn.sUserName, sAdmin, strlen(sAdmin));
	memcpy(&loginInfo_hkcn.sPassword, sPassword, strlen(sPassword));
	loginInfo_hkcn.wPort = nPort;
	nvrInfo.m_lServerID = NET_DVR_Login_V40(&loginInfo_hkcn, &deviceInfo_hkcn);
	//NET_DVR_GET_IPPARACFG(nvrInfo.m_lServerID, NET_DVR_GET_IPPARACFG_V40,0,)
	if (nvrInfo.m_lServerID < 0)
	{
		return NET_DVR_GetLastError();
	}

	NET_DVR_SetDVRMessageCallBack_V31((MSGCallBack_V31)PlateDataCallBack, nullptr);
	NET_DVR_SETUPALARM_PARAM alarm_Param = { 0 };
	alarm_Param.dwSize = sizeof(alarm_Param);
	alarm_Param.byAlarmInfoType = 1;
	alarm_Param.byLevel = 0;
	NET_DVR_SetupAlarmChan_V41(nvrInfo.m_lServerID, &alarm_Param);
	//DWORD dwReturn = 0;
	//NET_DVR_GetDVRConfig(nvrInfo.m_lServerID, NET_DVR_GET_IPPARACFG_V40, 0, &struIPPARACFG, sizeof(struIPPARACFG), &dwReturn);
	return SUCCESS;
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
	strcpy(debugInfo, "NowAreaID：");
	_itoa(areaInfo[tempIndex].areaNo, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), " video：");
	_itoa(areaInfo[tempIndex].videoChanNo, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), " NextAreaID:");
	_itoa(areaInfo[next].areaNo, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), " video：");
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
		
		//释放识别库
		//TH_UninitPlateIDSDK(&th_PlateIDCfg);
		
		write_log_file("Debug.txt", MAX_FILE_SIZE, "begin change channel", 20,3);
		//停止预览
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
		strcpy(debugInfo, "宽度");
		_itoa(pFrameInfo->nWidth, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " 高度");
		_itoa(pFrameInfo->nHeight, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " 视频格式");
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
				strcpy(debugInfo, "当前识别结果：");
				memcpy(debugInfo+strlen(debugInfo), recogResult[i].license, strlen(recogResult[i].license));
				strcpy(debugInfo + strlen(debugInfo), "当前识别区域：");
				_itoa(areaInfo[nCurAreaIndex].areaNo, debugInfo + strlen(debugInfo), 10);
				strcpy(debugInfo + strlen(debugInfo), "  识别区下角标：");
				_itoa(nCurAreaIndex, debugInfo + strlen(debugInfo), 10);
				strcpy(debugInfo + strlen(debugInfo), "  车牌置信度：");
				_itoa(recogResult[i].nConfidence, debugInfo + strlen(debugInfo), 10);
				write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),3);

				if (recogResult[i].nConfidence > tempCarOut.nConfidence &&recogResult[i].nConfidence >75
					&& strcmp(recogResult[i].license,tempCarOut.license) != 0)
				{
					write_log_file("Debug.txt", MAX_FILE_SIZE, "replace result", strlen("replace result"), 3);
					//memcpy(lastLicense[nCurAreaIndex], recogResult[i].license, strlen(recogResult[i].license));
					memcpy(tempCarOut.license, recogResult[i].license, strlen(recogResult[i].license));
					memcpy(tempCarOut.color, recogResult[i].color, 8);
//					memcpy(tempCarOut.pic, pBuf, nSize);
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
					write_log_file("Error.txt", MAX_FILE_SIZE, "未提取车辆超过队列长度，长度置0", strlen("未提取车辆超过队列长度，长度置0"), 1);
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
	case NET_DVR_SYSHEAD:    //系统头
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "RealDataCallBack-> NET_DVR_SYSHEAD dwBufSize:");
		_itoa(dwBufSize, debugInfo + strlen(debugInfo), 10);
		write_log_file("Callback.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),4);
		if (nPort < 0)
		{
			if (!PlayM4_GetPort(&nPort)) //获取播放库未使用的通道号
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
			//设置解码回调函数 只解码不显示
			if (!PlayM4_SetDecCallBack(nPort, DecCBFun))
			{
				dRet = PlayM4_GetLastError(nPort);
				break;
			}



			//打开视频解码
			if (!PlayM4_Play(nPort, nullptr))
			{
				dRet = PlayM4_GetLastError(nPort);
				break;
			}
			//bSwitchComplete = true;

		}

		break;

	case NET_DVR_STREAMDATA:   //码流数据
		
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
		}
		break;
	}
	
}
void CALLBACK PlateDataCallBack(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void *pUser)
{
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "PlateDataCallBack lCommand:");
	_itoa(lCommand, debugInfo + strlen(debugInfo), 10);
	write_log_file("PlateDataCallBack.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	int x = 0;
	int y = 0;
	switch (lCommand)
	{
	case COMM_UPLOAD_PLATE_RESULT:
		/*NET_DVR_PLATE_RESULT struPlateResult = { 0 };
		memcpy(&struPlateResult, pAlarmInfo, sizeof(struPlateResult));
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo + strlen(debugInfo), "plate:");
		memcpy(debugInfo + strlen(debugInfo), &struPlateResult.sLicense, strlen(struPlateResult.sLicense));
		strcpy(debugInfo + strlen(debugInfo), " byChanIndex:");
		_itoa(struPlateResult.byChanIndex, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "  wVehicleLogoRecog:");
		_itoa(struPlateResult.wVehicleLogoRecog, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "  byVehicleSubLogoRecog:");
		_itoa(struPlateResult.wVehicleSubLogoRecog, debugInfo + strlen(debugInfo), 10);
		write_log_file("PlateDataCallBack.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 4);*/
		break;
	case  COMM_ITS_PLATE_RESULT:
		memcpy(&struItsPlateResult, pAlarmInfo, sizeof(struItsPlateResult));
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo + strlen(debugInfo), "plate:");
		memcpy(debugInfo + strlen(debugInfo), struItsPlateResult.struPlateInfo.sLicense, strlen(struItsPlateResult.struPlateInfo.sLicense));
		strcpy(debugInfo + strlen(debugInfo), " byChanIndex:");
		_itoa(struItsPlateResult.byChanIndex, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "  wVehicleLogoRecog:");
		_itoa(struItsPlateResult.struVehicleInfo.wVehicleLogoRecog, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "  byVehicleSubLogoRecog:");
		_itoa(struItsPlateResult.struVehicleInfo.byVehicleSubLogoRecog, debugInfo + strlen(debugInfo), 10);
		write_log_file("PlateDataCallBack.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		//int plateLenth = strlen(struItsPlateResult.struPlateInfo.sLicense);
		if (strlen(struItsPlateResult.struPlateInfo.sLicense) > 2)
		{
			memcpy(carInfoOut[nCurPutIndex].license, &struItsPlateResult.struPlateInfo.sLicense[2], strlen(struItsPlateResult.struPlateInfo.sLicense) - 2);
			memcpy(carInfoOut[nCurPutIndex].color, &struItsPlateResult.struPlateInfo.sLicense, 2);
		}
		
		carInfoOut[nCurPutIndex].nCarLogo = struItsPlateResult.struVehicleInfo.byVehicleLogoRecog;
		carInfoOut[nCurPutIndex].nSubCarLogo = struItsPlateResult.struVehicleInfo.byVehicleSubLogoRecog;
		carInfoOut[nCurPutIndex].nCarModel = struItsPlateResult.struVehicleInfo.byVehicleModel;
		carInfoOut[nCurPutIndex].nVideoChannel = struItsPlateResult.byChanIndex;
		//carInfoOut[nCurPutIndex].nAreaNo = 1;
		carInfoOut[nCurPutIndex].nPicHeight = 1080;
		carInfoOut[nCurPutIndex].nPicWidth = 1920;
		x = struItsPlateResult.struPlateInfo.struPlateRect.fX * carInfoOut[nCurPutIndex].nPicWidth;
		y = struItsPlateResult.struPlateInfo.struPlateRect.fY * carInfoOut[nCurPutIndex].nPicHeight;
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo + strlen(debugInfo), "fX:");
		_itoa(x, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " fY:");
		_itoa(y, debugInfo + strlen(debugInfo), 10);
		write_log_file("PlateDataCallBack.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		for (int i = 0; i < nAreaCount; i++)
		{
			if (areaInfo[i].videoChanNo == struItsPlateResult.byChanIndex &&
				areaInfo[i].th_rect.left < x && areaInfo[i].th_rect.right > x &&
				areaInfo[i].th_rect.top < y && areaInfo[i].th_rect.bottom > y)
			{

				carInfoOut[nCurPutIndex].nAreaNo = areaInfo[i].areaNo;
				memset(debugInfo, 0, sizeof(debugInfo));
				strcpy(debugInfo, "match area：");
				_itoa(areaInfo[i].areaNo, debugInfo + strlen(debugInfo), 10);
				write_log_file("PlateDataCallBack.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
				break;
			}
		}
		carInfoOut[nCurPutIndex].nPicLenth = struItsPlateResult.struPicInfo[0].dwDataLen;
		carInfoOut[nCurPutIndex].nPicType = 0; //JPG
		carInfoOut[nCurPutIndex].nPicHeight = 1080;
		carInfoOut[nCurPutIndex].nPicWidth = 1920;
//		memcpy(carInfoOut[nCurPutIndex].pic, struItsPlateResult.struPicInfo[0].pBuffer, struItsPlateResult.struPicInfo[0].dwDataLen);
		PostMessage(HWND_BROADCAST, WM_CARDATA, 0, 0);
		//write_log_file("Debug.txt", MAX_FILE_SIZE, "post license massage done", strlen("post license massage done"), 3);
		if (++nCurPutIndex == MAX_CAR_COUNT)
			nCurPutIndex = 0;

		if (++nCurCarCount > MAX_CAR_COUNT)
		{
			nCurCarCount = 0;
			write_log_file("Error.txt", MAX_FILE_SIZE, "未提取车辆超过队列长度，长度置0", strlen("未提取车辆超过队列长度，长度置0"), 1);
		}
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "nCurCarCount：");
		_itoa(nCurCarCount, debugInfo + strlen(debugInfo), 10);
		write_log_file("PlateDataCallBack.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		break;
	default:
		break;
	}
}
void CALLBACK RealDataCallBack_MultiChan(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{
	int index = -1;
	for (int i=0;i<nVideoChanCount;i++)
	{
		if (playInfo[i].lPlayHandle == lPlayHandle)
		{
			index = i;
			break;
		}
	}
	if (index < 0)
	{
		return;
	}
	DWORD dRet;
	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:    //系统头
		if (playInfo[index].nPort < 0)
		{
			if (!PlayM4_GetPort(&playInfo[index].nPort)) //获取播放库未使用的通道号
			{
				break;
			}
		}
		//nPort = -1;

		if (dwBufSize > 0)
		{

			bSwitchComplete = true;
			if (!PlayM4_OpenStream(playInfo[index].nPort, pBuffer, dwBufSize, 1024 * 1024))
			{
				dRet = PlayM4_GetLastError(playInfo[index].nPort);
				break;
			}
			//设置解码回调函数 只解码不显示
			if (!PlayM4_SetDecCallBack(playInfo[index].nPort, DecCBFun_MultiChan))
			{
				dRet = PlayM4_GetLastError(playInfo[index].nPort);
				break;
			}



			//打开视频解码
			if (!PlayM4_Play(playInfo[index].nPort, nullptr))
			{
				dRet = PlayM4_GetLastError(playInfo[index].nPort);
				break;
			}
			//bSwitchComplete = true;

		}

		break;

	case NET_DVR_STREAMDATA:   //码流数据

		if (nLogLevel >= 4)
		{
			memset(debugInfo, 0, sizeof(debugInfo));
			strcpy(debugInfo, "RealDataCallBack-> NET_DVR_STREAMDATA dwBufSize:");
			_itoa(dwBufSize, debugInfo + strlen(debugInfo), 10);
			write_log_file("Callback.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 4);
			switch (index)
			{
			case 0:
				write_log_file("call0.txt", MAX_FILE_SIZE, "call", 4, 4);
				break;
			case 1:
				write_log_file("call1.txt", MAX_FILE_SIZE, "call", 4, 4);
				break;
			case 2:
				write_log_file("call2.txt", MAX_FILE_SIZE, "call", 4, 4);
				break;
			case 3:
				write_log_file("call3.txt", MAX_FILE_SIZE, "call", 4, 4);
				break;
			default:
				break;
			}
		}
		
		
		
		if (dwBufSize > 0 && playInfo[index].nPort != -1 && bSwitchComplete)
		{
			if (nLogLevel >= 4)
			{
				memset(debugInfo, 0, sizeof(debugInfo));
				strcpy(debugInfo, "RealDataCallBack-> PlayM4_InputData");
				write_log_file("Callback.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 4);
			}
			BOOL inData = PlayM4_InputData(playInfo[index].nPort, pBuffer, dwBufSize);

			//write_log_file("play.txt", MAX_FILE_SIZE, "1", 1, 3);
			while (!inData)
			{
				Sleep(10);
				inData = PlayM4_InputData(playInfo[index].nPort, pBuffer, dwBufSize);
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
			//			write_log_file("Error.txt", MAX_FILE_SIZE, "未提取车辆超过队列长度，长度置0", strlen("未提取车辆超过队列长度，长度置0"), 1);
			//		}
			//	}
			//	memset(&tempCarOut, 0, sizeof(tempCarOut));
			//	SwithNextArea();
			//}
		}
		break;
	}
}
void CALLBACK DecCBFun_MultiChan(long nPort, char *pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2)
{
	int index = -1;
	for (int i=0;i<nVideoChanCount;i++)
	{
		if (nPort == playInfo[i].nPort)
		{
			index = i;
			break;
		}
	}
	
	if (nLogLevel >= 4)
	{
		memset(debugInfoThread, 0, sizeof(debugInfoThread));
		strcpy(debugInfoThread, "nPort");
		_itoa(nPort, debugInfoThread + strlen(debugInfoThread), 10);
		strcpy(debugInfoThread + strlen(debugInfoThread), "宽度");
		_itoa(pFrameInfo->nWidth, debugInfoThread + strlen(debugInfoThread), 10);
		strcpy(debugInfoThread + strlen(debugInfoThread), " 高度");
		_itoa(pFrameInfo->nHeight, debugInfoThread + strlen(debugInfoThread), 10);
		strcpy(debugInfoThread + strlen(debugInfoThread), " 视频格式");
		_itoa(pFrameInfo->nType, debugInfoThread + strlen(debugInfoThread), 10);
		
		switch (index)
		{
		case 0:
			write_log_file("Dec0.txt", MAX_FILE_SIZE, debugInfoThread, strlen(debugInfoThread), 4);
			break;
		case 1:
			write_log_file("Dec1.txt", MAX_FILE_SIZE, debugInfoThread, strlen(debugInfoThread), 4);
			break;
		case 2:
			write_log_file("Dec2.txt", MAX_FILE_SIZE, debugInfoThread, strlen(debugInfoThread), 4);
			break;
		case 3:
			write_log_file("Dec3.txt", MAX_FILE_SIZE, debugInfoThread, strlen(debugInfoThread), 4);
			break;
		default:
			break;
		}
		
	}
	long lFrameType = pFrameInfo->nType;
	if (lFrameType == T_YV12)
	{
		TH_PlateIDResult Result[6];
		nCarNum = 1;
		unsigned char * p = (unsigned char *)pBuf;
		const unsigned char *pp = (const unsigned char *)p;
		//TH_PlateIDResult recogResult[6];
		//write_log_file("plate.txt", MAX_FILE_SIZE, "begin recog", strlen("begin recog"), 3);
		int ret = TH_RecogImage(pp, pFrameInfo->nWidth, pFrameInfo->nHeight, Result, &nCarNum, nullptr, &th_PlateCfg[index]);

		if (nCarNum > 0)
		{
			bool bMatch = false;
			int areaNo = -1;
			for (int i = 0; i<nCarNum; i++)
			{
				if (strlen(Result[i].license) < 5)
				{
					continue;
				}
				memset(debugInfoThread, 0, sizeof(debugInfoThread));
				strcpy(debugInfoThread, "当前识别结果：");
				memcpy(debugInfoThread + strlen(debugInfoThread), Result[i].license, strlen(Result[i].license));
				strcpy(debugInfoThread + strlen(debugInfoThread), "当前识别通道：");
				_itoa(playInfo[index].nVideoChan, debugInfoThread + strlen(debugInfoThread), 10);
				strcpy(debugInfoThread + strlen(debugInfoThread), "  车牌置信度：");
				_itoa(Result[i].nConfidence, debugInfoThread + strlen(debugInfoThread), 10);
				strcpy(debugInfoThread + strlen(debugInfoThread), "  车牌坐标：");
				_itoa(Result[i].rcLocation.left, debugInfoThread + strlen(debugInfoThread), 10);
				strcpy(debugInfoThread + strlen(debugInfoThread), " ");
				_itoa(Result[i].rcLocation.right, debugInfoThread + strlen(debugInfoThread), 10);
				strcpy(debugInfoThread + strlen(debugInfoThread), " ");
				_itoa(Result[i].rcLocation.top, debugInfoThread + strlen(debugInfoThread), 10);
				strcpy(debugInfoThread + strlen(debugInfoThread), "  ");
				_itoa(Result[i].rcLocation.bottom, debugInfoThread + strlen(debugInfoThread), 10);
				write_log_file("plate.txt", MAX_FILE_SIZE, debugInfoThread, strlen(debugInfoThread), 3);
				/*switch (index)
				{
				case 0:
					write_log_file("plate0.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
					break;
				case 1:
					write_log_file("plate1.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
					break;
				case 2:
					write_log_file("plate2.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
					break;
				case 3:
					write_log_file("plate3.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
					break;
				default:
					break;
				}
				*/
				
				if (Result[i].nConfidence >= 70)
					//&& strcmp(recogResult[i].license, tempCarOut.license) != 0)
				{
					
					for (int j=0;j<videoInfo[index].nAreaCount;j++)
					{
						if (Result[i].rcLocation.left > videoInfo[index].areas[j].th_rect.left &&
							Result[i].rcLocation.right < videoInfo[index].areas[j].th_rect.right &&
							Result[i].rcLocation.top > videoInfo[index].areas[j].th_rect.top &&
							Result[i].rcLocation.bottom < videoInfo[index].areas[j].th_rect.bottom)
						{
							areaNo = videoInfo[index].areas[j].areaNo;
							write_log_file("plate.txt", MAX_FILE_SIZE, "matched area", strlen("matched area"), 3);
							break;
						}
					}

					if (areaNo < 0)
					{
						write_log_file("plate.txt", MAX_FILE_SIZE, "match area fail", strlen("match area fail"), 3);
						continue;
					}
					memcpy(areaCar[areaNo - 1].license, Result[i].license, strlen(Result[i].license));
					memcpy(areaCar[areaNo - 1].color, Result[i].color, 8);
					//memcpy(areaCar[index - 1].pic, pBuf, nSize);
					areaCar[areaNo - 1].nCarColor = Result[i].nCarColor;
					areaCar[areaNo - 1].nCarLogo = Result[i].nCarLogo;
					areaCar[areaNo - 1].nSubCarLogo = Result[i].nCarType;
					areaCar[areaNo - 1].nCarModel = Result[i].nCarModel;
					areaCar[areaNo - 1].nColor = Result[i].nColor;
					areaCar[areaNo - 1].nConfidence = Result[i].nConfidence;
					areaCar[areaNo - 1].nPicLenth = nSize;
					areaCar[areaNo - 1].nVideoChannel = videoInfo[index].nChanNo;
					areaCar[areaNo - 1].nAreaNo = areaNo;
					areaCar[areaNo - 1].nPicType = T_YV12;
					areaCar[areaNo - 1].nType = Result[i].nType;
					areaCar[areaNo - 1].nPicWidth = pFrameInfo->nWidth;
					areaCar[areaNo - 1].nPicHeight = pFrameInfo->nHeight;
					bMatch = true;
				}
				
			}
			if (bMatch)
			{
				PostMessage(HWND_BROADCAST, WM_AREACAR, areaNo, videoInfo[index].nChanNo);
				write_log_file("plate.txt", MAX_FILE_SIZE, "postmessage", strlen("postmessage"), 3);
			}
		}
		
	}
	else
	{
		write_log_file("Error.txt", MAX_FILE_SIZE, "error midea type", 16, 1);
	}


}


