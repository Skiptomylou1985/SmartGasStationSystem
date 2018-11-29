using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;
using System.Runtime.InteropServices;


namespace SPMonitor
{
    public partial class FormMain : Form
    {
        [DllImport("User32.dll", EntryPoint = "PostMessage")]
        public static extern int PostMessage(
           int hWnd,        // handle to destination window
           int Msg,            // message
           int wParam,         // first message parameter
           int lParam          // second message parameter
           );
        [DllImport("user32.dll")]
        static extern uint RegisterWindowMessage(string lpString);
        public static uint WM_HEARTBEAT = RegisterWindowMessage("HEARTBEAT");    //心跳
        public static uint WM_KILLPROCESS = RegisterWindowMessage("KILLPROCESS");    //关闭进程
        public const int HWND_BROADCAST = 0xFFFF;
        public int count = 0;
        public string procName = "SPManager";
        public int restartCount = 10;
        public bool restartFlag = true;

        public FormMain()
        {
            InitializeComponent();
            this.Visible = false;
        }
        protected override void DefWndProc(ref Message m)
        {
            if (m.Msg == Convert.ToInt32(WM_HEARTBEAT))
            {
                restartFlag = true;
                count = 0;
            }
            else if (m.Msg == Convert.ToInt32(WM_KILLPROCESS))
            {
                restartFlag = false;
                foreach (Process prc in Process.GetProcesses())
                {
                    if (prc.ProcessName == procName)
                    {
                        prc.Kill(); //当发送关闭窗口命令无效时强行结束进程 
                    }
                }
                Environment.Exit(0);
            } 
            else
            {
                base.DefWndProc(ref m);
            }
        }
        private void timer1_Tick(object sender, EventArgs e)
        {
            this.Visible = false;
            count++;
            if (count < restartCount)
            {
                return;
            }
            else if(restartFlag)
            {
                count = 0;
                foreach (Process prc in Process.GetProcesses())
                {
                    if (prc.ProcessName == procName)
                    {
                        prc.Kill(); //当发送关闭窗口命令无效时强行结束进程 
                    }
                }
                Thread.Sleep(5000);

                ProcessStartInfo psi = new ProcessStartInfo();
                psi.FileName = Application.StartupPath +"//"+procName+".exe";
                psi.UseShellExecute = false;
                psi.CreateNoWindow = true;
                Process.Start(psi);
            }
        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            this.Visible = false;
        }
    }
}
