
#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <functional>
#include <muduo/net/TcpConnection.h>
#include <mutex>
#include <unordered_map>
using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "CommonConnectionPool.h"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "json.hpp"
#include "offlinemessagemodel.hpp"
#include "usermodel.hpp"
using json = nlohmann::json;

// ��ʾ������Ϣ���¼��ص���������
using MsgHandler =
std::function<void(const TcpConnectionPtr& conn, json& js, Timestamp)>;

// ���������ҵ����
class ChatService {
public:
    // ��ȡ��������Ľӿں���
    static ChatService* instance();

    // ������������ӳ�
    ConnectionPool* _connPool;

    // �����¼ҵ��
    void login(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // ����ע��ҵ��
    void reg(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // һ��һ����ҵ��
    void oneChat(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // ��Ӻ���ҵ��
    void addFriend(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // ����Ⱥ��ҵ��
    void createGroup(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // ����Ⱥ��ҵ��
    void addGroup(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // Ⱥ������ҵ��
    void groupChat(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // ����ע��ҵ��
    void loginout(const TcpConnectionPtr& conn, json& js, Timestamp time);
    // ����ͻ����쳣�˳�
    void clientCloseException(const TcpConnectionPtr& conn);
    // �������쳣��ҵ�����÷���
    void reset();

    // ��ȡ��Ϣ��Ӧ�Ĵ�����
    MsgHandler getHandler(int msgid);

private:
    ChatService();

    // �洢��Ϣ id �����Ӧ��ҵ������
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // �洢�����û���ͨ������
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    // ���廥��������֤ _userConnMap ���̰߳�ȫ
    mutex _connMutex;

    // ���ݲ��������
    UserModel _userModel;
    OfflineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;
};

#endif
