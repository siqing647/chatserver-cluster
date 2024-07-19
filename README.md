# �����������Ⱥ��

- [���������������](https://github.com/Corner430/chatserver/tree/standalone)
- [�����������Ⱥ��](https://github.com/Corner430/chatserver/tree/cluster)

ʹ�÷�ʽ

```shell
mkdir build && cmake .. && make # ֮�����п�ִ���ļ�����
```

## 1 ��������

[��Ⱥ�� Docker ����������Ubuntu 22.04](https://github.com/Corner430/Docker/tree/main/chatserver-cluster)

�õ��ļ���ջ��

- Json ���л��ͷ����л��������� [json for Modern C++](https://github.com/nlohmann/json)
- muduo ����⿪���������� [muduo](https://github.com/chenshuo/muduo)
- [nginx Դ��](https://github.com/nginx/nginx)���밲װ�ͻ�������
- nginx �� tcp ���ؾ���������
- ���ڷ���-���ĵķ������м�� redis ��Ϣ���б��ʵ���������� [hiredis](https://github.com/redis/hiredis)
- MySQL ���ӳص�ʹ�ã������� [MySQL-Connection-Pool](https://github.com/Corner430/MySQL-Connection-Pool)


## 2 ��Ŀ����

1. �ͻ������û�ע��
2. �ͻ����û���¼
3. �ͻ����û��˳�
4. ��Ӻ��Ѻ�Ⱥ��
5. ��������
6. Ⱥ������
7. ������Ϣ
8. nginx ���� tcp ���ؾ���
9. ��Ⱥ����ϵͳ֧�ֿͻ��˿������ͨ��

## 3 ��ĿĿ��

1. ���շ����������� I/O ģ�飬ҵ��ģ�飬����ģ��ֲ�����˼��
2. ���� C++ muduo �����ı���Լ�ʵ��ԭ��
3. ���� Json �ı��Ӧ��
4. ���� MySQL ���ӳص�ʹ��
5. ���� Docker һ������
6. ���� CMake
7. ���� nginx ���ò��� tcp ���ؾ�������Ӧ���Լ�ԭ��
8. ���շ������м����Ӧ�ó����ͻ��ڷ���-���ĵ� redis ���ʵ���Լ�Ӧ��ԭ��

## 4 JSON ���л��ͷ����л�

�ο��ٷ��ֿ���� [testjson.cpp ʾ���ļ�](https://github.com/Corner430/chatserver/blob/main/test/testjson/testjson.cpp)

## 5 muduo �����

muduo ��������ƣ�*reactors in threads --- one loop per thread*

�ص��� *one loop per thread*����һ�� *main reactor* ���� *accept* ���ӣ�Ȼ�����ӷַ���ĳһ�� *sub reactor* �������� *round-robin* �ķ�ʽ��ѡ�� *sub reactor*���������ӵ����в��������Ǹ� *sub reactor* �������߳�����ɡ�������ӿ��ܱ����ɵ�����߳��У��Գ������ CPU �Ķ�����ܡ�

*Reactor poll* �Ĵ�С�ǹ̶��ģ����� CPU ����Ŀȷ����
```cpp
// ���� EventLoop ���̸߳������ײ�ͨ�� EventLoopThreadPool �̳߳ع����߳��� EventLoopThread
_server.setThreadNum(10);
```

> ����й���ĺķ� CPU I/O �ļ������񣬿����ύ�������� ThreadPool �̳߳���ר�Ŵ����ʱ�ļ�������

������ϸ���ݲο� [muduo �ٷ��ĵ�](https://github.com/chenshuo/muduo) ���� [mymuduo](https://github.com/Corner430/mymuduo)

**ʹ�÷�ʽ**�ο�[muduo_server.cpp ʾ���ļ�](https://github.com/Corner430/chatserver/blob/main/test/testmuduo/muduo_server.cpp)

## 6 ��Ŀ�ṹ

```shell
.
������ bin # ��ִ���ļ�
��   ������ ChatClient
��   ������ ChatServer
������ build   # �����ļ�
������ CMakeLists.txt  # CMake �����ļ�
������ include # ͷ�ļ�
��   ������ public.hpp  # ����ͷ�ļ�
��   ������ server      # ������ͷ�ļ�
��       ������ chatserver.hpp  # ��������
��       ������ chatservice.hpp # ������ҵ����
��       ������ dbORM           # ���ݿ� ORM
��       ��   ������ group.hpp       # Ⱥ��
��       ��   ������ groupuser.hpp   # Ⱥ���û�
��       ��   ������ user.hpp        # �û�
��       ������ model           # ���ݿ����
��       ��   ������ friendmodel.hpp
��       ��   ������ groupmodel.hpp
��       ��   ������ model.hpp
��       ��   ������ offlinemessagemodel.hpp
��       ��   ������ usermodel.hpp
��       ������ MySQLConnectionPool # MySQL ���ӳ�
��       ��   ������ CommonConnectionPool.h
��       ��   ������ Connection.h
��       ��   ������ public.h
��       ������ redis
��           ������ redis.hpp
������ lib
��   ������ libmysql_connection_pool.so # MySQL ���ӳض�̬��
������ README.md   # ��Ŀ˵��
������ src # Դ�ļ�
��   ������ client
��   ��   ������ CMakeLists.txt
��   ��   ������ main.cpp
��   ������ CMakeLists.txt
��   ������ server
��       ������ chatserver.cpp
��       ������ chatservice.cpp
��       ������ CMakeLists.txt
��       ������ main.cpp
��       ������ model
��       ��   ������ friendmoel.cpp
��       ��   ������ groupmodel.cpp
��       ��   ������ offlinemessagemodel.cpp
��       ��   ������ usermodel.cpp
��       ������ redis
��           ������ redis.cpp
������ test        # �����ļ�
��   ������ testjson        # Json ���л��ͷ����л�����
��   ��   ������ json.hpp
��   ��   ������ testjson.cpp
��   ������ testmuduo       # muduo ��������
��       ������ CMakeLists.txt
��       ������ muduo_server.cpp
������ thirdparty
    ������ json.hpp    # Json ���л��ͷ����л�ͷ�ļ�
```

## 7 �������м��-���ڷ���-���ĵ� Redis

### 7.1 ��Ⱥ������֮���ͨ�����

�� ChatServer ��Ⱥ�����̨�������Ժ󣬵�¼�ڲ�ͬ�������ϵ��û���ν���ͨ�ţ�

![20240719114554](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240719114554.png)

�������ƣ��ø��� ChatServer ������**����֮��**���� TCP ���ӽ���ͨ�ţ���ȼ����ڷ���������֮����й㲥�����������ʹ��ÿ�����������Ƿ���ˣ����ǿͻ��ˣ�����������֮����϶�̫�ߣ�������ϵͳ��չ�����һ�ռ��ϵͳ������ socket ��Դ����������֮��Ĵ���ѹ���ܴ󣬲��ܹ���ʡ��Դ������Ŀͻ����ṩ�����������һ���ܲ��õ���ƣ�

��Ⱥ����ķ�����֮�����ͨ�ţ�**��õķ�ʽ���������м����Ϣ����**�����������������ʹ����ϵͳ����ϣ���߷���������Ӧ��������ʡ�������Ĵ�����Դ������ͼ��ʾ��

![20240719114641](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240719114641.png)

### 7.2 Redis ����-�����������

redis �ķ���-���Ļ��ƣ�����-����ģʽ���������ֽ�ɫ���ֱ�����Ϣ�ķ����ߺ���Ϣ�Ķ����ߡ������߿��Զ���һ�����߶�� channel�������߿�����ָ���� channel ������Ϣ�����ж����˸� channel �Ķ����߶����յ���Ϣ��

���� channel��`SUBSCRIBE channel [channel ...]`

```shell
root@14178aa96595:~# redis-cli
127.0.0.1:6379> SUBSCRIBE channel "corner"
Reading messages... (press Ctrl-C to quit)
1) "subscribe"
2) "channel"
3) (integer) 1
1) "subscribe"
2) "corner"
3) (integer) 2
1) "message"
2) "corner"
3) "hello corner!"
```

> ˵����`SUBSCRIBE` �����������ǰ�ͻ��ˣ�ֱ������Ϣ������ָ���� channel����ʱ����յ���Ϣ����״̬�£�ֻ��ִ�� `subscribe`��`unsubscribe`��`psubscribe`��`punsubscribe` �ĸ����

��һ���ͻ��ˣ�

```shell
root@14178aa96595:~# redis-cli
127.0.0.1:6379> publish "corner" "hello corner!"
(integer) 1
127.0.0.1:6379> 
```

> ˵����`publish` ����������ָ���� channel ������Ϣ������ֵ�Ƕ��ĸ� channel �Ķ�����������

���붩��״̬��ͻ��˿����յ� 3 �����͵Ļظ���ÿ�����͵Ļظ������� 3 ��ֵ���ֱ�����Ϣ���͡�channel ���ƺ���Ϣ�塣������Ϣ���͵Ĳ�ͬ��������ֵ������Ҳ��ͬ����Ϣ���͵�ȡֵ���£�
1. `subscribe`�����ĳɹ����ڶ���ֵ�Ƕ��ĳɹ��� channel ���ƣ�������ֵ�ǵ�ǰ�ͻ��˶��ĵ� channel ������
2. `message`���յ���Ϣ���ڶ���ֵ�ǲ�����Ϣ�� channel ���ƣ�������ֵ����Ϣ�塣
3. `unsubscribe`��ȡ�����ġ��ڶ���ֵ��ȡ�����ĵ� channel ���ƣ�������ֵ�ǵ�ǰ�ͻ��˶��ĵ� channel �������������Ϊ 0����ͻ��˻��˳�����״̬��

### 7.3 Redis ����-���ĵĿͻ��˱��

redis ֧�ֲ�ͬ�Ŀͻ��˱�����ԣ��� C��C++��Python��Java �ȡ�����ʹ�� C++ ������ԣ�ʹ�� [hiredis](https://github.com/redis/hiredis) ����б�̡�

��װ hiredis �⣺

```shell
git clone https://github.com/redis/hiredis  # ���� hiredis Դ��
cd hiredis  # ���� hiredis Ŀ¼
make    # ����
make install  # ��װ����ͷ�ļ������� /usr/local/include�������ļ������� /usr/local/lib
ldconfig /usr/local/lib   # ���¶�̬���ӿ�
```

## 8 ���ؾ���

### 8.1 ʲô�Ǹ��ؾ���

��̨������������Ӳ����Դ���������������޵ģ�����̨��������������Ӧ�ó����Ĳ���������ʱ������Ҫ���ǲ�������������ͬ����ͻ��˵Ĳ������󣬵��ǿͻ�����ô֪��ȥ���Ӿ�����̨��������?

��ʱ����Ҫһ̨���ؾ�������ͨ��Ԥ��ĸ����㷨��ָ���ͻ������ӷ�������

���ؾ������л��ڿͻ��˵ĸ��ؾ���ͷ������ĸ��ؾ���

### 8.2 nginx ���밲װ

�ڷ��������ټ�Ⱥ������У���������Ҫһ�����������õĸ��ؾ�������nginx �� 1.9 �汾֮ǰ��ֻ֧�� http Э�� web �������ĸ��ؾ��⣬�� 1.9 �汾��ʼ�Ժ�nginx ��ʼ֧�� tcp �ĳ����Ӹ��ؾ��⣬**���� nginx Ĭ�ϲ�û�б��� tcp ���ؾ���ģ�飬����ʱ����Ҫ���� `--with-stream` �������������ģ��**

> nginx ����ʱ���� `--with-stream` �������� tcp ���ؾ���ģ��

nginx ���밲װ��Ҫ�Ȱ�װ pcre��openssl��zlib �ȿ⣬Ҳ����ֱ�ӱ���ִ������� configure ������ݴ�����ʾ��Ϣ����װ��Ӧȱ�ٵĿ⡣

```shell
git clone https://github.com/nginx/nginx.git    # ���� nginx Դ��
apt update && apt install -y libpcre3 libpcre3-dev  # ��װ pcre ��
cd nginx    # ���� nginx Ŀ¼
./auto/configure --with-stream  # ���� nginx������ tcp ���ؾ���ģ��
make && make install    # ���밲װ
```

��ʱ nginx Ĭ�ϰ�װ�� `/usr/local/nginx` Ŀ¼�£������� 4 ��Ŀ¼ `conf  html  logs  sbin`����ִ���ļ��� `sbin` Ŀ¼�£������ļ��� `conf` Ŀ¼�¡�

**nginx ��������**��

- `./sbin/nginx` ���� nginx ����
- `./sbin/nginx -s stop` ֹͣ nginx ����
- `./sbin/nginx -s reload` ���¼��������ļ�

```shell
root@14178aa96595:/usr/local/nginx# netstat -tanp
Active Internet connections (servers and established)
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name    
tcp        0      0 127.0.0.1:33060         0.0.0.0:*               LISTEN      -                   
tcp        0      0 127.0.0.1:40309         0.0.0.0:*               LISTEN      36793/code-f1e16e1e 
tcp        0      0 127.0.0.1:3306          0.0.0.0:*               LISTEN      -                   
tcp        0      0 127.0.0.11:40853        0.0.0.0:*               LISTEN      -                   
tcp        0      0 0.0.0.0:80              0.0.0.0:*               LISTEN      61913/nginx: master 
tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN      24/sshd: /usr/sbin/ 
tcp        0      0 127.0.0.1:6379          0.0.0.0:*               LISTEN      -                   
tcp        0      0 127.0.0.1:40309         127.0.0.1:34242         ESTABLISHED 36793/code-f1e16e1e 
tcp        0      0 172.19.0.2:37324        185.125.190.82:80       TIME_WAIT   -                   
tcp        0      0 172.19.0.2:56746        140.82.112.22:443       ESTABLISHED 36830/node          
tcp        0      0 127.0.0.1:34242         127.0.0.1:40309         ESTABLISHED 36754/sshd: root@no 
tcp        0      0 172.19.0.2:52358        138.91.182.224:443      ESTABLISHED 36830/node          
tcp        0      0 172.19.0.2:22           10.0.0.141:61819        ESTABLISHED 36754/sshd: root@no 
tcp        0      0 172.19.0.2:49448        140.82.112.21:443       ESTABLISHED 36830/node          
tcp6       0      0 :::22                   :::*                    LISTEN      24/sshd: /usr/sbin/ 
tcp6       0      0 ::1:6379                :::*                    LISTEN      -                   
```

### 8.3 nginx ���� tcp ���ؾ���

���� conf �ļ����µ� `nginx.conf` �ļ�������������ã�

```conf
stream {
    # ����һ����Ϊ "MyServer" �����η�������
    upstream MyServer {
        # ʹ�ÿͻ��� IP ��ַ�Ĺ�ϣֵ�����и��ؾ��⣬ʹ��һ���Թ�ϣ�㷨
        hash $remote_addr consistent;
        
        # �����һ̨���η�����
        server 127.0.0.1:6000 weight=1 max_fails=3 fail_timeout=30s;
        # weight=1 ��ʾ��̨��������Ȩ�أ�Ĭ��Ϊ1��Ȩ��Խ�ߣ���ѡ�еĸ���Խ��
        # max_fails=3 ��ʾ�� fail_timeout ʱ���ڣ��������ʧ�ܵĴ���
        # fail_timeout=30s ��ʾ��30�������ʧ�ܴ������� max_fails����̨�������ᱻ���Ϊ������

        # ����ڶ�̨���η��������������һ̨��ͬ
        server 127.0.0.1:6001 weight=1 max_fails=3 fail_timeout=30s;
    }

    # ����������������
    server {
        # ���������η������������ӵĳ�ʱʱ��Ϊ1��
        proxy_connect_timeout 1s;

        # ���ô������ӵĳ�ʱʱ��Ϊ3��
        proxy_timeout 3s;

        # �����������������Ķ˿�Ϊ8000
        listen 8000;

        # ������������η������� "MyServer"
        proxy_pass MyServer;

        # ���� TCP_NODELAY ѡ������ӳ٣�������������
        tcp_nodelay on;
    }
}
```

![20240719143956](https://cdn.jsdelivr.net/gh/Corner430/Picture/images/20240719143956.png)

> ֮�� `./sbin/nginx -s reload` ���¼��������ļ���Ȼ�� `netstat -tanp` �鿴�˿ڼ��������

**������ֺܿ�Ͽ������**�����Էֱ����������ַ�����
1. �Ӵ�ʱʱ��
2. ��� `keepalive`����ȷ������ϵͳ����� `keepalive` ���ô򿪡�ȷ������ϵͳ����� `keepalive` ����Ҳ֧�ֳ�ʱ�䱣�����ӡ�������ϵͳ�����ļ��м�鲢������Щ���������� `/etc/sysctl.conf`��
```bash
# ��/etc/sysctl.conf������������ã���ʹ��sysctl������ʱ����

# ����TCP keepalive����
net.ipv4.tcp_keepalive_time = 1200  # ���ӿ���ʱ�䣬��λΪ��
net.ipv4.tcp_keepalive_intvl = 75   # ���ֻ̽��֮��ļ��ʱ�䣬��λΪ��
net.ipv4.tcp_keepalive_probes = 9   # ����Ϊ�����ѶϿ�֮ǰ���͵�̽�����
```

Ȼ��Ӧ����Щ���ã�`sudo sysctl -p`�����¼��� nginx �����ļ���

## 9 ���ݿ����

**User ��**

| �ֶ��� | ���� | ˵�� | Լ�� |
| --- | --- | --- | --- |
| id | INT | �û� id | PRIMARY KEY , AUTO_INCREMENT |
| name | VARCHAR(50) | �û��� | NOT NULL , UNIQUE |
| password | VARCHAR(50) | ���� | NOT NULL |
| state | ENUM('online', 'offline') | �û���¼״̬ | DEFAULT 'offline' |

**Friend ��**

| �ֶ��� | ���� | ˵�� | Լ�� |
| --- | --- | --- | --- |
| userid | INT | �û� id | NOT NULL , �������� |
| friendid | INT | ���� id | NOT NULL , �������� |

**AllGroup ��**

| �ֶ��� | ���� | ˵�� | Լ�� |
| --- | --- | --- | --- |
| id | INT | Ⱥ�� id | PRIMARY KEY , AUTO_INCREMENT |
| groupname | VARCHAR(50) | Ⱥ���� | NOT NULL , UNIQUE |
| groupdesc | VARCHAR(200) | Ⱥ������ | DEFAULT '' |

**GroupUser ��**

| �ֶ��� | ���� | ˵�� | Լ�� |
| --- | --- | --- | --- |
| groupid | INT | Ⱥ�� id | NOT NULL , �������� |
| userid | INT | ��Ա id | NOT NULL, �������� |
| grouprole | ENUM('creator', 'normal') | ��Ա��ɫ | DEFAULT 'normal' |

**OfflineMessage ��**

| �ֶ��� | ���� | ˵�� | Լ�� |
| --- | --- | --- | --- |
| userid | INT | �û� id | NOT NULL |
| message | VARCHAR(500) | ������Ϣ���洢 Json �ַ����� | NOT NULL |