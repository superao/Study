// 测试malloc, calloc, realloc函数的功能
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
    int* ptr = (int*)malloc(4);
    cout << ptr << endl;

    ptr = (int*)realloc(ptr, 5);
    cout << ptr << endl;

    ptr = (int*)realloc(ptr, 1000);
    cout << ptr << endl;

    return 0;
}
