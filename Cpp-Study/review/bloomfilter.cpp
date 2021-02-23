// 使用位图 + 字符串哈希函数实现布隆过滤器
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define SIZE 100000    // 位图的大小

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

class bloomfilter
{
    public:
        bloomfilter() : _bitmap(SIZE) {}

        // 插入
        void insert(string str)
        {
            size_t hash1 = SDBMHash(str.c_str()) % SIZE;
            size_t hash2 = RSHash(str.c_str()) % SIZE;
            size_t hash3 = APHash(str.c_str()) % SIZE;

            _bitmap.setbit(hash1);
            _bitmap.setbit(hash2);
            _bitmap.setbit(hash3);
        }

        // 布隆过滤器不支持删除操作
        void erase() = delete;

        // 查找
        bool find(string str)
        {
            size_t hash1 = SDBMHash(str.c_str()) % SIZE;
            size_t hash2 = RSHash(str.c_str()) % SIZE;
            size_t hash3 = APHash(str.c_str()) % SIZE;

            if(_bitmap.checkbit(hash1) && _bitmap.checkbit(hash2) 
            && _bitmap.checkbit(hash3))
                return true;
            else 
                return false;
        }

    private:
        // 哈希函数1:
        size_t SDBMHash(const char *str)
        {
            size_t hash = 0;
            while (size_t ch = (size_t)*str++)
            {
                hash = 65599 * hash + ch;
            }

            return hash;
        }

        // 哈希函数2:
        size_t RSHash(const char *str)
        {
            size_t hash = 0;
            size_t magic = 63689;
            while (size_t ch = (size_t)*str++)  
            {  
                hash = hash * magic + ch;  
                magic *= 378551;  
            }  

            return hash;
        }

        // 哈希函数3:
        size_t APHash(const char *str)
        {
            size_t hash = 0;  
            size_t ch;  
            for (long i = 0; ch = (size_t)*str++; i++)  
            {  
                if ((i & 1) == 0)  
                {  
                    hash ^= ((hash << 7) ^ ch ^ (hash >> 3));  
                }  
                else  
                {  
                    hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));  
                }  
            }

            return hash;
        }

    private:
        bitmap _bitmap;
};

int main()
{
    bloomfilter bf;
    bf.insert("abcd");
    bf.insert("hello");
    bf.insert("Hello");
    bf.insert("abdfbdfbdf");
    bf.insert("aaaa");

    cout << bf.find("abcd") << endl;
    cout << bf.find("hello") << endl;
    cout << bf.find("Hello") << endl;
    cout << bf.find("abd") << endl;
    cout << bf.find("aaaa") << endl;

    bf.insert("world!");
    cout << bf.find("world!") << endl;
    cout << bf.find("world") << endl;

    return 0;
}
