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
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.btnTest = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.realVideo = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.lblReturn = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.lblBufferSize = new System.Windows.Forms.Label();
            this.lblTimes = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textChanel = new System.Windows.Forms.TextBox();
            this.textBS = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.realVideo)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(2, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "初始化NVR";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(83, 12);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 1;
            this.button2.Text = "初始化算法";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // btnTest
            // 
            this.btnTest.Location = new System.Drawing.Point(319, 12);
            this.btnTest.Name = "btnTest";
            this.btnTest.Size = new System.Drawing.Size(75, 23);
            this.btnTest.TabIndex = 2;
            this.btnTest.Text = "接口测试";
            this.btnTest.UseVisualStyleBackColor = true;
            this.btnTest.Click += new System.EventHandler(this.btnTest_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(216, 12);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(75, 23);
            this.button4.TabIndex = 3;
            this.button4.Text = "预览";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // realVideo
            // 
            this.realVideo.Location = new System.Drawing.Point(24, 50);
            this.realVideo.Name = "realVideo";
            this.realVideo.Size = new System.Drawing.Size(402, 271);
            this.realVideo.TabIndex = 4;
            this.realVideo.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(36, 353);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 5;
            this.label1.Text = "返回值";
            // 
            // lblReturn
            // 
            this.lblReturn.AutoSize = true;
            this.lblReturn.Location = new System.Drawing.Point(95, 353);
            this.lblReturn.Name = "lblReturn";
            this.lblReturn.Size = new System.Drawing.Size(0, 12);
            this.lblReturn.TabIndex = 6;
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // lblBufferSize
            // 
            this.lblBufferSize.AutoSize = true;
            this.lblBufferSize.Location = new System.Drawing.Point(144, 353);
            this.lblBufferSize.Name = "lblBufferSize";
            this.lblBufferSize.Size = new System.Drawing.Size(41, 12);
            this.lblBufferSize.TabIndex = 7;
            this.lblBufferSize.Text = "返回值";
            // 
            // lblTimes
            // 
            this.lblTimes.AutoSize = true;
            this.lblTimes.Location = new System.Drawing.Point(250, 353);
            this.lblTimes.Name = "lblTimes";
            this.lblTimes.Size = new System.Drawing.Size(41, 12);
            this.lblTimes.TabIndex = 8;
            this.lblTimes.Text = "返回值";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(449, 85);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 9;
            this.label2.Text = "通道";
            // 
            // textChanel
            // 
            this.textChanel.Location = new System.Drawing.Point(490, 80);
            this.textChanel.Name = "textChanel";
            this.textChanel.Size = new System.Drawing.Size(52, 21);
            this.textChanel.TabIndex = 10;
            this.textChanel.Text = "33";
            // 
            // textBS
            // 
            this.textBS.Location = new System.Drawing.Point(490, 108);
            this.textBS.Name = "textBS";
            this.textBS.Size = new System.Drawing.Size(52, 21);
            this.textBS.TabIndex = 12;
            this.textBS.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(449, 112);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 12);
            this.label3.TabIndex = 11;
            this.label3.Text = "码流";
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(565, 374);
            this.Controls.Add(this.textBS);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textChanel);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lblTimes);
            this.Controls.Add(this.lblBufferSize);
            this.Controls.Add(this.lblReturn);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.realVideo);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.btnTest);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Name = "FormMain";
            this.Text = "加油站智能信息管理系统";
            ((System.ComponentModel.ISupportInitialize)(this.realVideo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button btnTest;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.PictureBox realVideo;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblReturn;
        private System.Windows.Forms.Label lblBufferSize;
        private System.Windows.Forms.Label lblTimes;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textChanel;
        private System.Windows.Forms.TextBox textBS;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Timer timer1;
    }
}

