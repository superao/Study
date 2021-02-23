#include <iostream>

using namespace std;
// 与运算符相关的一些常见操作:
// 将整数二进制中的某一位置为 1 ,置为 0.
void Set_one(int num, int n) {
  
  num = num | (1 << n);
  cout << num << endl;
}

void Set_zero(int num, int n) {

  num = num & ~(1 << n);
  cout << num << endl;
}

// 判断二进制位中有多少个 1 .(不能判断负数中有多少个 1)
int Num_one(int num) {

  int count = 0;
  while(num != 0) {

    // 如果最后一位为 1(奇数),那么 count++
    // 如果 num 为负数这里就会出错.
    if(num % 2 == 1) {

      count++;
    }

    num = num / 2;
    // num = num >> 1;
  }

  return count;
}

// 正负数都可以进行统计。
int Super_Num_One(int num) {

  int count = 0;
  for(int i = 0; i < (int)sizeof(int) * 8; i++) {

    if(((num >> i) & 1)  == 1) {

      count++;
    }
  }
  return count;
}
int main() {

  int num = 1;

  Set_one(num, 4);
  Set_zero(num, 4);

  int n = 10;
  cout << Num_one(n) << endl;

  cout << Super_Num_One(-10) << endl;


  return 0;
}

// 常见的运算符详解(查补知识弱点)
// https://blog.csdn.net/weixin_43411365/article/details/90109181
