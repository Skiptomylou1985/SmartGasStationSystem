namespace ParamSet
{
    partial class FormNVR
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
            this.label1 = new System.Windows.Forms.Label();
            this.textNVRIP = new System.Windows.Forms.TextBox();
            this.textLoginName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.textPassword = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textNVRPort = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.btnOK = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.textName = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.comboDeviceType = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(20, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "设备IP：";
            // 
            // textNVRIP
            // 
            this.textNVRIP.Location = new System.Drawing.Point(75, 12);
            this.textNVRIP.Name = "textNVRIP";
            this.textNVRIP.Size = new System.Drawing.Size(105, 21);
            this.textNVRIP.TabIndex = 1;
            // 
            // textLoginName
            // 
            this.textLoginName.Location = new System.Drawing.Point(75, 48);
            this.textLoginName.Name = "textLoginName";
            this.textLoginName.Size = new System.Drawing.Size(105, 21);
            this.textLoginName.TabIndex = 3;
            this.textLoginName.Text = "admin";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(20, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "登录名：";
            // 
            // textPassword
            // 
            this.textPassword.Location = new System.Drawing.Point(255, 48);
            this.textPassword.Name = "textPassword";
            this.textPassword.Size = new System.Drawing.Size(101, 21);
            this.textPassword.TabIndex = 5;
            this.textPassword.Text = "12345";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(213, 53);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "密码：";
            // 
            // textNVRPort
            // 
            this.textNVRPort.Location = new System.Drawing.Point(255, 12);
            this.textNVRPort.Name = "textNVRPort";
            this.textNVRPort.Size = new System.Drawing.Size(101, 21);
            this.textNVRPort.TabIndex = 7;
            this.textNVRPort.Text = "8000";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(200, 17);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "端口号：";
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(95, 123);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 8;
            this.btnOK.Text = "确认";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(202, 122);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 9;
            this.btnCancel.Text = "取消";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(191, 86);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 12);
            this.label5.TabIndex = 12;
            this.label5.Text = "设备类型：";
            // 
            // textName
            // 
            this.textName.Location = new System.Drawing.Point(75, 81);
            this.textName.Name = "textName";
            this.textName.Size = new System.Drawing.Size(105, 21);
            this.textName.TabIndex = 11;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(20, 86);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 10;
            this.label6.Text = "设备名：";
            // 
            // comboDeviceType
            // 
            this.comboDeviceType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboDeviceType.FormattingEnabled = true;
            this.comboDeviceType.Items.AddRange(new object[] {
            "海康",
            "科达",
            "大华"});
            this.comboDeviceType.Location = new System.Drawing.Point(255, 82);
            this.comboDeviceType.Name = "comboDeviceType";
            this.comboDeviceType.Size = new System.Drawing.Size(101, 20);
            this.comboDeviceType.TabIndex = 14;
            // 
            // FormNVR
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(368, 153);
            this.Controls.Add(this.comboDeviceType);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.textName);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.textNVRPort);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.textPassword);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textLoginName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textNVRIP);
            this.Controls.Add(this.label1);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormNVR";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "添加设备";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textNVRIP;
        private System.Windows.Forms.TextBox textLoginName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textPassword;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textNVRPort;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textName;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox comboDeviceType;
    }
}