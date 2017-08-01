// SPlate_xj.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "SPlate_xj.h"
#include <process.h>
SOCKET sclient = NULL;
bool socketIsConnected = false;
char recData[2048];
char jsonBuf[2048];
char ip[30];
int nFailSendCount = 0;
int nAreaCount = 0;
int nNozzleCount = 0;
int nVideoChanCount = 0;
int nLogLevel = 3;
int nCurCarCount = 0;
int nCurAreaIndex = 0;
int nDefaultStratChan = 33;
int nDefaultImageWidth = 1280;
int nDefaultImageHeight = 720;
char debugInfo[256];
int port;
bool bReconnetSocket = true;
DWORD dwReconInterval = 10000;
uintptr_t socketThreadHwd = NULL;
uintptr_t reconSocketThreadHwd = NULL;
HANDLE snapEvent = NULL;
struMultiCarInfoOut curSnapResult;
struSingleCarInfoOut areaCar[MAX_AREA_COUNT];
struNozzleInfo nozzleInfo[MAX_NOZZLE_COUNT];
struVideoInfo videoInfo[MAX_VIDEO_CHANNEL_COUNT];
StationIOInfo curStationIOInfo;
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

short getCRC16(unsigned char *buff, int offset, int lenth)
{
	return 0;
}
void _stdcall ThreadFuncRecv(LPVOID lpParam)
{
	while (socketIsConnected)
	{
		int len = recv(sclient, recData, 2048, 0);
		if (len > 9)
		{
			unsigned char buffer[2048];
			memcpy(buffer, recData, len);
			
			if (buffer[0] == 0xff && buffer[1] == 0xff&&(buffer[2] == 0x12||buffer[2] == 0x11))
			{
				int dataLenth = buffer[3] + buffer[4] * 256;
				short crc = getCRC16(buffer, 0, dataLenth + 5);
				if (true)
					//if (crc = buffer[dataLenth + 5] + buffer[dataLenth + 6] * 256)
				{
					
					memset(jsonBuf, 0, 2048);
					memcpy(&jsonBuf, &buffer[5], dataLenth);
					cJSON *root = cJSON_Parse(jsonBuf);
					write_log_file("Json.txt", MAX_FILE_SIZE, jsonBuf, strlen(jsonBuf), 3);
					cJSON *item;
					cJSON *object;
					item = cJSON_GetObjectItem(root, "WellPetrolInfo");
					if (strcmp("PetrolIsleQueryErr",item->valuestring) == 0) //返回失败指令
					{
						object = cJSON_GetObjectItem(root, "WellPetrolErrCode");
						memset(debugInfo, 0, 256);
						strcpy(debugInfo, "PetrolIsleQueryErr WellPetrolErrCode:");
						strcpy(debugInfo + strlen(debugInfo), object->valuestring);
						write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
						SetEvent(snapEvent);
					}
					else
					{
						memset(&curStationIOInfo, 0, sizeof(curStationIOInfo));
						item = cJSON_GetObjectItem(root, "StationIOInfo");
						object = cJSON_GetObjectItem(item, "plate_no");
						if (strlen(object->valuestring) >= 7)
						{
							//char plate[15];
							//char *plate;
							strcpy(curStationIOInfo.plateNo, object->valuestring);
							object = cJSON_GetObjectItem(item, "plate_roi");
							int roi[4] = {0,0,0,0};
							char sroi[30];
							strcpy(sroi, object->valuestring);
							int offset = 0;
							for (int i=0;i<strlen(sroi);i++)
							{
								if (sroi[i] >='0' && sroi[i] <='9')
								{
									roi[offset] = roi[offset] * 10 + (sroi[i]-'0');
								}
								else
								{
									offset++;
								}
								if (offset > 3)
								{
									break;
								}
							}
							curStationIOInfo.rect.left = roi[0];
							curStationIOInfo.rect.top = roi[1];
							curStationIOInfo.rect.right = roi[2];
							curStationIOInfo.rect.bottom = roi[3];
							object = cJSON_GetObjectItem(item, "plate_color");
							strcpy(curStationIOInfo.plateColor, object->valuestring);
							object = cJSON_GetObjectItem(item, "plate_img_height");
							curStationIOInfo.nImageHeight=atoi(object->valuestring);
							object = cJSON_GetObjectItem(item, "plate_img_width");
							curStationIOInfo.nImageWidth = atoi(object->valuestring);
							object = cJSON_GetObjectItem(item, "car_brand");
							strcpy(curStationIOInfo.carBrand, object->valuestring);
							object = cJSON_GetObjectItem(item, "sub_car_brand");
							strcpy(curStationIOInfo.subCarBrand, object->valuestring);
							object = cJSON_GetObjectItem(item, "move_status");
							strcpy(curStationIOInfo.moveStatus, object->valuestring);
							object = cJSON_GetObjectItem(item, "img_path");
							strcpy(curStationIOInfo.imagePath, object->valuestring);
							object = cJSON_GetObjectItem(item, "remarks");
							strcpy(curStationIOInfo.remark, object->valuestring);



							memset(debugInfo, 0, 256);
							strcpy(debugInfo, "Plate:");
							strcpy(debugInfo + strlen(debugInfo), curStationIOInfo.plateNo);
							strcpy(debugInfo + strlen(debugInfo), "  Rect left:");
							_itoa(curStationIOInfo.rect.left, debugInfo + strlen(debugInfo), 10);
							strcpy(debugInfo + strlen(debugInfo), " right:");
							_itoa(curStationIOInfo.rect.right, debugInfo + strlen(debugInfo), 10);
							strcpy(debugInfo + strlen(debugInfo), " top:");
							_itoa(curStationIOInfo.rect.top, debugInfo + strlen(debugInfo), 10);
							strcpy(debugInfo + strlen(debugInfo), " bottom:");
							_itoa(curStationIOInfo.rect.bottom, debugInfo + strlen(debugInfo), 10);
							write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);


							item = cJSON_GetObjectItem(root, "AdditionalInfo");
							if (nullptr != item)
							{
								object = cJSON_GetObjectItem(item, "camera_code");
								strcpy(curStationIOInfo.cameraCode, object->valuestring);
								object = cJSON_GetObjectItem(item, "detection_area");
								strcpy(curStationIOInfo.detectionArea, object->valuestring);
								object = cJSON_GetObjectItem(item, "token");
								strcpy(curStationIOInfo.token, object->valuestring);
								object = cJSON_GetObjectItem(item, "station_code");
								strcpy(curStationIOInfo.stationCode, object->valuestring);
								object = cJSON_GetObjectItem(item, "camera_type");
								strcpy(curStationIOInfo.cameraType, object->valuestring);
								object = cJSON_GetObjectItem(item, "timestamp");
								strcpy(curStationIOInfo.timestamp, object->valuestring);

								memset(debugInfo, 0, 256);
								strcpy(debugInfo, "camera_code:");
								strcpy(debugInfo + strlen(debugInfo), curStationIOInfo.cameraCode);
								strcpy(debugInfo + strlen(debugInfo), "  token:");
								strcpy(debugInfo + strlen(debugInfo), curStationIOInfo.token);
								write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);

							}
							if (buffer[2] = 0x12)
							{
								int tempVideoNo = -1;
								if (strcmp(curStationIOInfo.cameraCode, "CAM003") == 0)
									tempVideoNo = 0;
								else if (strcmp(curStationIOInfo.cameraCode, "CAM002") == 0)
									tempVideoNo = 3;
								else if (strcmp(curStationIOInfo.cameraCode, "CAM001") == 0)
									tempVideoNo = 14;
								else if (strcmp(curStationIOInfo.cameraCode, "CAM000") == 0)
									tempVideoNo = 1;
								if (tempVideoNo >=0)
								{
									memset(debugInfo, 0, 256);
									strcpy(debugInfo, "Match VideoNo:");
									_itoa(tempVideoNo, debugInfo + strlen(debugInfo), 10);
									write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);

									for (int j=0;j<nVideoChanCount;j++)
									{
										if (tempVideoNo == videoInfo[j].nChanNo)
										{
											for (int k=0;k<videoInfo[j].nAreaCount;k++)
											{

												memset(debugInfo, 0, 256);
												strcpy(debugInfo, "match area:");
												strcpy(debugInfo + strlen(debugInfo), " left:");
												_itoa(videoInfo[j].areas[k].th_rect.left, debugInfo + strlen(debugInfo), 10);
												strcpy(debugInfo + strlen(debugInfo), " right:");
												_itoa(videoInfo[j].areas[k].th_rect.right, debugInfo + strlen(debugInfo), 10);
												strcpy(debugInfo + strlen(debugInfo), " top:");
												_itoa(videoInfo[j].areas[k].th_rect.top, debugInfo + strlen(debugInfo), 10);
												strcpy(debugInfo + strlen(debugInfo), " bottom:");
												_itoa(videoInfo[j].areas[k].th_rect.bottom, debugInfo + strlen(debugInfo), 10);
												write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
												if (curStationIOInfo.rect.left > videoInfo[j].areas[k].th_rect.left &&
													curStationIOInfo.rect.right < videoInfo[j].areas[k].th_rect.right &&
													curStationIOInfo.rect.top >videoInfo[j].areas[k].th_rect.top &&
													curStationIOInfo.rect.bottom < videoInfo[j].areas[k].th_rect.bottom)
												{
													
													int areaNo = videoInfo[j].areas[k].areaNo;
													memset(debugInfo, 0, 256);
													strcpy(debugInfo, "Match AreaNo:");
													_itoa(areaNo, debugInfo + strlen(debugInfo), 10);
													write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
													memset(&areaCar[areaNo - 1], 0, sizeof(areaCar[areaNo - 1]));
													memcpy(areaCar[areaNo - 1].license, curStationIOInfo.plateNo, strlen(curStationIOInfo.plateNo));
													//memcpy(areaCar[areaNo - 1].color, Result[i].color, 8);
													//memcpy(areaCar[index - 1].pic, pBuf, nSize);
// 													areaCar[areaNo - 1].nCarColor = Result[i].nCarColor;
// 													areaCar[areaNo - 1].nCarLogo = Result[i].nCarLogo;
// 													areaCar[areaNo - 1].nSubCarLogo = Result[i].nCarType;
// 													areaCar[areaNo - 1].nCarModel = Result[i].nCarModel;
// 													areaCar[areaNo - 1].nColor = Result[i].nColor;
// 													areaCar[areaNo - 1].nConfidence = Result[i].nConfidence;
// 													areaCar[areaNo - 1].nPicLenth = nSize;
													areaCar[areaNo - 1].nVideoChannel = videoInfo[j].nChanNo;
													areaCar[areaNo - 1].nAreaNo = areaNo;
													areaCar[areaNo - 1].nPicType = -1;
													areaCar[areaNo - 1].nPicWidth = curStationIOInfo.nImageWidth;
													areaCar[areaNo - 1].nPicHeight = curStationIOInfo.nImageHeight;
													
													PostMessage(HWND_BROADCAST, WM_AREACAR, areaNo, videoInfo[j].nChanNo);
													break;
												}
											}
											break;
										}
									}
								}

							}
							else if (buffer[2] = 0x11)
							{
								memcpy(curSnapResult.license, object->valuestring, strlen(object->valuestring));
								curSnapResult.nLicenseCount = 1;
							}
						}
						else
						{
							memset(debugInfo, 0, 256);
							strcpy(debugInfo, "Error Plate:");
							strcpy(debugInfo + strlen(debugInfo), object->valuestring);
							write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
						}
					}

					cJSON_Delete(root);
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
			//write_log_file("socket reconnect", strlen("socket reconnect"));

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

//				write_log_file("socket reconnect fail", strlen("socket reconnect fail"));
			}
			else
			{
				socketIsConnected = true;
				socketThreadHwd = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadFuncRecv, NULL, 0, NULL);
		//		write_log_file("socket reconnect success", strlen("socket reconnect success"));
			}
		}
	}
}

