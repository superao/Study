// 多种类型转化(char* -> int -> char*)
#include <iostream>
#include <sstream>
#include <strings.h>
using namespace std;

int main()
{
    stringstream sstream;
    char buf[1024] = "1023";
    int num = 0;

    cout << "转化之前: " << buf << endl;

    sstream << buf;
    sstream >> num;

    // 对数字进行操作
    num++;

    // 将数字转化为字符串
    sstream.clear();
    bzero(buf, 1024);
    sstream << num;
    sstream >> buf;

    cout << "转化之后: " << buf << endl;

    return 0;
}
