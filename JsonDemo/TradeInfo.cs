using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace JsonDemo
{
    public class TradeInfo
    {
        public string GasStation_NO { set; get; }
        public string REQ_Time { set; get; }
        public string MSG_ID { set; get; }
        public string OilGun_NO { set; get; }
        public string OIL_TYPE { set; get; }
        public double OIL_Q { set; get; }
        public double OIL_AMT { set; get; }
        public double OIL_PRC { set; get; }
        public string START_TIME { set; get; }
        public string END_TIME { set; get; }
        public double START_READ { set; get; }
        public double END_READ { set; get; }
        public string VehicleNo { set; get; }
        public string VehicleBrand { set; get; }
        public string SubBrand { set; get; }
        public string VehicleModel { set; get; }
        public string VehicleColor { set; get; }
        public string BodyColor { set; get; }

    }
     public class PayInfo
    {
        public string GasStation_NO { set; get; }
        public string REQ_Time { set; get; }
        public string MSG_ID { set; get; }
        public string TRANS_TYPE { set; get; }
        public string TRANS_CODE { set; get; }
        public string BAR_CODE { set; get; }
        public double TRANS_Q { set; get; }
        public double TRANS_AMT { set; get; }
        public double TRANS_PRC { set; get; }
        public string FINISH_TIME { set; get; }
        public string SETTLE_DAY { set; get; }
        public string OilGun_NO { set; get; }
        public double START_READ { set; get; }
        public double END_READ { set; get; }
        public string BILL_NUM { set; get; }
        public string BILL_ITEM_ID { set; get; }
        public string POS_NO { set; get; }
        public string StatusType { set; get; }
        public string Pumpsrv_ref { set; get; }
        public string PAY_MODE { set; get; }
        public double PAY_AMT { set; get; }
        public double Discount_AMT { set; get; }
        public string PAY_CARD { set; get; }

        public int TRADE_ID { set; get; }

    }
    public class UpLoadTradeInfo
    {
        public int id { set; get; }
        public string stationCode { set; get; }
        public string stationName { set; get; }
        public string meterialCode { set; get; }
        public int nozzleNo { set; get; }
        public double volume { set; get; }
        public double realAmount { set; get; }
        public double price { set; get; }
        public DateTime startTime { set; get; }
        public DateTime endTime { set; get; }
        public double startRead { set; get; }
        public double endRead { set; get; }
        public string carNumber { set; get; }
        public int carBrand { set; get; }
        public int subBrand { set; get; }
        public int carType { set; get; }
        public int carColor { set; get; }
        public int carNumColor { set; get; }
        public string realCarBrand { set; get; }
        public string realSubBrand { set; get; }
        public string oilName { set; get; }
        public string oilCode { set; get; }
        public string oilClass { set; get; }

    }
}
