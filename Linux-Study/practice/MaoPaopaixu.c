#include <stdio.h>
#include <time.h>

void Sort(int* arr, int length) {
  // 先写左闭右闭区间：
  int i, j,temp = 0;;
  for(i = 0; i < length; i++) {
    int count = 0;
    for(j = 0; j <= length - i - 2; j++) {
      if(arr[j + 1] < arr[j]) {
          temp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = temp;
          count = 1;
       } 
    }
    if(count == 0) {
      break;
    }
}
  return;
}

int main() {
  int arr[10] = {1,4,3,2,5,7,6,8,9,0};
  Sort(arr, 10);
  
  int i = 0;
  for(i = 0; i < 10; i++) {
    printf("%d\n", arr[i]);
  }

  return 0;

}
