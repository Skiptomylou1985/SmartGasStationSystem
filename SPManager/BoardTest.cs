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
    public partial class BoardTest : Form
    {
        public BoardTest()
        {
            InitializeComponent();
            
        }

        private void btnTest_Click(object sender, EventArgs e)
        {
            panelIsland1.Enabled = false;
           // string controlName = "btnArea1";
            //setControlAtrribute("btnArea1", "butten", "Color", Color.Red);
            //setControlAtrribute("btnArea1", "butten", "Enable", false);


        }

        public void setControlAtrribute(string controlName, string attrType,object attrValue)
        {
            Control control = (Control)this.GetType().GetField(controlName, System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.IgnoreCase).GetValue(this);
            //control.BackColor = Color.Red;
            //                     
            //             switch (controlType)
            //             {
            //                 case "butten":
            //                     Button btn = (Button)this.GetType().GetField(controlName, System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.IgnoreCase).GetValue(this);
            //                     btn.BackColor = (Color)attrValue;
            //                     break;
            //                 case "panel":
            //                     Panel panel = (Panel)this.GetType().GetField(controlName, System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.IgnoreCase).GetValue(this);
            //                     panel.Visible = (bool)attrValue;
            //                     break;
            //                 default:
            //                     break;
            //             }
            switch (attrType)
            {
                case "Color":
                    control.BackColor = (Color)attrValue;
                    break;
                case "Visible":
                    control.Visible = (bool)attrValue;
                    break;
                case "Enable":
                    control.Enabled = (bool)attrValue;
                    break;
                case "Text":
                    control.Text = attrValue.ToString();
                    break;
                case "Image":
                    control.BackgroundImage = (Image)attrValue;
                    break;
                default:
                    break;
            }
        }

        private void panelIsland1_MouseHover(object sender, EventArgs e)
        {
            panelIsland1.BackColor = Color.SeaShell;
            tip.ShowAlways = true;
            tip.SetToolTip(this.panelIsland1, "鼠标点击后可调整位置");
        }

        private void panelIsland1_MouseLeave(object sender, EventArgs e)
        {
            panelIsland1.BackColor = Color.Transparent;
            tip.ShowAlways = false;
        }

        Point pt;
        bool moves = true;
        ToolTip tip = new ToolTip();
        private void panelIsland1_MouseDown(object sender, MouseEventArgs e)
        {
            pt = Cursor.Position;
        }

        private void panelIsland1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                int px = Cursor.Position.X - pt.X;
                int py = Cursor.Position.Y - pt.Y;
                panelIsland1.Location = new Point(panelIsland1.Location.X + px, panelIsland1.Location.Y + py);
                pt = Cursor.Position;
                moves = false;
            }
        }

        private void panelIsland1_MouseUp(object sender, MouseEventArgs e)
        {
            moves = true;
        }

        private void btnTest2_Click(object sender, EventArgs e)
        {
            setControlAtrribute("btnArea1", "Color", Color.Red);
            setControlAtrribute("btnArea1", "Text", "京A12345");
        }

        private void panel34_MouseHover(object sender, EventArgs e)
        {
            tip.ShowAlways = true;
            tip.SetToolTip(this.panel34, "双击设置关联视频通道");
        }
    }
}
