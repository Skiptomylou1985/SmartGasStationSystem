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
                    if (paramName == "captureflag")
                        Global.nCaptureFlag = int.Parse(paramValue);
                    if (paramName == "videorecog")
                        Global.nVideoRecogFlag = int.Parse(paramValue);
                    if (paramName == "videorecogtype")
                        Global.nVideoRecogType = int.Parse(paramValue);
                    if (paramName == "videosource")
                        Global.nVideoSource = int.Parse(paramValue);
                    if (paramName == "authtype")
                        Global.nAuthType = int.Parse(paramValue);
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
            Global.nvrList.Clear();
            try
            {
               
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
                Global.videoList.Clear();
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
                    Global.LogServer.Add(new LogInfo("ParamSet-Debug", "Main->GetRecogAreaListFromDB videoid:" +
                        video.id.ToString() + "  video.channelNo:" + video.channelNo.ToString(), (int)EnumLogLevel.DEBUG));
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
                Global.recogAreaList.Clear();
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
                    area.videoLaneNo = int.Parse(dr["vchlane"].ToString());
                    foreach (ClsNozzle nozzle in Global.nozzleList)
                    {
                        if (nozzle.areaid == area.id)
                        {
                            area.nozzleList.Add(nozzle);
                        }
                    }

                    Global.recogAreaList.Add(area);
                    Global.LogServer.Add(new LogInfo("ParamSet-Debug", "Main->GetRecogAreaListFromDB areaid:" + 
                        area.id.ToString()+"  videoid:"+area.videoid.ToString(), (int)EnumLogLevel.DEBUG));
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
                Global.nozzleList.Clear();
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
                    Global.LogServer.Add(new LogInfo("ParamSet-Debug", "Main->GetNozzleListFromDB nozzleNo:"+ nozzle.nozzleNo.ToString(), (int)EnumLogLevel.DEBUG));
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
                    comboMainArea.Enabled = false;
                    comboSubArea.Enabled = false;
                    comboMainArea2.Enabled = false;
                    comboSubArea2.Enabled = false;
                    break;
                case 1: //正在添加
                    btnAddCurve.Enabled = false;
                    btnChangeCurve.Enabled = false;
                    btnDeleteCurve.Enabled = false;
                    btnCancel.Enabled = true;
                    btnSaveCurve.Enabled = true;
                    comboNozzleNo.Enabled = false;
                    comboOilType.Enabled = false;
                    comboArea.Enabled = true;
                    btnDeleteCurve.Enabled = false;
                    btnAddNozzle.Enabled = false;
                    btnDeleteNozzle.Enabled = false;
                    comboMainArea.Enabled = false;
                    comboSubArea.Enabled = false;
                    comboMainArea2.Enabled = false;
                    comboSubArea2.Enabled = false;
                    break;
                case 2: //正在修改
                    btnAddCurve.Enabled = false;
                    btnChangeCurve.Enabled = false;
                    btnDeleteCurve.Enabled = false;
                    btnCancel.Enabled = true;
                    btnSaveCurve.Enabled = true;
                    comboNozzleNo.Enabled = false;
                    comboOilType.Enabled = true;
                    comboArea.Enabled = true;
                    btnDeleteCurve.Enabled = false;
                    btnAddNozzle.Enabled = false;
                    btnDeleteNozzle.Enabled = false;
                    comboMainArea.Enabled = false;
                    comboSubArea.Enabled = false;
                    comboMainArea2.Enabled = false;
                    comboSubArea2.Enabled = false;
                    break;
                case 3: //正在添加油枪
                    btnAddCurve.Enabled = false;
                    btnChangeCurve.Enabled = false;
                    btnDeleteCurve.Enabled = false;
                    btnCancel.Enabled = true;
                    btnSaveCurve.Enabled = true;
                    comboNozzleNo.Enabled = true;
                    comboOilType.Enabled = true;
                    comboArea.Enabled = false;
                    btnDeleteCurve.Enabled = false;
                    btnAddNozzle.Enabled = false;
                    btnDeleteNozzle.Enabled = false;
                    comboMainArea.Enabled = true;
                    comboSubArea.Enabled = true;
                    comboMainArea2.Enabled = true;
                    comboSubArea2.Enabled = true;
                    break;
                
            }

        }


       
        private void AddOrUpdateArea(int AoU)
        { 

            switch(AoU)
            {
                case 1:
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
                                    area.videoLaneNo = comboHKArea.SelectedIndex + 1;
                                    area.id = Global.mysqlHelper.ExecuteSql(area.getInsertString());
                                    Global.recogAreaList.Add(area);
                                    video.areaList.Add(area);
                                    return;
                                }
                            }
                        }
                    }
                    break;
                case 2:
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
                    break;
                case 3:
                    ClsNozzle nozzle = new ClsNozzle();
                    nozzle.nozzleNo = int.Parse(comboNozzleNo.Text);
                    nozzle.oilType = comboOilType.SelectedIndex;
                    nozzle.areaid = int.Parse(comboMainArea.Text);
                    nozzle.id = Global.mysqlHelper.ExecuteSql(nozzle.getInsertString());

                    string linkSqlString = "insert into nozzle_area (nozzleNo,areaid,linkmode) values ("+nozzle.nozzleNo.ToString()+
                        ","+comboMainArea.Text+",1)";
                    nozzle.linkedMainAreaList.Add(int.Parse(comboMainArea.Text));
                    if (comboMainArea2.Text != "不使用")
                    {
                        linkSqlString += ",(" + nozzle.nozzleNo.ToString() + "," + comboMainArea.Text + ",1)";
                        nozzle.linkedMainAreaList.Add(int.Parse(comboMainArea2.Text));
                    }
                    if (comboSubArea.Text != "不使用")
                    {
                        linkSqlString += ",(" + nozzle.nozzleNo.ToString() + "," + comboSubArea.Text + ",2)";
                        nozzle.linkedSubAreaList.Add(int.Parse(comboSubArea.Text));
                    }
                       
                    if (comboSubArea2.Text != "不使用")
                    {
                        linkSqlString += ",(" + nozzle.nozzleNo.ToString() + "," + comboSubArea2.Text + ",2)";
                        nozzle.linkedSubAreaList.Add(int.Parse(comboSubArea2.Text));
                    }
                        
                    Global.mysqlHelper.ExecuteSql(linkSqlString);
                    Global.nozzleList.Add(nozzle);
                    break;
                case 4:

                    break;
                default:
                    break;

            }

        }

       
        private bool HK_AddNozzleAndArea(int videoChan,int hkArea,int nozzleNo,int linkMode)
        {
            string sql = "select id from vch where vchno = " + videoChan.ToString();
            DataTable dt = Global.mysqlHelper.GetDataTable(sql);
            if (dt == null || dt.Rows.Count == 0)
            {
                return false;
            }
            int videoid = int.Parse(dt.Rows[0]["id"].ToString());
            
            return true;
        }


        private int HK_FindRecogAreaInVideoChan(int videoChan,int vchlane)
        {
            foreach (ClsRecogArea area in Global.recogAreaList)
            {
                if (area.videoChannel == videoChan && area.videoLaneNo == vchlane)
                {
                    return area.id;
                }
            }

            //没有匹配上，说明此识别区没有添加过，关联视频通道进行添加
            foreach (ClsVideoChannel video in Global.videoList)
            {
                if (video.channelNo == videoChan)
                {
                    ClsRecogArea area = new ClsRecogArea();
                    area.videoid = video.id;
                    area.left = 0;
                    area.right = 0;
                    area.top = 0;
                    area.bottom = 0;
                    area.videoLaneNo = vchlane;
                    area.videoChannel = videoChan;
                    area.id = Global.mysqlHelper.ExecuteSql(area.getInsertString());
                    Global.recogAreaList.Add(area);
                    video.areaList.Add(area);
                    return area.id;
                }
            }
            return -1;
        }

        private void InitHKGroupBoard()
        {

            group_hkcn.Enabled = true;
            hk_comboMainVideoChan1.Items.Clear();
            hk_comboMainVideoChan2.Items.Clear();
            hk_comboSubVideoChan1.Items.Clear();
            hk_comboSubVideoChan2.Items.Clear();
            if (Global.nMatchMode == 2 )
            {
                lblEntryExit.Visible = false;
            }
            hk_comboMainVideoChan2.Items.Add("不启用");
            hk_comboSubVideoChan1.Items.Add("不启用");
            hk_comboSubVideoChan2.Items.Add("不启用");
            foreach (ClsVideoChannel video in Global.videoList)
            {
                hk_comboMainVideoChan1.Items.Add(video.channelNo.ToString());
                hk_comboMainVideoChan2.Items.Add(video.channelNo.ToString());
                hk_comboSubVideoChan1.Items.Add(video.channelNo.ToString());
                hk_comboSubVideoChan2.Items.Add(video.channelNo.ToString());
            }
            if (hk_comboMainVideoChan1.Items.Count > 0)
            {
                hk_comboMainVideoChan1.SelectedIndex = 0;
            }
            
            hk_comboMainVideoChan2.SelectedIndex = 0;
            hk_comboSubVideoChan1.SelectedIndex = 0;
            hk_comboSubVideoChan2.SelectedIndex = 0;

            hk_comboSubVideoArea1.SelectedIndex = 0;
            hk_comboSubVideoArea2.SelectedIndex = 0;
            hk_comboMainVideoArea1.SelectedIndex = 0;
            hk_comboMainVideoArea2.SelectedIndex = 0;

            hk_comboNoz.SelectedIndex = 0;
            hk_comboOilType.SelectedIndex = 0;
            FlushDGV_HK();
            
        }

        private void FlushDGV_HK()
        {
            string sql = "select a.nozzleNo as noz, c.vchno as vchno, b.vchlane as vchlane ," +
                          "( case when a.linkmode = '1' then '主识别区' when a.linkmode = '2' then '副识别区' end) as linkmode" +
                        " FROM nozzle_area a, analysisarea as b , vch c" +
                        " where a.areaid = b.id and b.vchid = c.id order by a.nozzleNo asc";
            DataTable dt = Global.mysqlHelper.GetDataTable(sql);
            hk_DGV.DataSource = dt;
            hk_DGV.Columns[0].HeaderText = "油枪号";
            hk_DGV.Columns[1].HeaderText = "视频通道";
            hk_DGV.Columns[2].HeaderText = "识别区";
            hk_DGV.Columns[3].HeaderText = "关联类型";
            hk_DGV.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            hk_DGV.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            //dgv.AllowUserToAddRows = false;
            //dgv.AllowUserToResizeRows = false;
            hk_DGV.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
            foreach (DataGridViewColumn item in hk_DGV.Columns)
            {
                item.DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
               // item.ReadOnly = true;
            }
        }

        private bool FindVideoChanInList(int chanNo, string ip)
        {
            bool ret = false;
            foreach(ClsVideoChannel video in Global.videoList)
            {
                if (video.channelNo == chanNo && video.ip == ip)
                {
                    ret = true;
                }
            }
            return ret;

        }
    }
   
}
