using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace DIT_Demo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            HCNetSDK.NET_DVR_Init();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            HCNetSDK.NET_DVR_TestAPI();
        }
    }
}
