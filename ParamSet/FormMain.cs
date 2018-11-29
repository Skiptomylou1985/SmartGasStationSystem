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
        private int lPlayHandle = -1;
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
            group_hkcn.Enabled = false;
            group_wentong.Enabled = false;
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
                    return;
                }
                GetMainParam();
                Global.LogServer.Add(new LogInfo("ParamSet-Debug", "main->btnOpen_Click->GetMainParam done", (int)EnumLogLevel.DEBUG));
                treeMain.Nodes[0].Nodes.Clear();
                GetParamFromDB();
                foreach (ClsNVRInfo nvr in Global.nvrList)
                {
                    TreeNode nvrTree = new TreeNode(nvr.nvrName);
                    treeMain.Nodes[0].Nodes.Add(nvrTree);
                }
                
                treeMain.Enabled = true;
                groupBoxSet.Enabled = true;
                btnClose.Enabled = true;
                btnOpen.Enabled = false;
                btnSetInfo.Enabled = true;
                lblStationName.Text = Global.stationInfo.stationName;

                if (Global.nVideoRecogType == 0 )
                {
                    group_wentong.Enabled = true;
                }
                else if(Global.nVideoRecogType == 1 && Global.videoList.Count > 0)
                {
                    InitHKGroupBoard();
                }


                
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
                                        ClsVideoChannel videoChan = new ClsVideoChannel();
                                        videoChan.ip = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].struIP.sIpV4);
                                        videoChan.channelNo = i;
                                        videoChan.loginName = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].sUserName);
                                        videoChan.password = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].sPassword);
                                        videoChan.port = nvr.config.struIPDevInfo[i].wDVRPort;
                                        videoChan.streamType = nvr.config.struStreamMode[i].byGetStreamType; 
                                        videoChan.parentID = nvr.id;

                                        if (!FindVideoChanInList(videoChan.channelNo,videoChan.ip))
                                        {
                                            videoChan.id = Global.mysqlHelper.ExecuteSql(videoChan.getInsertString());
                                            Global.videoList.Add(videoChan);
                                            nvr.videoList.Add(videoChan);
                                        }
                                        
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

                        if (Global.nVideoRecogType == 1)
                        {
                            InitHKGroupBoard();
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
                                if (lPlayHandle >= 0)
                                {
                                    SPlate.SP_StopPreview(lPlayHandle);
                                    lPlayHandle = -1;
                                }

                                lPlayHandle = SPlate.SP_PreviewInfo(ref previewInfo, lenth);

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

             foreach(ClsNVRInfo nvr in Global.nvrList)
                {
                    if (Global.sCurSelectedNvrName == nvr.nvrName)
                    {
                        foreach (ClsVideoChannel video in nvr.videoList)
                        //foreach (ClsVideoChannel video in Global.videoList)
                        {
                            if (Global.nCurSelectedVideoChan == video.channelNo)
                            {
                            for (int i =0;i<video.areaList.Count; i++)
                                {
                                if ((Global.nCurStatus == 0 && (comboArea.Text == "全部" || video.areaList[i].id.ToString() == comboArea.Text.Trim())) ||
                                    Global.nCurStatus == 1 || (Global.nCurStatus == 2 && video.areaList[i].id.ToString() != comboArea.Text.Trim())||
                                    (Global.nCurStatus == 3 && video.areaList[i].id.ToString() == comboMainArea.Text.Trim())||
                                    (Global.nCurStatus == 3 && video.areaList[i].id.ToString() == comboMainArea2.Text.Trim()))

                                  {
                                    int X1 = (int)(video.areaList[i].left * videoBox.Width);
                                        int X2 = (int)(video.areaList[i].right * videoBox.Width);
                                        int Y1 = (int)(video.areaList[i].top * videoBox.Height);
                                        int Y2 = (int)(video.areaList[i].bottom * videoBox.Height);
                                        Graphics g = this.videoBox.CreateGraphics();
                                        g.DrawRectangle(new Pen(Color.Red), X1, Y1, X2 - X1, Y2 - Y1);
                                  }
                                if ((Global.nCurStatus == 3 && video.areaList[i].id.ToString() == comboSubArea.Text.Trim())||
                                    Global.nCurStatus == 3 && video.areaList[i].id.ToString() == comboSubArea2.Text.Trim())
                                {
                                    int X1 = (int)(video.areaList[i].left * videoBox.Width);
                                    int X2 = (int)(video.areaList[i].right * videoBox.Width);
                                    int Y1 = (int)(video.areaList[i].top * videoBox.Height);
                                    int Y2 = (int)(video.areaList[i].bottom * videoBox.Height);
                                    Graphics g = this.videoBox.CreateGraphics();
                                    g.DrawRectangle(new Pen(Color.Blue), X1, Y1, X2 - X1, Y2 - Y1);
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
            GetParamFromDB();
            treeMain.Nodes[0].Nodes.Clear();
            foreach (ClsNVRInfo nvr in Global.nvrList)
            {
                TreeNode nvrTree = new TreeNode(nvr.nvrName);
                treeMain.Nodes[0].Nodes.Add(nvrTree);
            }
            if (Global.nVideoRecogType == 1)
            {
                InitHKGroupBoard();
            }else if (Global.nVideoRecogType == 0)
            {
                group_wentong.Enabled = true;
            }
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
                    videoChan.parentID = nvr.id;
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
            SwitchVideo();
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
            comboNozzleNo.Items.Clear();
            if (comboArea.Text != "全部")
            {
                foreach (ClsNozzle nozz in Global.nozzleList)
                {
                    if (nozz.areaid.ToString() == comboArea.Text)
                    {
                        comboNozzleNo.Items.Add(nozz.nozzleNo.ToString());
                    }
                    else if (nozz.subAreaid.ToString() == comboArea.Text)
                    {
                        comboNozzleNo.Items.Add(nozz.nozzleNo.ToString());
                    }
                }
            }
            
        }

        private void btnAddNozzle_Click(object sender, EventArgs e)
        {
            
            comboMainArea.Items.Clear();
            comboMainArea2.Items.Clear();
            comboSubArea.Items.Clear();
            comboSubArea2.Items.Clear();
            foreach (ClsVideoChannel video in Global.videoList)
            {
                if (video.channelNo == Global.nCurSelectedVideoChan)
                {
                    if (video.areaList.Count < 1)
                    {
                        MessageBox.Show("当前视频通道未添加识别区，请先添加识别区!");
                        return;
                    }
                    comboSubArea.Items.Add("不使用");
                    comboMainArea2.Items.Add("不使用");
                    comboSubArea2.Items.Add("不使用");
                    foreach (ClsRecogArea area in video.areaList)
                    {
                        comboMainArea.Items.Add(area.id.ToString());
                        comboMainArea2.Items.Add(area.id.ToString());
                        comboSubArea.Items.Add(area.id.ToString());
                        comboSubArea2.Items.Add(area.id.ToString());
                    }
                    comboMainArea.SelectedIndex = 0;
                    comboSubArea.SelectedIndex = 0;
                    comboMainArea2.SelectedIndex = 0;
                    comboSubArea2.SelectedIndex = 0;
                }
            }
            comboNozzleNo.Items.Clear();
            this.comboNozzleNo.Items.AddRange(new object[] {"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15",
            "16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32"});
            foreach (ClsNozzle nozz in Global.nozzleList)
            {
                this.comboNozzleNo.Items.Remove(nozz.nozzleNo.ToString());
            }
            Global.nCurStatus = 3;
            SwithFormStat(Global.nCurStatus);

        }


        private void btnDeleteNozzle_Click(object sender, EventArgs e)
        {
            if (DialogResult.Yes == MessageBox.Show("确认删除油枪" + comboNozzleNo.Text.ToString() + "?", "提示", MessageBoxButtons.YesNo))
            {
                string sqlString = "delete from nozzle_area where nozzleNo = " + comboNozzleNo.Text;
                Global.mysqlHelper.ExecuteSql(sqlString);
                sqlString = "delete from nozzle where nozzleno = " + comboNozzleNo.Text;
                Global.mysqlHelper.ExecuteSql(sqlString);
                foreach (ClsNozzle nozz in Global.nozzleList)
                {
                    if (nozz.nozzleNo.ToString() == comboNozzleNo.Text)
                    {
                        Global.nozzleList.Remove(nozz);
                        break;
                    }
                }

            }
        }

        private void btn_reset_Click(object sender, EventArgs e)
        {
            if (DialogResult.Yes == MessageBox.Show("确认删除所有识别区及油枪配置?", "提示", MessageBoxButtons.YesNo))
            {
                string sql = "truncate table nozzle_area ";
                Global.mysqlHelper.ExecuteSql(sql);
                sql = "truncate table nozzle ";
                Global.mysqlHelper.ExecuteSql(sql);
                sql = "truncate table analysisarea";
                Global.mysqlHelper.ExecuteSql(sql);
                MessageBox.Show("重置完毕！");
            }
        }

        private void hk_btnAdd_Click(object sender, EventArgs e)
        {
            if (hk_comboNoz.SelectedIndex < 2)
            {
                if (hk_comboMainVideoChan1.Text != "")
                {
                    int videoChan = int.Parse(hk_comboMainVideoChan1.Text);
                    int vchLane = hk_comboMainVideoArea1.SelectedIndex + 1;
                    int id = HK_FindRecogAreaInVideoChan(videoChan, vchLane);
                    int nozNo = hk_comboNoz.SelectedIndex + 98;  //入口99 出口100
                    if (id > 0)
                    {
                        string sql = "insert into nozzle_area (nozzleNo,areaid,linkmode) values (" + nozNo.ToString()
                            + "," + id.ToString() + ",1)";
                        Global.mysqlHelper.ExecuteSql(sql);
                        FlushDGV_HK();
                        MessageBox.Show("添加出入口成功!");
                    }
                }
                return;
            }
            ClsNozzle nozzle = new ClsNozzle();
            nozzle.nozzleNo = int.Parse(hk_comboNoz.Text);
            nozzle.oilType = hk_comboOilType.SelectedIndex;
            nozzle.areaid = 0;
            nozzle.subAreaid = 0;
            nozzle.id = Global.mysqlHelper.ExecuteSql(nozzle.getInsertString());
            Global.nozzleList.Add(nozzle);
            StringBuilder sbSql = new StringBuilder();
            sbSql.Append("insert into nozzle_area (nozzleNo,areaid,linkmode) values");
            
            if (hk_comboMainVideoChan1.Text != "")
            {
                int videoChan = int.Parse(hk_comboMainVideoChan1.Text);
                int vchLane = hk_comboMainVideoArea1.SelectedIndex + 1;
                int id = HK_FindRecogAreaInVideoChan(videoChan, vchLane);
                if (id > 0)
                {
                    sbSql.Append(" ( " + nozzle.nozzleNo.ToString() + "," + id.ToString() + ",1)");
                }
            }
            

            if (hk_comboMainVideoChan2.SelectedIndex != 0)
            {
                int videoChan = int.Parse(hk_comboMainVideoChan2.Text);
                int vchLane = hk_comboMainVideoArea2.SelectedIndex+1;
                int id = HK_FindRecogAreaInVideoChan(videoChan, vchLane);
                if (id > 0)
                {
                    sbSql.Append(" ,( " + nozzle.nozzleNo.ToString() + "," + id.ToString() + ",1)");
                }
            }

            if (hk_comboSubVideoChan1.SelectedIndex != 0)
            {
                int videoChan = int.Parse(hk_comboSubVideoChan1.Text);
                int vchLane = hk_comboSubVideoArea1.SelectedIndex + 1;
                int id = HK_FindRecogAreaInVideoChan(videoChan, vchLane);
                if (id > 0)
                {
                    sbSql.Append(" ,( " + nozzle.nozzleNo.ToString() + "," + id.ToString() + ",2)");
                }
            }
            if (hk_comboSubVideoChan2.SelectedIndex != 0)
            {
                int videoChan = int.Parse(hk_comboSubVideoChan2.Text);
                int vchLane = hk_comboSubVideoArea2.SelectedIndex + 1;
                int id = HK_FindRecogAreaInVideoChan(videoChan, vchLane);
                if (id > 0)
                {
                    sbSql.Append(" ,( " + nozzle.nozzleNo.ToString() + "," + id.ToString() + ",2)");
                }
            }

            Global.mysqlHelper.ExecuteSql(sbSql.ToString());

            FlushDGV_HK();
            hk_btnAdd.Enabled = false;
            hk_btnDelete.Enabled = true;
            Global.LogServer.Add(new LogInfo("ParamSet-Debug", sbSql.ToString(), (int)EnumLogLevel.DEBUG));
            MessageBox.Show("油枪添加成功!");
        }

        private void hk_btnClear_Click(object sender, EventArgs e)
        {

        }

        private void hk_btnReset_Click(object sender, EventArgs e)
        {
            if (DialogResult.OK == MessageBox.Show("确认重置所有匹配信息？","提示",MessageBoxButtons.OKCancel))
            {
                Global.mysqlHelper.ExecuteSql("truncate table nozzle_area");
                Global.mysqlHelper.ExecuteSql("truncate table analysisarea");
                Global.mysqlHelper.ExecuteSql("truncate table nozzle");
                GetParamFromDB();
                FlushDGV_HK();

            } 
        }

        private void hk_comboMainVideoChan1_SelectedIndexChanged(object sender, EventArgs e)
        {
            
        }

        private void hk_comboMainVideoChan2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (hk_comboMainVideoChan2.SelectedIndex == 0)
            {
                hk_comboMainVideoArea2.Enabled = false;
            }
            else
            {
                hk_comboMainVideoArea2.Enabled = true;
            }
        }

        private void hk_comboSubVideoChan1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (hk_comboSubVideoChan1.SelectedIndex == 0)
            {
                hk_comboSubVideoArea1.Enabled = false;
            }
            else
            {
                hk_comboSubVideoArea1.Enabled = true;
            }
        }

        private void hk_comboSubVideoChan2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (hk_comboSubVideoChan2.SelectedIndex == 0)
            {
                hk_comboSubVideoArea2.Enabled = false;
            }
            else
            {
                hk_comboSubVideoArea2.Enabled = true;
            }
        }

        private void hk_comboNoz_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (hk_comboNoz.SelectedIndex < 2)
            {
                hk_btnDelete.Enabled = true;
                hk_btnAdd.Enabled = true;
                return;
            }
            int nozNo = int.Parse(hk_comboNoz.Text);
            bool assigned = false;
            for (int i=0;i<Global.nozzleList.Count;i++)
            {
                if (Global.nozzleList[i].nozzleNo == nozNo)
                {
                    assigned = true;
                }
            }
            
            if (assigned)
            {
                hk_btnDelete.Enabled = true;
                hk_btnAdd.Enabled = false;
            }
            else
            {
                hk_btnDelete.Enabled = false;
                hk_btnAdd.Enabled = true;
            }
            
        }

        private void hk_btnDelete_Click(object sender, EventArgs e)
        {
            int nozNo = 0;
            if (hk_comboNoz.SelectedIndex < 2) //出入口
                nozNo = hk_comboNoz.SelectedIndex + 98;
            else
                nozNo = int.Parse(hk_comboNoz.Text);
            foreach (ClsNozzle noz in Global.nozzleList)
            {
                if (noz.nozzleNo == nozNo)
                {
                    Global.nozzleList.Remove(noz);
                    break;
                }
            }

            Global.mysqlHelper.ExecuteSql("delete from nozzle_area where nozzleNo = " + nozNo.ToString());
            Global.mysqlHelper.ExecuteSql("delete from nozzle where nozzleNo = " + nozNo.ToString());
            FlushDGV_HK();
            hk_btnAdd.Enabled = true;
            hk_btnDelete.Enabled = false;
            MessageBox.Show("删除成功！");
            
        }

        private void textDBIP_TextChanged(object sender, EventArgs e)
        {

        }

        private void contextTreeAdd_Opening(object sender, CancelEventArgs e)
        {

        }

        private void btn_test_Click(object sender, EventArgs e)
        {
            timer1.Enabled = true;
//             for(int i = 1;i<563;i++)
//             {
//                 string sql =
//                 "INSERT into pos(station_code, material_code, price, endtime, pump_sn, pay_type) select '" +
//                i.ToString() + "',material_code,price,endtime,pump_sn,pay_type from pos2";
//                 sql = "INSERT into storage(station_code,oiltank_sn,volume,picktime,oil_name) select '" +
//                i.ToString() + "',oiltank_sn,volume,picktime,oil_name from storage_bak";
//                 Global.mysqlHelper.ExecuteSql(sql);
//             }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            DateTime dt = DateTime.Now;
            int sec = 3600 * dt.Hour + 60 * dt.Minute + dt.Second;
            double chunqiang = sec * 0.071;
            int renshu = (int)(sec * 1.8);
            double feiyou = 0.0031 * sec;
            string sql = "update ynss.daping_title set value = " + chunqiang.ToString()+" where title = '当日纯枪销量'";
            Global.mysqlHelper.ExecuteSql(sql);
            sql = "update ynss.daping_title set value = " + renshu.ToString() + " where title = '当日提枪次数'";
            Global.mysqlHelper.ExecuteSql(sql);
            sql = "update ynss.daping_title set value = " + feiyou.ToString() + " where title = '当日非油收入'";
            Global.mysqlHelper.ExecuteSql(sql);
        }
    }
}
