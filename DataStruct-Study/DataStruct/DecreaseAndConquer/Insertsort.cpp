// 插入排序(减而治之)    =>   此处使用循环挪动元素，我们也可以使用栈来实现
#include <iostream>
using namespace std;

// 升序
bool InsertSort(int array[], int n)
{
  // 序列前面部分为 sorted, 后面部分为 random.(第一个元素默认已排序)
  for(int i = 1; i < n; ++i)
  {
    int e = array[i];
    int j = 0;
    // 当前元素小于 sorted 序列时(j 表示 sorted 区间)，扫描寻找合适位置
    for(j = i - 1; j >= 0 && array[j] > array[i]; --j);

    // 当前元素大于 sorted 序列中某个元素时，挪动元素，插入新数
    if(array[j] < array[i])
    {
      // 从 j 的下一个位置开始挪动，一直挪动到当前位置(k 表示元素新位置区间)
      for(int k = i; k >= j + 2; --k)
      {
        array[k] = array[k - 1];
      }

      // 留出 j + 1 的位置，新元素入住
      array[j + 1] = e;
    }
  }                                                 // ++i 表示当前元素已就绪，处理下一个元素(减而治之)

  return true;
}

int main()
{
  int array[10] = {2, 3, 4, 1, 5, 9, 6, 11, 7, 12};
  
  InsertSort(array, 10);

  for(int i = 0; i < 10; ++i)
  {
    cout << array[i] << " ";
  }
  cout << endl;

  return 0;
}
