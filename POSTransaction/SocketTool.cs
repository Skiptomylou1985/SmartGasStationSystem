/*
 *
 * 该类用于管理tcp连接通讯
 * 
 */

using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.Text;

namespace POSTransaction
{
    /// <summary>
    /// 服务端
    /// </summary>
    public class MyTcpServer
    {
        public static List<string> xmlList= new List<string>();
        private Socket ServerSocket = null;//服务端  
        public Dictionary<string, MySession> dic_ClientSocket = new Dictionary<string, MySession>();//tcp客户端字典
        private Dictionary<string, Thread> dic_ClientThread = new Dictionary<string, Thread>();//线程字典,每新增一个连接就添加一条线程
        private bool Flag_Listen = true;//监听客户端连接的标志
        private int maxClientNum = 10;
        private int port = 8880;

        public MyTcpServer()
        {

        }
        public MyTcpServer(int port)
        {
            this.port = port;
        }
        public MyTcpServer(int port,int maxClient)
        {
            this.port = port;
            this.maxClientNum = maxClient;
        }

        /// <summary>
        /// 启动服务
        /// </summary>
        /// <param name="port">端口号</param>
        public bool Run()
        {
            try
            {
                Flag_Listen = true;
                // 创建负责监听的套接字，注意其中的参数；
                ServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                // 创建包含ip和端口号的网络节点对象；
                IPEndPoint endPoint = new IPEndPoint(IPAddress.Any, this.port);
                try
                {
                    // 将负责监听的套接字绑定到唯一的ip和端口上；
                    ServerSocket.Bind(endPoint);
                }
                catch
                {
                    return false;
                }
                // 设置监听队列的长度；
                ServerSocket.Listen(maxClientNum);
                // 创建负责监听的线程；
                Thread Thread_ServerListen = new Thread(ListenConnecting);
                Thread_ServerListen.IsBackground = true;
                Thread_ServerListen.Start();

                Thread Thread_Monitoring = new Thread(Monitoring);
                Thread_Monitoring.IsBackground = true;
                Thread_Monitoring.Start();
                


                return true;
            }
            catch
            {
                return false;
            }
        }
        /// <summary>
        /// 关闭服务
        /// </summary>
        public void Close()
        {
            lock (dic_ClientSocket)
            {
                foreach (var item in dic_ClientSocket)
                {
                    item.Value.Close();//关闭每一个连接
                }
                dic_ClientSocket.Clear();//清除字典
            }
            lock (dic_ClientThread)
            {
                foreach (var item in dic_ClientThread)
                {
                    item.Value.Abort();//停止线程
                }
                dic_ClientThread.Clear();
            }
            Flag_Listen = false;
            //ServerSocket.Shutdown(SocketShutdown.Both);//服务端不能主动关闭连接,需要把监听到的连接逐个关闭
            if (ServerSocket != null)
                ServerSocket.Close();

        }
        /// <summary>
        /// 监听客户端请求的方法；
        /// </summary>
        private void ListenConnecting()
        {
            while (Flag_Listen)  // 持续不断的监听客户端的连接请求；
            {
                try
                {
                    Socket sokConnection = ServerSocket.Accept(); // 一旦监听到一个客户端的请求，就返回一个与该客户端通信的 套接字；
                    // 将与客户端连接的 套接字 对象添加到集合中；
                    string str_EndPoint = sokConnection.RemoteEndPoint.ToString();
                    MySession myTcpClient = new MySession() { TcpSocket = sokConnection };
                    //创建线程接收数据
                    Thread th_ReceiveData = new Thread(ReceiveData);
                    th_ReceiveData.IsBackground = true;
                    th_ReceiveData.Start(myTcpClient);
                    //把线程及客户连接加入字典
                    dic_ClientThread.Add(str_EndPoint, th_ReceiveData);
                    dic_ClientSocket.Add(str_EndPoint, myTcpClient);
                }
                catch
                {

                }
                Thread.Sleep(200);
            }
        }
        /// <summary>
        /// 监控链接状态
        /// </summary>
        private void Monitoring()
        {
            while(Flag_Listen)
            {
                if (dic_ClientSocket.Count > 0)
                {
                    try
                    {
                        foreach (var item in dic_ClientSocket)
                        {
                            //SelectMode.SelectRead表示，如果已调用 并且有挂起的连接，true。
                            // -或 - 如果有数据可供读取，则为 true。-或 - 如果连接已关闭、重置或终止，则返回 true（此种情况就表示若客户端断开连接了，则此方法就返回true）； 否则，返回 false。
                            if (item.Value.TcpSocket.Poll(1000, SelectMode.SelectRead))
                            {
                                lock (dic_ClientThread)
                                {
                                    Thread th = null;
                                    dic_ClientThread.TryGetValue(item.Key, out th);
                                    if (th != null)
                                    {
                                        th.Abort();
                                        dic_ClientThread.Remove(item.Key);
                                    }
                                }

                                lock (dic_ClientSocket)
                                {
                                    item.Value.Close();
                                    dic_ClientSocket.Remove(item.Key);
                                }


                            }
                        }
                    }
                    catch (System.Exception ex)
                    {
                    	
                    }
                   
                }
                Thread.Sleep(1000);
            }
            
        }

