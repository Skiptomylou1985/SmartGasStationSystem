// SPlate_dh.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "SPlate_dh.h"


SPLATE_API int SP_InitRunParam(BYTE *pChan, int areaCount)
{
	return 0;
 }
 SPLATE_API int SP_InitRunParam_Nozzle(unsigned char *pNozzleInfo, int nozzleCount)
 {
	 return 0;
 }
 SPLATE_API int SP_InitRunParam_Video(unsigned char *pVideoInfo, int videoCount)
 {
	 return 0;
 }
 SPLATE_API int SP_InitNVR(char *IpAddress, LONG nPort, char *sAdmin, char *sPassword)
 {
	// char outXML[MAX_OUTXML_LENTH];
	// char debugInfo[256];
	// //write_log_file("Debug.txt", MAX_FILE_SIZE, "SP_InitNVR", strlen("SP_InitNVR"), 3);
	// int ret = CMU_SC_Init();
	///* memset(debugInfo, 0, sizeof(debugInfo));
	// strcpy(debugInfo + strlen(debugInfo), "CMU_SC_Init return value：");
	// _itoa(ret, debugInfo + strlen(debugInfo), 10);
	// write_log_file("Debug.txt", MAX_FILE_SIZE, debugInfo, strlen(debugInfo), 3);*/
	// ret = CMU_SC_Login(2000, "0", IpAddress, nPort, sAdmin, sPassword, &outXML, MAX_OUTXML_LENTH);
	// if (ret != 200)
	// {
	//	 return ret;
	// }
	// CMarkup xml;
	// write_log_file("Debug.txt", MAX_FILE_SIZE, outXML, strlen(outXML), 3);
	// xml.SetDoc((const char*)outXML);
	// xml.ResetMainPos();
	// if (xml.FindElem("root"))
	// {
	//	 xml.IntoElem();
	//	 if (xml.FindElem("handle"))
	//	 {
	//		 int handle = _ttoi(xml.GetData());
	//	 }
	//	 if (xml.FindElem("handle"))
	//	 {
	//		 int handle = _ttoi(xml.GetData());
	//	 }
	// }
	 
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
	 return 0;
 }
 SPLATE_API int SP_GetNvrStatus()
 {
	 return 0;
 }
 SPLATE_API int SP_SetLogLevel(int loglevel)
 {
	 return 0;
 }
 SPLATE_API int SP_SetSwitchCount(int frameCount)
 {
	 return 0;
 }
 SPLATE_API int SP_Snap(int videoChan, char *lic, unsigned char * picBuffer, int &picLenth)
 {
	 return 0;
 }
 SPLATE_API int SP_Capture(int areaNo, struSingleCarInfoOut *carinfo)
 {
	 return 0;
 }
 SPLATE_API int SP_Capture_V2(int nozzleNo, struMultiCarInfoOut *carInfo)
 {
	 return 0;
 }
 SPLATE_API int SP_DecJpeg(const unsigned char * pJpegPic, int nJpegLenth, char *license)
 {
	 return 0;
 }
 SPLATE_API int SP_InitNVR_HKCN(char *IpAddress, LONG nPort, char *sAdmin, char *sPassword)
 {
	 return 0;
 }


