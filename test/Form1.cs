using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            List<string> lit = new List<string>();
            for (int i=0;i<10;i++)
            {
                lit.Add(i.ToString());
            }

            foreach (string s in lit)
            {
                if (s == "0")
                {
                    lit.Remove(s);
                }
            }
            
        }
    }
}
