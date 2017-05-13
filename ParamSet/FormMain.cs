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
        public struDraw[] struDrawInfo;
        public int nCurDrawIndex;
        public FormMain()
        {
            InitializeComponent();
        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            
            Global.LogServer = new Log(Global.nLogLevel);
            Global.LogServer.Run();
            nCurDrawIndex = 0;
            struDrawInfo = new struDraw[4];
            for (int i=0;i<4;i++)
            {
                struDrawInfo[i].g = this.videoBox.CreateGraphics();
                struDrawInfo[i].start = new Point();
                struDrawInfo[i].end = new Point();
                struDrawInfo[i].bShowDraw = false;
                struDrawInfo[i].bReDraw = false;
            }
            comboDBType.SelectedIndex = 0;
            treeMain.Nodes.Add("设备");
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {

            try
            {
                DBInfo info = new DBInfo();
                info.type = comboDBType.Text.ToString();
                info.ip = textDBIP.Text.ToString();
                info.dbname = textDBName.Text.ToString() ;
                info.username = textDBAdmin.Text.ToString();
                info.password = textDBPwd.Text.ToString();
                info.port = 3306;
                Global.LogServer.Add(new LogInfo("Debug", "main->InitDatabase param value" +
                   Global.iniPath + " " + info.type + " " + info.ip + " " + info.dbname + " " + info.username + " " + info.password, (int)EnumLogLevel.DEBUG));
                Global.mysqlHelper = new MysqlHelper(info);
                GetMainParam();
                GetNVRList();
                
              
                
            }
            catch (System.Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "Main:InitDatabase 初始化数据库失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                MessageBox.Show("数据库连接失败！");
            }


        }


        private void treeDevice_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (e.Button == MouseButtons.Right && e.Node.Text == treeMain.Nodes[0].Text)
            {
                Point pos = new Point(e.Node.Bounds.X + e.Node.Bounds.Width, e.Node.Bounds.Y + e.Node.Bounds.Height / 2);
                this.contextTreeMenu.Show(this.treeMain, pos);
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
            if (struDrawInfo[nCurDrawIndex].bReDraw)
            {
                struDrawInfo[nCurDrawIndex].start.X = e.X;
                struDrawInfo[nCurDrawIndex].start.Y = e.Y;
                struDrawInfo[nCurDrawIndex].end.X = e.X;
                struDrawInfo[nCurDrawIndex].end.Y = e.Y;
            }
           
        }

        private void videoBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (struDrawInfo[nCurDrawIndex].bReDraw)
            {
                struDrawInfo[nCurDrawIndex].end.X = e.X;
                struDrawInfo[nCurDrawIndex].end.Y = e.Y;
            }

        }

        private void videoBox_MouseUp(object sender, MouseEventArgs e)
        {
            struDrawInfo[nCurDrawIndex].bReDraw = false;
        }

        private void FormMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            Global.LogServer.Stop();
        }

        private void treeMain_DoubleClick(object sender, EventArgs e)
        {
            TreeNode node = treeMain.SelectedNode;
            if (node.Nodes.Count > 0)
            {
                return;
            }
            foreach (ClsNVRInfo nvr in Global.nvrInfoList)
            {
                if (node.Text == nvr.nvrName)
                {
                    if (0 == SPlate.SP_InitNVR(nvr.ip, nvr.port, nvr.loginName, nvr.password))
                    {
                        Global.LogServer.Add(new LogInfo("paramset", "SP_InitNVR true", (int)EnumLogLevel.DEBUG));
                        IntPtr ip = Marshal.AllocHGlobal(Marshal.SizeOf(nvr.config));
                        int lenth = 0;
                        SPlate.SP_GetNvrCfg(ip, ref lenth);
                        nvr.config = (NET_DVR_IPPARACFG_V40)Marshal.PtrToStructure(ip, typeof(NET_DVR_IPPARACFG_V40));
                        
                        for (int i=0;i<nvr.config.dwDChanNum;i++)
                        {
                            Global.LogServer.Add(new LogInfo("paramset", "dwDChanNum:"+i.ToString(), (int)EnumLogLevel.DEBUG));
                            if (nvr.config.struIPDevInfo[i].byEnable == 1)
                            {
                                ClsVideoChannel videoChan = new ClsVideoChannel();
                                videoChan.ip = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].struIP.sIpV4);
                                videoChan.channelNo = i;
                                videoChan.loginName = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].sUserName);
                                videoChan.password = System.Text.Encoding.Default.GetString(nvr.config.struIPDevInfo[i].sPassword);
                                videoChan.port = nvr.config.struIPDevInfo[i].wDVRPort;
                                videoChan.streamType = nvr.config.struStreamMode[i].byGetStreamType;
                                nvr.videoList.Add(videoChan);
                                TreeNode cNode = new TreeNode();
                                cNode.Text = "Video" + i.ToString();
                                node.Nodes.Add(cNode);
                                Global.LogServer.Add(new LogInfo("paramset", "struIPDevInfo.byEnable true", (int)EnumLogLevel.DEBUG));
                                
                            }


                        }
                    }
                    break;
                }
                else
                {
                    foreach (ClsVideoChannel video in nvr.videoList)
                    {
                        Global.LogServer.Add(new LogInfo("paramset", "Video" + video.channelNo.ToString(), (int)EnumLogLevel.DEBUG));
                        if (node.Text == "Video"+video.channelNo.ToString())
                        {
                            NET_DVR_PREVIEWINFO previewInfo = new NET_DVR_PREVIEWINFO();
                            previewInfo.hPlayWnd = videoBox.Handle;//预览窗口
                            previewInfo.lChannel = nvr.config.dwStartDChan+video.channelNo;
                            previewInfo.dwStreamType = 0;//码流类型：0-主码流，1-子码流，2-码流3，3-码流4，以此类推
                            previewInfo.dwLinkMode = 0;//连接方式：0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP 
                            previewInfo.bBlocked = false; //0- 非阻塞取流，1- 阻塞取流
                            previewInfo.dwDisplayBufNum = 15;
                            int lenth = Marshal.SizeOf(previewInfo);
                            SPlate.SP_PreviewInfo(ref previewInfo, lenth).ToString();
                            break;
                        }
                    }
                }
            }
        }

        private void timerCurve_Tick(object sender, EventArgs e)
        {
                int X1, X2, Y1, Y2;
                for (int i=0;i<4;i++)
                {
                    if (struDrawInfo[i].bShowDraw)
                    {
                        X1 = struDrawInfo[i].start.X;
                        X2 = struDrawInfo[i].end.X;
                        Y1 = struDrawInfo[i].start.Y;
                        Y2 = struDrawInfo[i].end.Y;
                    struDrawInfo[i].g.DrawRectangle(new Pen(Color.Red), X1, Y1, X2 - X1, Y2 - Y1);
                    }
                }
        }

        private void addDevice_Click(object sender, EventArgs e)
        {
            FormNVR formnvr = new FormNVR();
            formnvr.ShowDialog();
        }

        private void deleteDevice_Click(object sender, EventArgs e)
        {

        }
    }
}
