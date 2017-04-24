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
unsigned char *videoChan;
int nVideoChanCount;
int nCurVideoChan = 0;



SPLATE_API int SP_InitRunParam(unsigned char *pChan, int lenth)
{
	memcpy(videoChan, pChan, lenth);
	nVideoChanCount = lenth;
	return 0;
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
	return nvrInfo.m_lServerID;
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
SPLATE_API int SP_TestAPI()
{
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
	char *debugInfo = NULL;
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
			unsigned char *bmpImage = NULL;
			debugInfo = "start save image \n";
			write_log_file("Debug.txt", FILE_MAX_SIZE, debugInfo, strlen(debugInfo));
			if (YV12_to_RGB24((unsigned char *)pBuf, bmpImage, pFrameInfo->nWidth, pFrameInfo->nHeight))
			{

				save_image_file("test01.bmp", (char *)bmpImage, nSize * 2);
			}
			debugInfo = "end save image \n";
			write_log_file("Debug.txt", FILE_MAX_SIZE, debugInfo, strlen(debugInfo));
		}
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


