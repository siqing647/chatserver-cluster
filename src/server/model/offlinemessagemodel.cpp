
#include "offlinemessagemodel.hpp"

// �洢�û���������Ϣ
void OfflineMsgModel::insert(int userid, string msg) {
    // 1. ��װ sql ���
    char sql[1024] = { 0 };
    sprintf(sql, "insert into offlinemessage values(%d, '%s')", userid,
        msg.c_str());

    shared_ptr<Connection> sp = _connPool->getConnection();
    if (sp)
        sp->update(sql);
}

// ɾ���û���������Ϣ
void OfflineMsgModel::remove(int userid) {
    // 1. ��װ sql ���
    char sql[1024] = { 0 };
    sprintf(sql, "delete from offlinemessage where userid=%d", userid);

    shared_ptr<Connection> sp = _connPool->getConnection();
    if (sp)
        sp->update(sql);
}

// ��ѯ�û���������Ϣ
vector<string> OfflineMsgModel::query(int userid) {
    // 1. ��װ sql ���
    char sql[1024] = { 0 };
    sprintf(sql, "select message from offlinemessage where userid = %d", userid);

    vector<string> vec;
    shared_ptr<Connection> sp = _connPool->getConnection();
    if (sp) {
        MYSQL_RES* res = sp->query(sql);
        if (res != nullptr) {
            // �� userid �û�������������Ϣ���� vec �з���
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
                vec.push_back(row[0]);
            mysql_free_result(res);
            return vec;
        }
    }
    return vec;
}
