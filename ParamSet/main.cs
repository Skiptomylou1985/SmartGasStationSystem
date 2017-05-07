using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Windows.Forms;

namespace ParamSet
{
    partial class FormMain
    {
        private bool GetMainParam()
        {

            string queryString = "select paramName,paramValue,content,defaultValue from param ";
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                foreach (DataRow dr in dt.Rows)
                {
                    string paramName = dr["paramName"].ToString();
                    string paramValue = dr["paramValue"].ToString();
                    if (paramName == "loglevel")
                        Global.nLogLevel = int.Parse(paramValue);
                    else if (paramName == "stationname")
                        Global.stationInfo.stationName = paramValue;
                    else if (paramName == "stationcode")
                        Global.stationInfo.stationCode = paramValue;
                    else if (paramName == "province")
                        Global.stationInfo.province = paramValue;
                    else if (paramName == "city")
                        Global.stationInfo.city = paramValue;
                    else if (paramName == "district")
                        Global.stationInfo.district = paramValue;
                    else if (paramName == "address")
                        Global.stationInfo.addr = paramValue;
                    //TODO 一系列参数的初始化
                }
            }
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetMainParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            //queryString = "select "

            return true;
        }
        private bool GetNozzleChannelParam()
        {
            string queryString = "select a.vchno,b.x1,b.x2,b.y1,b.y2,c.nozzleno,c.oiltype,d.id " +
                                    "from (vch a right join analysisarea b on a.id = b.vchid) right join nozzle c on b.id = c.areaid ";
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                foreach (DataRow dr in dt.Rows)
                {
                    ClsNozzle nozzle = new ClsNozzle();
                    nozzle.machineNo = int.Parse(dr["nozzleno"].ToString());
                    nozzle.oilType = int.Parse(dr["oiltype"].ToString());
                    nozzle.recogArea.left = (int)(double.Parse(dr["x1"].ToString()) * Global.nDefaultWidth);
                    nozzle.recogArea.right = (int)(double.Parse(dr["x2"].ToString()) * Global.nDefaultWidth);
                    nozzle.recogArea.top = (int)(double.Parse(dr["y1"].ToString()) * Global.nDefaultHeight);
                    nozzle.recogArea.bottom = (int)(double.Parse(dr["y2"].ToString()) * Global.nDefaultHeight);
                    nozzle.videoChanNo = int.Parse(dr["vchno"].ToString());
                    Global.nozzleList.Add(nozzle);

                    StringBuilder info = new StringBuilder();
                    info.Append("machineNo：" + nozzle.machineNo.ToString());
                    info.Append(" videoChanNo：" + nozzle.videoChanNo.ToString());
                    info.Append(" oilType：" + nozzle.oilType.ToString());
                    info.Append(" left：" + nozzle.recogArea.left.ToString());
                    info.Append(" right：" + nozzle.recogArea.right.ToString());
                    info.Append(" top：" + nozzle.recogArea.top.ToString());
                    info.Append(" bottom：" + nozzle.recogArea.bottom.ToString());
                    Global.LogServer.Add(new LogInfo("Main", "Main->InitParam->GetNozzleChannelParam get param:" + info.ToString(), (int)EnumLogLevel.DEBUG));


                }
            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetNozzleChannelParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            return true;
        }

        private bool GetNVRList()
        {
            string queryString = "select * from videohost";
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                
                foreach (DataRow dr in dt.Rows)
                {
                    ClsNVRInfo nvr = new ClsNVRInfo();
                    nvr.nvrType = dr["hosttype"].ToString();
                    nvr.nvrName = dr["hostname"].ToString();
                    nvr.ip = dr["hostip"].ToString();
                    nvr.password = dr["loginpwd"].ToString();
                    nvr.loginName = dr["loginname"].ToString();
                    nvr.port = int.Parse(dr["hostport"].ToString());
                    Global.nvrInfoList.Add(nvr);
                    TreeNode nvrTree = new TreeNode(nvr.nvrName);
                    treeMain.Nodes[0].Nodes.Add(nvrTree);
                }
            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetNozzleChannelParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            return true;
        }
        private bool GetVideoInfoFromDB()
        {
            return true;

        }
    }
   
}
