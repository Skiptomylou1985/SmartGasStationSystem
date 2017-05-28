using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Diagnostics;
using System.Threading;
namespace Moniter
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Thread.Sleep(1000);
            foreach (Process prc in Process.GetProcesses())
            {
                if (prc.ProcessName=="SPManager")
                {
                    //if (!prc.CloseMainWindow())
                   // prc.CloseMainWindow();
                    prc.Kill(); //当发送关闭窗口命令无效时强行结束进程 
                }
            }
            Application.Exit();
            //Application.Run(new Form1());
        }
    }
}
