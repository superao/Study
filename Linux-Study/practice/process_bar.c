#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {

  char arr[102];
  memset(arr,0,sizeof(arr));
  // 旋转样子：
  const char* z = "|/-\\";
 
  int i = 0;
  while(i <= 100) {
    printf("[%-100s][%d%%][%c]\r",arr, i, z[i%4]);

    // 刷新缓冲区，否则当缓冲区储存满时才会输出。
    fflush(stdout);
    arr[i] = '*';
    i++;
    usleep(100000);
  }
  printf("\n");
  return 0;

}
