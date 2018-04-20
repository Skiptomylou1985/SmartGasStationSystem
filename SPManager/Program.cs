using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Diagnostics;
namespace SPManager
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

            int prcount = 0;
            foreach (Process prc in Process.GetProcesses())
            {
                if (prc.ProcessName == Process.GetCurrentProcess().ProcessName)
                {
                    prcount++;
                }
            }
            if (1 < prcount)
            {
                //MessageBox.Show("该程序已经在运行中!", "提示");
                Application.Exit();
            }
            else
            {
                Application.Run(new FormMain());
               // Application.Run(new BoardTest());
            }
        }
    }
}
