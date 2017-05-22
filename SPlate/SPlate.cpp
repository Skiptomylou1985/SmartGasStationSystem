// SPlate.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "SPlate.h"
#include <tchar.h>

//硬盘录像机相关
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
unsigned char *videoChan [MAX_VIDEO_CHANNEL_COUNT];
struNozzleInfo nozzleInfo[MAX_NOZZLE_COUNT];
int nNozzleCount = 0;
int nVideoChanCount = 0;
int nLogLevel = 3;
int nCurCarCount = 0;
int nCurNozzleIndex= 0;
char debugInfo[256] ;
int calc = 0;
NET_DVR_IPPARACFG_V40 struIPPARACFG;

int nSwitchCount = 100;
char *lastLicense[MAX_NOZZLE_COUNT] ;


SPLATE_API int SP_InitRunParam(unsigned char *pChan, int lenth)
{
	if (lenth > MAX_NOZZLE_COUNT)
	{
		return INVALID_NOZZLE_COUNT;
	}
	memcpy(nozzleInfo, pChan, lenth*sizeof(struNozzleInfo));
	nNozzleCount = lenth;
	for (int i = 0; i < MAX_NOZZLE_COUNT; i++)
	{
		lastLicense[i] = (char *)malloc(16);
		nozzleInfo[i].videoChanNo += struIPPARACFG.dwStartDChan;
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
	if (nvrInfo.m_lServerID > 0)
	{
		NET_DVR_Logout(nvrInfo.m_lServerID);
		NET_DVR_Cleanup();
	}
	
	
	return SUCCESS;
}
SPLATE_API int SP_PreviewInfo(NET_DVR_PREVIEWINFO *preInfo, int lenth)
{
	memcpy(&previewInfo, preInfo, lenth);
	//previewInfo.lChannel = nozzleInfo[nCurNozzleIndex].videoChanNo;
	HWND pUser = nullptr;//用户数据
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
	previewInfo.hPlayWnd = nullptr;
	previewInfo.lChannel = nozzleInfo[nCurNozzleIndex].videoChanNo;
	if (hPlayHandle != NULL)
	{
		previewInfo.hPlayWnd = hPlayHandle;
	}
	previewInfo.dwStreamType = 0;//码流类型：0-主码流，1-子码流，2-码流3，3-码流4，以此类推
	previewInfo.dwLinkMode = 0;//连接方式：0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP 
	previewInfo.bBlocked = false; //0- 非阻塞取流，1- 阻塞取流
	previewInfo.dwDisplayBufNum = 15;
	HWND pUser = nullptr;//用户数据
	nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, RealDataCallBack, pUser);
	
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "NET_DVR_RealPlay_V40 return value:");
	_itoa(nvrInfo.m_lPlayHandle, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo+strlen(debugInfo), " 通道号:");
	_itoa(nozzleInfo[nCurNozzleIndex].videoChanNo, debugInfo + strlen(debugInfo), 10);
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
	TH_SetRecogThreshold(5, 2, &th_PlateIDCfg);//设置阈值 
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
SPLATE_API int SP_SetSwitchFlag(int frameCount)
{
	nSwitchCount = frameCount;
	return SUCCESS;
}
SPLATE_API int SP_TestAPI()
{
	//PostMessage(HWND_BROADCAST, WM_CARDATA, 0, 0);
	//char test[16] = "12345";
	//lastLicense[0] = "init";
	//lastLicense[0] = (char *)malloc(16);
	//memcpy(lastLicense[0], test, 5);
	//if (strcmp(lastLicense[0],test) == 0)
	//{
	//	return 0;
	//}
	return 0;
	//return SwithNextNozzle();
}
int SwithNextNozzle(void)
{
	DWORD pUser = 0;
	

	//NET_DVR_SetRealDataCallBack(nvrInfo.m_lPlayHandle, NULL, pUser);
	//PlayM4_SetDecCallBack(nPort, NULL);
	
	//Sleep(500);
	int tempIndex = nCurNozzleIndex;
	
	if (++nCurNozzleIndex == nNozzleCount)
		nCurNozzleIndex = 0;
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "Now：");
	_itoa(tempIndex, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), " video：");
	_itoa(nozzleInfo[tempIndex].videoChanNo, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), " next:");
	_itoa(nCurNozzleIndex, debugInfo + strlen(debugInfo), 10);
	strcpy(debugInfo + strlen(debugInfo), " video：");
	_itoa(nozzleInfo[nCurNozzleIndex].videoChanNo, debugInfo + strlen(debugInfo), 10);
	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),3);
	if (nozzleInfo[tempIndex].videoChanNo == nozzleInfo[nCurNozzleIndex].videoChanNo)
	{
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
		NET_DVR_StopRealPlay(nvrInfo.m_lPlayHandle);
		write_log_file("Debug.txt", MAX_FILE_SIZE, "Stoped RealPlay", 15,3);
		previewInfo.lChannel = nozzleInfo[nCurNozzleIndex].videoChanNo;
		//重新初始化识别库
		//memcpy(&th_PlateIDCfg, &th_PlateIDCfg_bak, sizeof(TH_PlateIDCfg));
		//th_PlateIDCfg.pFastMemory = (unsigned char*)malloc(th_PlateIDCfg.nFastMemorySize);
		//th_PlateIDCfg.pMemory = (unsigned char*)malloc(th_PlateIDCfg.nMemorySize);
		//nAlgStatus = TH_InitPlateIDSDK(&th_PlateIDCfg);
		//if (nAlgStatus != 0)
		//{
		//	write_log_file("Error.txt", MAX_FILE_SIZE, "Alg reInit Fail", 15,1);
		//}
		//TH_SetImageFormat(ImageFormatYV12, false, false, &th_PlateIDCfg);
		//TH_SetRecogThreshold(5, 2, &th_PlateIDCfg);//设置阈值 

		nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, RealDataCallBack, nullptr);
		
		write_log_file("Debug.txt", MAX_FILE_SIZE, "end switch", 10,3);
	}
	return 0;

}
bool YV12_to_RGB24(unsigned char* pYV12, unsigned char* pRGB24, int iWidth, int iHeight)
{
	if (!pYV12 || !pRGB24)
		return false;

	const long nYLen = long(iHeight * iWidth);
	const int nHfWidth = (iWidth >> 1);

	if (nYLen < 1 || nHfWidth < 1)
		return false;

	unsigned char* yData = pYV12;
	unsigned char* vData = &yData[nYLen];
	unsigned char* uData = &vData[nYLen >> 2];
	if (!uData || !vData)
		return false;

	int rgb[3];
	int i, j, m, n, x, y;
	m = -iWidth;
	n = -nHfWidth;
	for (y = 0; y < iHeight; y++)
	{
		m += iWidth;

		if (!(y % 2))
			n += nHfWidth;

		for (x = 0; x < iWidth; x++)
		{
			i = m + x;
			j = n + (x >> 1);
			rgb[2] = int(yData[i] + 1.370705 * (vData[j] - 128)); // r分量值  
			rgb[1] = int(yData[i] - 0.698001 * (uData[j] - 128) - 0.703125 * (vData[j] - 128)); // g分量值  
			rgb[0] = int(yData[i] + 1.732446 * (uData[j] - 128)); // b分量值  
			j = nYLen - iWidth - m + x;
			i = (j << 1) + j;
			for (j = 0; j < 3; j++)
			{
				if (rgb[j] >= 0 && rgb[j] <= 255)
					pRGB24[i + j] = rgb[j];
				else
					pRGB24[i + j] = (rgb[j] < 0) ? 0 : 255;
			}
		}
	}

	return true;
}
void CALLBACK DecCBFun(long nPort, char *pBuf, long nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2)
{
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
		
		nCarNum = 1;
		unsigned char * p = (unsigned char *)pBuf;
		const unsigned char *pp = (const unsigned char *)p;
		write_log_file("Callback.txt", MAX_FILE_SIZE, "begin recog", strlen("begin recog"),4);
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "nCurNozzleIndex:");
		_itoa(nCurNozzleIndex, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo+strlen(debugInfo), "   th_rect:");
		_itoa(nozzleInfo[nCurNozzleIndex].th_rect.left, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " ");
		_itoa(nozzleInfo[nCurNozzleIndex].th_rect.right, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " ");
		_itoa(nozzleInfo[nCurNozzleIndex].th_rect.top, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " ");
		_itoa(nozzleInfo[nCurNozzleIndex].th_rect.bottom, debugInfo + strlen(debugInfo), 10);

		write_log_file("Callback.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 4);
		int ret = TH_RecogImage(pp, pFrameInfo->nWidth, pFrameInfo->nHeight, recogResult, &nCarNum, &nozzleInfo[nCurNozzleIndex].th_rect, &th_PlateIDCfg);
		
		write_log_file("Callback.txt", MAX_FILE_SIZE, "end recog", strlen("end recog"), 4);
		/*if (nLogLevel >= 4)
		{
			memset(debugInfo, 0, sizeof(debugInfo));
			strcpy(debugInfo, "end recog car count:");
			_itoa(nCarNum, debugInfo + strlen(debugInfo), 10);
			write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),4);
		}*/
			
		if (nCarNum > 0)
		{
			for (int i =0;i<nCarNum;i++)
			{

				memset(debugInfo, 0, sizeof(debugInfo));
				strcpy(debugInfo, "当前识别结果：");
				memcpy(debugInfo+strlen(debugInfo), recogResult[i].license, strlen(recogResult[i].license));
				write_log_file("license.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),2);

				if (strcmp(lastLicense[nCurNozzleIndex],recogResult[i].license) == 0)
				{
					write_log_file("license.txt", MAX_FILE_SIZE, "license repeat", strlen("license repeat"), 2);
					continue;
				}
				memcpy(lastLicense[nCurNozzleIndex], recogResult[i].license, 16);
				memcpy(carInfoOut[nCurPutIndex].license,recogResult[i].license,16);
				memcpy(carInfoOut[nCurPutIndex].color, recogResult[i].color, 16);
				memcpy(carInfoOut[nCurPutIndex].pic, pBuf, nSize);
				carInfoOut[nCurPutIndex].nCarColor = recogResult[i].nCarColor;
				carInfoOut[nCurPutIndex].nCarLogo = recogResult[i].nCarLogo;
				carInfoOut[nCurPutIndex].nSubCarLogo = recogResult[i].nCarType;
				carInfoOut[nCurPutIndex].nCarModel = recogResult[i].nCarModel;
				carInfoOut[nCurPutIndex].nColor = recogResult[i].nColor;
				carInfoOut[nCurPutIndex].nConfidence = recogResult[i].nConfidence;
				carInfoOut[nCurPutIndex].nPicLenth = nSize;
				carInfoOut[nCurPutIndex].nVideoChannel = nozzleInfo[nCurNozzleIndex].videoChanNo;
				carInfoOut[nCurPutIndex].nNozzleNo = nozzleInfo[nCurNozzleIndex].nozzleNo;
				carInfoOut[nCurPutIndex].nPicType = T_YV12;
				carInfoOut[nCurPutIndex].nType = recogResult[i].nType;
				carInfoOut[nCurPutIndex].nPicWidth = pFrameInfo->nWidth;
				carInfoOut[nCurPutIndex].nPicHeight = pFrameInfo->nHeight;
				

				if (++nCurPutIndex == MAX_CAR_COUNT)
				{
					nCurPutIndex = 0;
				}
				nCurCarCount++;
				write_log_file("license.txt", MAX_FILE_SIZE, "post massage", strlen("post massage"), 2);
				PostMessage(HWND_BROADCAST,WM_CARDATA ,0, 0);
			}
			memset(debugInfo, 0, sizeof(debugInfo));
			strcpy(debugInfo, "当前油枪号：");
			_itoa(nCurNozzleIndex, debugInfo, 10);
			write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),3);
		}
		calc++;
		if (calc > nSwitchCount)
		{
			calc = 0;
			SwithNextNozzle();
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
		if (dwBufSize > 0 && nPort != -1)
		{
			if (nLogLevel >= 4)
			{
				memset(debugInfo, 0, sizeof(debugInfo));
				strcpy(debugInfo, "RealDataCallBack-> PlayM4_InputData");
				write_log_file("Callback.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo),4);
			}
			BOOL inData = PlayM4_InputData(nPort, pBuffer, dwBufSize);
			while (!inData)
			{
				Sleep(10);
				inData = PlayM4_InputData(nPort, pBuffer, dwBufSize);
			}
		}
		break;
	}
	
}


