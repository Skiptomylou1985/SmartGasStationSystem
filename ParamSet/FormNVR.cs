using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ParamSet
{
    public partial class FormNVR : Form
    {
        public FormNVR()
        {
            InitializeComponent();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (AddDevice())
            {
                MessageBox.Show("设备添加成功!");
                this.Close();
            } 
            else
            {
                MessageBox.Show("输入信息有误，无法添加设备！");
            }
            
        }
        private bool AddDevice()
        {
            return false;

        }
    }
}
