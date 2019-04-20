using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
namespace SPManager
{
    //车辆信息类
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

        public string licenseColorString;
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
                _volume.ToString(), _realamnout.ToString(), _StartCounter.ToString(), _EndCounter.ToString(),_Price.ToString(),MeterialCode);
        }
    }

    public class UploadCarInfo
    {
        public int id { get; set; }

        public string carNumber { get; set; }
        
        public int carNumColor { get; set; }

        public int carType { get; set; }

        public int carLogo { get; set; }

        public int subCarLogo { get; set; }

        public int carColor { get; set; }

        public string arriveTime { get; set; }

        public string leaveTime { get; set; }
        
        public int nozzleNo { get; set; }

        public int areaNo { get; set; }

        public string picPath { get; set; }

        public string beginTime { get; set; }

        public string endTime { get; set; }

        public int oilType { get; set; }

        public int matchFlag { get; set; }

        public double volume { get; set; }

        public double realAmount { get; set; }

        public string tradeSn { get; set; }

        public string msgId { get; set; }

        public double nozzleVolume { get; set; }

        public double startRead { get; set; }

        public double endRead { get; set; }

        public double oilPrice { get; set; }

        public string meterialCode {get; set;}

        public string stationCode { get; set; }

        public string stationName { get; set; }
    }

    //油枪信息类
    public class ClsNozzle
    {
        //关联的主识别区
        public List<int> linkedMainAreaList = new List<int>();
        //关联的副识别区，油岛另外一侧 
        public List<int> linkedSubAreaList = new List<int>();
        //关联的油岛号
        public int linkedIslandNo;
        //当前油枪占位车辆信息
        public ClsCarInfo nozzleCar = new ClsCarInfo();
        //油枪状态 0空闲，1提枪 2 加油，3挂枪
        public int curStatus = 0;
        //当前油枪是否已匹配车辆
        public bool bMatched = false;
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

        public string getInsertString()
        {
            string str = "insert into nozzle (nozzleno,oiltype,areaid,subareaid,parentid) values (" + nozzleNo.ToString() + "," +
                oilType.ToString() + "," + areaid.ToString() + "," + subAreaid.ToString() + "," + parentid.ToString() + ")";
            return str;
        }
    }
    //识别区域类
    public class ClsRecogArea
    {
        public List<ClsNozzle> nozzleList = new List<ClsNozzle>();
        public Queue<ClsCarInfo> carQueue = new Queue<ClsCarInfo>();
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

        public int areaFlag //是否为出入口识别区,0为油枪识别区，99 入口  100 出口
        {
            get { return _areaFlag; }
            set { _areaFlag = value; }
        }
        private int _areaFlag = 0;
        public int videoChannel
        {
            get { return _videoChannel; }
            set { _videoChannel = value; }
        }
        private int _videoChannel = 0;
        public int chanIndex
        {
            get { return _chanIndex; }
            set { _chanIndex = value; }
        }
        private int _chanIndex = 33;
        public int videoLaneNo
        {
            get { return _videoLaneNo; }
            set { _videoLaneNo = value; }
        }
        private int _videoLaneNo = 0;
        public string getInsertString()
        {
            string str = "insert into analysisarea (x1,x2,y1,y2,vchid,vcharea) values (" + left.ToString() + "," +
                right.ToString() + "," + top.ToString() + "," + bottom.ToString() + "," + videoid.ToString() + "," + videoLaneNo.ToString() + ")";
            return str;
        }
        public string getUpdateString()
        {
            string str = "update analysisarea set x1 = " + left.ToString() + ",x2 = " + right.ToString() +
                        ",y1=" + top.ToString() + ",y2=" + bottom.ToString() + " where id = " + id.ToString();
            return str;
        }
    }

    //站点信息类
    public class ClsStationInfo
    {
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

        public string stationIP
        {
            get { return _stationIP; }
            set { _stationIP = value; }
        }
        private string _stationIP = "";

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

    //视频通道类
    public class ClsVideoChannel
    {
        public int id
        {
            get { return _id; }
            set { _id = value; }
        }
        private int _id = 0;
        public int channelNo
        {
            get { return _channelNo; }
            set { _channelNo = value; }
        }
        private int _channelNo = 0;

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

        public int videoType
        {
            get { return _videoType; }
            set { _videoType = value; }
        }
        private int _videoType = 0;
        public int streamType
        {
            get { return _streamType; }
            set { _streamType = value; }
        }
        private int _streamType = 0;
        //public List<int> locationNoList = new List<int>();
        // public List<int> videoNoList = new List<int>();
        public List<int> nozzleNoList = new List<int>();
        public List<int> areaNoList = new List<int>();
        public List<ClsCarInfo> carList = new List<ClsCarInfo>();

    }

    //油岛类，一个油岛可对应多个视频通道，包含多个油枪、识别区、加油位
    public class ClsGasIsland
    {
        //油岛ID
        public int id
        {
            get { return _id; }
            set { _id = value; }
        }
        private int _id = 0;

        public List<int> locationNoList = new List<int>();
        public List<int> videoNoList = new List<int>();
        public List<int> nozzleNoList = new List<int>();
        public List<int> areaNoList = new List<int>();
        public List<ClsCarInfo> carList = new List<ClsCarInfo>();
    }

    //油位信息类
    public class ClsGasLocation
    {
        public int gasIslandNo
        {
            get { return _gasIslandNo; }
            set { _gasIslandNo = value; }
        }
        private int _gasIslandNo = 0;
        public List<int> areaNoList = new List<int>();
        public List<int> nozzleNoList = new List<int>();
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
        private int _id;
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
        public string picName
        {
            get { return _picName; }
            set { _picName = value; }
        }
        private string _picName = "";
        //图片类型  1入口图片 2加油图片 3出口图片
        public int picType
        {
            get { return _picType; }
            set { _picType = value; }
        }
        private int _picType = 2;
        public int picWidth
        {
            get { return _picWidth; }
            set { _picWidth = value; }
        }
        private int _picWidth = 1920;
        public int picHeight
        {
            get { return _picHeight; }
            set { _picHeight = value; }
        }
        private int _picHeight = 1080;

        public byte[] picBufer;
    }

    public class ClsServiceStatus
    {
        public bool bRecogIsRun;
        public bool bMoniterIsRun;
        public bool bAutoUpdate;
        public bool bSocketDitIsRun;
        public bool bSocketTradeIsRun;
    }
    public class ClsCarArrive
    {
        public ClsCarArrive(string plate, struCarInfoOut car, DateTime time)
        {
            this.plate = plate;
            this.carInfo = car;
            this.arriveTime = time;
        }
        public string plate;
        public struCarInfoOut carInfo;
        public DateTime arriveTime;
        public int matchFlag = 0; // 0未匹配，1已匹配，默认未匹配
    }

    public class TradeInfo
    {
        public string GasStation_NO { set; get; }
        public string REQ_Time { set; get; }
        public string MSG_ID { set; get; }
        public string OilGun_NO { set; get; }
        public string OIL_TYPE { set; get; }
        public double OIL_Q { set; get; }
        public double OIL_AMT { set; get; }
        public double OIL_PRC { set; get; }
        public string START_TIME { set; get; }
        public string END_TIME { set; get; }
        public double START_READ { set; get; }
        public double END_READ { set; get; }
        public string VehicleNo { set; get; }
        public string VehicleBrandCode { set; get; }
        public string SubBrandCode { set; get; }
        public string VehicleModel { set; get; }
        public string VehicleColor { set; get; }
        public string BodyColor { set; get; }

        public string CarBrand { set; get; }
        public string SubBrand { set; get; }
        public string OilName { set; get; }
        public string OilCode { set; get; }
        public string OilClass { set; get; }


        public string toSaveSqlString()
        {
            String sqlString = "INSERT into tradelog (nozzleno,meterialcode,volume,realamount,price,starttime,endtime,startread,endread," +
                "carnumber,carbrand,subbrand,cartype,carcolor,carnumcolor,realcarbrand,realsubbrand,oilname,oilcode,oilclass)" +
       "VALUES({0}, '{1}', {2}, {3}, {4}, '{5}', '{6}', {7}, {8}, '{9}', {10}, {11},{12},{13},{14},'{15}', '{16}','{17}','{18}','{19}') ";
            return String.Format(sqlString, OilGun_NO, OIL_TYPE, OIL_Q.ToString(), OIL_AMT.ToString(), OIL_PRC.ToString(), START_TIME, END_TIME, START_READ.ToString(),
                END_READ.ToString(), VehicleNo, VehicleBrandCode, SubBrandCode, VehicleModel, VehicleColor, BodyColor, CarBrand, SubBrand, OilName, OilCode, OilClass);
        }

    }

    public class UpLoadTradeInfo
    {
        public int id { set; get; }
        public string stationCode { set; get; }
        public string stationName { set; get; }
        public string meterialCode { set; get; }
        public int nozzleNo { set; get; }
        public double volume { set; get; }
        public double realAmount { set; get; }
        public double price { set; get; }
        public string startTime { set; get; }
        public string endTime { set; get; }
        public double startRead { set; get; }
        public double endRead { set; get; }
        public string carNumber { set; get; }
        public int carBrand { set; get; }
        public int subBrand { set; get; }
        public int carType { set; get; }
        public int carColor { set; get; }
        public int carNumColor { set; get; }
        public string realCarBrand { set; get; }
        public string realSubBrand { set; get; }
        public string oilName { set; get; }
        public string oilCode { set; get; }
        public string oilClass { set; get; }

    }
    public class OrderInfo
    {
        public string GasStation_NO { set; get; }
        public string REQ_Time { set; get; }
        public string MSG_ID { set; get; }
        public string TRANS_TYPE { set; get; }
        public string TRANS_CODE { set; get; }
        public string BAR_CODE { set; get; }
        public double TRANS_Q { set; get; }
        public double TRANS_AMT { set; get; }
        public double TRANS_PRC { set; get; }
        public string FINISH_TIME { set; get; }
        public string SETTLE_DAY { set; get; }
        public string OilGun_NO { set; get; }
        public double START_READ { set; get; }
        public double END_READ { set; get; }
        public string BILL_NUM { set; get; }
        public string BILL_ITEM_ID { set; get; }
        public string POS_NO { set; get; }
        public string StatusType { set; get; }
        public string Pumpsrv_ref { set; get; }
        public int TRADE_ID { set; get; }
        public string toSaveSqlString()
        {
            String sqlString = "INSERT into orderlog (transtype,transcode,meterialcode,volume,realamount,price,paytime,settledate,nozzleno," +
                "startread,endread,billno,billitemid,posno,statustype,paycode,tradeid)" +
       "VALUES('{0}','{1}','{2}', {3}, {4}, {5}, '{6}', '{7}', {8}, {9}, {10}, {11},{12},'{13}','{14}','{15}',{16}) ";
            return String.Format(sqlString, TRANS_TYPE, TRANS_CODE, BAR_CODE, TRANS_Q.ToString(), TRANS_AMT.ToString(), TRANS_PRC.ToString(),
                FINISH_TIME, SETTLE_DAY, OilGun_NO.ToString(), START_READ.ToString(), END_READ.ToString(), BILL_NUM.ToString(),
                BILL_ITEM_ID.ToString(), POS_NO, StatusType, Pumpsrv_ref, TRADE_ID.ToString());
        }
    }

    public class UploadOrderInfo
    {
        public int id { set; get; }
        public string transType { set; get; }
        public string transCode { set; get; }
        public string meterialCode { set; get; }
        public double volume { set; get; }
        public double realAmount { set; get; }
        public double price { set; get; }
        public string payTime { set; get; }
        public string settleDate { set; get; }
        public int nozzleNo { set; get; }
        public double startRead { set; get; }
        public double endRead { set; get; }
        public int billNo { set; get; }
        public int billItemId { set; get; }
        public string posNo { set; get; }
        public string statusType { set; get; }
        public string payCode { set; get; }
        public int tradeId { set; get; }
        public int upload { set; get; }
        public string stationCode { set; get; }
        public string stationName { set; get; }
    }

    public class PayInfo
    {
        public string BILL_NUM { set; get; }
        public string PAY_MODE { set; get; }
        public double PAY_AMT { set; get; }
        public double Discount_AMT { set; get; }
        public string PAY_CARD { set; get; }

        public int TRADE_ID { set; get; }
        public string toSaveSqlString()
        {
            String sqlString = "INSERT into paylog (billno,paymode,payamount,discount,paycard,tradeid)" +
       "VALUES('{0}','{1}',{2},{3},'{4}',{5}) ";
            return String.Format(sqlString, BILL_NUM.ToString(), PAY_MODE, PAY_AMT.ToString(), Discount_AMT.ToString(), PAY_CARD, TRADE_ID.ToString());
        }
    }

    public class UploadPayInfo
    {
        public int id { set; get; }
        public int billNo { set; get; }
        public string payMode { set; get; }
        public double payAmount { set; get; }
        public double discount { set; get; }
        public string payCard { set; get; }
        public int tradeId { set; get; }

        public int upload { set; get; }
        public string stationCode { set; get; }
        public string stationName { set; get; }
    }

    public class PumpInfo
    {
        public string PumpID { set; get; }

        public string PumpFlag { set; get; }

        public string GradeID { set; get; }

        public string Volume { set; get; }

        public string Value { set; get; }

        public string Time { set; get; }
        public string MsgID { set; get; }
        public string StartCounter { set; get; }
        public string EndCounter { set; get; }
    }
    public class PumpBackInfo
    {
        public string VehicleNo { set; get; }
        public string VehicleBrand { set; get; }
        public string SubBrand { set; get; }
        public string VehicleModel { set; get; }
        public string VehicleColor { set; get; }
        public string BodyColor { set; get; }
        public string PumpID { set; get; }
        public string Time { set; get; }
        public string MsgID { set; get; }
    }

    public class OilInfo
    {
        public int id { set; get; }
        public string MeterialCode { set; get; }
        public string OilName { set; get; }
        public string OilCode { set; get; }
        public string OilClass { set; get; }
    }

    public class CarBrandInfo
    {
        public int id { set; get; }
        public string CarCode { set; get; }
        public string SubCarCode { set; get; }
        public string CarBrand { set; get; }
        public string SubCarBrand { set; get; }
    }
}
