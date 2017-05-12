using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace DIT_Server
{

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct NET_ITS_PLATE_RESULT
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] sLicense;     //车牌号码
        public byte byPlateColor;                  //车牌颜色
        public byte byColor;                       ///车颜色
        public short wVehicleLogoRecog;             ///车品牌
        public short wVehicleSubLogoRecog;          ///子品牌
        public byte byVehicleShape;					///车型
        public byte byVehicleState;              //进出站标识 1进站 2出站
    }
    [StructLayout(LayoutKind.Sequential,Pack =1)]
    public struct NET_DVR_PLATE_RESULT
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] sLicense;     //车牌号码
        public byte byPlateColor;                  //车牌颜色
        public byte byColor;                           ///车颜色
        public short wVehicleLogoRecog;             ///车品牌
        public short wVehicleSubLogoRecog;              ///子品牌
        public byte byVehicleShape;                    ///车型
        public byte byPumpID;                      ///油枪ID
        public byte byPumpStatus;					///油枪状态

    }
    public class SysUnit
    {
        [DllImport("User32.dll", EntryPoint = "PostMessage")]
        public static extern int PostMessage(
            int hWnd,        // handle to destination window
            int Msg,            // message
            int wParam,         // first message parameter
            int lParam          // second message parameter
            );
        [DllImport("user32.dll")]
        static extern uint RegisterWindowMessage(string lpString);
        public static uint WM_CARSNAP = RegisterWindowMessage("CARSNAP");    //抓拍
        //public static NET_DVR_PLATE_RESULT carInfo = new NET_DVR_PLATE_RESULT();
        public static byte byNozzle = 0;
        public static byte byNozzleStatus = 0;
        public const int HWND_BROADCAST = 0xFFFF;
    }
}
