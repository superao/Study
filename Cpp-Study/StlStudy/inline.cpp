// 体会内联函数与宏之间的区别
#include <iostream>
// 宏
// 选出最大值的宏
#define MAX(a,b) ((a) > (b) ? (a) : (b))

// 用宏来实现值的交换
#define SWAP(a,b) {int t = *a;\
                  *a = *b;\
                  *b = t;\
                  }

// 内联函数来实现相同的功能
inline int Max(int a, int b) {

  return a > b ? a : b;
}

inline void Swap(int& a, int& b) {

  int t = a;
  a = b;
  b = t;
}

using namespace std;

int main () {

  int a = 10;
  int b = 20;

  SWAP(&a,&b);
  Swap(a,b);

  cout << a << endl;
  cout << b << endl;

  return 0;
}

// 内联函数的作用:
// inline 的作用就是告诉编译器(只是一个建议),在调用内联函数的地方直接展开,不要函数压栈,这样少去了函数压栈的开销
// 从而提高了程序的运行效率。
// 宏相比而言的优缺点:
// 1.增强代码的复用性
// 2.提高性能
// 缺点:
// 1.不能调式
// 2.代码可读性变差,不易于维护
// 3.没有安全性检查

// 我们可以用 const enum inlian 来替换宏
