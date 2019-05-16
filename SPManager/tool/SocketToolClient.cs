using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace SPManager.tool
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
                        // 解析返回值
                        Array.Copy(buff, 0, _tcpRecvBuffer, _tcpRecvBufValidLength, buff.Length);
                        _tcpRecvBufValidLength += buff.Length;
                        DealPackage(ref _tcpRecvBuffer, ref _tcpRecvBufValidLength);
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

        public bool SendTcpData(byte packType, byte[] data)
        {
            try
            {
                byte[] packData = null;
                MakePackage(packType, data, out packData);
                Send(packData);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
            return true;
        }

        public byte[] MakePackage(byte packType, byte[] data, out byte[] packData)
        {
            byte[] tempData = null;
            byte[] encryptedData = data;
            if (data != null
                    && data.Length > 0)
            {
                tempData = new byte[1 + 2 + 1 + encryptedData.Length + 1];
                //拷贝命令数据
                Array.Copy(encryptedData, 0, tempData, 4, encryptedData.Length);
            }
            else
            {
                tempData = new byte[1 + 2 + 1 + 1];
            }
            tempData[0] = 0xAA;//包头
            tempData[1] = 0xFF;//设备地址低字节
            tempData[2] = 0xFF;//设备地址高字节
            tempData[3] = packType;//指令码
            tempData[tempData.Length - 1] = 0xCC;//包尾

            //转义处理
            int beginIndex = 1;
            int validLength = tempData.Length - 1 - 1;
            tempData = EscapeData(tempData, beginIndex, validLength);

            //校验
            UInt16 crcResult = CaculateCRC(tempData, tempData.Length);
            byte[] crcArray = GetArrayByValue(crcResult, 2);

            //校验和包合并
            packData = new byte[tempData.Length + crcArray.Length];
            Array.Copy(tempData, 0, packData, 0, tempData.Length);
            Array.Copy(crcArray, 0, packData, tempData.Length, crcArray.Length);
            return packData;
        }

        /// <summary>
        /// 解析数据帧
        /// </summary>
        public bool ParsePackage(byte[] packData, out byte packType, out byte[] data)
        {
            packType = 0;
            data = null;

            //解析校验
            int nBeginIndex = 0;
            int validLength = packData.Length - 2;
            UInt16 packageCrc = CaculateCRC(packData, validLength);
            if (!CheckCrc(packData, packageCrc))
            {
                return false;
            }
            //对转义的字节进行处理
            nBeginIndex = 1;
            validLength = packData.Length - 1 - 1 - 2;
            packData = UnescapeData(packData, nBeginIndex, validLength);
            //解析包功能类型
            nBeginIndex += 2;
            packType = packData[nBeginIndex];

            //解析数据
            nBeginIndex += 1;
            //包头（1） + 包类型（1）+ 设备地址（2）+ 校验（2）+ 包尾（1）
            validLength = packData.Length - 1 - 1 - 2 - 2 - 1;
            if (validLength > 0)
            {
                data = new byte[validLength];
                Array.Copy(packData, nBeginIndex, data, 0, validLength);
            }
            return true;
        }

        /// <summary>
        /// 将整型数据转换正字节数据
        /// </summary>
        private byte[] GetArrayByValue(int value, int arrayLength)
        {
            byte[] data = new byte[arrayLength];
            for (int i = 0; i < arrayLength; i++)
            {
                data[i] = (byte)(value >> (8 * i));
            }
            return data;
        }

        /// <summary>
        /// 对数据进行转义处理
        /// </summary>
        private byte[] EscapeData(byte[] tdata, int beginIndex, int validLength)
        {
            //0xAA 转换为 0xEE, 0x0A
            byte[] b0xAA = new byte[2];
            b0xAA[0] = 0xEE;
            b0xAA[1] = 0x0A;

            //0xCC 转换为 0xEE, 0x0C
            byte[] b0xCC = new byte[2];
            b0xCC[0] = 0xEE;
            b0xCC[1] = 0x0C;

            //0xEE 转换为 0xEE, 0x0E
            byte[] b0xEE = new byte[2];
            b0xEE[0] = 0xEE;
            b0xEE[1] = 0x0E;

            byte[] bVal = null;
            byte[] bTemp = new byte[1];
            System.IO.MemoryStream stream = new System.IO.MemoryStream();
            try
            {
                byte temp = 0;
                for (int i = 0; i < tdata.Length; i++)
                {
                    temp = tdata[i];
                    if (i >= beginIndex
                        && i < beginIndex + validLength)
                    {
                        switch (temp)
                        {
                            case 0xAA:
                                stream.Write(b0xAA, 0, b0xAA.Length);
                                break;
                            case 0xCC:
                                stream.Write(b0xCC, 0, b0xCC.Length);
                                break;
                            case 0xEE:
                                stream.Write(b0xEE, 0, b0xEE.Length);
                                break;
                            default:
                                bTemp[0] = temp;
                                stream.Write(bTemp, 0, bTemp.Length);
                                break;
                        }
                    }
                    else
                    {
                        bTemp[0] = temp;
                        stream.Write(bTemp, 0, bTemp.Length);
                    }
                }
                bVal = stream.ToArray();
            }
            catch (Exception ee)
            {
                throw ee;
            }
            finally
            {
                stream.Close();
            }
            return bVal;
        }

        /// <summary>
        /// 计算CRC校验值
        /// </summary>
        private UInt16 CaculateCRC(byte[] data, int len)
        {
            UInt16 fcs = 0xffff;
            for (int i = 0; i < len; i++)
            {
                fcs = (UInt16)((fcs >> 8) ^ s_CRCValue[(fcs ^ data[i]) & 0xff]);
            }
            return fcs;
        }

        /// <summary>
        /// 判断数据的CRC值是否正确
        /// </summary>
        private bool CheckCrc(byte[] data, UInt16 caculateCrc)
        {
            try
            {
                if (data == null)
                {
                    return false;
                }
                int crcBeginIndex = data.Length - 2;
                int tempCrc = (((int)data[crcBeginIndex + 1]) << 8) + data[crcBeginIndex];
                if (tempCrc != caculateCrc)
                {
                    return false;
                }
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        /// <summary>
        ///  对数据进行反转义处理
        /// </summary>
        private byte[] UnescapeData(byte[] tdata, int beginIndex, int validLength)
        {
            byte[] bVal = null;
            byte[] bTemp = new byte[1];
            System.IO.MemoryStream stream = new System.IO.MemoryStream();
            try
            {
                byte temp = 0;
                for (int i = 0; i < tdata.Length; i++)
                {
                    temp = tdata[i];
                    if (i >= beginIndex
                        && i < validLength + beginIndex)
                    {
                        switch (temp)
                        {
                            case 0xEE:
                                byte temp1 = tdata[i + 1];
                                switch (temp1)
                                {
                                    case 0x0A:
                                        i++;
                                        bTemp[0] = 0xAA;
                                        stream.Write(bTemp, 0, bTemp.Length);
                                        break;
                                    case 0x0C:
                                        i++;
                                        bTemp[0] = 0xCC;
                                        stream.Write(bTemp, 0, bTemp.Length);
                                        break;
                                    case 0x0E:
                                        i++;
                                        bTemp[0] = 0xEE;
                                        stream.Write(bTemp, 0, bTemp.Length);
                                        break;
                                    default:
                                        bTemp[0] = temp;
                                        stream.Write(bTemp, 0, bTemp.Length);
                                        break;

                                }
                                break;
                            default:
                                bTemp[0] = temp;
                                stream.Write(bTemp, 0, bTemp.Length);
                                break;

                        }
                    }
                    else
                    {
                        bTemp[0] = temp;
                        stream.Write(bTemp, 0, bTemp.Length);
                    }
                }
                bVal = stream.ToArray();
            }
            catch (Exception ee)
            {
                throw ee;
            }
            finally
            {
                stream.Close();
            }
            return bVal;
        }
        private ushort[] s_CRCValue = new ushort[]
                    {
                             0x0000,0x1189,0x2312,0x329b,0x4624,0x57ad,0x6536,0x74bf,0x8c48,0x9dc1,
                             0xaf5a,0xbed3,0xca6c,0xdbe5,0xe97e,0xf8f7,0x1081,0x0108,0x3393,0x221a,
                             0x56a5,0x472c,0x75b7,0x643e,0x9cc9,0x8d40,0xbfdb,0xae52,0xdaed,0xcb64,
                             0xf9ff,0xe876,0x2102,0x308b,0x0210,0x1399,0x6726,0x76af,0x4434,0x55bd,
                             0xad4a,0xbcc3,0x8e58,0x9fd1,0xeb6e,0xfae7,0xc87c,0xd9f5,0x3183,0x200a,
                             0x1291,0x0318,0x77a7,0x662e,0x54b5,0x453c,0xbdcb,0xac42,0x9ed9,0x8f50,
                             0xfbef,0xea66,0xd8fd,0xc974,0x4204,0x538d,0x6116,0x709f,0x0420,0x15a9,
                             0x2732,0x36bb,0xce4c,0xdfc5,0xed5e,0xfcd7,0x8868,0x99e1,0xab7a,0xbaf3,
                             0x5285,0x430c,0x7197,0x601e,0x14a1,0x0528,0x37b3,0x263a,0xdecd,0xcf44,
                             0xfddf,0xec56,0x98e9,0x8960,0xbbfb,0xaa72,0x6306,0x728f,0x4014,0x519d,
                             0x2522,0x34ab,0x0630,0x17b9,0xef4e,0xfec7,0xcc5c,0xddd5,0xa96a,0xb8e3,
                             0x8a78,0x9bf1,0x7387,0x620e,0x5095,0x411c,0x35a3,0x242a,0x16b1,0x0738,
                             0xffcf,0xee46,0xdcdd,0xcd54,0xb9eb,0xa862,0x9af9,0x8b70,0x8408,0x9581,
                             0xa71a,0xb693,0xc22c,0xd3a5,0xe13e,0xf0b7,0x0840,0x19c,0x2b52,0x3adb,
                             0x4e64,0x5fed,0x6d76,0x7cff,0x9489,0x8500,0xb79b,0xa612,0xd2ad,0xc324,
                             0xf1bf,0xe036,0x18c1,0x0948,0x3bd3,0x2a5a,0x5ee5,0x4f6c,0x7df7,0x6c7e,
                             0xa50a,0xb483,0x8618,0x9791,0xe32e,0xf2a7,0xc03c,0xd1b5,0x2942,0x38cb,
                             0x0a50,0x1bd9,0x6f66,0x7eef,0x4c74,0x5dfd,0xb58b,0xa402,0x9699,0x8710,
                             0xf3af,0xe226,0xd0bd,0xc134,0x39c3,0x284a,0x1ad1,0x0b58,0x7fe7,0x6e6e,
                             0x5cf5,0x4d7c,0xc60c,0xd785,0xe51e,0xf497,0x8028,0x91a1,0xa33a,0xb2b3,
                             0x4a44,0x5bcd,0x6956,0x78df,0x0c60,0x1de9,0x2f72,0x3efb,0xd68d,0xc704,
                             0xf59f,0xe416,0x90a9,0x8120,0xb3bb,0xa232,0x5ac5,0x4b4c,0x79d7,0x685e,
                             0x1ce1,0x0d68,0x3ff3,0x2e7a,0xe70e,0xf687,0xc41c,0xd595,0xa12a,0xb0a3,
                             0x8238,0x93b1,0x6b46,0x7acf,0x4854,0x59dd,0x2d62,0x3ceb,0x0e70,0x1ff9,
                             0xf78f,0xe606,0xd49d,0xc514,0xb1ab,0xa022,0x92b9,0x8330,0x7bc7,0x6a4e,
                             0x58d5,0x495c,0x3de3,0x2c6a,0x1ef1,0x0f78
                    };

        #region 对接收到的数据处理
        private byte[] _tcpRecvBuffer = new byte[10 * 10 * 1024];
        private int _tcpRecvBufValidLength = 0;

        private void DealPackage(ref byte[] bufferData, ref int validLengrh)
        {
            byte[] packageData = null;
            int nBeginIndex = 0;
            int packageOffset = 0;

            byte packType = 0;
            byte[] data = null;

            while (validLengrh > 0)
            {
                //查找起始帧位置
                if (!FindPackageHead(bufferData, 0, out nBeginIndex))
                {
                    Array.Clear(bufferData, 0, validLengrh);
                    validLengrh = 0;
                    return;
                }
                //获取完整包
                if (!GetPackageData(bufferData, nBeginIndex, out packageOffset, out packageData))
                {
                    return;
                }
                int nValidLength = packageData.Length;
                //删除前面没用的数据
                int nClearLength = packageOffset + nValidLength;
                Array.Clear(bufferData, 0, nClearLength);
                Array.Copy(bufferData, nClearLength, bufferData, 0, validLengrh - nClearLength);
                Array.Clear(bufferData, validLengrh - nClearLength, bufferData.Length - validLengrh + nClearLength);
                validLengrh -= nClearLength;
                //解析数据帧
                if (!ParsePackage(packageData, out packType, out data))
                {
                    continue;
                }
                byte[] decryptedData = data;

                switch (packType)
                {
                    case (byte)0x00:
                        #region 心跳
                        string heartInfo = Encoding.UTF8.GetString(decryptedData, 0, decryptedData.Length);
                        Global.LogServer.Add(new LogInfo("OLED", "Main->ReceiveMasssage: 大屏心跳检测 : " + heartInfo, (int)EnumLogLevel.DEBUG));
                        #endregion
                        break;
                    case (byte)0x1C:
                        #region 指定显示列表
                        if (null != decryptedData && decryptedData[0] == 1)
                        {
                        }
                        else
                        {
                        }
                        #endregion
                        break;
                    case (byte)0x89:
                        #region 局部实时更新
                        if (null != decryptedData && decryptedData[0] == 1)
                        {
                            Global.LogServer.Add(new LogInfo("OLED", "Main->ReceiveMasssage: 大屏局部实时更新 成功", (int)EnumLogLevel.DEBUG));
                        }
                        else
                        {
                            Global.LogServer.Add(new LogInfo("OLED", "Main->ReceiveMasssage: 大屏局部实时更新 失败", (int)EnumLogLevel.DEBUG));
                        }
                        #endregion
                        break;
                    case (byte)0x12:
                        #region 文件名发送
                        if (null != decryptedData && decryptedData[0] == 1)
                        {
                        }
                        else
                        {
                        }
                        #endregion
                        break;
                    case (byte)0x14:
                        #region 文件数据块发送

                        #endregion
                        break;
                    case (byte)0xF9:
                        #region 文件发送结果
                        if (null != decryptedData && decryptedData[0] == 1)
                        {
                        }
                        else
                        {
                        }
                        #endregion
                        break;
                    default:
                        if (null != decryptedData && decryptedData[0] == 1)
                        {
                        }
                        else
                        {
                        }
                        break;
                }
            }
        }
        /// <summary>
        /// 查找数据帧起始符位置
        /// </summary>
        private bool FindPackageHead(byte[] data, int beginIndex, out int offset)
        {
            offset = 0;
            if (data == null
                || data.Length < 1)
            {
                return false;
            }
            for (int i = beginIndex; i < data.Length; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    if (data[i + j] != 0xAA)
                    {
                        break;
                    }
                    offset = i;
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// 查找数据帧结束符位置
        /// </summary>
        public bool FindPackageEnd(byte[] data, int beginIndex, out int offset)
        {
            offset = 0;
            for (int i = beginIndex; i < data.Length; i++)
            {
                for (int j = 0; j < 1; j++)
                {
                    if (data[i + j] != 0xCC)
                    {
                        break;
                    }
                    offset = i;
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// 获取一个完整的数据帧
        /// </summary>
        public bool GetPackageData(byte[] data, int beginIndex, out int packageOffset, out byte[] packageData)
        {
            packageOffset = 0;
            packageData = null;
            if (data == null)
            {
                return false;
            }
            if (!FindPackageHead(data, beginIndex, out packageOffset))
            {
                return false;
            }
            int nEndOffset = 0;
            if (!FindPackageEnd(data, packageOffset, out nEndOffset))
            {
                return false;
            }
            int dataLength = nEndOffset + 1 + 2 - packageOffset;
            packageData = new byte[dataLength];
            Array.Copy(data, packageOffset, packageData, 0, dataLength);
            return true;
        }
        #endregion
    }
}
