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
                Global.LogServer.Add(new LogInfo("ParamSet-Error", "Main->InitParam->GetMainParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            return true;
        }

        //private bool GetNozzleChannelParam()
        //{
        //    string queryString = "select a.vchno,b.x1,b.x2,b.y1,b.y2,c.nozzleno,c.oiltype,d.id " +
        //                            "from (vch a right join analysisarea b on a.id = b.vchid) right join nozzle c on b.id = c.areaid ";
        //    try
        //    {
        //        DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
        //        foreach (DataRow dr in dt.Rows)
        //        {
        //            ClsNozzle nozzle = new ClsNozzle();
        //            nozzle.machineNo = int.Parse(dr["nozzleno"].ToString());
        //            nozzle.oilType = int.Parse(dr["oiltype"].ToString());
        //            nozzle.recogArea.left = (int)(double.Parse(dr["x1"].ToString()) * Global.nDefaultWidth);
        //            nozzle.recogArea.right = (int)(double.Parse(dr["x2"].ToString()) * Global.nDefaultWidth);
        //            nozzle.recogArea.top = (int)(double.Parse(dr["y1"].ToString()) * Global.nDefaultHeight);
        //            nozzle.recogArea.bottom = (int)(double.Parse(dr["y2"].ToString()) * Global.nDefaultHeight);
        //            nozzle.videoChanNo = int.Parse(dr["vchno"].ToString());
        //            Global.nozzleList.Add(nozzle);

        //            StringBuilder info = new StringBuilder();
        //            info.Append("machineNo：" + nozzle.machineNo.ToString());
        //            info.Append(" videoChanNo：" + nozzle.videoChanNo.ToString());
        //            info.Append(" oilType：" + nozzle.oilType.ToString());
        //            info.Append(" left：" + nozzle.recogArea.left.ToString());
        //            info.Append(" right：" + nozzle.recogArea.right.ToString());
        //            info.Append(" top：" + nozzle.recogArea.top.ToString());
        //            info.Append(" bottom：" + nozzle.recogArea.bottom.ToString());
        //            Global.LogServer.Add(new LogInfo("Main", "Main->InitParam->GetNozzleChannelParam get param:" + info.ToString(), (int)EnumLogLevel.DEBUG));


        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        Global.LogServer.Add(new LogInfo("Error", "Main->InitParam->GetNozzleChannelParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
        //        return false;
        //    }
        //    return true;
        //}

        private bool GetNVRListFromDB()
        {
            string queryString = "select * from videohost";
            Global.stationInfo.nvrList.Clear();
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                
                foreach (DataRow dr in dt.Rows)
                {
                    ClsNVRInfo nvr = new ClsNVRInfo();
                    nvr.id= int.Parse(dr["id"].ToString());
                    nvr.nvrType = dr["hosttype"].ToString();
                    nvr.nvrName = dr["hostname"].ToString();
                    nvr.ip = dr["hostip"].ToString();
                    nvr.password = dr["loginpwd"].ToString();
                    nvr.loginName = dr["loginname"].ToString();
                    nvr.port = int.Parse(dr["hostport"].ToString());
                    foreach (ClsVideoChannel video in Global.videoList)
                    {
                        if (video.parentID == nvr.id)
                        {
                            nvr.videoList.Add(video);
                        }
                    }
                    Global.nvrList.Add(nvr);
                    TreeNode nvrTree = new TreeNode(nvr.nvrName);
                    treeMain.Nodes[0].Nodes.Add(nvrTree);
                    
                }
            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("ParamSet-Error", "Main->InitParam->GetNozzleChannelParam 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            return true;
        }

        private bool GetVideoListFromDB()
        {
            string queryString = "select * from vch ";
            DataTable dt = Global.mysqlHelper.GetDataTable(queryString);

            foreach (DataRow dr in dt.Rows)
            {
                ClsVideoChannel video = new ClsVideoChannel();
                video.id = int.Parse(dr["id"].ToString());
                video.channelNo = int.Parse(dr["vchno"].ToString());
                video.ip = dr["vchip"].ToString();
                video.port = int.Parse(dr["vchport"].ToString());
                video.loginName = dr["loginname"].ToString();
                video.password = dr["loginpwd"].ToString();
                video.parentID = int.Parse(dr["parentid"].ToString());
                video.streamType = int.Parse(dr["streamType"].ToString());
                video.videoName = dr["vchname"].ToString();
                video.videoType = int.Parse(dr["vchtype"].ToString());
                video.videoAttr = dr["vchAttr"].ToString();
                foreach (ClsRecogArea area in Global.recogAreaList)
                {
                    if (area.videoid == video.id)
                    {
                        video.areaList.Add(area);
                    }
                }
                Global.videoList.Add(video);
            }
            return true;

        }

        private bool GetRecogAreaListFromDB()
        {
            string queryString = "select * from analysisarea";
            DataTable dt = Global.mysqlHelper.GetDataTable(queryString);

            foreach (DataRow dr in dt.Rows)
            {
                ClsRecogArea area = new ClsRecogArea();
                area.videoid = int.Parse(dr["vchid"].ToString());
                area.id = int.Parse(dr["id"].ToString());
                area.left = double.Parse(dr["X1"].ToString());
                area.right = double.Parse(dr["X2"].ToString());
                area.top = double.Parse(dr["Y1"].ToString());
                area.bottom = double.Parse(dr["Y2"].ToString());
                foreach(ClsNozzle nozzle in Global.nozzleList)
                {
                    if (nozzle.areaid == area.id)
                    {
                        area.nozzle = nozzle;
                    }
                }

                Global.recogAreaList.Add(area);
            }
            return true;

        }
        private bool GetNozzleListFromDB()
        {
            string queryString = "select * from nozzle";
            DataTable dt = Global.mysqlHelper.GetDataTable(queryString);

            foreach (DataRow dr in dt.Rows)
            {
                ClsNozzle nozzle = new ClsNozzle();
                nozzle.id = int.Parse(dr["id"].ToString());
                nozzle.parentid = int.Parse(dr["parentid"].ToString());
                nozzle.nozzleNo = int.Parse(dr["nozzleno"].ToString());
                nozzle.oilType = int.Parse(dr["oiltype"].ToString());
                nozzle.areaid = int.Parse(dr["areaid"].ToString());
                nozzle.subAreaid = int.Parse(dr["subareaid"].ToString());
                Global.nozzleList.Add(nozzle);
            }
            return true;

        }

        private void SwitchVideo()
        {
            
                foreach (ClsVideoChannel video in Global.videoList)
                {
                    if (video.channelNo == Global.nCurSelectedVideoChan)
                    {
                        comboAreaShow.Items.Add("全部");
                        comboAreaShow.Items.Add("不显示");
                    foreach (ClsRecogArea area in video.areaList )
                        {
                            comboAreaShow.Items.Add("油枪" + area.nozzle.nozzleNo.ToString());
                        }
                    }
                }
        }
        private void FlushFormItems()
        {
            comboNozzleNo.Items.Clear();
            //comboOilType.Items.Clear();
            comboAreaShow.Items.Clear();
        }
    }
   
}
