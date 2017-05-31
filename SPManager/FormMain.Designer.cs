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
            this.timerServiceStaus = new System.Windows.Forms.Timer(this.components);
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.btnUpdate = new System.Windows.Forms.Button();
            this.btnShowData = new System.Windows.Forms.Button();
            this.lblLogLevel = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.comboLogLevel = new System.Windows.Forms.ComboBox();
            this.btnChangeLogLevel = new System.Windows.Forms.Button();
            this.statusSystem = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolCPU = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolRAM = new System.Windows.Forms.ToolStripStatusLabel();
            this.btnCloseMonitor = new System.Windows.Forms.Button();
            this.btnOpenMonitor = new System.Windows.Forms.Button();
            this.pBoxMonitor = new System.Windows.Forms.PictureBox();
            this.label3 = new System.Windows.Forms.Label();
            this.btnCloseMain = new System.Windows.Forms.Button();
            this.btnOpenMain = new System.Windows.Forms.Button();
            this.pBoxMain = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.btnCloseUpdate = new System.Windows.Forms.Button();
            this.btnOpenUpdate = new System.Windows.Forms.Button();
            this.pBoxUpdate = new System.Windows.Forms.PictureBox();
            this.label4 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnCloseSocket = new System.Windows.Forms.Button();
            this.btnOpenSocket = new System.Windows.Forms.Button();
            this.pBoxSocket = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.btnSwitch = new System.Windows.Forms.Button();
            this.richTextBoxDIT = new System.Windows.Forms.RichTextBox();
            this.listViewCache = new System.Windows.Forms.ListView();
            this.notifyIconMain = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuExit = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItemExit = new System.Windows.Forms.ToolStripMenuItem();
            this.timerDataProc = new System.Windows.Forms.Timer(this.components);
            this.tabPage1.SuspendLayout();
            this.statusSystem.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMonitor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMain)).BeginInit();
            this.panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxUpdate)).BeginInit();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxSocket)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.contextMenuExit.SuspendLayout();
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
            this.tabPage1.Controls.Add(this.btnUpdate);
            this.tabPage1.Controls.Add(this.btnShowData);
            this.tabPage1.Controls.Add(this.lblLogLevel);
            this.tabPage1.Controls.Add(this.label5);
            this.tabPage1.Controls.Add(this.comboLogLevel);
            this.tabPage1.Controls.Add(this.btnChangeLogLevel);
            this.tabPage1.Controls.Add(this.statusSystem);
            this.tabPage1.Controls.Add(this.btnCloseMonitor);
            this.tabPage1.Controls.Add(this.btnOpenMonitor);
            this.tabPage1.Controls.Add(this.pBoxMonitor);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.btnCloseMain);
            this.tabPage1.Controls.Add(this.btnOpenMain);
            this.tabPage1.Controls.Add(this.pBoxMain);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.panel3);
            this.tabPage1.Controls.Add(this.panel1);
            this.tabPage1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Margin = new System.Windows.Forms.Padding(0);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Size = new System.Drawing.Size(436, 286);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "运行状态";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // btnUpdate
            // 
            this.btnUpdate.Font = new System.Drawing.Font("宋体", 9F);
            this.btnUpdate.Location = new System.Drawing.Point(265, 232);
            this.btnUpdate.Name = "btnUpdate";
            this.btnUpdate.Size = new System.Drawing.Size(78, 29);
            this.btnUpdate.TabIndex = 36;
            this.btnUpdate.Text = "升级软件";
            this.btnUpdate.UseVisualStyleBackColor = true;
            this.btnUpdate.Click += new System.EventHandler(this.btnUpdate_Click);
            // 
            // btnShowData
            // 
            this.btnShowData.Font = new System.Drawing.Font("宋体", 9F);
            this.btnShowData.Location = new System.Drawing.Point(175, 232);
            this.btnShowData.Name = "btnShowData";
            this.btnShowData.Size = new System.Drawing.Size(75, 29);
            this.btnShowData.TabIndex = 35;
            this.btnShowData.Text = "查看数据";
            this.btnShowData.UseVisualStyleBackColor = true;
            this.btnShowData.Click += new System.EventHandler(this.btnShowData_Click);
            // 
            // lblLogLevel
            // 
            this.lblLogLevel.AutoSize = true;
            this.lblLogLevel.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblLogLevel.ForeColor = System.Drawing.Color.Green;
            this.lblLogLevel.Location = new System.Drawing.Point(127, 181);
            this.lblLogLevel.Name = "lblLogLevel";
            this.lblLogLevel.Size = new System.Drawing.Size(42, 21);
            this.lblLogLevel.TabIndex = 34;
            this.lblLogLevel.Text = "调试";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(8, 180);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(122, 21);
            this.label5.TabIndex = 10;
            this.label5.Text = "当前日志级别：";
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
            this.comboLogLevel.Location = new System.Drawing.Point(175, 179);
            this.comboLogLevel.Name = "comboLogLevel";
            this.comboLogLevel.Size = new System.Drawing.Size(75, 29);
            this.comboLogLevel.TabIndex = 32;
            // 
            // btnChangeLogLevel
            // 
            this.btnChangeLogLevel.Font = new System.Drawing.Font("宋体", 9F);
            this.btnChangeLogLevel.Location = new System.Drawing.Point(265, 179);
            this.btnChangeLogLevel.Name = "btnChangeLogLevel";
            this.btnChangeLogLevel.Size = new System.Drawing.Size(75, 29);
            this.btnChangeLogLevel.TabIndex = 31;
            this.btnChangeLogLevel.Text = "切  换";
            this.btnChangeLogLevel.UseVisualStyleBackColor = true;
            this.btnChangeLogLevel.Click += new System.EventHandler(this.btnChangeLogLevel_Click);
            // 
            // statusSystem
            // 
            this.statusSystem.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolCPU,
            this.toolStripStatusLabel2,
            this.toolRAM});
            this.statusSystem.Location = new System.Drawing.Point(0, 264);
            this.statusSystem.Name = "statusSystem";
            this.statusSystem.Size = new System.Drawing.Size(436, 22);
            this.statusSystem.TabIndex = 25;
            this.statusSystem.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(80, 17);
            this.toolStripStatusLabel1.Text = "CPU占用率：";
            // 
            // toolCPU
            // 
            this.toolCPU.Name = "toolCPU";
            this.toolCPU.Size = new System.Drawing.Size(26, 17);
            this.toolCPU.Text = "0%";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(80, 17);
            this.toolStripStatusLabel2.Text = "内存占用率：";
            // 
            // toolRAM
            // 
            this.toolRAM.Name = "toolRAM";
            this.toolRAM.Size = new System.Drawing.Size(40, 17);
            this.toolRAM.Text = "100%";
            // 
            // btnCloseMonitor
            // 
            this.btnCloseMonitor.Font = new System.Drawing.Font("宋体", 9F);
            this.btnCloseMonitor.Location = new System.Drawing.Point(328, 90);
            this.btnCloseMonitor.Name = "btnCloseMonitor";
            this.btnCloseMonitor.Size = new System.Drawing.Size(75, 23);
            this.btnCloseMonitor.TabIndex = 9;
            this.btnCloseMonitor.Text = "关  闭";
            this.btnCloseMonitor.UseVisualStyleBackColor = true;
            // 
            // btnOpenMonitor
            // 
            this.btnOpenMonitor.Font = new System.Drawing.Font("宋体", 9F);
            this.btnOpenMonitor.Location = new System.Drawing.Point(233, 90);
            this.btnOpenMonitor.Name = "btnOpenMonitor";
            this.btnOpenMonitor.Size = new System.Drawing.Size(75, 23);
            this.btnOpenMonitor.TabIndex = 8;
            this.btnOpenMonitor.Text = "开  启";
            this.btnOpenMonitor.UseVisualStyleBackColor = true;
            // 
            // pBoxMonitor
            // 
            this.pBoxMonitor.Image = ((System.Drawing.Image)(resources.GetObject("pBoxMonitor.Image")));
            this.pBoxMonitor.Location = new System.Drawing.Point(152, 86);
            this.pBoxMonitor.Name = "pBoxMonitor";
            this.pBoxMonitor.Size = new System.Drawing.Size(32, 32);
            this.pBoxMonitor.TabIndex = 7;
            this.pBoxMonitor.TabStop = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(12, 91);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(122, 21);
            this.label3.TabIndex = 6;
            this.label3.Text = "运行监控服务：";
            // 
            // btnCloseMain
            // 
            this.btnCloseMain.Font = new System.Drawing.Font("宋体", 9F);
            this.btnCloseMain.Location = new System.Drawing.Point(327, 7);
            this.btnCloseMain.Name = "btnCloseMain";
            this.btnCloseMain.Size = new System.Drawing.Size(75, 23);
            this.btnCloseMain.TabIndex = 5;
            this.btnCloseMain.Text = "关  闭";
            this.btnCloseMain.UseVisualStyleBackColor = true;
            this.btnCloseMain.Click += new System.EventHandler(this.btnCloseMain_Click);
            // 
            // btnOpenMain
            // 
            this.btnOpenMain.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnOpenMain.Location = new System.Drawing.Point(232, 7);
            this.btnOpenMain.Name = "btnOpenMain";
            this.btnOpenMain.Size = new System.Drawing.Size(75, 23);
            this.btnOpenMain.TabIndex = 4;
            this.btnOpenMain.Text = "开  启";
            this.btnOpenMain.UseVisualStyleBackColor = true;
            // 
            // pBoxMain
            // 
            this.pBoxMain.Image = ((System.Drawing.Image)(resources.GetObject("pBoxMain.Image")));
            this.pBoxMain.Location = new System.Drawing.Point(152, 3);
            this.pBoxMain.Name = "pBoxMain";
            this.pBoxMain.Size = new System.Drawing.Size(32, 32);
            this.pBoxMain.TabIndex = 3;
            this.pBoxMain.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(11, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(122, 21);
            this.label1.TabIndex = 2;
            this.label1.Text = "车牌识别服务：";
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.panel3.Controls.Add(this.btnCloseUpdate);
            this.panel3.Controls.Add(this.btnOpenUpdate);
            this.panel3.Controls.Add(this.pBoxUpdate);
            this.panel3.Controls.Add(this.label4);
            this.panel3.Location = new System.Drawing.Point(-4, 126);
            this.panel3.Margin = new System.Windows.Forms.Padding(0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(614, 40);
            this.panel3.TabIndex = 1;
            // 
            // btnCloseUpdate
            // 
            this.btnCloseUpdate.Font = new System.Drawing.Font("宋体", 9F);
            this.btnCloseUpdate.Location = new System.Drawing.Point(332, 8);
            this.btnCloseUpdate.Name = "btnCloseUpdate";
            this.btnCloseUpdate.Size = new System.Drawing.Size(75, 23);
            this.btnCloseUpdate.TabIndex = 9;
            this.btnCloseUpdate.Text = "关  闭";
            this.btnCloseUpdate.UseVisualStyleBackColor = true;
            // 
            // btnOpenUpdate
            // 
            this.btnOpenUpdate.Font = new System.Drawing.Font("宋体", 9F);
            this.btnOpenUpdate.Location = new System.Drawing.Point(237, 8);
            this.btnOpenUpdate.Name = "btnOpenUpdate";
            this.btnOpenUpdate.Size = new System.Drawing.Size(75, 23);
            this.btnOpenUpdate.TabIndex = 8;
            this.btnOpenUpdate.Text = "开  启";
            this.btnOpenUpdate.UseVisualStyleBackColor = true;
            // 
            // pBoxUpdate
            // 
            this.pBoxUpdate.Image = ((System.Drawing.Image)(resources.GetObject("pBoxUpdate.Image")));
            this.pBoxUpdate.Location = new System.Drawing.Point(157, 4);
            this.pBoxUpdate.Name = "pBoxUpdate";
            this.pBoxUpdate.Size = new System.Drawing.Size(32, 32);
            this.pBoxUpdate.TabIndex = 7;
            this.pBoxUpdate.TabStop = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(16, 9);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(122, 21);
            this.label4.TabIndex = 6;
            this.label4.Text = "自动升级服务：";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.panel1.Controls.Add(this.btnCloseSocket);
            this.panel1.Controls.Add(this.btnOpenSocket);
            this.panel1.Controls.Add(this.pBoxSocket);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Location = new System.Drawing.Point(-7, 38);
            this.panel1.Margin = new System.Windows.Forms.Padding(0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(617, 40);
            this.panel1.TabIndex = 0;
            // 
            // btnCloseSocket
            // 
            this.btnCloseSocket.Font = new System.Drawing.Font("宋体", 9F);
            this.btnCloseSocket.Location = new System.Drawing.Point(334, 8);
            this.btnCloseSocket.Name = "btnCloseSocket";
            this.btnCloseSocket.Size = new System.Drawing.Size(75, 23);
            this.btnCloseSocket.TabIndex = 9;
            this.btnCloseSocket.Text = "关  闭";
            this.btnCloseSocket.UseVisualStyleBackColor = true;
            // 
            // btnOpenSocket
            // 
            this.btnOpenSocket.Font = new System.Drawing.Font("宋体", 9F);
            this.btnOpenSocket.Location = new System.Drawing.Point(239, 8);
            this.btnOpenSocket.Name = "btnOpenSocket";
            this.btnOpenSocket.Size = new System.Drawing.Size(75, 23);
            this.btnOpenSocket.TabIndex = 8;
            this.btnOpenSocket.Text = "开  启";
            this.btnOpenSocket.UseVisualStyleBackColor = true;
            // 
            // pBoxSocket
            // 
            this.pBoxSocket.Image = ((System.Drawing.Image)(resources.GetObject("pBoxSocket.Image")));
            this.pBoxSocket.Location = new System.Drawing.Point(159, 4);
            this.pBoxSocket.Name = "pBoxSocket";
            this.pBoxSocket.Size = new System.Drawing.Size(32, 32);
            this.pBoxSocket.TabIndex = 7;
            this.pBoxSocket.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(18, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(122, 21);
            this.label2.TabIndex = 6;
            this.label2.Text = "网络通讯服务：";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(444, 312);
            this.tabControl1.TabIndex = 18;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.btnSwitch);
            this.tabPage2.Controls.Add(this.richTextBoxDIT);
            this.tabPage2.Controls.Add(this.listViewCache);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Size = new System.Drawing.Size(559, 401);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "缓存队列";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // btnSwitch
            // 
            this.btnSwitch.Location = new System.Drawing.Point(221, 346);
            this.btnSwitch.Name = "btnSwitch";
            this.btnSwitch.Size = new System.Drawing.Size(75, 23);
            this.btnSwitch.TabIndex = 2;
            this.btnSwitch.Text = "切换视频";
            this.btnSwitch.UseVisualStyleBackColor = true;
            this.btnSwitch.Click += new System.EventHandler(this.btnSwitch_Click);
            // 
            // richTextBoxDIT
            // 
            this.richTextBoxDIT.Location = new System.Drawing.Point(354, 0);
            this.richTextBoxDIT.Name = "richTextBoxDIT";
            this.richTextBoxDIT.Size = new System.Drawing.Size(202, 337);
            this.richTextBoxDIT.TabIndex = 1;
            this.richTextBoxDIT.Text = "";
            // 
            // listViewCache
            // 
            this.listViewCache.GridLines = true;
            this.listViewCache.Location = new System.Drawing.Point(0, 0);
            this.listViewCache.Name = "listViewCache";
            this.listViewCache.Size = new System.Drawing.Size(356, 340);
            this.listViewCache.TabIndex = 0;
            this.listViewCache.UseCompatibleStateImageBehavior = false;
            this.listViewCache.View = System.Windows.Forms.View.Details;
            // 
            // notifyIconMain
            // 
            this.notifyIconMain.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIconMain.Icon")));
            this.notifyIconMain.Text = "notifyIcon1";
            this.notifyIconMain.Visible = true;
            this.notifyIconMain.MouseClick += new System.Windows.Forms.MouseEventHandler(this.notifyIconMain_MouseClick);
            this.notifyIconMain.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIconMain_MouseDoubleClick);
            // 
            // contextMenuExit
            // 
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
            this.timerDataProc.Enabled = true;
            this.timerDataProc.Interval = 1000;
            this.timerDataProc.Tick += new System.EventHandler(this.timerDataProc_Tick);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(444, 312);
            this.Controls.Add(this.tabControl1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FormMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "加油站智能信息管理系统";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormMain_FormClosed);
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.statusSystem.ResumeLayout(false);
            this.statusSystem.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMonitor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMain)).EndInit();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxUpdate)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxSocket)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.contextMenuExit.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Timer timerServiceStaus;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.ComboBox comboLogLevel;
        private System.Windows.Forms.Button btnChangeLogLevel;
        private System.Windows.Forms.StatusStrip statusSystem;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel toolCPU;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel toolRAM;
        private System.Windows.Forms.Button btnCloseMonitor;
        private System.Windows.Forms.Button btnOpenMonitor;
        private System.Windows.Forms.PictureBox pBoxMonitor;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnCloseMain;
        private System.Windows.Forms.Button btnOpenMain;
        private System.Windows.Forms.PictureBox pBoxMain;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Button btnCloseUpdate;
        private System.Windows.Forms.Button btnOpenUpdate;
        private System.Windows.Forms.PictureBox pBoxUpdate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button btnCloseSocket;
        private System.Windows.Forms.Button btnOpenSocket;
        private System.Windows.Forms.PictureBox pBoxSocket;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.NotifyIcon notifyIconMain;
        private System.Windows.Forms.ContextMenuStrip contextMenuExit;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemExit;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lblLogLevel;
        private System.Windows.Forms.Button btnShowData;
        private System.Windows.Forms.Button btnUpdate;
        private System.Windows.Forms.Timer timerDataProc;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.ListView listViewCache;
        private System.Windows.Forms.RichTextBox richTextBoxDIT;
        private System.Windows.Forms.Button btnSwitch;
    }
}

