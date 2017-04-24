using System;
using System.Collections.Generic;
using System.Text;

namespace SPManager
{
    class CarInfo
    {

        public string license
        {
            get { return _license; }
            set { _license = value; }
        }
        private string _license = "";

        public string licenseColor
        {
            get { return _licenseColor; }
            set { _licenseColor = value; }
        }
        private string _licenseColor = "蓝";
        public string type
        {
            get { return _type; }
            set { _type = value; }
        }
        private string _type = "小汽车";
        public string carLogo
        {
            get { return _carLogo; }
            set { _carLogo = value; }
        }
        private string _carLogo = "丰田";
        public string subCarLogo
        {
            get { return _subCarLogo; }
            set { _subCarLogo = value; }
        }
        private string _subCarLogo = "丰田";
        public string carColor
        {
            get { return _carColor; }
            set { _carColor = value; }
        }
        private string _carColor = "蓝";
        public DateTime arriveTime
        {
            get { return _arriveTime; }
            set { _arriveTime = value; }
        }
        private DateTime _arriveTime = new DateTime();
        public DateTime leaveTime
        {
            get { return _leaveTime; }
            set { _leaveTime = value; }
        }
        private DateTime _leaveTime = new DateTime();

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
            get { return _beginTime; }
            set { _beginTime = value; }
        }
        private DateTime _beginTime = new DateTime();
        public DateTime endTime
        {
            get { return _endTime; }
            set { _endTime = value; }
        }
        private DateTime _endTime = new DateTime();

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
    }
    
}
