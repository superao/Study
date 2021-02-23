#include <stdio.h>
#include <stdlib.h>

void Find (char** str, char ch) {

  // 第一个循环来遍历字符串。
  while(*str != NULL) {
    
    // 第二个循环来进行遍历字符。
    while(**str != NULL) {

      if (**str == ch) {
        
        printf("找到了！\n");
        
      }
      
      **str++;
    }


    *str++;
  }
  printf("没有找到！\n");

}
int main () {

  // 二维数组用来储存所查找的字符
  char str[3][20] = {0}; 
  char ch;

  // 输入：
  int i = 0;
  printf("请输入字符内容：\n");
  for(i = 0; i < 3; i++) {

    gets(str[i]); // str[i] 为char* ,是一个指针.
    
  }
  printf("请输入需要查找的字符：\n");
  scanf("%c", ch);

  
  // 查找：
  Find(str, ch);

  return 0;
}
