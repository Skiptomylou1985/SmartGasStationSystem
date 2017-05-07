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
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.videoBox = new System.Windows.Forms.PictureBox();
            this.contextTreeMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addDevice = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteDevice = new System.Windows.Forms.ToolStripMenuItem();
            this.treeMain = new System.Windows.Forms.TreeView();
            this.timerCurve = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.videoBox)).BeginInit();
            this.contextTreeMenu.SuspendLayout();
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
            this.textDBName.Text = "gsims";
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
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.videoBox);
            this.groupBox3.Location = new System.Drawing.Point(186, 71);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(810, 647);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "操作界面";
            // 
            // videoBox
            // 
            this.videoBox.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("videoBox.BackgroundImage")));
            this.videoBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.videoBox.Location = new System.Drawing.Point(16, 20);
            this.videoBox.Name = "videoBox";
            this.videoBox.Size = new System.Drawing.Size(782, 471);
            this.videoBox.TabIndex = 0;
            this.videoBox.TabStop = false;
            this.videoBox.MouseDown += new System.Windows.Forms.MouseEventHandler(this.videoBox_MouseDown);
            this.videoBox.MouseMove += new System.Windows.Forms.MouseEventHandler(this.videoBox_MouseMove);
            this.videoBox.MouseUp += new System.Windows.Forms.MouseEventHandler(this.videoBox_MouseUp);
            // 
            // contextTreeMenu
            // 
            this.contextTreeMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addDevice,
            this.deleteDevice});
            this.contextTreeMenu.Name = "contextTreeMenu";
            this.contextTreeMenu.Size = new System.Drawing.Size(125, 48);
            this.contextTreeMenu.MouseClick += new System.Windows.Forms.MouseEventHandler(this.contextTreeMenu_MouseClick);
            // 
            // addDevice
            // 
            this.addDevice.Name = "addDevice";
            this.addDevice.Size = new System.Drawing.Size(124, 22);
            this.addDevice.Text = "添加设备";
            // 
            // deleteDevice
            // 
            this.deleteDevice.Name = "deleteDevice";
            this.deleteDevice.Size = new System.Drawing.Size(124, 22);
            this.deleteDevice.Text = "删除设备";
            // 
            // treeMain
            // 
            this.treeMain.Location = new System.Drawing.Point(13, 81);
            this.treeMain.Name = "treeMain";
            this.treeMain.Size = new System.Drawing.Size(162, 637);
            this.treeMain.TabIndex = 4;
            this.treeMain.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.treeDevice_NodeMouseClick);
            this.treeMain.DoubleClick += new System.EventHandler(this.treeMain_DoubleClick);
            // 
            // timerCurve
            // 
            this.timerCurve.Enabled = true;
            this.timerCurve.Interval = 10;
            this.timerCurve.Tick += new System.EventHandler(this.timerCurve_Tick);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 730);
            this.Controls.Add(this.treeMain);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FormMain";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormMain_FormClosed);
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.videoBox)).EndInit();
            this.contextTreeMenu.ResumeLayout(false);
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
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ContextMenuStrip contextTreeMenu;
        private System.Windows.Forms.ToolStripMenuItem addDevice;
        private System.Windows.Forms.ToolStripMenuItem deleteDevice;
        private System.Windows.Forms.TreeView treeMain;
        private System.Windows.Forms.PictureBox videoBox;
        private System.Windows.Forms.TextBox textDBName;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Timer timerCurve;
    }
}

