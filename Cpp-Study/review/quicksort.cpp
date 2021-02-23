#include <iostream>
using namespace std;

void quicksort(int arr[], int l, int r)
{
    if(l >= r) return;

    int x = arr[l + r >> 1];

    int i = l - 1, j = r + 1;
    while(i < j)
    {
        do i++; while(arr[i] < x);
        do j--; while(arr[j] > x);

        if(i < j) swap(arr[i], arr[j]);
    }

    quicksort(arr, l, j);
    quicksort(arr, j + 1, r);
}

int main()
{
    int arr[] = {1, 10, 3, 2, 5, 5, 7, 4};

    for(auto& e : arr)
        cout << e << " ";
    cout << endl;

    quicksort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);

    for(auto& e : arr)
        cout << e << " ";
    cout << endl;

    return 0;
}
