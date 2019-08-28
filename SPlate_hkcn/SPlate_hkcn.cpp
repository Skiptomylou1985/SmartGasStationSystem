// SPlate_hkcn.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "SPlate_hkcn.h"

//硬盘录像机相关
NET_DVR_DEVICEINFO_V30 deviceInfo;
NET_DVR_PREVIEWINFO previewInfo;
struNVRInfo nvrInfo;
LONG testBufferSize;
LONG callBackNum;
NET_DVR_USER_LOGIN_INFO loginInfo_hkcn;
NET_DVR_DEVICEINFO_V40 deviceInfo_hkcn;
NET_ITS_PLATE_RESULT struItsPlateResult;
//TH_PlateIDCfg th_PlateIDCfg_bak;
int nCarNum;
LONG nPort = -1;
const int XML_ABILITY_OUT_LEN = 3 * 1024 * 1024;


int nAlgStatus = 0;
int nCurGetIndex = 0;
int nCurPutIndex = 0;
int nCodeType = 1; //编码方式  1:utf-8  2:gbk
struSingleCarInfoOut carInfoOut[MAX_CAR_COUNT];
struSingleCarInfoOut tempCarOut;
struMultiCarInfoOut carOutCache;
unsigned char *videoChan[MAX_VIDEO_CHANNEL_COUNT];
struPlayInfo playInfo[MAX_VIDEO_CHANNEL_COUNT];
struAreaInfo areaInfo[MAX_AREA_COUNT];
struNozzleInfo nozzleInfo[MAX_NOZZLE_COUNT];
struVideoInfo videoInfo[MAX_VIDEO_CHANNEL_COUNT];
struSingleCarInfoOut areaCar[MAX_AREA_COUNT];
int nAreaCount = 0;
int nNozzleCount = 0;
int nVideoChanCount = 0;
int nLogLevel = 3;
int nDefaultStratChan = 33;
int nDefaultImageWidth = 1920;
int nDefaultImageHeight = 1080;
char debugInfo[512];
NET_DVR_IPPARACFG_V40 struIPPARACFG;
bool isRecog = false;
int nSwitchCount = 10;
char *lastLicense[MAX_AREA_COUNT];
int nSwithFlag;
uintptr_t ThreadSwith = NULL;
bool bSwitchComplete = false;
int nframeCount;
char pBuffer[MAX_PIC_LENTH];
char outBuf[XML_ABILITY_OUT_LEN];
NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
void CALLBACK PlateDataCallBack(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void *pUser)
{
// 	memset(debugInfo, 0, sizeof(debugInfo));
// 	strcpy(debugInfo, "lCommand:");
// 	_itoa(lCommand, debugInfo + strlen(debugInfo), 10);
// 	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	int areaNo = -1;
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
		memset(&struItsPlateResult, 0, sizeof(struItsPlateResult));
		memcpy(&struItsPlateResult, pAlarmInfo, sizeof(struItsPlateResult));
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo + strlen(debugInfo), "回调车牌:");
		memcpy(debugInfo + strlen(debugInfo), struItsPlateResult.struPlateInfo.sLicense, strlen(struItsPlateResult.struPlateInfo.sLicense));
		strcpy(debugInfo + strlen(debugInfo), " 识别通道:");
		_itoa(struItsPlateResult.byChanIndex, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " 通道识别区号:");
		_itoa(struItsPlateResult.byDriveChan, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " 车辆品牌代码:");
		_itoa(struItsPlateResult.struVehicleInfo.wVehicleLogoRecog, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " 车辆子品牌代码:");
		_itoa(struItsPlateResult.struVehicleInfo.byVehicleSubLogoRecog, debugInfo + strlen(debugInfo), 10);
		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo + strlen(debugInfo), "匹配识别区 -->> nVideoChanCount:");
		_itoa(nVideoChanCount, debugInfo + strlen(debugInfo), 10);
		write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);

		for (int i=0;i<nVideoChanCount;i++)
		{
			memset(debugInfo, 0, sizeof(debugInfo));
			strcpy(debugInfo + strlen(debugInfo), "匹配识别区 -->> nChanNo:");
			_itoa(videoInfo[i].nChanNo, debugInfo + strlen(debugInfo), 10);
			strcpy(debugInfo + strlen(debugInfo), "， byChanIndex:");
			_itoa(struItsPlateResult.byChanIndex, debugInfo + strlen(debugInfo), 10);
			write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
			if (videoInfo[i].nChanNo == struItsPlateResult.byChanIndex)
			{
				for (int j=0;j<videoInfo[i].nAreaCount;j++)
				{
					memset(debugInfo, 0, sizeof(debugInfo));
					strcpy(debugInfo + strlen(debugInfo), "匹配识别区 -->> videoLaneNo:");
					_itoa(videoInfo[i].areas[j].videoLaneNo, debugInfo + strlen(debugInfo), 10);
					strcpy(debugInfo + strlen(debugInfo), "， byDriveChan:");
					_itoa(struItsPlateResult.byDriveChan, debugInfo + strlen(debugInfo), 10);
					write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
					if (videoInfo[i].areas[j].videoLaneNo == struItsPlateResult.byDriveChan)
					{
						areaNo = videoInfo[i].areas[j].areaNo;
						break;
					}
				}
				break;
			}
		}
		if (areaNo < 0)
		{
			write_log_file("Debug.txt", MAX_FILE_SIZE, "未找到对应识别区", strlen("未找到对应识别区"), 3);
			return;
		}

		//int plateLenth = strlen(struItsPlateResult.struPlateInfo.sLicense);
		if (strlen(struItsPlateResult.struPlateInfo.sLicense) > 2)
		{
			memcpy(areaCar[areaNo - 1].license, &struItsPlateResult.struPlateInfo.sLicense[2], strlen(struItsPlateResult.struPlateInfo.sLicense) - 2);
			memcpy(areaCar[areaNo - 1].color, &struItsPlateResult.struPlateInfo.sLicense, 2);
		}
		areaCar[areaNo - 1].nCarLogo = struItsPlateResult.struVehicleInfo.wVehicleLogoRecog;
		areaCar[areaNo - 1].nSubCarLogo = struItsPlateResult.struVehicleInfo.byVehicleSubLogoRecog;
		areaCar[areaNo - 1].nCarModel = struItsPlateResult.struVehicleInfo.byVehicleModel;
		areaCar[areaNo - 1].nVideoChannel = struItsPlateResult.byChanIndex;
		areaCar[areaNo - 1].nPicLenth = struItsPlateResult.struPicInfo[0].dwDataLen;
		areaCar[areaNo - 1].nPicType = 0; //JPG
		areaCar[areaNo - 1].nPicHeight = 1080;
		areaCar[areaNo - 1].nPicWidth = 1920;
		PostMessage(HWND_BROADCAST, WM_AREACAR, areaNo, struItsPlateResult.byChanIndex);
		break;
	default:
		break;
	}
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
		nozzleInfo[i].videoChan += nDefaultStratChan;
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
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "SP_InitRunParam_Video  ");
	strcpy(debugInfo + strlen(debugInfo), "videoCount：");
	_itoa(videoCount, debugInfo + strlen(debugInfo), 10);
	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	if (videoCount > MAX_VIDEO_CHANNEL_COUNT)
	{
		return INVALID_VIDEO_COUNT;
	}
	memcpy(videoInfo, pVideoInfo, videoCount * sizeof(struVideoInfo));
	nVideoChanCount = videoCount;
	for (int i = 0; i < nVideoChanCount; i++)
	{
		videoInfo[i].nChanNo += nDefaultStratChan;
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
	write_log_file("Debug.txt", MAX_FILE_SIZE, "初始化成功", strlen("初始化成功"), 3);
	//ret = NET_DVR_SetDVRMessageCallBack_V31((MSGCallBack_V31)PlateDataCallBack, nullptr);
	ret = NET_DVR_SetDVRMessageCallBack_V30((MSGCallBack)PlateDataCallBack, nullptr);
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo + strlen(debugInfo), "NET_DVR_SetDVRMessageCallBack_V30:");
	_itoa(ret, debugInfo + strlen(debugInfo), 10);
	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	NET_DVR_SETUPALARM_PARAM alarm_Param = { 0 };
	alarm_Param.dwSize = sizeof(alarm_Param);
	alarm_Param.byRetVQDAlarmType = true;
	alarm_Param.byRetAlarmTypeV40 = true;
	alarm_Param.byRetDevInfoVersion = true;
	alarm_Param.byAlarmInfoType = 1;
	alarm_Param.byLevel = 1;
	alarm_Param.byDeployType = 0;
	ret =  NET_DVR_SetupAlarmChan_V41(nvrInfo.m_lServerID, &alarm_Param);
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo + strlen(debugInfo), "NET_DVR_SetupAlarmChan_V41:");
	_itoa(ret, debugInfo + strlen(debugInfo), 10);

	if (ret != 0)
	{
		ret = NET_DVR_GetLastError();
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo + strlen(debugInfo), "NET_DVR_GetLastError:");
		_itoa(ret, debugInfo + strlen(debugInfo), 10);
	}

	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	return SUCCESS;
}
SPLATE_API int SP_GetNvrCfg(BYTE *nvrCfg, int &lenth)
{
	DWORD dwReturn = 0;
	NET_DVR_GetDVRConfig(nvrInfo.m_lServerID, NET_DVR_GET_IPPARACFG_V40, 0, &struIPPARACFG, sizeof(struIPPARACFG), &dwReturn);
	lenth = sizeof(struIPPARACFG);
	memcpy(nvrCfg, &struIPPARACFG, sizeof(struIPPARACFG));
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
	FILE *fp = NULL;
	int i = 0;
	char buffer[2048] = { 0 }; // char 数组，存放结果
	if ((fp = fopen("C:\\plate.txt", "r")) == NULL) {
		return 1;
	}
	while (i < 2048) // 这是为了防止文件长度大于BUFFERSIZE导致崩溃，不然可以写成while(1)
	{
		char ch = fgetc(fp);
		if (ch != EOF)
		{
			buffer[i++] = ch;
		}
		else
		{
			break;   // 到达文件结尾了
		}
	}
	//buffer[i] = '\0';
	fclose(fp);

// 	struInput.dwSize = sizeof(struInput);
// 	struOuput.dwSize = sizeof(struOuput);
// 	char url[100] = "GET /ISAPI/Traffic/channels/33/vehicleDetect/manualTrigger/1";
// 	struInput.lpRequestUrl = url;
// 	struInput.dwRequestUrlLen = strlen(url);
// 	struOuput.dwSize = sizeof(struOuput);
// 	memset(outBuf, 0, XML_ABILITY_OUT_LEN);
// 	struOuput.dwSize = sizeof(NET_DVR_XML_CONFIG_OUTPUT);
// 	struOuput.lpOutBuffer = outBuf;
// 	struOuput.dwOutBufferSize = XML_ABILITY_OUT_LEN;
// 	int ret = NET_DVR_STDXMLConfig(nvrInfo.m_lServerID, &struInput, &struOuput);
// 
// 	memset(debugInfo, 0, sizeof(debugInfo));
// 
// 	strcpy(debugInfo + strlen(debugInfo), "output dwOutBufferSize:");
// 	_itoa(struOuput.dwOutBufferSize, debugInfo + strlen(debugInfo), 10);
// 	strcpy(debugInfo + strlen(debugInfo), " dwReturnedXMLSize:");
// 	_itoa(struOuput.dwReturnedXMLSize, debugInfo + strlen(debugInfo), 10);
// 	write_log_file("manualTrigger.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
// 	write_log_file("manualTrigger.txt", MAX_FILE_SIZE, outBuf, strlen(outBuf), 3);

	CMarkup xml;
	xml.SetDoc(buffer);
	xml.ResetMainPos();
	if (xml.FindElem((MCD_CSTR)"VehicleDetectManualTrigger") && xml.IntoElem())
	{
		if (xml.FindElem((MCD_CSTR)"ANPRList") && xml.IntoElem())
		{

			if (xml.FindElem((MCD_CSTR)"ANPR")&& xml.IntoElem())
			{
				if (xml.FindElem((MCD_CSTR)"licensePlate"))
				{
					char plate[15] = {0};
					CString str = _T("");
					str = xml.GetData();
					int len2 = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
					WideCharToMultiByte(CP_ACP, 0, str, -1, plate, len2, NULL, NULL);
					//char *plate = (char *)strplate.GetBuffer(0);
					//strcpy(plate, (const char*)strplate.GetBuffer(strplate.GetLength()));
					//sprintf(plate, "%s", strPlate);
					char plate2[15];
					strcpy(plate2, &plate[3]);
					write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "xml plate", strlen("xml plate"), 3);
					write_log_file("manualTrigger.txt", MAX_FILE_SIZE, plate, strlen(plate), 3);
				}
				if (xml.FindElem((MCD_CSTR)"confidenceLevel"))
				{
					write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "xml confidenceLevel", strlen("xml confidenceLevel"), 3);
				}
				if (xml.FindElem((MCD_CSTR)"CarFeature")&&xml.IntoElem())
				{
					if (xml.FindElem((MCD_CSTR)"vehicleLogo"))
					{
						write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "xml vehicleLogo", strlen("xml vehicleLogo"), 3);
					}
					if (xml.FindElem((MCD_CSTR)"vehicleSubLogo"))
					{
						write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "xml vehicleSubLogo", strlen("xml vehicleSubLogo"), 3);
					}

				}
			}



		}
	}
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
		areaCar[areaNo - 1].nConfidence = 0;
		memset(areaCar[areaNo - 1].license, 0, 16);
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

