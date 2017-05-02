//////////////////////////////////////////////////////////////////////////
//Commit:   通用数据库操作类
//Author:   HYF
//Date：    2017-04-28
//Version:  1.0
//////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Data;
using System.Data.Common;
using System.Data.SqlClient;
using MySql.Data.MySqlClient;

namespace SPManager
{
    public class MysqlHelper
    {
        private DBInfo LocalDB;
        private string DbConnString = "";
        private MySqlConnection myDBConn = null;
        private MySqlConnection DBConn = null;

        public MysqlHelper()
        {
        }
        public MysqlHelper(DBInfo dbinfo)
        {
            this.LocalDB = dbinfo;
            ConnectDB();
        }

        public void SetDBInfo(DBInfo info)
        {
            this.LocalDB = info;
        }
        /************************************************************************
          Function:  根据不同的数据库类型,获取不同的数据库连接                                      
          In:                                                           
          Out:  DbConnection,  which is opened    
          Author: HYF
          Date: 2017-04-28
        ************************************************************************/
        public bool ConnectDB()
        {
            DbConnString = @"server=" + this.LocalDB.ip + ";user id=" + this.LocalDB.username +
                                   ";password=" + this.LocalDB.password + ";database=" + this.LocalDB.dbname;
            this.DBConn = new MySqlConnection(DbConnString);
            try
            {
                this.DBConn.Open();
            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "DBUnit:ConnectDB 连接数据库失败，错误信息：" + ex.Message,(int)EnumLogLevel.ERROR));
                return false;
            }
            return true;
        }


        /************************************************************************
          Function:  根据sql语句获取DataReader                                      
          In:   string sql, DbConnection                                                        
          Out:  DataReader 
          Author: HYF
          Date: 2017-04-28
        ************************************************************************/
        public System.Data.IDataReader GetDataReader(string sql)
        {
            System.Data.IDataReader reader = null;
            if (this.DBConn == null)
            {
                Global.LogServer.Add(new LogInfo("Error", "DBUnit:GetDataReader 数据库连接对象为空", (int)EnumLogLevel.ERROR));
                return null;
            }
            try
            {
                if (this.DBConn.State == System.Data.ConnectionState.Closed)
                {
                    this.DBConn.Open();
                }
                if (this.DBConn.State == ConnectionState.Open)
                {
                    System.Data.IDbCommand cmd = this.DBConn.CreateCommand();
                    cmd.CommandText = sql;
                    reader = cmd.ExecuteReader();
                    return reader;
                }
            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "DBUnit:GetDataReader 执行sql语句失败！sql: " + sql, (int)EnumLogLevel.ERROR));
                return null;
            }
            return null;
        }

        /************************************************************************
          Function:  根据sql语句获取DataTable                                      
          In:   string sql, DbConnection                                                        
          Out:  DataTable 
          Author: HYF
          Date: 2017-04-28
        ************************************************************************/
        public System.Data.DataTable GetDataTable(string sql)
        {
            if (this.DBConn == null)
            {
                Global.LogServer.Add(new LogInfo("Error", "DBUnit:GetDataTable 数据库连接对象为空", (int)EnumLogLevel.ERROR));
                return null;
            }
            try
            {
                if (this.DBConn.State == System.Data.ConnectionState.Closed)
                {
                    this.DBConn.Open();
                }
                if (this.DBConn.State == ConnectionState.Open)
                {
                    System.Data.DataTable dt = new System.Data.DataTable();
                    System.Data.IDataReader reader = GetDataReader(sql);
                    dt.Load(reader);
                    return dt;
                }
            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "DBUnit:GetDataTable 错误信息：" + ex.Message, (int)EnumLogLevel.ERROR));
                return null;
            }
            return null;
        }

        /************************************************************************
          Function:  执行sql语句                                      
          In:   string sqlstr, DbConnection                                                        
          Out:  void
          Author: HYF
          Date: 2017-04-28
        ************************************************************************/
        public void ExecuteSql(string sqlstr)
        {
            if (this.DBConn == null)
            {
                Global.LogServer.Add(new LogInfo("Error", "DBUnit:ExecuteSql 数据库连接对象为空", (int)EnumLogLevel.ERROR));
                return ;
            }
            try
            {
                if (this.DBConn.State == System.Data.ConnectionState.Closed)
                {
                    this.DBConn.Open();
                }
                if (this.DBConn.State == ConnectionState.Open)
                {
                    using(System.Data.IDbCommand cmd = this.DBConn.CreateCommand())
                    {
                        cmd.CommandText = sqlstr;
                        cmd.ExecuteNonQuery();
                    }                    
                }                
            }
            catch (Exception ex)
            {
                Global.LogServer.Add(new LogInfo("Error", "DBUnit:ExecuteSql 执行sql语句失败！sql: " + sqlstr + "错误信息：" + ex.Message, (int)EnumLogLevel.ERROR));
                return;
            }
        }
    }

    public class DBInfo
    {
        public DBInfo(string Type,string DBName,string IP,int Port,string Username,string Password)
        {
            this.type = Type;
            this.dbname = DBName;
            this.ip = IP;
            this.port = Port;
            this.username = Username;
            this.password = Password;
        }
        public DBInfo()
        {
        }
        public string type
        {
            get { return _type; }
            set { _type = value; }
        }
        private string _type = "";
        public string dbname
        {
            get { return _dbname; }
            set { _dbname = value; }
        }
        private string _dbname = "";
        public string ip
        {
            get { return _ip; }
            set { _ip = value; }
        }
        private string _ip = "";
        public int port
        {
            get { return _port; }
            set { _port = value; }
        }
        private int _port = 3306;
        public string username
        {
            get { return _username; }
            set { _username = value; }
        }
        private string _username = "";
        public string password
        {
            get { return _password; }
            set { _password = value; }
        }
        private string _password = "";
    }
}
