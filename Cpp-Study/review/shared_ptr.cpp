// 模拟实现 shared_ptr
#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <memory>
using namespace std;

template <class T>
class Shared_Ptr
{
    public:
        Shared_Ptr(T* ptr = nullptr)
            :_ptr(ptr)
            ,_mutex(new mutex)
            ,_count(new int(1))
        {

        }

        Shared_Ptr(Shared_Ptr<T>& oldptr)
            :_ptr(oldptr._ptr)
            ,_mutex(oldptr._mutex)
            ,_count(oldptr._count)
        {
            // 计数器加1
            AddCount();
        }

        Shared_Ptr<T>& operator=(Shared_Ptr<T>& oldptr)
        {
            // 检测是否是自己给自己赋值
            if(_ptr == oldptr._ptr)
                return *this;

            // 释放旧资源
            Release();

            // 管理新资源
            _ptr = oldptr._ptr;
            _mutex = oldptr._mutex;
            _count = oldptr._count;
            AddCount();

            return *this;
        }

        ~Shared_Ptr()
        {
            Release();
        }

        T& operator*()
        {
            return *_ptr;
        }

        T* operator->()
        {
            return _ptr;
        }
        
        void GetCount()
        {
            cout << *_count << endl;
        }

    private:
        void AddCount()
        {
            _mutex->lock();
            (*_count)++;
            _mutex->unlock();
        }

        void DiminshCount()
        {
            _mutex->lock();
            (*_count)--;
            _mutex->unlock();
        }

        void Release()
        {
            // 计数器减1
            DiminshCount();
            _mutex->lock();
            if((*_count) != 0)
            {
                _mutex->unlock();
                return ;
            }

            // _count为 0，表示需要释放资源 
            delete _ptr;
            delete _count;
            _mutex->unlock();
            delete _mutex;
        }

    private:
        T* _ptr;        // 资源
        mutex* _mutex;  // 锁
        int* _count;    // 计数器
};

class Date
{
    public:
        void Print()
        {
            cout << _year << "-" << _month << "-" << _day << endl;
        }

    public:
        int _year;
        int _month;
        int _day;
};

// 测试自身引用计数是否是线程安全的      ->     线程安全
Shared_Ptr<Date> p1(new Date);
void threadfunc(int num)
{
    Shared_Ptr<Date> pp(p1);
    cout << num << ":";
    pp.GetCount();

    sleep(10);   // 防止线程执行完毕后，pp局部对象生命周期结束，释放掉对资源的管理权
}

// 测试对shared_ptr进行读写是否是线程安全的      ->     不是线程安全的
Shared_Ptr<Date> p2(new Date);
void threadfunc2(int num)
{
    cout << num << ":";
    p2->_year++;
    p2->_month++;
    p2->_day++;
    p2->Print();
}

int main()
{
    // 测试代码
    Shared_Ptr<Date> ptr1(new Date());
    ptr1->_year = 1999;
    ptr1->_month = 12;
    ptr1->_day = 22;
    ptr1->Print();              // 1999-12-22

    Shared_Ptr<Date> ptr2(ptr1);
    ptr2->_year = 2000;
    ptr2->Print();              // 2000-12-22

    // 测试ptr1
    ptr1->_month = 111;
    ptr1->Print();              // 2000-111-22
    ptr1.GetCount();            // 2 

    Shared_Ptr<Date> ptr3(new Date());
    ptr3.GetCount();            // 1

    ptr3 = ptr1;
    ptr3.GetCount();            // 3

    {
        Shared_Ptr<Date> ptr4(ptr1);
        ptr4.GetCount();        // 4
    }
    ptr1.GetCount();            // 3

    cout << "--------------------------------" << endl;
    
    // 多线程测试
//    for(int i = 0; i < 30; ++i) 
//    { thread th(threadfunc, i); 
//        th.detach(); 
//    }
    
    for(int i = 0; i < 200; ++i) 
    { thread th(threadfunc2, i); 
        th.detach(); 
    }

    sleep(100); 
    return 0; 
}
