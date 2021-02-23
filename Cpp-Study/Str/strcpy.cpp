// 模拟实现 strcpy 函数
#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
using namespace std;

// 库原型: char * strcpy ( char * destination, const char * source  )
char* Strcpy(char* des, char* sou)
{
  assert(des && sou);

  // 保存目标字符首地址
  char* ret = des;

  // 逐个字符进行拷贝
  while(*(des++) = *(sou++));

  return ret;
}

int main()
{
  char* str1 = "heheheasvsbdfbdfsbdfb";
  char* str2 = (char*)malloc(strlen(str1));

  cout << str1 << endl;
  cout << Strcpy(str2, str1) << endl;
  cout << str2 << endl;

  return 0;
}
