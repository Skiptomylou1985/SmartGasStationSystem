using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ParamSet
{
    public partial class FormStationInfo : Form
    {
        public FormStationInfo()
        {
            InitializeComponent();
        }

        private void textPicPath_MouseClick(object sender, MouseEventArgs e)
        {
            FolderBrowserDialog folder = new FolderBrowserDialog();
            if (folder.ShowDialog() == DialogResult.OK)
            {

                Global.basePicPath = folder.SelectedPath;
            }
            textPicPath.Text = Global.basePicPath;
        }

        private void btnSet_Click(object sender, EventArgs e)
        {
            Global.stationInfo.stationName = textStationName.Text.Trim();
            updateParam("stationname", Global.stationInfo.stationName);
            Global.stationInfo.stationCode = textStationCode.Text.Trim();
            updateParam("stationcode", Global.stationInfo.stationCode);
            Global.nMatchMode = comboMatchMode.SelectedIndex + 1;
            updateParam("matchmode", Global.nMatchMode.ToString());
            Global.nLogLevel = comboLogLevel.SelectedIndex + 1;
            updateParam("loglevel", Global.nLogLevel.ToString());
            Global.basePicPath = textPicPath.Text.Trim();
            updateParam("picpath", Global.basePicPath);

            MessageBox.Show("设置成功!");

        }
        private void updateParam(string key,string value)
        {
            string sqlString = "update param set paramValue = '" + value + "' where paramName = '" + key + "'";
            Global.mysqlHelper.ExecuteSql(sqlString);
        }

        private void FormStationInfo_Load(object sender, EventArgs e)
        {
            textStationName.Text = Global.stationInfo.stationName;
            textStationCode.Text = Global.stationInfo.stationCode;
            comboMatchMode.SelectedIndex = Global.nMatchMode - 1;
            comboLogLevel.SelectedIndex = Global.nLogLevel - 1;
            textPicPath.Text = Global.basePicPath;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
