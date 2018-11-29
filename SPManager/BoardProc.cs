using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.Net;
using System.Net.Sockets;

namespace SPManager
{
    partial class FormMain
    {
        private void ControlMove(Control con, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                int px = Cursor.Position.X - pt.X;
                int py = Cursor.Position.Y - pt.Y;
                con.Location = new Point(con.Location.X + px, con.Location.Y + py);
                pt = Cursor.Position;
                moves = false;
            }

        }

        private void SetSingleControlAttr(Control con, string linkKind, string origin, bool bMustShow)
        {
            FormSet set = new FormSet(linkKind, origin, bMustShow);
            DialogResult dr = set.ShowDialog();
            if (dr == DialogResult.OK)
            {
                foreach (ControlBoard cb in Global.listControls)
                {
                    if (cb.ControlName == con.Name)
                    {
                        switch (linkKind)
                        {
                            case "island":
                                cb.Visible = set.bShow;
                                cb.ShowText = set.Value;
                                for (int i = 0; i < Global.listControls.Count; i++)
                                {
                                    if (Global.listControls[i].ControlName == cb.ControlName + "_Text")
                                    {
                                        Global.listControls[i].ShowText = set.Value;
                                        break;
                                    }
                                }
                                Control subCon = (Control)this.GetType().GetField(con.Name + "_Text", System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.IgnoreCase).GetValue(this);
                                subCon.Text = cb.ShowText;
                                break;
                            case "area":
                                cb.Visible = set.bShow;
                                cb.ShowText = "通道" + set.Value + "-" + set.SubValue;
                                for (int i = 0; i < Global.areaList.Count; i++)
                                {
                                    if (Global.areaList[i].videoChannel.ToString() == set.Value &&
                                        Global.areaList[i].videoLaneNo.ToString() == set.SubValue)
                                    {
                                        cb.LinkIndex = Global.areaList[i].id;
                                        break;
                                    }
                                }
                                break;
                            case "nozzle":
                                cb.LinkIndex = int.Parse(set.Value);
                                cb.ShowText = set.Value;
                                cb.Visible = set.bShow;
                                break;
                            case "video":

                                break;
                            default:
                                break;
                        }
                        FlushSingleControlsSatus(cb);
                    }
                }
            }

        }

        private void SetNozzleLinkControl(Control nozzleControl)
        {
            string origin = "";
            for (int i = 0; i < Global.listControls.Count; i++)
            {
                if (Global.listControls[i].ControlName == nozzleControl.Name)
                {
                    origin = Global.listControls[i].LinkIndex.ToString();
                    break;
                }
            }
            SetSingleControlAttr(nozzleControl, "nozzle", origin, false);
        }


        private void SetAreaLinkControl(Control areaControl)
        {
            string origin = "";
            for (int i = 0; i < Global.listControls.Count; i++)
            {
                if (Global.listControls[i].ControlName == areaControl.Name)
                {
                    origin = Global.listControls[i].LinkIndex.ToString();
                    break;
                }
            }
            SetSingleControlAttr(areaControl, "area", origin, false);

        }

        private void GetSatationBoardParamFromDB()
        {
            Global.listControls.Clear();
            Global.DicAreaIndexInList.Clear();
            Global.DicNozzleIndexInList.Clear();
            string sql = "select * from board_param where name = ";
            if (Global.nStationBoardDirection == 0)
                sql = sql + "'StationBoardHorizon'";
            else
                sql = sql + "'StationBoardVertical'";
            DataTable dt = Global.mysqlHelper.GetDataTable(sql);
            if (dt != null && dt.Rows.Count > 0)
            {
                ControlBoard cb = new ControlBoard(dt.Rows[0]);
                Global.listControls.Add(cb);
                GetControlByParentId(cb.id);
            }
        }

        //通过父容器ID遍历控件
        private void GetControlByParentId(int parentid)
        {
            string sql = "select * from board_param where parentid = " + parentid.ToString();
            DataTable dt = Global.mysqlHelper.GetDataTable(sql);
            if (dt != null && dt.Rows.Count > 0)
            {
                foreach (DataRow dr in dt.Rows)
                {
                    ControlBoard cb = new ControlBoard(dr);
                    Global.listControls.Add(cb);
                    if (cb.LinkIndex > 0)
                    {
                        if (cb.LinkKind == "area")
                        {
                            Global.DicAreaIndexInList.Add(cb.LinkIndex, Global.listControls.IndexOf(cb));
                        }
                        else if (cb.LinkKind == "nozzle")
                        {
                            Global.DicNozzleIndexInList.Add(cb.LinkIndex, Global.listControls.IndexOf(cb));
                        }
                    }
                    GetControlByParentId(cb.id);
                }
            }

        }

