
# ���������������

ʹ�÷�ʽ

```shell
mkdir build && cmake .. && make  # ֮�����п�ִ���ļ�����
```

## 1 ��������

[������ Docker ����������Ubuntu 22.04](https://github.com/Corner430/Docker/tree/main/chatserver)

�õ��ļ���ջ��

- Json ���л��ͷ����л��������� [json for Modern C++](https://github.com/nlohmann/json)
- muduo ����⿪���������� [muduo](https://github.com/chenshuo/muduo)
- MySQL ���ӳص�ʹ�ã������� [MySQL-Connection-Pool](https://github.com/Corner430/MySQL-Connection-Pool)

## 2 ��Ŀ����

1. �ͻ������û�ע��
2. �ͻ����û���¼
3. �ͻ����û��˳�
4. ��Ӻ��Ѻ�Ⱥ��
5. ��������
6. Ⱥ������
7. ������Ϣ

## 3 ��ĿĿ��

1. ���շ����������� I/O ģ�飬ҵ��ģ�飬����ģ��ֲ�����˼��
2. ���� C++ muduo �����ı���Լ�ʵ��ԭ��
3. ���� Json �ı��Ӧ��
4. ���� MySQL ���ӳص�ʹ��
5. ���� Docker һ������
6. ���� CMake

## 4 ���ݿ����

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
