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

// 分割 ---> 前后指针法
int partition(int arry[], int left, int right) {

  int povit = arry[right];

  // d 下标之前的数表示比基准值小;d 与 i 下标之间的数表述比基准值大。
  int d = left;
  // i 用来遍历数组整个数组,并且与基准值进行比较,如果比基准值小,就交换 i d 下标所在的值
  // 这样的话,可以把大数放后面,小数放前面。
  int i = left;
  for(i = left; i < right; i++) {

    if(arry[i] < povit) {

      // 交换值
      Swap(arry,d,i);
      d++;
    }
  }

  Swap(arry,d,right);

  return d;
}


void QuickInner(int arry[], int left, int right) {

  // 递归终止条件
  if(left  == right) {

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
                                 // mid 在对应的位置是有序的*****
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
