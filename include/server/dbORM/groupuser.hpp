
#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.hpp"

// Ⱥ���û�������һ�� role ��ɫ��Ϣ���� User ��ֱ�Ӽ̳У����� User ��������Ϣ
class GroupUser : public User {
public:
	void setRole(string role) { this->role = role; }
	string getRole() { return this->role; }

private:
	string role;
};

#endif
