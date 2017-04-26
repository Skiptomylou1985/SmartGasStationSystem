// SPlate.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "SPlate.h"

//硬盘录像机相关
NET_DVR_DEVICEINFO_V30 deviceInfo;
NET_DVR_PREVIEWINFO previewInfo;
HWND hRealVideoHanlder;
NVRInfo nvrInfo;
LONG testBufferSize ;
LONG callBackNum;

TH_PlateIDCfg th_PlateIDCfg ;
TH_PlateIDResult recogResult[6];
int nCarNum;
BITMAPINFOHEADER bitmapHeader;
TH_RECT th_RECT;
LONG nPort = -1;

int nCurGetIndex = 0;
int nCurPutIndex = 0;
CarInfoOut carInfoOut[MAX_CAR_COUNT];
unsigned char *videoChan = new unsigned char[MAX_VIDEO_CHANNEL_COUNT];
int nVideoChanCount;
int nCurVideoChan = 0;
int nLogLevel = 0;
int nCurCarCount = 0;
char *debugInfo = NULL;




SPLATE_API int SP_InitRunParam(unsigned char *pChan, int lenth)
{
	if (lenth > MAX_VIDEO_CHANNEL_COUNT)
	{
		return INVALID_VIDEO_COUNT;
	}
	memcpy(videoChan, pChan, lenth);
	nVideoChanCount = lenth;
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
	if (nvrInfo.m_lServerID < 0)
	{
		return NET_DVR_GetLastError();
	}
	return SUCCESS;
}

SPLATE_API int SP_PreviewInfo(NET_DVR_PREVIEWINFO *preInfo)
{
	memcpy(&previewInfo, preInfo, sizeof(previewInfo));
	previewInfo.lChannel = videoChan[nCurVideoChan];
	HWND pUser = nullptr;//用户数据
	nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, RealDataCallBack, pUser);
	if (nvrInfo.m_lPlayHandle < 0)
	{
		return NET_DVR_GetLastError();
	}
	return nvrInfo.m_lPlayHandle;
}
SPLATE_API int SP_InitAlg(TH_PlateIDCfg *th_plateIDCfg)
{
	memcpy(&th_PlateIDCfg, th_plateIDCfg, sizeof(TH_PlateIDCfg));
	int ret = TH_InitPlateIDSDK(&th_PlateIDCfg);
	if (ret != 0)
	{
		return ret;
	} 
	
	TH_SetImageFormat(1, false, false, &th_PlateIDCfg);
	TH_SetRecogThreshold(5, 2, &th_PlateIDCfg);//设置阈值 

	return ret;
}
SPLATE_API int SP_GetCarCount()
{
	return nCurCarCount;
}
SPLATE_API int SP_GetFirstCarInfo(CarInfoOut *carinfo)
{
	if (nCurCarCount > 0)
	{
		memcpy(carinfo, &carInfoOut[nCurGetIndex], sizeof(CarInfoOut));
		nCurCarCount--;
		if (nCurGetIndex++ == MAX_CAR_COUNT)
			nCurGetIndex = 0;
		return SUCCESS;
	}
	return FAIL;
}

SPLATE_API int SP_GetCarInfo(CarInfoOut *carinfo, int carCount)
{
	if (carCount > nCurCarCount || carCount <= 0)
		return INVALID_CAR_COUNT;
	int size = sizeof(CarInfoOut);
	for (int i = 0;i<carCount;i++)
	{
		memcpy(carinfo + size*i, &carInfoOut[nCurGetIndex], size);
		nCurCarCount--;
		if (nCurGetIndex++ == MAX_CAR_COUNT)
			nCurGetIndex = 0;
	}
	return SUCCESS;
}
SPLATE_API int SP_GetNvrStatus()
{
	return nvrInfo.m_lServerID;
}
SPLATE_API int SP_TestAPI()
{
	FILE *pFile = fopen("C:\\test01.txt", "r");
// 	fseek(pFile, 0, SEEK_END); //把指针移动到文件的结尾 ，获取文件长度
// 	int len = ftell(pFile); //获取文件长度
// 	rewind(pFile); //把指针移动到文件开头 因为我们一开始把指针移动到结尾，如果不移动回来 会出错
	for (int i=0;i<MAX_CAR_COUNT;i++)
	{
		char *license = "京A12345";
		memcpy(carInfoOut[i].license,license,strlen(license));
		carInfoOut[i].nConfidence = i;
		carInfoOut[i].nPicLenth = 2000+i;
		fread(carInfoOut[i].pic, sizeof(char), 6220800, pFile);
	}
	nCurCarCount = MAX_CAR_COUNT;
	
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

	long lFrameType = pFrameInfo->nType;
	
	if (lFrameType == T_YV12)
	{
		//PlayM4_SetDecCallBack(nPort, NULL);
		NET_DVR_StopRealPlay(nvrInfo.m_lServerID);
		nCarNum = 1;
		unsigned char * p = (unsigned char *)pBuf;
		const unsigned char *pp = (const unsigned char *)p;
		int ret = TH_RecogImage(pp, pFrameInfo->nWidth, pFrameInfo->nHeight, recogResult, &nCarNum, &th_RECT, &th_PlateIDCfg);
		if (nCarNum > 0)
		{
			for (int i =0;i<nCarNum;i++)
			{
				memcpy(carInfoOut[nCurPutIndex].license,recogResult[i].license,16);
				memcpy(carInfoOut[nCurPutIndex].color, recogResult[i].color, 16);
				memcpy(carInfoOut[nCurPutIndex].pic, pBuf, nSize);
				carInfoOut[nCurPutIndex].nCarColor = recogResult[i].nCarColor;
				carInfoOut[nCurPutIndex].nCarLogo = recogResult[i].nCarLogo;
				carInfoOut[nCurPutIndex].nCarType = recogResult[i].nCarType;
				carInfoOut[nCurPutIndex].nColor = recogResult[i].nColor;
				carInfoOut[nCurPutIndex].nConfidence = recogResult[i].nConfidence;
				carInfoOut[nCurPutIndex].nPicLenth = nSize;
				carInfoOut[nCurPutIndex].nVideoChannel = nCurVideoChan;
				carInfoOut[nCurPutIndex].nPicType = T_YV12;
				carInfoOut[nCurPutIndex].nType = recogResult[i].nType;
				nCurPutIndex++;
			}
			
			if (++nCurVideoChan >= nVideoChanCount)
			{
				nCurVideoChan = 0;
			}
			
		}
		previewInfo.lChannel = videoChan[nCurVideoChan];
		NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, NULL, nullptr);
	}
	else
	{
		char *errorInfo = "error midea type\n";
		write_log_file("error.txt", FILE_MAX_SIZE, errorInfo, strlen(errorInfo));
	}


}
void CALLBACK RealDataCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{
	DWORD dRet;

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:    //系统头
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
		if (dwBufSize > 0 && nPort != -1)
		{
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


