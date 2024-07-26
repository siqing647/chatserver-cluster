# ������־

### 1 test json

### 2 test muduo

### 3 Ŀ¼�ṹ + CMakeLists.txt

```shell
.
������ bin
��   ������ ChatClient
��   ������ ChatServer
������ CMakeLists.txt
������ include
��   ������ server
������ lib
������ logs.md
������ README.md
������ src
��   ������ client
��   ��   ������ CMakeLists.txt
��   ������ CMakeLists.txt
��   ������ server
��       ������ CMakeLists.txt
������ test
��   ������ testjson
��   ��   ������ json.hpp
��   ��   ������ testjson.cpp
��   ������ testmuduo
��       ������ CMakeLists.txt
��       ������ muduo_server.cpp
������ thirdparty
    ������ json.hpp
```

### 4 ��Ŀ���ݿ��Լ�������

### 5 ����ģ�� ChatServer

```shell
/include/server/ChatServer.hpp
/src/server/ChatServer.cpp
```

### 6 ҵ��ģ�� ChatService

```shell
/include/server/ChatService.hpp
/src/server/ChatService.cpp
/include/public.hpp
```

1. `static` ʵ�ֵ���ģʽ
2. ͨ�� `MsgHandler getHandler(int msgid);` ��Ԥ�ûص�**��������ģ���ҵ��ģ��**
3. ʹ�� `unordered_map` �洢��Ϣ�źͻص�������ӳ���ϵ����ʹ�ð��� `std::bind` ���а�

> **������ģ��ַ�ҵ���¼��ص��������ܽ��в���**

### 7 ���ݿ�ģ��

```shell
/include/server/MySQLConnectionPoll/
```

���� [MySQL Connection Pool](https://github.com/Corner430/MySQL-Connection-Pool) ʹ�����ݿ����ӳ�

~~�� `ChatService` ��������ݿ����ӳض��󣬲��ڹ��캯���г�ʼ��~~

### 8 Model ���ݲ���������

```shell
/include/server/dbORM/  # ���ݿ� ORM ���
/include/server/model/
/src/server/model/
```

1. `dbORM` ���ݿ� ORM ���
2. `model` ���ݲ���������
3. **`include/server/model/model.hpp` �ж����˵���ģʽ�����ӳض��󣬱����е� Model ��̳й���**

> **����ҵ��ģ������ݿ�ģ��**

### 9 �û���½/ע��/�˳�ҵ��ʵ�ּ�����

1. `ChatService::login`, `ChatService::reg`, `ChatService::loginout`, `usermodel`
2. ʹ�� `unordered_map<int, TcpConnectionPtr> _userConnMap;` �洢�����û���ͨ�����ӣ�Ϊ��֤�̰߳�ȫ��ʹ�� `lock_guard` ���м���

### 10 �ͻ����쳣�˳�ҵ��ʵ�ּ�����

1. `ChatService::clientCloseException()` ���������ͻ����쳣�˳�ʱ�����û��������û��б���ɾ�������������ݿ����û���״̬
2. �޸� `ChatServer::onConnection()` ���������ͻ����쳣�˳�ʱ������ `ChatService::clientCloseException` ����

### 11 ��Ե�����ҵ��ʵ�ּ�����

`ChatService::oneChat()` ������ʵ�ֵ�Ե�����ҵ��

### 12 ������Ϣҵ��ʵ�ּ�����

offlinemessagemodel.cpp

### 13 �������쳣�˳�ʵ�ּ�����

`/src/server/main.cpp` ����� [`signal`](https://en.cppreference.com/w/cpp/utility/program/signal) �źŴ����������������쳣�˳�ʱ������ `ChatService::reset()` �������������û������ݿ��и���Ϊ����״̬

### 14 ��Ӻ���ҵ��ʵ�ּ�����

`ChatService::addFriend()`, `friendmodel.cpp`

### 15 Ⱥ���������ҵ��

### 16 �ͻ��˿���

> ���ڵ�ǰ�û�����Ϣ��������Ϣ��Ⱥ����Ϣ���д洢�����ⷴ���ӷ�������ȡ

#### 16.1 ��ҳ���湦�ܿ���������

#### 16.2 ��Ӻ��Ѻ����칦�ܿ���������

#### 16.3 ������Ϣ���ܿ���������

#### 16.4 Ⱥ�����칦�ܿ���������

#### 16.5 �û�ע�����ܿ���������

#### 17 ���� redis ����-���ĵ���Ϣ����ʵ�ּ�Ⱥ��������ʵʱͨ��

#### 18 nginx �������ʵ�ָ��ؾ���