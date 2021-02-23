#include <iostream>
using namespace std;

namespace test1
{
    class A
    {
        public:
            int data;
        public:
            void* operator new(size_t size)
            {
                cout << "A::operator new()" << endl;
                return NULL;
            }

            void operator delete(void* ptr)
            {
                cout << "A::operator delete()" << endl;
            }

        public:
            A()
            {
                cout << "A()" << endl;
            }

            ~A()
            {
                cout << "~A()" << endl;
            }
    };

}

// 重载全局 operator new
void* operator new(size_t size)
{
    cout << "重载全局的operator new()" << endl;
    return NULL;
}

int main()
{
    test1::A* a = new test1::A;
    //a->A::A();                    // 不允许这样显示调用构造函数，析构函数
    //a->A::~A();
    delete a;
    cout << "----------------" << endl;

    int* p = new int;
    cout << p << endl;

    return 0;
}
