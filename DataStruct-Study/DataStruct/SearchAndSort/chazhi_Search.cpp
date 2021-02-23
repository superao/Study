// 插值查找:
// 对二分查找的优化,对分布均匀的数据来说,优于二分查找,对于分布不均分的数据,没有二分好。

#include <iostream>
#include <algorithm>
using namespace std;

int Search(int arry[], int size, int k) {

  // 由于插值查找,需要有序数组,因此,我们利用C++的功能模板,先帮我们排好序。
  // [start,end)
  sort(arry,arry + size);

  // 左闭右闭区间
  int left = 0;
  int right = size - 1;
  while(left <= right) {

    int mid = left + (k - arry[left]) / (arry[right] - arry[left]) * (right - left);
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

  Search(arry, sizeof(arry) / sizeof(int), 56);
  return 0;
}
