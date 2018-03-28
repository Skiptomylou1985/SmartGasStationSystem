//////////////////////////////////////////////////////////////////////////
//Commit:   日志记录类，包含写日志文件、删除日志文件夹
//Author:   HYF
//Date：    2017-04-27
//Version:  1.0
//////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.IO;
using System.Threading;

namespace SPServer
{

    public class LogHelper
    {

        private QueueManager<LogInfo> queue = new QueueManager<LogInfo>();
        private bool isRun = false;
        private Thread threadLog = null;
        public LogHelper(int logLevel)
        {
            LogLevel = logLevel;
        }
        public LogHelper()
        {

        }
        public int LogLevel
        {
            get { return _LogLevel; }
            set { _LogLevel = value; }
        }
        private int _LogLevel = 0;

        public int Add(LogInfo info)
        {
            if (!isRun)
                return -1;

            if (info.logLevel > this.LogLevel)
                return 1;
            queue.Add(info);
            return 0;
        }

        public bool Run()
        {
            if (isRun && null != this.threadLog)
                return true;
            try
            {
                isRun = true;
                threadLog = new Thread(new ThreadStart(_threadWrite));
                threadLog.Start();
                return true;
            }
            catch (Exception ex)
            {
                isRun = false;
                threadLog = null;
                return false;
            }
        }
        public void Stop()
        {
            isRun = false;
            threadLog = null;
        }
        private void _threadWrite()
        {
            while (isRun)
            {
                if (queue.GetQueueCount() > 0)
                {
                    LogInfo info = queue.Get();
                    WriteLog(info.moduleName, "", info.msg, info.logTime);
                }
                else
                    Thread.Sleep(100);
            }

        }

        /************************************************************************
         * Function: Create Directory if not exists
         * IN:  string dirPath
         * OUT: void
         * Author: HYF
         * Date: 2017-04-27
        ************************************************************************/
        public void CreateDir(string dirPath)
        {
            if (!Directory.Exists(dirPath))
            {
                try
                {
                    Directory.CreateDirectory(dirPath);
                }
                catch { }
            }
        }

        /************************************************************************
         * Function: Write Log to the Module log file, one day a file
         *      the file path like: log\2012-08-22\HSData.2012-08-22.log
         * IN:  string ModuleName, which Module Error Occur
         *      string ErrorType, Error Type: Error, Warning or Message
         *      string Msg, the message 
         * OUT: void
         * Author: HYF
         * Date: 2017-04-27
        ************************************************************************/
        public void WriteLog(string ModuleName, string ErrorType, string Msg, DateTime logTime)
        {
            string sDirPath = "log\\" + DateTime.Now.ToString("yyyy-MM-dd") + "\\";
            CreateDir(sDirPath);
            string sFilePath = sDirPath + ModuleName + "." + DateTime.Now.ToString("MM-dd") + ".log";
            try
            {
                using (StreamWriter sw = File.AppendText(sFilePath))
                {
                    sw.WriteLine(logTime.ToString("yyyy-MM-dd HH:mm:ss.fff") + "->" + ErrorType + ":  " + Msg);
                    sw.Flush();
                    sw.Dispose();
                }
            }
            catch { }
        }

        /************************************************************************
         * Function: Delete The Directory and The files in the folder
         * IN:  string dir, the directory to be deleted
         * OUT: void
         * Author: HYF
         * Date: 2017-04-27
         * Commit: Directory.Delete("log\\2012-08-22\\", true); can also delete
         *      the folder
        ************************************************************************/
        public void DeleteDir(string dir)
        {
            try
            {
                if (Directory.Exists(dir))
                {
                    foreach (string d in Directory.GetFileSystemEntries(dir))
                    {
                        //Recursive Delete Directory
                        if (File.Exists(d))
                            File.Delete(d);
                        else
                            DeleteDir(d);
                    }
                    //Delete the Empty Directory
                    Directory.Delete(dir);
                }
            }
            catch { }
        }
    }

    public class LogInfo
    {
        public LogInfo(string ModuleName, string Msg, int LogLevel, DateTime LogTime)
        {
            this.moduleName = ModuleName;
            this.msg = Msg;
            this.logLevel = LogLevel;
            this.logTime = LogTime;
        }
        public LogInfo(string ModuleName, string Msg, int LogLevel)
        {
            this.moduleName = ModuleName;
            this.msg = Msg;
            this.logLevel = LogLevel;
            this.logTime = DateTime.Now;
        }
        public string moduleName
        {
            get { return _moduleName; }
            set { _moduleName = value; }
        }
        private string _moduleName = "";
        public string msg
        {
            get { return _msg; }
            set { _msg = value; }
        }
        private string _msg = "";

        public int logLevel
        {
            get { return _logLevel; }
            set { _logLevel = value; }
        }
        private int _logLevel = 0;
        public DateTime logTime
        {
            get { return _logTime; }
            set { _logTime = value; }
        }
        private DateTime _logTime;
    }

}
