#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 插入排序(最好理解的，但是是没有优化过的。)
void InsertSort(int arry[], int size) {

  // 有序区间[0, i - 1];
  // 无序区间[i, size - 1];
  // 由于插入排序一次只能处理一个数，故外层需要 size 次。
  int i = 0;
  for(i = 0; i < size; i++) {

    // i表示需要待排的数的下标。
    // 在有序区间进行查找合适的位置。
    int j = 0;
    for(j = 0; j <= i - 1 && arry[j] > arry[i]; j++);

    // 顺序表的插入，移出空的位置。
    int key = arry[i];
    int k = i;
    for(k = i; k > j; k--) {

      // 往后搬。
      arry[k] = arry[k - 1];
    }

    // 新数入位
    arry[j] = key;

  }
}


int main() {

  int arry[] = {9,5,2,7};
  InsertSort(arry,4);

  int i = 0;
  for(i = 0; i < 4; i++) {

    printf("%d\t", arry[i]);
  }

  printf("\n");
  return 0;
}
