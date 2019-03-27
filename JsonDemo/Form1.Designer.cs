namespace JsonDemo
{
    partial class Form1
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
            this.btn_test = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.txtIP = new System.Windows.Forms.TextBox();
            this.txtPort = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textTotalCount = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textCurrentCount = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textVersion = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.comboStatus = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.textTotal = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textCurrent = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textIP = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textCode = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textName = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btn_test
            // 
            this.btn_test.Location = new System.Drawing.Point(367, 21);
            this.btn_test.Name = "btn_test";
            this.btn_test.Size = new System.Drawing.Size(75, 21);
            this.btn_test.TabIndex = 0;
            this.btn_test.Text = "发送";
            this.btn_test.UseVisualStyleBackColor = true;
            this.btn_test.Click += new System.EventHandler(this.btn_test_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "服务IP：";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // txtIP
            // 
            this.txtIP.Location = new System.Drawing.Point(57, 22);
            this.txtIP.Name = "txtIP";
            this.txtIP.Size = new System.Drawing.Size(86, 21);
            this.txtIP.TabIndex = 2;
            this.txtIP.Text = "127.0.0.1";
            this.txtIP.TextChanged += new System.EventHandler(this.txtIP_TextChanged);
            // 
            // txtPort
            // 
            this.txtPort.Location = new System.Drawing.Point(191, 22);
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(45, 21);
            this.txtPort.TabIndex = 4;
            this.txtPort.Text = "6700";
            this.txtPort.TextChanged += new System.EventHandler(this.txtPort_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(153, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "端口：";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textTotalCount);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.textCurrentCount);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.textVersion);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.comboStatus);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.textTotal);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.textCurrent);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.textIP);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.textCode);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.textName);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Location = new System.Drawing.Point(12, 59);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(436, 299);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "订单数据";
            // 
            // textTotalCount
            // 
            this.textTotalCount.Location = new System.Drawing.Point(299, 108);
            this.textTotalCount.Name = "textTotalCount";
            this.textTotalCount.Size = new System.Drawing.Size(131, 21);
            this.textTotalCount.TabIndex = 22;
            this.textTotalCount.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(226, 113);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(59, 12);
            this.label10.TabIndex = 21;
            this.label10.Text = "车辆总数:";
            // 
            // textCurrentCount
            // 
            this.textCurrentCount.Location = new System.Drawing.Point(81, 108);
            this.textCurrentCount.Name = "textCurrentCount";
            this.textCurrentCount.Size = new System.Drawing.Size(131, 21);
            this.textCurrentCount.TabIndex = 20;
            this.textCurrentCount.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(8, 113);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(71, 12);
            this.label11.TabIndex = 19;
            this.label11.Text = "当天车辆数:";
            // 
            // textVersion
            // 
            this.textVersion.Location = new System.Drawing.Point(81, 179);
            this.textVersion.Name = "textVersion";
            this.textVersion.Size = new System.Drawing.Size(131, 21);
            this.textVersion.TabIndex = 18;
            this.textVersion.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(8, 184);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(59, 12);
            this.label8.TabIndex = 17;
            this.label8.Text = "软件版本:";
            // 
            // comboStatus
            // 
            this.comboStatus.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboStatus.FormattingEnabled = true;
            this.comboStatus.Items.AddRange(new object[] {
            "正常",
            "设备故障",
            "DIT通讯故障"});
            this.comboStatus.Location = new System.Drawing.Point(299, 76);
            this.comboStatus.Name = "comboStatus";
            this.comboStatus.Size = new System.Drawing.Size(121, 20);
            this.comboStatus.TabIndex = 16;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(226, 76);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(59, 12);
            this.label9.TabIndex = 15;
            this.label9.Text = "当前状态:";
            // 
            // textTotal
            // 
            this.textTotal.Location = new System.Drawing.Point(299, 143);
            this.textTotal.Name = "textTotal";
            this.textTotal.Size = new System.Drawing.Size(131, 21);
            this.textTotal.TabIndex = 12;
            this.textTotal.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(226, 148);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 12);
            this.label7.TabIndex = 11;
            this.label7.Text = "总匹配率:";
            // 
            // textCurrent
            // 
            this.textCurrent.Location = new System.Drawing.Point(81, 143);
            this.textCurrent.Name = "textCurrent";
            this.textCurrent.Size = new System.Drawing.Size(131, 21);
            this.textCurrent.TabIndex = 10;
            this.textCurrent.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(8, 148);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(71, 12);
            this.label6.TabIndex = 9;
            this.label6.Text = "当天匹配率:";
            // 
            // textIP
            // 
            this.textIP.Location = new System.Drawing.Point(81, 71);
            this.textIP.Name = "textIP";
            this.textIP.Size = new System.Drawing.Size(131, 21);
            this.textIP.TabIndex = 8;
            this.textIP.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 76);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 12);
            this.label5.TabIndex = 7;
            this.label5.Text = "站点IP:";
            // 
            // textCode
            // 
            this.textCode.Location = new System.Drawing.Point(299, 33);
            this.textCode.Name = "textCode";
            this.textCode.Size = new System.Drawing.Size(131, 21);
            this.textCode.TabIndex = 6;
            this.textCode.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(226, 38);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 12);
            this.label4.TabIndex = 5;
            this.label4.Text = "站点编码:";
            // 
            // textName
            // 
            this.textName.Location = new System.Drawing.Point(81, 33);
            this.textName.Name = "textName";
            this.textName.Size = new System.Drawing.Size(131, 21);
            this.textName.TabIndex = 4;
            this.textName.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 38);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "站点名称:";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(286, 21);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 21);
            this.button1.TabIndex = 7;
            this.button1.Text = "测试";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(231, -1);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 21);
            this.button2.TabIndex = 8;
            this.button2.Text = "初始化";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(459, 397);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.txtPort);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtIP);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btn_test);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btn_test;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtIP;
        private System.Windows.Forms.TextBox txtPort;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox textName;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboStatus;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textTotal;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textCurrent;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textIP;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textCode;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textVersion;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textTotalCount;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textCurrentCount;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}

