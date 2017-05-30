using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace ParamSet
{
    public partial class FormMain : Form
    {
        private ComboBox comboNozzleBak ;
        public struDraw struDrawInfo;
        public int nCurDrawIndex;
        private Graphics[] g = new Graphics[4];
        public FormMain()
        {
            InitializeComponent();
        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            comboNozzleBak = this.comboNozzleNo;
            groupBoxSet.Enabled = false;
            treeMain.Enabled = false;
            Global.LogServer = new Log(Global.nLogLevel);
            Global.LogServer.Run();
            nCurDrawIndex = 0;
            struDrawInfo = new struDraw();
            struDrawInfo.g = this.videoBox.CreateGraphics();
            comboDBType.SelectedIndex = 0;
            treeMain.Nodes.Add("设备");
            btnClose.Enabled = false;
            btnSetInfo.Enabled = false;
            SwithFormStat(0);
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            try
            {
                DBInfo info = new DBInfo();
                info.type = comboDBType.Text.ToString();
                info.ip = textDBIP.Text.ToString();
                info.dbname = textDBName.Text.ToString();
                info.username = textDBAdmin.Text.ToString();
                info.password = textDBPwd.Text.ToString();
                info.port = 3306;
                Global.LogServer.Add(new LogInfo("ParamSet-Debug", "main->InitDatabase param value" +
                   Global.iniPath + " " + info.type + " " + info.ip + " " + info.dbname + " " + info.username + " " + info.password, (int)EnumLogLevel.DEBUG));
                Global.mysqlHelper = new MysqlHelper(info);
                if (!Global.mysqlHelper.ConnectDB())
                {
                    MessageBox.Show("数据库连接失败！");
                }
                GetMainParam();
                Global.LogServer.Add(new LogInfo("ParamSet-Debug", "main->btnOpen_Click->GetMainParam done", (int)EnumLogLevel.DEBUG));
                GetParamFromDB();
                treeMain.Enabled = true;
                groupBoxSet.Enabled = true;
                btnClose.Enabled = true;
                btnOpen.Enabled = false;
                btnSetInfo.Enabled = true;
                lblStationName.Text = Global.stationInfo.stationName;
            }
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("ParamSet-Error", "Main:InitDatabase 初始化数据库失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                MessageBox.Show("数据库连接失败！");
            }


        }


        private void treeDevice_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Button == MouseButtons.Right  )
            {
                if (e.Node.Text == treeMain.Nodes[0].Text)
                {
                    Point pos = new Point(e.Node.Bounds.X + e.Node.Bounds.Width, e.Node.Bounds.Y + e.Node.Bounds.Height / 2);
                    this.contextTreeAdd.Show(this.treeMain, pos);
                } 
                else 
                {
                    Point pos = new Point(e.Node.Bounds.X + e.Node.Bounds.Width, e.Node.Bounds.Y + e.Node.Bounds.Height / 2);
                    this.contextMenuDelete.Show(this.treeMain, pos);
                }
                
            }
        }

        private void contextTreeMenu_MouseClick(object sender, MouseEventArgs e)
        {
            //if (e.Button == MouseButtons.Left && contextTreeMenu.Items[0].Selected)
            //{
            //    FormNVR formnvr = new FormNVR();
            //    formnvr.ShowDialog();
            //} 
            //else if(contextTreeMenu.Items[0].Selected)
            //{
            //}
        }

        private void videoBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (Global.nCurStatus == 1 || Global.nCurStatus == 2)
            {
                struDrawInfo.bReDraw = true;
                struDrawInfo.start.X = e.X;
                struDrawInfo.start.Y = e.Y;
                struDrawInfo.end.X = e.X;
                struDrawInfo.end.Y = e.Y;
            }

        }

        private void videoBox_MouseMove(object sender, MouseEventArgs e)
        {
            if ((Global.nCurStatus == 1 || Global.nCurStatus == 2) && struDrawInfo.bReDraw)
            {
                struDrawInfo.end.X = e.X;
                struDrawInfo.end.Y = e.Y;
            }

        }

        private void videoBox_MouseUp(object sender, MouseEventArgs e)
        {
            struDrawInfo.bReDraw = false;
        }

        private void FormMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            Global.LogServer.Stop();
        }

        private void treeMain_DoubleClick(object sender, EventArgs e)
        {
            try
            {
                TreeNode node = treeMain.SelectedNode;
                if (node.Nodes.Count > 0)
                {
                    return;
                }
                foreach (ClsNVRInfo nvr in Global.nvrList)
                {
                    if (node.Text == nvr.nvrName)
                    {
                        try
                        {
                            if (0 == SPlate.SP_InitNVR(nvr.ip, nvr.port, nvr.loginName, nvr.password))
                            {
                                Global.LogServer.Add(new LogInfo("ParamSet-Debug", "SP_InitNVR true", (int)EnumLogLevel.DEBUG));
                                IntPtr ip = Marshal.AllocHGlobal(Marshal.SizeOf(nvr.config));
                                int lenth = 0;
                                SPlate.SP_GetNvrCfg(ip, ref lenth);
                                nvr.config = (NET_DVR_IPPARACFG_V40)Marshal.PtrToStructure(ip, typeof(NET_DVR_IPPARACFG_V40));

                                for (int i = 0; i < nvr.config.dwDChanNum; i++)
                                {
                                    Global.LogServer.Add(new LogInfo("ParamSet-Debug", "dwDChanNum:" + i.ToString(), (int)EnumLogLevel.DEBUG));
                                    if (nvr.config.struIPDevInfo[i].byEnable == 1)
                                    {
                                        TreeNode cNode = new TreeNode();
                                        cNode.Text = "Video" + i.ToString();
                                        node.Nodes.Add(cNode);
                                        Global.LogServer.Add(new LogInfo("ParamSet-Debug", "struIPDevInfo.byEnable true", (int)EnumLogLevel.DEBUG));

                                    }
                                }
                            }
                            Global.sCurSelectedNvrName = nvr.nvrName;
                            break;
                        }
                        catch (System.Exception ex)
                        {
                            Global.LogServer.Add(new LogInfo("ParamSet-Error", "FormMain->treeMain_DoubleClick", (int)EnumLogLevel.ERROR));
                        }

                    }
                    else
                    {
                        for (int i = 0; i < nvr.config.dwDChanNum; i++)
                        {
                            if (node.Text == "Video" + i.ToString())
                            {
                                NET_DVR_PREVIEWINFO previewInfo = new NET_DVR_PREVIEWINFO();
                                previewInfo.hPlayWnd = videoBox.Handle;//预览窗口
                                previewInfo.lChannel = nvr.config.dwStartDChan + i;
                                previewInfo.dwStreamType = 0;//码流类型：0-主码流，1-子码流，2-码流3，3-码流4，以此类推
                                previewInfo.dwLinkMode = 0;//连接方式：0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP 
                                previewInfo.bBlocked = false; //0- 非阻塞取流，1- 阻塞取流
                                previewInfo.dwDisplayBufNum = 15;
                                int lenth = Marshal.SizeOf(previewInfo);
                                SPlate.SP_PreviewInfo(ref previewInfo, lenth).ToString();

                                //更新当前被选中的视频线路
                                Global.bVideoInShow = true;
                                Global.nCurSelectedVideoChan = i;
                                lblCurVideoNo.Text = "当前视频：Video" + i.ToString();
                                break;
                            }
                        }

                        SwitchVideo();
                    }
                }
            }
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("ParamSet-Error", "FormMain->treeMain_DoubleClick:"+ex.Message, (int)EnumLogLevel.ERROR));
            }
            
        }

        private void timerCurve_Tick(object sender, EventArgs e)
        {
            
            if (Global.nCurStatus == 1 || Global.nCurStatus == 2)  //添加或修改识别区域
            {
                struDrawInfo.g.DrawRectangle(new Pen(Color.Red), struDrawInfo.start.X, struDrawInfo.start.Y,
                                             struDrawInfo.end.X - struDrawInfo.start.X, struDrawInfo.end.Y - struDrawInfo.start.Y);
            }
            else if (Global.nCurStatus == 0)
            {
                
                foreach(ClsNVRInfo nvr in Global.nvrList)
                {
                    if (Global.sCurSelectedNvrName == nvr.nvrName)
                    {
                        foreach (ClsVideoChannel video in nvr.videoList)
                        {
                            if (Global.nCurSelectedVideoChan == video.channelNo)
                            {
                                for (int i =0;i<video.areaList.Count; i++)
                                {
                                    if (comboArea.SelectedIndex == 0 || video.areaList[i].id.ToString() == comboArea.Text.Trim() ) 
                                    {
                                        int X1 = (int)(video.areaList[i].left * videoBox.Width);
                                        int X2 = (int)(video.areaList[i].right * videoBox.Width);
                                        int Y1 = (int)(video.areaList[i].top * videoBox.Height);
                                        int Y2 = (int)(video.areaList[i].bottom * videoBox.Height);
                                        Graphics g = this.videoBox.CreateGraphics();
                                        g.DrawRectangle(new Pen(Color.Red), X1, Y1, X2 - X1, Y2 - Y1);
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }

        private void addDevice_Click(object sender, EventArgs e)
        {
            FormNVR formnvr = new FormNVR();
            formnvr.ShowDialog();
            GetNVRListFromDB();
        }

        private void deleteDevice_Click(object sender, EventArgs e)
        {

        }
        private void deleteDevice()

        {
            TreeNode node = treeMain.SelectedNode;
            foreach (ClsNVRInfo nvr in Global.nvrList)
            {
                if (node.Text == nvr.nvrName)
                {
                    string sqlString = "delete a,b,c,d from nozzle a,analysisarea b,vch c ,videohost d " +
                                        "where a.areaid = b.id and b.vchid = c.id and c.parentid = d.id and d.hostname = '" + nvr.nvrName + "'";
                    Global.mysqlHelper.ExecuteSql(sqlString);
                    Global.nvrList.Remove(nvr);
                }
            }
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if(DialogResult.Yes == (MessageBox.Show("确认删除设备？", "提示", MessageBoxButtons.YesNo)))
            {
                TreeNode node = treeMain.SelectedNode;
                foreach (ClsNVRInfo nvr in Global.nvrList)
                {
                    if (node.Text == nvr.nvrName)
                    {
                        string sqlString = "delete a,b,c,d from nozzle a,analysisarea b,vch c ,videohost d " +
                                            "where a.areaid = b.id and b.vchid = c.id and c.parentid = d.id and d.hostname = '" + nvr.nvrName + "'";
                        Global.mysqlHelper.ExecuteSql(sqlString);
                        sqlString = "delete b,c,d from analysisarea b,vch c ,videohost d " +
                                            "where b.vchid = c.id and c.parentid = d.id and d.hostname = '" + nvr.nvrName + "'";
                        Global.mysqlHelper.ExecuteSql(sqlString);
                        sqlString = "delete c,d from vch c ,videohost d " +
                                            "where c.parentid = d.id and d.hostname = '" + nvr.nvrName + "'";
                        Global.mysqlHelper.ExecuteSql(sqlString);
                        sqlString = "delete from videohost where hostname = '" + nvr.nvrName + "'";
                        Global.mysqlHelper.ExecuteSql(sqlString);
                        break;
                    }
                }
                GetParamFromDB();
            }
        }

        private void btnAddCurve_Click(object sender, EventArgs e)
        {
            Global.nCurStatus = 1;
            lblAction.Text = "请绘制识别区并保存";
            lblAction.ForeColor = Color.Red;
            SwithFormStat(1);
            foreach (ClsNVRInfo nvr in Global.nvrList)
            {
                if (nvr.nvrName == Global.sCurSelectedNvrName)
                {
                    foreach (ClsVideoChannel video in Global.videoList)
                    {
                        if (video.channelNo == Global.nCurSelectedVideoChan)
                        {
                            return;
                        }

                    }
                    ClsVideoChannel videoChan = new ClsVideoChannel();
                    int i = Global.nCurSelectedVideoChan;
                    videoChan.ip = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].struIP.sIpV4);
                    videoChan.channelNo = Global.nCurSelectedVideoChan;
                    videoChan.loginName = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].sUserName);
                    videoChan.password = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].sPassword);
                    videoChan.port = nvr.config.struIPDevInfo[i].wDVRPort;
                    videoChan.streamType = nvr.config.struStreamMode[i].byGetStreamType;
                    videoChan.id = Global.mysqlHelper.ExecuteSql(videoChan.getInsertString());

                    Global.videoList.Add(videoChan);
                    nvr.videoList.Add(videoChan);
                }
            }
            
            
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Global.nCurStatus = 0;
            SwithFormStat(0);
        }

        private void btnSaveCurve_Click(object sender, EventArgs e)
        {

            //if (comboNozzleNo.SelectedIndex < 0)
            //{
            //    MessageBox.Show("请选择油枪");
            //    return;
            //}
            //if (comboOilType.SelectedIndex < 0)
            //{
            //    MessageBox.Show("请选择油类型");
            //    return;
            //}
            //if (comboNozzleNo.Text.ToString().Trim() == "入口") //入口
            //{
            //    AddOrUpdateNozzleOrInOut(0, Global.nCurStatus);
            //}
            //else if(comboNozzleNo.Text.ToString().Trim() == "出口")
            //{
            //    AddOrUpdateNozzleOrInOut(100, Global.nCurStatus);
            //}
            //else
            //{
            //    AddOrUpdateNozzleOrInOut(int.Parse(comboNozzleNo.Text.ToString()), Global.nCurStatus);
            //}
            AddOrUpdateArea(Global.nCurStatus);
            SwithFormStat(0);
            SwitchVideo();
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void btnChangeCurve_Click(object sender, EventArgs e)
        {
            //this.comboNozzleNo.Items.Clear();
            this.comboArea.Items.Clear();
            foreach (ClsVideoChannel video in Global.videoList)
            {
                if (video.channelNo == Global.nCurSelectedVideoChan)
                {
                    foreach (ClsRecogArea area in video.areaList)
                    {
                        this.comboArea.Items.Add(area.id.ToString());
                    }
                    if (this.comboArea.Items.Count > 0)
                    {
                        this.comboArea.SelectedIndex = 0;
                    }
                    break;
                }
            }
            
            SwithFormStat(2);
        }

        private void comboNozzleNo_SelectedIndexChanged(object sender, EventArgs e)
        {
            //if (Global.nCurStatus == 2)
            //{
            //    foreach (ClsRecogArea area in Global.recogAreaList)
            //    {
            //        if (area.nozzle.nozzleNo.ToString() == comboNozzleNo.Text.Trim())
            //        {
            //            struDrawInfo.start.X = (int)(area.left * videoBox.Width);
            //            struDrawInfo.start.Y = (int)(area.top * videoBox.Height);
            //            struDrawInfo.end.X = (int)(area.right * videoBox.Width);
            //            struDrawInfo.end.Y = (int)(area.bottom * videoBox.Height);
            //            comboOilType.SelectedIndex = area.nozzle.oilType;
            //        }
            //    }

            //}
        }

        private void btnDeleteCurve_Click(object sender, EventArgs e)
        {
           
            if (comboArea.Text.Trim() == "全部")
            {
                if (DialogResult.Yes == MessageBox.Show("确认删除视频"+Global.nCurSelectedVideoChan.ToString()+"所有关联的所有识别区及油枪信息?","提示",MessageBoxButtons.YesNo))
                {
                    string sqlString = "delete a ,b from nozzle a,analysisarea b,vch c where a.areaid = b.id and b.vchid = c.id and c.vchno = " + Global.nCurSelectedVideoChan.ToString();
                    Global.mysqlHelper.ExecuteSql(sqlString);
                    sqlString = "delete b from analysisarea b,vch c where  b.vchid = c.id and c.vchno = " + Global.nCurSelectedVideoChan.ToString();
                    Global.mysqlHelper.ExecuteSql(sqlString);
                    GetParamFromDB();
                }
            }
            else
            {
                if (DialogResult.Yes == MessageBox.Show("确认删除视频" + Global.nCurSelectedVideoChan.ToString() + "所关联的识别区"+comboArea.Text+"及该区域所关联的油枪?", "提示", MessageBoxButtons.YesNo))
                {
                    
                    string sqlString = "delete a ,b from nozzle a,analysisarea b,vch c where a.areaid = b.id and b.vchid = c.id and c.vchno = " + 
                        Global.nCurSelectedVideoChan.ToString();
                    Global.mysqlHelper.ExecuteSql(sqlString);
                    sqlString = "delete b from analysisarea b,vch c where b.vchid = c.id and c.vchno = " +
                        Global.nCurSelectedVideoChan.ToString() + " and b.id = " + comboArea.Text.Trim();
                    Global.mysqlHelper.ExecuteSql(sqlString);
                    GetParamFromDB();
                }
            }
        }

        private void btnSetInfo_Click(object sender, EventArgs e)
        {
            FormStationInfo info = new FormStationInfo();
            info.ShowDialog();
            lblStationName.Text = Global.stationInfo.stationName;
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            treeMain.Nodes[0].Nodes.Clear();
            Global.nvrList.Clear();
            Global.videoList.Clear();
            Global.recogAreaList.Clear();
            Global.nozzleList.Clear();
            groupBoxSet.Enabled = false;
            treeMain.Enabled = false;
            btnOpen.Enabled = true;
            btnClose.Enabled = false;
            btnSetInfo.Enabled = false;
        }

        private void comboArea_SelectedIndexChanged(object sender, EventArgs e)
        {
            string info = "已关联油枪：";
            if (comboArea.Text != "全部")
            {
                foreach (ClsNozzle nozz in Global.nozzleList)
                {
                    if (nozz.areaid.ToString() == comboArea.Text)
                    {
                        info = info + nozz.nozzleNo.ToString() + " ";
                    }
                }
            }
            
        }

        private void btnAddNozzle_Click(object sender, EventArgs e)
        {

        }
    }
}
