using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
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
           
            Global.nLogLevel = comboLogLevel.SelectedIndex + 1;
            updateParam("loglevel", Global.nLogLevel.ToString());
            Global.basePicPath = textPicPath.Text.Trim();
            updateParam("picpath", Global.basePicPath);

            MessageBox.Show("设置成功!");
            this.Close();

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
            comboAuthType.SelectedIndex = Global.nAuthType;
            comboCapture.SelectedIndex = Global.nCaptureFlag;
            comboVideoRecog.SelectedIndex = Global.nVideoRecogFlag;
            comboVideoRecogType.SelectedIndex = Global.nVideoRecogType;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void btnSetRecogInfo_Click(object sender, EventArgs e)
        {
            Global.nCaptureFlag = comboCapture.SelectedIndex; //
            updateParam("captureflag", Global.nCaptureFlag.ToString());
            Global.nVideoRecogFlag = comboVideoRecog.SelectedIndex;
            updateParam("videorecog", Global.nVideoRecogFlag.ToString());
            Global.nVideoRecogType = comboVideoRecogType.SelectedIndex; // 0 算法识别，1 海康超脑，2大华超脑
            updateParam("videorecogtype", Global.nVideoRecogType.ToString());
            Global.nMatchMode = comboMatchMode.SelectedIndex + 1;
            updateParam("matchmode", Global.nMatchMode.ToString());
            try
            {
                if (File.Exists(Application.StartupPath + @"//TH_PLATEID.dll"))
                {
                    File.Delete(Application.StartupPath + @"//TH_PLATEID.dll");
                }
                if (comboAuthType.SelectedIndex == 0)
                {
                    FileInfo f = new FileInfo(Application.StartupPath + "//localAuth//TH_PLATEID.dll");
                    f.CopyTo(Application.StartupPath + @"//TH_PLATEID.dll");
                }
                else if (comboAuthType.SelectedIndex == 1)
                {
                    FileInfo f = new FileInfo(Application.StartupPath + "//netAuth//TH_PLATEID.dll");
                    f.CopyTo(Application.StartupPath + @"//TH_PLATEID.dll");
                }
                Global.nAuthType = comboAuthType.SelectedIndex;  //算法授权模式 0本地授权 1 网络授权
                updateParam("authtype", Global.nAuthType.ToString());
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("更新授权方式失败，" + ex.Message);
            }
            MessageBox.Show("设置识别参数成功！");
            // Global.nVideoSource = ;  //0海康 1大华 2科达
            // updateParam("videosource", Global.nVideoSource.ToString());
        }
    }
}
