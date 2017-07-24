using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace DIT_Demo
{
    public partial class FormDIT : Form
    {
        public Dictionary<int, string> dicPlateColor = new Dictionary<int, string>();
        public Dictionary<int, string> dicCarColor = new Dictionary<int, string>();
        public Dictionary<int, string> dicCarBrand = new Dictionary<int, string>();
        public Dictionary<int, string> dicInOut = new Dictionary<int, string>();
        public FormDIT()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (HCNetSDK.NET_DVR_Init())
            {
                NET_DVR_DEVICEINFO_V30 device = new NET_DVR_DEVICEINFO_V30();
               if (HCNetSDK.NET_DVR_Login_V30(textIP.Text.Trim(),8870,"admin","12345",ref device) == 0)
               {
                    MessageBox.Show("连接成功");
               }
               else
                {
                    MessageBox.Show("连接失败");
                }
            }
            else
            {
                MessageBox.Show("初始化失败");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            HCNetSDK.NET_DVR_Cleanup();
        }

        private void btnSetCallback_Click(object sender, EventArgs e)
        {
            HCNetSDK.MSGCallBack_V31 plateCallBack = new HCNetSDK.MSGCallBack_V31(PlateDataCallBack);
            IntPtr pUser = new IntPtr();
            if (HCNetSDK.NET_DVR_SetDVRMessageCallBack_V31(plateCallBack, pUser))
            {
                MessageBox.Show("注册回调函数成功");
            }
        }
        public void PlateDataCallBack(int lcomd, IntPtr para1, IntPtr pAlarmInfo, int lenth, IntPtr pUser)
        {
            int a = lcomd;
            NET_ITS_PLATE_RESULT plateInfo = new NET_ITS_PLATE_RESULT();
            int b = Marshal.SizeOf(plateInfo);
            plateInfo = (NET_ITS_PLATE_RESULT)Marshal.PtrToStructure(pAlarmInfo, typeof(NET_ITS_PLATE_RESULT));
            lblPlate.Text = System.Text.Encoding.Default.GetString(plateInfo.sLicense);
            lblPlateColor.Text = dicPlateColor[plateInfo.byPlateColor];
            lblCarBrand.Text = dicCarBrand[plateInfo.wVehicleLogoRecog];
            lblCarColor.Text = dicCarColor[plateInfo.byColor];
            lblInOut.Text = dicInOut[plateInfo.byVehicleState];
            lblCarSubBrand.Text = "未知";
            lblCarType.Text = "未知";

        }

        private void btnSnap_Click(object sender, EventArgs e)
        {
            NET_DVR_MANUALSNAP snap = new NET_DVR_MANUALSNAP();
            snap.byPumpID = (byte)comboNozzle.SelectedIndex;
            snap.byPumpStatus = (byte)comboNozzleStatus.SelectedIndex;
            NET_DVR_PLATE_RESULT plateResult = new NET_DVR_PLATE_RESULT();
            IntPtr ret = Marshal.AllocHGlobal(Marshal.SizeOf(plateResult));
            if (HCNetSDK.NET_DVR_ManualSnap(0, ref snap, ret))
            {
                plateResult = (NET_DVR_PLATE_RESULT)Marshal.PtrToStructure(ret, typeof(NET_DVR_PLATE_RESULT));
                lblPlate.Text = System.Text.Encoding.Default.GetString(plateResult.sLicense);
                lblPlateColor.Text = dicPlateColor[plateResult.byPlateColor];
                lblCarBrand.Text = dicCarBrand[plateResult.wVehicleLogoRecog];
                lblCarColor.Text = dicCarColor[plateResult.byColor];
                lblCarSubBrand.Text = "未知";
                lblCarType.Text = "未知";
            }
            else
            {
                MessageBox.Show("抓拍失败");
            }
        }

        private void FormDIT_Load(object sender, EventArgs e)
        {
            comboNozzle.SelectedIndex = 0;
            comboNozzleStatus.SelectedIndex = 1;
            dicCarColor.Add(0, "白色");
            dicCarColor.Add(1, "银色");
            dicCarColor.Add(2, "黄色");
            dicCarColor.Add(3, "粉色");
            dicCarColor.Add(4, "红色");
            dicCarColor.Add(5, "绿色");
            dicCarColor.Add(6, "蓝色");
            dicCarColor.Add(7, "棕色");
            dicCarColor.Add(8, "黑色");

            dicPlateColor.Add(0, "未知");
            dicPlateColor.Add(1, "蓝色");
            dicPlateColor.Add(2, "黄色");
            dicPlateColor.Add(3, "白色");
            dicPlateColor.Add(4, "黑色");
            dicPlateColor.Add(5, "绿色");

            dicCarBrand.Add(0, "未知");
            dicCarBrand.Add(1, "奥迪");
            dicCarBrand.Add(2, "宝马");
            dicCarBrand.Add(3, "奔驰");
            dicCarBrand.Add(4, "本田");
            dicCarBrand.Add(5, "标致");
            dicCarBrand.Add(6, "别克");
            dicCarBrand.Add(7, "大众");
            dicCarBrand.Add(8, "丰田");
            dicCarBrand.Add(9, "福特");

            dicInOut.Add(1, "进站");
            dicInOut.Add(2, "出站");
        }

        private void btnSendTrade_Click(object sender, EventArgs e)
        {
            NET_ITS_TRANS_INFO trade = new NET_ITS_TRANS_INFO();
            trade.sStartTime = new byte[20];
            trade.sEndTime = new byte[20];
            //int a = Marshal.SizeOf(trade);
            trade.nPumpID = (byte)comboNozzle.SelectedIndex;
            trade.nOilType = 92;
            trade.fTradeLitre = 3.2f;
            trade.fTradeMoney = 35.0f;
            trade.fTradePrice = 6.80f;
            trade.fStartRead = 1000.1f;
            trade.fEndRead = 1003.3f;
            string time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            byte[] byTime = System.Text.Encoding.Default.GetBytes(time);
            Buffer.BlockCopy(byTime, 0, trade.sStartTime, 0, byTime.Length);
            Buffer.BlockCopy(byTime, 0, trade.sEndTime, 0, byTime.Length);
            HCNetSDK.NET_DVR_SendTrans(trade);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string a = "鲁A12345";
            MessageBox.Show(a.Substring(1));
        }
    }
}
