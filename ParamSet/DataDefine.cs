using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Drawing;
namespace ParamSet
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
            return String.Format(sqlString, _license, _licenseColor.ToString(), _type.ToString(), _carLogo.ToString(), _subCarLogo.ToString(), _carColor.ToString(), _arriveTime, _leaveTime, _oilMachine.ToString(), _picPath, _beginTime, _endTime, _oilType);
        }
    }
    public class ClsNozzle
    {
        public int id
        {
            get { return _id; }
            set { _id = value; }
        }
        private int _id = 0;
        public int parentid
        {
            get { return _parentid; }
            set { _parentid = value; }
        }
        private int _parentid = 0;
        public int nozzleNo
        {
            get { return _nozzleNo; }
            set { _nozzleNo = value; }
        }
        private int _nozzleNo = 0;
        public int oilType
        {
            get { return _oilType; }
            set { _oilType = value; }
        }
        private int _oilType = 1;
        public int areaid
        {
            get { return _areaid; }
            set { _areaid = value; }
        }
        private int _areaid = 0;
        public int subAreaid
        {
            get { return _subAreaid; }
            set { _subAreaid = value; }
        }
        private int _subAreaid = 0;
        //public ClsRecogArea recogArea
        //{
        //    get { return _recogArea; }
        //    set { _recogArea = value; }
        //}
        //private ClsRecogArea _recogArea = new ClsRecogArea();

        //public int videoChanNo
        //{
        //    get { return _videoChanNo; }
        //    set { _videoChanNo = value; }
        //}
        //private int _videoChanNo = 33;
    }
    public class ClsRecogArea
    {
        public ClsNozzle nozzle = new ClsNozzle();
        public int id
        {
            get { return _id; }
            set { _id = value; }
        }
        private int _id = 0;
        public int videoid
        {
            get { return _videoid; }
            set { _videoid = value; }
        }
        private int _videoid = 0;
        public double top
        {
            get { return _top; }
            set { _top = value; }
        }
        private double _top = 0;
        public double bottom
        {
            get { return _bottom; }
            set { _bottom = value; }
        }
        private double _bottom = 0;
        public double left
        {
            get { return _left; }
            set { _left = value; }
        }
        private double _left = 0;
        public double right
        {
            get { return _right; }
            set { _right = value; }
        }
        private double _right = 0;
    }
    public class ClsStationInfo
    {
        public List<ClsNVRInfo> nvrList = new List<ClsNVRInfo>();
        public string stationCode
        {
            get { return _stationCode; }
            set { _stationCode = value; }
        }
        private string _stationCode = "";
        public string stationName
        {
            get { return _stationName; }
            set { _stationName = value; }
        }
        private string _stationName = "";
        public string province
        {
            get { return _province; }
            set { _province = value; }
        }
        private string _province = "";
        public string city
        {
            get { return _city; }
            set { _city = value; }
        }
        private string _city = "";
        public string district
        {
            get { return _district; }
            set { _district = value; }
        }
        private string _district = "";
        public string addr
        {
            get { return _addr; }
            set { _addr = value; }
        }
        private string _addr = "";

        public int machineCount
        {
            get { return _machineCount; }
            set { _machineCount = value; }
        }
        private int _machineCount = 0;

        public int cameraCount
        {
            get { return _cameraCount; }
            set { _cameraCount = value; }
        }
        private int _cameraCount = 0;
    }

    public class ClsVideoChannel
    {
        public List<ClsRecogArea> areaList = new List<ClsRecogArea>();
        public int id
        {
            get { return _id; }
            set { _id = value; }
        }
        private int _id = 0;
        public int parentID
        {
            get { return _parentID; }
            set { _parentID = value; }
        }
        private int _parentID = 0;
        public int channelNo
        {
            get { return _channelNo; }
            set { _channelNo = value; }
        }
        private int _channelNo = 101;

        public string ip
        {
            get { return _ip; }
            set { _ip = value; }
        }
        private string _ip = "";

        public int port
        {
            get { return _port; }
            set { _port = value; }
        }
        private int _port = 0;

        public string loginName
        {
            get { return _loginName; }
            set { _loginName = value; }
        }
        private string _loginName = "";
        public string password
        {
            get { return _password; }
            set { _password = value; }
        }
        private string _password = "";

        public string videoName
        {
            get { return _videoName; }
            set { _videoName = value; }
        }
        private string _videoName = "";
        public int videoType
        {
            get { return _videoType; }
            set { _videoType = value; }
        }
        private int _videoType = 0;
        public string videoAttr
        {
            get { return _videoAttr; }
            set { _videoAttr = value; }
        }
        private string _videoAttr = "0";
        public int streamType
        {
            get { return _streamType; }
            set { _streamType = value; }
        }
        private int _streamType = 0;

        public string getInsertString()
        {
            string str = "insert into vch (parentid,vchtype,vchname,vchno,vchip,vchport,loginname,loginpwd,vchAttr,streamType) values("+
                           parentID.ToString()+","+videoType.ToString()+",'"+videoName+"',"+channelNo.ToString()+",'"+
                           ip+"',"+port.ToString()+ ",'"+loginName+"','"+password+"','"+videoAttr+"',"+streamType.ToString()+")";
            return str;
        }
    }

    public class ClsNVRInfo
    {
        public NET_DVR_IPPARACFG_V40 config = new NET_DVR_IPPARACFG_V40();
        public List<ClsVideoChannel> videoList = new List<ClsVideoChannel>();
        public int id
        {
            get { return _id; }
            set { _id = value; }
        }
        private int _id ;
        public string ip
        {
            get { return _ip; }
            set { _ip = value; }
        }
        private string _ip = "10.225.142.28";

        public int port
        {
            get { return _port; }
            set { _port = value; }
        }
        private int _port = 8000;

        public string loginName
        {
            get { return _loginName; }
            set { _loginName = value; }
        }
        private string _loginName = "admin";
        public string password
        {
            get { return _password; }
            set { _password = value; }
        }
        private string _password = "12345";
        public int channelCount
        {
            get { return _channelCount; }
            set { _channelCount = value; }
        }
        private int _channelCount = 16;
        public string nvrType
        {
            get { return _nvrType; }
            set { _nvrType = value; }
        }
        private string _nvrType = "8208";
        public string nvrName
        {
            get { return _nvrName; }
            set { _nvrName = value; }
        }
        private string _nvrName = "";

        public int startChan
        {
            get { return _startChan; }
            set { _startChan = value; }
        }
        private int _startChan = 33;
    }

    public class ClsPicture
    {
        public string picPath
        {
            get { return _picPath; }
            set { _picPath = value; }
        }
        private string _picPath = "";

        //图片类型  1入口图片 2加油图片 3出口图片
        public int picType
        {
            get { return _picType; }
            set { _picType = value; }
        }
        private int _picType = 2;

        public byte[] picBufer;


    }
    public struct struDraw
    {
        public Point start ;
        public Point end;
        public Graphics g;
        public bool bShowDraw;
        public bool bReDraw;
    }
   
}
