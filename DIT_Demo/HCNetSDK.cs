using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
namespace DIT_Demo
{
    class HCNetSDK
    {
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_Init();
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_Cleanup();
        //[DllImport("HCNetSDK.dll")]
        //public static extern  int NET_DVR_Login_V30(string DVRIP,ushort wDVRPort,string sUserName,string sPassWord,LPNET_DVR_DEVICEINFO_V30 lpDeviceInfo);
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_Logout(uint lUserID);
        //[DllImport("HCNetSDK.dll")]
        //public static extern bool NET_DVR_ManualSnap(uint lUserID,NET_DVR_MANUALSNAP const* lpInter,LPNET_DVR_PLATE_RESULT lpOuter);
        //[DllImport("HCNetSDK.dll")]
        //public static extern bool NET_DVR_SetDVRMessageCallBack_V31(MSGCallBack_V31 fMessageCallBack,void* pUser);
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_SetConnectTime(int dwWaitTime,int dwTryTimes);
        [DllImport("HCNetSDK.dll")]
        public static extern bool NET_DVR_SetReconnect(int dwInterval,bool bEnableRecon);
        [DllImport("HCNetSDK.dll")]
        public static extern void NET_DVR_TestAPI();
    }
}
