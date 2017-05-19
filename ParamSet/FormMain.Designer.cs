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
            this.btnCancel = new System.Windows.Forms.Button();
            this.comboAreaShow = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
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
            this.groupBox1.SuspendLayout();
            this.groupBoxSet.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.videoBox)).BeginInit();
            this.contextTreeAdd.SuspendLayout();
            this.contextMenuDelete.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
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
            this.groupBox1.Size = new System.Drawing.Size(973, 52);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "数据库";
            // 
            // textDBName
            // 
            this.textDBName.Location = new System.Drawing.Point(621, 17);
            this.textDBName.Name = "textDBName";
            this.textDBName.Size = new System.Drawing.Size(71, 21);
            this.textDBName.TabIndex = 10;
            this.textDBName.Text = "gsims2";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(538, 21);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "数据库名称：";
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(728, 16);
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
            this.comboDBType.Location = new System.Drawing.Point(77, 18);
            this.comboDBType.Name = "comboDBType";
            this.comboDBType.Size = new System.Drawing.Size(73, 20);
            this.comboDBType.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "数据库类型：";
            // 
            // textDBPwd
            // 
            this.textDBPwd.Location = new System.Drawing.Point(440, 18);
            this.textDBPwd.Name = "textDBPwd";
            this.textDBPwd.Size = new System.Drawing.Size(84, 21);
            this.textDBPwd.TabIndex = 5;
            this.textDBPwd.Text = "12345";
            this.textDBPwd.UseSystemPasswordChar = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(393, 22);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "密码：";
            // 
            // textDBAdmin
            // 
            this.textDBAdmin.Location = new System.Drawing.Point(331, 18);
            this.textDBAdmin.Name = "textDBAdmin";
            this.textDBAdmin.Size = new System.Drawing.Size(56, 21);
            this.textDBAdmin.TabIndex = 3;
            this.textDBAdmin.Text = "root";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(279, 23);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "登录名：";
            // 
            // textDBIP
            // 
            this.textDBIP.Location = new System.Drawing.Point(187, 18);
            this.textDBIP.Name = "textDBIP";
            this.textDBIP.Size = new System.Drawing.Size(86, 21);
            this.textDBIP.TabIndex = 1;
            this.textDBIP.Text = "127.0.0.1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(158, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "IP：";
            // 
            // groupBoxSet
            // 
            this.groupBoxSet.Controls.Add(this.groupBox2);
            this.groupBoxSet.Controls.Add(this.videoBox);
            this.groupBoxSet.Location = new System.Drawing.Point(186, 65);
            this.groupBoxSet.Name = "groupBoxSet";
            this.groupBoxSet.Size = new System.Drawing.Size(810, 569);
            this.groupBoxSet.TabIndex = 2;
            this.groupBoxSet.TabStop = false;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnCancel);
            this.groupBox2.Controls.Add(this.comboAreaShow);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.btnChangeCurve);
            this.groupBox2.Controls.Add(this.comboOilType);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.comboNozzleNo);
            this.groupBox2.Controls.Add(this.btnDeleteCurve);
            this.groupBox2.Controls.Add(this.btnSaveCurve);
            this.groupBox2.Controls.Add(this.btnAddCurve);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Location = new System.Drawing.Point(6, 20);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(800, 84);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "油枪出入口关联设置";
            this.groupBox2.Enter += new System.EventHandler(this.groupBox2_Enter);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(242, 39);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 21;
            this.btnCancel.Text = "取  消";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // comboAreaShow
            // 
            this.comboAreaShow.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboAreaShow.FormattingEnabled = true;
            this.comboAreaShow.Items.AddRange(new object[] {
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
            this.comboAreaShow.Location = new System.Drawing.Point(608, 38);
            this.comboAreaShow.Name = "comboAreaShow";
            this.comboAreaShow.Size = new System.Drawing.Size(59, 20);
            this.comboAreaShow.TabIndex = 20;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(573, 43);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(41, 12);
            this.label8.TabIndex = 19;
            this.label8.Text = "显示：";
            // 
            // btnChangeCurve
            // 
            this.btnChangeCurve.Location = new System.Drawing.Point(83, 39);
            this.btnChangeCurve.Name = "btnChangeCurve";
            this.btnChangeCurve.Size = new System.Drawing.Size(75, 23);
            this.btnChangeCurve.TabIndex = 18;
            this.btnChangeCurve.Text = "修改绘图";
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
            this.comboOilType.Location = new System.Drawing.Point(496, 39);
            this.comboOilType.Name = "comboOilType";
            this.comboOilType.Size = new System.Drawing.Size(62, 20);
            this.comboOilType.TabIndex = 17;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(446, 44);
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
            this.comboNozzleNo.Location = new System.Drawing.Point(373, 40);
            this.comboNozzleNo.Name = "comboNozzleNo";
            this.comboNozzleNo.Size = new System.Drawing.Size(67, 20);
            this.comboNozzleNo.TabIndex = 14;
            this.comboNozzleNo.SelectedIndexChanged += new System.EventHandler(this.comboNozzleNo_SelectedIndexChanged);
            // 
            // btnDeleteCurve
            // 
            this.btnDeleteCurve.Location = new System.Drawing.Point(682, 36);
            this.btnDeleteCurve.Name = "btnDeleteCurve";
            this.btnDeleteCurve.Size = new System.Drawing.Size(88, 23);
            this.btnDeleteCurve.TabIndex = 13;
            this.btnDeleteCurve.Text = "删除关联油枪";
            this.btnDeleteCurve.UseVisualStyleBackColor = true;
            this.btnDeleteCurve.Click += new System.EventHandler(this.btnDeleteCurve_Click);
            // 
            // btnSaveCurve
            // 
            this.btnSaveCurve.Location = new System.Drawing.Point(162, 39);
            this.btnSaveCurve.Name = "btnSaveCurve";
            this.btnSaveCurve.Size = new System.Drawing.Size(75, 23);
            this.btnSaveCurve.TabIndex = 12;
            this.btnSaveCurve.Text = "保  存";
            this.btnSaveCurve.UseVisualStyleBackColor = true;
            this.btnSaveCurve.Click += new System.EventHandler(this.btnSaveCurve_Click);
            // 
            // btnAddCurve
            // 
            this.btnAddCurve.Location = new System.Drawing.Point(6, 39);
            this.btnAddCurve.Name = "btnAddCurve";
            this.btnAddCurve.Size = new System.Drawing.Size(75, 23);
            this.btnAddCurve.TabIndex = 11;
            this.btnAddCurve.Text = "添加绘图";
            this.btnAddCurve.UseVisualStyleBackColor = true;
            this.btnAddCurve.Click += new System.EventHandler(this.btnAddCurve_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(326, 43);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "油枪号：";
            // 
            // videoBox
            // 
            this.videoBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("videoBox.BackgroundImage")));
            this.videoBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.videoBox.Location = new System.Drawing.Point(6, 109);
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
            this.treeMain.Location = new System.Drawing.Point(13, 74);
            this.treeMain.Name = "treeMain";
            this.treeMain.Size = new System.Drawing.Size(162, 559);
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
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 642);
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
            this.ResumeLayout(false);

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
        private System.Windows.Forms.ComboBox comboAreaShow;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ContextMenuStrip contextMenuDelete;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.Button btnCancel;
    }
}

