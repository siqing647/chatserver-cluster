
#ifndef OFFLINEMESSAGEMODEL_H
#define OFFLINEMESSAGEMODEL_H

#include "model.hpp"
#include <string>
#include <vector>
using namespace std;

// �ṩ������Ϣ��Ĳ����ӿڷ���
class OfflineMsgModel : public model {
public:
	// �洢�û���������Ϣ
	void insert(int userid, string msg);

	// ɾ���û���������Ϣ
	void remove(int userid);

	// ��ѯ�û���������Ϣ
	vector<string> query(int userid);
};

#endif
