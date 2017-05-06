namespace SPManager
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
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.comboLogLevel = new System.Windows.Forms.ComboBox();
            this.button9 = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.realVideo = new System.Windows.Forms.PictureBox();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button7 = new System.Windows.Forms.Button();
            this.statusSystem = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolCPU = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolRAM = new System.Windows.Forms.ToolStripStatusLabel();
            this.button6 = new System.Windows.Forms.Button();
            this.btnCloseMonitor = new System.Windows.Forms.Button();
            this.btnOpenMonitor = new System.Windows.Forms.Button();
            this.pBoxMonitor = new System.Windows.Forms.PictureBox();
            this.label3 = new System.Windows.Forms.Label();
            this.btnCloseMain = new System.Windows.Forms.Button();
            this.btnOpenMain = new System.Windows.Forms.Button();
            this.pBoxMain = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.btnCloseUpdate = new System.Windows.Forms.Button();
            this.btnOpenUpdate = new System.Windows.Forms.Button();
            this.pBoxUpdate = new System.Windows.Forms.PictureBox();
            this.label4 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnCloseSocket = new System.Windows.Forms.Button();
            this.btnOpenSocket = new System.Windows.Forms.Button();
            this.pBoxSocket = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.button1 = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.realVideo)).BeginInit();
            this.statusSystem.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMonitor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMain)).BeginInit();
            this.panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxUpdate)).BeginInit();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxSocket)).BeginInit();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(507, 421);
            this.tabControl1.TabIndex = 18;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.button1);
            this.tabPage1.Controls.Add(this.comboLogLevel);
            this.tabPage1.Controls.Add(this.button9);
            this.tabPage1.Controls.Add(this.button8);
            this.tabPage1.Controls.Add(this.realVideo);
            this.tabPage1.Controls.Add(this.button3);
            this.tabPage1.Controls.Add(this.button4);
            this.tabPage1.Controls.Add(this.button7);
            this.tabPage1.Controls.Add(this.statusSystem);
            this.tabPage1.Controls.Add(this.button6);
            this.tabPage1.Controls.Add(this.btnCloseMonitor);
            this.tabPage1.Controls.Add(this.btnOpenMonitor);
            this.tabPage1.Controls.Add(this.pBoxMonitor);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.btnCloseMain);
            this.tabPage1.Controls.Add(this.btnOpenMain);
            this.tabPage1.Controls.Add(this.pBoxMain);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.panel3);
            this.tabPage1.Controls.Add(this.panel1);
            this.tabPage1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Margin = new System.Windows.Forms.Padding(0);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Size = new System.Drawing.Size(499, 395);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "运行状态";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // comboLogLevel
            // 
            this.comboLogLevel.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboLogLevel.FormattingEnabled = true;
            this.comboLogLevel.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4"});
            this.comboLogLevel.Location = new System.Drawing.Point(316, 233);
            this.comboLogLevel.Name = "comboLogLevel";
            this.comboLogLevel.Size = new System.Drawing.Size(69, 29);
            this.comboLogLevel.TabIndex = 32;
            // 
            // button9
            // 
            this.button9.Font = new System.Drawing.Font("宋体", 9F);
            this.button9.Location = new System.Drawing.Point(402, 238);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(75, 23);
            this.button9.TabIndex = 31;
            this.button9.Text = "日志切换";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // button8
            // 
            this.button8.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button8.Location = new System.Drawing.Point(217, 197);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(75, 23);
            this.button8.TabIndex = 30;
            this.button8.Text = "预览有图";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // realVideo
            // 
            this.realVideo.Location = new System.Drawing.Point(37, 238);
            this.realVideo.Name = "realVideo";
            this.realVideo.Size = new System.Drawing.Size(246, 132);
            this.realVideo.TabIndex = 29;
            this.realVideo.TabStop = false;
            // 
            // button3
            // 
            this.button3.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button3.Location = new System.Drawing.Point(310, 197);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 28;
            this.button3.Text = "取头车";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click_1);
            // 
            // button4
            // 
            this.button4.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button4.Location = new System.Drawing.Point(136, 197);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 27;
            this.button4.Text = "预览无图";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click_1);
            // 
            // button7
            // 
            this.button7.Font = new System.Drawing.Font("宋体", 9F);
            this.button7.Location = new System.Drawing.Point(402, 197);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(75, 23);
            this.button7.TabIndex = 26;
            this.button7.Text = "切换视频";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // statusSystem
            // 
            this.statusSystem.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolCPU,
            this.toolStripStatusLabel2,
            this.toolRAM});
            this.statusSystem.Location = new System.Drawing.Point(0, 373);
            this.statusSystem.Name = "statusSystem";
            this.statusSystem.Size = new System.Drawing.Size(499, 22);
            this.statusSystem.TabIndex = 25;
            this.statusSystem.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(80, 17);
            this.toolStripStatusLabel1.Text = "CPU占用率：";
            // 
            // toolCPU
            // 
            this.toolCPU.Name = "toolCPU";
            this.toolCPU.Size = new System.Drawing.Size(26, 17);
            this.toolCPU.Text = "0%";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(80, 17);
            this.toolStripStatusLabel2.Text = "内存占用率：";
            // 
            // toolRAM
            // 
            this.toolRAM.Name = "toolRAM";
            this.toolRAM.Size = new System.Drawing.Size(40, 17);
            this.toolRAM.Text = "100%";
            // 
            // button6
            // 
            this.button6.Font = new System.Drawing.Font("宋体", 9F);
            this.button6.Location = new System.Drawing.Point(37, 197);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(75, 23);
            this.button6.TabIndex = 24;
            this.button6.Text = "初始化";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click_1);
            // 
            // btnCloseMonitor
            // 
            this.btnCloseMonitor.Font = new System.Drawing.Font("宋体", 9F);
            this.btnCloseMonitor.Location = new System.Drawing.Point(328, 90);
            this.btnCloseMonitor.Name = "btnCloseMonitor";
            this.btnCloseMonitor.Size = new System.Drawing.Size(75, 23);
            this.btnCloseMonitor.TabIndex = 9;
            this.btnCloseMonitor.Text = "关  闭";
            this.btnCloseMonitor.UseVisualStyleBackColor = true;
            // 
            // btnOpenMonitor
            // 
            this.btnOpenMonitor.Font = new System.Drawing.Font("宋体", 9F);
            this.btnOpenMonitor.Location = new System.Drawing.Point(233, 90);
            this.btnOpenMonitor.Name = "btnOpenMonitor";
            this.btnOpenMonitor.Size = new System.Drawing.Size(75, 23);
            this.btnOpenMonitor.TabIndex = 8;
            this.btnOpenMonitor.Text = "开  启";
            this.btnOpenMonitor.UseVisualStyleBackColor = true;
            // 
            // pBoxMonitor
            // 
            this.pBoxMonitor.Image = ((System.Drawing.Image)(resources.GetObject("pBoxMonitor.Image")));
            this.pBoxMonitor.Location = new System.Drawing.Point(153, 86);
            this.pBoxMonitor.Name = "pBoxMonitor";
            this.pBoxMonitor.Size = new System.Drawing.Size(32, 32);
            this.pBoxMonitor.TabIndex = 7;
            this.pBoxMonitor.TabStop = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(12, 91);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(122, 21);
            this.label3.TabIndex = 6;
            this.label3.Text = "运行监控服务：";
            // 
            // btnCloseMain
            // 
            this.btnCloseMain.Font = new System.Drawing.Font("宋体", 9F);
            this.btnCloseMain.Location = new System.Drawing.Point(327, 7);
            this.btnCloseMain.Name = "btnCloseMain";
            this.btnCloseMain.Size = new System.Drawing.Size(75, 23);
            this.btnCloseMain.TabIndex = 5;
            this.btnCloseMain.Text = "关  闭";
            this.btnCloseMain.UseVisualStyleBackColor = true;
            this.btnCloseMain.Click += new System.EventHandler(this.btnCloseMain_Click);
            // 
            // btnOpenMain
            // 
            this.btnOpenMain.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnOpenMain.Location = new System.Drawing.Point(232, 7);
            this.btnOpenMain.Name = "btnOpenMain";
            this.btnOpenMain.Size = new System.Drawing.Size(75, 23);
            this.btnOpenMain.TabIndex = 4;
            this.btnOpenMain.Text = "开  启";
            this.btnOpenMain.UseVisualStyleBackColor = true;
            // 
            // pBoxMain
            // 
            this.pBoxMain.Location = new System.Drawing.Point(152, 3);
            this.pBoxMain.Name = "pBoxMain";
            this.pBoxMain.Size = new System.Drawing.Size(32, 32);
            this.pBoxMain.TabIndex = 3;
            this.pBoxMain.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(11, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(122, 21);
            this.label1.TabIndex = 2;
            this.label1.Text = "车牌识别服务：";
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.panel3.Controls.Add(this.btnCloseUpdate);
            this.panel3.Controls.Add(this.btnOpenUpdate);
            this.panel3.Controls.Add(this.pBoxUpdate);
            this.panel3.Controls.Add(this.label4);
            this.panel3.Location = new System.Drawing.Point(-4, 126);
            this.panel3.Margin = new System.Windows.Forms.Padding(0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(500, 40);
            this.panel3.TabIndex = 1;
            // 
            // btnCloseUpdate
            // 
            this.btnCloseUpdate.Font = new System.Drawing.Font("宋体", 9F);
            this.btnCloseUpdate.Location = new System.Drawing.Point(332, 8);
            this.btnCloseUpdate.Name = "btnCloseUpdate";
            this.btnCloseUpdate.Size = new System.Drawing.Size(75, 23);
            this.btnCloseUpdate.TabIndex = 9;
            this.btnCloseUpdate.Text = "关  闭";
            this.btnCloseUpdate.UseVisualStyleBackColor = true;
            // 
            // btnOpenUpdate
            // 
            this.btnOpenUpdate.Font = new System.Drawing.Font("宋体", 9F);
            this.btnOpenUpdate.Location = new System.Drawing.Point(237, 8);
            this.btnOpenUpdate.Name = "btnOpenUpdate";
            this.btnOpenUpdate.Size = new System.Drawing.Size(75, 23);
            this.btnOpenUpdate.TabIndex = 8;
            this.btnOpenUpdate.Text = "开  启";
            this.btnOpenUpdate.UseVisualStyleBackColor = true;
            // 
            // pBoxUpdate
            // 
            this.pBoxUpdate.Image = ((System.Drawing.Image)(resources.GetObject("pBoxUpdate.Image")));
            this.pBoxUpdate.Location = new System.Drawing.Point(157, 4);
            this.pBoxUpdate.Name = "pBoxUpdate";
            this.pBoxUpdate.Size = new System.Drawing.Size(32, 32);
            this.pBoxUpdate.TabIndex = 7;
            this.pBoxUpdate.TabStop = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(16, 9);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(122, 21);
            this.label4.TabIndex = 6;
            this.label4.Text = "自动升级服务：";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.panel1.Controls.Add(this.btnCloseSocket);
            this.panel1.Controls.Add(this.btnOpenSocket);
            this.panel1.Controls.Add(this.pBoxSocket);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Location = new System.Drawing.Point(-7, 38);
            this.panel1.Margin = new System.Windows.Forms.Padding(0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(500, 40);
            this.panel1.TabIndex = 0;
            // 
            // btnCloseSocket
            // 
            this.btnCloseSocket.Font = new System.Drawing.Font("宋体", 9F);
            this.btnCloseSocket.Location = new System.Drawing.Point(334, 8);
            this.btnCloseSocket.Name = "btnCloseSocket";
            this.btnCloseSocket.Size = new System.Drawing.Size(75, 23);
            this.btnCloseSocket.TabIndex = 9;
            this.btnCloseSocket.Text = "关  闭";
            this.btnCloseSocket.UseVisualStyleBackColor = true;
            // 
            // btnOpenSocket
            // 
            this.btnOpenSocket.Font = new System.Drawing.Font("宋体", 9F);
            this.btnOpenSocket.Location = new System.Drawing.Point(239, 8);
            this.btnOpenSocket.Name = "btnOpenSocket";
            this.btnOpenSocket.Size = new System.Drawing.Size(75, 23);
            this.btnOpenSocket.TabIndex = 8;
            this.btnOpenSocket.Text = "开  启";
            this.btnOpenSocket.UseVisualStyleBackColor = true;
            // 
            // pBoxSocket
            // 
            this.pBoxSocket.Image = ((System.Drawing.Image)(resources.GetObject("pBoxSocket.Image")));
            this.pBoxSocket.Location = new System.Drawing.Point(159, 4);
            this.pBoxSocket.Name = "pBoxSocket";
            this.pBoxSocket.Size = new System.Drawing.Size(32, 32);
            this.pBoxSocket.TabIndex = 7;
            this.pBoxSocket.TabStop = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(18, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(122, 21);
            this.label2.TabIndex = 6;
            this.label2.Text = "网络通讯服务：";
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(499, 395);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("宋体", 9F);
            this.button1.Location = new System.Drawing.Point(402, 276);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 33;
            this.button1.Text = "测试";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(507, 421);
            this.Controls.Add(this.tabControl1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "FormMain";
            this.Text = "加油站智能信息管理系统";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormMain_FormClosed);
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.realVideo)).EndInit();
            this.statusSystem.ResumeLayout(false);
            this.statusSystem.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMonitor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMain)).EndInit();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxUpdate)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxSocket)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Button btnCloseMonitor;
        private System.Windows.Forms.Button btnOpenMonitor;
        private System.Windows.Forms.PictureBox pBoxMonitor;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnCloseMain;
        private System.Windows.Forms.Button btnOpenMain;
        private System.Windows.Forms.PictureBox pBoxMain;
        private System.Windows.Forms.Button btnCloseUpdate;
        private System.Windows.Forms.Button btnOpenUpdate;
        private System.Windows.Forms.PictureBox pBoxUpdate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button btnCloseSocket;
        private System.Windows.Forms.Button btnOpenSocket;
        private System.Windows.Forms.PictureBox pBoxSocket;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.StatusStrip statusSystem;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel toolCPU;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel toolRAM;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.PictureBox realVideo;
        private System.Windows.Forms.ComboBox comboLogLevel;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button button1;
    }
}

