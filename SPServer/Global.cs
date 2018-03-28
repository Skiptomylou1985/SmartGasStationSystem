using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace SPServer
{
    class Global
    {
        public static int socketPort = 6700;  //网络监听端口
        public static EnumLogLevel logLevel = EnumLogLevel.RUN;    //日志级别
        public static bool bShowLog = true;

        //public static int multiple = 1;
        public static DBInfo dbInfo;
        public static MysqlHelper mysqlHelper;
        public static SocketHelper socketHelper;
        public static QueueManager<StationInfo> StationQueue = new QueueManager<StationInfo>();
        public static Dictionary<string, string> dicStation ;
        public static LogHelper logServer;
        public static QueueManager<String> ShowLogQueue = new QueueManager<String>();
        
    }
    enum EnumLogLevel
    {
        ERROR = 1,
        RUN = 2,
        DEBUG = 3,
        FULL = 4
    }


}
