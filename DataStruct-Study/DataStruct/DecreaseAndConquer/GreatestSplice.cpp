// 最长连续子序列(减而治之，时间复杂度为 O(n))
// 体会减而治之
#include <iostream>
using namespace std;

// 蛮力破解(O(n^3))
int Greatest1(int array[], int n)
{
  int sum = 0;
  for(int i = 0; i < n; ++i)
  {
    for(int j = i; j < n; ++j)
    {
      // 枚举了所有连续子序列
      int n = 0;
      for(int k = i; k <= j; ++k)
      {
        cout << array[k] << " ";
        n += array[k];
      }
      cout << endl;
      if(n > sum)
      {
        sum = n;
      }
    }
  }

  return sum;
}

// 优化蛮力破解(O(n^2))
int Greatest2(int array[], int n)
{
  int sum = 0;
  for(int i = 0; i < n; ++i)
  {
    int num = 0;
    for(int j = i; j < n; ++j)
    {
      num += array[j];                  // 当前子序列的和 = 上一个子序列 + 当前元素的值
      if(num > sum)                     // 取最大即可
      {
        sum = num;
      }
    }
  }

  return sum;
}

// 减而治之(O(n))
int Greatest(int array[], int n)
{
  int sum = 0;
  for(int i = n - 1; i >= 0; --i)
  {
    sum += array[i];

    if(sum <= 0)                                // 减而治之
    {
      sum = 0;
    }
  }

  return sum;
}

int main()
{
  int array[7] = {1, 4, 2, -1, -3, 5, -6};
  cout << Greatest2(array, 7) << endl;
  return 0;
}
