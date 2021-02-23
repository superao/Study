// 在auto_ptr, unique_ptr的基础上，学习并实现shared_ptr.
#include <memory>
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
class Date
{
  public:
    int _year = 0;
    int _month = 0;
    int _day = 0;

    ~Date()
    {
      cout << "~Date()" << endl;
    }
};

// 仿函数控制不同的删除
template<class T>
class Delete    // 删除普通元素
{
  public:
    void operator()(T* ptr)
    {
      if(ptr != nullptr)
      {
        delete ptr;
      }
    }
};

template<class T>
class DeleteArray // 删除数组元素 
{
  public:
    void operator()(T* ptr)
    {
      if(ptr != nullptr)
      {
        delete [] ptr;
      }
    }
};


// mutex _mut; 
// 全局锁的力度太大了，导致我们的效率没有提升，反而有可能效率会大大下降。

template<class T, class DeleteFun = Delete<T>>
class Shared_Ptr
{
  public:
    // 实现RAII(资源获取立即进行初始化)
    Shared_Ptr(T* ptr = nullptr) :_ptr(ptr), _count(new int), _mut(new mutex) { *_count = 1; }
    ~Shared_Ptr()
    {
      // 引用计数减 1 后等于 0 时我们再进行释放空间
      if(Mutex_Mutil() == 0)
      {
        // 释放内存
        DeleteFun()(_ptr);
        delete _count;
      }
    }

    // 加锁操作
    int Mutex_Add()
    {
      _mut->lock();
      (*_count)++;
      _mut->unlock();
      return *_count; 
    }

    int Mutex_Mutil()
    {
      _mut->lock();
      (*_count)--;
      _mut->unlock();
      return *_count; 
    }

    // 拷贝构造
    Shared_Ptr(Shared_Ptr& ap)
      :_ptr(ap._ptr)
      ,_count(ap._count)
    {
      Mutex_Add();
    }
    // 赋值构造
    Shared_Ptr& operator=(Shared_Ptr& ap)
    {
      if(&ap != this)
      {
        if(Mutex_Mutil() == 0)
        {
          delete _ptr;
          delete _count;
        }

        _ptr = ap._ptr;
        _count = ap._count;

        Mutex_Add();
      }
      return *this;
    }

    // 实现指针的功能
    T& operator*()
    {
      return *_ptr;
    }

    T* operator->()
    {
      return _ptr;
    }

    int Count()
    {
      return *_count;
    }

  private:
    T* _ptr;

    // 为每个空间增加一个引用计数，表示当前这块空间有几个指针在进行管理。
    int* _count;
    // 为每个空间设置一把锁，这样的话，每个空间的中的线程在某些地方并行操作
    // 而不同的空间中的线程并发操作，这样的话，我们的效率会大大的提升。
    mutex* _mut;
};
//
//void thread_start(Shared_Ptr<Date>& tmp)
//{
//
//  for(int i = 0; i < 100000; ++i)
//  {
//    Shared_Ptr<Date> sp(tmp);
//  }
//
//}
//
int main()
{
  // 单线程环境下
//  Shared_Ptr<Date> sp(new Date);
//  sp->_day = 100;
//  sp->_month = 100;
//  sp->_year = 100;
//  cout << sp->_year << " " << sp->_month << " " << sp->_day << endl;
//
//  Shared_Ptr<Date> sp1(sp);
//  sp1->_year = 2019;
//  sp->_month = 9;
//  sp->_day = 16;
//  cout << sp1->_year << " " << sp1->_month << " " << sp1->_day << endl;
//  cout << sp1.Count() << endl;
//
//  Shared_Ptr<Date> sp2(new Date);
//  Shared_Ptr<Date> sp3(sp2);
//  sp2 = sp;
//
//  cout << sp.Count() << endl;
//  cout << sp3.Count() << endl;

  // 多线程环境
//  Shared_Ptr<Date> sp(new Date);
//  std::thread t1(thread_start, sp);
//  std::thread t2(thread_start, sp);
//  
//  t1.join();
//  t2.join();
//  cout << sp.Count() << endl;

  // 不同元素的析构问题
//  Shared_Ptr<Date, DeleteArray<Date>> sp(new Date[10]);

  // 循环引用问题

  return 0;
}

