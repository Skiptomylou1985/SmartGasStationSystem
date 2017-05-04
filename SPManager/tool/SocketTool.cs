using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Net.Sockets;
using System.Threading;

namespace SPManager
{
    class SocketTool
    {
        private Socket ssocket = null;
        private Socket csocket = null;
        public SocketTool(string serverIP,int serverPort)
        {
            ip = serverIP;
            port = serverPort;
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
