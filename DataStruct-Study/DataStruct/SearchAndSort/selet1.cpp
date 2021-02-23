// 选择排序:从小到大,从前往后选.
// 有序区间:[0,i)
// 无序区间:[i,size)
// 大致思路:遍历无序区间,找到最小值,并用 flag 来记录下标,最后和无序区间的第一个值进行交换,一直循环,直到整体有序.

#include <iostream> 

using namespace std;

void Swap(int arry[], int a, int b) {

  int t = arry[a];
  arry[a] = arry[b];
  arry[b] = t;
}


void Select_Sort(int arry[], int size) {

  // i:表示有序数组的下标
  int i = 0;
  for(i = 0; i < size; i++) {

    int flag = i;
    int j = i + 1;
    // 挑选区间最小值
    for(j = i + 1; j < size; j++) {

      if(arry[flag] > arry[j]) {

        flag = j;
      }
    }

    Swap(arry,flag,i);
  }
}

int main () {

  int arry[] = {1,4,7,2,6,8,5,9,0,9,5,2,7};

  Select_Sort(arry,sizeof(arry) / sizeof(int));

  for(int i = 0; i < (int)(sizeof(arry) / sizeof(int)); i++) {

    cout << arry[i] << endl;
  }

  return 0;
}
