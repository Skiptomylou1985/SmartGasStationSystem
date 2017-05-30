namespace ParamSet
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnClose = new System.Windows.Forms.Button();
            this.btnSetInfo = new System.Windows.Forms.Button();
            this.textDBName = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.btnOpen = new System.Windows.Forms.Button();
            this.comboDBType = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textDBPwd = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textDBAdmin = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textDBIP = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBoxSet = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnDeleteNozzle = new System.Windows.Forms.Button();
            this.btnAddNozzle = new System.Windows.Forms.Button();
            this.comboArea = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.btnCancel = new System.Windows.Forms.Button();
            this.lblAction = new System.Windows.Forms.Label();
            this.btnChangeCurve = new System.Windows.Forms.Button();
            this.comboOilType = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.comboNozzleNo = new System.Windows.Forms.ComboBox();
            this.btnDeleteCurve = new System.Windows.Forms.Button();
            this.btnSaveCurve = new System.Windows.Forms.Button();
            this.btnAddCurve = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.videoBox = new System.Windows.Forms.PictureBox();
            this.contextTreeAdd = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addDevice = new System.Windows.Forms.ToolStripMenuItem();
            this.treeMain = new System.Windows.Forms.TreeView();
            this.timerCurve = new System.Windows.Forms.Timer(this.components);
            this.contextMenuDelete = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.lblStationName = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.lblCurVideoNo = new System.Windows.Forms.ToolStripStatusLabel();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBoxSet.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.videoBox)).BeginInit();
            this.contextTreeAdd.SuspendLayout();
            this.contextMenuDelete.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnClose);
            this.groupBox1.Controls.Add(this.btnSetInfo);
            this.groupBox1.Controls.Add(this.textDBName);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.btnOpen);
            this.groupBox1.Controls.Add(this.comboDBType);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.textDBPwd);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.textDBAdmin);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.textDBIP);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(11, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(985, 69);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "数据库";
            // 
            // btnClose
            // 
            this.btnClose.Location = new System.Drawing.Point(808, 24);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(75, 23);
            this.btnClose.TabIndex = 22;
            this.btnClose.Text = "断  开";
            this.btnClose.UseVisualStyleBackColor = true;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // btnSetInfo
            // 
            this.btnSetInfo.Location = new System.Drawing.Point(889, 23);
            this.btnSetInfo.Name = "btnSetInfo";
            this.btnSetInfo.Size = new System.Drawing.Size(80, 24);
            this.btnSetInfo.TabIndex = 11;
            this.btnSetInfo.Text = "站点设置";
            this.btnSetInfo.UseVisualStyleBackColor = true;
            this.btnSetInfo.Click += new System.EventHandler(this.btnSetInfo_Click);
            // 
            // textDBName
            // 
            this.textDBName.Location = new System.Drawing.Point(646, 25);
            this.textDBName.Name = "textDBName";
            this.textDBName.Size = new System.Drawing.Size(71, 21);
            this.textDBName.TabIndex = 10;
            this.textDBName.Text = "gsims";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(563, 29);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "数据库名称：";
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(727, 24);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(75, 23);
            this.btnOpen.TabIndex = 8;
            this.btnOpen.Text = "连  接";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // comboDBType
            // 
            this.comboDBType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboDBType.FormattingEnabled = true;
            this.comboDBType.Items.AddRange(new object[] {
            "MySQL",
            "SQL Server",
            "Oracle"});
            this.comboDBType.Location = new System.Drawing.Point(102, 26);
            this.comboDBType.Name = "comboDBType";
            this.comboDBType.Size = new System.Drawing.Size(73, 20);
            this.comboDBType.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(31, 30);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "数据库类型：";
            // 
            // textDBPwd
            // 
            this.textDBPwd.Location = new System.Drawing.Point(465, 26);
            this.textDBPwd.Name = "textDBPwd";
            this.textDBPwd.Size = new System.Drawing.Size(84, 21);
            this.textDBPwd.TabIndex = 5;
            this.textDBPwd.Text = "12345";
            this.textDBPwd.UseSystemPasswordChar = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(418, 30);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "密码：";
            // 
            // textDBAdmin
            // 
            this.textDBAdmin.Location = new System.Drawing.Point(356, 26);
            this.textDBAdmin.Name = "textDBAdmin";
            this.textDBAdmin.Size = new System.Drawing.Size(56, 21);
            this.textDBAdmin.TabIndex = 3;
            this.textDBAdmin.Text = "root";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(304, 31);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "登录名：";
            // 
            // textDBIP
            // 
            this.textDBIP.Location = new System.Drawing.Point(212, 26);
            this.textDBIP.Name = "textDBIP";
            this.textDBIP.Size = new System.Drawing.Size(86, 21);
            this.textDBIP.TabIndex = 1;
            this.textDBIP.Text = "127.0.0.1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(183, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "IP：";
            // 
            // groupBoxSet
            // 
            this.groupBoxSet.Controls.Add(this.groupBox2);
            this.groupBoxSet.Controls.Add(this.videoBox);
            this.groupBoxSet.Location = new System.Drawing.Point(186, 102);
            this.groupBoxSet.Name = "groupBoxSet";
            this.groupBoxSet.Size = new System.Drawing.Size(810, 581);
            this.groupBoxSet.TabIndex = 2;
            this.groupBoxSet.TabStop = false;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.btnDeleteNozzle);
            this.groupBox2.Controls.Add(this.btnAddNozzle);
            this.groupBox2.Controls.Add(this.comboArea);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.btnCancel);
            this.groupBox2.Controls.Add(this.lblAction);
            this.groupBox2.Controls.Add(this.btnChangeCurve);
            this.groupBox2.Controls.Add(this.comboOilType);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.comboNozzleNo);
            this.groupBox2.Controls.Add(this.btnDeleteCurve);
            this.groupBox2.Controls.Add(this.btnSaveCurve);
            this.groupBox2.Controls.Add(this.btnAddCurve);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Location = new System.Drawing.Point(6, 11);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(800, 110);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "油枪出入口关联设置";
            this.groupBox2.Enter += new System.EventHandler(this.groupBox2_Enter);
            // 
            // btnDeleteNozzle
            // 
            this.btnDeleteNozzle.Location = new System.Drawing.Point(533, 22);
            this.btnDeleteNozzle.Name = "btnDeleteNozzle";
            this.btnDeleteNozzle.Size = new System.Drawing.Size(88, 23);
            this.btnDeleteNozzle.TabIndex = 25;
            this.btnDeleteNozzle.Text = "删除油枪";
            this.btnDeleteNozzle.UseVisualStyleBackColor = true;
            // 
            // btnAddNozzle
            // 
            this.btnAddNozzle.Location = new System.Drawing.Point(429, 22);
            this.btnAddNozzle.Name = "btnAddNozzle";
            this.btnAddNozzle.Size = new System.Drawing.Size(89, 23);
            this.btnAddNozzle.TabIndex = 24;
            this.btnAddNozzle.Text = "添加油枪";
            this.btnAddNozzle.UseVisualStyleBackColor = true;
            this.btnAddNozzle.Click += new System.EventHandler(this.btnAddNozzle_Click);
            // 
            // comboArea
            // 
            this.comboArea.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboArea.FormattingEnabled = true;
            this.comboArea.Items.AddRange(new object[] {
            "入口",
            "出口",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16",
            "17",
            "18",
            "19",
            "20",
            "21",
            "22",
            "23",
            "24",
            "25",
            "26",
            "27",
            "28",
            "29",
            "30",
            "31",
            "32"});
            this.comboArea.Location = new System.Drawing.Point(55, 56);
            this.comboArea.Name = "comboArea";
            this.comboArea.Size = new System.Drawing.Size(75, 20);
            this.comboArea.TabIndex = 23;
            this.comboArea.SelectedIndexChanged += new System.EventHandler(this.comboArea_SelectedIndexChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 59);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(53, 12);
            this.label9.TabIndex = 22;
            this.label9.Text = "识别区：";
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(256, 54);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 21;
            this.btnCancel.Text = "取  消";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // lblAction
            // 
            this.lblAction.AutoSize = true;
            this.lblAction.Location = new System.Drawing.Point(391, 89);
            this.lblAction.Name = "lblAction";
            this.lblAction.Size = new System.Drawing.Size(41, 12);
            this.lblAction.TabIndex = 19;
            this.lblAction.Text = "显示：";
            // 
            // btnChangeCurve
            // 
            this.btnChangeCurve.Location = new System.Drawing.Point(156, 22);
            this.btnChangeCurve.Name = "btnChangeCurve";
            this.btnChangeCurve.Size = new System.Drawing.Size(75, 23);
            this.btnChangeCurve.TabIndex = 18;
            this.btnChangeCurve.Text = "修改识别区";
            this.btnChangeCurve.UseVisualStyleBackColor = true;
            this.btnChangeCurve.Click += new System.EventHandler(this.btnChangeCurve_Click);
            // 
            // comboOilType
            // 
            this.comboOilType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboOilType.FormattingEnabled = true;
            this.comboOilType.Items.AddRange(new object[] {
            "90#汽油",
            "92#汽油",
            "95#汽油",
            "97#汽油",
            "98#汽油",
            "0#柴油"});
            this.comboOilType.Location = new System.Drawing.Point(550, 54);
            this.comboOilType.Name = "comboOilType";
            this.comboOilType.Size = new System.Drawing.Size(62, 20);
            this.comboOilType.TabIndex = 17;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(500, 59);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 12);
            this.label7.TabIndex = 15;
            this.label7.Text = "油类型：";
            // 
            // comboNozzleNo
            // 
            this.comboNozzleNo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboNozzleNo.FormattingEnabled = true;
            this.comboNozzleNo.Items.AddRange(new object[] {
            "入口",
            "出口",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16",
            "17",
            "18",
            "19",
            "20",
            "21",
            "22",
            "23",
            "24",
            "25",
            "26",
            "27",
            "28",
            "29",
            "30",
            "31",
            "32"});
            this.comboNozzleNo.Location = new System.Drawing.Point(429, 56);
            this.comboNozzleNo.Name = "comboNozzleNo";
            this.comboNozzleNo.Size = new System.Drawing.Size(67, 20);
            this.comboNozzleNo.TabIndex = 14;
            this.comboNozzleNo.SelectedIndexChanged += new System.EventHandler(this.comboNozzleNo_SelectedIndexChanged);
            // 
            // btnDeleteCurve
            // 
            this.btnDeleteCurve.Location = new System.Drawing.Point(256, 22);
            this.btnDeleteCurve.Name = "btnDeleteCurve";
            this.btnDeleteCurve.Size = new System.Drawing.Size(75, 23);
            this.btnDeleteCurve.TabIndex = 13;
            this.btnDeleteCurve.Text = "删除识别区";
            this.btnDeleteCurve.UseVisualStyleBackColor = true;
            this.btnDeleteCurve.Click += new System.EventHandler(this.btnDeleteCurve_Click);
            // 
            // btnSaveCurve
            // 
            this.btnSaveCurve.Location = new System.Drawing.Point(156, 54);
            this.btnSaveCurve.Name = "btnSaveCurve";
            this.btnSaveCurve.Size = new System.Drawing.Size(75, 23);
            this.btnSaveCurve.TabIndex = 12;
            this.btnSaveCurve.Text = "保  存";
            this.btnSaveCurve.UseVisualStyleBackColor = true;
            this.btnSaveCurve.Click += new System.EventHandler(this.btnSaveCurve_Click);
            // 
            // btnAddCurve
            // 
            this.btnAddCurve.Location = new System.Drawing.Point(53, 22);
            this.btnAddCurve.Name = "btnAddCurve";
            this.btnAddCurve.Size = new System.Drawing.Size(75, 23);
            this.btnAddCurve.TabIndex = 11;
            this.btnAddCurve.Text = "添加识别区";
            this.btnAddCurve.UseVisualStyleBackColor = true;
            this.btnAddCurve.Click += new System.EventHandler(this.btnAddCurve_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(379, 60);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "油枪号：";
            // 
            // videoBox
            // 
            this.videoBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("videoBox.BackgroundImage")));
            this.videoBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.videoBox.Location = new System.Drawing.Point(6, 127);
            this.videoBox.Name = "videoBox";
            this.videoBox.Size = new System.Drawing.Size(800, 450);
            this.videoBox.TabIndex = 0;
            this.videoBox.TabStop = false;
            this.videoBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.videoBox_MouseDown);
            this.videoBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.videoBox_MouseMove);
            this.videoBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.videoBox_MouseUp);
            // 
            // contextTreeAdd
            // 
            this.contextTreeAdd.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addDevice});
            this.contextTreeAdd.Name = "contextTreeMenu";
            this.contextTreeAdd.Size = new System.Drawing.Size(125, 26);
            this.contextTreeAdd.MouseClick += new System.Windows.Forms.MouseEventHandler(this.contextTreeMenu_MouseClick);
            // 
            // addDevice
            // 
            this.addDevice.Name = "addDevice";
            this.addDevice.Size = new System.Drawing.Size(124, 22);
            this.addDevice.Text = "添加设备";
            this.addDevice.Click += new System.EventHandler(this.addDevice_Click);
            // 
            // treeMain
            // 
            this.treeMain.Location = new System.Drawing.Point(13, 111);
            this.treeMain.Name = "treeMain";
            this.treeMain.Size = new System.Drawing.Size(162, 572);
            this.treeMain.TabIndex = 4;
            this.treeMain.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.treeDevice_NodeMouseClick);
            this.treeMain.DoubleClick += new System.EventHandler(this.treeMain_DoubleClick);
            // 
            // timerCurve
            // 
            this.timerCurve.Enabled = true;
            this.timerCurve.Interval = 20;
            this.timerCurve.Tick += new System.EventHandler(this.timerCurve_Tick);
            // 
            // contextMenuDelete
            // 
            this.contextMenuDelete.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1});
            this.contextMenuDelete.Name = "contextMenuDelete";
            this.contextMenuDelete.Size = new System.Drawing.Size(125, 26);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(124, 22);
            this.toolStripMenuItem1.Text = "删除设备";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.lblStationName,
            this.toolStripStatusLabel2,
            this.lblCurVideoNo});
            this.statusStrip1.Location = new System.Drawing.Point(0, 860);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1008, 22);
            this.statusStrip1.TabIndex = 5;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(68, 17);
            this.toolStripStatusLabel1.Text = "站点名称：";
            // 
            // lblStationName
            // 
            this.lblStationName.Name = "lblStationName";
            this.lblStationName.Size = new System.Drawing.Size(44, 17);
            this.lblStationName.Text = "测试站";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(28, 17);
            this.toolStripStatusLabel2.Text = "     ";
            // 
            // lblCurVideoNo
            // 
            this.lblCurVideoNo.Name = "lblCurVideoNo";
            this.lblCurVideoNo.Size = new System.Drawing.Size(68, 17);
            this.lblCurVideoNo.Text = "当前视频：";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(13, 87);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(77, 12);
            this.label8.TabIndex = 26;
            this.label8.Text = "已关联油枪：";
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 882);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.treeMain);
            this.Controls.Add(this.groupBoxSet);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FormMain";
            this.Text = "智能加油站系统初始化工具";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormMain_FormClosed);
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBoxSet.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.videoBox)).EndInit();
            this.contextTreeAdd.ResumeLayout(false);
            this.contextMenuDelete.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textDBPwd;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textDBAdmin;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textDBIP;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboDBType;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.GroupBox groupBoxSet;
        private System.Windows.Forms.ContextMenuStrip contextTreeAdd;
        private System.Windows.Forms.ToolStripMenuItem addDevice;
        private System.Windows.Forms.TreeView treeMain;
        private System.Windows.Forms.PictureBox videoBox;
        private System.Windows.Forms.TextBox textDBName;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Timer timerCurve;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btnAddCurve;
        private System.Windows.Forms.Button btnSaveCurve;
        private System.Windows.Forms.Button btnDeleteCurve;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox comboNozzleNo;
        private System.Windows.Forms.Button btnChangeCurve;
        private System.Windows.Forms.ComboBox comboOilType;
        private System.Windows.Forms.Label lblAction;
        private System.Windows.Forms.ContextMenuStrip contextMenuDelete;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnSetInfo;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel lblStationName;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel lblCurVideoNo;
        private System.Windows.Forms.Button btnDeleteNozzle;
        private System.Windows.Forms.Button btnAddNozzle;
        private System.Windows.Forms.ComboBox comboArea;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
    }
}

