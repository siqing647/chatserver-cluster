
#include "friendmodel.hpp"

// ��Ӻ��ѹ�ϵ
void FriendModel::insert(int userid, int friendid) {
    // 1. ��װ sql ���
    char sql[1024] = { 0 };
    sprintf(sql, "insert into friend values(%d, %d)", userid, friendid);

    shared_ptr<Connection> sp = _connPool->getConnection();
    if (sp) sp->update(sql);
}

// �����û������б�
vector<User> FriendModel::query(int userid) {
    // 1. ��װ sql ���
    char sql[1024] = { 0 };

    sprintf(sql,
        "select a.id, a.name, a.state from user a inner join friend b on "
        "b.friendid = a.id where b.userid=%d",
        userid);

    vector<User> vec;
    shared_ptr<Connection> sp = _connPool->getConnection();
    if (sp) {
        MYSQL_RES* res = sp->query(sql);
        if (res != nullptr) {
            // �� userid �û������к�����Ϣ���� vec �з���
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr) {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                vec.push_back(user);
            }
            mysql_free_result(res);
            return vec;
        }
    }
    return vec;
}
