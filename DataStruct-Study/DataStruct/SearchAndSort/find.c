// 遍历查找整个数组
// 1.优化版
// 2.非优化版

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 非优化版
int find(int arry[], int size, int k){

  // i:表示当前数组的下标
  int i = 1;
  for(i ; i < size; i++) {

    if(arry[i] == k) {

      printf("找到了: %d \n",i);
      return i;
    }
  }

  printf("没有找到\n");
  return 0;
}


// 优化版:
// 利用数组第 0 位来储存关键字,并且设置哨兵,从数组最后一位开始向前查找,当 i = 0,那么意味着没有找到.
// 优化了每次都需要判断数组是否越界的步骤。
int superfind(int arry[], int size, int k) {

  // 设置哨兵
  arry[0] = k;
  int i = size - 1;
  while(arry[i] != k) {

    i--;
  }

  if(i == 0) {

    printf("没有找到!\n");
  }
  else{

    printf("找到了: %d \n",i);
  }

  return i;
}
int main() {

  // 有效数据为[1 ~ size - 1]
  int arry[] = {0,2,4,9,5,2,7,6,8,10};

  find(arry,sizeof(arry) / sizeof(int), 100);
  
  superfind(arry,sizeof(arry) / sizeof(int), 100);

  return 0;
}
