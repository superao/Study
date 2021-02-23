// 二分查找:

#include <iostream>
#include <algorithm>
using namespace std;

int Binary_Search(int arry[], int size, int k) {

  // 由于二分查找,需要有序数组,因此,我们利用C++的功能模板,先帮我们排好序。
  // [start,end)
  sort(arry,arry + size);

  // 左闭右闭区间
  int left = 0;
  int right = size - 1;
  while(left <= right) {

    int mid = left + (right - left) / 2;
    if(arry[mid] == k) {

      cout << "找到了!" << endl;
      return mid;
    }
    else if(arry[mid] > k) {

      // 到左边区间进行查找
      right = mid - 1;
    }
    else {

      // 到右边区间进行查找
      left = mid + 1;
    }
  }

  cout << "没有找到!" << endl;
  return -1;
}


int main() {

  int arry[] = {1,5,7,3,2,8,0,4,2,7,10,2,56,7,5};

  Binary_Search(arry, sizeof(arry) / sizeof(int), 0);
  return 0;
}
