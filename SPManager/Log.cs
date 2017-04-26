//////////////////////////////////////////////////////////////////////////
//Commit:   日志记录类，包含写日志文件、删除日志文件夹
//Author:   DQS
//Date：    2012-08-22
//Version:  1.0
//////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.IO;

namespace SPManager
{
        public static class Log
        {
            /************************************************************************
             * Function: Create Directory if not exists
             * IN:  string dirPath
             * OUT: void
             * Author: DQS
             * Date: 2012-08-22
            ************************************************************************/
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

            /************************************************************************
             * Function: Write Log to the Module log file, one day a file
             *      the file path like: log\2012-08-22\HSData.2012-08-22.log
             * IN:  string ModuleName, which Module Error Occur
             *      string ErrorType, Error Type: Error, Warning or Message
             *      string Msg, the message 
             * OUT: void
             * Author: DQS
             * Date: 2012-08-22
            ************************************************************************/
            public static void WriteLog(string ModuleName, string ErrorType, string Msg)
            {
                string sDirPath = "log\\" + DateTime.Now.ToShortDateString() + "\\";
                CreateDir(sDirPath);
                string sFilePath = sDirPath + ModuleName + "." + DateTime.Now.ToShortDateString() + ".log";
                try
                {
                    using (StreamWriter sw = File.AppendText(sFilePath))
                    {
                        sw.WriteLine(DateTime.Now.ToString() + "->" + ErrorType + ":  " + Msg);
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
             * Author: DQS
             * Date: 2012-08-22
             * Commit: Directory.Delete("log\\2012-08-22\\", true); can also delete
             *      the folder
            ************************************************************************/
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
