#include <iostream>
using namespace std;

// 定义一个模板类型的静态数组
// 数据类型    数组长度(非类型模板参数)
template<class T, size_t N>
class Array{
  public:
    void show()
    {
      cout << "静态数组" << endl;
      cout << "大小" << N << endl;
      cout << sizeof(T) << endl;
    }

  protected:
    // 类型为 T ，长度为 N 的静态数组
    T arry[N];
};

// 总结:
// 这样避免了开辟空间所带类内存消耗.

// 函数模板的特化
// 普通函数模板
template<class T1, class T2>
void Fun()
{
  cout << "class<T1, T2>" << endl;
}

// 函数模板的全特化
template<>
void Fun<char, int>()
{
  cout << "class<char, int>" << endl;
}

template<>
void Fun<char, char>()
{
  cout << "class <char, char>" << endl;
}

// 判断是否相等
template<class T>
bool Isequal(T a, T b)
{
  return a == b;
}

template<class T>
bool Isequal(T* a, T* b)
{
  // 这里，我们可以特殊化处理对字符串类型的一些操作
  cout << "字符串类型的特殊处理" << endl;
}

// 总结:
// 函数模板不支持偏特化.

// 类模板的特化(全特化/偏特化)
template<class T1, class T2>
class MyClass
{
  public:

    MyClass(T1 b1, T2 b2) :a1(b1), a2(b2){}


    void show()
    {
      cout << a1 << endl;
      cout << a2 << endl;
    }

  protected:
    T1 a1;
    T2 a2;
};

// 偏特化/半特化(两种表现形式)
// 1.部分参数特化
// 2.更进一步限制模板参数(指针，引用)
template<class T>
class MyClass<T, int>
{
  public:
    void show()
    {
      cout << "class<T, int>" << endl;
    }
};

template<class T>
class MyClass<char, T>
{
   
  public:
    void show()
    {
      cout << "class<char, T>" << endl;
    }
};

template<class T1, class T2>
class MyClass<T1*, T2*>
{
  public:
    void show()
    {
      cout << "class<T1*, T2*>" << endl;
    }
};

// 全特化(模板参数确定化)
template<>
class MyClass <int, int>
{
  public:
    void show()
    {
      cout << "class<int, int>" << endl;
    }
};
















