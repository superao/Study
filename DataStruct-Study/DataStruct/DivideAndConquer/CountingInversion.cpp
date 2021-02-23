// 统计序列逆序对("蛮力" + "分而治之")
#include <iostream>
#include <vector>
using namespace std;

// 蛮力解法(时间复杂度为 O(I * n))
// 类似于 "插入排序的过程"
int CountingInversion(vector<int>& array)
{

  int inversionsum = 0;

  // 扫描向量
  for(size_t i = 0; i < array.size(); ++i)
  {
    // 向前扫描，比较
    for(int j = i - 1; j >= 0; --j)
    {
      if(array[j] > array[i])
        inversionsum++;
    }
  }

  return inversionsum;
}

// "分而治之" 解法(闭区间)
// 借助 "归并排序" 的合并过程
int count = 0;
void CountingInversion1(vector<int>& array, int lo, int hi, vector<int>& extra)
{
  // 递归基(当前区间只剩下一个元素)
  if(hi - lo < 1)
    return ;

  // 递归左右区间
  int mi = (lo + hi) / 2;
  CountingInversion1(array, lo, mi, extra);
  CountingInversion1(array, mi + 1, hi, extra);

  // 当前区间(区间：[lo, mi], [mi + 1, hi])进行有序合并(方便后续统计)，并且统计逆序对
  // 对当前区间下标进行备份，以防影响后续递归
  int tlo = lo;
  int thi = hi;
  int tmi = (tlo + thi) / 2;
  int rindex = tmi + 1;

  int index = tlo;                                                  // 合并时间复杂度为 O(n)
  while(tlo <= mi && rindex <= thi)
  {
    if(array[tlo] > array[rindex])
    {
      count += (mi - tlo + 1);
      extra[index++] = array[rindex++];
    }
    else 
    {
      extra[index++] = array[tlo++];
    }
  }

  // 将某一个区间剩下的元素全部加入
  while(tlo <= tmi)
  {
    extra[index++] = array[tlo++];
  }

  while(rindex <= thi)
  {
    extra[index++] = array[rindex++];
  }

  // 将数据拷贝到原有数组中
  for(int i = lo; i <= hi; ++i)
  {
    array[i] = extra[i];
  }

  return ;
}

int main()
{
  vector<int> array = {2, 9, 4, 1, 5, 3, 7, 4, 8};
  vector<int> extra(array.size(), 0);
  CountingInversion1(array, 0, array.size() - 1, extra);
  cout << count << endl;

  return 0;
}
