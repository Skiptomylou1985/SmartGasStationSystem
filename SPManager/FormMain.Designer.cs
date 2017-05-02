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
            this.notifyIconMain = new System.Windows.Forms.NotifyIcon(this.components);
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.btnQuit = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.pBoxMain = new System.Windows.Forms.PictureBox();
            this.btnOpenMain = new System.Windows.Forms.Button();
            this.btnCloseMain = new System.Windows.Forms.Button();
            this.btnCloseSocket = new System.Windows.Forms.Button();
            this.btnOpenSocket = new System.Windows.Forms.Button();
            this.pBoxSocket = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btnCloseMonitor = new System.Windows.Forms.Button();
            this.btnOpenMonitor = new System.Windows.Forms.Button();
            this.pBoxMonitor = new System.Windows.Forms.PictureBox();
            this.label3 = new System.Windows.Forms.Label();
            this.btnCloseUpdate = new System.Windows.Forms.Button();
            this.btnOpenUpdate = new System.Windows.Forms.Button();
            this.pBoxUpdate = new System.Windows.Forms.PictureBox();
            this.label4 = new System.Windows.Forms.Label();
            this.button6 = new System.Windows.Forms.Button();
            this.statusSystem = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolCPU = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolRAM = new System.Windows.Forms.ToolStripStatusLabel();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMain)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxSocket)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMonitor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxUpdate)).BeginInit();
            this.statusSystem.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // notifyIconMain
            // 
            this.notifyIconMain.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIconMain.Icon")));
            this.notifyIconMain.Text = "notifyIcon1";
            this.notifyIconMain.Visible = true;
            this.notifyIconMain.DoubleClick += new System.EventHandler(this.notifyIconMain_DoubleClick);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(429, 345);
            this.tabControl1.TabIndex = 18;
            // 
            // tabPage1
            // 
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
            this.tabPage1.Size = new System.Drawing.Size(421, 319);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "运行状态";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.btnQuit);
            this.tabPage2.Controls.Add(this.button5);
            this.tabPage2.Controls.Add(this.button3);
            this.tabPage2.Controls.Add(this.button4);
            this.tabPage2.Controls.Add(this.button2);
            this.tabPage2.Controls.Add(this.button1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(421, 319);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // btnQuit
            // 
            this.btnQuit.Location = new System.Drawing.Point(104, 163);
            this.btnQuit.Name = "btnQuit";
            this.btnQuit.Size = new System.Drawing.Size(75, 23);
            this.btnQuit.TabIndex = 24;
            this.btnQuit.Text = "关闭软件";
            this.btnQuit.UseVisualStyleBackColor = true;
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(104, 134);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(75, 23);
            this.button5.TabIndex = 22;
            this.button5.Text = "取多车";
            this.button5.UseVisualStyleBackColor = true;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(104, 105);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 21;
            this.button3.Text = "取头车";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(104, 69);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 20;
            this.button4.Text = "预览";
            this.button4.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(104, 40);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 19;
            this.button2.Text = "初始化算法";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(104, 7);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 18;
            this.button1.Text = "初始化NVR";
            this.button1.UseVisualStyleBackColor = true;
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
            // pBoxMain
            // 
            this.pBoxMain.Location = new System.Drawing.Point(152, 3);
            this.pBoxMain.Name = "pBoxMain";
            this.pBoxMain.Size = new System.Drawing.Size(32, 32);
            this.pBoxMain.TabIndex = 3;
            this.pBoxMain.TabStop = false;
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
            // button6
            // 
            this.button6.Font = new System.Drawing.Font("宋体", 9F);
            this.button6.Location = new System.Drawing.Point(327, 197);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(75, 23);
            this.button6.TabIndex = 24;
            this.button6.Text = "接口测试";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click_1);
            // 
            // statusSystem
            // 
            this.statusSystem.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolCPU,
            this.toolStripStatusLabel2,
            this.toolRAM});
            this.statusSystem.Location = new System.Drawing.Point(0, 297);
            this.statusSystem.Name = "statusSystem";
            this.statusSystem.Size = new System.Drawing.Size(421, 22);
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
            this.toolCPU.Size = new System.Drawing.Size(40, 17);
            this.toolCPU.Text = "100%";
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
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(429, 345);
            this.Controls.Add(this.tabControl1);
            this.Name = "FormMain";
            this.Text = "加油站智能信息管理系统";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormMain_FormClosing);
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMain)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxSocket)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxMonitor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pBoxUpdate)).EndInit();
            this.statusSystem.ResumeLayout(false);
            this.statusSystem.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.NotifyIcon notifyIconMain;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button btnQuit;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
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
    }
}

