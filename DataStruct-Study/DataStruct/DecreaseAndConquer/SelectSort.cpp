// 选择排序(减而治之)
#include <iostream>
using namespace std;

bool SelectSort(int array[], int n)
{
  // 升序(默认后面为 sorted, 前面为 random)
  for(int i = n - 1; i >= 0; --i)
  {
    int tmp = 0; int index = 0;
    // 在 random 中进行选择最大的数
    for(int j = i; j >= 0; --j)                  // 这种线性扫描可以优化为 logn
    {
      if(array[j] > tmp)
      {
        tmp = array[j];                          // 记录 random 序列中的最大值
        index = j;                               // 记录最大值的下标
      }
    }
    swap(array[i], array[index]);                // i-- 表明当前的数已到达自己所处的位置
                                                 // 处理下一个random序列中的数(减而治之的策略)
  }

  return true;
}

int main()
{
  int array[10] = {2, 9, 4, 1, 5, 3, 6, 10, 55, 12};

  SelectSort(array, 10);

  for(int i = 0; i < 10; ++i)
  {
    cout << array[i] << " ";
  }
  cout << endl;

  return 0;
}
