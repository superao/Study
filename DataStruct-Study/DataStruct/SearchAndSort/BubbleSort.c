// 优化版的冒泡排序
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 左闭右闭区间
void BubbleSort(int arry[], int size) {

  // 有序区间[size - 1 - i + 1,size - 1]
  // 无序区间[0, size - 1 - i]
  // 每次只能处理一个数,那么就需要处理 size - 1次
  int i = 0;
  for(i = 0; i < size; i++) {

    // 优化:
    int flag = 0;

    int j = 0;
    for(j = 0; j < size - 1 - i; j++) {
            // 有等号的话会发生错误,由于引用了 j + 1 .
      if(arry[j] > arry[j + 1]) {

        flag = 1;

        // 相邻的两个数,如果前者比较大,就将他们进行交换
        int temp = arry[j];
        arry[j] = arry[j + 1];
        arry[j + 1] = temp;
      }
    }

    // 说明没有发生过一次交换,该数组本身有序,直接退出。
    if(flag == 0) {

      break;
    }
  }
}

int main() {

  int arry[] = {9,5,2,7,1,0,3};

  BubbleSort(arry,7);

  int i = 0;
  for(i = 0; i < 7; i++) {

    printf("%d\t",arry[i]);
  }

  printf("\n");

  return 0;
}
