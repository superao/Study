// 测试 move 函数，探究 move 的实现
#include <iostream>
using namespace std;

void func(int& a)
{
    cout << "void func(int& a)" << a << endl;
}

void func(int&& a)
{
    cout << "void func(int&& a)" << a << endl;
}

void fun(string& str)
{
    cout << "void fun(string& str)" << str << endl;
}

void fun(string&& str)
{
    cout << "void fun(string&& str)" << str << endl;
}

int main()
{
    func(2);
    
    int a = 10;
    func(a);

    func(move(a));

    func(move(20));

    func(static_cast<int>(20));
    func(static_cast<int>(a));

    string str = "hello!";
    fun(str);
    fun(move(str));
    fun(static_cast<string>(str));


    fun(move(string("hello world!")));
    fun(static_cast<string>(string("hello world!")));

    return 0;
}
