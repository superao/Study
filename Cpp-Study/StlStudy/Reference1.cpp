// 学习"引用"的使用:
// 1.引用语法的使用
// 2.常引用的使用

#include <iostream>

using namespace std;

int main() {

  // 引用的基本语法:

  int a = 10;
  // 相当于 a 所对应的那块地址,又为它起了一个另外一个名字叫 b。
  // 它们的三者的地址完全相同。
  int& b = a;
  int& c = a;
  // int& d; 语法出错,引用必须初始化。
  // 对一个变量可以有多个引用。

  cout << a << endl;
  cout << b << endl;
  cout << c << endl;
  cout << "&a = " << &a << endl;
  cout << "&b = " << &b << endl;
  cout << "&c = " << &c << endl;

  // 常引用,以及利用"权限"来理解常引用:
  int aa = 20;
  int& ra = aa;

  const int aaa = 20;
  const int& raaa = aaa;

  // int& raaa = aaa;
  // 理解如下:
  // 本身 aaa 为 const int,即为"可读权限",现在你要把它赋值给一个 int,即为"可读可写权限",这样的话,
  // 相当于把权限给放大了,那么肯定是不允许,权限放大是不行的,权限放小是可以的.

  // 权限放小了:合法.
  int bbb = 10;
  const int& rbbb = bbb;

  // 权限没有改变:
  const int& ccc = 10;
  // 理解如下:
  // 在内存中的常量区,取一个数据'10',"可读权限",把它赋值给'const int', 即"可读赋值给可读权限".


  double da = 10.02;
  const int& rba = da;   // 对该数据进行可读是可以的,但是没有权限修改它的值.

  // int& rr = da;       // 类型不匹配,也可以利用权限来理解。


  return 0;
}


