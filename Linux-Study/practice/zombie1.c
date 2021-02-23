#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>


int main() {
  
  int pid = fork();
  if(pid == 0) {

    sleep(5);
    exit(0);
  }
  
  uint64_t a = 0;
  while(1) {
    a++;
    usleep(1000);
    
  }

  return 0;

}
