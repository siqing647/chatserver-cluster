#pragma once

#include "CommonConnectionPool.h"

class model {
public:
	model() { _connPool = ConnectionPool::getConnectionPool(); }
	// ������������ӳ�
	ConnectionPool* _connPool;
};
