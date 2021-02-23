// 数组模拟实现位图
#include <iostream>
#include <vector>
using namespace std;

class bitmap
{
    public:
        bitmap(const int range = 1000)         // 默认比特位为: 1000位(最大范围)
        {
            _bitmap.resize((range >> 5) + 1, 0);
        }

        // 将该元素对应的比特位置为 1
        void setbit(int x)
        {
            int num1 = x >> 5;
            int num2 = x % 32;
            _bitmap[num1] |= (1 << num2); 

            count++;
        }

        // 将该元素对应的比特位置为 0
        void clearbit(int x)
        {
            int num1 = x >> 5;
            int num2 = x % 32;
            _bitmap[num1] &= ~(1 << num2);

            count--;
        }

        // 查看该元素对应的比特位是否为 1
        bool checkbit(int x)
        {
            int num1 = x >> 5;
            int num2 = x % 32;
            
            if(_bitmap[num1] & (1 << num2))
                return true;
            else 
                return false;
        }

    private:
        vector<int> _bitmap;    // 存储结构
        int count = 0;
};

int main()
{
    // 测试位图
    bitmap test;
    test.setbit(0);
    test.setbit(2);
    test.setbit(5);
    test.setbit(7);
    test.setbit(8);
    test.setbit(55);
    test.setbit(89);
    test.setbit(888);
    
    cout << test.checkbit(2) << endl;
    cout << test.checkbit(5) << endl;
    cout << test.checkbit(55) << endl;
    cout << test.checkbit(89) << endl;
    cout << test.checkbit(20) << endl;
    cout << "------------------" << endl;
    test.clearbit(89);
    cout << test.checkbit(89) << endl;
    test.clearbit(888);
    cout << test.checkbit(888) << endl;
    cout << "-----------------" << endl;

    cout << test.checkbit(23) << endl;
    test.setbit(23);
    cout << test.checkbit(23) << endl;

    return 0;
}
