// 学习"引用"的使用:
// 1.引用作为函数参数来使用

#include <iostream>

using namespace std;

// 练习引用作为函数参数

// 传值
// 结论:没有交换它们的值,形参的数值,只是对实参值的一份拷贝,并没有改变原来的地址的值。
void Swap(int a, int b) {

  int temp = a;
  a = b;
  b = temp;
}

// 传址
// 结论:交换了它们的值,原因如下,由于函数参数传入的是它们的地址,直接用它们地址中的值来进行交换,
// 所以,最后 a, b 发生了改变,本质就是,原来地址中的东西发生了改变。
void Swap1(int* a, int* b) {

  int temp = *a;
  *a = *b;
  *b = temp;
}

// 传引用
// 结论:交换了它们的值,原因如下,由于引用的本质,就是对某一个地址起别名,相当于地址还是原来的地址,只有名字发生了改变
// 引用的底层还是利用指针来是实现的。
void Swap2(int& a, int& b) {

  int temp = a;
  a = b;
  b = temp;
}


int main() {
  
  int a = 10;
  int b = 20;

  cout << a << endl;
  cout << b << endl;
  
  Swap(a,b);

  Swap1(&a, &b);

  Swap2(a, b);

  cout << a << endl;
  cout << b << endl;

  return 0;
}


