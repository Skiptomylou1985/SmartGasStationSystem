using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace SPServer
{
    public partial class FormMain : Form
    {
        string iniPath = Application.StartupPath + "\\config.ini";
        public FormMain()
        {
            InitializeComponent();
        }

        private void comboStauts_SelectedIndexChanged(object sender, EventArgs e)
        {
            FlushDGV();
        }

        private void timerGetInfo_Tick(object sender, EventArgs e)
        {
            getInfo();
        }

        private void getInfo()
        {
            if (Global.StationQueue.GetQueueCount() > 0)
            {
                StationInfo info = Global.StationQueue.Get();
                string ret = "0";
                string sql;
                if (Global.dicStation.TryGetValue(info.StationCode,out ret))
                {
                    sql = "update station set status = " + info.Status.ToString() + ",updatetime = '" + info.UpdateTime.ToString("yyyy-MM-dd HH:mm:ss") +
                   "',currentratio = " + info.CurrentRatio.ToString() + ",totalratio=" + info.TotalRatio.ToString() + ",totalcount=" + info.TotalCount.ToString() +
                   ",currentcount=" + info.CurrentCount.ToString() +",softversion = '"+info.SoftVersion+"' where ip = '" + info.IP + "' and stationcode = '" + info.StationCode + "'";
                    
                }
                else
                {
                    sql = "insert into station (stationname,stationcode,ip,status,updatetime,currentratio,totalratio,currentcount,totalcount,softversion) values ('" + info.StationName +
                         "','" + info.StationCode + "','" + info.IP + "'," + info.Status.ToString() + ",'" + info.UpdateTime.ToString("yyyy-MM-dd HH:mm:ss") + "'," +
                         info.CurrentRatio.ToString() + "," + info.TotalRatio.ToString() + "," + info.CurrentCount.ToString() + "," + info.TotalCount.ToString() + ",'" + info.SoftVersion + "')";
                    Global.dicStation.Add(info.StationCode, info.IP);
                }
                Global.mysqlHelper.ExecuteSql(sql);
                getInfo();
            }
            
        }

        private bool InitLogServer()
        {

            try
            {
                Global.logLevel = (EnumLogLevel)Enum.Parse(typeof(EnumLogLevel), IniHelper.GetINIValue(iniPath, "main", "loglevel"));
                Global.logServer = new LogHelper((int)Global.logLevel);
                Global.logServer.Run();
            }
            catch (Exception ex)
            {
                return false;
            }

            return true;
        }

        private bool InitDatabase()
        {
            try
            {
                DBInfo info = new DBInfo();
                
                info.type = IniHelper.GetINIValue(iniPath, "database", "type");
                info.ip = IniHelper.GetINIValue(iniPath, "database", "ip");
                info.dbname = IniHelper.GetINIValue(iniPath, "database", "name");
                info.username = IniHelper.GetINIValue(iniPath, "database", "username");
                info.password = IniHelper.GetINIValue(iniPath, "database", "password");
                info.port = int.Parse(IniHelper.GetINIValue(iniPath, "database", "port"));
                Global.logServer.Add(new LogInfo("Debug", "main->InitDatabase param value" +
                   iniPath + " " + info.type + " " + info.ip + " " + info.dbname + " " + info.username + " " + info.password, (int)EnumLogLevel.DEBUG));
                Global.mysqlHelper = new MysqlHelper(info);

            }
            catch (System.Exception ex)
            {
                Global.logServer.Add(new LogInfo("Error", "Main:InitDatabase 初始化数据库失败:" + ex.Message, (int)EnumLogLevel.ERROR));
                return false;
            }
            return true;
        }
        public bool InitSocket()
        {
            Global.socketPort = int.Parse(IniHelper.GetINIValue(iniPath, "main", "socketport"));
            Global.socketHelper = new SocketHelper("127.0.0.1", Global.socketPort);
            return Global.socketHelper.Run();
        }
        public void InitParam()
        {
            Global.dicStation = new Dictionary<string, string>();
            string sql = "select stationcode,ip from station";
            DataTable dt = Global.mysqlHelper.GetDataTable(sql);
            if (dt != null && dt.Rows.Count > 0)
            {
                foreach(DataRow dr in dt.Rows)
                {
                    Global.dicStation.Add(dr["stationcode"].ToString(), dr["ip"].ToString());
                }
            }

        }

        private void FormMain_Load(object sender, EventArgs e)
        {
            InitLogServer();
            if (!InitDatabase())
            {
                MessageBox.Show("数据库初始化失败!");
                return;
            }
            InitParam();
            if (!InitSocket())
            {
                MessageBox.Show("网络初始化失败!");
                return;
            }
            string sql = "select * from station order by status desc";
            dgvStation.DataSource = Global.mysqlHelper.GetDataTable(sql);
            InitForm();
           // SetDGV();
        }

        private void timerShow_Tick(object sender, EventArgs e)
        {
            FlushDGV();
        }

        private void FlushDGV()
        {
            string sql = "select * from station ";
            if (comboStauts.SelectedIndex > 0)
            {
                sql = sql + " where status = " + comboStauts.SelectedIndex.ToString() + " order by updatetime asc";
            }
            else
            {
                sql = sql + " order by status desc";
            }

            dgvStation.DataSource = Global.mysqlHelper.GetDataTable(sql);

        }
        private void SetDGV()
        {
            dgvStation.Columns[0].HeaderText = "序号";
            dgvStation.Columns[0].Visible = false;
            dgvStation.Columns[1].HeaderText = "站点名称";
            dgvStation.Columns[2].HeaderText = "站点编号";
            dgvStation.Columns[3].HeaderText = "站点IP";
            dgvStation.Columns[4].HeaderText = "状态";
            dgvStation.Columns[5].HeaderText = "最后通讯时间";
            dgvStation.Columns[6].HeaderText = "车辆总数";
            dgvStation.Columns[7].HeaderText = "总匹配率 %";
            dgvStation.Columns[8].HeaderText = "当天车辆数";
            dgvStation.Columns[9].HeaderText = "当天匹配率 %";
            dgvStation.Columns[10].HeaderText = "软件版本";
            dgvStation.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            dgvStation.AllowUserToAddRows = false;
            dgvStation.AllowUserToResizeRows = false;
            dgvStation.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            //dgv.AllowUserToAddRows = false;
            //dgv.AllowUserToResizeRows = false;
            dgvStation.ColumnHeadersDefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;

            foreach (DataGridViewColumn item in dgvStation.Columns)
            {
                item.DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
                item.ReadOnly = true;
            }
        }

        private void  InitForm()
        {
            comboStauts.SelectedIndex = 0;
            checkAutoFlush.Checked = true;
            SetDGV();
        }

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {

        }

        private void FormMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            ExitApp();
         }
        private void ExitApp()
        {
            //ProcessStartInfo psi = new ProcessStartInfo();
            //psi.FileName = "Kill.exe";
            //psi.UseShellExecute = false;
            //psi.CreateNoWindow = true;
            //Process.Start(psi);
            Global.socketHelper.Close();
            if (Global.logServer != null)
                Global.logServer.Stop();
            //启动强制退出线程

            System.Environment.Exit(0);
        }

        private void checkAutoFlush_CheckedChanged(object sender, EventArgs e)
        {

            timerShowData.Enabled = checkAutoFlush.Checked;
        }

        private void btnSearch_Click(object sender, EventArgs e)
        {
            checkAutoFlush.Checked = false;
            string sql = "select * from station where stationname like '%" + textName.Text.Trim()+"%'";
            dgvStation.DataSource = Global.mysqlHelper.GetDataTable(sql);
        }

        private void btnTest_Click(object sender, EventArgs e)
        {
            string path = Application.StartupPath;
            using (FileStream file = new FileStream("c://test.jpg", FileMode.Open))
            {
                Image img = Image.FromStream(file);
                img.Save("C://images//test.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);
            }
        }

        private void checkLog_CheckedChanged(object sender, EventArgs e)
        {
            Global.bShowLog = checkLog.Checked;
            timerShowLog.Enabled = checkLog.Checked;
        }

        private void timerShowLog_Tick(object sender, EventArgs e)
        {
            if (Global.ShowLogQueue.GetQueueCount() > 0)
            {
                String info = Global.ShowLogQueue.Get();
                showRTBInfo(info);
            }
        }
        private void showRTBInfo(string infoString)
        {
            if (richTextLog.Lines.Length > 500)
            {
                richTextLog.Clear();
            }
            richTextLog.AppendText(infoString + "\n");
            //让文本框获取焦点
            this.richTextLog.Focus();
            //设置光标的位置到文本尾
            this.richTextLog.Select(this.richTextLog.TextLength, 0);
            //滚动到控件光标处
            this.richTextLog.ScrollToCaret();
        }

        Point pt;
        bool moves = true;
        private void button1_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void button1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                int px = Cursor.Position.X - pt.X;
                int py = Cursor.Position.Y - pt.Y;
                button1.Location = new Point(button1.Location.X + px, button1.Location.Y + py);
                pt = Cursor.Position;
                moves = false;
            }
        }

        private void button1_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }
}
