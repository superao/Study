// 双指针算法
// 在一个字符串中找到所有的单词
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

// 暴力枚举
void func(string str)
{
    for(int i = 0; i < (int)str.size(); ++i)         // 枚举单词的起始位置
    {
        int j = 0;
        while(j < (int)str.size() && (j <= i || str[j] != ' '))     // 枚举单词的终止位置
            j++;

        // 从起始位置开始输出
        while(i < j)
            cout << str[i++];
        cout << endl;
    }
}

// 双指针算法
void func1(string str)
{
    for(int i = 0; i < (int)str.size(); ++i)
    {
        int j = i;                                   // 有些状态是不需要枚举的 
        while(j < (int)str.size() && str[j] != ' ') j++;

        while(i < j)
            cout << str[i++];
        cout << endl;
    }
}

int main()
{
    char str[100];
    gets(str);

    func(str);
    func1(str);

    return 0;
}
