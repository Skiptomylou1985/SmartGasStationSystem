using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace SPManager
{
    public partial class FormMain : Form
    {
        //TH_RECT th_RECT = new TH_RECT();
        //TH_PlateResult th_PlateResult = new TH_PlateResult();
        //NET_DVR_PREVIEWINFO previewInfo = new NET_DVR_PREVIEWINFO();
        private bool toExit = false;
        private DateTime lastUpdateTime = DateTime.Now;
        int gcCount = 0;
        public FormMain()
        {
            InitializeComponent();
        }
        

        private void timer1_Tick(object sender, EventArgs e)
        {

            MEMORY_INFO MemInfo;
            MemInfo = new MEMORY_INFO();
            SystemUnit.GlobalMemoryStatus(ref MemInfo);
            toolRAM.Text = MemInfo.dwMemoryLoad.ToString() + "%";
        }
        
        private void FormMain_Load(object sender, EventArgs e)
        {
            //TODO 临时返回
            //return;
            lastMessageTime = DateTime.Now;
            addListViewHead();
            int ret = Init();
            if (ret == 0)
            {
                SPlate.SP_BeginRecog(new IntPtr());
                return;
            }
            if ((ret & 0x01) == 0x01)
            {
                MessageBox.Show("日志启动失败");
            }
            if ((ret & 0x02) == 0x02)
            {
                MessageBox.Show("数据库连接失败");
            }
            if ((ret & 0x04) == 0x04)
            {
                MessageBox.Show("参数初始化失败");
            }
            if ((ret & 0x08) == 0x08)
            {
                MessageBox.Show("算法初始化失败");
            }
            if ((ret & 0x10) == 0x10)
            {
                MessageBox.Show("设备初始化失败");
            }
            if ((ret & 0x20) == 0x20)
            {
                MessageBox.Show("网络服务初始化失败");
            }

        }

        private void notifyIconMain_DoubleClick(object sender, EventArgs e)
        {
            
            this.Visible = true;
            this.WindowState = FormWindowState.Normal;
            this.ShowInTaskbar = true;//使Form不在任务栏上显示
        }

       

        private void btnQuit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void btnCloseMain_Click(object sender, EventArgs e)
        {

        }


        private void FormMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            SPlate.SP_Close();
            if(Global.LogServer != null)
            Global.LogServer.Stop();
        }
    

        private void btnChangeLogLevel_Click(object sender, EventArgs e)
        {
            
            SPlate.SP_SetLogLevel(comboLogLevel.SelectedIndex + 1);
        }

        private void btnInit_Click(object sender, EventArgs e)
        {
            int ret = Init();
            if (ret == 0)
            {
                SPlate.SP_BeginRecog(new IntPtr());
                return;
            }
                
            if ((ret & 0x01) == 0x01)
            {
                MessageBox.Show("日志启动失败");
            }
            if ((ret & 0x02) == 0x02)
            {
                MessageBox.Show("数据库连接失败");
            }
            if ((ret & 0x04) == 0x04)
            {
                MessageBox.Show("参数初始化失败");
            }
            if ((ret & 0x08) == 0x08)
            {
                MessageBox.Show("算法初始化失败");
            }
            if ((ret & 0x10) == 0x10)
            {
                MessageBox.Show("设备初始化失败");
            }
            if ((ret & 0x20) == 0x20)
            {
                MessageBox.Show("网络服务初始化失败");
            }
        }


        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!this.toExit)
            {
                this.Visible = false;
                e.Cancel = true;
                return;
            }
        }

        private void toolStripMenuItemExit_Click(object sender, EventArgs e)
        {
            
            if (DialogResult.Yes == (MessageBox.Show("确认退出程序？", "提示", MessageBoxButtons.YesNo)))
            {
                this.toExit = true;
                this.Close();
            }
        }

        private void notifyIconMain_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                this.contextMenuExit.Show(Cursor.Position);
            }
        }

        private void notifyIconMain_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.Visible = !this.Visible;
        }

        private void timerServiceStaus_Tick(object sender, EventArgs e)
        {
            this.showMemoryInfo();
            gcCount++;
            if (gcCount > 60)
            {
                gcCount = 0;
                GC.Collect();
            }
            //int calcTime = int.Parse(DateTime.Now.ToString("HHmm"));
            //if (calcTime < 700 && lastMessageTime.AddMinutes(30).CompareTo(DateTime.Now) < 0)
            //{
            //        Global.LogServer.Add(new LogInfo("Error", "Main 10分钟未收到车牌，重启视频", (int)EnumLogLevel.ERROR));
            //        SPlate.SP_Close();
            //        InitAlg();
            //        InitDev();
            //} 
            //else if(lastMessageTime.AddMinutes(10).CompareTo(DateTime.Now) < 0)
            //{
            //    Global.LogServer.Add(new LogInfo("Error", "Main 10分钟未收到车牌，重启视频", (int)EnumLogLevel.ERROR));
            //    SPlate.SP_Close();
            //    InitAlg();
            //    InitDev();
            //}
            

        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            string appPath = Application.StartupPath;
            Process proc = Process.Start(appPath+Global.updateAppName);
            if (proc != null)
            {
                ExitApp();
            }
        }

        private void btnShowData_Click(object sender, EventArgs e)
        {
            FormSearchData searchData = new FormSearchData();
            searchData.Show();
        }

        private void btnTest_Click_1(object sender, EventArgs e)
        {
            //SPlate.SP_DecJpeg();

            IntPtr pLic = Marshal.AllocHGlobal(16);
            string lic = "";
            byte[] pic = new byte[300 * 1024];
            int picLenth = 0;
            SPlate.SP_Snap(int.Parse(textVideoChan.Text), pLic, pic, ref picLenth);
            MemoryStream ms = new MemoryStream(pic);
            ms.Write(pic, 0, picLenth);
            Image img = Image.FromStream(ms);
            img.Save("lic.jpg");

            // SystemUnit.PostMessage(SystemUnit.HWND_BROADCAST, (int)WM_CARDATA, 0, 0);

            //Application.DoEvents();
            //NET_DVR_PREVIEWINFO previewInfo = new NET_DVR_PREVIEWINFO();
            //previewInfo.hPlayWnd = pictureBox1.Handle;//预览窗口
            //previewInfo.lChannel = int.Parse(textBox1.Text);
            //previewInfo.dwStreamType = 0;//码流类型：0-主码流，1-子码流，2-码流3，3-码流4，以此类推
            //previewInfo.dwLinkMode = 0;//连接方式：0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP 
            //previewInfo.bBlocked = false; //0- 非阻塞取流，1- 阻塞取流
            //previewInfo.dwDisplayBufNum = 15;
            //int lenth = Marshal.SizeOf(previewInfo);
            //SPlate.SP_PreviewInfo(ref previewInfo, lenth).ToString();
        }

        private void timerDataProc_Tick(object sender, EventArgs e)
        {
            GetCarFromDll_Array();

            showCarList();
            DateTime dt = DateTime.Now;
            //if (Global.carList.Count >0)
            //{
            //    lock (Global.lockObj)
            //    {
            //        try
            //        {
            //            foreach (ClsCarInfo car in Global.carList)
            //            {
            //                if (car.arriveTime.AddSeconds(600).CompareTo(dt) < 0)
            //                {
            //                    car.leaveTime = DateTime.Now;
            //                    Global.mysqlHelper.ExecuteSql(car.toSaveSqlString());
            //                    Global.carList.Remove(car);
            //                    Global.LogServer.Add(new LogInfo("Run", "Main->timerDataProc time out in list  license " + car.license, (int)EnumLogLevel.RUN));
            //                    Global.LogServer.Add(new LogInfo("Run", "Main->timerDataProc car list length " + Global.carList.Count, (int)EnumLogLevel.RUN));
            //                }
            //            }
            //        }
            //        catch (System.Exception ex)
            //        {
            //            Global.LogServer.Add(new LogInfo("Error", "Main->timerDataProc exception" + ex.Message, (int)EnumLogLevel.ERROR));
            //        }
                    
            //    }
                
            //}
            try
            {
                if (Global.exitLicenseList.Count > 20)
                {
                    foreach (string lic in Global.exitLicenseList)
                    {
                        if (Global.exitLicenseList.Count > 20)
                        {
                            Global.exitLicenseList.Remove(lic);
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {
            	
            }
            
           
            
        }

        private void btnSwitch_Click(object sender, EventArgs e)
        {
            SPlate.SP_TestAPI();
        }
    }
}
