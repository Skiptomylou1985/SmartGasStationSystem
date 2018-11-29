using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;

namespace POSTransaction
{
    public partial class FormMain : Form
    {
        private MyTcpServer server;
        public FormMain()
        {
            InitializeComponent();
        }

        private void tabPage1_Click(object sender, EventArgs e)
        {

        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            if (btnOpen.Text == "打开")
            {
                server = new MyTcpServer(int.Parse(textPort.Text.Trim()));
                if (server.Run())
                {
                    btnOpen.Text = "关闭";
                }
            }
            else
            {
                server.Close();
                btnOpen.Text = "打开";
            }

        }

        private void btnTest_Click(object sender, EventArgs e)
        {
            if (MyTcpServer.xmlList.Count > 0)
            {
                var doc = new XmlDocument();
                doc.LoadXml(MyTcpServer.xmlList[0]);
                var rowNoteList = doc.SelectNodes("/CardServiceRequest/Terminal/POSdata/POSTimeStamp/OutdoorPosition/QRCode/SaleItems/SaleItem");


                if (rowNoteList != null)
                {
                    TransactionInfo info = new TransactionInfo();
                    foreach (XmlNode rowNode in rowNoteList)
                    {
                        if (rowNode.Name == "CardServiceRequest")
                        {
                            info.RequestType = rowNode.Attributes["RequestType"].Value;
                            info.ApplicationSender = rowNode.Attributes["ApplicationSender"].Value;
                            info.WorkStationID = rowNode.Attributes["WorkstationID"].Value;
                            info.RequestID = rowNode.Attributes["RequestID"].Value;
                        }else if (rowNode.Name == "Terminal")
                        {
                            info.TerminalID = rowNode.Attributes["TerminalID"].Value;
                        }else if (rowNode.Name == "POSTimeStamp")
                        {
                            info.PosTimeStamp = rowNode.Value;
                        }
                        else if (rowNode.Name == "OutdoorPosition")
                        {
                            info.OutDoorPosition = rowNode.Value;
                        }
                        else if (rowNode.Name == "QRCode")
                        {
                            info.QRCode = rowNode.Value;
                        }
                        else if (rowNode.Name == "SaleItems")
                        {
                            info.ItemCount = int.Parse(rowNode.Attributes["ItemCount"].Value);
                            if (info.ItemCount > 0)
                            {
                                info.SaleItems = new SaleItem[info.ItemCount];
                            }
                        }
                        else if (rowNode.Name == "SaleItem")
                        {
                        }


                    }
                }

            }
        }
    }
}
