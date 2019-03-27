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
        MysqlHelper mysqlHelper;
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

        private void txtIP_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void txtPort_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {

            ClsCarInfo car = new ClsCarInfo();
            car.license = "abc";
            car.StartCounter = 12.1;
            car.Price = 1.1;
            car.volume = 1.2;
            car.EndCounter = 13.1;
            //MessageBox.Show(car.toSaveSqlString());
            
            mysqlHelper.ExecuteSql(car.toSaveSqlString());
            return;

            Upload load = new Upload();
            UpLoadTradeInfo info = new UpLoadTradeInfo();
            string sql = "select * from tradelog where upload = 0 order by id desc limit 1";
            System.Data.DataTable dt = mysqlHelper.GetDataTable(sql);
            if (dt != null && dt.Rows.Count > 0)
            {
                info.id = int.Parse(dt.Rows[0]["id"].ToString());
                info.carBrand = int.Parse(dt.Rows[0]["carbrand"].ToString());
                info.carColor = int.Parse(dt.Rows[0]["carcolor"].ToString());
                info.carNumColor = int.Parse(dt.Rows[0]["carnumcolor"].ToString());
                info.carType = int.Parse(dt.Rows[0]["cartype"].ToString());
                info.carNumber = dt.Rows[0]["carnumber"].ToString();
                info.carBrand = int.Parse(dt.Rows[0]["carbrand"].ToString());
                info.stationName = "测试站";
                info.stationCode = "X001";
                info.nozzleNo = int.Parse(dt.Rows[0]["nozzleno"].ToString());
                info.oilClass = dt.Rows[0]["oilclass"].ToString();
                info.meterialCode = dt.Rows[0]["meterialcode"].ToString();
                info.oilCode = dt.Rows[0]["oilcode"].ToString();
                info.oilName = dt.Rows[0]["oilname"].ToString();
                info.price = double.Parse(dt.Rows[0]["price"].ToString()); ;
                info.realAmount = double.Parse(dt.Rows[0]["realamount"].ToString());
                info.realCarBrand = dt.Rows[0]["realcarbrand"].ToString();
                info.realSubBrand = dt.Rows[0]["realsubbrand"].ToString();
                info.startRead = double.Parse(dt.Rows[0]["startread"].ToString());
                info.endRead = double.Parse(dt.Rows[0]["endread"].ToString());
                info.startTime = DateTime.Parse(dt.Rows[0]["starttime"].ToString());

                System.DateTime startTime = TimeZone.CurrentTimeZone.ToLocalTime(new System.DateTime(1970, 1, 1)); // 当地时区
                long timeStamp = (long)(info.startTime - startTime).TotalSeconds; // 相差秒数
                info.endTime = DateTime.Parse(dt.Rows[0]["endtime"].ToString());
            }



            //             info.id = 1;
            //             info.stationname = "测试站";
            //             info.stationcode = "X001";
            //             info.nozzleno = 2;
            //             info.oilclass = "汽油";
            //             info.meterialcode = "300876";
            //             info.oilcode = "92#";
            //             info.oilname = "92号汽油";
            //             info.price = 8.1;
            //             info.realamount = 69.8;
            //             info.realcarbrand = "丰田";
            //             info.realsubbrand = "皇冠";
            //             info.startread = 4123.2;
            //             info.endread = 4182.1;
            //             info.starttime = "2018-01-01 12:34:52";
            //             info.endtime = "2018-01-01 12:36:52";

            load.DoUpload(info, "http://47.95.13.182:8080/fulin/business/oilstation/add/trade");
            //load.DoUpload(info, "http://47.95.13.182:8080/fulin/business/worktrade/add");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DBInfo DBinfo = new DBInfo();
            DBinfo.ip = "47.95.13.182";
            DBinfo.dbname = "gsims";
            DBinfo.password = "root";
            DBinfo.username = "root";
            DBinfo.port = 3306;
            DBinfo.type = "mysql";
            mysqlHelper = new MysqlHelper(DBinfo);
        }
    }
}
