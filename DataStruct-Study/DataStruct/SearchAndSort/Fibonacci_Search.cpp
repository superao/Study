// 斐波那契查找(黄金分割查找):
// 利用黄金分割比(0.618),来划分数组的长度,进行递归查找。

#include <iostream>
#include <algorithm>
#define N 10    // 有效数据
#define MAX 100 // 数组的大小,只有让数组足够大,才能保证最后填充数据的时候,数组不会越界。

namespace superao {
  // 在自己的命名空间构建一个斐波那契数列
  void Fibonacci(int arry[]) {

    arry[0] = 0;
    arry[1] = 1;

    int i = 0;
    for(i = 2; i <= 1024; i++) {

      arry[i] = arry[i - 1] + arry[i - 2];
    }
  }
}

using namespace std;

// 定义一个全局数组
int f[1024] = {0};

// 左闭右闭区间:[0,size];
int Fibonacci_Search(int arry[], int size, int v) {

  // 由于需要对有序数组进行查找,所以,我们利用 C++ 的模板
  // [arry, arry + size)
  sort(arry,arry + size);

  // 创建斐波那契数列
  superao::Fibonacci(f);

  // 1.算出数组长度,到对应的斐波那契数列中查找大于该长度的对应的值.
  int k = 0;
  int n = size - 1;
  while(n > f[k] - 1) {

    k++;
  }

  // 2.将待查找数组扩充为 f[k] - 1 这么大,空缺元素用数组最后一个元素来进行填充.
  for(int i = n + 1; i <= f[k] - 1; i++) {

    arry[i] = arry[n]; 
  }

  // 理解难点:为什么将数组扩充到f[k] - 1;这样扩充的话,方便书写循环和递归的表达式,如下:
  // f[k] - 1 = (f[k - 1] - 1)(左区间) + 1(mid) + (f[k - 2] - 1)(右区间);
  // 中间的 1 就是用来对比的,两边的用来递归缩小区间. 
  
  int left = 0;
  int right = f[k] - 1;
  int mid = 0;

  while(left <= right) {

    mid = left + f[k - 1] - 1;

    // 如果分割的位置,比原来边界所在的位置还小,直接退出,防止数组越界。
    if(f[k - 1] - 1 < 0) {

      break;
    }

    if(arry[mid] == v) {

      cout << "找到了" << endl;
      // 找到了,返回对应的下标
      if(mid < n) {

        return mid;
      }
      else {

        return n;
      }

    }
    // 更变区间
    else if(arry[mid] > v) {

      // 左区间进行查找
      right = mid - 1;
      k = k - 1;
    }
    else{

      left = mid + 1;
      k = k - 2;
    }
  }

  cout << "没有找到" << endl;
  return -1;
}

int main() {

  int arry[MAX] = {1,4,2,5,8,0,5,3,56,78};

  Fibonacci_Search(arry, N, 700);
  return 0;
}
