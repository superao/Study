#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

  int pid = vfork();
  if(pid == 0) {
    printf("child-----%d\n", getpid());
    exit(0);
  }
  else {
    printf("parent-----%d\n",getpid());
  }

  //return 0;
  //子进程释放了资源，父进程函数调用栈混乱，导致死循环等等。

  while(1) {
    printf("--------%d\n",getgid());
    sleep(1);
  }

  return 0;
}
