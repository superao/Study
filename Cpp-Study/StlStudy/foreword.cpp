// 体会需要 完美转发 的场景
#include <iostream>
using namespace std;

// 目标函数
void func(int& avg)
{
    cout << "void func(int & avg)" << avg << endl;
}

void func(int&& avg)
{
    cout << "void func(int && avg)" << avg << endl;
}

// 转发函数
void preprocess(int& avg)     // 转发左值
{
    cout << "void preprocess(int& avg)" << avg << endl;
    //func(avg);

    func(forward<int>(avg));
}

void preprocess(int&& avg)    // 转发右值
{
    cout << "void preprocess(int&& avg)" << avg << endl;
    //func(avg);

    func(forward<int>(avg));
}

int main()
{
    int a = 10;
    func(a);
    func(20);

    preprocess(a);
    preprocess(move(a));

    return 0;
}
