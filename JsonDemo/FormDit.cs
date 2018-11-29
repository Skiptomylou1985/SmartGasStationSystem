using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace JsonDemo
{
    
    public partial class FormDit : Form
    {
       
        private Socket socketSend;
        private bool isConnected = false;
        SocketTool socketServer;
        public FormDit()
        {
            InitializeComponent();
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void btn_link_Click(object sender, EventArgs e)
        {
            if (btn_link.Text == "连接")
            {
                if (connectDit(txtIP.Text.Trim(), int.Parse(txtPort.Text.Trim())))
                {
                    btn_link.Text = "断开";
                    MessageBox.Show("连接成功!");
                    
                }
            } 
            else
            {
                isConnected = false;
                socketSend.Close();
                btn_link.Text = "连接";
            }
            
        }

        private bool connectDit(string ip, int port)
        {
            try
            {
                //创建负责通信的Socket
                socketSend = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPAddress ipa = IPAddress.Parse(ip);
                IPEndPoint point = new IPEndPoint(ipa, port);
                //获得要连接的远程服务器应用程序的IP地址和端口号
                socketSend.Connect(point);

                //开启一个新的线程不停的接收服务端发来的消息
                Thread th = new Thread(Recive);
                th.IsBackground = true;
                isConnected = true;
                th.Start();
                return true;
            }
            catch
            {
                return false;
            }
        }
        void Recive()
        {
            while (isConnected)
            {
                try
                {
                    byte[] buff = new byte[512];
                    int count = socketSend.Receive(buff);
                    if (count > 5)
                    {

                    }
                }
                catch (System.Exception ex)
                {
                	
                }
               
                
            }
        }

        private void btn_open_Click(object sender, EventArgs e)
        {
            if (btn_open.Text == "开启服务")
            {
                socketServer = new SocketTool("0.0.0.0", int.Parse(txtServerPort.Text.Trim()));
                socketServer.Run();
                btn_open.Text = "关闭服务";
                timerDit.Enabled = true;
            } 
            else
            {
                socketServer.Close();
                btn_open.Text = "开启服务";
                timerDit.Enabled = false;
            }
            
        }

        private void btn_send_Click(object sender, EventArgs e)
        {
            VehicelInfo info = new VehicelInfo();
            info.Flag = (comboFlag.SelectedIndex + 1).ToString();
            info.Time = DateTime.Now.ToString("yyyy-MM-dd hh:mm:ss");
            info.VehicleNo = textVehicleNo.Text;
            info.VehicleBrand = textVehicleBrand.Text;
            info.SubBrand = textSubBrand.Text;
            info.VehicleModel = comboVehicleModel.Text;
            info.VehicleColor = comboVehicleColor.Text;
            info.BodyColor = comboBodyColor.Text;
            lblTime.Text = info.Time;
            string infoJson = JsonHelper.SerializeObject(info);
            //byte [] buf = System.Text.Encoding.UTF8.GetBytes(infoJson);
           // byte[] buf = System.Text.Encoding.ASCII.GetBytes(infoJson);
           // socketSend.Send(buf);
            string covert = Encoding.GetEncoding("GBK").GetString(Encoding.Default.GetBytes(infoJson));
            socketSend.Send(Encoding.Default.GetBytes(covert));
        }

        private void timerDit_Tick(object sender, EventArgs e)
        {
            if (Global.pumpList.Count > 0)
            {
                PumpInfo pumpInfo = Global.pumpList[0];
                lblPumpId.Text = pumpInfo.PumpID;
                lblPumpFlag.Text = pumpInfo.PumpFlag;
                lblVolume.Text = pumpInfo.Volume;
                lblValue.Text = pumpInfo.Value;
                lblGradeID.Text = pumpInfo.GradeID;
                lblPumpTime.Text = pumpInfo.Time;


                PumpBackInfo backInfo = new PumpBackInfo();
                backInfo.VehicleNo = textVehicleNo.Text;
                backInfo.VehicleBrand = textVehicleBrand.Text;
                backInfo.SubBrand = textSubBrand.Text;
                backInfo.VehicleModel = comboVehicleModel.Text;
                backInfo.VehicleColor = comboVehicleColor.Text;
                backInfo.BodyColor = comboBodyColor.Text;
                string infoJson = JsonHelper.SerializeObject(backInfo);
                //byte[] buf = System.Text.Encoding.UTF8.GetBytes(infoJson);
                string covert = Encoding.GetEncoding("GBK").GetString(Encoding.Default.GetBytes(infoJson));
              
                socketServer.Send(Encoding.Default.GetBytes(covert));
                Global.pumpList.RemoveAt(0);
            }
        }

        private void btn_test_Click(object sender, EventArgs e)
        {
            PumpInfo pumpInfo = new PumpInfo();
//             pumpInfo.PumpID =  1;
//             pumpInfo.PumpFlag = 1;
//             pumpInfo.Volume = 10.0;
//             pumpInfo.Value = 82.0;
            pumpInfo.GradeID = "300665";
            pumpInfo.Time = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
            string infoJson = JsonHelper.SerializeObject(pumpInfo);
            byte[] buf = System.Text.Encoding.UTF8.GetBytes(infoJson);
            socketSend.Send(buf);

        }

        private void FormDit_Load(object sender, EventArgs e)
        {
            comboFlag.SelectedIndex = 0;
            comboBodyColor.SelectedIndex = 0;
            comboVehicleColor.SelectedIndex = 0;
            comboVehicleModel.SelectedIndex = 0;
            textVehicleBrand.Text = "丰田";
            textSubBrand.Text = "皇冠";
        }
    }
}
