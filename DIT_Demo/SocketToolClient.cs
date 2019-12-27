using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace DIT_Demo
{
    public class SocketToolClient
    {
        private Socket cSocket = null;
        private bool isRun = false;

        public SocketToolClient(string serverIP, int serverPort)
        {
            ip = serverIP;
            port = serverPort;

        }
        public SocketToolClient()
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

                cSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                cSocket.Connect(ip, port);

                isRun = true;
                Thread myThread = new Thread(new ThreadStart(ReceiveMasssage));
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
            Console.WriteLine("1111");
            if (isRun && cSocket != null)
            {
                try
                {
                    cSocket.Send(buff);
                    Console.WriteLine("Success");
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
                try
                {
                    this.cSocket.Shutdown(SocketShutdown.Both);
                    this.cSocket.Close();
                    this.cSocket = null;
                }
                catch
                {
                }
            }

        }

        private void ReceiveMasssage()
        {
            while (isRun)
            {
                try
                {
                    byte[] buff = new byte[1024];
                    int count = cSocket.Receive(buff);
                    if (count > 0)
                    {
                        Console.WriteLine("ReceiveMasssage");
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
