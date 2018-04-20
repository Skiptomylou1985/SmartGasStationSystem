// HCNetSDK.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "HCNetSDK.h"
#include "log.h"
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
#define  CMDTRADE 0x06

SOCKET sclient = NULL;
bool socketIsConnected = false;
char recData[256];
uintptr_t socketThreadHwd = NULL;
uintptr_t reconSocketThreadHwd = NULL;
int nSocketTimeOut = 0;
int nSocketConnectTimes = 10;
bool bReconnetSocket = true;
DWORD dwReconInterval = 10000;
MSGCallBack_V31 msgCallBack_V31;
NET_ITS_PLATE_RESULT curCallBackResult;
NET_DVR_PLATE_RESULT curSnapResult;
HANDLE snapEvent  = NULL;
HANDLE loginEvent = NULL;
bool bLoginIn = false;
char ip[30];
int port;
int failSendCount = 0;
int lastError = 0;

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
		if (len > 0 )
		{
			char buffer[256];
			memcpy(buffer, recData, len);
			if (buffer[2] == 0x06 && NULL != msgCallBack_V31)  //回调返回
			{
				write_log_file("receive callback data", strlen("receive callback data"));
				memset(&curCallBackResult, 0, sizeof(NET_ITS_PLATE_RESULT));
				memcpy(&curCallBackResult, &buffer[4], sizeof(NET_ITS_PLATE_RESULT));
				char info[128] = "Plate:";
				strcpy(info + strlen(info), curCallBackResult.sLicense);
				strcpy(info + strlen(info), "  byVehicleState:");
				_itoa(curCallBackResult.byVehicleState, info + strlen(info), 10);
				write_log_file(info, strlen(info));
				NET_DVR_ALARMER *p = new NET_DVR_ALARMER();
				DWORD dwbuflen = sizeof(NET_ITS_PLATE_RESULT);
				char *pInfo = (char *)malloc(dwbuflen);
				memcpy(pInfo, &curCallBackResult, dwbuflen);
				write_log_file("execute callback function begin", strlen("execute callback function begin"));
				msgCallBack_V31(COMM_ITS_PLATE_RESULT, p, pInfo, dwbuflen, nullptr);
				write_log_file("execute callback function end", strlen("execute callback function end"));
			}
			else if (buffer[2] == 0x03 )
			{
				write_log_file("receive snap data", strlen("receive snap data"));
				memset(&curSnapResult, 0, sizeof(NET_DVR_PLATE_RESULT));
				memcpy(&curSnapResult, &buffer[4], sizeof(NET_DVR_PLATE_RESULT));
				
				SetEvent(snapEvent);
			}
			else if (buffer[2] == 0x02 )
			{
				if (buffer[4] == 0x01)
				{
					SetEvent(loginEvent);
					write_log_file("receive login success info", strlen("receive login success info"));
				}
				else
				{
					write_log_file("receive login fail info", strlen("receive login fail info"));
				}
				
			}
		}
		Sleep(20);
	}
}
void _stdcall ThreadReconSocket()
{
	while (bReconnetSocket)
	{
		Sleep(dwReconInterval);
		if (!socketIsConnected)
		{
			write_log_file("socket reconnect", strlen("socket reconnect"));

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
			sclient = getSocketConnect(ip, port);
			if (NULL == sclient)
			{
				
				write_log_file("socket reconnect fail", strlen("socket reconnect fail"));
			}
			else
			{
				socketIsConnected = true;
				socketThreadHwd = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadFuncRecv, NULL, 0, NULL);
				write_log_file("socket reconnect success", strlen("socket reconnect success"));
			}
		}
	}
}
HCNETSDK_API BOOL NET_DVR_Init()
{
	//write_log_file("NET_DVR_Init begin", strlen("NET_DVR_Init begin"));
	
	//GetPrivateProfileStringA("server", "ip", "127.0.0.1", ip, 10, ".\\HCNetSDKConfig.ini");
	//char sPort[8];
	//GetPrivateProfileStringA("server", "port", "8870", sPort, 10, ".\\HCNetSDKConfig.ini");
	//port = atoi(sPort);
	//char info[128] = "get parameters from file HCNetSDKConfig.ini    server ip:";
	//strcpy(info + strlen(info), ip);
	//strcpy(info + strlen(info), "  port:");
	//strcpy(info + strlen(info), sPort);
	//write_log_file(info, strlen(info));

	snapEvent = CreateEvent(NULL, false, true, NULL);
	loginEvent = CreateEvent(NULL, false, true, NULL);
	
	//reconSocketThreadHwd = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadReconSocket, NULL, 0, NULL);
	write_log_file("NET_DVR_Init Success", strlen("NET_DVR_Init Success"));
	return true;
}
HCNETSDK_API BOOL NET_DVR_Cleanup()
{
	write_log_file("NET_DVR_Cleanup Begin", strlen("NET_DVR_Cleanup Begin"));
	socketIsConnected = false;
	bReconnetSocket = false;
	//msgCallBack_V31 = nullptr;
	if (NULL != socketThreadHwd)
	{
		TerminateThread((HANDLE)socketThreadHwd, NULL);
		socketThreadHwd = NULL;
	}
	if (NULL != reconSocketThreadHwd)
	{
		TerminateThread((HANDLE)reconSocketThreadHwd, NULL);
		socketThreadHwd = NULL;
	}
	if (NULL != sclient)
	{
		closesocket(sclient);
		sclient = NULL;
	}
	write_log_file("NET_DVR_Cleanup SUCCESS", strlen("NET_DVR_Cleanup SUCCESS"));
	return true;
}
HCNETSDK_API LONG NET_DVR_Login_V30(char  *sDVRIP,WORD wDVRPort,char  *sUserName,char  *sPassWord,LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo)
{
	write_log_file("NET_DVR_Login_V30 Begin", strlen("NET_DVR_Login_V30 Begin"));
	memcpy(ip, sDVRIP, strlen(sDVRIP));
	port = wDVRPort;
	sclient = getSocketConnect(sDVRIP, wDVRPort);
	bReconnetSocket = true;
	if (NULL == sclient)
	{
		lastError = -1;
		reconSocketThreadHwd = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadReconSocket, NULL, 0, NULL);
		return -1;
	}

	socketIsConnected = true;
	socketThreadHwd = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadFuncRecv, NULL, 0, NULL);
	reconSocketThreadHwd = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadReconSocket, NULL, 0, NULL);
	/*LONG ret = -1;
	char sendbuf[66];
	memset(sendbuf, 0, 66);
	sendbuf[0] = 0xFF;
	sendbuf[1] = 0xFF;
	sendbuf[2] = CMDLOGIN;
	sendbuf[3] = 58;
	memcpy(&sendbuf[4], sDVRIP, strlen(sDVRIP));
	sendbuf[20] = wDVRPort % 256;
	sendbuf[21] = wDVRPort / 256;
	memcpy(&sendbuf[22], sUserName, strlen(sUserName));
	memcpy(&sendbuf[42], sPassWord, strlen(sPassWord));
	sendbuf[62] = 0x00;
	sendbuf[63] = 0x00;
	sendbuf[64] = 0xEE;
	sendbuf[65] = 0xEE;
	send(sclient, &sendbuf[0], 66, 0);
	ResetEvent(loginEvent);
	DWORD dw = WaitForSingleObject(loginEvent, 3000);
	char info[128] = "NET_DVR_Login_V30 :";
	switch (dw)
	{
	case WAIT_OBJECT_0:
		ret = 0;
		write_log_file("NET_DVR_Login_V30 SUCCESS", strlen("NET_DVR_Login_V30 SUCCESS"));
		break;
	case WAIT_TIMEOUT:
		lastError = 0;
		write_log_file("NET_DVR_Login_V30 WAIT_TIMEOUT", strlen("NET_DVR_Login_V30 WAIT_TIMEOUT"));
		break;
	case WAIT_FAILED:
		write_log_file("NET_DVR_Login_V30 WAIT_FAILED", strlen("NET_DVR_Login_V30 WAIT_FAILED"));
		break;
	}*/
	bLoginIn = true;
	write_log_file("NET_DVR_Login_V30 SUCCESS", strlen("NET_DVR_Login_V30 SUCCESS"));
	return 0;
}
HCNETSDK_API BOOL NET_DVR_Logout(LONG lUserID)
{
	bLoginIn = false;
	write_log_file("NET_DVR_Logout SUCCESS", strlen("NET_DVR_Logout SUCCESS"));
	return true;
}
HCNETSDK_API BOOL NET_DVR_ManualSnap(LONG lUserID,NET_DVR_MANUALSNAP * lpInter,LPNET_DVR_PLATE_RESULT lpOuter)
{
	write_log_file("NET_DVR_ManualSnap Begin", strlen("NET_DVR_ManualSnap Begin"));
	bool ret = false;
	if (socketIsConnected && sclient != NULL )
	{
		failSendCount++;
		if (failSendCount > 2)
		{
			socketIsConnected = false;
			failSendCount = 0;
		}
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
		//char info[128] = "Snap Result Plate:";
		char info[128];
		memset(info, 0, 128);
		strcpy(info + strlen(info), "  PumpID:");
		_itoa(curSnapResult.byPumpID, info + strlen(info), 10);
		strcpy(info + strlen(info), "  PumpStatus:");
		_itoa(curSnapResult.byPumpStatus, info + strlen(info), 10);
		write_log_file(info, strlen(info));
		DWORD dw = WaitForSingleObject(snapEvent, 3000);
		
		switch (dw)
		{
		case WAIT_OBJECT_0:
			failSendCount = 0;
			memcpy(lpOuter, &curSnapResult, sizeof(NET_DVR_PLATE_RESULT));
			ret = true;
			memset(info, 0, 128);
			strcpy(info, "车牌号:");
			strcpy(info + strlen(info),curSnapResult.sLicense);
			write_log_file(info, strlen(info));
			//write_log_file(curSnapResult.sLicense, strlen(curSnapResult.sLicense));
			write_log_file("NET_DVR_ManualSnap SUCCESS", strlen("NET_DVR_ManualSnap SUCCESS"));
			return true;
			break;
		case WAIT_TIMEOUT:
			lastError = -2;
			write_log_file("snap WAIT_TIMEOUT", strlen("snap WAIT_TIMEOUT"));
			break;
		case WAIT_FAILED:
			lastError = -3;
			write_log_file("snap WAIT_FAILED", strlen("snap WAIT_FAILED"));
			break;
		}
	}
	return false;
	
}
HCNETSDK_API BOOL NET_DVR_SetDVRMessageCallBack_V31(MSGCallBack_V31 fMessageCallBack, void* pUser)
{
	
	msgCallBack_V31 = fMessageCallBack;
	write_log_file("NET_DVR_SetDVRMessageCallBack_V31 SUCCESS", strlen("NET_DVR_SetDVRMessageCallBack_V31 SUCCESS"));
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
	write_log_file("NET_DVR_SetConnectTime SUCCESS", strlen("NET_DVR_SetConnectTime SUCCESS"));
	return true;
	
}
HCNETSDK_API BOOL NET_DVR_SetReconnect(DWORD  dwInterval,BOOL  bEnableRecon)
{
	dwReconInterval = dwInterval;
	bReconnetSocket = bEnableRecon;
	write_log_file("NET_DVR_SetReconnect SUCCESS", strlen("NET_DVR_SetReconnect SUCCESS"));
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
	return lastError;
}
HCNETSDK_API BOOL NET_DVR_SendTrans(NET_ITS_TRANS_INFO tradeInfo)
{
	write_log_file("NET_DVR_SendTrans Begin", strlen("NET_DVR_SendTrade Begin"));
	bool ret = false;
	if (socketIsConnected && sclient != NULL)
	{
		failSendCount++;
		if (failSendCount > 2)
		{
			socketIsConnected = false;
			failSendCount = 0;
		}
		//NET_ITS_TRADE_INFO info;
		//memcpy(&info, tradeInfo, sizeof(info));
		int dataLenth = sizeof(tradeInfo);
		char sendbuf[76];
		sendbuf[0] = 0xFF;
		sendbuf[1] = 0xFF;
		sendbuf[2] = CMDTRADE;
		sendbuf[3] = dataLenth;
		memcpy(&sendbuf[4], &tradeInfo, dataLenth);
		sendbuf[dataLenth+4] = 0;
		sendbuf[dataLenth + 5] = 0;
		sendbuf[dataLenth + 6] = 0xEE;
		sendbuf[dataLenth + 7] = 0xEE;
		send(sclient, &sendbuf[0], dataLenth + 8, 0);
		ret = true;
	}
	return ret;
}





