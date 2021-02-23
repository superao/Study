// 二分搜索
#include <iostream>
using namespace std;

int bsearch1(int array[], int l, int r, int x)
{
    while(l < r)
    {
        int mid = (l + r + 1) >> 1;
        if(array[mid] <= x) l = mid;
        else r = mid - 1;
    }

    if(array[l] == x) return l;
    else return -1;
}

int bsearch2(int array[], int l, int r, int x)
{
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(array[mid] >= x) r = mid;
        else l = mid + 1;
    }

    if(array[l] == x) return l;
    else return -1;
}

int main()
{
    int arr[] = {1, 3, 7, 8, 10, 14, 16, 20};

    cout << "下标为: " << bsearch1(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1, 3) << endl;
    
    cout << "下标为: " << bsearch2(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1, 3) << endl;

    return 0;
}