        //刷新面板所有控件状态
        private void FlushStationBoard()
        {
            
            this.StationBoardHorizon.Visible = false;
            this.StationBoardVertical.Visible = false;
            if (Global.nStationBoardDirection == 0)
            {
                this.StationBoardHorizon.Visible = true;
                this.StationBoardHorizon.Enabled = Global.bStationBoardInSet;
            }
            else
            {
                this.StationBoardVertical.Visible = true;
                this.StationBoardVertical.Enabled = Global.bStationBoardInSet;
            }
            foreach (ControlBoard cb in Global.listControls)
            {

                FlushSingleControlsSatus(cb);
            }


        }

        //刷新单个控件显示状态
        private void FlushSingleControlsSatus(ControlBoard cb)
        {
            Control con = (Control)this.GetType().GetField(cb.ControlName, System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.IgnoreCase).GetValue(this);
            con.Location = new Point(cb.LocationX, cb.LocationY);
            con.Visible = true;
            //con.BackColor = cb.BaseColor;
            if (Global.bStationBoardInSet && !cb.Visible && cb.level > 1) //设置状态下,隐藏控件背景为灰色
            {
                con.BackColor = Color.Gray;
            }
            else if (!cb.Visible)
            {
                con.Visible = false;
                return;
            }
           
            if (Global.bStationBoardInSet && cb.LinkKind == "island")
            {
                con.BackColor = Color.SeaShell;
            }
            else if (cb.LinkKind == "island")
            {
                con.BackColor = Color.Transparent;
            }

            con.Text = cb.ShowText;
            if (Global.bStationBoardInSet && cb.LinkKind == "area")
            {
                con.Text = cb.ShowText;
            }
            else if (cb.LinkKind == "area")
            {
                con.Text = cb.RunText;
            }

        }

        //根据提枪信号更新面板油枪状态
        private void UpdateStationBoardNozzleControlStatus(int nozzleNo, int status)
        {
            Global.LogServer.Add(new LogInfo("Debug", "Main->UpdateStationBoardNozzleControlStatus 更新油枪控件状态，油枪号:" + nozzleNo.ToString() + ",状态:" + status.ToString(), (int)EnumLogLevel.DEBUG));

            if (Global.DicNozzleIndexInList.ContainsKey(nozzleNo))
            {
                int index = Global.DicNozzleIndexInList[nozzleNo];
                Global.listControls[index].StatusFlag = 1;
                switch (status)
                {
                    case 1:
                        break;
                        Global.listControls[index].RunColor = Color.LightPink;
                    case 2:
                        Global.listControls[index].RunColor = Color.Red;
                        break;
                    case 3:
                        Global.listControls[index].RunColor = Color.Lime;
                        break;
                    default:
                        Global.listControls[index].RunColor = Color.Lime;
                        break;
                }
            }

        }

        //根据车牌推送更新面板区域状态
        private void UpdateStationBoardAreaControlStatus(int areaId, string plate, Color color)
        {
            Global.LogServer.Add(new LogInfo("Debug", "Main->UpdateStationBoardAreaControlStatus 更新识别区控件状态，识别区:" + areaId.ToString() + ",车牌:" + plate +",颜色："+color.ToString(), (int)EnumLogLevel.DEBUG));

            if (Global.DicAreaIndexInList.ContainsKey(areaId))
            {

                int index = Global.DicAreaIndexInList[areaId];
                Global.listControls[index].RunText = plate;
                Global.listControls[index].RunColor = color;
                Global.listControls[index].StatusFlag = 1;
            }
        }
        //刷新控件显示，识别区，油枪
        private void FlushStationBoardRunControls()
        {
            if (Global.bStationBoardInSet)
            {
                return;
            }
            for (int i = 0; i < Global.listControls.Count; i++)
            {
                if (Global.listControls[i].StatusFlag == 1)
                {
                    Global.LogServer.Add(new LogInfo("Debug", "Main->FlushStationBoardRunControls " + Global.listControls[i].ControlName + " 已更新状态,关联类型："
                        + Global.listControls[i].LinkKind + " ,显示颜色： " + Global.listControls[i].RunColor.ToString(), (int)EnumLogLevel.DEBUG));

                    Global.listControls[i].StatusFlag = 0;
                    Control con = (Control)this.GetType().GetField(Global.listControls[i].ControlName, System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.IgnoreCase).GetValue(this);
                    if (Global.listControls[i].LinkKind == "area")
                    {
                        con.Text = Global.listControls[i].RunText;
                        con.BackColor = Global.listControls[i].RunColor;
                    }
                    else
                    {
                        con.BackColor = Global.listControls[i].RunColor;
                    }
                }
            }
        }

