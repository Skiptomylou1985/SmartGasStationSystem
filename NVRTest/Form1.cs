using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace NVRTest
{
    public partial class Form1 : Form
    {
        private NET_DVR_PREVIEWINFO[] viewInfo;
        private long[] playHandle;
        IntPtr playWindow ;
        public Form1()
        {
            InitializeComponent();
            viewInfo = new NET_DVR_PREVIEWINFO[8];
            playHandle = new long[8];
            playWindow = new IntPtr();
            for (int i=0;i<viewInfo.Length;i++)
            {
                viewInfo[i].lChannel = i+33;
                viewInfo[i].dwLinkMode = 0;
                viewInfo[i].bBlocked = false;
                viewInfo[i].dwDisplayBufNum = 15;
            }
        }
        
        private void btnInit_Click(object sender, EventArgs e)
        {
            int i = SPlate.SP_InitNVR(textIP.Text.Trim(), int.Parse(textPort.Text.Trim()), textUser.Text.Trim(), textPwd.Text.Trim());
            if (i != 0)
            {
                MessageBox.Show("初始化失败，返回值：" + i.ToString());
            }
        }

        private void btnView_Click(object sender, EventArgs e)
        {
            int index = comboChan.SelectedIndex;
            viewInfo[index].hPlayWnd = playWindow;
            playHandle[index] = SPlate.SP_PreviewInfo(ref viewInfo[index],Marshal.SizeOf(viewInfo[index]));
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            playWindow = pictureBox1.Handle;

        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            playWindow = pictureBox2.Handle;
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            playWindow = pictureBox3.Handle;
        }

        private void pictureBox4_Click(object sender, EventArgs e)
        {
            playWindow = pictureBox4.Handle;
        }
    }
}
