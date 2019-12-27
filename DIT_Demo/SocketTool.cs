using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
//using System.Threading.Tasks;
using System.IO;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.Windows.Forms;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Data;
using DIT_Demo;

namespace DIT_Demo
{
    struct struClient
    {
        Socket clent;
        bool isRun;
    }
    public class SocketTool
    {
        private Socket sSocket = null;
        private Socket cSocket = null;
        private TcpClient client = null;
        private TcpListener listener = null;
        private bool isRun = false;
        private int maxClientNum = 1;

        public SocketTool(string serverIP, int serverPort)
        {
            ip = serverIP;
            port = serverPort;

        }
        public SocketTool(string serverIP, int serverPort, int maxclientNum)
        {
            ip = serverIP;
            port = serverPort;
            maxClientNum = maxclientNum;
        }
        public SocketTool()
        {
        }
        public void SetIPnPort(string serverIP, int serverPort)
        {
            ip = serverIP;
            port = serverPort;
        }
        public bool Run()
        {
            try
            {
                IPAddress serverIP = IPAddress.Parse(ip);
                sSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                sSocket.Bind(new IPEndPoint(serverIP, port));  //绑定IP地址：端口  
                sSocket.Listen(maxClientNum);    //设定最多10个排队连接请求  
                isRun = true;
                Thread myThread = new Thread(ListenClientConnect);
                myThread.IsBackground = true;
                myThread.Start();
                return true;
            }
            catch (System.Exception ex)
            {
                isRun = false;
                return false;
            }

        }

