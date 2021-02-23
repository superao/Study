#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 向下调整(调整为小堆)
void Heapfiy(int arry[], int size, int index){
  
  while(1) {

  // 1.如果为叶子结点，则直接退出。
  int leftchild = index * 2 + 1;
  if(leftchild >= size) {

    return ;
  }

  // 2.找到最小的孩子进行调整调换。
  int rightchild = index * 2 + 2;
  int minchild = leftchild;
  if(rightchild < size && arry[leftchild] > arry[rightchild]) {

    // 如果有右孩子，并且右孩子比左孩子小，则把右孩子赋值给最小的孩子。
    minchild = rightchild;
  }

  // 3.比较最小孩子的值与根节点的值，将两者最下的值赋值给根。
  if(arry[minchild] > arry[index]) {

    break;
  }
  else {

    // 进行交换
    int temp = arry[index];
    arry[index] = arry[minchild];
    arry[minchild] = temp;
  }

  // 4.将刚才交换的位置，继续进行向下调整
  index = minchild;

  } 
}


// 建堆 ---> 将无序的数组建立为一个小堆
void CreatHeap(int arry[], int size) {

  // 1.找到最后一个非叶子结点，从它开始进行向下调整，直到数组头元素。
  int unleaf = ((size - 1) - 1) / 2;
  for(unleaf; unleaf >= 0; unleaf--) {

    Heapfiy(arry, size, unleaf);
  }
}


// 堆排序 --> 升序建大堆，降序建小堆。(降序)
void HeapSort(int arry[], int size) {
  
  // 建堆
  CreatHeap(arry,size);
  // 将堆定元素放到数组中的最后一位，依次循环所有数组
  int i = 0;
  for(i = 0; i < size; i++) {

    int temp = arry[0];
    arry[0] = arry[size - 1 - i];
    arry[size - 1 - i] = temp;
    Heapfiy(arry, size - 1 - i, 0);
  }

}


int main() {

  // 待排序int arry[] = {1,2,7,8,5,9,8,1,8,0};
  int arry[] = {1,2,3,4,5};
  // 排序
  HeapSort(arry,(int)(sizeof(arry) / sizeof(int)));

  // 输出：
  int i = 0;
  for(i = 0; i < (int)(sizeof(arry) / sizeof(int)); i++) {

    printf("%d\t",arry[i]);
  }

  printf("\n");

  return 0;
}
