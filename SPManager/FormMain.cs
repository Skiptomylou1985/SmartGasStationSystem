using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;

namespace SPManager
{
    public partial class FormMain : Form
    {
        TH_RECT th_RECT = new TH_RECT();
        
        TH_PlateResult th_PlateResult = new TH_PlateResult();
        NET_DVR_PREVIEWINFO previewInfo = new NET_DVR_PREVIEWINFO();

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
//             this.notifyIconMain.Visible = true;//在通知区显示Form的Icon
// 
//             this.WindowState = FormWindowState.Minimized;
// 
//             this.Visible = false;
// 
//             this.ShowInTaskbar = false;//使Form不在任务栏上显示
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
        
        private void btnGetCar_Click(object sender, EventArgs e)
        {
            GetCarFromDll();
        }

        private void btnBeginWithVideo_Click(object sender, EventArgs e)
        {
            SPlate.SP_BeginRecog(realVideo.Handle);
        }

        private void btnBeginRecog_Click(object sender, EventArgs e)
        {
            int ret = SPlate.SP_BeginRecog(new IntPtr());
        }

        private void btnTest_Click(object sender, EventArgs e)
        {
            SPlate.SP_TestAPI();
        }

        private void btnTimer_Click(object sender, EventArgs e)
        {
            timer1.Enabled = !timer1.Enabled;
        }

        private void btnChangeLogLevel_Click(object sender, EventArgs e)
        {
            SPlate.SP_SetLogLevel(comboLogLevel.SelectedIndex + 1);
        }

        private void btnInit_Click(object sender, EventArgs e)
        {
            int ret = Init();
            if (ret == 0)
                return;
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
    }
}