SPLATE_API int SP_SetCodeType(int codeType)
{
	nCodeType = codeType;
	return SUCCESS;
}



SPLATE_API int SP_Capture(int nozzleNo, struMultiCarInfoOut *carInfo)
{
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "SP_Capture Start");
	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
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
	memset(&carOutCache, 0, sizeof(carOutCache));
	
	int licIndex = 0;
	for (int i = 0; i < nozzleInfo[index].areaCount; i++)
	{
		char url[100] = "GET /ISAPI/Traffic/channels/";
		_itoa(nozzleInfo[index].videoChan, url + strlen(url), 10);
		strcpy(url + strlen(url), "/vehicleDetect/manualTrigger/");
		struInput.dwSize = sizeof(NET_DVR_XML_CONFIG_INPUT);
		_itoa(nozzleInfo[index].areas[i].videoLaneNo, url + strlen(url), 10);
		write_log_file("manualTrigger.txt", MAX_FILE_SIZE, url, strlen(url), 3);
		struInput.lpRequestUrl = url;
		struInput.dwRequestUrlLen = strlen(url);
		memset(outBuf, 0, XML_ABILITY_OUT_LEN);
		struOuput.dwSize = sizeof(NET_DVR_XML_CONFIG_OUTPUT);
		struOuput.lpOutBuffer = outBuf;
		struOuput.dwOutBufferSize = XML_ABILITY_OUT_LEN;
		write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "NET_DVR_STDXMLConfig", strlen("NET_DVR_STDXMLConfig"), 3);
		int ret = NET_DVR_STDXMLConfig(nvrInfo.m_lServerID, &struInput, &struOuput);
		memset(debugInfo, 0, sizeof(debugInfo));
		strcpy(debugInfo + strlen(debugInfo), "output dwOutBufferSize:");
		_itoa(struOuput.dwOutBufferSize, debugInfo + strlen(debugInfo), 10);
		strcpy(debugInfo + strlen(debugInfo), " dwReturnedXMLSize:");
		_itoa(struOuput.dwReturnedXMLSize, debugInfo + strlen(debugInfo), 10);
		write_log_file("manualTrigger.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
		write_log_file("manualTrigger.txt", MAX_FILE_SIZE, outBuf, strlen(outBuf), 3);
		
		CMarkup xml;
		xml.SetDoc(outBuf);
		xml.ResetMainPos();
		if (xml.FindElem((MCD_CSTR)"VehicleDetectManualTrigger") && xml.IntoElem())
		{
			if (xml.FindElem((MCD_CSTR)"ANPRList") && xml.IntoElem())
			{
				write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "FindElem ANPRList", strlen("FindElem ANPRList"), 3);
				
				if (xml.FindElem((MCD_CSTR)"ANPR") && xml.IntoElem())
				{
					write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "FindElem ANPRList", strlen("FindElem ANPR"), 3);

					if (xml.FindElem((MCD_CSTR)"licensePlate"))
					{
						write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "FindElem licensePlate", strlen("FindElem licensePlate"), 3);
						char plate[15];
						CString str = _T("");
						str = xml.GetData();
						int len2 = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
						WideCharToMultiByte(CP_ACP, 0, str, -1, plate, len2, NULL, NULL);
						if (nCodeType == 1)
						{
							strcpy(carOutCache.license[licIndex].license, &plate[3]);
							memcpy(carOutCache.license[licIndex].color, plate, 3);
						} 
						else
						{
							strcpy(carOutCache.license[licIndex].license, &plate[2]);
							memcpy(carOutCache.license[licIndex].color, plate, 2);
						}
						memset(debugInfo, 0, sizeof(debugInfo));
						strcpy(debugInfo + strlen(debugInfo), "lenth:");
						_itoa(strlen(plate), debugInfo + strlen(debugInfo), 10);
						strcpy(debugInfo + strlen(debugInfo), " plate:");
						strcpy(debugInfo + strlen(debugInfo), plate);
						write_log_file("manualTrigger.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
					}
					if (xml.FindElem((MCD_CSTR)"confidenceLevel"))
					{
						write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "FindElem confidenceLevel", strlen("FindElem confidenceLevel"), 3);
						carOutCache.license[licIndex].nConfidence = _ttoi(xml.GetData())/10; //超脑置信度范围 0-1000，转换为0-100
					}
					if (xml.FindElem((MCD_CSTR)"CarFeature") && xml.IntoElem())
					{
						write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "FindElem CarFeature", strlen("FindElem CarFeature"), 3);

						if (xml.FindElem((MCD_CSTR)"vehicleLogo"))
						{
							write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "FindElem vehicleLogo", strlen("FindElem vehicleLogo"), 3);
							carOutCache.license[licIndex].nCarLogo = _ttoi(xml.GetData());
						}
						if (xml.FindElem((MCD_CSTR)"vehicleSubLogo"))
						{
							write_log_file("manualTrigger.txt", MAX_FILE_SIZE, "FindElem vehicleSubLogo", strlen("FindElem vehicleSubLogo"), 3);
							carOutCache.license[licIndex].nSubCarLogo = _ttoi(xml.GetData());
						}

					}
					carOutCache.license[licIndex].nAreaNo = nozzleInfo[index].areas[i].areaNo;
					carOutCache.nLicenseCount += 1;
					licIndex += 1;
				}
				
			}
		}
	}
	memset(debugInfo, 0, sizeof(debugInfo));
	strcpy(debugInfo, "SP_Capture End");
	write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);
	memcpy(carInfo, &carOutCache, sizeof(carOutCache));
	return 0;
}
