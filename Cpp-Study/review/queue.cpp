// 数组模拟队列
#include <iostream>
#include <string.h>
using namespace std;

const int N = 1e5;
int arr[N], front = 0, back = 0;

void init()
{
    memset(arr, 0, N);
}

void push(int x)
{
    arr[back++] = x;
}

int pop()
{
    return arr[front++];
}

bool empty()
{
    if(back <= front)
        return true;
    else 
        return false;
}

int main()
{
    // 队列的基本操作
    push(1);
    push(2);
    push(4);
    push(3);

    cout << empty() << endl;

    cout << pop() << endl;
    cout << pop() << endl;
    cout << pop() << endl;
    
    cout << empty() << endl;

    cout << pop() << endl;
    
    cout << empty() << endl;

    push(10);
    push(12);
    cout << pop() << endl;
    push(13);

    cout << pop() << endl;
    cout << empty() << endl;
    
    return 0;
}
