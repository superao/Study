#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main() {
  
  // 1.打印格式：
  while(1) {
    printf("[superao@lacalhost ~]$ ");
  
    // 读入用户输入：
    char input[1024];
    // %[^\n] 获取字符串直到遇到 \n 为止。
    // %*c 将一个字符从缓冲区中取出。
    if(scanf("%[^\n]%*c",input) == 0) {
      
      // 读入参数失败,重新获取,并且清空原来缓冲区的内容。
      getchar();
      continue;
    }
    
    // [     ls      -l     ]
    // 2.解析用户输入：
    int argc = 0;
    char* ptr = input;
    char* argv[1024];
    while(*ptr != '\0') {
      
      // 如果不是空白字符就获取参数
      if(!isspace(*ptr)) {
        
        // 将参数首地址储存到参数数组中。
        argv[argc++] = ptr;
        while(!isspace(*ptr) && *ptr != '\0') {
          
          // 走到参数尾部。
          ptr++;
        }

        // 切割字符串。
        *ptr = '\0';
        
      }

      ptr++;                
    }

    argv[argc] = NULL;
    // 判断命令是否为内建命令：
    if(strcmp(argv[0],"cd") == 0) {

      chdir(argv[1]);
    }
    // 3. 创建子进程：
    int pid = fork();
    if(pid < 0) {

      // 如果创建失败，则继续
      continue;
    }
    else if(pid == 0) {

      // 创建成功，程序替换
      execvp(argv[0],argv); 
    }
    else {

      // 5.进程等待，避免产生僵死进程。
      wait(NULL);
    }

  }

  return 0;
}
