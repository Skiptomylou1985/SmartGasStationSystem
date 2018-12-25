using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace JsonDemo
{
    public partial class FormTrade : Form
    {
        SocketTool socketServer;
        public FormTrade()
        {
            InitializeComponent();
        }

        private void btn_open_Click(object sender, EventArgs e)
        {
            if (btn_open.Text == "开启服务")
            {
                socketServer = new SocketTool("0.0.0.0", int.Parse(txtServerPort.Text.Trim()));
                socketServer.Run();
                btn_open.Text = "关闭服务";
                timerTrade.Enabled = true;
            }
            else
            {
                socketServer.Close();
                btn_open.Text = "开启服务";
                timerTrade.Enabled = false;
            }
        }

        private void timerTrade_Tick(object sender, EventArgs e)
        {
            if (Global.tradeList.Count > 0)
            {
                TradeInfo info = Global.tradeList[0];
                richTextBox1.Clear();
                richTextBox1.AppendText( Global.showStr);

                Global.tradeList.RemoveAt(0);
            }else if (Global.payList.Count > 0)
            {
                PayInfo pay = Global.payList[0];
                richTextBox1.Clear();
                richTextBox1.AppendText(Global.showStr);
                Global.payList.RemoveAt(0);
            }

        }

        private void btnTest_Click(object sender, EventArgs e)
        {
            
        }
    }
}
