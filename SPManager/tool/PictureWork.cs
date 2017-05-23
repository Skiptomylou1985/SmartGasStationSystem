using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Drawing;
using System.IO;

namespace SPManager
{
    public class PictureWork
    {
        private double[,] YUV2RGB_CONVERT_MATRIX = new double[3, 3] { { 1, 0, 1.4022 }, { 1, -0.3456, -0.7145 }, { 1, 1.771, 0 } };
        private QueueManager<ClsPicture> queue = new QueueManager<ClsPicture>();
        private bool isRun = false;
        private Thread threadPic = null;
        public PictureWork()
        {
            
        }
        public int Add(ClsPicture info)
        {
            if (!isRun)
                return -1;
            queue.Add(info);
            return 0;
        }

        public bool Run()
        {
            if (isRun && null != this.threadPic)
                return true;
            try
            {
                isRun = true;
                threadPic = new Thread(new ThreadStart(_threadSave));
                threadPic.Start();
                return true;
            }
            catch (Exception ex)
            {
                isRun = false;
                threadPic = null;
                return false;
            }
        }
        public void Stop()
        {
            isRun = false;
            threadPic = null;
        }
        private void _threadSave()
        {
            while (isRun)
            {
                if (queue.GetQueueCount() > 0)
                {
                    SavePic(queue.Get());
                }
                else
                    Thread.Sleep(100);
            }

        }
        public void SavePic(ClsPicture pic)
        {
            Global.LogServer.Add(new LogInfo("Debug", "PictureWork->SavePic picpath:" + pic.picPath + pic.picName, (int)EnumLogLevel.DEBUG));
            string path = pic.picPath.Replace(@"\","\\");
            Global.LogServer.Add(new LogInfo("Debug", "PictureWork->SavePic picpath:" + path + pic.picName, (int)EnumLogLevel.DEBUG));

            try
            {
                if (!Directory.Exists(path))
                {
                    Directory.CreateDirectory(path);
                }
            }
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "PictureWork->SavePic 查找创建图片路径失败:" + ex.Message, (int)EnumLogLevel.ERROR));
            }

            //string sPicDst = pic.picPath+pic.picName;
           // string sPicDst = "D:\\Image\\"+ pic.picName;
            //Global.LogServer.Add(new LogInfo("Debug", "PictureWork->SavePic picpath:" + sPicDst, (int)EnumLogLevel.DEBUG));
            if (pic.picType == 3)
            {
                try
                {
                    byte[] rgbBuf = new byte[pic.picWidth * pic.picHeight * 3];
                    Bitmap bm = ConvertYUV2RGB(pic.picBufer, rgbBuf, pic.picWidth, pic.picHeight);
                    bm.Save(path + pic.picName);
                    //bm.Save(sPicDst);
                }
                catch (System.Exception ex)
                {
                    Global.LogServer.Add(new LogInfo("Error", "PictureWork->SavePic 图片存储失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                }
                
            }
        }

        private Bitmap ConvertYUV2RGB(byte[] yuvFrame, byte[] rgbFrame, int width, int height)
        {
            int uIndex = width * height;
            int vIndex = uIndex + ((width * height) >> 2);
            int gIndex = width * height;
            int bIndex = gIndex * 2;

            int temp = 0;


            //图片为pic1,RGB颜色的二进制数据转换得的int r,g,b;
            Bitmap bm = new Bitmap(width, height);

            int r = 0;
            int g = 0;
            int b = 0;


            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    // R分量
                    temp = (int)(yuvFrame[y * width + x] + (yuvFrame[vIndex + (y / 2) * (width / 2) + x / 2] - 128) * YUV2RGB_CONVERT_MATRIX[0, 2]);
                    rgbFrame[y * width + x] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));
                    // G分量
                    temp = (int)(yuvFrame[y * width + x] + (yuvFrame[uIndex + (y / 2) * (width / 2) + x / 2] - 128) * YUV2RGB_CONVERT_MATRIX[1, 1] + (yuvFrame[vIndex + (y / 2) * (width / 2) + x / 2] - 128) * YUV2RGB_CONVERT_MATRIX[1, 2]);
                    rgbFrame[gIndex + y * width + x] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));
                    // B分量
                    temp = (int)(yuvFrame[y * width + x] + (yuvFrame[uIndex + (y / 2) * (width / 2) + x / 2] - 128) * YUV2RGB_CONVERT_MATRIX[2, 1]);
                    rgbFrame[bIndex + y * width + x] = (byte)(temp < 0 ? 0 : (temp > 255 ? 255 : temp));
                    Color c = Color.FromArgb(rgbFrame[y * width + x], rgbFrame[gIndex + y * width + x], rgbFrame[bIndex + y * width + x]);
                    bm.SetPixel(x, y, c);
                }
            }
            return bm;
        }

    }
}
