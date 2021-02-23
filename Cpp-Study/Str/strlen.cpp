// 模拟实现 strlen 函数的功能
#include <stdio.h>
#include <assert.h>

int Strlen(const char* str)
{
  assert(str);
  int count = 0;
//  for(int i = 0; str[i] != '\0'; ++i)
//  {
//    count++;
//  }
  while(*str != '\0')
  {
    str++;
    count++;
  }

  return count;
}

int main()
{
  char* str = "hello wolrd";
  printf("%d\n", Strlen(str));
  return 0;
}
