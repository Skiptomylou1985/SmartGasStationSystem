using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.Windows.Forms;

namespace SPManager
{
    class SocketTool
    {
        private Socket ssocket = null;
        private Socket csocket = null;
        private bool isRun = false;
       
        public SocketTool(string serverIP,int serverPort)
        {
            ip = serverIP;
            port = serverPort;
        }
        public bool Run()
        {
            try
            {
                IPAddress serverIP = IPAddress.Parse(ip);
                ssocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                ssocket.Bind(new IPEndPoint(serverIP, port));  //绑定IP地址：端口  
                ssocket.Listen(10);    //设定最多10个排队连接请求  
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
        private void ListenClientConnect()
        {
            while(isRun)
            {
                Socket client = ssocket.Accept();
                Thread receiveThd = new Thread(ReceiveMasssage);
                receiveThd.Start(client);
            }
        }
        private void ReceiveMasssage(object clientSocket)
        {
            Socket myClientSocket = (Socket)clientSocket;
            byte[] buff = new byte[1024];
            while (isRun)
            {
                int count = myClientSocket.Receive(buff);
                if (count > 0)
                {
                    MessageBox.Show(System.Text.Encoding.Default.GetString(buff));
                }
            }
        }
        public string ip
        {
            get { return _ip; }
            set { _ip = value; }
        }
        private string _ip = "";

        public int port
        {
            get { return _port; }
            set { _port = value; }
        }
        private int _port = 8870;
    }
}
