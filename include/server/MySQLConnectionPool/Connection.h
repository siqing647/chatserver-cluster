
#pragma once

#include <mysql/mysql.h>
#include <string>

using namespace std;

class Connection {
public:
    Connection();  // ��ʼ�����ݿ�����
    ~Connection(); // �ͷ����ݿ�������Դ
    bool connect(string ip, unsigned int port, string username, string password,
        string dbname);  // �������ݿ�
    bool update(string sql);      // ���²���, insert, update, delete
    MYSQL_RES* query(string sql); // ��ѯ����, select

    // ��ȡ��ǰ MySQL ����
    MYSQL* getConnection() const { return _conn; }

    // ˢ�����ӵ���ʼ�Ŀ���ʱ��㣬clock() ���ص��� CPU ʱ��
    void refreshAliveTime() { _alivetime = clock(); }

    // ���ش���ʱ��
    clock_t getAliveTime() const { return clock() - _alivetime; }

private:
    MYSQL* _conn;       // ���ݿ�����
    clock_t _alivetime; // ��¼���ӵĿ���ʱ����ʼ��
};
