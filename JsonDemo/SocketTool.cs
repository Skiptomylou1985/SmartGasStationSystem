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

namespace JsonDemo
{
    struct struClient
    {
        Socket clent;
        bool isRun;
    }
    class SocketTool
    {
        private Socket sSocket = null;
        private Socket cSocket = null;
        private bool isRun = false;
        private int maxClientNum = 1;
       
        public SocketTool(string serverIP,int serverPort)
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
            if (null != cSocket)
            {
                cSocket.Close();
                cSocket = null;
            }
            if (null != sSocket)
            {
                sSocket.Close();
                sSocket = null;
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
            while(isRun)
            {
                try
                {
                    cSocket = sSocket.Accept();
                    Thread receiveThd = new Thread(ReceiveMasssage);
                    receiveThd.Start(null);
                }
                catch (System.Exception ex)
                {
                	
                }
                
            }
        }
        private void ReceiveMasssage(object clientSocket)
        {
            //Socket myClientSocket = (Socket)clientSocket;
            while (isRun)
            {
                try
                {
                    byte[] buff = new byte[1024];
                    int count = cSocket.Receive(buff);
                    if (count > 0)
                    {
                        if (buff[0] == 0x32 && buff[1] == 0x30 && buff[2] == 0x31 && buff[3] == 0x30 && buff[4] == 0x31) //交易数据
                        {
                            int pidlenth = buff[5];
                            string pid = Encoding.Default.GetString(buff,6, pidlenth);
                            string info = Encoding.Default.GetString(buff,10+pidlenth,count-pidlenth-10);
                            JObject obj = JObject.Parse(info);
                            
                            Global.showStr = info;
                            string subinfo = info.Substring(info.IndexOf("[{")+1);

                            string msgid = obj["msgID"].ToString();
                            byte[] sendbuff = new byte[256];
                            int offset = 0;
                            Buffer.BlockCopy(buff, 0, sendbuff,offset , pidlenth + 6);
                            offset += pidlenth + 6;
                            sendbuff[offset] = (byte)msgid.Length;
                            offset += 1;
                            byte[] msgbuff = Encoding.Default.GetBytes(msgid);
                            Buffer.BlockCopy(msgbuff, 0, sendbuff, offset, msgbuff.Length);
                            offset += msgbuff.Length;
                            sendbuff[offset] = 0x31;
                            cSocket.Send(sendbuff,offset+1,0);
                            if (pid == "P91_10007")
                            {
                                TradeInfo trade = new TradeInfo();
                                trade.GasStation_NO = obj["source"].ToString();
                                trade.REQ_Time = obj["time"].ToString();
                                trade.MSG_ID = obj["msgID"].ToString();
                                trade.OilGun_NO = obj["data"][0]["1"].ToString();
                                trade.OIL_TYPE = obj["data"][0]["2"].ToString();
                                trade.OIL_Q = double.Parse(obj["data"][0]["3"].ToString());
                                trade.OIL_AMT = double.Parse(obj["data"][0]["4"].ToString());
                                trade.OIL_PRC = double.Parse(obj["data"][0]["5"].ToString());
                                trade.START_TIME = obj["data"][0]["6"].ToString();
                                trade.END_TIME = obj["data"][0]["7"].ToString();
                                trade.START_READ = double.Parse(obj["data"][0]["8"].ToString());
                                trade.END_READ = double.Parse(obj["data"][0]["9"].ToString());
                                trade.VehicleNo = obj["data"][0]["10"].ToString();
                                trade.VehicleBrand = obj["data"][0]["11"].ToString();
                                trade.SubBrand = obj["data"][0]["12"].ToString();
                                trade.VehicleModel = obj["data"][0]["13"].ToString();
                                trade.VehicleColor = obj["data"][0]["14"].ToString();
                                trade.BodyColor = obj["data"][0]["15"].ToString();
                                Global.tradeList.Add(trade);


                            } 
                            else if(pid == "P91_10003")
                            {
                                PayInfo pay = new PayInfo();
                                pay.GasStation_NO = obj["source"].ToString();
                                pay.REQ_Time = obj["time"].ToString();
                                pay.MSG_ID = obj["msgID"].ToString();
                                pay.TRANS_TYPE = obj["data"][0]["1"].ToString();
                                pay.TRANS_CODE = obj["data"][0]["2"].ToString();
                                pay.BAR_CODE = obj["data"][0]["3"].ToString();
                                pay.TRANS_Q = double.Parse(obj["data"][0]["4"].ToString());
                                pay.TRANS_PRC = double.Parse(obj["data"][0]["6"].ToString());
                                pay.TRANS_AMT = double.Parse(obj["data"][0]["5"].ToString());
                                pay.FINISH_TIME = obj["data"][0]["7"].ToString();
                                pay.SETTLE_DAY = obj["data"][0]["8"].ToString();
                                pay.OilGun_NO = obj["data"][0]["9"].ToString();
                                pay.START_READ = double.Parse(obj["data"][0]["10"].ToString());
                                pay.END_READ = double.Parse(obj["data"][0]["11"].ToString());
                                pay.BILL_NUM = obj["data"][0]["12"].ToString();
                                pay.BILL_ITEM_ID = obj["data"][0]["13"].ToString();
                                pay.POS_NO = obj["data"][0]["14"].ToString();
                                pay.StatusType = obj["data"][0]["15"].ToString();
                                pay.Pumpsrv_ref = obj["data"][0]["16"].ToString();
                                pay.PAY_MODE = obj["ext_data"][0]["1"].ToString();
                                pay.PAY_AMT = double.Parse(obj["ext_data"][0]["2"].ToString());
                                pay.Discount_AMT = double.Parse(obj["ext_data"][0]["3"].ToString());
                                pay.PAY_CARD = obj["ext_data"][0]["4"].ToString();
                                Global.payList.Add(pay);
                            }
                         }
                        else 
                        {
                             string info = Encoding.Default.GetString(buff);
                            if (info.IndexOf("PumpFlag") > 0)
                            {
                                PumpInfo pumpInfo = JsonHelper.DeserializeJsonToObject<PumpInfo>(info);
                                Global.pumpList.Add(pumpInfo);
                            }
                             
                        }
                       
                    }
                    Thread.Sleep(30);
                }
                catch (System.Exception ex)
                {
                    MessageBox.Show(ex.ToString());
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