        //重新建表
        private void CreateBoardParamTable()
        {
            Global.mysqlHelper.ExecuteSql("DROP TABLE IF EXISTS board_param");
            StringBuilder sb = new StringBuilder();
            sb.Append("create table board_param (");
            sb.Append("`id` int(11) NOT NULL AUTO_INCREMENT,");
            sb.Append(" `name` varchar(30) DEFAULT NULL COMMENT '控件名',");
            sb.Append("`controltype` varchar(50) DEFAULT NULL COMMENT '控件类型',");
            sb.Append("`linkindex` int(11) DEFAULT NULL COMMENT '关联序号',");
            sb.Append("`locationx` int(11) DEFAULT NULL COMMENT 'X位置',");
            sb.Append(" `locationy` int(11) DEFAULT NULL COMMENT 'Y位置',");
            sb.Append("`text` varchar(20) DEFAULT NULL COMMENT '显示内容',");
            sb.Append("`basecolor` varchar(20) DEFAULT NULL COMMENT '基础颜色',");
            sb.Append("`visible` varchar(10) DEFAULT NULL COMMENT '是否可见',");
            sb.Append("`editable` varchar(10) DEFAULT NULL COMMENT '是否可编辑',");
            sb.Append("`level` int(11) DEFAULT NULL,");
            sb.Append("`parentid` int(11) DEFAULT NULL,");
            sb.Append("`linkkind` varchar(20) DEFAULT '' COMMENT '关联系统类别，油枪或是识别区等',");
            sb.Append("PRIMARY KEY(`id`)");
            sb.Append(") ENGINE = InnoDB  DEFAULT CHARSET = utf8");
            Global.mysqlHelper.ExecuteSql(sb.ToString());
            Global.LogServer.Add(new LogInfo("Debug", "Main->CreateBoardParamTable 执行SQL:" + sb.ToString(), (int)EnumLogLevel.DEBUG));

        }

        //重置所有面板信息
        private void StationBoardReset()
        {
            Global.LogServer.Add(new LogInfo("Debug", "Main->StationBoardReset", (int)EnumLogLevel.DEBUG));
            CreateBoardParamTable();
            ForeachStationBoard(StationBoard, 1, 0);
            Global.mysqlHelper.ExecuteSql("update board_param set linkkind = 'area' where name like '%area%'");
            Global.mysqlHelper.ExecuteSql("update board_param set linkkind = 'nozzle' where name like '%Noz%'");
            Global.mysqlHelper.ExecuteSql("update board_param set linkkind = 'island' where name like '%Island%'");
            Global.mysqlHelper.ExecuteSql("update board_param set linkkind = 'text' where name like '%Text%'");
            GetSatationBoardParamFromDB();
            FlushStationBoard();
        }

        //从数据提取面板控件参数
        private void UpdateStationBoardParamToDB()
        {
            string sql = "update param set  paramValue = '" + Global.bShowStationBoard.ToString() + "' where paramName = 'showstationboard'";
            Global.mysqlHelper.ExecuteSql(sql);
            sql = "update param set paramValue = '" + Global.nStationBoardDirection.ToString() + "' where paramName = 'stationboarddirection'";
            Global.mysqlHelper.ExecuteSql(sql);

            foreach (ControlBoard cb in Global.listControls)
            {
                if (cb.level < 3) //等级小于2的更新坐标位置
                {
                    Control con = (Control)this.GetType().GetField(cb.ControlName, System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.IgnoreCase).GetValue(this);
                    cb.LocationX = con.Location.X;
                    cb.LocationY = con.Location.Y;
                }

                Global.mysqlHelper.ExecuteSql(cb.getUpdateSQL());
            }
        }
        //遍历控件并存入数据库
        private void ForeachStationBoard(Control cointainer, int level, int parentid)
        {
            foreach (Control con in cointainer.Controls)
            {
                ControlBoard cb = new ControlBoard();
                cb.LocationX = con.Location.X;
                cb.LocationY = con.Location.Y;
                cb.ShowText = con.Text.Trim();
                cb.Visible = con.Visible;
                cb.Visible = true;
                cb.Editable = con.Enabled;
                cb.BaseColor = con.BackColor.ToString();
                cb.ControlName = con.Name;
                cb.ControlType = con.GetType().ToString();
                cb.level = level;
                cb.ParentId = parentid;
                cb.id = Global.mysqlHelper.ExecuteSqlGetId(cb.getInsertSQL());
                ForeachStationBoard(con, level + 1, cb.id);
            }
        }

    }
}
