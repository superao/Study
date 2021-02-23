// 学习使用委派构造函数
#include <iostream>
#include <string>
using namespace std;

class Person
{
  public:
    // 目标构造函数
    Person(const string school = "西安工业大学", const string address = "西安未央") :_school(school), _address(address)
      ,_name(""), _age(0), _grade(0.0)
    {
      cout << "我是目标构造函数:" << endl;
      cout << _school << endl;
      cout << _address << endl;
      cout << _name << endl;
      cout << _age << endl;
      cout << _grade << endl;
    }

    // 委派构造函数 1 
    Person(const int age) 
      :Person()
    {
      _age = age;
      cout << "我是委派构造函数 1:" << endl;
      cout << _school << endl;
      cout << _address << endl;
      cout << _name << endl;
      cout << _age << endl;
      cout << _grade << endl;
    }
    // 委派构造函数 2 
    Person(const double grade) 
      :Person()
    {
      _grade = grade;
      cout << "我是委派构造函数 2:" << endl;
      cout << _school << endl;
      cout << _address << endl;
      cout << _name << endl;
      cout << _age << endl;
      cout << _grade << endl;
    }

    // 注意: 目标构造函数与委派构造函数之间不要相互调用，这样会导致循环压栈，导致程序崩溃。

  private:
    string _school;
    string _address;
    string _name;
    int _age;
    double _grade;
};

int main()
{
  Person p(10);
  Person p1(1.23);
  return 0;
}
