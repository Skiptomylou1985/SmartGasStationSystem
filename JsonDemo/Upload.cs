using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace JsonDemo
{
    public class Upload
    {
        public bool DoUpload(object obj,string url)
        {
            
            try
            {
                //序列化参数
                string jsonParam = JsonHelper.SerializeObject(obj);
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
                MessageBox.Show(ex.ToString());
                return false;
            }
            return true;
        }
        
    }
}
