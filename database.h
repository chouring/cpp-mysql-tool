#ifndef __MYSQL_H__
#define __MYSQL_H__

#include<mysql/mysql.h>
#include<iostream>
#include<string>
using namespace std;

class DataBaseController {
public:
    MYSQL* con;
    MYSQL_RES* res_ptr;
    MYSQL_ROW res_row;
    MYSQL_FIELD* field;
    string host;
    string user;
    string pwd;
    string db_name;
    int column;
    int row;

    DataBaseController() {
        con = mysql_init(NULL);
    }

    void init(string host, string user, string pwd, string db_name) {
        this->host = host;
        this->user = user;
        this->pwd = pwd;
        this->db_name = db_name;
        mysql_real_connect(this->con, this->host.c_str(), this->user.c_str(), this->pwd.c_str(), this->db_name.c_str(), 0, NULL, 0);
    }

    void query(string sql) {
        mysql_query(con, sql.c_str());
        
    }

    void printRes(int k) {
        res_ptr = mysql_store_result(con);
        this->column = mysql_num_fields(res_ptr);
        this->row = mysql_num_rows(res_ptr) + 1;
        printf("查到%d行", row);
        puts("");
        char *str_field[32];  //定义一个字符串数组存储字段信息
        for (int i = 0; i < k; i++)   //在已知字段数量的情况下获取字段名 
        {
            str_field[i] = mysql_fetch_field(res_ptr)->name;	//返回一个所有字段结构的数组。
        }
        for (int i = 0; i < k; i++)   //打印字段  
            printf("%s  \t", str_field[i]);
	    puts("");
        for (int i = 1; i < row; i++) {
            res_row = mysql_fetch_row(res_ptr);
            for (int j = 0; j < column; j++) {
                printf("%s\t", res_row[j]);
            }
            printf("\n");
        }
    }
    void close() {
        mysql_close(con);
    }
};

#endif



// int main() {
//     MYSQL* con = mysql_init(NULL);
//     MYSQL_RES* res_ptr;
//     MYSQL_ROW res_row;
//     MYSQL_FIELD* field;
//     string host = "localhost";
//     string user = "root";
//     string pwd = "123456";
//     string db_name = "student_info";
//     mysql_real_connect(con, host.c_str(), user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
//     mysql_query(con, "set names utf-8");
//     mysql_query(con, "select * from students");
//     res_ptr = mysql_store_result(con);
//     int column = mysql_num_fields(res_ptr);
//     int row = mysql_num_rows(res_ptr) + 1;
//     mysql_close(con);
//     DataBaseController dbc;
//     dbc.init("localhost", "root", "123456", "student_info");
//     dbc.query("select * from students");
//     dbc.printRes();
//     dbc.query("insert into students values ('3', '22', 'wuming', 'science')");
//     dbc.query("select * from students");
//     dbc.printRes();
//     dbc.query("DELETE FROM students WHERE id=3;");
//     dbc.query("select * from students");
//     dbc.printRes();
//     dbc.close();
//     return 0;
// }
