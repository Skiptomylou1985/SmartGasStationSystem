// HCNetSDK.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "HCNetSDK.h"
#include <WINSOCK2.H> 
#include <process.h>
#pragma  comment(lib,"ws2_32.lib")  

SOCKET sclient = NULL;
bool socketIsConnected = false;
char recData[256];
uintptr_t socketThreadHwd = NULL;
int nSocketTimeOut = 0;
int nSocketConnectTimes = 10;
bool bReconnetSocket = true;
DWORD dwReconInterval = 1000;


HCNETSDK_API BOOL NET_DVR_Init()
{
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

	return 0;
}
HCNETSDK_API BOOL NET_DVR_Logout(LONG lUserID)
{
	return true;
}
HCNETSDK_API BOOL NET_DVR_ManualSnap(LONG lUserID,NET_DVR_MANUALSNAP const* lpInter,LPNET_DVR_PLATE_RESULT lpOuter)
{
	return true;
}
HCNETSDK_API BOOL NET_DVR_SetDVRMessageCallBack_V31(MSGCallBack_V31 fMessageCallBack, void* pUser)
{
	return true;
}
HCNETSDK_API BOOL NET_DVR_SetConnectTime(DWORD  dwWaitTime,DWORD  dwTryTimes)
{
	nSocketTimeOut = dwWaitTime;
	nSocketConnectTimes = dwTryTimes;
	if (sclient != NULL)
	{
		int ret = setsockopt(sclient, SOL_SOCKET, SO_SNDTIMEO, &nSocketTimeOut, sizeof(nSocketTimeOut));
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
	char *buf = new char[2] {0x31, 0x32};
	send(sclient, buf, 2, 0);
}

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
		if (len > 0)
		{
			char buffer[256];
			memcpy(buffer, recData, len);
		}
		Sleep(50);
	}
}



