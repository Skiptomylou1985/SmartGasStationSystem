using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace DIT_Demo
{
    partial class FormDIT
    {
        SocketTool socketDit;
        SocketToolClient sockToolClient;

        private void InitSocket()
        {
            socketDit = new SocketTool("10.97.178.33", 8870);
            socketDit.Run();

            //sockToolClient = new SocketToolClient("10.97.178.33", 8870);
            //sockToolClient.Run();
        }

        private void SendToDIT()
        {
            PumpBackInfo backInfo = new PumpBackInfo();
            backInfo.VehicleNo = "";
            backInfo.VehicleBrand = "";
            backInfo.SubBrand = "";
            backInfo.VehicleModel = "0";
            backInfo.VehicleColor = "";
            backInfo.BodyColor = "";
            backInfo.MsgID = "";
            backInfo.PumpID = "";
            backInfo.Time = "";
            string infoJson = JsonHelper.SerializeObject(backInfo);
            socketDit.Send(Encoding.Default.GetBytes(infoJson));

            string nsgLog = "发送车辆数据：\n" + " CarNum: 京AP42D5";
            this.textBox_Msg.AppendText(nsgLog + " \r \n");
        }

        private void FormDIT_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (null != socketDit)
            {
                socketDit.Close();
            }
            if (null != sockToolClient)
            {
                sockToolClient.Close();
            }
        }
    }
}
