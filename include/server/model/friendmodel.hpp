
#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include "model.hpp"
#include "user.hpp"
#include <vector>
using namespace std;

// ά��������Ϣ�Ĳ����ӿڷ���
class FriendModel : public model {
public:
	// ��Ӻ��ѹ�ϵ
	void insert(int userid, int friendid);

	// �����û������б�
	vector<User> query(int userid);
};

#endif
