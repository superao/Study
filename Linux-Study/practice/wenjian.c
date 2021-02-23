#include <stdio.h>
#include <stdlib.h>

int main() {
  
  char* temp[1024] = {0};
  FILE* fp = fopen("wenzihao.txt", "r");
  
  if(fp == NULL) {

    printf("打开失败\n");
    perror("失败！");

  }
  
  // 将文件内容写进字符数组进行储存。
  fread(temp, 1, 1024, fp);
  printf("文件内容：%s!\n", temp);
  // 关闭文件。
  fclose(fp);

  return 0;

}
