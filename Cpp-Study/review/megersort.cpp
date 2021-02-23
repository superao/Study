#include <iostream>
using namespace std;

const int N = 1e5;
int temp[N];

void megersort(int arr[], int l, int r)
{
    if(l >= r) return ;

    int mid = l + r >> 1;

    megersort(arr, l, mid), megersort(arr, mid + 1, r);

    int k = 0;
    int i = l, j = mid + 1;
    while(i <= mid && j <= r)
    {
        if(arr[i] < arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }

    while(i <= mid) temp[k++] = arr[i++];
    while(j <= r) temp[k++] = arr[j++]; 

    for(int i = l, j = 0; i <= r; i++, j++) arr[i] = temp[j];
}

int main()
{
    int arr[] = {1, 4, 3, 2, 15, 10, 4, 8, 12};

    for(auto& e : arr)
        cout << e << " ";
    cout << endl;

    megersort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);

    for(auto& e : arr)
        cout << e << " ";
    cout << endl;

    return 0;
}
