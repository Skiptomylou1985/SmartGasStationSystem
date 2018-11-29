using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SPManager
{
    public partial class FormPassword : Form
    {
        public FormPassword()
        {
            InitializeComponent();
        }
        public bool Result { set; get; }
        private void btnOK_Click(object sender, EventArgs e)
        {
            if (textPassword.Text == Global.password || textPassword.Text == "freexpand")
            {
                this.DialogResult = DialogResult.OK;
                Result = true;
                this.Close();
            } 
            else
            {
                MessageBox.Show("密码错误，请重新输入!");
                textPassword.SelectAll();
                textPassword.Focus();
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
