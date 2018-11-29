using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;

namespace SPManager
{
    public class ControlBoard
    {
        public ControlBoard()
        {

        }
        public ControlBoard(DataRow dr)
        {
            this.id = int.Parse(dr["id"].ToString());
            this.ControlName = dr["name"].ToString();
            this.ControlType = dr["controltype"].ToString();
            this.LinkKind = dr["linkkind"].ToString();
            this.LinkIndex = int.Parse(dr["linkindex"].ToString());
            this.LocationX = int.Parse(dr["locationx"].ToString());
            this.LocationY = int.Parse(dr["locationy"].ToString());
            this.ShowText = dr["text"].ToString();
            this.BaseColor = dr["basecolor"].ToString();
            this.Visible = bool.Parse(dr["visible"].ToString());
            this.Editable = bool.Parse(dr["editable"].ToString());
            this.level = int.Parse(dr["level"].ToString());
            this.ParentId = int.Parse(dr["parentid"].ToString());
        }
        public int id { set; get; }
        public string ControlName { set; get; }
        public string ControlType { set; get; }
        public string LinkKind { set; get; }
        public int LinkIndex { set; get; }
        public int LocationX { set; get; }
        public int LocationY { set; get; }
        public string ShowText { set; get; }
        public string BaseColor { set; get; }

        public bool Visible { set; get; }
        public bool Editable { set; get; }
        public int level { set; get; }
        public int ParentId { set; get; }
        public string RunText { set; get; }
        public Color RunColor { set; get; }

        public int StatusFlag { set; get; }
        public string getUpdateSQL()
        {
         
            String sqlString = "update board_param set linkkind = '{0}',linkindex = {1},locationx = {2},locationy = {3},text = '{4}',basecolor = '{5}',visible = '{6}'," +
                                "editable = '{7}',level = {8},parentid = {9} where id = {10}";
            return String.Format(sqlString, LinkKind, LinkIndex.ToString(), LocationX.ToString(), LocationY.ToString(), ShowText, BaseColor, Visible, Editable, level.ToString(), ParentId.ToString(),id.ToString());
            
        }
        public string getInsertSQL()
        {
            String sqlString = "INSERT into board_param (name,controltype,linkkind,linkindex,locationx,locationy,text,basecolor,visible,editable,level,parentid)" +
       "VALUES('{0}', '{1}', '{2}', {3}, {4}, {5}, '{6}', '{7}', '{8}', '{9}', {10}, {11}) ";
            return String.Format(sqlString, ControlName, ControlType, LinkKind, LinkIndex.ToString(), LocationX.ToString(), LocationY.ToString(), ShowText, BaseColor,Visible, Editable,level.ToString() ,ParentId.ToString());

        }

    }
}
