using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SPManager
{
    public partial class FormSearchData : Form
    {
        private Image arrivePic = null;
        private Image leavePic = null;
        private Image pumpPic = null;
        public FormSearchData()
        {
            InitializeComponent();
        }

        private void btnQuery_Click(object sender, EventArgs e)
        {
            
            string arriveBegin = dateArriveBegin.Value.ToString("yyyy-MM-dd") + timeArriveBegin.Value.ToString(" HH:mm:ss");
            string arriveEnd = dateArriveEnd.Value.ToString("yyyy-MM-dd") + timeArriveEnd.Value.ToString(" HH:mm:ss");
            string leaveBegin = dateLeaveBegin.Value.ToString("yyyy-MM-dd") + timeLeaveBegin.Value.ToString(" HH:mm:ss");
            string leaveEnd = dateLeaveEnd.Value.ToString("yyyy-MM-dd") + timeLeaveEnd.Value.ToString(" HH:mm:ss");
            StringBuilder sbQuery = new StringBuilder();
            sbQuery.Append("select id,carnumber,nozzleno,oiltype,arrivetime,begintime,leavetime,carlogo,carcolor,picpath from carlog ");
            sbQuery.Append(" where 1 = 1");
            if (textLicense.Text.Trim().Length >0)
            {
                sbQuery.Append(" and carnumber like '%" + textLicense.Text.Trim() + "%'");
            }
            if (checkBoxArriveTime.Checked)
            {
                sbQuery.Append(" and (arrivetime between '" + arriveBegin + "' and '" + arriveEnd + "')");
            }
            if (checkBoxLeaveTime.Checked)
            {
                sbQuery.Append(" and (leavetime between '" + leaveBegin + "' and '" + leaveEnd + "')");
            }
            sbQuery.Append(" order by leavetime desc limit 0,500");
            DataTable dt = Global.mysqlHelper.GetDataTable(sbQuery.ToString());
            dataGridCar.DataSource = dt;
            setDGV(dataGridCar);
        }
        public void setDGV(DataGridView dgv)
        {
            
            dgv.Columns[0].HeaderText = "序号";
            dgv.Columns[1].HeaderText = "车牌号";
            dgv.Columns[2].HeaderText = "油枪号";
            dgv.Columns[3].HeaderText = "油类型";
            dgv.Columns[4].HeaderText = "进站时间";
            dgv.Columns[5].HeaderText = "加油时间";
            dgv.Columns[6].HeaderText = "出站时间";
            dgv.Columns[7].HeaderText = "车辆品牌";
            dgv.Columns[8].HeaderText = "车辆颜色";
            dgv.Columns[9].Visible = false;
            dgv.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            dgv.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            //dgv.AllowUserToAddRows = false;
            //dgv.AllowUserToResizeRows = false;
            foreach (DataGridViewColumn item in dgv.Columns)
            {
                item.DefaultCellStyle.Alignment = DataGridViewContentAlignment.MiddleCenter;
                item.ReadOnly = true;
            }
        }

        private void FormSearchData_Load(object sender, EventArgs e)
        {
            //setDGV(dataGridCar);
        }

        private void dataGridCar_CellClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void dataGridCar_SelectionChanged(object sender, EventArgs e)
        {
            int cur = 0;
            if (dataGridCar.CurrentCell != null)    //过车时刷新，当前单元格为空，选中首行
                cur = dataGridCar.CurrentCell.RowIndex;
            try
            {
                lblLicense.Text = dataGridCar.Rows[cur].Cells["carnumber"].Value.ToString();
                lblNozzleNo.Text = dataGridCar.Rows[cur].Cells["nozzleno"].Value.ToString();
                lblOilType.Text = dataGridCar.Rows[cur].Cells["oiltype"].Value.ToString();
                lblArriveTime.Text = dataGridCar.Rows[cur].Cells["arrivetime"].Value.ToString();
                lblLeaveTime.Text = dataGridCar.Rows[cur].Cells["leavetime"].Value.ToString();
                lblCarLogo.Text = dataGridCar.Rows[cur].Cells["carlogo"].Value.ToString();

                string picPath = dataGridCar.Rows[cur].Cells["picpath"].Value.ToString();
                
                //pictureBoxArrive.Image = Image.FromFile(picPath + ".jpg");

            }
            catch (System.Exception ex)
            {
            	
            }
            

        }

        private void timerCalc_Tick(object sender, EventArgs e)
        {
            string today = DateTime.Now.ToString("yyyy-MM-dd") + " 00:00:00";
            string sqlString = "select count(*) as count from carlog where arrivetime > '" + today + "'";
            try
            {
                DataTable dt = Global.mysqlHelper.GetDataTable(sqlString);
                lblTotalCar.Text = dt.Rows[0]["count"].ToString();
                sqlString = "select count(*) as count from carlog where nozzleno > 0 and arrivetime > '" + today + "'";
                dt = Global.mysqlHelper.GetDataTable(sqlString);
                lblMatchCar.Text = dt.Rows[0]["count"].ToString();
                lblUnMatchCar.Text = (int.Parse(lblTotalCar.Text.Trim()) - int.Parse(lblMatchCar.Text.Trim())).ToString();
            }
            catch (System.Exception ex)
            {
            	
            }
            
        }
    }
}
