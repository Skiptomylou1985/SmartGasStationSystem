using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace SPManager
{
    //定义CPU的信息结构  
    [StructLayout(LayoutKind.Sequential,Pack =1)]
    public struct CPU_INFO
    {
        public uint dwOemId;
        public uint dwPageSize;
        public uint lpMinimumApplicationAddress;
        public uint lpMaximumApplicationAddress;
        public uint dwActiveProcessorMask;
        public uint dwNumberOfProcessors;
        public uint dwProcessorType;
        public uint dwAllocationGranularity;
        public uint dwProcessorLevel;
        public uint dwProcessorRevision;
    }
    //定义内存的信息结构  
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct MEMORY_INFO
    {
        public uint dwLength;
        public uint dwMemoryLoad;
        public uint dwTotalPhys;
        public uint dwAvailPhys;
        public uint dwTotalPageFile;
        public uint dwAvailPageFile;
        public uint dwTotalVirtual;
        public uint dwAvailVirtual;
    }
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct struArea
    {
        public int areaNo;
        public int videoChanNo;
        public int left;
        public int top;
        public int right;
        public int bottom;
        public int videoLaneNo;  //视频通道中的识别区号
    }
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct struNozzleRecog
    {
        public int nozzleNo;
        public int videoChan;
        public int areaCount;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public struArea[] areas;
    }
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct struVideoChan
    {
        public int chanNo;
        public int videoType;  //视频通道类型  0 加油岛  1 入口  2 出口
        public int areaCount;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public struArea[] areas;
    }
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct struCarInfoOut
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] license;   // 车牌字符串
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] color;      // 车牌颜色
        public int nColor;         // 车牌颜色
        public int nType;          // 车牌类型
        public int nConfidence;    // 整牌可信度
        public int nCarColor;      //车的颜色
        public int nCarLogo;         //车标类型
        public int nSubCarLogo;         //车辆品牌
        public int nCarModel;           //车辆类型，已弃用
        public int nVideoChannel;  //识别视频通道
        public int nAreaNo;
        public int nPicType;       //图片类型
        public int nPicWidth;
        public int nPicHeight;
        public int nPicLenth;
        //[MarshalAs(UnmanagedType.ByValArray, SizeConst = 10 * 1024 * 1024)]
        //public byte[] pic;

    }
    public struct struCarInfoOut_V2
    {
        public int nLicenseCount;
        public int nVideoChannel;  //识别视频通道
        public int nPicType;       //图片类型
        public int nPicWidth;
        public int nPicHeight;
        public int nPicLenth;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public struLicense[] license;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10 * 1024 * 1024)]
        public byte[] pic;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
        public byte[] picName;

    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct struLicense
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public byte[] license;   // 车牌字符串
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public byte[] color;      // 车牌颜色
        public int nColor;         // 车牌颜色
        public int nType;          // 车牌类型
        public int nConfidence;    // 整牌可信度
        public int nCarColor;      //车的颜色
        public int nCarLogo;         //车标类型
        public int nSubCarLogo;         //车辆品牌
        public int nCarModel;           //车辆类型，已弃用
        public int nAreaNo;
    }


    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct struPic
    {
        public string sPicPath;
        public int nPicType;
        public int nSaveType;
        public int nWidth;
        public int nHeight;
        public int nLenth;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10 * 1024 * 1024)]
        public byte[] brPicBuffer;
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

}
