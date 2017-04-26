using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.IO;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Security.Cryptography;

namespace SPManager
{
    class SystemUnit
    {
        [DllImport("kernel32.dll", EntryPoint = "SetLocaleInfoA")]
        public static extern int SetLocaleInfo(int Locale, int LCType, string lpLCData);
        [DllImport("user32.dll", EntryPoint = "SendMessageTimeout")]
        public static extern long SendMessageTimeout(int hWnd, int Msg, int wParam, int lParam, int fuFlags, int uTimeout, ref int lpdwResult);
        [DllImport("User32.dll", EntryPoint = "PostMessage")]
        public static extern int PostMessage(
            int hWnd,        // handle to destination window
            int Msg,            // message
            int wParam,         // first message parameter
            int lParam          // second message parameter
            );

        public const int LOCALE_USER_DEFAULT = 0x0400;
        public const int LOCALE_SYSTEM_DEFAULT = 0x0800;
        public const int LOCALE_SSHORTDATE = 0x1F;
        public const int LOCALE_STIMEFORMAT = 0x1003;
        public const int HWND_BROADCAST = 0xFFFF;
        public const int WM_SETTINGCHANGE = 0x001A;
        public const int SMTO_ABORTIFHUNG = 2;

        // MD5加密函数
        public static string MD5Encrypt(string strText)
        {
            MD5 md5 = new MD5CryptoServiceProvider();
            byte[] result = md5.ComputeHash(System.Text.Encoding.Default.GetBytes(strText));
            return BitConverter.ToString(result).Replace("-", "");
        } 

