// 模拟实现 auto_ptr
#include <iostream>
using namespace std;

template <class T>
class Auto_Ptr
{
    public:
        Auto_Ptr(T* ptr = nullptr)
            :_ptr(ptr)
        {

        }

        ~Auto_Ptr()
        {
            if(_ptr)
                delete _ptr;
        }

        Auto_Ptr(Auto_Ptr<T>& oldptr)
            :_ptr(oldptr._ptr)              // 直接将资源管理权交给新对象
        {
            oldptr._ptr = nullptr;     
        }

        Auto_Ptr<T>& operator=(Auto_Ptr<T>& oldptr)
        {
            if(oldptr._ptr == _ptr)
                return *this;

            // 释放之前的资源
            if(_ptr)
                delete _ptr;

            // 管理新资源
            _ptr = oldptr._ptr;             // 直接将资源管理权交给新对象
            oldptr._ptr = nullptr;
            return *this;
        }

        // 提供像指针一样的操作
        T& operator*()
        {
            return *_ptr;
        }

        T* operator->()
        {
            return _ptr;
        }
         
    private:
        T* _ptr;
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

int main()
{
    // 测试代码
    Auto_Ptr<Date> ptr1(new Date());
    ptr1->_year = 1999;
    ptr1->_month = 1;
    ptr1->_day = 1;
    ptr1->Print();

    Auto_Ptr<Date> ptr2(ptr1);      // ptr1管理的资源将转交给ptr2管理，ptr1将失去管理权
    ptr2->_month = 10;
    ptr2->_day = 15;
    ptr2->Print();

    // ptr1->_year = 2000;   段错误，内存访问越界
    // ptr1->Print();
    
    return 0;
}

