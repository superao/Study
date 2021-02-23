// 模拟实现 unique_ptr
#include <iostream>
using namespace std;

template <class T>
class Unique_Ptr
{
    public:
        Unique_Ptr(T* ptr = nullptr)
            :_ptr(ptr)
        {

        }

        ~Unique_Ptr()
        {
            if(_ptr)
                delete _ptr;
        }

        // 防止拷贝发生
        Unique_Ptr(Unique_Ptr<T>& oldptr) = delete;
        Unique_Ptr<T>& operator=(Unique_Ptr<T>& oldptr) = delete;

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
    Unique_Ptr<Date> ptr1(new Date());
    ptr1->_year = 1999;
    ptr1->_month = 10;
    ptr1->_day = 15;
    ptr1->Print();

    // Unique_Ptr<Date> ptr2(ptr1);      // 编译不通过，不允许多个unique_ptr管理同一份资源
    // ptr2 = ptr1                       // 编译不通过
    
    return 0;
}

