#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int arr[N];

// 查找集合编号(路径压缩)
int find(int x)
{
    if(x != arr[x])
    {
        int t = find(arr[x]);
        arr[x] = t;
    }

    return arr[x];
}

int main()
{
    // 测试 10 个数
    for(int i = 0; i < 10; ++i)
    {
        arr[i] = i;
    }

    // 合并两个集合(4, 5)
    arr[5] = find(4);
    cout << arr[5] << endl;
    cout << arr[4] << endl;

    // 合并两个集合(8, 4)
    arr[8] = find(4);
    cout << arr[8] << endl;
    cout << arr[4] << endl;

    return 0;
}
