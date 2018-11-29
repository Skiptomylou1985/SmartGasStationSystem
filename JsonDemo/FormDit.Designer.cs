namespace JsonDemo
{
    partial class FormDit
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
            this.txtPort = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtIP = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_link = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btn_test = new System.Windows.Forms.Button();
            this.comboBodyColor = new System.Windows.Forms.ComboBox();
            this.comboVehicleColor = new System.Windows.Forms.ComboBox();
            this.comboVehicleModel = new System.Windows.Forms.ComboBox();
            this.comboFlag = new System.Windows.Forms.ComboBox();
            this.lblTime = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.textSubBrand = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textVehicleBrand = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.textVehicleNo = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.btn_send = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.lblPumpTime = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.lblValue = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.lblVolume = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.lblGradeID = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.lblPumpFlag = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.lblPumpId = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.txtServerPort = new System.Windows.Forms.TextBox();
            this.btn_open = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.timerDit = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtPort
            // 
            this.txtPort.Location = new System.Drawing.Point(238, 33);
            this.txtPort.Name = "txtPort";
            this.txtPort.Size = new System.Drawing.Size(45, 21);
            this.txtPort.TabIndex = 9;
            this.txtPort.Text = "9101";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(200, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "端口：";
            // 
            // txtIP
            // 
            this.txtIP.Location = new System.Drawing.Point(82, 33);
            this.txtIP.Name = "txtIP";
            this.txtIP.Size = new System.Drawing.Size(86, 21);
            this.txtIP.TabIndex = 7;
            this.txtIP.Text = "11.0.27.211";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(29, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 6;
            this.label1.Text = "服务IP：";
            // 
            // btn_link
            // 
            this.btn_link.Location = new System.Drawing.Point(297, 32);
            this.btn_link.Name = "btn_link";
            this.btn_link.Size = new System.Drawing.Size(75, 21);
            this.btn_link.TabIndex = 5;
            this.btn_link.Text = "连接";
            this.btn_link.UseVisualStyleBackColor = true;
            this.btn_link.Click += new System.EventHandler(this.btn_link_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btn_test);
            this.groupBox1.Controls.Add(this.comboBodyColor);
            this.groupBox1.Controls.Add(this.comboVehicleColor);
            this.groupBox1.Controls.Add(this.comboVehicleModel);
            this.groupBox1.Controls.Add(this.comboFlag);
            this.groupBox1.Controls.Add(this.lblTime);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.textSubBrand);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.textVehicleBrand);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.textVehicleNo);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.btn_send);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtPort);
            this.groupBox1.Controls.Add(this.btn_link);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.txtIP);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(483, 180);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = " 发送至DIT";
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // btn_test
            // 
            this.btn_test.Location = new System.Drawing.Point(388, 81);
            this.btn_test.Name = "btn_test";
            this.btn_test.Size = new System.Drawing.Size(75, 21);
            this.btn_test.TabIndex = 30;
            this.btn_test.Text = "测试";
            this.btn_test.UseVisualStyleBackColor = true;
            this.btn_test.Click += new System.EventHandler(this.btn_test_Click);
            // 
            // comboBodyColor
            // 
            this.comboBodyColor.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBodyColor.FormattingEnabled = true;
            this.comboBodyColor.Items.AddRange(new object[] {
            "蓝色",
            "黄色",
            "绿色",
            "白色",
            "黑色"});
            this.comboBodyColor.Location = new System.Drawing.Point(238, 141);
            this.comboBodyColor.Name = "comboBodyColor";
            this.comboBodyColor.Size = new System.Drawing.Size(86, 20);
            this.comboBodyColor.TabIndex = 29;
            // 
            // comboVehicleColor
            // 
            this.comboVehicleColor.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboVehicleColor.FormattingEnabled = true;
            this.comboVehicleColor.Items.AddRange(new object[] {
            "白色",
            "黑色",
            "红色",
            "蓝色",
            "灰色",
            "棕色",
            "绿色",
            "金色"});
            this.comboVehicleColor.Location = new System.Drawing.Point(82, 141);
            this.comboVehicleColor.Name = "comboVehicleColor";
            this.comboVehicleColor.Size = new System.Drawing.Size(86, 20);
            this.comboVehicleColor.TabIndex = 28;
            // 
            // comboVehicleModel
            // 
            this.comboVehicleModel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboVehicleModel.FormattingEnabled = true;
            this.comboVehicleModel.Items.AddRange(new object[] {
            "小汽车",
            "面包车",
            "卡车",
            "巴士",
            "拖挂车"});
            this.comboVehicleModel.Location = new System.Drawing.Point(238, 115);
            this.comboVehicleModel.Name = "comboVehicleModel";
            this.comboVehicleModel.Size = new System.Drawing.Size(86, 20);
            this.comboVehicleModel.TabIndex = 27;
            // 
            // comboFlag
            // 
            this.comboFlag.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboFlag.FormattingEnabled = true;
            this.comboFlag.Items.AddRange(new object[] {
            "进站",
            "出站"});
            this.comboFlag.Location = new System.Drawing.Point(82, 60);
            this.comboFlag.Name = "comboFlag";
            this.comboFlag.Size = new System.Drawing.Size(86, 20);
            this.comboFlag.TabIndex = 26;
            // 
            // lblTime
            // 
            this.lblTime.AutoSize = true;
            this.lblTime.Location = new System.Drawing.Point(265, 66);
            this.lblTime.Name = "lblTime";
            this.lblTime.Size = new System.Drawing.Size(29, 12);
            this.lblTime.TabIndex = 25;
            this.lblTime.Text = "    ";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(176, 144);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(59, 12);
            this.label10.TabIndex = 24;
            this.label10.Text = "车牌颜色:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(20, 144);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(59, 12);
            this.label11.TabIndex = 22;
            this.label11.Text = "车辆颜色:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(188, 117);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(47, 12);
            this.label9.TabIndex = 20;
            this.label9.Text = "  车型:";
            // 
            // textSubBrand
            // 
            this.textSubBrand.Location = new System.Drawing.Point(82, 114);
            this.textSubBrand.Name = "textSubBrand";
            this.textSubBrand.Size = new System.Drawing.Size(86, 21);
            this.textSubBrand.TabIndex = 19;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(32, 117);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(47, 12);
            this.label8.TabIndex = 18;
            this.label8.Text = "子品牌:";
            // 
            // textVehicleBrand
            // 
            this.textVehicleBrand.Location = new System.Drawing.Point(238, 90);
            this.textVehicleBrand.Name = "textVehicleBrand";
            this.textVehicleBrand.Size = new System.Drawing.Size(80, 21);
            this.textVehicleBrand.TabIndex = 17;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(188, 93);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(47, 12);
            this.label7.TabIndex = 16;
            this.label7.Text = "车品牌:";
            // 
            // textVehicleNo
            // 
            this.textVehicleNo.Location = new System.Drawing.Point(82, 87);
            this.textVehicleNo.Name = "textVehicleNo";
            this.textVehicleNo.Size = new System.Drawing.Size(86, 21);
            this.textVehicleNo.TabIndex = 15;
            this.textVehicleNo.Text = "京A12345";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(32, 90);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(47, 12);
            this.label6.TabIndex = 14;
            this.label6.Text = "车牌号:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(188, 66);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(71, 12);
            this.label5.TabIndex = 13;
            this.label5.Text = "进出站时间:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(32, 63);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 11;
            this.label3.Text = "进出站:";
            // 
            // btn_send
            // 
            this.btn_send.Location = new System.Drawing.Point(388, 32);
            this.btn_send.Name = "btn_send";
            this.btn_send.Size = new System.Drawing.Size(75, 21);
            this.btn_send.TabIndex = 10;
            this.btn_send.Text = "发送进出站";
            this.btn_send.UseVisualStyleBackColor = true;
            this.btn_send.Click += new System.EventHandler(this.btn_send_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.lblPumpTime);
            this.groupBox2.Controls.Add(this.label19);
            this.groupBox2.Controls.Add(this.lblValue);
            this.groupBox2.Controls.Add(this.label21);
            this.groupBox2.Controls.Add(this.lblVolume);
            this.groupBox2.Controls.Add(this.label15);
            this.groupBox2.Controls.Add(this.lblGradeID);
            this.groupBox2.Controls.Add(this.label17);
            this.groupBox2.Controls.Add(this.lblPumpFlag);
            this.groupBox2.Controls.Add(this.label14);
            this.groupBox2.Controls.Add(this.lblPumpId);
            this.groupBox2.Controls.Add(this.label12);
            this.groupBox2.Controls.Add(this.txtServerPort);
            this.groupBox2.Controls.Add(this.btn_open);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Location = new System.Drawing.Point(12, 198);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(483, 180);
            this.groupBox2.TabIndex = 11;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "接收DIT信号";
            // 
            // lblPumpTime
            // 
            this.lblPumpTime.AutoSize = true;
            this.lblPumpTime.Location = new System.Drawing.Point(241, 112);
            this.lblPumpTime.Name = "lblPumpTime";
            this.lblPumpTime.Size = new System.Drawing.Size(11, 12);
            this.lblPumpTime.TabIndex = 34;
            this.lblPumpTime.Text = "0";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(180, 112);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(59, 12);
            this.label19.TabIndex = 33;
            this.label19.Text = "提挂时间:";
            // 
            // lblValue
            // 
            this.lblValue.AutoSize = true;
            this.lblValue.Location = new System.Drawing.Point(76, 112);
            this.lblValue.Name = "lblValue";
            this.lblValue.Size = new System.Drawing.Size(11, 12);
            this.lblValue.TabIndex = 32;
            this.lblValue.Text = "0";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(11, 112);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(59, 12);
            this.label21.TabIndex = 31;
            this.label21.Text = "加油金额:";
            // 
            // lblVolume
            // 
            this.lblVolume.AutoSize = true;
            this.lblVolume.Location = new System.Drawing.Point(241, 87);
            this.lblVolume.Name = "lblVolume";
            this.lblVolume.Size = new System.Drawing.Size(11, 12);
            this.lblVolume.TabIndex = 30;
            this.lblVolume.Text = "0";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(180, 87);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(59, 12);
            this.label15.TabIndex = 29;
            this.label15.Text = "加油升数:";
            // 
            // lblGradeID
            // 
            this.lblGradeID.AutoSize = true;
            this.lblGradeID.Location = new System.Drawing.Point(76, 87);
            this.lblGradeID.Name = "lblGradeID";
            this.lblGradeID.Size = new System.Drawing.Size(11, 12);
            this.lblGradeID.TabIndex = 28;
            this.lblGradeID.Text = "0";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(23, 87);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(47, 12);
            this.label17.TabIndex = 27;
            this.label17.Text = "油品号:";
            // 
            // lblPumpFlag
            // 
            this.lblPumpFlag.AutoSize = true;
            this.lblPumpFlag.Location = new System.Drawing.Point(241, 61);
            this.lblPumpFlag.Name = "lblPumpFlag";
            this.lblPumpFlag.Size = new System.Drawing.Size(11, 12);
            this.lblPumpFlag.TabIndex = 26;
            this.lblPumpFlag.Text = "0";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(180, 61);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(59, 12);
            this.label14.TabIndex = 25;
            this.label14.Text = "油枪标识:";
            // 
            // lblPumpId
            // 
            this.lblPumpId.AutoSize = true;
            this.lblPumpId.Location = new System.Drawing.Point(76, 61);
            this.lblPumpId.Name = "lblPumpId";
            this.lblPumpId.Size = new System.Drawing.Size(11, 12);
            this.lblPumpId.TabIndex = 24;
            this.lblPumpId.Text = "0";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(23, 61);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(47, 12);
            this.label12.TabIndex = 23;
            this.label12.Text = "油枪号:";
            // 
            // txtServerPort
            // 
            this.txtServerPort.Location = new System.Drawing.Point(58, 21);
            this.txtServerPort.Name = "txtServerPort";
            this.txtServerPort.Size = new System.Drawing.Size(45, 21);
            this.txtServerPort.TabIndex = 9;
            this.txtServerPort.Text = "9100";
            // 
            // btn_open
            // 
            this.btn_open.Location = new System.Drawing.Point(139, 20);
            this.btn_open.Name = "btn_open";
            this.btn_open.Size = new System.Drawing.Size(75, 21);
            this.btn_open.TabIndex = 5;
            this.btn_open.Text = "开启服务";
            this.btn_open.UseVisualStyleBackColor = true;
            this.btn_open.Click += new System.EventHandler(this.btn_open_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(20, 24);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 8;
            this.label4.Text = "端口：";
            // 
            // timerDit
            // 
            this.timerDit.Interval = 50;
            this.timerDit.Tick += new System.EventHandler(this.timerDit_Tick);
            // 
            // FormDit
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(507, 388);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "FormDit";
            this.Text = "FormDit";
            this.Load += new System.EventHandler(this.FormDit_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox txtPort;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtIP;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_link;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btn_send;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox txtServerPort;
        private System.Windows.Forms.Button btn_open;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboFlag;
        private System.Windows.Forms.Label lblTime;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textSubBrand;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textVehicleBrand;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textVehicleNo;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBodyColor;
        private System.Windows.Forms.ComboBox comboVehicleColor;
        private System.Windows.Forms.ComboBox comboVehicleModel;
        private System.Windows.Forms.Timer timerDit;
        private System.Windows.Forms.Label lblPumpId;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label lblPumpFlag;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label lblPumpTime;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label lblValue;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label lblVolume;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label lblGradeID;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Button btn_test;
    }
}