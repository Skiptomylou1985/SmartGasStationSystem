using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using Emgu.CV;
using Emgu.CV.Structure;

namespace SPManager.tool
{
    public class PictureWork
    {
        private double[,] YUV2RGB_CONVERT_MATRIX = new double[3, 3] { { 1, 0, 1.4022 }, { 1, -0.3456, -0.7145 }, { 1, 1.771, 0 } };
        private QueueManager<struPic> queue = new QueueManager<struPic>();
        private bool isRun = false;
        private Thread threadPic = null;
        private Dictionary<int, string> nameDic = new Dictionary<int, string>();
        public PictureWork()
        {
            nameDic.Add(1, "entry.jpg");
            nameDic.Add(2, "gas.jpg");
            nameDic.Add(3, "exit.jpg");
        }
        public int Add(struPic info)
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
                    struPic info = queue.Get();
                }
                else
                    Thread.Sleep(100);
            }

        }
        private void SavePic(struPic pic)
        {
            string sPicDst = pic.sPicPath+"\\"+nameDic[1];
            MCvMat dst = new MCvMat();
            
            
        }


    }
}
