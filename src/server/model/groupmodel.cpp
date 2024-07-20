
#include "groupmodel.hpp"

// ����Ⱥ��
bool GroupModel::createGroup(Group& group) {
    // 1. ��װ sql ���
    char sql[1024] = { 0 };
    sprintf(sql, "insert into allgroup(groupname, groupdesc) values('%s', '%s')",
        group.getName().c_str(), group.getDesc().c_str());

    shared_ptr<Connection> sp = _connPool->getConnection();
    if (sp)
        if (sp->update(sql)) {
            // �� group �� id ����Ϊ��ǰ��������ݵ� id��������������
            group.setId(mysql_insert_id((*sp).getConnection()));
            return true;
        }

    return false;
}

// ����Ⱥ��
void GroupModel::addGroup(int userid, int groupid, string role) {
    // 1. ��װ sql ���
    char sql[1024] = { 0 };
    sprintf(sql, "insert into groupuser values(%d, %d, '%s')", groupid, userid,
        role.c_str());

    shared_ptr<Connection> sp = _connPool->getConnection();
    if (sp)
        sp->update(sql);
}

// ��ѯ�û�����Ⱥ����Ϣ
vector<Group> GroupModel::queryGroups(int userid) {
    /*
     * 1. �ȸ��� userid �� groupuser ���в�ѯ�����û�������Ⱥ����Ϣ
     * 2. �ٸ���Ⱥ����Ϣ����ѯ���ڸ�Ⱥ��������û��� userid
     *    ���Һ� user ����ж�����ϲ�ѯ������û�����ϸ��Ϣ
     */
    char sql[1024] = { 0 };
    sprintf(sql,
        "select a.id, a.groupname, a.groupdesc from allgroup a inner join \
         groupuser b on a.id = b.groupid where b.userid=%d",
        userid);

    vector<Group> groupVec;

    shared_ptr<Connection> sp = _connPool->getConnection();
    if (sp) {
        MYSQL_RES* res = sp->query(sql);
        if (res != nullptr) {
            MYSQL_ROW row;
            // ��� userid ���е�Ⱥ����Ϣ
            while ((row = mysql_fetch_row(res)) != nullptr) {
                Group group;
                group.setId(atoi(row[0]));
                group.setName(row[1]);
                group.setDesc(row[2]);
                groupVec.push_back(group);
            }
            mysql_free_result(res);
        }
    }

    // ��ѯȺ����û���Ϣ
    for (Group& group : groupVec) {
        sprintf(sql, "select a.id, a.name, a.state, b.grouprole from user a \
            inner join groupuser b on b.userid = a.id where b.groupid=%d",
            group.getId());

        MYSQL_RES* res = sp->query(sql);
        if (res != nullptr) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr) {
                GroupUser user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                user.setRole(row[3]);
                group.getUsers().push_back(user);
            }
            mysql_free_result(res);
        }
    }
    return groupVec;
}

// ����ָ���� groupid ��ѯȺ���û� id �б��� userid �Լ�
// ��Ҫ����Ⱥ��ҵ���Ⱥ��������ԱȺ����Ϣ
vector<int> GroupModel::queryGroupUsers(int userid, int groupid) {
    char sql[1024] = { 0 };
    sprintf(sql,
        "select userid from groupuser where groupid = %d and userid != %d",
        groupid, userid);

    vector<int> idVec;
    shared_ptr<Connection> sp = _connPool->getConnection();
    if (sp) {
        MYSQL_RES* res = sp->query(sql);
        if (res != nullptr) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
                idVec.push_back(atoi(row[0]));
            mysql_free_result(res);
        }
    }
    return idVec;
}
