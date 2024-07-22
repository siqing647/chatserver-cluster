
#ifndef REDIS_H
#define REDIS_H

#include <functional>
#include <hiredis/hiredis.h>
#include <thread>
using namespace std;

/*
 * redis ��Ϊ��Ⱥ������ͨ�ŵĻ��ڷ���-������Ϣ����ʱ�������������Ѹ�� bug ����
 * bug 1. ����Ϣ�м�� PUBLISH ������Ϣ���ɹ��������޷��������ͨ��
 * bug 2. ������м�� SUBSCRIBE ������Ϣ����������Ӧ���ͻ���Ҳ����Ӧ
 */
class Redis {
public:
	Redis();
	~Redis();

	// ���� redis ������
	bool connect();

	// �� redis ָ����ͨ�� channel ������Ϣ
	bool publish(int channel, string message);

	// �� redis ָ����ͨ�� subscribe ������Ϣ
	bool subscribe(int channel);

	// �� redis ָ����ͨ�� unsubscribe ȡ��������Ϣ
	bool unsubscribe(int channel);

	// �ڶ����߳��н��ն���ͨ���е���Ϣ
	void observer_channel_message();

	// ��ʼ����ҵ����ϱ�ͨ����Ϣ�Ļص�����
	void init_notify_handler(function<void(int, string)> fn);

private:
	// hiredis ͬ�������Ķ��󣬸��� publish ��Ϣ
	redisContext* _publish_context;

	// hiredis ͬ�������Ķ��󣬸��� subscribe ��Ϣ
	redisContext* _subcribe_context;

	// �ص��������յ����ĵ���Ϣ����service���ϱ�
	function<void(int, string)> _notify_message_handler;
};

#endif
