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
            string ip = textNVRIP.Text.Trim();
            int port = int.Parse(textNVRPort.Text.Trim());
            string loginName = textLoginName.Text.Trim();
            string password = textPassword.Text.Trim();
            if (SPlate.SP_InitNVR(ip, port, loginName, password) == 0)
            {
                string sqlString = "insert into videohost (hosttype,hostname,hostip,hostport,loginname,loginpwd) values (" +
                    comboDeviceType.SelectedIndex.ToString() + ",'" + textName.Text.Trim() + "','" + ip + "'," + port.ToString() + ",'" + loginName + "','" + password + "')";
                Global.LogServer.Add(new LogInfo("ParamSet-Debug", "FormNVR->AddDevice sqlString:" + sqlString, (int)EnumLogLevel.DEBUG));
                Global.mysqlHelper.ExecuteSql(sqlString);
                return true;
            }
            //switch (comboDeviceType.SelectedIndex)
            //{
            //    case 0: //海康
            //        break;
            //    case 1: //科达
            //        break;
            //    case 2: //大华
            //        break;
            //    default:
            //        break;
            //}
            return false;

        }
    }
}