int SendSnapToXJ(int nozzleNo)
{
	int nLicCount = 0;
	int index = -1;
	for (int i = 0; i < nNozzleCount; i++)
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
	return 0;
}
SPLATE_API int SP_InitRunParam(BYTE *pChan, int areaCount)
{
	return 0;
}
SPLATE_API int SP_InitRunParam_Nozzle(unsigned char *pNozzleInfo, int nozzleCount)
{
	//memset(&tempCarOut, 0, sizeof(tempCarOut));
	if (nozzleCount > MAX_NOZZLE_COUNT)
	{
		return INVALID_NOZZLE_COUNT;
	}
	memcpy(nozzleInfo, pNozzleInfo, nozzleCount * sizeof(struNozzleInfo));
	nNozzleCount = nozzleCount;
	for (int i = 0; i < nNozzleCount; i++)
	{
		//nozzleInfo[i].videoChan += struIPPARACFG.dwStartDChan;

		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo, "index：");
		_itoa(i, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), "nozzleNo：");
		_itoa(nozzleInfo[i].nozzleNo, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " video：");
		_itoa(nozzleInfo[i].videoChan, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " areaCount：");
		_itoa(nozzleInfo[i].areaCount, debugInfo + strlen(debugInfo), 10);
		for (int j = 0; j < nozzleInfo[i].areaCount; j++)
		{
			strcpy(debugInfo + strlen(debugInfo), " areaId：");
			_itoa(nozzleInfo[i].areas[j].areaNo, debugInfo + strlen(debugInfo), 10);
			strcpy(debugInfo + strlen(debugInfo), " rect：left ");
			_itoa(nozzleInfo[i].areas[j].th_rect.left, debugInfo + strlen(debugInfo), 10);
			strcpy(debugInfo + strlen(debugInfo), " right ");
			_itoa(nozzleInfo[i].areas[j].th_rect.right, debugInfo + strlen(debugInfo), 10);
			strcpy(debugInfo + strlen(debugInfo), " top ");
			_itoa(nozzleInfo[i].areas[j].th_rect.top, debugInfo + strlen(debugInfo), 10);
			strcpy(debugInfo + strlen(debugInfo), " bottom ");
			_itoa(nozzleInfo[i].areas[j].th_rect.bottom, debugInfo + strlen(debugInfo), 10);
		}

		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);

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
	return SUCCESS;
}
SPLATE_API int SP_InitNVR(char *IpAddress, LONG nPort, char *sAdmin, char *sPassword)
{
	snapEvent = CreateEvent(NULL, false, true, NULL);
	memcpy(ip, IpAddress, strlen(IpAddress));
	port = nPort;
	sclient = getSocketConnect(IpAddress, nPort);
	bReconnetSocket = true;
	if (NULL == sclient)
	{
		reconSocketThreadHwd = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadReconSocket, NULL, 0, NULL);
		return -1;
	}

	socketIsConnected = true;
	socketThreadHwd = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadFuncRecv, NULL, 0, NULL);
	reconSocketThreadHwd = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)ThreadReconSocket, NULL, 0, NULL);
	return 0;
}
SPLATE_API int SP_GetNvrCfg(BYTE *nvrCfg, int &lenth)
{
	return 0;
}
SPLATE_API int SP_Close()
{
	return 0;
}
SPLATE_API int SP_PreviewInfo(BYTE *preInfo, int lenth)
{
	return 0;
}
SPLATE_API int SP_StopPreview(LONG lplayHandle)
{
	return 0;
}
SPLATE_API int SP_BeginRecog()
{
	return 0;
}
SPLATE_API int SP_InitAlg(BYTE *th_plateIDCfg, int lenth)
{
	return 0;
}
SPLATE_API int SP_TestAPI()
{
	return 0;
}
SPLATE_API int SP_GetCarCount()
{
	return 0;
}
SPLATE_API int SP_GetFirstCarInfo(struSingleCarInfoOut *carinfo, int &lenth)
{
	return 0;
}
SPLATE_API int SP_GetCarInfo(struSingleCarInfoOut *carinfo, int carCount, int &lenth)
{
	return 0;
}
SPLATE_API int SP_GetAreaCarInfo(struSingleCarInfoOut *carinfo, int areaNo)
{
	if (areaNo > 0 && areaNo <= MAX_AREA_COUNT)
	{
		memcpy(carinfo, &areaCar[areaNo - 1], sizeof(struSingleCarInfoOut));
		//areaCar[areaNo - 1].nConfidence = 0;
		//memset(areaCar[areaNo - 1].license, 0, 16);
	}
	else
		return INVALID_AREA_COUNT;
}
SPLATE_API int SP_GetNvrStatus()
{
	return INVALID_METHOD;
}
SPLATE_API int SP_SetLogLevel(int loglevel)
{
	nLogLevel = loglevel;
	set_log_level(loglevel);
	return SUCCESS;
}
SPLATE_API int SP_SetSwitchCount(int frameCount)
{
	return INVALID_METHOD;
}
SPLATE_API int SP_Snap(int videoChan, char *lic, unsigned char * picBuffer, int &picLenth)
{
	return INVALID_METHOD;
}
SPLATE_API int SP_Capture(int areaNo, struSingleCarInfoOut *carinfo)
{
	return INVALID_METHOD;
}
SPLATE_API int SP_Capture_V2(int nozzleNo, struMultiCarInfoOut *carInfo)
{
	ResetEvent(snapEvent);
	if (SUCCESS == SendSnapToXJ(nozzleNo))
	{
		
		DWORD dw = WaitForSingleObject(snapEvent, 3000);

		switch (dw)
		{
		case WAIT_OBJECT_0:
			nFailSendCount = 0;
			memcpy(carInfo, &curSnapResult, sizeof(curSnapResult));
// 			memset(info, 0, 128);
// 			strcpy(info, "车牌号:");
// 			strcpy(info + strlen(info), curSnapResult.sLicense);
// 			write_log_file(info, strlen(info));
			//write_log_file(curSnapResult.sLicense, strlen(curSnapResult.sLicense));
			//write_log_file("NET_DVR_ManualSnap SUCCESS", strlen("NET_DVR_ManualSnap SUCCESS"));
			return true;
			break;
		case WAIT_TIMEOUT:
			
			break;
		case WAIT_FAILED:
			
			break;
		}
	}
	
}
SPLATE_API int SP_DecJpeg(const unsigned char * pJpegPic, int nJpegLenth, char *license)
{
	return INVALID_METHOD;
}
SPLATE_API int SP_InitNVR_HKCN(char *IpAddress, LONG nPort, char *sAdmin, char *sPassword)
{
	return INVALID_METHOD;
}




