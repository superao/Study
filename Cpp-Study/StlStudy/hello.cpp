// C++ 的第一个程序:
// 1.命令空间
// 2.函数重载
// 3.缺省函数

#include <iostream>

// 1.命名空间: 划分了标识符的作用域,使得相同名字的标识符在各自的作用区间功能不同。
using namespace std;
namespace superao{

  char* a = "superao";

  // 由于各个的作用区域不同,那就这样定义时没有任何问题的。
  int printf = 10;
}

// 2.函数重载
// 函数构成重载的原因:
// 由于 C++ 引入了函数名修饰规则,在修饰函数名的时候,加入了参数的类型等,可以通过"反汇编(objdump -S)"
// C 语言没有加入函数名修饰规则,在调用函数时,只是通过函数名,来调用函数,识别 不了函数之间的区别,所以构成不了重载
// 参数相同,返回值不同也构成不了重载,因为没有对它继续修饰。
int Add(int a, int b) {

  return a + b;
}

double Add(double a, double b) {

  return a + b;
}


// 3.缺省函数:当对函数不传参数,函数将使用默认的参数值,当然缺省值,只能从右向左进行缺省,并且中间不能"空".
// 3.1 全缺省
int mult(int a = 10, int b = 20) {

  return a * b;
}

// 3.2 半缺省
int divi(int a, int b = 2) {

  return a / b;
}

int main() {

  double a,b;
  cin >> a >> b;

  cout << Add(a,b) << endl;

  cout << mult() << endl;

  cout << mult(1,2) << endl;

  cout << divi(10) << endl;

  cout << divi(2,2) << endl;
 
  cout << superao::a << endl;
  cout << "hello world,change world!" << endl;
  return 0;
}

