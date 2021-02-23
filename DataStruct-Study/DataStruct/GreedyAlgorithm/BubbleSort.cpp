// 基于贪心策略的冒泡排序
// 主要思想：
//    每次只是局部的观察当前两个元素的位置，如果位置不对进行swap，否则依次向后扫描，最后导致全局有序。
// 缺点：
//    虽然这种贪心策略相当的简单，并且只要重复此过程就可以达到全局有序，但是在贪心策略中有很多多余的步骤，
//    因此，对于贪心策略我们需要对其进行优化，从而使贪心策略的效率进行提升
#include <iostream>
#include <algorithm>
using namespace std;

// 这里有可能会有很多的无效的扫描
void Bubble(int array[], int n)
{
  // 依次扫描
  for(int i = 1; i < n; ++i)
  {
    // 可读性的体现以及贪心策略的体现
    if(array[i - 1] > array[i])
    {
      swap(array[i - 1], array[i]);
    }
  }
}

// 优化1：设置哨兵
bool Bubble1(int array[], int n)
{
  // 设置哨兵
  int flag = false;
  
  for(int i = 1; i < n; ++i)
  {
    if(array[i - 1] > array[i])
    {
      flag = true;
      swap(array[i - 1], array[i]);
    }
  }

  return flag;
}

// 优化2：减少不必要的扫描
int Bubble2(int array[], int n)
{
  // 记录下标
  int index = 0;

  for(int i = 1; i < n; ++i)
  {
    if(array[i - 1] > array[i])
    {
      swap(array[i - 1], array[i]);
      // 从左向右扫，若出现逆序对，那么记录最右边的元素，从而排除掉后边无效扫描
      index = i;
    }
  }

  return index;
}

void BubbleSort(int array[], int n)
{
  int left = 0;
  int right = n;

  while(left < right) 
  {
    Bubble(array, right); 
    right--;
  }
}

void BubbleSort1(int array[], int n)
{
  while(Bubble1(array, n--));
}

void BubbleSort2(int array[], int n)
{
  int left = 0;
  int right = n;

  while(left < right) 
  {
    int num = Bubble2(array, right); 
    right = num;
  }
}

int main()
{
  int array[10] = {1, 4, 7, 2, 5, 8, 0, 10, 6, 3};

  BubbleSort2(array, 10);

  for(int i = 0; i < 10; ++i)
  {
    cout << array[i] << " "; 
  }
  cout << endl;

  return 0;
}
