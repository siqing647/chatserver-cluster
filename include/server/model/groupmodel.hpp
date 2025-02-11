
#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include "group.hpp"
#include "model.hpp"
#include <string>
#include <vector>
using namespace std;

// 维护群组信息的操作接口方法
class GroupModel : public model {
public:
	// 创建群组
	bool createGroup(Group& group);
	// 加入群组
	void addGroup(int userid, int groupid, string role);
	// 查询用户所在群组信息
	vector<Group> queryGroups(int userid);
	// 根据指定的 groupid 查询群组用户 id 列表，除 userid 自己
	// 主要用于群聊业务给群组其它成员群发消息
	vector<int> queryGroupUsers(int userid, int groupid);
};

#endif
