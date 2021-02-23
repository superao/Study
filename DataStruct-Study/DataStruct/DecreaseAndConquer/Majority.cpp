// 对于特定输入求解 "众数" (众数：在一组输入中，出现次数超过一半的称之为 "众数" )
#include <iostream>
using namespace std;

int Find(int array[], int n)
{
  int e = -1;
  int count = 0;
  for(int i = 0; i < n; ++i)
  {
    if(count == 0)
    {
      e = array[i];
    }

    if(e == array[i])                      // "减"
      count++;
    else
      count--;
  }

  return e;                                 // 这里必然可以找出次数超过一半的数
}

int main()
{
  int array[10] = {2, 2, 1, 2, 1, 2, 1, 2, 5, 2};

  cout << Find(array, 10) << endl;;

  return 0;
}
