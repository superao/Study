#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 选择排序：
void SelectSort(int arry[], int size) {

  // 由于选择排序一次执行处理一个数，那么有多少个数，
  // 就需要有多少次循环。
  int i = 0;
  for(i = 0; i < size; i++) {

    // 无序区间[0, size - 1 - i];
    // 有序区间[size - 1 - i + 1, size - 1];
    
    // 先保存随便保存一个无序区间的最大值下标。
    int maxindex = 0;
    
    // 找最大值的下标
    int j = 0;
    for(j = 0; j <= size - 1 - i; j++) {

      if(arry[maxindex] < arry[j]) {

        // 更新最大值的下标
        maxindex = j;
      }
    }

    // 将一个无序中的最大值与无序中的最后一个元素进行交换
    int temp = arry[maxindex];
    arry[maxindex] = arry[size - 1 - i];
    arry[size -1 - i] = temp;
  }

}


int main() {

  int arry[] = {9,5,2,7};
  SelectSort(arry,(int)(sizeof(arry) / sizeof(int)));

  int i = 0;
  for(i = 0; i < 4; i++) {

    printf("%d\t",arry[i]);
  }

  printf("\n");

  return 0;
}
