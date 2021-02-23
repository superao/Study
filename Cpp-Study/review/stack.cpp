// 数组模拟实现栈
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int array[N], idx = -1;

// 插入元素
void push(int x)
{
    ++idx;
    array[idx] = x;
}

// 删除元素
void pop()
{
    --idx;
}

// 栈顶元素
int top()
{
    return array[idx];
}

// 判断栈是否为空
bool empty()
{
    return idx < 0 ? true : false;
}

int main()
{
    // 测试代码
    push(1);
    push(2);
    push(3);
    push(4);
    
    cout << empty() << endl;
    cout << top() << endl;
    pop();
    cout << top() << endl;
    pop();
    cout << top() << endl;
    pop();

    push(10);
    push(11);
    push(12);
    cout << top() << endl;
    pop();
    cout << top() << endl;
    pop();
    cout << top() << endl;
    pop();
    cout << top() << endl;
    pop();
    cout << empty() << endl;

    return 0;
}
