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
                    Global.LogServer.Add(new LogInfo("Debug", "Upload-> doUpload：发送trade信息", (int)EnumLogLevel.DEBUG));
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
