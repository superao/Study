#include <stdio.h>
#include <stdlib.h>
#define MAX 10

// 折半查找：
void Find (int num[], int left, int right, int n) {
  
  int middle;
  while (left <= right) {
    
    middle = (left + right) / 2;
    if (num[middle] > n) {     // 如果小于中间的数，则缩小区间。
      right = middle - 1;
    }

    if (num[middle] < n) {
      left = middle + 1; 
    }

    if (num[middle] == n) {
      printf("找到了!\n");
      printf("下标为：%d\n", middle);
      return;
    }

  }
  printf("没有找到！");
  
}
int main() {
  
  int num[1024];
  int i, left, right;

  // 读入数字：
  printf("请输入10个数字：\n");
  for(i = 0; i < MAX; i++) {
    scanf("%d", &num[i]);
  }
  
  // 调用函数：
  left = 0;
  right = MAX - 1;
  printf("请输入需要查找的数字：");
  scanf("%d", &i);
  Find (num, left, right, i); 
  
  return 0;

}
