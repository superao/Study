// 快速排序(分而治之)
#include <iostream>
#include <vector>
using namespace std;

// 闭区间
template<class T>
void QuickSort(vector<T>& array, int lo, int hi)
{
  // 递归基(当前只有一个元素的时候)
  if(hi - lo < 1)
  {
    return ;
  }

  // 随机选择基准(默认以区间最左元素为基准)
  int pivot = array[lo];
  int tlo = lo;
  int thi = hi;
  while(tlo < thi)
  {
    // 为了防止处理特殊情况，我们默认从基准的反方向开始移动
    if(array[thi] >= pivot)                    // 等号保证稳定性
    {
      thi--;
      continue;
    }
     
    if(array[tlo] <= pivot)
    {
      tlo++;
      continue;
    }

    swap(array[tlo], array[thi]);
  }

  // 当前 lo == hi, 从而确定基准元素的准确位置。
  swap(array[lo], array[tlo]);

  // 递归分别处理左区间与右区间
  QuickSort(array, lo, tlo);
  QuickSort(array, tlo + 1, hi);

  return ;
}

int main()
{
  vector<int> array = {2, 9, 4, 1, 5, 3, 0, 10, 8, 7, 12, 43, 1, -1, -4, 6, 90, 20};
  
  QuickSort(array, 0, array.size() - 1);

  for(auto& e : array)
  {
    cout << e << endl;
  }

  return 0;
}
