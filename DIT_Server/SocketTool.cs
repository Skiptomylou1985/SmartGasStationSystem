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

namespace DIT_Server
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
                    //int count = myClientSocket.Receive(buff);
                    int count = cSocket.Receive(buff);
                    if (count > 0)
                    {
                        if (buff[2] == 0x03 && buff[3] == 2)
                        {
                            SysUnit.byNozzle = buff[4];
                            SysUnit.byNozzleStatus = buff[5];
                            SysUnit.PostMessage(SysUnit.HWND_BROADCAST, (int)SysUnit.WM_CARSNAP, 0, 0);
                        }
                        else if(buff[2] == 0x01)
                        {
                            
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
