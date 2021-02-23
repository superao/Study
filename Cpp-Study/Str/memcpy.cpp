// 模拟实现 memcpy 函数
// 功能：什么类型都可以进行拷贝
// 实现：memcpy 的实现是按照一个字节一个字节来进行拷贝的
#include <iostream>
#include <assert.h>
using namespace std;

// 函数原型: void * memcpy ( void * destination, const void * source, size_t num  );
void* Memcpy(void* des, const void*sou, size_t num)
{
  assert(des && sou);
  char* ret = (char*)des;
  char* csou = (char*)sou;
  
  for(size_t i = 0; i < num; ++i)
  {
    *(ret++) = *(csou++);
  }

  return (void*)ret;
}

int main()
{
  // 测试 int*
  int arr[10] = {1, 2, 3, 4};
  int arr1[10] = {0};
  Memcpy(arr1, arr, 4);
  for(int i = 0; i < 10; ++i)
  {
    cout << arr1[i] << endl;
  }

  // 测试 char*
  char* str = "hello";
  char str1[3];
  Memcpy(str1, str, 3);
  cout << str1 << endl;

  return 0;
}
