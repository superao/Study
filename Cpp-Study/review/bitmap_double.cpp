// 对位图进行拓展(使用两个比特位来对元素的状态进行标记)
#include <iostream>
#include <vector>
using namespace std;

// 两个比特位来标记某个元素的状态
class bitmap
{
    public:
        bitmap(const int range = 1000)   // 默认比特为: 1000位
        {
            _bitmap.resize((range >> 4) + 1, 0);
        }

        void SetBit(int x)
        {
            int num1 = x >> 4;
            int num2 = x % 16;
            num2 *= 2;

            // x 第四次出现直接忽略
            if(_bitmap[num1] & (1 << num2) && _bitmap[num1] & (1 << (num2 + 1)))
            {
                cout << "已经出现第四次了，超过计数器上限了~" << endl;
            }
            // x 第三次出现
            else if(_bitmap[num1] & (1 << (num2 + 1)))
            {
                _bitmap[num1] |= (1 << num2);
            }
            // x 第二次出现
            else if(_bitmap[num1] & (1 << num2))
            {
                _bitmap[num1] |= (1 << (num2 + 1));
                _bitmap[num1] &= ~(1 << num2);
            }
            // x 第一次出现
            else 
            {
                _bitmap[num1] |= (1 << num2);
            }
        }

        void ClearBit(int x)
        {
            int num1 = x >> 4;
            int num2 = x % 16;
            num2 *= 2;

            // 11
            if(_bitmap[num1] & (1 << num2) && _bitmap[num1] & (1 << (num2 + 1)))
            {
                _bitmap[num1] &= ~(1 << num2);
            }
            // 10
            else if(_bitmap[num1] & (1 << (num2 + 1)))
            {
                _bitmap[num1] &= ~(1 << (num2 + 1));
                _bitmap[num1] |= (1 << num2);
            }
            // 01
            else if(_bitmap[num1] & (1 << num2))
            {
                _bitmap[num1] &= ~(1 << num2);
            }
        }

        int CheckBit(int x)
        {
            int num1 = x >> 4;
            int num2 = x % 16;
            num2 *= 2;
           
            // 11
            if(_bitmap[num1] & (1 << num2) && _bitmap[num1] & (1 << (num2 + 1)))
            {
                return 3;
            }
            // 10
            else if(_bitmap[num1] & (1 << (num2 + 1)))
            {
                return 2;
            }
            // 01
            else if(_bitmap[num1] & (1 << num2))
            {
                return 1;
            }
            // 00
            else 
            {
                return 0;
            }
        }
        
    private:
        vector<int> _bitmap;
};

int main()
{
    bitmap test;
    test.SetBit(100);
    test.SetBit(101);
    test.SetBit(104);
    test.SetBit(111);
    test.SetBit(134);
    test.SetBit(100);
    test.SetBit(100);
    test.SetBit(100);

    cout << test.CheckBit(101) << endl;
    cout << test.CheckBit(104) << endl;
    cout << test.CheckBit(111) << endl;
    cout << test.CheckBit(88) << endl;
    cout << test.CheckBit(100) << endl;
    cout << "----------------" << endl;

    cout << test.CheckBit(120) << endl;
    test.SetBit(120);
    cout << test.CheckBit(120) << endl;
    test.SetBit(120);
    cout << test.CheckBit(120) << endl;
    test.SetBit(120);
    cout << test.CheckBit(120) << endl;
    test.ClearBit(120);
    cout << test.CheckBit(120) << endl;
    test.ClearBit(120);
    cout << test.CheckBit(120) << endl;

    return 0;
}
