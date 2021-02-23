// 最长连续子序列(分而治之)
#include <iostream>
using namespace std;

// 闭区间
int GSlice(int array[], int lo, int hi)
{
  // 递归基(当前只有一个元素)
  if(hi - lo < 1) { return array[hi]; }

  // 寻找跨边界的最大序列
  int mi = (lo + hi) / 2;
  int l = mi;
  int lsum = array[l];                 // 最好使用第一个数进行初始化 
  int lcur = 0;
  while(l >= lo)
  {
    lcur += array[l];
    if(lsum < lcur)
    {
      lsum = lcur;
    }

    l--;
  }

  int r = mi + 1;
  int rcur = 0;
  int rsum = array[r];
  while(r <= hi)
  {
    rcur += array[r];
    if(rsum < rcur)
    {
      rsum = rcur;
    }

    r++;
  }

  // 左右小问题递归处理
  return max(lsum + rsum, max(GSlice(array, lo, mi), GSlice(array, mi + 1, hi)));
}


int main()
{
  int array[7] = {1, 4, 2, -1, 3, 5, -6};

  cout << GSlice(array, 0, 6) << endl;

  return 0;
}
