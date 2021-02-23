// 使用 stringstream 进行字符串拼接
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    stringstream sstream;
    string str = "hello";
    string str1 = "world!";
    string result;

    sstream << str << " " << str1 << endl;
    result = sstream.str();

    cout << result;

    return 0;
}
