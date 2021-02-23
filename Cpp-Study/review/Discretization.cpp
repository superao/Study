// 离散化
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int arr[N];

int find(int arr[], int l, int r, int x)
{
    while(l < r)
    {
        int mid = l + r >> 1;
        if(arr[mid] >= x) r = mid;
        else l = mid + 1;
    }

    return l;
}

int main()
{
    // 待离散化的数据(5个)
    arr[1] = 1;
    arr[4] = 4;
    arr[5] = 5;
    arr[100] = 100;
    arr[10000] = 10000;

    // 离散化 (1, 2, 3, ...)
    const int n = 5;
    int k = 0;
    int alls[n] = {0};
    for(int i = 0; i < N; ++i)
    {
        if(arr[i] != 0)
            alls[k++] = arr[i];
    }

    for(int i = 0; i < n; ++i)
    {
        cout << alls[i] << endl;
    }

    // 查找元素 x 离散化后的下标(0 ~ n - 1: 表示离散化后的区间)
    cout << "1 离散化后的下标: " << find(alls, 0, n - 1, 1) << endl;
    cout << "4 离散化后的下标: " << find(alls, 0, n - 1, 4) << endl;
    cout << "5 离散化后的下标: " << find(alls, 0, n - 1, 5) << endl;
    cout << "100 离散化后的下标: " << find(alls, 0, n - 1, 100) << endl;
    cout << "10000 离散化后的下标: " << find(alls, 0, n - 1, 10000) << endl;
    
    return 0;
}
