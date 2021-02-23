// 测试函数重载
#include <iostream>
using namespace std;

namespace AA
{
class B
{
    public:
        void add(int a, int b)
        {
            cout << "void add(int a, int b)" << endl;
        }

        int add(double a, int b)
        {
            cout << "int add(int a, int b)" << endl;
            return b;
        }
};
}

int main()
{
    AA::B a;
    a.add(10, 20);
    a.add(1.0, 20);

    return 0;
}
