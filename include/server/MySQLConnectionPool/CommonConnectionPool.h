
#pragma once

/*
 * ���ݿ����ӳ�
 */

#include "Connection.h"
#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
using namespace std;

class ConnectionPool {
public:
	static ConnectionPool* getConnectionPool(); // ��ȡ���ӳض���
	shared_ptr<Connection> getConnection();     // ��ȡ��������

private:
	ConnectionPool(); // ����ģʽ

	bool loadConfigFile(); // �������ļ��м�������

	void produceConnectionTask(); // �������̣߳�����������

	void scannerConnectionTask(); // ��ʱ���������ӣ����ճ�ʱ����

	string _ip;             // ���ݿ�ip
	unsigned short _port;   // ���ݿ�˿�
	string _username;       // ���ݿ��û���
	string _password;       // ���ݿ�����
	string _dbname;         // ���ݿ���
	int _initSize;          // ���ݿ����ӳ����ӳ�ʼ����
	int _maxSize;           // ���ݿ����ӳ��������
	int _maxIdleTime;       // ������ʱ��
	int _connectionTimeout; // ���ݿ����ӳ�ʱʱ��

	queue<Connection*> _connectionQue; // ���Ӷ���
	mutex _queueMutex;                  // ���Ӷ��л�����
	condition_variable cv;     // �������������ڻ����������߳�
	atomic_int _connectionCnt; // ��ǰ�Ѵ�����������
};
