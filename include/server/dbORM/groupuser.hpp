
#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.hpp"

// 群组用户，多了一个 role 角色信息，从 User 类直接继承，复用 User 的其它信息
class GroupUser : public User {
public:
	void setRole(string role) { this->role = role; }
	string getRole() { return this->role; }

private:
	string role;
};

#endif
