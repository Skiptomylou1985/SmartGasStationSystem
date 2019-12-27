using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;

namespace SPManager
{
    public class FTPHelper
    {
        #region 属性与构造函数

        /// <summary>
        /// IP地址
        /// </summary>
        public string IpAddr { get; set; }

        /// <summary>
        /// 相对路径
        /// </summary>
        public string RelatePath { get; set; }

        /// <summary>
        /// 端口号
        /// </summary>
        public string Port { get; set; }

        /// <summary>
        /// 用户名
        /// </summary>
        public string UserName { get; set; }

        /// <summary>
        /// 密码
        /// </summary>
        public string Password { get; set; }



        public FTPHelper()
        {

        }

        public FTPHelper(string ipAddr, string port, string userName, string password)
        {
            this.IpAddr = ipAddr;
            this.Port = port;
            this.UserName = userName;
            this.Password = password;
        }

        #endregion

        #region 方法


        /// <summary>
        /// 下载文件
        /// </summary>
        /// <param name="filePath"></param>
        /// <param name="isOk"></param>
        public void DownLoad(string filePath, out bool isOk)
        {
            string method = WebRequestMethods.Ftp.DownloadFile;
            var statusCode = FtpStatusCode.DataAlreadyOpen;
            FtpWebResponse response = callFtp(method);
            ReadByBytes(filePath, response, statusCode, out isOk);
        }

        public void UpLoad(string file, out bool isOk)
        {
            isOk = false;
            FileInfo fi = new FileInfo(file);
            FileStream fs = fi.OpenRead();
            long length = fs.Length;
            string uri = string.Format("ftp://{0}:{1}{2}", this.IpAddr, this.Port, this.RelatePath);
            FtpWebRequest request = (FtpWebRequest)WebRequest.Create(uri);
            request.Credentials = new NetworkCredential(UserName, Password);
            request.Method = WebRequestMethods.Ftp.UploadFile;
            request.UseBinary = true;
            request.ContentLength = length;
            request.Timeout = 10 * 1000;
            try
            {
                Stream stream = request.GetRequestStream();

                int BufferLength = 2048; //2K   
                byte[] b = new byte[BufferLength];
                int i;
                while ((i = fs.Read(b, 0, BufferLength)) > 0)
                {
                    stream.Write(b, 0, i);
                }
                stream.Close();
                stream.Dispose();
                isOk = true;
            }
            catch (Exception ex)
            {
                Console.WriteLine();
                Global.LogServer.Add(new LogInfo("Error", "Main->ftpUpload: 文件上传异常 --> 图片名称：" + file + "  异常信息：" + ex.ToString(), (int)EnumLogLevel.DEBUG));
            }
            finally
            {
                if (request != null)
                {
                    request.Abort();
                    request = null;
                }
            }
        }

