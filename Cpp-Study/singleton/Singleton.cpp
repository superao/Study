// 单例模式
#include <iostream>
#include <string>
using namespace std;

// 懒汉模式
class Singleton1
{
  public:
    static Singleton1* Getinstance()
    {
      if(instance == nullptr)
      {
        cout << "This is one" << endl;
        instance = new Singleton1();
      }
      else 
      {
        cout << "This is two" << endl;
      }

      return instance;
    }

  private:
    // 私有传统构造器
    Singleton1() { cout << "懒汉模式构造" << endl;};
    static Singleton1* instance;
};
Singleton1* Singleton1::instance = nullptr;


void Singleton1Test()
{
  Singleton1* s = Singleton1::Getinstance();
  Singleton1* s1 = Singleton1::Getinstance();
  cout << s << " " <<s1 << endl;
}




// 饿汉模式
class Singleton2 
{
  public:
    static Singleton2* Getinstance()
    {
      return instance;
    }

  private:
    Singleton2() {cout << "饿汉模式构造" << endl;};
    static Singleton2* instance;
};
Singleton2* Singleton2::instance = new Singleton2();


void Singleton2Test()
{
  Singleton2* s = Singleton2::Getinstance();
  Singleton2* s1(s);
  cout << s << " " <<s1 << endl;
}


int main()
{
  cout << "main 开始" << endl;
  Singleton1Test();
  Singleton2Test();
  return 0;
}
