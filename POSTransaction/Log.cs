//////////////////////////////////////////////////////////////////////////
//Commit:   日志记录类，包含写日志文件、删除日志文件夹
//Author:   HYF
//Date：    2017-04-02
//Version:  1.0
//////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.IO;

namespace POSTransaction
{
        public static class Log
        {
           
            public static void CreateDir(string dirPath)
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

           
            public static void WriteLog(string ModuleName, string ErrorType, string Msg)
            {
                string sDirPath = "log\\" + DateTime.Now.ToString("yyyy-MM") + "\\";
                CreateDir(sDirPath);
                string sFilePath = sDirPath + ModuleName + "." + DateTime.Now.ToString("yyyy-MM-dd") + ".log";
                try
                {
                    using (StreamWriter sw = File.AppendText(sFilePath))
                    {
                        sw.WriteLine(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + "->" + ErrorType + ":  " + Msg);
                        sw.Flush();
                        sw.Dispose();
                    }
                }
                catch { }
            }

           
            public static void DeleteDir(string dir)
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
       
}
