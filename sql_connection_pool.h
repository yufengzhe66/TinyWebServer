#ifndef _CONNECTION_POOL_
#define _CONNECTION_POOL_

#include<stdio.h>
#include<list>
#include<mysql/mysql.h>
#include<error.h>
#include<string.h>
#include<iostream>
#include<string>
#include "locker.h"
#include "log.h"


using namespace std;

class connection_pool
{
public:
    MYSQL *GetConnection();
    bool ReleaseConnection();
    int GetFreeConn();
    void DestroyPool();

    static connection_pool *GetInstance();     //单例模式
    
    void init(string url, string User, string PassWord, string DataBaseName, int Port, int MaxConn, int close_log);

private:
    connection_pool();
    ~connection_pool();

    int m_MaxConn;
    int m_CurConn;
    int m_FreeConn;
    locker lock;
    list<MYSQL *> connList;
    sem reserve;

public:
    string m_url;                              //主机地址
    string m_Port;                             //数据库端口号
    string m_User;                             //登录数据库用户名
    string m_PassWord;                         //登录数据库密码
    string m_DatabaseName;                     //使用数据库名
    int m_close_log;                           //日志开关
};

class connectionRAII
{
public:
    connectionRAII(MYSQL **conn, connection_pool *connPool);
    ~connectionRAII();


private:
    MYSQL *conRAII;
    connection_pool *poolRAII;
};


#endif

