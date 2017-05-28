namespace DIT_Demo
{
    partial class FormDIT
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
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.btnSetCallback = new System.Windows.Forms.Button();
            this.btnSnap = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.lblPlate = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.comboNozzle = new System.Windows.Forms.ComboBox();
            this.comboNozzleStatus = new System.Windows.Forms.ComboBox();
            this.lblCarColor = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lblCarBrand = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.lblPlateColor = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.lblCarSubBrand = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.lblCarType = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.lblInOut = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.textIP = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(14, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(90, 36);
            this.button1.TabIndex = 0;
            this.button1.Text = "初始化连接";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(221, 12);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(90, 36);
            this.button2.TabIndex = 1;
            this.button2.Text = "关闭";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // btnSetCallback
            // 
            this.btnSetCallback.Location = new System.Drawing.Point(117, 12);
            this.btnSetCallback.Name = "btnSetCallback";
            this.btnSetCallback.Size = new System.Drawing.Size(90, 36);
            this.btnSetCallback.TabIndex = 3;
            this.btnSetCallback.Text = "注册回调";
            this.btnSetCallback.UseVisualStyleBackColor = true;
            this.btnSetCallback.Click += new System.EventHandler(this.btnSetCallback_Click);
            // 
            // btnSnap
            // 
            this.btnSnap.Location = new System.Drawing.Point(209, 66);
            this.btnSnap.Name = "btnSnap";
            this.btnSnap.Size = new System.Drawing.Size(87, 49);
            this.btnSnap.TabIndex = 4;
            this.btnSnap.Text = "抓拍";
            this.btnSnap.UseVisualStyleBackColor = true;
            this.btnSnap.Click += new System.EventHandler(this.btnSnap_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(26, 130);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 5;
            this.label1.Text = "车牌结果：";
            // 
            // lblPlate
            // 
            this.lblPlate.AutoSize = true;
            this.lblPlate.Location = new System.Drawing.Point(105, 130);
            this.lblPlate.Name = "lblPlate";
            this.lblPlate.Size = new System.Drawing.Size(23, 12);
            this.lblPlate.TabIndex = 6;
            this.lblPlate.Text = "abc";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(34, 98);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "油枪状态：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(44, 71);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 7;
            this.label3.Text = "油枪号：";
            // 
            // comboNozzle
            // 
            this.comboNozzle.AutoCompleteCustomSource.AddRange(new string[] {
            "不生效",
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
            "16"});
            this.comboNozzle.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboNozzle.FormattingEnabled = true;
            this.comboNozzle.Items.AddRange(new object[] {
            "0",
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
            "16"});
            this.comboNozzle.Location = new System.Drawing.Point(103, 66);
            this.comboNozzle.Name = "comboNozzle";
            this.comboNozzle.Size = new System.Drawing.Size(92, 20);
            this.comboNozzle.TabIndex = 9;
            // 
            // comboNozzleStatus
            // 
            this.comboNozzleStatus.AutoCompleteCustomSource.AddRange(new string[] {
            "不生效",
            "提枪",
            "加油",
            "挂枪"});
            this.comboNozzleStatus.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboNozzleStatus.FormattingEnabled = true;
            this.comboNozzleStatus.Items.AddRange(new object[] {
            "不生效",
            "提枪",
            "开始加油",
            "挂枪"});
            this.comboNozzleStatus.Location = new System.Drawing.Point(103, 95);
            this.comboNozzleStatus.Name = "comboNozzleStatus";
            this.comboNozzleStatus.Size = new System.Drawing.Size(92, 20);
            this.comboNozzleStatus.TabIndex = 10;
            // 
            // lblCarColor
            // 
            this.lblCarColor.AutoSize = true;
            this.lblCarColor.Location = new System.Drawing.Point(105, 160);
            this.lblCarColor.Name = "lblCarColor";
            this.lblCarColor.Size = new System.Drawing.Size(23, 12);
            this.lblCarColor.TabIndex = 12;
            this.lblCarColor.Text = "abc";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(26, 160);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 12);
            this.label5.TabIndex = 11;
            this.label5.Text = "车辆颜色：";
            // 
            // lblCarBrand
            // 
            this.lblCarBrand.AutoSize = true;
            this.lblCarBrand.Location = new System.Drawing.Point(255, 160);
            this.lblCarBrand.Name = "lblCarBrand";
            this.lblCarBrand.Size = new System.Drawing.Size(23, 12);
            this.lblCarBrand.TabIndex = 14;
            this.lblCarBrand.Text = "abc";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(176, 160);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(65, 12);
            this.label7.TabIndex = 13;
            this.label7.Text = "车辆品牌：";
            // 
            // lblPlateColor
            // 
            this.lblPlateColor.AutoSize = true;
            this.lblPlateColor.Location = new System.Drawing.Point(255, 130);
            this.lblPlateColor.Name = "lblPlateColor";
            this.lblPlateColor.Size = new System.Drawing.Size(23, 12);
            this.lblPlateColor.TabIndex = 16;
            this.lblPlateColor.Text = "abc";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(176, 130);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(65, 12);
            this.label9.TabIndex = 15;
            this.label9.Text = "车牌颜色：";
            // 
            // lblCarSubBrand
            // 
            this.lblCarSubBrand.AutoSize = true;
            this.lblCarSubBrand.Location = new System.Drawing.Point(105, 192);
            this.lblCarSubBrand.Name = "lblCarSubBrand";
            this.lblCarSubBrand.Size = new System.Drawing.Size(23, 12);
            this.lblCarSubBrand.TabIndex = 18;
            this.lblCarSubBrand.Text = "abc";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(26, 192);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(65, 12);
            this.label11.TabIndex = 17;
            this.label11.Text = "车子品牌：";
            // 
            // lblCarType
            // 
            this.lblCarType.AutoSize = true;
            this.lblCarType.Location = new System.Drawing.Point(255, 192);
            this.lblCarType.Name = "lblCarType";
            this.lblCarType.Size = new System.Drawing.Size(23, 12);
            this.lblCarType.TabIndex = 20;
            this.lblCarType.Text = "abc";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(176, 192);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(65, 12);
            this.label12.TabIndex = 19;
            this.label12.Text = "车辆类型：";
            // 
            // lblInOut
            // 
            this.lblInOut.AutoSize = true;
            this.lblInOut.Location = new System.Drawing.Point(105, 220);
            this.lblInOut.Name = "lblInOut";
            this.lblInOut.Size = new System.Drawing.Size(23, 12);
            this.lblInOut.TabIndex = 22;
            this.lblInOut.Text = "abc";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(14, 220);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(77, 12);
            this.label6.TabIndex = 21;
            this.label6.Text = "进出站标识：";
            // 
            // textIP
            // 
            this.textIP.Location = new System.Drawing.Point(178, 211);
            this.textIP.Name = "textIP";
            this.textIP.Size = new System.Drawing.Size(100, 21);
            this.textIP.TabIndex = 23;
            this.textIP.Text = "127.0.0.1";
            // 
            // FormDIT
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(332, 241);
            this.Controls.Add(this.textIP);
            this.Controls.Add(this.lblInOut);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.lblCarType);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.lblCarSubBrand);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.lblPlateColor);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.lblCarBrand);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.lblCarColor);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.comboNozzleStatus);
            this.Controls.Add(this.comboNozzle);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lblPlate);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnSnap);
            this.Controls.Add(this.btnSetCallback);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Name = "FormDIT";
            this.Text = "DIT模拟客户端";
            this.Load += new System.EventHandler(this.FormDIT_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button btnSetCallback;
        private System.Windows.Forms.Button btnSnap;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblPlate;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboNozzle;
        private System.Windows.Forms.ComboBox comboNozzleStatus;
        private System.Windows.Forms.Label lblCarColor;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lblCarBrand;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label lblPlateColor;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label lblCarSubBrand;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label lblCarType;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label lblInOut;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textIP;
    }
}

