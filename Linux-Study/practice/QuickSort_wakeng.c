// 快速排序的总结:
// 1.找到基准值(3 种方法 --> 1.选取最右边 2.随机数 3.找中间).
// 2.将整个数组进行分割.(3 种方法 --> hoare 挖坑法 前后下标).
// 3.遍历每个区间，进行调换.
//      1.将比基准值小的放到数组的左边
//      2.将比基准值大的放到数组的右边

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
  // 将数组进行分割
  // 左闭右闭区间
  // 对左边所分割的区间再次继续分割  
  // 对左边所分割的区间再次继续分割

void Swap(int arry[], int a, int b) {

  int temp = arry[a];
  arry[a] = arry[b];
  arry[b] = temp;
}

// 分割 ---> 挖坑法
int partition(int arry[], int left, int right) {

  // 基准值
  // 默认使用最右边的作为基准值
  int povit = arry[right];

  // 对区间进行遍历
  int begin = left;
  int end = right;
  while(begin < end) {

    // 如果还有区间并且 begin 所在的值小于等于 povit,则
    while(begin < end && arry[begin] <= povit) {
                      // 特别注意:这里如果没有等于号的话,程序就会出现逻辑错误
                      // 例子1:当两头的数据相等的话,他就是死循环
                      // 例子2:当第一个数大于基准的话,他会不停交换，最后交换完数据还是没有变
      begin++;
    }

    // 由于现在找到了一个比 povit 大的数了,现在将它填到坑中
    arry[end] = arry[begin];

    // 如果还有区间并且 end 所在的值大于等于 povit 则
    while(begin < end && arry[end] >= povit) {

      end--;
    }

    // 由于刚才将一个数填到坑中了,又有一个坑是空闲的，所以将他继续填到坑中去。
    arry[begin] = arry[end];

  }


  // 由于在填坑的时候,数组最后一个数(基准)已经被替换了,所以直接将基准值赋值给 begin
  arry[begin] = povit;

  return begin;
}


void QuickInner(int arry[], int left, int right) {

  // 递归终止条件
  if(left == right) {

    // 如果区间只剩下一个数,那么就说明它一定在该区间中是有序的。
    return ;
  }

  if(left > right) {

    // 如果区间没有数了，那么直接退出
    return ;
  }

  int mid = partition(arry,left,right);

  // 递归过程
  QuickInner(arry,left,mid - 1); // 对左边小的区间继续进行分割,分组
                                 // mid 在对应的位置是有序的
  QuickInner(arry,mid + 1,right);// 对右边小的区间继续进行分割,分组

}

// 快速排序 ---> 递归排序的一种。
void QuickSort(int arry[], int size){

  // 内部实现
  QuickInner(arry,0,size - 1);
}


int main () {

  int arry[] = {9,5,2,7,3,6,9,0};

  QuickSort(arry,sizeof(arry)/sizeof(int));

  int i = 0;
  for(i = 0; i < 8; i++) {

    printf("%d\t",arry[i]);
  }

  printf("\n");
  return 0;
}
