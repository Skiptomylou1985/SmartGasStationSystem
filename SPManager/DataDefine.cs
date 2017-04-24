using System;
using System.Collections.Generic;
using System.Text;

namespace SPManager
{
    class DataDefine
    {
    }
    public class OilMachine
    {
        public int machineNo
        {
            get { return _machineNo; }
            set { _machineNo = value; }
        }
        private int _machineNo = 0;
        public int oilType
        {
            get { return _oilType; }
            set { _oilType = value; }
        }
        private int _oilType = 92;
    }
    public class recogArea
    {
        public int top
        {
            get { return _top; }
            set { _top = value; }
        }
        private int _top = 0;
        public int oilType
        {
            get { return _bottom; }
            set { _bottom = value; }
        }
        private int _bottom = 0;
        public int left
        {
            get { return _left; }
            set { _left = value; }
        }
        private int _left = 0;
        public int right
        {
            get { return _right; }
            set { _right = value; }
        }
        private int _right = 92;
    }
    public class stationInfo
    {
        public string stationNo
        {
            get { return _stationNo; }
            set { _stationNo = value; }
        }
        private string _stationNo = "";
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
}
