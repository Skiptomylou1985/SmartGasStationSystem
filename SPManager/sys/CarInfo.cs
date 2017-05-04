using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;

namespace SPManager
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct CarInfoOut
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public Char[] license;   // 车牌字符串
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8)]
        public Char[] color;      // 车牌颜色
        public int nColor;         // 车牌颜色
        public int nType;          // 车牌类型
        public int nConfidence;    // 整牌可信度
        public int nCarColor;      //车的颜色
        public int nCarLogo;         //车标类型
        public int nCarType;           //车辆类型，已弃用
        public int nVideoChannel;  //识别图片通道
        public int nPicType;       //图片类型
        public int nPicLenth;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10 * 1024 * 1024)]
        public byte[] pic;

    }
    public class CarInfo
    {

        public string license
        {
            get { return _license; }
            set { _license = value; }
        }
        private string _license = "";

        public int licenseColor
        {
            get { return _licenseColor; }
            set { _licenseColor = value; }
        }
        private int _licenseColor = 1;
        public int type
        {
            get { return _type; }
            set { _type = value; }
        }
        private int _type = 0;
        public int carLogo
        {
            get { return _carLogo; }
            set { _carLogo = value; }
        }
        private int _carLogo = 0;
        public int subCarLogo
        {
            get { return _subCarLogo; }
            set { _subCarLogo = value; }
        }
        private int _subCarLogo = 0;
        public int carColor
        {
            get { return _carColor; }
            set { _carColor = value; }
        }
        private int _carColor = 0;
        public DateTime arriveTime
        {
            get { return DateTime.Parse(_arriveTime); }
            set { _arriveTime = value.ToString("yyyy-MM-dd HH:mm:ss"); }
        }
        private string _arriveTime = "2000-01-01 00:00:00";
        public DateTime leaveTime
        {
            get { return DateTime.Parse(_leaveTime); }
            set { _leaveTime = value.ToString("yyyy-MM-dd HH:mm:ss"); }
        }
        private string _leaveTime = "2000-01-01 00:00:00";
       

        public int oilMachine
        {
            get { return _oilMachine; }
            set { _oilMachine = value; }
        }
        private int _oilMachine = 0;

        public string picPath
        {
            get { return _picPath; }
            set { _picPath = value; }
        }
        private string _picPath = "";
        
        public DateTime beginTime
        {
            get { return DateTime.Parse(_beginTime); }
            set { _beginTime = value.ToString("yyyy-MM-dd HH:mm:ss"); }
        }
        private string _beginTime = "2000-01-01 00:00:00";
        
        public DateTime endTime
        {
            get { return DateTime.Parse(_endTime); }
            set { _endTime = value.ToString("yyyy-MM-dd HH:mm:ss"); }
        }
        private string _endTime = "2000-01-01 00:00:00";

        public int oilType
        {
            get { return _oilType; }
            set { _oilType = value; }
        }
        private int _oilType = 92;

        public int matchFlag
        {
            get { return _matchFlag; }
            set { _matchFlag = value; }
        }
        private int _matchFlag = 0;
        public string toSqlString()
        {
            String sqlString = "INSERT into gsims.carlog (carnumber,carnumcolor,cartype,carlogo,subcarlogo,carcolor,arrivetime,leavetime,nozzleno,picpath,begintime,endtime,oiltype)" +
        "VALUES('{0}', {1}, {2}, {3}, {4}, {5}, '{6}', '{7}', {8}, '{9}', '{10}', '{11}',{12}) ";
            return String.Format(sqlString,_license,_licenseColor.ToString(),_type.ToString(),_carLogo.ToString(),_subCarLogo.ToString(),_carColor.ToString(),_arriveTime,_leaveTime,_oilMachine.ToString(),_picPath,_beginTime,_endTime,_oilType);
        }
    }
    
}
