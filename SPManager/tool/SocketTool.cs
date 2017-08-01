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

namespace SPManager
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
           // TcpClient tcpClient = new TcpClient();
           // tcpClient.Connect(ip, port);

            //NetworkStream ns = tcpClient.GetStream();
            //if (ns.CanWrite)
            //{
            //    Byte[] sendBytes = Encoding.ASCII.GetBytes("Exit");
            //    ns.Write(sendBytes, 0, sendBytes.Length);
            //}
            //else
            //{
            //    return;
            //}
            //ns.Close();
            //tcpClient.Close();
            if (null != sSocket)
            {
                try
                {
                    this.sSocket.Shutdown(SocketShutdown.Both);
                    this.sSocket.Dispose();
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
                    this.cSocket.Dispose();
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
                    //sSocket.BeginAccept(AcceptCallBack, sSocket);
                   // client = listener.AcceptTcpClient();
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
                    byte[] buff = new byte[1024];
                    
                    int count = cSocket.Receive(buff);
                    if (count > 0)
                    {
                        if (buff[2] == 0x03 && buff[3] == 2)
                        {
                            SystemUnit.PostMessage(SystemUnit.HWND_BROADCAST, (int)Global.WM_CARSNAP, buff[4], buff[5]);
                        }
                        else if (buff[2] == 0x02 && buff[3] == 58 && count >= 62)
                        {
                            struLoginInfo info = new struLoginInfo();
                            byte[] reivBuf = new byte[58];
                            Buffer.BlockCopy(buff, 4, reivBuf, 0, 58);
                            info = (struLoginInfo)SystemUnit.BytesToStruts(reivBuf, typeof(struLoginInfo));
                            string ip = System.Text.Encoding.Default.GetString(info.byIP);
                            int port  = info.wPort;
                            string loginName = System.Text.Encoding.Default.GetString(info.byLoginName);
                            string password = System.Text.Encoding.Default.GetString(info.byPassword);
                            byte[] sendbuf = new byte[9];
                            sendbuf[0] = 0xFF;
                            sendbuf[1] = 0xFF;
                            sendbuf[2] = 0x02;
                            sendbuf[3] = 1;
                            if (ip == Global.clsNvrInfo.ip && port == Global.clsNvrInfo.port &&
                               loginName == Global.clsNvrInfo.loginName && password == Global.clsNvrInfo.password)
                                sendbuf[4] = 1;//1 成功 
                            else
                                sendbuf[4] = 0;//0 失败 
                            ushort crc = SystemUnit.getCRC(sendbuf, 0, 5);
                            sendbuf[5] = (byte)(crc / 256); 
                            sendbuf[6] = (byte)(crc % 256); 
                            sendbuf[7] = 0xEE;
                            sendbuf[8] = 0xEE;
                            Send(sendbuf);
                        }
                    }
                    Thread.Sleep(30);
                }
                catch (System.Exception ex)
                {

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
