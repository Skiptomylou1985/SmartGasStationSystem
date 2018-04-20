using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SPManager
{
    public partial class FormSet : Form
    {
        private string linkkind;
        public FormSet()
        {
            InitializeComponent();
        }
        public FormSet(string linkKind,bool bMustUse)
        {
            InitializeComponent();
            this.linkkind = linkkind;
            checkUse.Checked = true;
            if (bMustUse)
            {
                checkUse.Enabled = false;
            }
            lblKind.Visible = false;
            comboMain.Visible = false;
            comboSub.Visible = false;
            switch (linkkind)
            {
                case "nozzle":
                    lblKind.Text = "关联油枪号";
                    lblKind.Visible = true;
                    comboMain.Visible = true;
                    comboMain.Items.Clear();
                    comboMain.Items.AddRange(new object[] {"油枪1","油枪2","油枪3","油枪4","油枪5",
                                                            "油枪6","油枪7","油枪8","油枪9","油枪10",
                                                            "油枪11","油枪12","油枪13","油枪14","油枪15",
                                                            "油枪16","油枪17","油枪18","油枪19","油枪20",
                                                            "油枪21","油枪22","油枪23","油枪24","油枪25",
                                                            "油枪26","油枪27","油枪28","油枪29","油枪30",
                                                            "油枪31","油枪32"});
                    break;
                case "area":
                    lblKind.Text = "关联识别区";
                    lblKind.Visible = true;
                    comboMain.Visible = true;
                    comboSub.Visible = true;
                    comboMain.Items.Clear();
                    comboMain.Items.AddRange(new object[] {"通道1","通道2","通道3","通道4","通道5",
                                                            "通道6","通道7","通道8","通道9","通道10",
                                                            "通道11","通道12","通道13","通道14","通道15",
                                                            "通道16","通道17","通道18","通道19","通道20",
                                                            "通道21","通道22","通道23","通道24","通道25",
                                                            "通道26","通道27","通道28","通道29","通道30",
                                                            "通道31","通道32"});
                    break;
                case "island":
                    lblKind.Visible = false;
                    comboMain.Visible = false;
                    comboSub.Visible = false;
                    break;
                default:
                    break;
            }
        }
        public string Value { set; get; }
        public bool bShow { set; get; }

        private void btnOK_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Value = comboMain.Text;
            this.bShow = checkUse.Checked;
            this.Close();

        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void checkUse_CheckedChanged(object sender, EventArgs e)
        {
            comboMain.Enabled = checkUse.Checked;
            comboSub.Enabled = checkUse.Checked;
        }
    }
}