        /// <summary>
        /// 删除本地文件
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        public bool DeleteLocationFile(string path)
        {
            try
            {
                if (File.Exists(path))
                {
                    File.Delete(path);
                }
                return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// 删除文件
        /// </summary>
        /// <param name="isOk"></param>
        /// <returns></returns>
        public string[] DeleteFile(out bool isOk)
        {
            string method = WebRequestMethods.Ftp.DeleteFile;
            var statusCode = FtpStatusCode.FileActionOK;
            FtpWebResponse response = callFtp(method);
            return ReadByLine(response, statusCode, out isOk);
        }

        /// <summary>
        /// 展示目录
        /// </summary>
        public string[] ListDirectory(out bool isOk)
        {
            string method = WebRequestMethods.Ftp.ListDirectoryDetails;
            var statusCode = FtpStatusCode.DataAlreadyOpen;
            FtpWebResponse response = callFtp(method);
            return ReadByLine(response, statusCode, out isOk);
        }

        /// <summary>
        /// 设置上级目录
        /// </summary>
        public void SetPrePath()
        {
            string relatePath = this.RelatePath;
            if (string.IsNullOrEmpty(relatePath) || relatePath.LastIndexOf("/") == 0)
            {
                relatePath = "";
            }
            else
            {
                relatePath = relatePath.Substring(0, relatePath.LastIndexOf("/"));
            }
            this.RelatePath = relatePath;
        }

        #endregion

        #region 私有方法

        /// <summary>
        /// 调用Ftp,将命令发往Ftp并返回信息
        /// </summary>
        /// <param name="method">要发往Ftp的命令</param>
        /// <returns></returns>
        private FtpWebResponse callFtp(string method)
        {
            string uri = string.Format("ftp://{0}:{1}{2}", this.IpAddr, this.Port, this.RelatePath);
            FtpWebRequest request; request = (FtpWebRequest)FtpWebRequest.Create(uri);
            request.UseBinary = true;
            request.UsePassive = true;
            request.Credentials = new NetworkCredential(UserName, Password);
            request.KeepAlive = false;
            request.Method = method;
            FtpWebResponse response = (FtpWebResponse)request.GetResponse();
            return response;
        }

        /// <summary>
        /// 按行读取
        /// </summary>
        /// <param name="response"></param>
        /// <param name="statusCode"></param>
        /// <param name="isOk"></param>
        /// <returns></returns>
        private string[] ReadByLine(FtpWebResponse response, FtpStatusCode statusCode, out bool isOk)
        {
            List<string> lstAccpet = new List<string>();
            int i = 0;
            while (true)
            {
                if (response.StatusCode == statusCode)
                {
                    using (StreamReader sr = new StreamReader(response.GetResponseStream()))
                    {
                        string line = sr.ReadLine();
                        while (!string.IsNullOrEmpty(line))
                        {
                            lstAccpet.Add(line);
                            line = sr.ReadLine();
                        }
                    }
                    isOk = true;
                    break;
                }
                i++;
                if (i > 10)
                {
                    isOk = false;
                    break;
                }
                Thread.Sleep(200);
            }
            response.Close();
            return lstAccpet.ToArray();
        }

        private void ReadByBytes(string filePath, FtpWebResponse response, FtpStatusCode statusCode, out bool isOk)
        {
            isOk = false;
            int i = 0;
            while (true)

            {
                if (response.StatusCode == statusCode)
                {
                    long length = response.ContentLength;
                    int bufferSize = 2048;
                    int readCount;
                    byte[] buffer = new byte[bufferSize];
                    using (FileStream outputStream = new FileStream(filePath, FileMode.Create))
                    {

                        using (Stream ftpStream = response.GetResponseStream())
                        {
                            readCount = ftpStream.Read(buffer, 0, bufferSize);
                            while (readCount > 0)
                            {
                                outputStream.Write(buffer, 0, readCount);
                                readCount = ftpStream.Read(buffer, 0, bufferSize);
                            }
                        }
                    }
                    break;
                }
                i++;
                if (i > 10)
                {
                    isOk = false;
                    break;
                }
                Thread.Sleep(200);
            }
            response.Close();
        }
        #endregion

        /// <summary>
        /// 获取指定驱动器的空间总大小(单位为GB)
        /// </summary>
        /// <param name="str_HardDiskName"> 只需输入代表驱动器的字母即可 </param>
        /// <returns></returns>
        public static long GetHardDiskSpace(string str_HardDiskName)
        {
            long totalSize = new long();
            str_HardDiskName = str_HardDiskName + ":\\";
            System.IO.DriveInfo[] drives = System.IO.DriveInfo.GetDrives();
            foreach (System.IO.DriveInfo drive in drives)
            {
                if (drive.Name == str_HardDiskName)
                {
                    totalSize = drive.TotalSize / (1024 * 1024 * 1024);
                }
            }
            return totalSize;
        }

        /// <summary>
        /// 获取指定驱动器的剩余空间总大小(单位为GB)
        /// </summary>
        /// <param name="str_HardDiskName"> 只需输入代表驱动器的字母即可 </param>
        /// <returns></returns>
        public static long GetHardDiskFreeSpace(string str_HardDiskName)
        {
            long freeSpace = new long();
            str_HardDiskName = str_HardDiskName + ":\\";
            System.IO.DriveInfo[] drives = System.IO.DriveInfo.GetDrives();
            foreach (System.IO.DriveInfo drive in drives)
            {
                if (drive.Name == str_HardDiskName)
                {
                    freeSpace = drive.TotalFreeSpace / (1024 * 1024 * 1024);
                }
            }
            return freeSpace;
        }

        /// <summary>
        /// 直接删除指定目录下的所有文件及文件夹(保留目录)
        /// </summary>
        /// <param name="file"> 文件夹路径 </param>
        public static void DeleteDir(string file)
        {
            try
            {
                //去除文件夹和子文件的只读属性
                //去除文件夹的只读属性
                System.IO.DirectoryInfo fileInfo = new DirectoryInfo(file);
                fileInfo.Attributes = FileAttributes.Normal & FileAttributes.Directory;
                //去除文件的只读属性
                System.IO.File.SetAttributes(file, System.IO.FileAttributes.Normal);
                //判断文件夹是否还存在
                if (Directory.Exists(file))
                {
                    foreach (string f in Directory.GetFileSystemEntries(file))
                    {
                        if (File.Exists(f))
                        {
                            //如果有子文件删除文件
                            File.Delete(f);
                            Console.WriteLine(f);
                        }
                        else
                        {
                            //循环递归删除子文件夹
                            DeleteDir(f);
                        }
                    }
                    //删除空文件夹
                    Directory.Delete(file);
                }
            }
            catch (Exception ex) // 异常处理
            {
                Console.WriteLine(ex.Message.ToString());// 异常信息
            }
        }
    }

    /// <summary>
    /// Ftp内容类型枚举
    /// </summary>
    public enum FtpContentType
    {
        undefined = 0,
        file = 1,
        folder = 2
    }
}
