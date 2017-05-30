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
                    if (paramName == "matchmode")
                        Global.nMatchMode = int.Parse(paramValue);
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
                    else if (paramName == "picpath")
                        Global.basePicPath = paramValue;
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
                treeMain.Nodes[0].Nodes.Clear();
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                if (dt == null || dt.Rows.Count < 1)
                {
                    return true;
                }
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
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                if (dt == null || dt.Rows.Count < 1)
                {
                    return true;
                }
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
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("ParamSet-Error", "Main->InitParam->GetVideoListFromDB 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            

        }

        private bool GetRecogAreaListFromDB()
        {
            string queryString = "select * from analysisarea";
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                if (dt == null || dt.Rows.Count < 1)
                {
                    return true;
                }
                foreach (DataRow dr in dt.Rows)
                {
                    ClsRecogArea area = new ClsRecogArea();
                    area.videoid = int.Parse(dr["vchid"].ToString());
                    area.id = int.Parse(dr["id"].ToString());
                    area.left = double.Parse(dr["X1"].ToString());
                    area.right = double.Parse(dr["X2"].ToString());
                    area.top = double.Parse(dr["Y1"].ToString());
                    area.bottom = double.Parse(dr["Y2"].ToString());
                    foreach (ClsNozzle nozzle in Global.nozzleList)
                    {
                        if (nozzle.areaid == area.id)
                        {
                            area.nozzleList.Add(nozzle);
                        }
                    }

                    Global.recogAreaList.Add(area);
                }
                return true;
            }
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("ParamSet-Error", "Main->InitParam->GetRecogAreaListFromDB 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            

        }
        private bool GetNozzleListFromDB()
        {
            string queryString = "select * from nozzle";
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(queryString);
                if (dt == null || dt.Rows.Count < 1)
                {
                    return true;
                }

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
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("ParamSet-Error", "Main->InitParam->GetNozzleListFromDB 运行初始化失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            

        }

        private void GetParamFromDB()
        {
            Global.nvrList.Clear();
            Global.videoList.Clear();
            Global.recogAreaList.Clear();
            Global.nozzleList.Clear();
            GetNozzleListFromDB();
            Global.LogServer.Add(new LogInfo("ParamSet-Debug", "main->GetParamFromDB->GetNozzleListFromDB done", (int)EnumLogLevel.DEBUG));
            GetRecogAreaListFromDB();
            Global.LogServer.Add(new LogInfo("ParamSet-Debug", "main->GetParamFromDB->GetRecogAreaListFromDB done", (int)EnumLogLevel.DEBUG));
            GetVideoListFromDB();
            Global.LogServer.Add(new LogInfo("ParamSet-Debug", "main->GetParamFromDB->GetVideoListFromDB done", (int)EnumLogLevel.DEBUG));
            GetNVRListFromDB();
            Global.LogServer.Add(new LogInfo("ParamSet-Debug", "main->GetParamFromDB->GetNVRListFromDB done", (int)EnumLogLevel.DEBUG));
        }
        private void SwitchVideo()
        {
            comboArea.Items.Clear();
            foreach (ClsVideoChannel video in Global.videoList)
            {
                if (video.channelNo == Global.nCurSelectedVideoChan)
                {
                    if (video.areaList.Count < 1)
                    {
                        comboArea.Items.Add("无");
                        return;
                    }
                    comboArea.Items.Add("全部");
                    foreach (ClsRecogArea area in video.areaList)
                    {
                        comboArea.Items.Add( area.id.ToString());
                    }
                    comboArea.SelectedIndex = 0;
                }
            }
           // 
        }
       
        private void SwithFormStat(int status)
        {
            Global.nCurStatus = status;
            switch(status)
            {
                case 0: //正常显示
                    btnAddCurve.Enabled = true;
                    btnChangeCurve.Enabled = true;
                    btnDeleteCurve.Enabled = true;
                    btnCancel.Enabled = false;
                    btnSaveCurve.Enabled = false;
                    comboNozzleNo.Enabled = true;
                    comboOilType.Enabled = true;
                    comboArea.Enabled = true;
                    btnDeleteCurve.Enabled = true;
                    btnAddNozzle.Enabled = true;
                    btnDeleteNozzle.Enabled = true;
                    break;
                case 1: //正在添加
                    btnAddCurve.Enabled = false;
                    btnChangeCurve.Enabled = false;
                    btnDeleteCurve.Enabled = false;
                    btnCancel.Enabled = true;
                    btnSaveCurve.Enabled = true;
                    comboNozzleNo.Enabled = false;
                    comboOilType.Enabled = false;
                    comboArea.Enabled = false;
                    btnDeleteCurve.Enabled = false;
                    btnAddNozzle.Enabled = false;
                    btnDeleteNozzle.Enabled = false;
                    break;
                case 2: //正在修改
                    btnAddCurve.Enabled = false;
                    btnChangeCurve.Enabled = false;
                    btnDeleteCurve.Enabled = false;
                    btnCancel.Enabled = true;
                    btnSaveCurve.Enabled = true;
                    comboNozzleNo.Enabled = false;
                    comboOilType.Enabled = true;
                    comboArea.Enabled = false;
                    btnDeleteCurve.Enabled = false;
                    btnAddNozzle.Enabled = false;
                    btnDeleteNozzle.Enabled = false;
                    break;
            }

        }


       
        private void AddOrUpdateArea(int AoU)
        { 

            if (AoU == 1) //add 
            {
                foreach (ClsNVRInfo nvr in Global.nvrList)
                {
                    if (nvr.nvrName == Global.sCurSelectedNvrName)
                    {
                        foreach (ClsVideoChannel video in nvr.videoList)
                        {
                            if (video.channelNo == Global.nCurSelectedVideoChan)
                            {
                                ClsRecogArea area = new ClsRecogArea();
                                area.videoid = video.id;
                                area.left = (double)Math.Round((decimal)struDrawInfo.start.X / this.videoBox.Width, 4);
                                area.right = (double)Math.Round((decimal)struDrawInfo.end.X / this.videoBox.Width, 4);
                                area.top = (double)Math.Round((decimal)struDrawInfo.start.Y / this.videoBox.Height, 4);
                                area.bottom = (double)Math.Round((decimal)struDrawInfo.end.Y / this.videoBox.Height, 4);
                                area.id = Global.mysqlHelper.ExecuteSql(area.getInsertString());
                                Global.recogAreaList.Add(area);
                                video.areaList.Add(area);
                                return;
                            }
                        }

                        //没有匹配到，则添加视频通道
                        //ClsVideoChannel videoChan = new ClsVideoChannel();
                        //int i = Global.nCurSelectedVideoChan;
                        //videoChan.ip = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].struIP.sIpV4);
                        //videoChan.channelNo = Global.nCurSelectedVideoChan;
                        //videoChan.loginName = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].sUserName);
                        //videoChan.password = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].sPassword);
                        //videoChan.port = nvr.config.struIPDevInfo[i].wDVRPort;
                        //videoChan.streamType = nvr.config.struStreamMode[i].byGetStreamType;
                        //videoChan.id = Global.mysqlHelper.ExecuteSql(videoChan.getInsertString());

                        //ClsRecogArea area2 = new ClsRecogArea();
                        //area2.videoid = videoChan.id;
                        //area2.left = (double)Math.Round((decimal)struDrawInfo.start.X / this.videoBox.Width, 4);
                        //area2.right = (double)Math.Round((decimal)struDrawInfo.end.X / this.videoBox.Width, 4);
                        //area2.top = (double)Math.Round((decimal)struDrawInfo.start.Y / this.videoBox.Height, 4);
                        //area2.bottom = (double)Math.Round((decimal)struDrawInfo.end.Y / this.videoBox.Height, 4);
                        //area2.id = Global.mysqlHelper.ExecuteSql(area2.getInsertString());
                        
                        //Global.recogAreaList.Add(area2);
                        //videoChan.areaList.Add(area2);
                        //Global.videoList.Add(videoChan);
                        //nvr.videoList.Add(videoChan);
                    }
                }
            } 
            else if(AoU == 2) //update
            {
                foreach (ClsRecogArea area in Global.recogAreaList)
                {
                    if (area.id.ToString() == comboArea.Text.Trim())
                    {
                        area.left = (double)Math.Round((decimal)struDrawInfo.start.X / this.videoBox.Width, 4);
                        area.right = (double)Math.Round((decimal)struDrawInfo.end.X / this.videoBox.Width, 4);
                        area.top = (double)Math.Round((decimal)struDrawInfo.start.Y / this.videoBox.Height, 4);
                        area.bottom = (double)Math.Round((decimal)struDrawInfo.end.Y / this.videoBox.Height, 4);
                        Global.mysqlHelper.ExecuteSql(area.getUpdateString());
                    }
                }

            }

        }

       

    }
   
}
