using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace SPManager
{
    public static class WinSock
    {
        public const Int64 FD_READ = 0x01;        // FD_READ
        public const Int64 FD_CLOSE = 0x20;       // FD_CLOSE
        public const Int16 AF_INET = 2;           // socket连接地址结构中的sin_family,2代表连接类型为tcp，1为udp
        public const int SOCK_STREAM = 1;         // TCP Type
        public const int SOCK_DGRAM = 2;          // UDP Type
        public const int SOCK_RAW = 3;            // RAW Type
        public const int SOCK_RDM = 4;            // RDM Type
        public const int SOCK_SEQPACKET = 5;      // SEQPACKET Type

        public const int SD_BOTH = 0x02;
        public const int SD_SEND = 0x01;
        public const int SD_RECEIVE = 0x00;
        public const int SOCKET_ERROR = -1;

        //声明winsock相关函数 
        [DllImport("ws2_32.dll")]
        public static extern int WSAStartup(UInt16 version, out WSAData lpWSAData);

        [DllImport("ws2_32.dll")]
        public static extern int WSACleanup();

        [DllImport("ws2_32.dll")]
        public static extern int WSAAsyncSelect(int socket, IntPtr hWnd, uint wMsg, long lEvent);

        [DllImport("ws2_32.dll")]
        public static extern int socket(
            int af,
            int type,
            int protocol
        );

        [DllImport("ws2_32.dll")]
        public static extern int connect(
            int socket,
            ref SockAddr_In name,
            int namelen
        );

        [DllImport("ws2_32.dll")]
        public static extern int bind(int s, ref SockAddr_In name, int namelen);

        [DllImport("ws2_32.dll")]
        public static extern int closesocket(
            int socket
        );

        [DllImport("ws2_32.dll")]
        public static extern int shutdown(int socket, int how);

        [DllImport("ws2_32.dll")]
        public static extern uint inet_addr(
            string cp
        );

        [DllImport("ws2_32.dll")]
        public static extern UInt16 htons(
            UInt16 hostshort
        );

        [DllImport("ws2_32.dll")]
        public static extern int send(
            int socket,
            byte[] buf,
            int len,
            int flags
        );

        [DllImport("ws2_32.dll")]
        public static extern int recv(
            int socket,
            byte[] buf,
            int len,
            int flags
        );

        [DllImport("ws2_32.dll")]
        public static extern int sendto(
          int s,
          byte[] buf, 
          int len,
          int flags,
          ref SockAddr_In to,
          int tolen
        );

        [DllImport("ws2_32.dll")]
        public static extern int recvfrom(
          int s,  
          byte[] buf,  
          int len,  
          int flags,
          ref SockAddr_In from,
          int fromlen);

        public struct SockAddr_In
        {
            public Int16 sin_family;      /* Address family */
            public UInt16 sin_port;       /* Port number */                //ushort
            public In_Addr sin_addr;      /* Internet address */
            public byte[] sin_zero;       /* Same size as struct sockaddr */   // char[]
        };

        public struct In_Addr
        {
            public uint s_addr;                    //unsigned long
        };

        public struct WSAData
        {
            public UInt16 wVersion;
            public UInt16 wHighVersion;
            public char Description;
            public char SystemStatus;
            public UInt16 iMaxSockets;
            public UInt16 iMaxUdpDg;
            public byte lpVendorInfo;       //对应c++中的char *
        } 
    }
}


