// SPlate.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "SPlate.h"

//Ӳ��¼������
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
unsigned char *videoChan [MAX_VIDEO_CHANNEL_COUNT];
NozzleInfo nozzleInfo[MAX_NOZZLE_COUNT];
int nNozzleCount = 0;
int nVideoChanCount = 0;
int nCurVideoChan = 0;
int nLogLevel = 3;
int nCurCarCount = 0;
int nCurNozzleIndex= 0;
char debugInfo[256] ;
int calc = 0;
bool bSwith = false;
bool bRecog = false;
NET_DVR_IPPARACFG_V40 struIPPARACFG;





SPLATE_API int SP_InitRunParam(unsigned char *pChan, int lenth)
{
	if (lenth > MAX_NOZZLE_COUNT)
	{
		return INVALID_NOZZLE_COUNT;
	}
	memcpy(nozzleInfo, pChan, lenth*sizeof(NozzleInfo));
	nNozzleCount = lenth;
	for (int i = 0; i < MAX_NOZZLE_COUNT; i++)
	{
		nozzleInfo[i].videoChanNo += struIPPARACFG.dwStartDChan;
	}
	return SUCCESS;
}

SPLATE_API int SP_InitNVR(char *IpAddress, LONG nPort, char *sAdmin, char *sPassword)
{
	write_log_file("debug.txt", MAX_FILE_SIZE, "aaaa", 4);
	bool ret = NET_DVR_Init();
	write_log_file("debug.txt", MAX_FILE_SIZE, "bbbb", 4);
	NET_DVR_SetConnectTime(2000, 1); 
	NET_DVR_SetReconnect(10000, true);
	write_log_file("debug.txt", MAX_FILE_SIZE, "cccc", 4);
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
	write_log_file("debug.txt", MAX_FILE_SIZE, "0000", 4);
	NET_DVR_GetDVRConfig(nvrInfo.m_lServerID, NET_DVR_GET_IPPARACFG_V40, 0, &struIPPARACFG, sizeof(struIPPARACFG), &dwReturn);
	write_log_file("debug.txt", MAX_FILE_SIZE, "1111", 4);
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

SPLATE_API int SP_PreviewInfo(NET_DVR_PREVIEWINFO *preInfo)
{
	memcpy(&previewInfo, preInfo, sizeof(previewInfo));
	previewInfo.lChannel = nozzleInfo[nCurNozzleIndex].videoChanNo;
	HWND pUser = nullptr;//�û�����
	nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, RealDataCallBack, pUser);
	if (nvrInfo.m_lPlayHandle < 0)
	{
		return NET_DVR_GetLastError();
	}
	return nvrInfo.m_lPlayHandle;
}
SPLATE_API int SP_BeginRecog()
{
	previewInfo.hPlayWnd = nullptr;
	previewInfo.lChannel = nozzleInfo[nCurNozzleIndex].videoChanNo;

	previewInfo.dwStreamType = 0;//�������ͣ�0-��������1-��������2-����3��3-����4���Դ�����
	previewInfo.dwLinkMode = 0;//���ӷ�ʽ��0- TCP��ʽ��1- UDP��ʽ��2- �ಥ��ʽ��3- RTP��ʽ��4-RTP/RTSP��5-RSTP/HTTP 
	previewInfo.bBlocked = false; //0- ������ȡ����1- ����ȡ��
	previewInfo.dwDisplayBufNum = 15;
	HWND pUser = nullptr;//�û�����
	nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, RealDataCallBack, pUser);
	
	if (nLogLevel >= 3)
	{
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "NET_DVR_RealPlay_V40 return value:");
		_itoa(nvrInfo.m_lPlayHandle, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo+strlen(debugInfo), " ͨ����:");
		_itoa(nozzleInfo[nCurNozzleIndex].videoChanNo, debugInfo + strlen(debugInfo), 10);
		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo));
	}
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
	
	TH_SetImageFormat(ImageFormatYV12, false, false, &th_PlateIDCfg);
	TH_SetRecogThreshold(5, 2, &th_PlateIDCfg);//������ֵ 

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
SPLATE_API int SP_SetLogLevel(int loglevel)
{
	nLogLevel = loglevel;
	return SUCCESS;
}
SPLATE_API int SP_TestAPI()
{
	//return SwithNextNozzle();
	//return 0;
	NET_DVR_GET_STREAM_UNION teet;
	int a = sizeof(NET_DVR_GET_STREAM_UNION);
	return a;
}
int SwithNextNozzle(void)
{
	DWORD pUser = 0;
	NET_DVR_SetRealDataCallBack(nvrInfo.m_lPlayHandle, NULL, pUser);
	PlayM4_SetDecCallBack(nPort, NULL);
	bSwith = true;
	write_log_file("DecCBFun.txt", MAX_FILE_SIZE, "000", 3);
	
	//Sleep(500);
	int tempIndex = nCurNozzleIndex;
	
	if (++nCurNozzleIndex == nNozzleCount)
		nCurNozzleIndex = 0;
	if (nLogLevel >= 3)
	{
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "Now��");
		_itoa(tempIndex, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " video��");
		_itoa(nozzleInfo[tempIndex].videoChanNo, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " next:");
		_itoa(nCurNozzleIndex, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " video��");
		_itoa(nozzleInfo[nCurNozzleIndex].videoChanNo, debugInfo + strlen(debugInfo), 10);
		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo));
	}
	if (nozzleInfo[tempIndex].videoChanNo == nozzleInfo[nCurNozzleIndex].videoChanNo)
	{
		write_log_file("Debug.txt", MAX_FILE_SIZE, "in", 2);
		bSwith = false;
		return 0;
	}
	else
	{
		write_log_file("DecCBFun.txt", MAX_FILE_SIZE, "444", 3);
		if(nLogLevel >= 3)
			write_log_file("Debug.txt", MAX_FILE_SIZE, "begin change channel", 20);
		NET_DVR_StopRealPlay(nvrInfo.m_lPlayHandle);
		write_log_file("DecCBFun.txt", MAX_FILE_SIZE, "555", 3);
		if (nLogLevel >= 3)
			write_log_file("Debug.txt", MAX_FILE_SIZE, "StopRealPlay", 12);
		previewInfo.lChannel = nozzleInfo[nCurNozzleIndex].videoChanNo;
			
		nvrInfo.m_lPlayHandle = NET_DVR_RealPlay_V40(nvrInfo.m_lServerID, &previewInfo, RealDataCallBack, nullptr);
		write_log_file("DecCBFun.txt", MAX_FILE_SIZE, "666", 3);
		if (nLogLevel >= 3)
			write_log_file("Debug.txt", MAX_FILE_SIZE, "end", 3);
	}
	bSwith = false;
	write_log_file("DecCBFun.txt", MAX_FILE_SIZE, "777", 3);
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
			rgb[2] = int(yData[i] + 1.370705 * (vData[j] - 128)); // r����ֵ  
			rgb[1] = int(yData[i] - 0.698001 * (uData[j] - 128) - 0.703125 * (vData[j] - 128)); // g����ֵ  
			rgb[0] = int(yData[i] + 1.732446 * (uData[j] - 128)); // b����ֵ  
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
		strcpy(debugInfo, "���");
		_itoa(pFrameInfo->nWidth, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " �߶�");
		_itoa(pFrameInfo->nHeight, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " ��Ƶ��ʽ");
		_itoa(pFrameInfo->nType, debugInfo + strlen(debugInfo), 10);
		write_log_file("DecCBFun.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo));
	}
	long lFrameType = pFrameInfo->nType;
	
	if (lFrameType == T_YV12)
	{
		
		nCarNum = 1;
		unsigned char * p = (unsigned char *)pBuf;
		const unsigned char *pp = (const unsigned char *)p;
		if (nLogLevel >= 3)
			write_log_file("DecCBFun.txt", MAX_FILE_SIZE, "begin recog", strlen("begin recog"));
		if (bSwith)
		{
			return;
		}
		int ret = TH_RecogImage(pp, pFrameInfo->nWidth, pFrameInfo->nHeight, recogResult, &nCarNum, &nozzleInfo[nCurNozzleIndex].th_rect, &th_PlateIDCfg);
		//int ret = TH_RecogImage(pp, 1920, 1080, recogResult, &nCarNum, &nozzleInfo[nCurNozzleIndex].th_rect, &th_PlateIDCfg);
		
		if (nLogLevel >= 3)
		{
			memset(debugInfo, 0, sizeof(debugInfo));
			strcpy(debugInfo, "end recog car count:");
			_itoa(nCarNum, debugInfo + strlen(debugInfo), 10);
			write_log_file("DecCBFun.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo));
		}
			
		if (nCarNum > 0)
		{
			for (int i =0;i<nCarNum;i++)
			{

				if (nLogLevel >= 2)
				{
					memset(debugInfo, 0, sizeof(debugInfo));
					strcpy(debugInfo, "��ǰʶ������");
					memcpy(debugInfo+strlen(debugInfo), recogResult[i].license, strlen(recogResult[i].license));
					write_log_file("license.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo));
				}

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
			if (nLogLevel >= 3)
			{
				memset(debugInfo, 0, sizeof(debugInfo));
				strcpy(debugInfo, "��ǰ��ǹ�ţ�");
				_itoa(nCurNozzleIndex, debugInfo, 10);
				write_log_file("DecCBFun.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo));
			}
			
			//SwithNextNozzle();
		}
		
	}
	else
	{
		char *errorInfo = "error midea type";
		write_log_file("error.txt", MAX_FILE_SIZE, errorInfo, strlen(errorInfo));
	}
	

}
void CALLBACK RealDataCallBack(LONG lPlayHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{
	DWORD dRet;
	if (bSwith)
	{
		return;
	}

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:    //ϵͳͷ
		if (nLogLevel >= 3)
		{
			memset(debugInfo, 0, sizeof(debugInfo));
			strcpy(debugInfo, "RealDataCallBack-> NET_DVR_SYSHEAD dwBufSize:");
			_itoa(dwBufSize, debugInfo + strlen(debugInfo), 10);
			write_log_file("time.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo));
		}
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

		}
		break;

	case NET_DVR_STREAMDATA:   //��������
		if (nLogLevel >= 4)
		{
			memset(debugInfo, 0, sizeof(debugInfo));
			strcpy(debugInfo, "RealDataCallBack-> NET_DVR_STREAMDATA dwBufSize:");
			_itoa(dwBufSize, debugInfo + strlen(debugInfo), 10);
			write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo));
		}
		if (dwBufSize > 0 && nPort != -1)
		{
			if (nLogLevel >= 4)
			{
				memset(debugInfo, 0, sizeof(debugInfo));
				strcpy(debugInfo, "RealDataCallBack-> PlayM4_InputData");
				write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo));
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
	/*calc++;
	if (calc > 10)
	{
		calc = 0;
		SwithNextNozzle();
	}*/


}


