
#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
using namespace muduo;
using namespace muduo::net;

// ���������������
class ChatServer {
public:
    // ��ʼ���������������
    ChatServer(EventLoop* loop, const InetAddress& listenAddr,
        const string& nameArg);

    // ��������
    void start();

private:
    // �ϱ����������Ϣ�Ļص�����
    void onConnection(const TcpConnectionPtr&);

    // �ϱ���д�¼������Ϣ�Ļص�����
    void onMessage(const TcpConnectionPtr&, Buffer*, Timestamp);

    TcpServer _server; // ��ϵ� muduo �⣬ʵ�ַ��������ܵ������
    EventLoop* _loop;  // ָ���¼�ѭ�������ָ��
};

#endif
