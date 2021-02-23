// K-选取问题(平均时间复杂度为 nlogn)
// "减而治之(分类，切除) + 猜测" 实现
#include <iostream>
using namespace std;

// 实现思想：
//    我们随便猜测一个数，就认定它为第 K 小的数(作为基准)。然后对序列中的数进行分类，比基准大的数放到序列的右边；
//    比基准小的数放到序列的左边，最后观察左边数的个数来判定以基准为界将要舍去哪一边的序列，舍去后继续在新序列中猜测。
int QuickSelect(int array[], int n, int k)
{
  for(int i = 0, j = n - 1; i <= j;)
  {
    int lo = i, hi = j; 
    int pivot = array[i];                          // 当选取区间左边数为基准时，最好从右边开始扫描。(否则就需要处理很多特殊情况)

    while(lo < hi)
    {
      if(array[hi] >= pivot)
      {
        hi--;
        continue;
      }
      if(array[lo] <= pivot)                        // "=" 保证相同元素的稳定性
      {
        lo++;
        continue;
      }

      swap(array[lo], array[hi]);
    }

    // lo == hi(当前 pivot 已经到达自己的位置,交换基准值与当前元素的位置)
    swap(array[lo], array[i]);
    
    // 减而治之
    if(lo < k - 1)
      i = lo + 1;
    if(k - 1 < lo)
      j = lo - 1;
    if(k - 1 == lo)                                 // 由于数组下标从 0 开始，因此 k 的值在进行比较时需要减 1
      return lo;
  }

  return -1;
}


int main()
{
  int array[10] = {2, 9, 4, 1000, 5, 3, 6, 8, 9, 100};

  int index = QuickSelect(array, 10, 8);

  cout << "该数为：" << array[index] << endl;;

  return 0;
}
