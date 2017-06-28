using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace DIT_Server
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct NET_ITS_TRANS_INFO
    {
        public int nPumpID;  //油枪ID
        public int nOilType;                  //油品编码
        public float fTradeLitre;                      //交易升数
        public float fTradeMoney;                      //交易金额
        public float fTradePrice;                      //交易单价
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public byte[] sStartTime;    //提枪时间
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public byte[] sEndTime;     //挂枪时间
        public float fStartRead;       //提枪泵码
        public float fEndRead;         //挂枪泵码
    }
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
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct struLoginInfo
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] byIP;     
        public ushort wPort;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public byte[] byLoginName;     
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
        public byte[] byPassword;     
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
        public static uint WM_CARTRADE = RegisterWindowMessage("CARTRADE");    //抓拍
        //public static NET_DVR_PLATE_RESULT carInfo = new NET_DVR_PLATE_RESULT();
        public static byte byNozzle = 0;
        public static byte byNozzleStatus = 0;
        public const int HWND_BROADCAST = 0xFFFF;
        public static NET_ITS_TRANS_INFO tradeInfo = new NET_ITS_TRANS_INFO();
        // 将byte[]转换为struct
        public static object BytesToStruts(byte[] bytes, Type type)
        {
            //得到结构体的大小
            int size = Marshal.SizeOf(type);
            //byte数组长度小于结构体的大小
            if (size > bytes.Length)
            {
                //返回空
                return null;
            }
            //分配结构体大小的内存空间
            IntPtr structPtr = Marshal.AllocHGlobal(size);
            //将byte数组拷到分配好的内存空间
            Marshal.Copy(bytes, 0, structPtr, size);
            //将内存空间转换为目标结构体
            object obj = Marshal.PtrToStructure(structPtr, type);
            //释放内存空间
            Marshal.FreeHGlobal(structPtr);
            //返回结构体
            return obj;
        }
    }
}
