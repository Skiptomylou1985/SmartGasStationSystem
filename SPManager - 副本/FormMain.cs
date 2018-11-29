using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace SPManager
{
    public partial class FormMain : Form
    {
        //TH_RECT th_RECT = new TH_RECT();
        //TH_PlateResult th_PlateResult = new TH_PlateResult();
        //NET_DVR_PREVIEWINFO previewInfo = new NET_DVR_PREVIEWINFO();
        private bool toExit = false;
        private DateTime lastUpdateTime = DateTime.Now;
        int gcCount = 0;
        int statusCount = 0;
        private bool moves = true;
        private Point pt;
        private ToolTip tip = new ToolTip();
        public FormMain()
        {
            InitializeComponent();
        }
        

        private void timer1_Tick(object sender, EventArgs e)
        {

            MEMORY_INFO MemInfo;
            MemInfo = new MEMORY_INFO();
            SystemUnit.GlobalMemoryStatus(ref MemInfo);
            toolRAM.Text = MemInfo.dwMemoryLoad.ToString() + "%";
        }
        
        private void FormMain_Load(object sender, EventArgs e)
        {
            startProtectProcess();//启动保护进程
            lastMessageTime = DateTime.Now;
            int ret = Init();
            InitFormInfo();
            if (ret == 0)
            {
                SPlate.SP_BeginRecog();
                ShowNozzleCarList();
                ShowAreaCarList();
                return;
            }
            if ((ret & 0x01) == 0x01)
            {
                MessageBox.Show("日志启动失败");
            }
            if ((ret & 0x02) == 0x02)
            {
                MessageBox.Show("数据库连接失败");
            }
            if ((ret & 0x04) == 0x04)
            {
                MessageBox.Show("参数初始化失败");
            }
            if ((ret & 0x08) == 0x08)
            {
                MessageBox.Show("算法初始化失败");
            }
            if ((ret & 0x10) == 0x10)
            {
                MessageBox.Show("设备初始化失败");
            }
            if ((ret & 0x20) == 0x20)
            {
                MessageBox.Show("网络服务初始化失败");
            }
            
        }

        private void notifyIconMain_DoubleClick(object sender, EventArgs e)
        {
            
            this.Visible = true;
            this.WindowState = FormWindowState.Normal;
            this.ShowInTaskbar = true;//使Form不在任务栏上显示
        }

       

        private void btnQuit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void btnCloseMain_Click(object sender, EventArgs e)
        {

        }


        private void FormMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            ExitApp();
            //SPlate.SP_Close();
            //if(Global.LogServer != null)
            //Global.LogServer.Stop();
        }
    

        private void btnChangeLogLevel_Click(object sender, EventArgs e)
        {
            Global.nLogLevel = comboLogLevel.SelectedIndex + 1;
            SPlate.SP_SetLogLevel(comboLogLevel.SelectedIndex + 1);
        }

       

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!this.toExit)
            {
                this.Visible = false;
                e.Cancel = true;
                return;
            }
        }

        private void toolStripMenuItemExit_Click(object sender, EventArgs e)
        {
            
            if (DialogResult.Yes == (MessageBox.Show("确认退出程序？", "提示", MessageBoxButtons.YesNo)))
            {
                this.toExit = true;
                this.Close();
                
            }
        }

        private void notifyIconMain_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                this.contextMenuExit.Show(Cursor.Position);
            }
        }

        private void notifyIconMain_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.Visible = !this.Visible;
        }

        private void timerServiceStaus_Tick(object sender, EventArgs e)
        {
            this.ShowMemoryInfo();
            this.ShowMatchRatio();
            SystemUnit.PostMessage(SystemUnit.HWND_BROADCAST, (int)WM_HEARTBEAT, 0, 0);
            gcCount++;
            if (gcCount > 60)
            {
                gcCount = 0;
                GC.Collect();
            }
            statusCount++;
             if (statusCount > 3)
            {
                statusCount = 0;
                SendStatusToRemote();
            }
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            string appPath = Application.StartupPath;
            Process proc = Process.Start(appPath+Global.updateAppName);
            if (proc != null)
            {
                ExitApp();
            }
        }

       // private int bas = 0;
        private void btnShowData_Click(object sender, EventArgs e)
        {
            FormSearchData searchData = new FormSearchData();
            searchData.Show();
//             for (int i=0;i<1000;i++)
//             {
//                 bas++;
//                 showRTBInfo("显示第" + bas.ToString() + "行测试数据");
//             }
        }

        int hourcount = 0;
        private void timerDataProc_Tick(object sender, EventArgs e)
        {
            hourcount++;
            if (hourcount > 60)
            {
                hourcount = 0;
                //QueryHourDataFromDB();
            }
            
            if (Global.bShowStationBoard)
            {
                FlushStationBoardRunControls();
            }
        }

        private void btnSwitch_Click(object sender, EventArgs e)
        {
            SPlate.SP_TestAPI();
        }

        private void startProtectProcess()
        {
            ProcessStartInfo psi = new ProcessStartInfo();
            if (File.Exists(Application.StartupPath + "//SPMonitor.exe"))
            {
                psi.FileName = Application.StartupPath + "//SPMonitor.exe";
                psi.UseShellExecute = false;
                psi.CreateNoWindow = true;
                Process.Start(psi);
            }
           
        }
        private void btnTest_Click(object sender, EventArgs e)
        {
            SetRealtimeDGV(dataGridRealtime);

        }

        private void btnOpenMain_Click(object sender, EventArgs e)
        {

        }

        private void statusSystem_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void btnQuery_Click(object sender, EventArgs e)
        {
            string columns = "id,carnumber,nozzleno,oiltype,arrivetime,begintime,leavetime,carlogo,carcolor,picpath";
            dataGridSearch.DataSource = QueryData(columns, true);
            SetSearchDGV(dataGridSearch);
        }

        private void dataGridCar_SelectionChanged(object sender, EventArgs e)
        {
            int cur = 0;
            if (dataGridSearch.CurrentCell != null)    //过车时刷新，当前单元格为空，选中首行
                cur = dataGridSearch.CurrentCell.RowIndex;
            else
                return;
            try
            {
                lblLicense.Text = dataGridSearch.Rows[cur].Cells["carnumber"].Value.ToString();
                lblNozzleNo.Text = dataGridSearch.Rows[cur].Cells["nozzleno"].Value.ToString();
                lblOilType.Text = dataGridSearch.Rows[cur].Cells["oiltype"].Value.ToString();
                lblArriveTime.Text = dataGridSearch.Rows[cur].Cells["arrivetime"].Value.ToString();
                lblLeaveTime.Text = dataGridSearch.Rows[cur].Cells["leavetime"].Value.ToString();
                lblCarLogo.Text = dataGridSearch.Rows[cur].Cells["carlogo"].Value.ToString();
                string picPath = dataGridSearch.Rows[cur].Cells["picpath"].Value.ToString();
                
//                 if (File.Exists(picPath))
//                 {
//                 }
//                 pictureBoxArrive.Image = Image.FromFile(picPath + ".jpg");

            }
            catch (System.Exception ex)
            {

            }
        }

        private void btnChangeLogLevel_Click_1(object sender, EventArgs e)
        {
            if (btnChangeLogLevel.Text == "修改")
            {
                comboLogLevel.Visible = true;
                comboLogLevel.SelectedIndex = Global.nLogLevel - 1;
                lblLogLevel.Visible = false;
                btnChangeLogLevel.Text = "确定";
            }else
            {
                comboLogLevel.Visible = false;
                Global.nLogLevel = comboLogLevel.SelectedIndex  + 1;
                lblLogLevel.Visible = true;
                btnChangeLogLevel.Text = "修改";
                Global.mysqlHelper.ExecuteSql("update param set paramValue = '" + Global.nLogLevel.ToString() + "' where paramName = 'loglevel'");
                lblLogLevel.Text = comboLogLevel.Text;
            }
           
        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog folder = new FolderBrowserDialog();
            if (DialogResult.OK == folder.ShowDialog())
            {
                String path = folder.SelectedPath + "\\车辆检测数据" + DateTime.Now.ToString("yyyyMMddHHmmss") + ".xlsx";
                string columns = "id,carnumber,nozzleno,arrivetime,begintime,leavetime,carlogo,subcarlogo";
                DataTable dt =QueryData(columns, false);
                dt.Columns.Add("carbrand", typeof(string));
                for (int i = 0; i < dt.Rows.Count; i++)
                {
                    string carlogoKey = dt.Rows[i]["carlogo"].ToString() + "-" + dt.Rows[i]["subcarlogo"].ToString();
                    string carlogo = "未知";
                    if (Global.carLogoHashtable.Contains(carlogoKey))
                    {
                        carlogo = (string)Global.carLogoHashtable[carlogoKey];
                    }
                    dt.Rows[i]["carbrand"] = carlogo;
                }

                if (SystemUnit.ExportDataToExcel(dt, path))
                    MessageBox.Show("导出数据成功");
                else
                    MessageBox.Show("导出数据失败");

            }
        }

       

       

        private void Island1_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island1_MouseHover(object sender, EventArgs e)
        {
            //Island1.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island1, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island1_MouseLeave(object sender, EventArgs e)
        {
            //Island1.BackColor = Color.Transparent;
            tip.ShowAlways = false;
        }

        private void Island1_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Island1, e);
        }

        private void Island1_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Island1_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Island1, "island","", false);
        }



        private void Island2_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Island2, "island", "", false);
        }

        private void Island2_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island2_MouseHover(object sender, EventArgs e)
        {
           // Island2.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island2, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island2_MouseLeave(object sender, EventArgs e)
        {
            //Island2.BackColor = Color.Transparent;
            tip.ShowAlways = false;
        }

        private void Island2_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Island2, e);

        }

        private void Island2_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Island3_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Island3, "island", "", false);
        }

        private void Island3_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island3_MouseHover(object sender, EventArgs e)
        {
            //Island3.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island3, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island3_MouseLeave(object sender, EventArgs e)
        {
            //Island3.BackColor = Color.Transparent;
            tip.ShowAlways = false;
        }

        private void Island3_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Island3, e);
        }

        private void Island3_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Island4_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Island4, "island", "", false);
        }

        private void Island4_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island4_MouseHover(object sender, EventArgs e)
        {
            //Island4.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island4, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island4_MouseLeave(object sender, EventArgs e)
        {
            //Island4.BackColor = Color.Transparent;
            tip.ShowAlways = false;
        }

        private void Island4_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Island4, e);
        }

        private void Island4_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Island5_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Island5, "island", "", false);
        }

        private void Island5_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island5_MouseHover(object sender, EventArgs e)
        {
            //Island5.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island5, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island5_MouseLeave(object sender, EventArgs e)
        {
            //Island5.BackColor = Color.Transparent;
            tip.ShowAlways = false;
        }

        private void Island5_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Island5, e);
        }

        private void Island5_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Island6_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Island6, "island", "", false);
        }

        private void Island6_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island6_MouseHover(object sender, EventArgs e)
        {
            //Island6.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island6, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island6_MouseLeave(object sender, EventArgs e)
        {
            //Island6.BackColor = Color.Transparent;
            tip.ShowAlways = false;
        }

        private void Island6_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Island6, e);
        }

        private void Island6_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void btnTest_Click_1(object sender, EventArgs e)
        {
            //QueryHourDataFromDB();
            //FlushStatisticsBoard();
            //StationBoardReset();
            // InitBoardControls();

            // this.StationBoardHorizon.Enabled = false;
        }

        private void btnSetStaionBoard_Click(object sender, EventArgs e)
        {
            
            if (btnSetStaionBoard.Text == "设置站点")
            {
                FormPassword fp = new FormPassword();
                DialogResult dr = fp.ShowDialog();
                if (dr == DialogResult.OK && fp.Result)
                {
                    StationBoard.Visible = true;
                    comboStationDirection.Visible = true;
                    StationBoardHorizon.Visible = true;
                    StationBoardVertical.Visible = true;
                    comboStationDirection.SelectedIndex = Global.nStationBoardDirection;
                    checkShowStationBoard.Visible = true;
                    checkShowStationBoard.Checked = Global.bShowStationBoard;
                    Global.bStationBoardInSet = true;
                    btnSetStaionBoard.Text = "保存设置";
                    btnReset.Visible = true;
                }
               
            } 
            else
            {
                btnReset.Visible = false;
                comboStationDirection.Visible = false;
                checkShowStationBoard.Visible = false;
                Global.bShowStationBoard = checkShowStationBoard.Checked  ;
                StationBoard.Visible = Global.bShowStationBoard;
                Global.bStationBoardInSet = false;
                Global.nStationBoardDirection = comboStationDirection.SelectedIndex;
                UpdateStationBoardParamToDB();
                btnSetStaionBoard.Text = "设置站点";
            }
            FlushStationBoard();
        }

        private void I1_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I1_Noz1);
        }

        private void I1_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I1_Noz2);
        }

        private void I1_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I1_Noz3);
        }

        private void I1_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I1_Noz4);
        }

        private void I1_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I1_Noz5);
        }

        private void I1_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I1_Noz6);
        }

        private void I2_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I2_Noz1);
        }

        private void I2_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I2_Noz2);
        }

        private void I2_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I2_Noz3);
        }

        private void I2_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I2_Noz4);
        }

        private void I2_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I2_Noz5);
        }

        private void I2_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I2_Noz6);
        }

        private void I3_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I3_Noz1);
        }

        private void I3_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I3_Noz2);
        }

        private void I3_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I3_Noz3);
        }

        private void I3_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I3_Noz4);
        }

        private void I3_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I3_Noz5);
        }

        private void I3_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I3_Noz6);
        }

        private void I4_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I4_Noz1);
        }

        private void I4_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I4_Noz2);
        }

        private void I4_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I4_Noz3);
        }

        private void I4_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I4_Noz4);
        }

        private void I4_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I4_Noz5);
        }

        private void I4_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I4_Noz6);
        }

        private void I5_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I5_Noz1);
        }

        private void I5_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I5_Noz2);
        }

        private void I5_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I5_Noz3);
        }

        private void I5_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I5_Noz4);
        }

        private void I5_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I5_Noz5);
        }

        private void I5_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I5_Noz6);
        }

        private void I6_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I6_Noz1);
        }

        private void I6_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I6_Noz2);
        }

        private void I6_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I6_Noz3);
        }

        private void I6_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I6_Noz4);
        }

        private void I6_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I6_Noz5);
        }

        private void I6_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(I6_Noz6);
        }

        private void btnEntrance_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void btnEntrance_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(btnEntrance, e);
        }

        private void btnEntrance_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void btnStore_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void btnStore_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(btnStore, e);
        }
        private void btnStore_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void btnExit_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void btnExit_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(btnExit, e);
        }

        private void btnExit_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void I1_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I1_Area1);
        }

        private void I1_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I1_Area2);
        }

        private void I1_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I1_Area3);
        }

        private void I1_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I1_Area4);

        }

        private void I2_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I2_Area1);
        }

        private void I2_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I2_Area2);
        }

        private void I2_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I2_Area3);
        }

        private void I2_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I2_Area4);
        }

        private void I3_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I3_Area1);
        }

        private void I3_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I3_Area2);
        }

        private void I3_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I3_Area3);
        }

        private void I3_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I3_Area4);
        }

        private void I4_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I4_Area1);
        }

        private void I4_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I4_Area2);
        }

        private void I4_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I4_Area3);
        }

        private void I4_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I4_Area4);
        }

        private void I5_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I5_Area1);
        }

        private void I5_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I5_Area2);
        }

        private void I5_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I5_Area3);
        }

        private void I5_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I5_Area4);
        }

        private void I6_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I6_Area1);
        }

        private void I6_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I6_Area2);
        }

        private void I6_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I6_Area3);
        }

        private void I6_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(I6_Area4);
        }

        private void comboStationDirection_SelectedIndexChanged(object sender, EventArgs e)
        {
            Global.nStationBoardDirection = comboStationDirection.SelectedIndex ;
            GetSatationBoardParamFromDB();
            FlushStationBoard();
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            StationBoardReset();
        }

        private void Ver_Island1_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Ver_Island1, "island", "", false);
        }

        private void Ver_Island2_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Ver_Island2, "island", "", false);
        }

        private void Ver_Island3_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Ver_Island3, "island", "", false);
        }

        private void Ver_Island4_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Ver_Island4, "island", "", false);
        }

        private void Ver_Island5_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Ver_Island5, "island", "", false);
        }

        private void Ver_Island6_DoubleClick(object sender, EventArgs e)
        {
            SetSingleControlAttr(Ver_Island6, "island", "", false);
        }

        private void Ver_Island1_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Ver_Island2_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Ver_Island3_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Ver_Island4_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Ver_Island5_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Ver_Island6_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Ver_Island1_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Ver_Island1, e);
        }

        private void Ver_Island2_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Ver_Island2, e);
        }

        private void Ver_Island3_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Ver_Island3, e);
        }

        private void Ver_Island4_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Ver_Island4, e);
        }

        private void Ver_Island5_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Ver_Island5, e);
        }

        private void Ver_Island6_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Ver_Island6, e);
        }

        private void Ver_Island1_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Ver_Island2_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Ver_Island3_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Ver_Island4_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Ver_Island5_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Ver_Island6_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Ver_I1_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I1_Area1);
        }

        private void Ver_I1_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I1_Area2);
        }

        private void Ver_I1_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I1_Area3);
        }

        private void Ver_I1_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I1_Area4);
        }

        private void Ver_I2_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I2_Area1);
        }

        private void Ver_I2_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I2_Area2);
        }

        private void Ver_I2_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I2_Area3);
        }

        private void Ver_I2_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I2_Area4);
        }

        private void Ver_I3_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I3_Area1);
        }

        private void Ver_I3_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I3_Area2);
        }

        private void Ver_I3_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I3_Area3);
        }

        private void Ver_I3_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I3_Area4);
        }

        private void Ver_I4_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I4_Area1);
        }

        private void Ver_I4_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I4_Area2);
        }

        private void Ver_I4_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I4_Area3);
        }

        private void Ver_I4_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I4_Area4);
        }

        private void Ver_I5_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I5_Area1);
        }

        private void Ver_I5_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I5_Area2);
        }

        private void Ver_I5_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I5_Area3);
        }

        private void Ver_I5_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I5_Area4);
        }

        private void Ver_I6_Area1_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I6_Area1);
        }

        private void Ver_I6_Area2_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I6_Area2);
        }

        private void Ver_I6_Area3_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I6_Area3);
        }

        private void Ver_I6_Area4_Click(object sender, EventArgs e)
        {
            SetAreaLinkControl(Ver_I6_Area4);
        }

        private void Ver_I1_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I1_Noz1);
        }

        private void Ver_I1_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I1_Noz2);
        }

        private void Ver_I1_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I1_Noz3);
        }

        private void Ver_I1_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I1_Noz4);
        }

        private void Ver_I1_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I1_Noz5);
        }

        private void Ver_I1_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I1_Noz6);
        }

        private void Ver_I2_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I2_Noz1);
        }

        private void Ver_I2_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I2_Noz2);
        }

        private void Ver_I2_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I2_Noz3);
        }

        private void Ver_I2_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I2_Noz4);
        }

        private void Ver_I2_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I2_Noz5);
        }

        private void Ver_I2_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I2_Noz6);
        }

        private void Ver_I3_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I3_Noz1);
        }

        private void Ver_I3_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I3_Noz2);
        }

        private void Ver_I3_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I3_Noz3);
        }

        private void Ver_I3_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I3_Noz4);
        }

        private void Ver_I3_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I3_Noz5);
        }

        private void Ver_I3_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I3_Noz6);
        }

        private void Ver_I4_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I4_Noz1);
        }

        private void Ver_I4_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I4_Noz2);
        }

        private void Ver_I4_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I4_Noz3);
        }

        private void Ver_I4_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I4_Noz4);
        }

        private void Ver_I4_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I4_Noz5);
        }

        private void Ver_I4_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I4_Noz6);
        }

        private void Ver_I5_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I5_Noz1);
        }

        private void Ver_I5_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I5_Noz2);
        }

        private void Ver_I5_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I5_Noz3);
        }

        private void Ver_I5_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I5_Noz4);
        }

        private void Ver_I5_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I5_Noz5);
        }

        private void Ver_I5_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I5_Noz6);
        }

        private void Ver_I6_Noz1_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I6_Noz1);
        }

        private void Ver_I6_Noz2_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I6_Noz2);
        }

        private void Ver_I6_Noz3_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I6_Noz3);
        }

        private void Ver_I6_Noz4_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I6_Noz4);
        }

        private void Ver_I6_Noz5_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I6_Noz5);
        }

        private void Ver_I6_Noz6_Click(object sender, EventArgs e)
        {
            SetNozzleLinkControl(Ver_I6_Noz6);
        }

        private void Ver_btnEntrance_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Ver_btnStore_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Ver_btnExit_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Ver_btnEntrance_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Ver_btnEntrance, e);
        }
        private void Ver_btnStore_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Ver_btnStore, e);
        }

        private void Ver_btnExit_MouseMove(object sender, MouseEventArgs e)
        {
            ControlMove(Ver_btnExit, e);
        }
        private void Ver_btnStore_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Ver_btnEntrance_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void Ver_btnExit_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void checkShowStationBoard_CheckedChanged(object sender, EventArgs e)
        {
            comboStationDirection.Enabled = checkShowStationBoard.Checked;
        }

        private void timerClearCarlist_Tick(object sender, EventArgs e)
        {
            foreach(ClsCarArrive car in Global.listCarArrive)
            {
                if (DateTime.Now.CompareTo(car.arriveTime.AddSeconds(600)) > 0)
                {
                    lock(Global.lockObj)
                    {

                    }
                    SendCallbackInfo(car.carInfo, 2);
                    ShowRTBInfo("获取入口车牌：" + car.plate + " 车辆品牌:" + car.carInfo.nCarLogo.ToString()
                        + " 车辆子品牌:" + car.carInfo.nSubCarLogo.ToString());

                    lock (Global.lockObj)
                    {
                        Global.listCarArrive.Remove(car);
                    }
                    return;
                    
                }
            }
        }
    }
}
