#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

  int i = 0;
  for(i = 0; i < 2; i++) {
    fork();
    printf("_\n");
  }


  return 0;
}
