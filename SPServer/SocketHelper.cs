using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.Data;

namespace SPServer
{

    public class SocketHelper
    {
        private Socket sSocket = null;
        private bool isRun = false;
        private int maxClientNum = 20;
        static Dictionary<string, Socket> clientConnectionItems = new Dictionary<string, Socket> { };

        public SocketHelper(string serverIP, int serverPort)
        {
            ip = serverIP;
            port = serverPort;

        }
        public SocketHelper(string serverIP, int serverPort, int maxclientNum)
        {
            ip = serverIP;
            port = serverPort;
            maxClientNum = maxclientNum;
        }
        public SocketHelper()
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

        public void Send(Socket cSocket, byte[] buff)
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
            Socket connection = null;
            while (true)
            {
                try
                {
                    connection = sSocket.Accept();
                }
                catch (System.Exception ex)
                {
                    break;
                }
                if (!isRun)
                {
                    break;
                }
                IPAddress clientIP = (connection.RemoteEndPoint as IPEndPoint).Address;
                int clientPort = (connection.RemoteEndPoint as IPEndPoint).Port;
                //客户端网络结点号  
                string remoteEndPoint = connection.RemoteEndPoint.ToString();
                //显示与客户端连接情况
                Global.logServer.Add(new LogInfo("Info", "Socket:成功与" + remoteEndPoint + "客户端建立连接", (int)EnumLogLevel.RUN));
                if (Global.bShowLog)
                {
                    Global.ShowLogQueue.Add(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + "--->Socket: 成功与" + remoteEndPoint + "客户端建立连接");
                }
                //添加客户端信息  
                clientConnectionItems.Add(remoteEndPoint, connection);
                // IPEndPoint netpoint = connection.RemoteEndPoint as IPEndPoint;
                //创建一个通信线程      
                ParameterizedThreadStart pts = new ParameterizedThreadStart(ReceiveMasssage);
                Thread thread = new Thread(pts);
                //设置为后台线程，随着主线程退出而退出 
                thread.IsBackground = true;
                //启动线程     
                thread.Start(connection);
            }
        }
        
        private void ReceiveMasssage(object clientSocket)
        {
            Socket socketClient = clientSocket as Socket;
            while (true)
            {
                 try
                 {
                    byte[] buff = new byte[512];
                    int count = socketClient.Receive(buff);
                    if (count > 20 && buff[0] == 0xff && buff[1] == 0xff)
                    {
                        string info = Encoding.UTF8.GetString(buff, 3, count-3);
                        Global.logServer.Add(new LogInfo("Info", "Socket:获取站点信息" + info, (int)EnumLogLevel.RUN));
                        if (Global.bShowLog)
                        {
                            Global.ShowLogQueue.Add(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + "--->Socket:获取站点信息" + info);
                        }
                        StationInfo stationInfo = JsonHelper.DeserializeJsonToObject<StationInfo>(info);
                        if (stationInfo.StationCode != null && stationInfo.IP != null)
                        {
                            stationInfo.UpdateTime = DateTime.Now;
                            Global.StationQueue.Add(stationInfo);
                        }
                        
                        break;
                    }
                }
                catch (System.Exception ex)
                {
                    break;

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
        private int _port = 6789;

       

    }
}
