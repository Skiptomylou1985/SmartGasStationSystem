// HCNetSDK.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "HCNetSDK.h"
#include <WINSOCK2.H> 
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#pragma  comment(lib,"ws2_32.lib")  
#define  CMDINIT 0x01
#define  CMDLOGIN 0x02
#define  CMDSNAP 0x03
#define  CMDHEARTBIT 0x04
#define  CMDSETMODE 0x05

SOCKET sclient = NULL;
bool socketIsConnected = false;
char recData[256];
uintptr_t socketThreadHwd = NULL;
int nSocketTimeOut = 0;
int nSocketConnectTimes = 10;
bool bReconnetSocket = true;
DWORD dwReconInterval = 1000;
MSGCallBack_V31 msgCallBack_V31;
NET_ITS_PLATE_RESULT curCallBackResult;
NET_DVR_PLATE_RESULT curSnapResult;
HANDLE snapEvent  = NULL;
bool bLoginIn = false;

SOCKET getSocketConnect(char *hostIP, int port)
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return NULL;
	}

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET)
	{
		return NULL;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);
	serAddr.sin_addr.S_un.S_addr = inet_addr(hostIP);
	if (connect(client, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		closesocket(client);
		return NULL;
	}
	return client;
}
void _stdcall ThreadFuncRecv(LPVOID lpParam)
{
	while (socketIsConnected)
	{
		int len = recv(sclient, recData, 256, 0);
		if (len > 0 && bLoginIn)
		{
			char buffer[256];
			memcpy(buffer, recData, len);
			if (buffer[2] == 0x06 && NULL != msgCallBack_V31)  //回调返回
			{
				memset(&curCallBackResult, 0, sizeof(NET_ITS_PLATE_RESULT));
				memcpy(&curCallBackResult, &buffer[4], sizeof(NET_ITS_PLATE_RESULT));
				NET_DVR_ALARMER *p = new NET_DVR_ALARMER();
				DWORD dwbuflen = sizeof(NET_ITS_PLATE_RESULT);
				char *pInfo = (char *)malloc(dwbuflen);
				memcpy(pInfo, &curCallBackResult, dwbuflen);
				msgCallBack_V31(COMM_ITS_PLATE_RESULT, p, pInfo, dwbuflen, nullptr);
			}
			else if (buffer[2] == 0x03)
			{
				memset(&curSnapResult, 0, sizeof(NET_DVR_PLATE_RESULT));
				memcpy(&curSnapResult, &buffer[4], sizeof(NET_DVR_PLATE_RESULT));
				SetEvent(snapEvent);
			}
		}
		Sleep(20);
	}
}
HCNETSDK_API BOOL NET_DVR_Init()
{
	/*char ip[30];
	GetPrivateProfileString("server", "ip", "127.0.0.1", ip, 10, ".\\HCNetSDKConfig.ini")*/

	snapEvent = CreateEvent(NULL, false, true, NULL);
	sclient = getSocketConnect("127.0.0.1", 8870);
	if (NULL == sclient)
		return false;
	socketIsConnected = true;
	socketThreadHwd = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadFuncRecv, NULL, 0,NULL);
	return true;
}

HCNETSDK_API BOOL NET_DVR_Cleanup()
{
	socketIsConnected = false;
	msgCallBack_V31 = nullptr;
	if (NULL != socketThreadHwd)
	{
		TerminateThread((HANDLE)socketThreadHwd, NULL);
		socketThreadHwd = NULL;
	}
	if (NULL != sclient)
	{
		closesocket(sclient);
		sclient = NULL;
	}
	
	return true;
}
HCNETSDK_API LONG NET_DVR_Login_V30(char  *sDVRIP,WORD wDVRPort,char  *sUserName,char  *sPassWord,LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo)
{
	bLoginIn = true;
	return 0;
}
HCNETSDK_API BOOL NET_DVR_Logout(LONG lUserID)
{
	bLoginIn = false;
	return true;
}
HCNETSDK_API BOOL NET_DVR_ManualSnap(LONG lUserID,NET_DVR_MANUALSNAP * lpInter,LPNET_DVR_PLATE_RESULT lpOuter)
{
	if (socketIsConnected && sclient != NULL && bLoginIn)
	{
		NET_DVR_MANUALSNAP snap = NET_DVR_MANUALSNAP();
		snap.byPumpID = lpInter->byPumpID;
		snap.byPumpStatus = lpInter->byPumpStatus;
		
		//memcpy(&snap, lpInter, 2);
		char sendbuf[10];
		sendbuf[0] = 0xFF;
		sendbuf[1] = 0xFF;
		sendbuf[2] = CMDSNAP;
		sendbuf[3] = 2;
		sendbuf[4] = snap.byPumpID;
		sendbuf[5] = snap.byPumpStatus; 
		sendbuf[6] = 0;
		sendbuf[7] = 0;
		sendbuf[8] = 0xEE;
		sendbuf[9] = 0xEE;
		send(sclient, &sendbuf[0], 10, 0);
		ResetEvent(snapEvent);
		DWORD dw = WaitForSingleObject(snapEvent, 3000);
		switch (dw)
		{
		case WAIT_OBJECT_0:
			memcpy(lpOuter, &curSnapResult, sizeof(NET_DVR_PLATE_RESULT));
			break;

		case WAIT_TIMEOUT:
			return false;
			break;

		case WAIT_FAILED:
			return false;
			break;
		}
		return true;
	}
	return false;
	
}
HCNETSDK_API BOOL NET_DVR_SetDVRMessageCallBack_V31(MSGCallBack_V31 fMessageCallBack, void* pUser)
{
	msgCallBack_V31 = fMessageCallBack;
	return true;
}
HCNETSDK_API BOOL NET_DVR_SetConnectTime(DWORD  dwWaitTime,DWORD  dwTryTimes)
{
	char timeOut[10];
	_itoa(dwWaitTime, timeOut, 10);
	nSocketTimeOut = dwWaitTime;
	nSocketConnectTimes = dwTryTimes;
	if (sclient != NULL)
	{
		int ret = setsockopt(sclient, SOL_SOCKET, SO_SNDTIMEO, timeOut, strlen(timeOut));
		if (ret < 0)
			return false;
	}
	return true;
	
}
HCNETSDK_API BOOL NET_DVR_SetReconnect(DWORD  dwInterval,BOOL  bEnableRecon)
{
	dwReconInterval = dwInterval;
	bReconnetSocket = bEnableRecon;
	return true;
}
HCNETSDK_API void NET_DVR_TestAPI()
{
	/*NET_DVR_ALARMER *p = new NET_DVR_ALARMER();
	memset(&curCallBackResult, 0, sizeof(NET_ITS_PLATE_RESULT));
	memcpy(curCallBackResult.sLicense, "京A12345", strlen("京A12345"));
	curCallBackResult.byPlateColor = 1;
	curCallBackResult.byColor = 2;
	curCallBackResult.wVehicleLogoRecog = 3;
	curCallBackResult.wVehicleSubLogoRecog = 4;
	DWORD dwbuflen = sizeof(NET_ITS_PLATE_RESULT);
	char *pInfo = (char *)malloc(dwbuflen);
	memcpy(pInfo, &curCallBackResult, dwbuflen);
	msgCallBack_V31(COMM_ITS_PLATE_RESULT, p, pInfo, dwbuflen, nullptr);*/
}
HCNETSDK_API DWORD NET_DVR_GetLastError()
{
	return 0;
}





