// 快速排序
// 1.选取最右边的数作为基准值。
// 2.前后指针法(好写)
// 3.非递归
// 4.左闭右闭区间

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

void Swap(int arry[], int d, int i) {

      int temp = arry[d];
      arry[d] = arry[i];
      arry[i] = temp;
}


// 前后指针:i 在前跑,d 在后跑``.
int partition(int arry[], int left, int right) {

  int povit = arry[right];

  // i 表示遍历整个数组,并且与基准值继续比较,d 到 i 区间表示比基准值大。
  int i = left;
  int d = left;
  for(i = left; i < right; i++) {

    // d 表示 d 之前的区间比基准值小。
    if(arry[i] < povit) {

      // 如果比基准小,就与 d 所在的下标进行交换。
      // 目的:将小的数放到前面,有点类似于冒泡的方法,只是有时候,步幅较大而已
      Swap(arry,d,i);
      d++;
    }
  }

  // 循环出来后,最后再将基准值放到合适的位置(d 所在的下标)
  Swap(arry,d,right);

  return d;
}

void Quickinner(int arry[], int left, int right) {

  // 非递归 ---> 栈 + 循环
  // 创建一个栈
  std::stack<int> stack;

  // 开始循环: 将数组左右边界压入栈中
  stack.push(right);
  stack.push(left);

  // 栈不为空,就一直进行 partition,直到所有元素带自己的位置
  while(!stack.empty()) {

    int left = stack.top();
    stack.pop();

    int right = stack.top();
    stack.pop();

    // 注:如果某一段区间长度不存在/为 0 ,则直接进行另一端。
    if(left >= right) {

      continue;
    }



    // 进行 partition
    int mid = partition(arry,left,right);

    // 继续将两边小数组依次压栈,由于想先处理左边的数组,所以先压右边的。
    // 在压栈的时候,检查数组是否越界。
    stack.push(right);
    stack.push(mid + 1);
    
    stack.push(mid - 1);
    stack.push(left);
   }
}


void QuickSort(int arry[], int size) {

  // 内部实现
  Quickinner(arry,0,size - 1);
}

int main() {

  int arry[] = {9,5,2,7,6,3,8,4,0};
  int size = sizeof(arry) / sizeof(int);

  QuickSort(arry, size);

  int i = 0; 
  for(i = 0; i < size; i++) {

    printf("%d\t", arry[i]);
  }

  printf("\n");
  return 0;
}