        // 设置日期时间格式
        public static void SetDateTimeFormat()
        {
            int val = 0;
            try
            {
                SetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, "yyyy-MM-dd");
                SetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIMEFORMAT, "HH:mm:ss");
                if (0 == SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, 0, SMTO_ABORTIFHUNG, 10, ref val))
                    Log.WriteLog("SystemUnit", "Error", "SendMessageTimeout失败");
            }
            catch (Exception ex)
            {
                Log.WriteLog("SystemUnit", "Error", "设置日期时间格式失败,错误信息:" + ex.Message);
            }
        }

        // 获取指定路径磁盘剩余空间大小，以Mb为单位
        public static float GetVolumeFreeSize(string path)
        {
            System.IO.DriveInfo di = new System.IO.DriveInfo(path[0].ToString());
            float freeSize = (float)di.TotalFreeSpace / 1024;
            return freeSize;
        }

        // 获取指定路径磁盘已用空间比例
        public static float GetVolumeUseScale(string path)
        {
            System.IO.DriveInfo di = new System.IO.DriveInfo(path[0].ToString());
            float Scale = (1 - (float)di.TotalFreeSpace / di.TotalSize) * 100;
            return Scale;
        }

        // 延时函数
        public static void TimeDelay(int iInterval)
        {
            DateTime now = DateTime.Now;
            while (now.AddMilliseconds(iInterval) > DateTime.Now)
            {
                Application.DoEvents();
            }
            return;
        }

        // 将Image转换为byte[]
        public static byte[] ImageToBuffer(Image Image, System.Drawing.Imaging.ImageFormat imageFormat) 
        {
            if (Image == null) { return null; }
            byte[] data = null;
            try
            {
                using (MemoryStream oMemoryStream = new MemoryStream())
                {
                    using (Bitmap oBitmap = new Bitmap(Image))
                    {
                        oBitmap.Save(oMemoryStream, imageFormat);
                        oMemoryStream.Position = 0;
                        data = new byte[oMemoryStream.Length];
                        oMemoryStream.Read(data, 0, Convert.ToInt32(oMemoryStream.Length));
                        oMemoryStream.Flush();
                    }
                }
            }
            catch (Exception ex)
            {
                Log.WriteLog("SystemUnit", "Error", "转换图像时错误,错误信息:" + ex.Message);
            }
            return data;
        }

        // 将byte[]转换为Image     
        public static Image BufferToImage(byte[] Buffer)
        {
            if (Buffer == null || Buffer.Length == 0) { return null; }
            MemoryStream oMemoryStream = null;
            byte[] data = null;
            Image oImage = null;
            Bitmap oBitmap = null;
            data = (byte[])Buffer.Clone();
            try
            {
                oMemoryStream = new MemoryStream(Buffer);
                oMemoryStream.Position = 0;
                oImage = System.Drawing.Image.FromStream(oMemoryStream);
                oBitmap = new Bitmap(oImage);
            }
            catch (Exception ex)
            {
                Log.WriteLog("SystemUnit", "Error", "转换图像时错误,错误信息:" + ex.Message);
            }
            finally
            {
                oMemoryStream.Dispose();
            }
            return oBitmap;
        }

        // 将Struct转换为byte[]
        public static byte[] StrutsToBytesArray(object structObj)
        {
            //得到结构体的大小
            int size = Marshal.SizeOf(structObj);
            //创建byte数组
            byte[] bytes = new byte[size];
            //分配结构体大小的内存空间
            IntPtr structPtr = Marshal.AllocHGlobal(size);
            //将结构体拷到分配好的内存空间
            Marshal.StructureToPtr(structObj, structPtr, false);
            //从内存空间拷到byte数组
            Marshal.Copy(structPtr, bytes, 0, size);
            //释放内存空间
            Marshal.FreeHGlobal(structPtr);
            //返回byte数组
            return bytes;
        }

        // 将byte[]转换为struct
        public static object BytesToStruts(byte[] bytes, Type type)
        {
            //得到结构体的大小
            int size = Marshal.SizeOf(type);
            //byte数组长度小于结构体的大小
            if (size > bytes.Length)
            {
                //返回空
                return null;
            }
            //分配结构体大小的内存空间
            IntPtr structPtr = Marshal.AllocHGlobal(size);
            //将byte数组拷到分配好的内存空间
            Marshal.Copy(bytes, 0, structPtr, size);
            //将内存空间转换为目标结构体
            object obj = Marshal.PtrToStructure(structPtr, type);
            //释放内存空间
            Marshal.FreeHGlobal(structPtr);
            //返回结构体
            return obj;
        }

        #region 窗体圆角
        public static void SetWindowRegion(Form frm)
        {
            GraphicsPath FormPath;
            Rectangle rect;
            FormPath = new System.Drawing.Drawing2D.GraphicsPath();
            if (frm.WindowState == FormWindowState.Normal)
                rect = new Rectangle(-1, -1, frm.Width + 1, frm.Height);
            else if (frm.WindowState == FormWindowState.Maximized)
                rect = new Rectangle(-1, -1, Screen.PrimaryScreen.Bounds.Width + 1, Screen.PrimaryScreen.Bounds.Height);
            else
                rect = new Rectangle(-1, -1, frm.Width + 1, frm.Height);
            FormPath = GetRoundedRectPath(rect, 24);
            frm.Region = new Region(FormPath);
        }

        //窗体圆角
        private static GraphicsPath GetRoundedRectPath(Rectangle rect, int radius)
        {
            int diameter = radius;
            Rectangle arcRect = new Rectangle(rect.Location, new Size(diameter, diameter));
            GraphicsPath path = new GraphicsPath();
            // 左上角
            path.AddArc(arcRect, 185, 90);
            // 右上角
            arcRect.X = rect.Right - diameter;
            path.AddArc(arcRect, 275, 90);
            // 右下角
            arcRect.Y = rect.Bottom - diameter;
            path.AddArc(arcRect, 356, 90);
            // 左下角
            arcRect.X = rect.Left;
            arcRect.Width += 2;
            arcRect.Height += 2;
            path.AddArc(arcRect, 90, 90);
            path.CloseFigure();
            return path;
        }
        #endregion

        #region 按钮圆角
        public static void SetButtonRegion(Button btn, int radius)
        {
            GraphicsPath BtnPath;
            BtnPath = new System.Drawing.Drawing2D.GraphicsPath();
            Rectangle rect = new Rectangle(-1, -1, btn.Width + 1, btn.Height);
            BtnPath = GetRoundedRectPath(rect, radius);
            btn.Region = new Region(BtnPath);
        }
        #endregion
    }
}
