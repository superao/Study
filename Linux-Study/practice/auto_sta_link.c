/* 学习使用静态库/动态库的生成与链接 */ 
/* 注：动态库/静态库中不能出现 main 函数 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// 包含头文件中的声明。
#include "myhead.h"

// 函数体的定义：
int add(int a, int b) {

  int result = 0;
  result = a + b;
  return result;
}



