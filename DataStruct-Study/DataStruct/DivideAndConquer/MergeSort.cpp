// 归并排序("分而治之"策略)
#include <iostream>
#include <vector>
using namespace std;

// 闭区间(升序)
template<class T>
void MergeSort(vector<T>& array, int lo, int hi, vector<T>& extra)
{
  // extra 额外空间，用于归并(空间复杂度为 O(n))

  // 递归基(当前区间只有一个元素)
  if(hi - lo < 1)
  {
    return ;
  }

  // 区间划分,递归调用
  int mi = (lo + hi) / 2;
  MergeSort(array, lo, mi, extra);
  MergeSort(array, mi + 1, hi, extra);

  // 归并, 排序(对区间[lo, mi], [mi + 1, hi]进行比较，然后归并)
  // 特别注意：
  //    对于归并操作来说，在归并的时候，我们有可能改变了某些下标的值，从而导致对后面的递归造成影响。
  //    对此有以下两种方法改进:
  //        1. 封装函数
  //        2. 归并的时候将各个区间变量的下标进行备份
  
  int tlo = lo;
  int thi = hi;
  int tmi = (tlo + thi) / 2;
  int tright = tmi + 1;
  
  int index = tlo;                     // 当前新向量下标
  
  while(tlo <= tmi && tright <= thi)
  {
    if(array[tlo] > array[tright])
    {
      extra[index] = array[tright];
      tright++;
    }
    else 
    {
      extra[index] = array[tlo];
      tlo++;
    }

    index++;
  }
  
  // 任意一个区间为空，将另一个区间元素全部放入
  while(tright <= thi)
  {
    extra[index] = array[tright];
    tright++;
    index++;
  }

  while(tlo <= tmi)
  {
    extra[index] = array[tlo];
    tlo++;
    index++;
  }

  // 将已经归并的元素放回到原来数组中，更新 array, 方便后续继续合并
  for(int i = lo; i <= hi; ++i)
  {
    array[i] = extra[i];
  }

  return ;
}


int main()
{
  vector<int> array = {2, 9, 4, 1, 5, 3, 2, 7, 4, 8, 10, 12, 56, 21, 0, -1, 2, 6};
  vector<int> extra(array.size(), 0);

  MergeSort(array, 0, array.size() - 1, extra);

  for(auto& e : extra)
  {
    cout << e << endl;
  }

  return 0;
}
