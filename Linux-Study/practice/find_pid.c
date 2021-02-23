#include <stdio.h>
#include <unistd.h>

int main() {

  // 获取调用进程的PID
  pid_t pid = getpid();
  while(1) {
    printf("你好！\n");
    printf("%d\n",pid);
    sleep(1);

  }

  return 0;
}