        /// <summary>
        /// 接收数据
        /// </summary>
        /// <param name="sokConnectionparn"></param>
        private void ReceiveData(object sokConnectionparn)
        {
            MySession tcpClient = sokConnectionparn as MySession;
            Socket socketClient = tcpClient.TcpSocket;
            bool Flag_Receive = true;
            int count = 0;
            int dataLenth = 0;
            StringBuilder sb = new StringBuilder();
            List<byte> buffer = new List<byte>();
            while (Flag_Receive)
            {
                try
                {
                    // 定义一个2M的缓存区；
                    byte[] arrMsgRec = new byte[1024  * 10];
                    // 将接受到的数据存入到输入  arrMsgRec中；
                    int length = -1;
                    try
                    {
                        length = socketClient.Receive(arrMsgRec); // 接收数据，并返回数据的长度；
                    }
                    catch
                    {
                        Flag_Receive = false;
                        // 从通信线程集合中删除被中断连接的通信线程对象；
                        string keystr = socketClient.RemoteEndPoint.ToString();
                        dic_ClientSocket.Remove(keystr);//删除客户端字典中该socket
                        dic_ClientThread[keystr].Abort();//关闭线程
                        dic_ClientThread.Remove(keystr);//删除字典中该线程

                        tcpClient = null;
                        socketClient = null;
                        break;
                    }
                    byte[] buf = new byte[length];
                    Array.Copy(arrMsgRec, buf, length);
                    Log.WriteLog("CommPort", "INFO", "【comm_DataReceived】 接收数据:" + ToHexString(buf));
                    buffer.AddRange(buf);
                    
                    count += length;
                    if (arrMsgRec[0] == 0x00 && arrMsgRec[1] == 0x00 && count == length)
                    {
                        dataLenth = arrMsgRec[2] * 256 + arrMsgRec[3] + 4;
                       // string xml = System.Text.Encoding.UTF8.GetString(arrMsgRec,4,length-4);
                       // xmlList.Add(xml);
                    }
                    if (count >= dataLenth)
                    {
                        byte[] data = buffer.ToArray();
                        Log.WriteLog("CommPort", "INFO", "完成数据拼接:" + ToHexString(data));
                        string xml = System.Text.Encoding.UTF8.GetString(data, 4, dataLenth - 4);
                        xmlList.Add(xml);
                        Log.WriteLog("CommPort", "INFO", xml);
                        count = 0;
                        dataLenth = 0;
                        buffer.Clear();
                    }
                    
                }
                catch(Exception ex)
                {

                }
                Thread.Sleep(100);
            }
        }
        public string ToHexString(byte[] bytes)

        {
            string hexString = string.Empty;

            if (bytes != null)

            {

                StringBuilder strB = new StringBuilder();

                for (int i = 0; i < bytes.Length; i++)

                {

                    strB.Append(bytes[i].ToString("X2") + " ");

                }

                hexString = strB.ToString();

            }
            return hexString;

        }

        /// <summary>
        /// 发送数据给指定的客户端
        /// </summary>
        /// <param name="_endPoint">客户端套接字</param>
        /// <param name="_buf">发送的数组</param>
        /// <returns></returns>
        public bool SendData(string _endPoint, byte[] _buf)
        {
            MySession myT = new MySession();
            if (dic_ClientSocket.TryGetValue(_endPoint, out myT))
            {
                myT.Send(_buf);
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    /// <summary>
    /// 会话端
    /// </summary>
    public class MySession
    {
        public Socket TcpSocket;//socket对象
        public List<byte> m_Buffer = new List<byte>();//数据缓存区

        public MySession()
        {

        }

        /// <summary>
        /// 发送数据
        /// </summary>
        /// <param name="buf"></param>
        public void Send(byte[] buf)
        {
            if (buf != null)
            {
                TcpSocket.Send(buf);
            }
        }
        /// <summary>
        /// 获取连接的ip
        /// </summary>
        /// <returns></returns>
        public string GetIp()
        {
            IPEndPoint clientipe = (IPEndPoint)TcpSocket.RemoteEndPoint;
            string _ip = clientipe.Address.ToString();
            return _ip;
        }
        /// <summary>
        /// 关闭连接
        /// </summary>
        public void Close()
        {
            TcpSocket.Shutdown(SocketShutdown.Both);
        }
        /// <summary>
        /// 提取正确数据包
        /// </summary>
        public byte[] GetBuffer(int startIndex, int size)
        {
            byte[] buf = new byte[size];
            m_Buffer.CopyTo(startIndex, buf, 0, size);
            m_Buffer.RemoveRange(0, startIndex + size);
            return buf;
        }

        /// <summary>
        /// 添加队列数据
        /// </summary>
        /// <param name="buffer"></param>
        public void AddQueue(byte[] buffer)
        {
            m_Buffer.AddRange(buffer);
        }
        /// <summary>
        /// 清除缓存
        /// </summary>
        public void ClearQueue()
        {
            m_Buffer.Clear();
        }
        
    }
}