        public void Send(byte[] buff)
        {
            if (isRun && cSocket != null)
            {
                try
                {
                    cSocket.Send(buff);
                }
                catch (System.Exception ex)
                {
                    cSocket = null;
                }

            }
        }
        public void Close()
        {
            isRun = false;
            if (null != sSocket)
            {
                try
                {
                    this.sSocket.Shutdown(SocketShutdown.Both);
                    //this.sSocket.Dispose();
                    this.sSocket.Close();
                    this.sSocket = null;
                }
                catch
                {
                }
            }
            
            if (null != cSocket)
            {
                try
                {
                    this.cSocket.Shutdown(SocketShutdown.Both);
                    //this.cSocket.Dispose();
                    this.cSocket.Close();
                    this.cSocket = null;
                }
                catch
                {
                }
            }

        }
        public int GetStatus()
        {
            if (isRun && null != sSocket)
            {
                return 0;
            }
            else
            {
                return -1;
            }
        }
        private void ListenClientConnect()
        {
            while (isRun)
            {
                try
                {
                    cSocket = sSocket.Accept();
                    cSocket.ReceiveTimeout = 1000;
                    Thread receiveThd = new Thread(ReceiveMasssage);
                    receiveThd.IsBackground = true;
                    receiveThd.Start(null);

                }
                catch (System.Exception ex)
                {

                }
                if (!isRun)
                {
                    break;
                }
            }
        }
        void AcceptCallBack(IAsyncResult ar)
        {
            Socket socket = ar.AsyncState as Socket;
             //结束异步Accept并获已连接的Socket
            cSocket = socket.EndAccept(ar);

            cSocket.ReceiveTimeout = 1000;
            Thread receiveThd = new Thread(ReceiveMasssage);
            receiveThd.Start(null);

            //继续异步Accept，保持Accept一直开启！
            socket.BeginAccept(AcceptCallBack, socket);
        }
        private void ReceiveMasssage(object clientSocket)
        {
           //Socket myClientSocket = (Socket)clientSocket;
            while (isRun)
            {
                try
                {
                    byte[] buff = new byte[10240];
                    
                    int count = cSocket.Receive(buff);
                    if (count > 0)
                    {
                        if (buff[0] == 0x32 && buff[1] == 0x30 && buff[2] == 0x31 && buff[3] == 0x30 && buff[4] == 0x31) //交易数据
                        {
                            int pidlenth = buff[5];
                            string pid = Encoding.Default.GetString(buff, 6, pidlenth);
                            string info = Encoding.UTF8.GetString(buff, 10 + pidlenth, count - pidlenth - 10);
                            JObject obj = null;
                            try {
                                obj = JObject.Parse(info);
                                string msgid = obj["msgID"].ToString();
                                byte[] sendbuff = new byte[256];
                                int offset = 0;
                                Buffer.BlockCopy(buff, 0, sendbuff, offset, pidlenth + 6);
                                offset += pidlenth + 6;
                                sendbuff[offset] = (byte)msgid.Length;
                                offset += 1;
                                byte[] msgbuff = Encoding.Default.GetBytes(msgid);
                                Buffer.BlockCopy(msgbuff, 0, sendbuff, offset, msgbuff.Length);
                                offset += msgbuff.Length;
                                sendbuff[offset] = 0x31;
                                cSocket.Send(sendbuff, offset + 1, 0);
                            }
                            catch (System.Exception ex) {

                                string msgid = "9999";
                                byte[] sendbuff = new byte[256];
                                int offset = 0;
                                Buffer.BlockCopy(buff, 0, sendbuff, offset, pidlenth + 6);
                                offset += pidlenth + 6;
                                sendbuff[offset] = (byte)msgid.Length;
                                offset += 1;
                                byte[] msgbuff = Encoding.Default.GetBytes(msgid);
                                Buffer.BlockCopy(msgbuff, 0, sendbuff, offset, msgbuff.Length);
                                offset += msgbuff.Length;
                                sendbuff[offset] = 0x32;
                                cSocket.Send(sendbuff, offset + 1, 0);
                                
                                continue;
                            }
                            
                            if (pid == "P91_10007")
                            {
                                try
                                {
                                //Global.LogServer.Add(new LogInfo("tradelog", "step:1", (int)EnumLogLevel.DEBUG));
                                TradeInfo trade = new TradeInfo();
                                trade.GasStation_NO = obj["source"].ToString();
                                trade.REQ_Time = obj["time"].ToString();
                                trade.MSG_ID = obj["msgID"].ToString();
                                //Global.LogServer.Add(new LogInfo("tradelog", "step:2", (int)EnumLogLevel.DEBUG));
                                trade.OilGun_NO = obj["data"][0]["1"].ToString();
                                trade.OIL_TYPE = obj["data"][0]["2"].ToString();
                                //Global.LogServer.Add(new LogInfo("tradelog", "step:3", (int)EnumLogLevel.DEBUG));

                                trade.OilName = "";
                                trade.OilCode = "";
                                trade.OilClass = "";

                                //Global.LogServer.Add(new LogInfo("tradelog", "step:4", (int)EnumLogLevel.DEBUG));
                                trade.OIL_Q = double.Parse(obj["data"][0]["3"].ToString());
                                trade.OIL_AMT = double.Parse(obj["data"][0]["4"].ToString());
                                trade.OIL_PRC = double.Parse(obj["data"][0]["5"].ToString());
                                trade.START_TIME = obj["data"][0]["6"].ToString();
                                trade.END_TIME = obj["data"][0]["7"].ToString();
                                trade.START_READ = double.Parse(obj["data"][0]["8"].ToString());
                                trade.END_READ = double.Parse(obj["data"][0]["9"].ToString());
                                //Global.LogServer.Add(new LogInfo("tradelog", "step:5", (int)EnumLogLevel.DEBUG));
                                trade.VehicleNo = obj["data"][0]["10"].ToString();
                                trade.VehicleBrandCode = obj["data"][0]["11"].ToString();
                                trade.SubBrandCode = obj["data"][0]["12"].ToString();
                                //Global.LogServer.Add(new LogInfo("tradelog", "step:6", (int)EnumLogLevel.DEBUG));
                                //if (Global.carBrandHashtable.Contains(trade.VehicleBrandCode+"-"+trade.SubBrandCode))
                                //                                     {
                                //                                        CarBrandInfo car = (CarBrandInfo)Global.carLogoHashtable[trade.VehicleBrandCode + "-" + trade.SubBrandCode];
                                //                                         trade.CarBrand = car.CarBrand;
                                //                                         trade.SubBrand = car.SubCarBrand;
                                //                                     }
                                trade.VehicleModel = obj["data"][0]["13"].ToString();
                                trade.VehicleColor = obj["data"][0]["14"].ToString();
                                trade.BodyColor = obj["data"][0]["15"].ToString();
                                
                                // Global.LogServer.Add(new LogInfo("tradelog", "step:7", (int)EnumLogLevel.DEBUG));
                                /*
                                string sql = "select count(*) from tradelog where startread = " +
                                trade.START_READ + " and endread = " + trade.END_READ;
                                DataTable dt = Global.mysqlHelper2.GetDataTable(sql);
                                if (int.Parse(dt.Rows[0][0].ToString()) == 0)
                                {
                                    Global.LogServer.Add(new LogInfo("tradelog", "SocketTool->存储加油交易信息: " + trade.toSaveSqlString(), (int)EnumLogLevel.DEBUG));
                                    int id = Global.mysqlHelper2.ExecuteSqlGetId(trade.toSaveSqlString());
                                    step = "8";
                                    if ((trade.BodyColor == "1" && trade.OilClass == "柴油") ||
                                        (trade.BodyColor == "0" && trade.OilClass == "汽油"))
                                    {
                                        Global.mysqlHelper2.ExecuteSql("update tradelog a ,carbrand b set a.realcarbrand = b.carlogo, a.realsubbrand = b.subcarlogo where a.carbrand = b.carcode and a.subbrand = b.subcarcode and a.id = " + id.ToString());
                                    }
                                    step = "9";
                                }
                                else
                                {
                                    Global.LogServer.Add(new LogInfo("tradelog", "SocketTool->存储加油交易信息,该条数据已存在 ", (int)EnumLogLevel.DEBUG));
                                }*/
                                }
                                catch (System.Exception ex)
                                {
                                    
                                }
                            } 
                            else if (pid == "P91_10003")
                            {
                                foreach(var suborder in obj["data"])
                                {
                                    OrderInfo order = new OrderInfo();
                                    order.GasStation_NO = obj["source"].ToString();
                                    order.REQ_Time = obj["time"].ToString();
                                    order.MSG_ID = obj["msgID"].ToString();
                                    order.TRANS_TYPE = suborder["1"].ToString();
                                    order.TRANS_CODE = suborder["2"].ToString();
                                    order.BAR_CODE = suborder["3"].ToString();
                                    order.TRANS_Q = double.Parse(suborder["4"].ToString());
                                    order.TRANS_PRC = double.Parse(suborder["6"].ToString());
                                    order.TRANS_AMT = double.Parse(suborder["5"].ToString());
                                    order.FINISH_TIME = suborder["7"].ToString();
                                    order.SETTLE_DAY = suborder["8"].ToString();
                                    order.OilGun_NO = suborder["9"].ToString();
                                    order.START_READ = double.Parse(suborder["10"].ToString());
                                    order.END_READ = double.Parse(suborder["11"].ToString());
                                    order.BILL_NUM = suborder["12"].ToString();
                                    order.BILL_ITEM_ID = suborder["13"].ToString();
                                    order.POS_NO = suborder["14"].ToString();
                                    order.StatusType = suborder["15"].ToString();
                                    order.Pumpsrv_ref = suborder["16"].ToString();
                                    
                                }
                                foreach(var extra in obj["ext_data"])
                                {
                                    PayInfo pay = new PayInfo();
                                    pay.BILL_NUM = obj["data"][0]["12"].ToString();
                                    pay.PAY_MODE = extra["1"].ToString();
                                    pay.PAY_AMT = double.Parse(extra["2"].ToString());
                                    pay.Discount_AMT = double.Parse(extra["3"].ToString());
                                    pay.PAY_CARD = extra["4"].ToString();
                                    
                                }
                               
                            }
                        }
                        //else if (Global.ditMode == 1) //DIT动态库模式
                        //{
                            
                        //} 
                        //else if(Global.ditMode == 2)
                        //{
                            
                        //}
                        
                    }
                    Thread.Sleep(30);
                }
                catch (System.Exception ex)
                {
                   // Global.LogServer.Add(new LogInfo("Error", "SocketTool->ReceiveMasssage ：" + ex.ToString(), (int)EnumLogLevel.ERROR));

                }

            }
        }

        public string ip
        {
            get { return _ip; }
            set { _ip = value; }
        }
        private string _ip = "127.0.0.1";

        public int port
        {
            get { return _port; }
            set { _port = value; }
        }
        private int _port = 8870;
    }
}
