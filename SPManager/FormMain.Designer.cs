namespace SPManager
{
    partial class FormMain
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.timerServiceStaus = new System.Windows.Forms.Timer(this.components);
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.listViewArea = new System.Windows.Forms.ListView();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.richTextBoxDIT = new System.Windows.Forms.RichTextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.dgvShow = new System.Windows.Forms.DataGridView();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.listViewCache = new System.Windows.Forms.ListView();
            this.statusSystem = new System.Windows.Forms.StatusStrip();
            this.toolStationName = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolMatchPoint = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolRAM = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnTest = new System.Windows.Forms.Button();
            this.comboLogLevel = new System.Windows.Forms.ComboBox();
            this.btnChangeLogLevel = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.pBoxUpdate = new System.Windows.Forms.PictureBox();
            this.label4 = new System.Windows.Forms.Label();
            this.lblLogLevel = new System.Windows.Forms.Label();
            this.btnShowData = new System.Windows.Forms.Button();
            this.pBoxSocket = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.pBoxMonitor = new System.Windows.Forms.PictureBox();
            this.label3 = new System.Windows.Forms.Label();
            this.pBoxMain = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.notifyIconMain = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuExit = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItemExit = new System.Windows.Forms.ToolStripMenuItem();
            this.timerDataProc = new System.Windows.Forms.Timer(this.components);
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.RTBLog = new System.Windows.Forms.RichTextBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.pageSetupDialog1 = new System.Windows.Forms.PageSetupDialog();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.tabPage1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvShow)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.statusSystem.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxUpdate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxSocket)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMonitor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMain)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.contextMenuExit.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.SuspendLayout();
            // 
            // timerServiceStaus
            // 
            this.timerServiceStaus.Enabled = true;
            this.timerServiceStaus.Interval = 10000;
            this.timerServiceStaus.Tick += new System.EventHandler(this.timerServiceStaus_Tick);
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.groupBox4);
            this.tabPage1.Controls.Add(this.groupBox3);
            this.tabPage1.Controls.Add(this.groupBox2);
            this.tabPage1.Controls.Add(this.groupBox1);
            this.tabPage1.Controls.Add(this.statusSystem);
            this.tabPage1.Controls.Add(this.panel1);
            this.tabPage1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Margin = new System.Windows.Forms.Padding(0);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Size = new System.Drawing.Size(1256, 696);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "运行信息";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.listViewArea);
            this.groupBox4.Location = new System.Drawing.Point(444, 45);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(370, 451);
            this.groupBox4.TabIndex = 40;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "视频识别队列";
            // 
            // listViewArea
            // 
            this.listViewArea.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.listViewArea.GridLines = true;
            this.listViewArea.Location = new System.Drawing.Point(8, 28);
            this.listViewArea.Name = "listViewArea";
            this.listViewArea.Size = new System.Drawing.Size(352, 413);
            this.listViewArea.TabIndex = 3;
            this.listViewArea.UseCompatibleStateImageBehavior = false;
            this.listViewArea.View = System.Windows.Forms.View.Details;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.richTextBoxDIT);
            this.groupBox3.Location = new System.Drawing.Point(831, 45);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(413, 451);
            this.groupBox3.TabIndex = 39;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "运行日志";
            // 
            // richTextBoxDIT
            // 
            this.richTextBoxDIT.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.richTextBoxDIT.Location = new System.Drawing.Point(10, 31);
            this.richTextBoxDIT.Name = "richTextBoxDIT";
            this.richTextBoxDIT.Size = new System.Drawing.Size(397, 410);
            this.richTextBoxDIT.TabIndex = 4;
            this.richTextBoxDIT.Text = "";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.dgvShow);
            this.groupBox2.Location = new System.Drawing.Point(8, 500);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(1238, 175);
            this.groupBox2.TabIndex = 38;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "检测数据";
            // 
            // dgvShow
            // 
            this.dgvShow.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvShow.Location = new System.Drawing.Point(5, 24);
            this.dgvShow.Name = "dgvShow";
            this.dgvShow.RowTemplate.Height = 23;
            this.dgvShow.Size = new System.Drawing.Size(1223, 144);
            this.dgvShow.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.listViewCache);
            this.groupBox1.Location = new System.Drawing.Point(8, 45);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(427, 451);
            this.groupBox1.TabIndex = 37;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "油枪匹配队列";
            // 
            // listViewCache
            // 
            this.listViewCache.Font = new System.Drawing.Font("微软雅黑", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.listViewCache.GridLines = true;
            this.listViewCache.Location = new System.Drawing.Point(6, 28);
            this.listViewCache.Name = "listViewCache";
            this.listViewCache.Size = new System.Drawing.Size(412, 413);
            this.listViewCache.TabIndex = 1;
            this.listViewCache.UseCompatibleStateImageBehavior = false;
            this.listViewCache.View = System.Windows.Forms.View.Details;
            // 
            // statusSystem
            // 
            this.statusSystem.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.statusSystem.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStationName,
            this.toolMatchPoint,
            this.toolStripStatusLabel2,
            this.toolRAM,
            this.toolStripStatusLabel3});
            this.statusSystem.Location = new System.Drawing.Point(0, 674);
            this.statusSystem.Name = "statusSystem";
            this.statusSystem.Size = new System.Drawing.Size(1256, 22);
            this.statusSystem.TabIndex = 25;
            this.statusSystem.Text = "statusStrip1";
            this.statusSystem.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.statusSystem_ItemClicked);
            // 
            // toolStationName
            // 
            this.toolStationName.Name = "toolStationName";
            this.toolStationName.Size = new System.Drawing.Size(72, 17);
            this.toolStationName.Text = "检测站点： ";
            // 
            // toolMatchPoint
            // 
            this.toolMatchPoint.Name = "toolMatchPoint";
            this.toolMatchPoint.Size = new System.Drawing.Size(26, 17);
            this.toolMatchPoint.Text = "0%";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(71, 17);
            this.toolStripStatusLabel2.Text = "内存占用率:";
            // 
            // toolRAM
            // 
            this.toolRAM.Name = "toolRAM";
            this.toolRAM.Size = new System.Drawing.Size(40, 17);
            this.toolRAM.Text = "100%";
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(0, 17);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.panel1.Controls.Add(this.btnTest);
            this.panel1.Controls.Add(this.comboLogLevel);
            this.panel1.Controls.Add(this.btnChangeLogLevel);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.pBoxUpdate);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.lblLogLevel);
            this.panel1.Controls.Add(this.btnShowData);
            this.panel1.Controls.Add(this.pBoxSocket);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.pBoxMonitor);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.pBoxMain);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Location = new System.Drawing.Point(-7, 2);
            this.panel1.Margin = new System.Windows.Forms.Padding(0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1461, 40);
            this.panel1.TabIndex = 0;
            // 
            // btnTest
            // 
            this.btnTest.Font = new System.Drawing.Font("宋体", 9F);
            this.btnTest.Location = new System.Drawing.Point(1352, 6);
            this.btnTest.Name = "btnTest";
            this.btnTest.Size = new System.Drawing.Size(75, 29);
            this.btnTest.TabIndex = 37;
            this.btnTest.Text = "测  试";
            this.btnTest.UseVisualStyleBackColor = true;
            this.btnTest.Click += new System.EventHandler(this.btnTest_Click);
            // 
            // comboLogLevel
            // 
            this.comboLogLevel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboLogLevel.FormattingEnabled = true;
            this.comboLogLevel.Items.AddRange(new object[] {
            "错误",
            "正常",
            "调试",
            "全部"});
            this.comboLogLevel.Location = new System.Drawing.Point(995, 6);
            this.comboLogLevel.Name = "comboLogLevel";
            this.comboLogLevel.Size = new System.Drawing.Size(75, 29);
            this.comboLogLevel.TabIndex = 32;
            // 
            // btnChangeLogLevel
            // 
            this.btnChangeLogLevel.Font = new System.Drawing.Font("宋体", 9F);
            this.btnChangeLogLevel.Location = new System.Drawing.Point(1085, 6);
            this.btnChangeLogLevel.Name = "btnChangeLogLevel";
            this.btnChangeLogLevel.Size = new System.Drawing.Size(75, 29);
            this.btnChangeLogLevel.TabIndex = 31;
            this.btnChangeLogLevel.Text = "切  换";
            this.btnChangeLogLevel.UseVisualStyleBackColor = true;
            this.btnChangeLogLevel.Click += new System.EventHandler(this.btnChangeLogLevel_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(823, 7);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(122, 21);
            this.label5.TabIndex = 10;
            this.label5.Text = "当前日志级别：";
            // 
            // pBoxUpdate
            // 
            this.pBoxUpdate.Image = ((System.Drawing.Image)(resources.GetObject("pBoxUpdate.Image")));
            this.pBoxUpdate.Location = new System.Drawing.Point(688, 3);
            this.pBoxUpdate.Name = "pBoxUpdate";
            this.pBoxUpdate.Size = new System.Drawing.Size(32, 32);
            this.pBoxUpdate.TabIndex = 7;
            this.pBoxUpdate.TabStop = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(568, 8);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(122, 21);
            this.label4.TabIndex = 6;
            this.label4.Text = "自动升级服务：";
            // 
            // lblLogLevel
            // 
            this.lblLogLevel.AutoSize = true;
            this.lblLogLevel.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblLogLevel.ForeColor = System.Drawing.Color.Green;
            this.lblLogLevel.Location = new System.Drawing.Point(947, 8);
            this.lblLogLevel.Name = "lblLogLevel";
            this.lblLogLevel.Size = new System.Drawing.Size(42, 21);
            this.lblLogLevel.TabIndex = 34;
            this.lblLogLevel.Text = "调试";
            // 
            // btnShowData
            // 
            this.btnShowData.Font = new System.Drawing.Font("宋体", 9F);
            this.btnShowData.Location = new System.Drawing.Point(1176, 6);
            this.btnShowData.Name = "btnShowData";
            this.btnShowData.Size = new System.Drawing.Size(75, 29);
            this.btnShowData.TabIndex = 35;
            this.btnShowData.Text = "查询数据";
            this.btnShowData.UseVisualStyleBackColor = true;
            this.btnShowData.Click += new System.EventHandler(this.btnShowData_Click);
            // 
            // pBoxSocket
            // 
            this.pBoxSocket.Image = ((System.Drawing.Image)(resources.GetObject("pBoxSocket.Image")));
            this.pBoxSocket.Location = new System.Drawing.Point(329, 3);
            this.pBoxSocket.Name = "pBoxSocket";
            this.pBoxSocket.Size = new System.Drawing.Size(32, 32);
            this.pBoxSocket.TabIndex = 7;
            this.pBoxSocket.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(207, 8);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(122, 21);
            this.label2.TabIndex = 6;
            this.label2.Text = "网络通讯服务：";
            // 
            // pBoxMonitor
            // 
            this.pBoxMonitor.Image = ((System.Drawing.Image)(resources.GetObject("pBoxMonitor.Image")));
            this.pBoxMonitor.Location = new System.Drawing.Point(509, 3);
            this.pBoxMonitor.Name = "pBoxMonitor";
            this.pBoxMonitor.Size = new System.Drawing.Size(32, 32);
            this.pBoxMonitor.TabIndex = 7;
            this.pBoxMonitor.TabStop = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(390, 8);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(122, 21);
            this.label3.TabIndex = 6;
            this.label3.Text = "运行监控服务：";
            // 
            // pBoxMain
            // 
            this.pBoxMain.Image = ((System.Drawing.Image)(resources.GetObject("pBoxMain.Image")));
            this.pBoxMain.Location = new System.Drawing.Point(140, 3);
            this.pBoxMain.Name = "pBoxMain";
            this.pBoxMain.Size = new System.Drawing.Size(32, 32);
            this.pBoxMain.TabIndex = 3;
            this.pBoxMain.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(18, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(122, 21);
            this.label1.TabIndex = 2;
            this.label1.Text = "车牌识别服务：";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1264, 722);
            this.tabControl1.TabIndex = 18;
            // 
            // notifyIconMain
            // 
            this.notifyIconMain.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIconMain.Icon")));
            this.notifyIconMain.Text = "SPManager";
            this.notifyIconMain.Visible = true;
            this.notifyIconMain.MouseClick += new System.Windows.Forms.MouseEventHandler(this.notifyIconMain_MouseClick);
            this.notifyIconMain.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIconMain_MouseDoubleClick);
            // 
            // contextMenuExit
            // 
            this.contextMenuExit.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.contextMenuExit.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItemExit});
            this.contextMenuExit.Name = "contextMenuStrip1";
            this.contextMenuExit.Size = new System.Drawing.Size(101, 26);
            // 
            // toolStripMenuItemExit
            // 
            this.toolStripMenuItemExit.Name = "toolStripMenuItemExit";
            this.toolStripMenuItemExit.Size = new System.Drawing.Size(100, 22);
            this.toolStripMenuItemExit.Text = "退出";
            this.toolStripMenuItemExit.Click += new System.EventHandler(this.toolStripMenuItemExit_Click);
            // 
            // timerDataProc
            // 
            this.timerDataProc.Interval = 1000;
            this.timerDataProc.Tick += new System.EventHandler(this.timerDataProc_Tick);
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Size = new System.Drawing.Size(1256, 696);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "车辆查询";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.RTBLog);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(1256, 696);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "运行日志";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.tableLayoutPanel1);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(1256, 696);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "统计信息";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // RTBLog
            // 
            this.RTBLog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.RTBLog.Location = new System.Drawing.Point(0, 0);
            this.RTBLog.Name = "RTBLog";
            this.RTBLog.Size = new System.Drawing.Size(1256, 696);
            this.RTBLog.TabIndex = 0;
            this.RTBLog.Text = "";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 200F));
            this.tableLayoutPanel1.Controls.Add(this.chart1, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1256, 696);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // chart1
            // 
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            this.chart1.Dock = System.Windows.Forms.DockStyle.Fill;
            legend1.Name = "Legend1";
            this.chart1.Legends.Add(legend1);
            this.chart1.Location = new System.Drawing.Point(3, 3);
            this.chart1.Name = "chart1";
            series1.ChartArea = "ChartArea1";
            series1.Legend = "Legend1";
            series1.Name = "Series1";
            this.chart1.Series.Add(series1);
            this.chart1.Size = new System.Drawing.Size(1250, 342);
            this.chart1.TabIndex = 19;
            this.chart1.Text = "chart1";
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 722);
            this.Controls.Add(this.tabControl1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FormMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "加油站智能信息管理系统SPManager V2.0.1.812";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormMain_FormClosed);
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgvShow)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.statusSystem.ResumeLayout(false);
            this.statusSystem.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxUpdate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxSocket)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMonitor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMain)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.contextMenuExit.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            this.tabPage4.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Timer timerServiceStaus;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.ComboBox comboLogLevel;
        private System.Windows.Forms.Button btnChangeLogLevel;
        private System.Windows.Forms.StatusStrip statusSystem;
        private System.Windows.Forms.ToolStripStatusLabel toolMatchPoint;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel toolRAM;
        private System.Windows.Forms.PictureBox pBoxMonitor;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.PictureBox pBoxMain;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox pBoxUpdate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox pBoxSocket;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.NotifyIcon notifyIconMain;
        private System.Windows.Forms.ContextMenuStrip contextMenuExit;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemExit;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lblLogLevel;
        private System.Windows.Forms.Button btnShowData;
        private System.Windows.Forms.Button btnTest;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ListView listViewCache;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.DataGridView dgvShow;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.ListView listViewArea;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RichTextBox richTextBoxDIT;
        private System.Windows.Forms.ToolStripStatusLabel toolStationName;
        private System.Windows.Forms.Timer timerDataProc;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.RichTextBox RTBLog;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.PageSetupDialog pageSetupDialog1;
    }
}

