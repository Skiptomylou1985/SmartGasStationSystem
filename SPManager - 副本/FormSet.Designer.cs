namespace SPManager
{
    partial class FormSet
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
            this.btnOK = new System.Windows.Forms.Button();
            this.btnCancel = new System.Windows.Forms.Button();
            this.lblKind = new System.Windows.Forms.Label();
            this.comboMain = new System.Windows.Forms.ComboBox();
            this.checkUse = new System.Windows.Forms.CheckBox();
            this.comboSub = new System.Windows.Forms.ComboBox();
            this.lblSub = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(31, 79);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 0;
            this.btnOK.Text = "确定";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnCancel
            // 
            this.btnCancel.Location = new System.Drawing.Point(137, 79);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(82, 23);
            this.btnCancel.TabIndex = 1;
            this.btnCancel.Text = "取消";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // lblKind
            // 
            this.lblKind.AutoSize = true;
            this.lblKind.Location = new System.Drawing.Point(83, 23);
            this.lblKind.Name = "lblKind";
            this.lblKind.Size = new System.Drawing.Size(71, 12);
            this.lblKind.TabIndex = 2;
            this.lblKind.Text = "关联油枪号:";
            this.lblKind.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // comboMain
            // 
            this.comboMain.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboMain.FormattingEnabled = true;
            this.comboMain.Items.AddRange(new object[] {
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
            this.comboMain.Location = new System.Drawing.Point(157, 20);
            this.comboMain.Name = "comboMain";
            this.comboMain.Size = new System.Drawing.Size(81, 20);
            this.comboMain.TabIndex = 3;
            // 
            // checkUse
            // 
            this.checkUse.AutoSize = true;
            this.checkUse.Location = new System.Drawing.Point(12, 21);
            this.checkUse.Name = "checkUse";
            this.checkUse.Size = new System.Drawing.Size(48, 16);
            this.checkUse.TabIndex = 4;
            this.checkUse.Text = "启用";
            this.checkUse.UseVisualStyleBackColor = true;
            this.checkUse.CheckedChanged += new System.EventHandler(this.checkUse_CheckedChanged);
            // 
            // comboSub
            // 
            this.comboSub.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboSub.FormattingEnabled = true;
            this.comboSub.Items.AddRange(new object[] {
            "识别区1",
            "识别区2",
            "识别区3",
            "识别区4"});
            this.comboSub.Location = new System.Drawing.Point(157, 46);
            this.comboSub.Name = "comboSub";
            this.comboSub.Size = new System.Drawing.Size(81, 20);
            this.comboSub.TabIndex = 6;
            // 
            // lblSub
            // 
            this.lblSub.AutoSize = true;
            this.lblSub.Location = new System.Drawing.Point(83, 49);
            this.lblSub.Name = "lblSub";
            this.lblSub.Size = new System.Drawing.Size(71, 12);
            this.lblSub.TabIndex = 5;
            this.lblSub.Text = "关联识别区:";
            this.lblSub.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // FormSet
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(253, 113);
            this.Controls.Add(this.comboSub);
            this.Controls.Add(this.lblSub);
            this.Controls.Add(this.checkUse);
            this.Controls.Add(this.comboMain);
            this.Controls.Add(this.lblKind);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormSet";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "设置关联信息";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Label lblKind;
        private System.Windows.Forms.ComboBox comboMain;
        private System.Windows.Forms.CheckBox checkUse;
        private System.Windows.Forms.ComboBox comboSub;
        private System.Windows.Forms.Label lblSub;
    }
}