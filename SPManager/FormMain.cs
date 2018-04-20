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
            //TODO 临时返回
            //return;

            startProtectProcess();//启动保护进程
            lastMessageTime = DateTime.Now;
            addListViewHead();
            Global.softVersion = INIUnit.GetINIValue(Application.StartupPath+"//version.ini", "main", "version");
            this.Text = "加油站智能信息管理系统SPManager " + Global.softVersion;
            int ret = Init();
            setRealtimeDGV(dataGridRealtime);
            toolStationName.Text = "站点名称:"+Global.stationInfo.stationName+"   ";
            comboLogLevel.Visible = false;
            if (ret == 0)
            {
                SPlate.SP_BeginRecog();
                showCarList();
                //timerDataProc.Enabled = true;
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

        private void btnInit_Click(object sender, EventArgs e)
        {
            int ret = Init();
            if (ret == 0)
            {
                SPlate.SP_BeginRecog();
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
            this.showMemoryInfo();
            this.showMatchRatio();
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
                sendStatusToRemote();
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
        
        private void timerDataProc_Tick(object sender, EventArgs e)
        {

            showCarList();
            //showCarListTest();
            DateTime dt = DateTime.Now;
        }

        private void btnSwitch_Click(object sender, EventArgs e)
        {
            SPlate.SP_TestAPI();
        }

        private void startProtectProcess()
        {
            ProcessStartInfo psi = new ProcessStartInfo();
            psi.FileName = Application.StartupPath + "//Kill.exe";
            psi.UseShellExecute = false;
            psi.CreateNoWindow = true;
            Process.Start(psi);
        }
        private void btnTest_Click(object sender, EventArgs e)
        {
            setRealtimeDGV(dataGridRealtime);

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
            dataGridSearch.DataSource = queryData(columns, true);
            setSearchDGV(dataGridSearch);
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
                DataTable dt = queryData(columns, false);
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
            Island1.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island1, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island1_MouseLeave(object sender, EventArgs e)
        {
            Island1.BackColor = Color.Transparent;
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
            FormSet set = new FormSet("Island",false);
            DialogResult dr = set.ShowDialog();
            if (dr == DialogResult.OK )
            {
                if (!set.bShow)
                {
                    Island1.Visible = false;
                }
            } 
        }



        private void Island2_DoubleClick(object sender, EventArgs e)
        {
           
        }

        private void Island2_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island2_MouseHover(object sender, EventArgs e)
        {
            Island2.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island2, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island2_MouseLeave(object sender, EventArgs e)
        {
            Island2.BackColor = Color.Transparent;
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

        }

        private void Island3_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island3_MouseHover(object sender, EventArgs e)
        {
            Island3.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island3, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island3_MouseLeave(object sender, EventArgs e)
        {
            Island3.BackColor = Color.Transparent;
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

        }

        private void Island4_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island4_MouseHover(object sender, EventArgs e)
        {
            Island4.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island4, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island4_MouseLeave(object sender, EventArgs e)
        {
            Island4.BackColor = Color.Transparent;
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

        }

        private void Island5_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island5_MouseHover(object sender, EventArgs e)
        {
            Island5.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island5, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island5_MouseLeave(object sender, EventArgs e)
        {
            Island5.BackColor = Color.Transparent;
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
           
        }

        private void Island6_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void Island6_MouseHover(object sender, EventArgs e)
        {
            Island6.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(Island6, "可拖动设置油岛位置,双击设置是否隐藏油岛。");
        }

        private void Island6_MouseLeave(object sender, EventArgs e)
        {
            Island6.BackColor = Color.Transparent;
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
            //             EnumControls(StationBoard, 1,0);
            //             Global.mysqlHelper.ExecuteSql("update board_param set linkkind = 'area' where name like '%area%'");
            //             Global.mysqlHelper.ExecuteSql("update board_param set linkkind = 'nozzle' where name like '%Noz%'");
            //             Global.mysqlHelper.ExecuteSql("update board_param set linkkind = 'island' where name like '%Island%'");
            InitBoardControls();
        }
    }
}
