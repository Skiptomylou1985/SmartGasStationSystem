//////////////////////////////////////////////////////////////////////////
//Commit:   INI文件操作类，可进行读写操作
//Author:   DQS
//Date：    2012-08-24
//Version:  1.0
//////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SPServer
{
   
        static class IniHelper
    {
            #region LoadIniAPI
            [DllImport("kernel32")]
            private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);
            [DllImport("kernel32")]
            private static extern int GetPrivateProfileString(string section, string key, string defVal, StringBuilder retVal, int size, string filePath);
            [DllImport("kernel32")]
            private static extern int GetPrivateProfileString(string section, string key, string defVal, Byte[] retVal, int size, string filePath);
            #endregion

            /************************************************************************
             * Function: Get Value of The Key
             * IN:  string IniFilePath
             *      string section
             *      string key
             * OUT: string
             * Author: DQS
             * Date: 2012-08-24
             * Commit: 
            ************************************************************************/
            public static string GetINIValue(string IniFilePath, string section, string key)
            {
                System.Text.StringBuilder temp = new System.Text.StringBuilder(255);
                GetPrivateProfileString(section, key, "", temp, 255, IniFilePath);
                return temp.ToString().Trim();
            }

            /************************************************************************
             * Function: Write Value of The Key to INI File
             * IN:  string IniFilePath
             *      string section
             *      string key
             *      strung value
             * OUT: void
             * Author: DQS
             * Date: 2012-08-24
             * Commit: 
             *      to write a key: SetINIValue(IniFilePath,section,key,value)
             *      to delete a key: SetINIValue(IniFilePath, section, key, null)
             *      to delete a section: SetINIValue(IniFilePath, section, null, null)
            ************************************************************************/
            public static void SetINIValue(string IniFilePath, string section, string key, string value)
            {
                WritePrivateProfileString(section, key, value, IniFilePath);
            }
        }
      
}
