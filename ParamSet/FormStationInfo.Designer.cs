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
            this.textPicPath = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.comboLogLevel = new System.Windows.Forms.ComboBox();
            this.label12 = new System.Windows.Forms.Label();
            this.comboMatchMode = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textStationCode = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textStationName = new System.Windows.Forms.TextBox();
            this.btnSetInfo = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.btnSet = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textPicPath
            // 
            this.textPicPath.Location = new System.Drawing.Point(91, 100);
            this.textPicPath.Name = "textPicPath";
            this.textPicPath.Size = new System.Drawing.Size(178, 21);
            this.textPicPath.TabIndex = 31;
            this.textPicPath.Text = "1000";
            this.textPicPath.MouseClick += new System.Windows.Forms.MouseEventHandler(this.textPicPath_MouseClick);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(2, 103);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(89, 12);
            this.label13.TabIndex = 30;
            this.label13.Text = "图片存储路径：";
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
            this.comboLogLevel.Location = new System.Drawing.Point(264, 62);
            this.comboLogLevel.Name = "comboLogLevel";
            this.comboLogLevel.Size = new System.Drawing.Size(95, 20);
            this.comboLogLevel.TabIndex = 29;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(193, 66);
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
            "有出入口相机",
            "无出入口相机"});
            this.comboMatchMode.Location = new System.Drawing.Point(264, 21);
            this.comboMatchMode.Name = "comboMatchMode";
            this.comboMatchMode.Size = new System.Drawing.Size(95, 20);
            this.comboMatchMode.TabIndex = 27;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(193, 25);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(65, 12);
            this.label11.TabIndex = 26;
            this.label11.Text = "站点模式：";
            // 
            // textStationCode
            // 
            this.textStationCode.Location = new System.Drawing.Point(91, 57);
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
            this.textStationName.Location = new System.Drawing.Point(91, 20);
            this.textStationName.Name = "textStationName";
            this.textStationName.Size = new System.Drawing.Size(86, 21);
            this.textStationName.TabIndex = 23;
            this.textStationName.Text = "测试站";
            // 
            // btnSetInfo
            // 
            this.btnSetInfo.Location = new System.Drawing.Point(393, 173);
            this.btnSetInfo.Name = "btnSetInfo";
            this.btnSetInfo.Size = new System.Drawing.Size(73, 23);
            this.btnSetInfo.TabIndex = 22;
            this.btnSetInfo.Text = "设  置";
            this.btnSetInfo.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(26, 62);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 34;
            this.label1.Text = "站点编号：";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(26, 24);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(65, 12);
            this.label9.TabIndex = 32;
            this.label9.Text = "站点名称：";
            // 
            // btnSet
            // 
            this.btnSet.Location = new System.Drawing.Point(70, 144);
            this.btnSet.Name = "btnSet";
            this.btnSet.Size = new System.Drawing.Size(73, 23);
            this.btnSet.TabIndex = 35;
            this.btnSet.Text = "设  置";
            this.btnSet.UseVisualStyleBackColor = true;
            this.btnSet.Click += new System.EventHandler(this.btnSet_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(214, 144);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(73, 23);
            this.btnCancel.TabIndex = 36;
            this.btnCancel.Text = "退  出";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // FormStationInfo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(385, 183);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnSet);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.textPicPath);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.comboLogLevel);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.comboMatchMode);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.textStationCode);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.textStationName);
            this.Controls.Add(this.btnSetInfo);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormStationInfo";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "站点信息设置";
            this.Load += new System.EventHandler(this.FormStationInfo_Load);
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
        private System.Windows.Forms.Button btnSetInfo;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button btnSet;
        private System.Windows.Forms.Button btnCancel;
    }
}