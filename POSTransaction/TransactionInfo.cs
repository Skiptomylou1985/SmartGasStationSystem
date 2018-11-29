using System;
using System.Collections.Generic;
using System.Text;

namespace POSTransaction
{
    public class TransactionInfo
    {
        public string RequestType { set; get; }
        public string ApplicationSender { set; get; }
        public string WorkStationID { set; get; }
        public string RequestID { set; get; }
        public string TerminalID { set; get; }
        public string PosTimeStamp { set; get; }
        public string OutDoorPosition { set; get; }
        public string QRCode { set; get; }
        public int ItemCount { set; get; }
        public SaleItem[] SaleItems;
    }
    public class SaleItem
    {
        public string TransactionNumber { set; get; }
        public string ItemID { set; get; }
        public string ProductCode { set; get; }
        public string GradeName {set; get; }
        public double Amount {set; get; }
        public string UnitMessage { set; get; }
        public double UnitPrice { set; get; }
        public double Quantity { set; get; }
        public string AdditonalProductCode { set; get; }
        public double TotalAmount { set; get; }
    }
}
