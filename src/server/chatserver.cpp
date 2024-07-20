
#include "chatserver.hpp"
#include "chatservice.hpp"
#include "json.hpp"

#include <functional>
#include <iostream>
#include <string>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

// ��ʼ���������������
ChatServer::ChatServer(EventLoop* loop, const InetAddress& listenAddr,
    const string& nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop) {
    // ע�����ӻص�
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    // ע����Ϣ�ص�
    _server.setMessageCallback(
        std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // �����߳�����
    _server.setThreadNum(4);
}

// ��������
void ChatServer::start() { _server.start(); }

// �ϱ����������Ϣ�Ļص�����
void ChatServer::onConnection(const TcpConnectionPtr& conn) {
    if (!conn->connected()) { // �ͻ��˶Ͽ�����
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}

// �ϱ���д�¼������Ϣ�Ļص�����
void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buffer,
    Timestamp time) {
    string buf = buffer->retrieveAllAsString();

    // ���ԣ����json��ӡ����
    // cout << buf << endl;

    // ���ݵķ����л�
    json js = json::parse(buf);

    // ���ã���ȫ��������ģ��Ĵ����ҵ��ģ��Ĵ���
    // ͨ�� js["msgid"] �� get<int>() ������ȡ��Ϣ����
    // ������Ϣ���ͣ����ض�Ӧ��ҵ������������һ���ص����������󣩣�
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());

    // ͨ�����Ȱ󶨺õĻص���������ִ����Ӧ��ҵ����
    msgHandler(conn, js, time);
}
