using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.IO;
using System.Threading;

namespace SPManager.tool
{
    public class Upload
    {
        private bool isRun = false;
        private string url;
        private string uploadType; //uploadType 上传类型，car,trade,order,pay
        public Upload(string url, string uploadType)
        {
            this.url = url+uploadType;
            this.uploadType = uploadType;

        }

        public bool Run()
        {
            try
            {
                isRun = true;
                Thread myThread = new Thread(upload);
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

        private void upload()
        {
            while(isRun)
            {

                doUpload();
                Thread.Sleep(500);
           
            }
        }

        private void doUpload()
        {
            switch (uploadType)
            {
                case "trade":
                   // Global.LogServer.Add(new LogInfo("Debug", "Upload-> doUpload：发送trade信息", (int)EnumLogLevel.DEBUG));
                    string sql = "select * from tradelog where upload = 0 order by id desc limit 1";
                    System.Data.DataTable dt = Global.mysqlHelper.GetDataTable(sql);
                    if (dt != null && dt.Rows.Count >0 )
                    {
                        UpLoadTradeInfo info = new UpLoadTradeInfo();
                        info.id = int.Parse(dt.Rows[0]["id"].ToString());
                        info.carBrand = int.Parse(dt.Rows[0]["carbrand"].ToString());
                        info.carColor = int.Parse(dt.Rows[0]["carcolor"].ToString());
                        info.carNumColor = int.Parse(dt.Rows[0]["carnumcolor"].ToString());
                        info.carType = int.Parse(dt.Rows[0]["cartype"].ToString());
                        info.carNumber = dt.Rows[0]["carnumber"].ToString();
                        info.carBrand = int.Parse(dt.Rows[0]["carbrand"].ToString());
                        info.stationName = Global.stationInfo.stationName;
                        info.stationCode = Global.stationInfo.stationCode;
                        info.nozzleNo = int.Parse(dt.Rows[0]["nozzleno"].ToString());
                        info.oilClass = dt.Rows[0]["oilclass"].ToString();
                        info.meterialCode = dt.Rows[0]["meterialcode"].ToString();
                        info.oilCode = dt.Rows[0]["oilcode"].ToString();
                        info.oilName = dt.Rows[0]["oilname"].ToString();
                        info.price = double.Parse(dt.Rows[0]["price"].ToString()); ;
                        info.realAmount = double.Parse(dt.Rows[0]["realamount"].ToString());
                        info.realCarBrand = dt.Rows[0]["realcarbrand"].ToString();
                        info.realSubBrand = dt.Rows[0]["realsubbrand"].ToString();
                        info.startRead = double.Parse(dt.Rows[0]["startread"].ToString());
                        info.endRead = double.Parse(dt.Rows[0]["endread"].ToString());
                        info.volume = double.Parse(dt.Rows[0]["volume"].ToString());
                        info.startTime = DateTime.Parse(dt.Rows[0]["starttime"].ToString()).ToString("yyyy-MM-dd HH:mm:ss");
                        info.endTime = DateTime.Parse(dt.Rows[0]["endtime"].ToString()).ToString("yyyy-MM-dd HH:mm:ss"); ;
                        Global.LogServer.Add(new LogInfo("Debug", "Upload-> doUpload：发送trade信息内容 " + JsonHelper.SerializeObject(info), (int)EnumLogLevel.DEBUG));
                        if (doUpload(info, url)) 
                        {
                            Global.LogServer.Add(new LogInfo("Debug", "Upload-> doUpload：发送trade信息成功", (int)EnumLogLevel.DEBUG));
                            Global.mysqlHelper.ExecuteSql("update tradelog set upload = 1 where id =  "+info.id);
                        }
                    }
                    break;
                case "orderlog":
                    string sqlOrder = "select * from orderlog where upload = 0 order by id desc limit 1";
                    System.Data.DataTable dtOrder = Global.mysqlHelper.GetDataTable(sqlOrder);
                    if (null != dtOrder && dtOrder.Rows.Count > 0)
                    {
                        UploadOrderInfo orderInfo = new UploadOrderInfo();
                        orderInfo.id = int.Parse(dtOrder.Rows[0]["id"].ToString());
                        orderInfo.transType = dtOrder.Rows[0]["transtype"].ToString();
                        orderInfo.transCode = dtOrder.Rows[0]["transcode"].ToString();
                        orderInfo.meterialCode = dtOrder.Rows[0]["meterialcode"].ToString();
                        orderInfo.volume = double.Parse(dtOrder.Rows[0]["volume"].ToString());
                        orderInfo.realAmount = double.Parse(dtOrder.Rows[0]["realamount"].ToString());
                        orderInfo.price = double.Parse(dtOrder.Rows[0]["price"].ToString());
                        orderInfo.payTime = dtOrder.Rows[0]["paytime"].ToString();
                        orderInfo.settleDate = dtOrder.Rows[0]["settledate"].ToString();
                        orderInfo.nozzleNo = int.Parse(dtOrder.Rows[0]["nozzleno"].ToString());
                        orderInfo.startRead = double.Parse(dtOrder.Rows[0]["startread"].ToString());
                        orderInfo.endRead = double.Parse(dtOrder.Rows[0]["endread"].ToString());
                        orderInfo.billNo = int.Parse(dtOrder.Rows[0]["billno"].ToString());
                        orderInfo.billItemId = int.Parse(dtOrder.Rows[0]["billitemid"].ToString());
                        orderInfo.posNo = dtOrder.Rows[0]["posno"].ToString();
                        orderInfo.statusType = dtOrder.Rows[0]["statustype"].ToString();
                        orderInfo.payCode = dtOrder.Rows[0]["paycode"].ToString();
                        orderInfo.tradeId = int.Parse(dtOrder.Rows[0]["tradeid"].ToString());
                        orderInfo.stationCode = Global.stationInfo.stationCode;
                        orderInfo.stationName = Global.stationInfo.stationName;

                        Global.LogServer.Add(new LogInfo("Debug", "Upload-> doUpload：发送order信息内容 " + JsonHelper.SerializeObject(orderInfo), (int)EnumLogLevel.DEBUG));
                        if (doUpload(orderInfo, url))
                        {
                            Global.LogServer.Add(new LogInfo("Debug", "Upload-> doUpload：发送order信息成功", (int)EnumLogLevel.DEBUG));
                            Global.mysqlHelper.ExecuteSql("update orderlog set upload = 1 where id =  " + orderInfo.id);
                        }
                    }
                    break;
                case "paylog":
                    string sqlPayment = "select * from paylog where upload = 0 order by id desc limit 1";
                    System.Data.DataTable dtPayment = Global.mysqlHelper.GetDataTable(sqlPayment);
                    if (null != dtPayment && dtPayment.Rows.Count > 0)
                    {
                        UploadPayInfo payInfo = new UploadPayInfo();

                        payInfo.id = int.Parse(dtPayment.Rows[0]["id"].ToString());
                        payInfo.billNo = int.Parse(dtPayment.Rows[0]["billno"].ToString());
                        payInfo.payMode = dtPayment.Rows[0]["paymode"].ToString();
                        payInfo.payAmount = double.Parse(dtPayment.Rows[0]["payamount"].ToString());
                        payInfo.discount = double.Parse(dtPayment.Rows[0]["discount"].ToString());
                        payInfo.payCard = dtPayment.Rows[0]["paycard"].ToString();
                        payInfo.tradeId = int.Parse(dtPayment.Rows[0]["tradeid"].ToString());
                        payInfo.stationCode = Global.stationInfo.stationCode;
                        payInfo.stationName = Global.stationInfo.stationName;
                        Global.LogServer.Add(new LogInfo("Debug", "Upload-> doUpload：发送payment信息内容 " + JsonHelper.SerializeObject(payInfo), (int)EnumLogLevel.DEBUG));
                        if (doUpload(payInfo, url))
                        {
                            Global.LogServer.Add(new LogInfo("Debug", "Upload-> doUpload：发送payment信息成功", (int)EnumLogLevel.DEBUG));
                            Global.mysqlHelper.ExecuteSql("update paylog set upload = 1 where id =  " + payInfo.id);
                        }
                    }
                    break;
                case "carlog":
                    //string sqlCar = "select * from carlog where upload = 0 order by id desc limit 1";
                    //System.Data.DataTable dtCar = Global.mysqlHelper.GetDataTable(sqlCar);
                    //if (null != dtCar && dtCar.Rows.Count > 0)
                    //{
                    //    UploadCarInfo carInfo = new UploadCarInfo();
                    //    carInfo.id = int.Parse(dtCar.Rows[0]["id"].ToString());
                    //    carInfo.carNumber = dtCar.Rows[0]["carnumber"].ToString();
                    //    carInfo.carNumColor = int.Parse(dtCar.Rows[0]["carnumcolor"].ToString());
                    //    carInfo.carType = int.Parse(dtCar.Rows[0]["cartype"].ToString());
                    //    carInfo.carLogo = int.Parse(dtCar.Rows[0]["carlogo"].ToString());
                    //    carInfo.subCarLogo = int.Parse(dtCar.Rows[0]["subcarlogo"].ToString());
                    //    carInfo.carColor = int.Parse(dtCar.Rows[0]["carcolor"].ToString());
                    //    carInfo.arriveTime = dtCar.Rows[0]["arrivetime"].ToString();
                    //    carInfo.leaveTime = dtCar.Rows[0]["leavetime"].ToString();
                    //    carInfo.nozzleNo = int.Parse(dtCar.Rows[0]["nozzleno"].ToString());
                    //    carInfo.picPath = dtCar.Rows[0]["picpath"].ToString();
                    //    carInfo.beginTime = dtCar.Rows[0]["begintime"].ToString();
                    //    carInfo.endTime = dtCar.Rows[0]["endtime"].ToString();
                    //    carInfo.oilType = int.Parse(dtCar.Rows[0]["oiltype"].ToString());
                    //    carInfo.volume = double.Parse(dtCar.Rows[0]["volume"].ToString());
                    //    carInfo.realAmount = double.Parse(dtCar.Rows[0]["realamount"].ToString());
                    //    carInfo.tradeSn = dtCar.Rows[0]["tradesn"].ToString();
                    //    carInfo.startRead = double.Parse(dtCar.Rows[0]["startread"].ToString());
                    //    carInfo.endRead = double.Parse(dtCar.Rows[0]["endread"].ToString());
                    //    carInfo.meterialCode = dtCar.Rows[0]["meterialcode"].ToString();
                    //    carInfo.oilPrice = double.Parse(dtCar.Rows[0]["oilprice"].ToString());
                    //    carInfo.stationCode = Global.stationInfo.stationCode;
                    //    carInfo.stationName = Global.stationInfo.stationName;
                    //    Global.LogServer.Add(new LogInfo("Debug", "Upload-> doUpload：发送car信息内容 " + JsonHelper.SerializeObject(carInfo), (int)EnumLogLevel.DEBUG));
                    //    if (doUpload(carInfo, url))
                    //    {
                    //        Global.LogServer.Add(new LogInfo("Debug", "Upload-> doUpload：发送car信息成功", (int)EnumLogLevel.DEBUG));
                    //        Global.mysqlHelper.ExecuteSql("update carlog set upload = 1 where id =  " + carInfo.id);
                    //    }
                    //}
                    break;
            }

        }


//         private UpLoadTradeInfo getTrade()
//         {
//             UpLoadTradeInfo info = new UpLoadTradeInfo();
// 
//         }

        public bool doUpload(object obj,string url)
        {
            string jsonParam = "";
            try
            {
                //序列化参数
                jsonParam = JsonHelper.SerializeObject(obj);
                //发送请求
                HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
                request.Method = "POST";
                request.ContentType = "application/json;charset=UTF-8";
                var byteData = Encoding.UTF8.GetBytes(jsonParam);
                var length = byteData.Length;
                request.ContentLength = length;
                var writer = request.GetRequestStream();
                writer.Write(byteData, 0, length);
                writer.Close();

                //接收数据
                HttpWebResponse response = (HttpWebResponse)request.GetResponse();
                Stream myResponseStream = response.GetResponseStream();
                StreamReader myStreamReader = new StreamReader(myResponseStream, Encoding.GetEncoding("utf-8"));
                string retString = myStreamReader.ReadToEnd();
                myStreamReader.Close();
                myResponseStream.Close();

            }
            catch (System.Exception ex)
            {
                //Global.LogServer.Add(new LogInfo("Error", "Upload:doUpload :url"+url+" json:"+ jsonParam+"  " + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            return true;
        
    }
        public void Close()
        {
            isRun = false;
        }

    }
}
