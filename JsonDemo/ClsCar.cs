using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JsonDemo
{
    public class ClsCarInfo
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


        public int nozzleNo
        {
            get { return _nozzleNo; }
            set { _nozzleNo = value; }
        }
        private int _nozzleNo = 0;
        public int areaNo
        {
            get { return _areaNo; }
            set { _areaNo = value; }
        }
        private int _areaNo = 0;
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

        public double volume
        {
            get { return _volume; }
            set { _volume = value; }
        }
        private double _volume = 0;

        public double realAmount
        {
            get { return _realamnout; }
            set { _realamnout = value; }
        }
        private double _realamnout = 0;

        public string tradeSn
        {
            get { return _tradeSn; }
            set { _tradeSn = value; }
        }
        private string _tradeSn = "";

        public string msgId
        {
            get { return _msgId; }
            set { _msgId = value; }
        }
        private string _msgId = "";

        public double nozzleVolume
        {
            get { return _nozzleVolume; }
            set { _nozzleVolume = value; }
        }
        private double _nozzleVolume = 0;

        public double StartCounter
        {
            get { return _StartCounter; }
            set { _StartCounter = value; }
        }
        private double _StartCounter = 0;

        public double EndCounter
        {
            get { return _EndCounter; }
            set { _EndCounter = value; }
        }
        private double _EndCounter = 0;

        public double Price
        {
            get { return _Price; }
            set { _Price = value; }
        }
        private double _Price = 0;

        public string MeterialCode
        {
            get { return _MeterialCode; }
            set { _MeterialCode = value; }
        }
        private string _MeterialCode = "";


        public string toSaveSqlString()
        {
            _picPath = "";
            String sqlString = "INSERT into carlog (carnumber,carnumcolor,cartype,carlogo,subcarlogo,carcolor,arrivetime,leavetime,nozzleno,picpath,begintime,endtime,oiltype,volume,realamount,startread,endread,oilprice,meterialcode)" +
        "VALUES('{0}', {1}, {2}, {3}, {4}, {5}, '{6}', '{7}', {8}, '{9}', '{10}', '{11}',{12},{13},{14},{15},{16},{17},'{18}') ";
            return String.Format(sqlString, _license, _licenseColor.ToString(), _type.ToString(), _carLogo.ToString(), _subCarLogo.ToString(), _carColor.ToString(), _arriveTime, _leaveTime,
                _nozzleNo.ToString(), _picPath, _beginTime, _endTime, _oilType.ToString(),
                _volume.ToString(), _realamnout.ToString(), _StartCounter.ToString(), _EndCounter.ToString(), _Price.ToString(), MeterialCode);
        }
    }
}
