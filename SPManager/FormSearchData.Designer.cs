namespace SPManager
{
    partial class FormSearchData
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
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.dataGridCar = new System.Windows.Forms.DataGridView();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.lblLicense = new System.Windows.Forms.Label();
            this.lblArriveTime = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lblLeaveTime = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.lblNozzleNo = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.lblOilType = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.lblCarLogo = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.textLicense = new System.Windows.Forms.TextBox();
            this.dateArriveBegin = new System.Windows.Forms.DateTimePicker();
            this.timeArriveBegin = new System.Windows.Forms.DateTimePicker();
            this.label14 = new System.Windows.Forms.Label();
            this.timeArriveEnd = new System.Windows.Forms.DateTimePicker();
            this.dateArriveEnd = new System.Windows.Forms.DateTimePicker();
            this.timeLeaveEnd = new System.Windows.Forms.DateTimePicker();
            this.dateLeaveEnd = new System.Windows.Forms.DateTimePicker();
            this.label16 = new System.Windows.Forms.Label();
            this.timeLeaveBegin = new System.Windows.Forms.DateTimePicker();
            this.dateLeaveBegin = new System.Windows.Forms.DateTimePicker();
            this.checkBoxArriveTime = new System.Windows.Forms.CheckBox();
            this.checkBoxLeaveTime = new System.Windows.Forms.CheckBox();
            this.btnQuery = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.pictureBoxArrive = new System.Windows.Forms.PictureBox();
            this.pictureBoxLeave = new System.Windows.Forms.PictureBox();
            this.pictureBoxPump = new System.Windows.Forms.PictureBox();
            this.tableLayoutPanel1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridCar)).BeginInit();
            this.panel1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabControl2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxArrive)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLeave)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxPump)).BeginInit();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.groupBox1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 117F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1424, 862);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.Control;
            this.groupBox1.Controls.Add(this.panel2);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(3, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1418, 111);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "查询条件";
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.SkyBlue;
            this.panel2.Controls.Add(this.btnQuery);
            this.panel2.Controls.Add(this.checkBoxLeaveTime);
            this.panel2.Controls.Add(this.checkBoxArriveTime);
            this.panel2.Controls.Add(this.timeLeaveEnd);
            this.panel2.Controls.Add(this.dateLeaveEnd);
            this.panel2.Controls.Add(this.label16);
            this.panel2.Controls.Add(this.timeLeaveBegin);
            this.panel2.Controls.Add(this.dateLeaveBegin);
            this.panel2.Controls.Add(this.timeArriveEnd);
            this.panel2.Controls.Add(this.dateArriveEnd);
            this.panel2.Controls.Add(this.label14);
            this.panel2.Controls.Add(this.timeArriveBegin);
            this.panel2.Controls.Add(this.dateArriveBegin);
            this.panel2.Controls.Add(this.textLicense);
            this.panel2.Controls.Add(this.label15);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(3, 19);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(1412, 89);
            this.panel2.TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 467F));
            this.tableLayoutPanel2.Controls.Add(this.groupBox3, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.groupBox2, 1, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 120);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(1418, 739);
            this.tableLayoutPanel2.TabIndex = 2;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.panel1);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Location = new System.Drawing.Point(954, 3);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(461, 733);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "车辆详情";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.dataGridCar);
            this.groupBox3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox3.Location = new System.Drawing.Point(3, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(945, 733);
            this.groupBox3.TabIndex = 1;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "车辆信息";
            // 
            // dataGridCar
            // 
            this.dataGridCar.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridCar.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridCar.Location = new System.Drawing.Point(3, 19);
            this.dataGridCar.Name = "dataGridCar";
            this.dataGridCar.RowTemplate.Height = 23;
            this.dataGridCar.Size = new System.Drawing.Size(939, 711);
            this.dataGridCar.TabIndex = 0;
            this.dataGridCar.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridCar_CellClick);
            this.dataGridCar.SelectionChanged += new System.EventHandler(this.dataGridCar_SelectionChanged);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.SkyBlue;
            this.panel1.Controls.Add(this.tabControl2);
            this.panel1.Controls.Add(this.tabControl1);
            this.panel1.Controls.Add(this.lblOilType);
            this.panel1.Controls.Add(this.label11);
            this.panel1.Controls.Add(this.lblCarLogo);
            this.panel1.Controls.Add(this.label13);
            this.panel1.Controls.Add(this.lblNozzleNo);
            this.panel1.Controls.Add(this.label9);
            this.panel1.Controls.Add(this.lblLeaveTime);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Controls.Add(this.lblArriveTime);
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.lblLicense);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 19);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(455, 711);
            this.panel1.TabIndex = 0;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(46, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 14);
            this.label2.TabIndex = 0;
            this.label2.Text = "车牌号：";
            // 
            // lblLicense
            // 
            this.lblLicense.AutoSize = true;
            this.lblLicense.Location = new System.Drawing.Point(115, 36);
            this.lblLicense.Name = "lblLicense";
            this.lblLicense.Size = new System.Drawing.Size(63, 14);
            this.lblLicense.TabIndex = 1;
            this.lblLicense.Text = "京A12345";
            // 
            // lblArriveTime
            // 
            this.lblArriveTime.AutoSize = true;
            this.lblArriveTime.Location = new System.Drawing.Point(300, 36);
            this.lblArriveTime.Name = "lblArriveTime";
            this.lblArriveTime.Size = new System.Drawing.Size(0, 14);
            this.lblArriveTime.TabIndex = 3;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(231, 36);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 14);
            this.label5.TabIndex = 2;
            this.label5.Text = "进站时间：";
            // 
            // lblLeaveTime
            // 
            this.lblLeaveTime.AutoSize = true;
            this.lblLeaveTime.Location = new System.Drawing.Point(300, 72);
            this.lblLeaveTime.Name = "lblLeaveTime";
            this.lblLeaveTime.Size = new System.Drawing.Size(0, 14);
            this.lblLeaveTime.TabIndex = 5;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(231, 72);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(77, 14);
            this.label7.TabIndex = 4;
            this.label7.Text = "出站时间：";
            // 
            // lblNozzleNo
            // 
            this.lblNozzleNo.AutoSize = true;
            this.lblNozzleNo.Location = new System.Drawing.Point(115, 72);
            this.lblNozzleNo.Name = "lblNozzleNo";
            this.lblNozzleNo.Size = new System.Drawing.Size(14, 14);
            this.lblNozzleNo.TabIndex = 7;
            this.lblNozzleNo.Text = "1\r\n";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(46, 72);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(77, 14);
            this.label9.TabIndex = 6;
            this.label9.Text = "加油机号：";
            // 
            // lblOilType
            // 
            this.lblOilType.AutoSize = true;
            this.lblOilType.Location = new System.Drawing.Point(115, 106);
            this.lblOilType.Name = "lblOilType";
            this.lblOilType.Size = new System.Drawing.Size(35, 14);
            this.lblOilType.TabIndex = 11;
            this.lblOilType.Text = "未知";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(46, 106);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(77, 14);
            this.label11.TabIndex = 10;
            this.label11.Text = "加油类型：";
            // 
            // lblCarLogo
            // 
            this.lblCarLogo.AutoSize = true;
            this.lblCarLogo.Location = new System.Drawing.Point(300, 106);
            this.lblCarLogo.Name = "lblCarLogo";
            this.lblCarLogo.Size = new System.Drawing.Size(35, 14);
            this.lblCarLogo.TabIndex = 9;
            this.lblCarLogo.Text = "未知";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(231, 106);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(77, 14);
            this.label13.TabIndex = 8;
            this.label13.Text = "车辆品牌：";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(35, 28);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(63, 14);
            this.label15.TabIndex = 2;
            this.label15.Text = "车牌号：";
            // 
            // textLicense
            // 
            this.textLicense.Location = new System.Drawing.Point(95, 23);
            this.textLicense.Name = "textLicense";
            this.textLicense.Size = new System.Drawing.Size(108, 23);
            this.textLicense.TabIndex = 4;
            // 
            // dateArriveBegin
            // 
            this.dateArriveBegin.Location = new System.Drawing.Point(310, 24);
            this.dateArriveBegin.Name = "dateArriveBegin";
            this.dateArriveBegin.Size = new System.Drawing.Size(118, 23);
            this.dateArriveBegin.TabIndex = 6;
            // 
            // timeArriveBegin
            // 
            this.timeArriveBegin.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.timeArriveBegin.Location = new System.Drawing.Point(434, 24);
            this.timeArriveBegin.Name = "timeArriveBegin";
            this.timeArriveBegin.Size = new System.Drawing.Size(99, 23);
            this.timeArriveBegin.TabIndex = 7;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(539, 36);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(14, 14);
            this.label14.TabIndex = 8;
            this.label14.Text = "~";
            // 
            // timeArriveEnd
            // 
            this.timeArriveEnd.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.timeArriveEnd.Location = new System.Drawing.Point(686, 24);
            this.timeArriveEnd.Name = "timeArriveEnd";
            this.timeArriveEnd.Size = new System.Drawing.Size(99, 23);
            this.timeArriveEnd.TabIndex = 10;
            // 
            // dateArriveEnd
            // 
            this.dateArriveEnd.Location = new System.Drawing.Point(562, 24);
            this.dateArriveEnd.Name = "dateArriveEnd";
            this.dateArriveEnd.Size = new System.Drawing.Size(118, 23);
            this.dateArriveEnd.TabIndex = 9;
            // 
            // timeLeaveEnd
            // 
            this.timeLeaveEnd.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.timeLeaveEnd.Location = new System.Drawing.Point(686, 53);
            this.timeLeaveEnd.Name = "timeLeaveEnd";
            this.timeLeaveEnd.Size = new System.Drawing.Size(99, 23);
            this.timeLeaveEnd.TabIndex = 16;
            // 
            // dateLeaveEnd
            // 
            this.dateLeaveEnd.Location = new System.Drawing.Point(562, 53);
            this.dateLeaveEnd.Name = "dateLeaveEnd";
            this.dateLeaveEnd.Size = new System.Drawing.Size(118, 23);
            this.dateLeaveEnd.TabIndex = 15;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(539, 65);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(14, 14);
            this.label16.TabIndex = 14;
            this.label16.Text = "~";
            // 
            // timeLeaveBegin
            // 
            this.timeLeaveBegin.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.timeLeaveBegin.Location = new System.Drawing.Point(434, 53);
            this.timeLeaveBegin.Name = "timeLeaveBegin";
            this.timeLeaveBegin.Size = new System.Drawing.Size(99, 23);
            this.timeLeaveBegin.TabIndex = 13;
            // 
            // dateLeaveBegin
            // 
            this.dateLeaveBegin.Location = new System.Drawing.Point(310, 53);
            this.dateLeaveBegin.Name = "dateLeaveBegin";
            this.dateLeaveBegin.Size = new System.Drawing.Size(118, 23);
            this.dateLeaveBegin.TabIndex = 12;
            // 
            // checkBoxArriveTime
            // 
            this.checkBoxArriveTime.AutoSize = true;
            this.checkBoxArriveTime.Location = new System.Drawing.Point(213, 25);
            this.checkBoxArriveTime.Name = "checkBoxArriveTime";
            this.checkBoxArriveTime.Size = new System.Drawing.Size(96, 18);
            this.checkBoxArriveTime.TabIndex = 17;
            this.checkBoxArriveTime.Text = "进站时间：";
            this.checkBoxArriveTime.UseVisualStyleBackColor = true;
            // 
            // checkBoxLeaveTime
            // 
            this.checkBoxLeaveTime.AutoSize = true;
            this.checkBoxLeaveTime.Location = new System.Drawing.Point(213, 56);
            this.checkBoxLeaveTime.Name = "checkBoxLeaveTime";
            this.checkBoxLeaveTime.Size = new System.Drawing.Size(96, 18);
            this.checkBoxLeaveTime.TabIndex = 18;
            this.checkBoxLeaveTime.Text = "出站时间：";
            this.checkBoxLeaveTime.UseVisualStyleBackColor = true;
            // 
            // btnQuery
            // 
            this.btnQuery.Location = new System.Drawing.Point(824, 26);
            this.btnQuery.Name = "btnQuery";
            this.btnQuery.Size = new System.Drawing.Size(75, 50);
            this.btnQuery.TabIndex = 19;
            this.btnQuery.Text = "查  询";
            this.btnQuery.UseVisualStyleBackColor = true;
            this.btnQuery.Click += new System.EventHandler(this.btnQuery_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(0, 144);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(455, 281);
            this.tabControl1.TabIndex = 14;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.pictureBoxArrive);
            this.tabPage1.Location = new System.Drawing.Point(4, 24);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(447, 253);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "进站图片";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.pictureBoxLeave);
            this.tabPage2.Location = new System.Drawing.Point(4, 24);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(428, 253);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "出站图片";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // tabControl2
            // 
            this.tabControl2.Controls.Add(this.tabPage3);
            this.tabControl2.Location = new System.Drawing.Point(0, 425);
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            this.tabControl2.Size = new System.Drawing.Size(455, 281);
            this.tabControl2.TabIndex = 15;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.pictureBoxPump);
            this.tabPage3.Location = new System.Drawing.Point(4, 24);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(447, 253);
            this.tabPage3.TabIndex = 0;
            this.tabPage3.Text = "加油图片";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // pictureBoxArrive
            // 
            this.pictureBoxArrive.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBoxArrive.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBoxArrive.Location = new System.Drawing.Point(3, 3);
            this.pictureBoxArrive.Name = "pictureBoxArrive";
            this.pictureBoxArrive.Size = new System.Drawing.Size(441, 247);
            this.pictureBoxArrive.TabIndex = 0;
            this.pictureBoxArrive.TabStop = false;
            // 
            // pictureBoxLeave
            // 
            this.pictureBoxLeave.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBoxLeave.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBoxLeave.Location = new System.Drawing.Point(3, 3);
            this.pictureBoxLeave.Name = "pictureBoxLeave";
            this.pictureBoxLeave.Size = new System.Drawing.Size(422, 247);
            this.pictureBoxLeave.TabIndex = 1;
            this.pictureBoxLeave.TabStop = false;
            // 
            // pictureBoxPump
            // 
            this.pictureBoxPump.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBoxPump.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBoxPump.Location = new System.Drawing.Point(3, 3);
            this.pictureBoxPump.Name = "pictureBoxPump";
            this.pictureBoxPump.Size = new System.Drawing.Size(441, 247);
            this.pictureBoxPump.TabIndex = 1;
            this.pictureBoxPump.TabStop = false;
            // 
            // FormSearchData
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 14F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1424, 862);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Name = "FormSearchData";
            this.Text = "FormSearchData";
            this.Load += new System.EventHandler(this.FormSearchData_Load);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridCar)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabControl2.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxArrive)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxLeave)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxPump)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.DataGridView dataGridCar;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label lblLicense;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblOilType;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label lblCarLogo;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label lblNozzleNo;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label lblLeaveTime;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label lblArriveTime;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DateTimePicker timeLeaveEnd;
        private System.Windows.Forms.DateTimePicker dateLeaveEnd;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.DateTimePicker timeLeaveBegin;
        private System.Windows.Forms.DateTimePicker dateLeaveBegin;
        private System.Windows.Forms.DateTimePicker timeArriveEnd;
        private System.Windows.Forms.DateTimePicker dateArriveEnd;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.DateTimePicker timeArriveBegin;
        private System.Windows.Forms.DateTimePicker dateArriveBegin;
        private System.Windows.Forms.TextBox textLicense;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.CheckBox checkBoxLeaveTime;
        private System.Windows.Forms.CheckBox checkBoxArriveTime;
        private System.Windows.Forms.Button btnQuery;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.PictureBox pictureBoxPump;
        private System.Windows.Forms.PictureBox pictureBoxArrive;
        private System.Windows.Forms.PictureBox pictureBoxLeave;
    }
}