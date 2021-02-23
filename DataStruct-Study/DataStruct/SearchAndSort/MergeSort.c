#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 合并两个有序数组
void Merge(int arry[], int left, int right, int* extra) {

  // i 表示左边区间的下标 [left,mid)
  // j 表示右边区间的下标 [mid, right)
  // k 表示数组的下标
  int i = left;
  int k = left;
  int mid = left + (right - left) / 2;
  int j = mid; // 注意,不能直接使用 mid ,因为 mid 的值一直在变化,会影响第二个数组的数据,可能会发生数组越界。

  // 只要两个数组中有一个没有了数,就退出循环
  while(i < mid && j < right) {

    if(arry[i] <= arry[j]) {

      extra[k++] = arry[i++];
    }
    else {

      extra[k++] = arry[j++];
    }

  }

  // 由于循环出来后,必定有一个数组已经为空,那么就将另一个数组的元素直接放到后面
  while(i < mid) {

    extra[k++] = arry[i++];
  }

  while(j < right) {

    extra[k++] = arry[j++];
  }

  // 将新数组中的值,放到原有数组中。
  int x = left;
  for(x; x < right; x++) {

    arry[x] = extra[x];
  }

}

// 归并排序 ---> 递归排序(分治)
void Mergeinner(int arry[], int left, int right, int* extra) {

  // 如果区间没有数了,则直接退出
  if(left >= right) {

    return ;
  }

  // [3, 4)
  // 如果区间只有一个数,那么它一定有序
  if(left + 1 == right) {

    return ;
  }


  // 平均分组
  int mid = left + (right - left) / 2;

  // 递归继续分组,直到区间有序(左闭右开)
  Mergeinner(arry,left,mid,extra);
  Mergeinner(arry,mid,right,extra);

  // 进行归并
  Merge(arry, left, right,extra);
}

void MergeSort(int arry[], int size) {

  // 新申请一个数组
  int* extra = (int*) malloc(sizeof(int) * size);
  if(extra == NULL) {

    perror("malloc error");
  }

  // 内部实现
  Mergeinner(arry,0,size,extra);

  free(extra);
}


int main () {

  int arry[] = {9,5,2,7,0,1};

  MergeSort(arry,sizeof(arry) / sizeof(int));

  int i = 0;
  for(i = 0; i < 6; i++) {

    printf("%d\t",arry[i]);
  }

  printf("\n");

  return 0;
}
