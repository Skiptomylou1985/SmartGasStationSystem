using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
namespace SPManager
{
    

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
    public class RecogArea
    {
        public int top
        {
            get { return _top; }
            set { _top = value; }
        }
        private int _top = 0;
        public int bottom
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
    public class StationInfo
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

    public class VideoChannel
    {
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
    }

    public class NVRInfo
    {
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
    }
   
}
