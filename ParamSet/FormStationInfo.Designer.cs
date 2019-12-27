namespace ParamSet
{
    partial class FormStationInfo
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.textPicPath = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.comboLogLevel = new System.Windows.Forms.ComboBox();
            this.label12 = new System.Windows.Forms.Label();
            this.comboMatchMode = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textStationCode = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textStationName = new System.Windows.Forms.TextBox();
            this.btnSetRecogInfo = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.btnSet = new System.Windows.Forms.Button();
            this.comboAuthType = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textFTPServerPwd = new System.Windows.Forms.TextBox();
            this.textFTPServerUsername = new System.Windows.Forms.TextBox();
            this.textFTPServerPort = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.textFTPServerIP = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.comboSavePic = new System.Windows.Forms.ComboBox();
            this.comboCarNumRemedy = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.comboVideoRecogType = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.comboVideoRecog = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.comboCapture = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.bindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).BeginInit();
            this.SuspendLayout();
            // 
            // textPicPath
            // 
            this.textPicPath.Location = new System.Drawing.Point(110, 203);
            this.textPicPath.Name = "textPicPath";
            this.textPicPath.Size = new System.Drawing.Size(178, 21);
            this.textPicPath.TabIndex = 31;
            this.textPicPath.Text = "1000";
            this.textPicPath.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textPicPath_MouseClick);
            this.textPicPath.TextChanged += new System.EventHandler(this.textPicPath_TextChanged);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(22, 206);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(89, 12);
            this.label13.TabIndex = 30;
            this.label13.Text = "图片存储路径：";
            this.label13.Click += new System.EventHandler(this.label13_Click);
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
            this.comboLogLevel.Location = new System.Drawing.Point(108, 65);
            this.comboLogLevel.Name = "comboLogLevel";
            this.comboLogLevel.Size = new System.Drawing.Size(86, 20);
            this.comboLogLevel.TabIndex = 29;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(41, 69);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(65, 12);
            this.label12.TabIndex = 28;
            this.label12.Text = "日志级别：";
            // 
            // comboMatchMode
            // 
            this.comboMatchMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboMatchMode.FormattingEnabled = true;
            this.comboMatchMode.Items.AddRange(new object[] {
            "有出有入",
            "无出无入",
            "有出无入",
            "无出有入"});
            this.comboMatchMode.Location = new System.Drawing.Point(106, 112);
            this.comboMatchMode.Name = "comboMatchMode";
            this.comboMatchMode.Size = new System.Drawing.Size(79, 20);
            this.comboMatchMode.TabIndex = 27;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(29, 116);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(77, 12);
            this.label11.TabIndex = 26;
            this.label11.Text = "出入口相机：";
            // 
            // textStationCode
            // 
            this.textStationCode.Location = new System.Drawing.Point(306, 30);
            this.textStationCode.Name = "textStationCode";
            this.textStationCode.Size = new System.Drawing.Size(86, 21);
            this.textStationCode.TabIndex = 25;
            this.textStationCode.Text = "1000";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(-156, 120);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(65, 12);
            this.label10.TabIndex = 24;
            this.label10.Text = "站点编号：";
            // 
            // textStationName
            // 
            this.textStationName.Location = new System.Drawing.Point(108, 29);
            this.textStationName.Name = "textStationName";
            this.textStationName.Size = new System.Drawing.Size(86, 21);
            this.textStationName.TabIndex = 23;
            this.textStationName.Text = "测试站";
            // 
            // btnSetRecogInfo
            // 
            this.btnSetRecogInfo.Location = new System.Drawing.Point(280, 111);
            this.btnSetRecogInfo.Name = "btnSetRecogInfo";
            this.btnSetRecogInfo.Size = new System.Drawing.Size(73, 23);
            this.btnSetRecogInfo.TabIndex = 22;
            this.btnSetRecogInfo.Text = "设  置";
            this.btnSetRecogInfo.UseVisualStyleBackColor = true;
            this.btnSetRecogInfo.Click += new System.EventHandler(this.btnSetRecogInfo_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(215, 35);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(89, 12);
            this.label1.TabIndex = 34;
            this.label1.Text = "站 点 编 号 ：";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(41, 33);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(65, 12);
            this.label9.TabIndex = 32;
            this.label9.Text = "站点名称：";
            // 
            // btnSet
            // 
            this.btnSet.Location = new System.Drawing.Point(318, 201);
            this.btnSet.Name = "btnSet";
            this.btnSet.Size = new System.Drawing.Size(73, 23);
            this.btnSet.TabIndex = 35;
            this.btnSet.Text = "设  置";
            this.btnSet.UseVisualStyleBackColor = true;
            this.btnSet.Click += new System.EventHandler(this.btnSet_Click);
            // 
            // comboAuthType
            // 
            this.comboAuthType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboAuthType.FormattingEnabled = true;
            this.comboAuthType.Items.AddRange(new object[] {
            "本机授权",
            "网络授权"});
            this.comboAuthType.Location = new System.Drawing.Point(106, 31);
            this.comboAuthType.Name = "comboAuthType";
            this.comboAuthType.Size = new System.Drawing.Size(79, 20);
            this.comboAuthType.TabIndex = 38;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 35);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 12);
            this.label2.TabIndex = 37;
            this.label2.Text = "算法授权模式：";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textFTPServerPwd);
            this.groupBox1.Controls.Add(this.textFTPServerUsername);
            this.groupBox1.Controls.Add(this.textFTPServerPort);
            this.groupBox1.Controls.Add(this.label16);
            this.groupBox1.Controls.Add(this.label15);
            this.groupBox1.Controls.Add(this.label14);
            this.groupBox1.Controls.Add(this.textFTPServerIP);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.comboSavePic);
            this.groupBox1.Controls.Add(this.comboCarNumRemedy);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.textPicPath);
            this.groupBox1.Controls.Add(this.textStationName);
            this.groupBox1.Controls.Add(this.textStationCode);
            this.groupBox1.Controls.Add(this.btnSet);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.label12);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.comboLogLevel);
            this.groupBox1.Controls.Add(this.label13);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(441, 246);
            this.groupBox1.TabIndex = 39;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "站点参数";
            // 
            // textFTPServerPwd
            // 
            this.textFTPServerPwd.Location = new System.Drawing.Point(291, 164);
            this.textFTPServerPwd.Name = "textFTPServerPwd";
            this.textFTPServerPwd.Size = new System.Drawing.Size(100, 21);
            this.textFTPServerPwd.TabIndex = 48;
            // 
            // textFTPServerUsername
            // 
            this.textFTPServerUsername.Location = new System.Drawing.Point(108, 164);
            this.textFTPServerUsername.Name = "textFTPServerUsername";
            this.textFTPServerUsername.Size = new System.Drawing.Size(100, 21);
            this.textFTPServerUsername.TabIndex = 47;
            // 
            // textFTPServerPort
            // 
            this.textFTPServerPort.Location = new System.Drawing.Point(291, 134);
            this.textFTPServerPort.Name = "textFTPServerPort";
            this.textFTPServerPort.Size = new System.Drawing.Size(100, 21);
            this.textFTPServerPort.TabIndex = 46;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(229, 168);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(65, 12);
            this.label16.TabIndex = 45;
            this.label16.Text = "FTP 密码：";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(33, 168);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(77, 12);
            this.label15.TabIndex = 44;
            this.label15.Text = "FTP 用户名：";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(229, 137);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(65, 12);
            this.label14.TabIndex = 43;
            this.label14.Text = "FTP 端口：";
            // 
            // textFTPServerIP
            // 
            this.textFTPServerIP.Location = new System.Drawing.Point(108, 134);
            this.textFTPServerIP.Name = "textFTPServerIP";
            this.textFTPServerIP.Size = new System.Drawing.Size(100, 21);
            this.textFTPServerIP.TabIndex = 42;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(26, 137);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(83, 12);
            this.label8.TabIndex = 41;
            this.label8.Text = "图片FTP地址：";
            // 
            // comboSavePic
            // 
            this.comboSavePic.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboSavePic.FormattingEnabled = true;
            this.comboSavePic.Items.AddRange(new object[] {
            "否",
            "是"});
            this.comboSavePic.Location = new System.Drawing.Point(109, 100);
            this.comboSavePic.Name = "comboSavePic";
            this.comboSavePic.Size = new System.Drawing.Size(86, 20);
            this.comboSavePic.TabIndex = 40;
            // 
            // comboCarNumRemedy
            // 
            this.comboCarNumRemedy.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboCarNumRemedy.FormattingEnabled = true;
            this.comboCarNumRemedy.Items.AddRange(new object[] {
            "否",
            "是"});
            this.comboCarNumRemedy.Location = new System.Drawing.Point(306, 69);
            this.comboCarNumRemedy.Name = "comboCarNumRemedy";
            this.comboCarNumRemedy.Size = new System.Drawing.Size(86, 20);
            this.comboCarNumRemedy.TabIndex = 39;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(215, 69);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(89, 12);
            this.label7.TabIndex = 38;
            this.label7.Text = "是否车牌补偿：";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(18, 103);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(89, 12);
            this.label6.TabIndex = 36;
            this.label6.Text = "是否保存抓图：";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.comboVideoRecogType);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.comboVideoRecog);
            this.groupBox2.Controls.Add(this.label11);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.comboCapture);
            this.groupBox2.Controls.Add(this.comboMatchMode);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.btnSetRecogInfo);
            this.groupBox2.Controls.Add(this.comboAuthType);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Location = new System.Drawing.Point(12, 264);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(441, 153);
            this.groupBox2.TabIndex = 40;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "识别参数";
            this.groupBox2.Enter += new System.EventHandler(this.groupBox2_Enter);
            // 
            // comboVideoRecogType
            // 
            this.comboVideoRecogType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboVideoRecogType.FormattingEnabled = true;
            this.comboVideoRecogType.Items.AddRange(new object[] {
            "文通算法",
            "海康超脑",
            "大华超脑"});
            this.comboVideoRecogType.Location = new System.Drawing.Point(280, 72);
            this.comboVideoRecogType.Name = "comboVideoRecogType";
            this.comboVideoRecogType.Size = new System.Drawing.Size(73, 20);
            this.comboVideoRecogType.TabIndex = 44;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(191, 75);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(89, 12);
            this.label5.TabIndex = 43;
            this.label5.Text = "视频识别方式：";
            // 
            // comboVideoRecog
            // 
            this.comboVideoRecog.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboVideoRecog.FormattingEnabled = true;
            this.comboVideoRecog.Items.AddRange(new object[] {
            "关闭",
            "开启"});
            this.comboVideoRecog.Location = new System.Drawing.Point(106, 72);
            this.comboVideoRecog.Name = "comboVideoRecog";
            this.comboVideoRecog.Size = new System.Drawing.Size(79, 20);
            this.comboVideoRecog.TabIndex = 42;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(41, 76);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 12);
            this.label4.TabIndex = 41;
            this.label4.Text = "视频识别：";
            // 
            // comboCapture
            // 
            this.comboCapture.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboCapture.FormattingEnabled = true;
            this.comboCapture.Items.AddRange(new object[] {
            "关闭",
            "开启"});
            this.comboCapture.Location = new System.Drawing.Point(280, 32);
            this.comboCapture.Name = "comboCapture";
            this.comboCapture.Size = new System.Drawing.Size(73, 20);
            this.comboCapture.TabIndex = 40;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(215, 36);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 39;
            this.label3.Text = "抓拍使能：";
            // 
            // FormStationInfo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(461, 440);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label10);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormStationInfo";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "站点信息设置";
            this.Load += new System.EventHandler(this.FormStationInfo_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textPicPath;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.ComboBox comboLogLevel;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.ComboBox comboMatchMode;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textStationCode;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textStationName;
        private System.Windows.Forms.Button btnSetRecogInfo;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button btnSet;
        private System.Windows.Forms.ComboBox comboAuthType;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ComboBox comboVideoRecogType;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox comboVideoRecog;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboCapture;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.BindingSource bindingSource1;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox comboSavePic;
        private System.Windows.Forms.ComboBox comboCarNumRemedy;
        private System.Windows.Forms.TextBox textFTPServerPwd;
        private System.Windows.Forms.TextBox textFTPServerUsername;
        private System.Windows.Forms.TextBox textFTPServerPort;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox textFTPServerIP;
        private System.Windows.Forms.Label label8;
    }
}