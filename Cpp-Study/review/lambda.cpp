// lambda 表达式的一些简单使用
#include <iostream>
using namespace std;

int main()
{
    // 最简单的lambda表达式，无意义
    []{};

    // 省略返回值类型，但是没有调用
    int num1 = 10, num2 = 20;
    [=](){return num1 + num2;};

    // 省略返回值类型和参数类型，但是没有调用
    int a = 1, b = 2;
    [=]{return a + b;};

    // lambda实现两数相乘
    int muti = 0;
    auto fun = [=, &muti]() ->int {return muti = num1 * num2;};
    cout << fun() << endl;       // 调用

    // lambda对传入的参数做处理
    int data = 1;
    auto fun1 = [data](int n)mutable ->int 
    {
        data += n;
        return data;
    };
    cout << fun1(200) << endl;

    // lambda对捕捉到的值进行修改
    string str = "hello";
    auto fun2 = [&str]{
        str = "world";
        return str;
    };
    cout << str << endl;
    fun2();
    cout << str << endl;

    return 0;
}
