#include <stdio.h>
#include <stdlib.h>

size_t String(char* str) {
  // 计数器。
  int count = 0;
  
  // 利用循环来进行遍历。
  while (*str++ != '\0') {
    count++;
  }

  return count;

}

int main() {
  
  // 模拟实现求字符串的长度！
  char* str = "hehehe";
  int num = String(str);
  printf("字符长度大小为：%d \n", num);

  return 0;
}
