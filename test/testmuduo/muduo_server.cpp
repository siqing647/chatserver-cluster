
/*
muduo �������û��ṩ��������Ҫ����
TcpServer �� ���ڱ�д����������
TcpClient �� ���ڱ�д�ͻ��˳���

epoll + �̳߳� + �¼�ѭ�� + �¼�����
�ŵ㣺���԰����� I/O ��ҵ����ֿ���д
*/

#include <iostream>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>

using namespace std;
using namespace muduo;
using namespace muduo::net;

/* ���� muduo ����⿪���������������Ҫ����
1. ����һ�� EventLoop ���� loop
2. ����һ�� InetAddress ���� listenAddr��ָ���������� IP ��ַ�Ͷ˿�
3. ����һ�� TcpServer ���� server
4. ���� TcpServer ���� server �ĸ�������
5. ���� TcpServer ���� server �ĸ��ֻص�����
6. ���� TcpServer ���� server �� start() ����
7. �� EventLoop ���� loop �� loop() ������ѭ���ȴ��ͻ��˵����Ӻ���Ϣ
*/

class ChatServer {
public:
    ChatServer(EventLoop* loop, const InetAddress& listenAddr,
        const string& nameArg)
        : server_(loop, listenAddr, nameArg), loop_(loop) {
        // ע�����ӻص��������ͻ������ӺͶϿ���
        server_.setConnectionCallback(bind(&ChatServer::onConnection, this, _1));

        // ע����Ϣ�ص���������д�¼���
        server_.setMessageCallback(bind(&ChatServer::onMessage, this, _1, _2, _3));

        // �����߳����� 4 ����1 �� I/O �̣߳�3 �������̣߳�
        server_.setThreadNum(4);
    }

    void start() { server_.start(); }

private:
    // ���ӻص�����
    void onConnection(const TcpConnectionPtr& conn) {
        if (conn->connected())
            cout << conn->peerAddress().toIpPort() << " -> "
            << conn->localAddress().toIpPort() << " state: connected\n";
        else {
            cout << conn->peerAddress().toIpPort() << " -> "
                << conn->localAddress().toIpPort() << " state: disconnected\n";
            conn->shutdown(); // close(fd)
        }
    }

    // ��Ϣ�ص������������д�¼�
    void onMessage(const TcpConnectionPtr& conn /* ���� */,
        Buffer* buffer /* ������ */,
        Timestamp time /* ���յ����ݵ�ʱ����Ϣ */) {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data: " << buf << " time: " << time.toFormattedString()
            << endl;
        conn->send(buf);
    }

    TcpServer server_; // ����������
    EventLoop* loop_;  // �¼�ѭ������epoll��
};

int main() {
    EventLoop loop;
    InetAddress listenAddr(8888);
    // InetAddress listenAddr("127.0.0.1", 8888);
    ChatServer server(&loop, listenAddr, "ChatServer");

    server.start(); // ������������epoll_ctl ���¼�
    loop.loop();    // �����¼�ѭ����epoll_wait
    // �����ȴ��¼������û������ӡ��������û��Ķ�д�¼�������
    return 0;
}
