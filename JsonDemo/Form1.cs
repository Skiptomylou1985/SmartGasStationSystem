using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace JsonDemo
{
    public partial class Form1 : Form
    {
        private Socket socketClient;
        private bool isConnected = false;
        private byte[] buff = new byte[1024];
        const byte Cmd_Status = 0x01;
        public Form1()
        {
            InitializeComponent();
        }

        private void btn_test_Click(object sender, EventArgs e)
        {
            try
            {
                //创建负责通信的Socket
                Socket socketSend = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPAddress ipa = IPAddress.Parse(txtIP.Text.Trim());
                IPEndPoint point = new IPEndPoint(ipa, int.Parse(txtPort.Text.Trim()));
                //获得要连接的远程服务器应用程序的IP地址和端口号
                socketSend.Connect(point);
                StationInfo info = new StationInfo();
                info.StationName = textName.Text;
                info.StationCode = textCode.Text;
                info.IP = textIP.Text;
                info.Status = comboStatus.SelectedIndex;
                info.CurrentRatio = int.Parse(textCurrent.Text.Trim());
                info.TotalRatio = int.Parse(textTotal.Text.Trim());
                info.CurrentCount = int.Parse(textCurrentCount.Text.Trim());
                info.TotalCount = int.Parse(textTotalCount.Text.Trim());
                info.SoftVersion = textVersion.Text;
                string json = JsonHelper.SerializeObject(info);
                byte[] data = System.Text.Encoding.UTF8.GetBytes(json);
                byte[] sendbuff = new byte[256];
                sendbuff[0] = 0xff;
                sendbuff[1] = 0xff;
                sendbuff[2] = Cmd_Status;
                Buffer.BlockCopy(data, 0, sendbuff, 3, data.Length);
                socketSend.Send(sendbuff, data.Length + 3, SocketFlags.None);
                socketSend.Close();
                MessageBox.Show("发送成功！");
            }
            catch
            {
                MessageBox.Show("发送失败！");
            }

            
        }
        private bool initSocket(string ip,int port)
        {
            try
            {
                //创建负责通信的Socket
                socketClient = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPAddress ipa = IPAddress.Parse(ip);
                IPEndPoint point = new IPEndPoint(ipa, port);
                //获得要连接的远程服务器应用程序的IP地址和端口号
                socketClient.Connect(point);

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
                int count = socketClient.Receive(buff);
                if (count > 5)
                {
                    if (buff[0] == 0xff && buff[1] == 0xff && buff[2] == 0x10 &&
                        buff[count-1] == 0xEE && buff[count-2] == 0xEE)
                    {
                        string info = Encoding.UTF8.GetString(buff,3,count-5);
                        Response res = JsonHelper.DeserializeJsonToObject<Response>(info);
                        if (res.Result)
                        {
                            MessageBox.Show("发送成功！");
                        }
                    }

                }
                   
                
            }
        }

        private void btn_connect_Click(object sender, EventArgs e)
        {
            if (initSocket(txtIP.Text.Trim(), int.Parse(txtPort.Text.Trim())))
            {
                MessageBox.Show("连接成功！");
            }else{
                MessageBox.Show("连接失败！");
            }
            
        }
    }
}
