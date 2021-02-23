#include <iostream>
#include <thread>
using namespace std;

class A
{
  public:
    // 成员函数
    void sayhello(int a)                          // 本质上有两个变量
    {
      cout << "hello" << "a = " << a << endl;
    }

    // 静态成员函数
    static void sayhehe(int a)
    {
      cout << "hehe" << "a = " << a << endl;
    }
};

// 普通函数
void saywold(int a)
{
  cout << "world" << "a = " << a << endl;
}

int main()
{
  int a = 10;
  A temp;

  thread t1(&A::sayhello, temp, a);     // 对于成员函数来说，在传递的过程中需要将对象也一并传入，因为成员函数中有隐含的this指针变量
                                        // 如果不传递对象则就没有this指针，因此也就无法调用到相应的函数。
  thread t2(&saywold, a);               // 普通函数只需要函数地址以及所需要的变量即可用thread对象去执行。
  thread t3(&A::sayhehe, a);            // 静态成员函数属于整个类，没有this指针，它相当于一个带有作用域的全局函数，
                                        // 因此，我们只需要将带有作用域的函数地址与参数传递到thread对象中即可。

  t1.join();
  t2.join();
  t3.join();
  
  return 0;
}
