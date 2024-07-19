
#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <string>
using namespace std;

// json ���л�ʾ�� 1
string func1() {
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";

    string sendBuf = js.dump(); // ���л�
    // cout << "���л����json����: " << sendBuf << endl;
    return sendBuf;
}

// json ���л�ʾ�� 2
string func2() {
    json js;
    // �������
    js["id"] = { 1, 2, 3, 4, 5 };
    // ��� key-value
    js["name"] = "zhang san";
    // ��Ӷ���
    js["msg"]["zhang san"] = "hello python";
    js["msg"]["liu shuo"] = "hello c++";
    // �����ͬ���������һ��������������
    js["msg"] = { {"zhang san", "hello python"}, {"liu shuo", "hello c++"} };
    // cout << js << endl;
    // cout << "���л����json����: " << js.dump() << endl;
    return js.dump();
}

// json �����л�ʾ�� 3
string func3() {
    json js;

    // ֱ�����л�һ�� vector ����
    vector<int> vec = { 1, 2, 5 };
    js["list"] = vec;

    // ֱ�����л�һ�� map ����
    map<int, string> m;
    m[1] = "zhang san";
    m[2] = "li si";
    js["name"] = m;

    string sendBuf = js.dump(); // ���л�
    // cout << "���л����json����: " << sendBuf << endl;
    return sendBuf;
}

int main() {
    string recvBuf = func1();
    json jsbuf = json::parse(recvBuf); // �����л�
    cout << jsbuf["msg_type"] << endl;
    cout << jsbuf["from"] << endl;
    cout << jsbuf["to"] << endl;
    cout << jsbuf["msg"] << endl;

    cout << "-----------------" << endl;

    recvBuf = func2();
    jsbuf = json::parse(recvBuf); // �����л�
    cout << jsbuf["id"] << endl;
    auto arr = jsbuf["id"];
    cout << arr[2] << endl;
    auto msgjs = jsbuf["msg"];
    cout << msgjs["zhang san"] << endl;
    cout << msgjs["liu shuo"] << endl;

    cout << "-----------------" << endl;

    recvBuf = func3();
    jsbuf = json::parse(recvBuf); // �����л�
    vector<int> vec = jsbuf["list"];
    // js ����������������ͣ�ֱ�ӷ��� vector ������
    for (int& v : vec)
        cout << v << " ";
    cout << endl;

    map<int, string> mymap = jsbuf["name"];
    for (auto& m : mymap)
        cout << m.first << " " << m.second << endl;
    cout << endl;

    return 0;
}
