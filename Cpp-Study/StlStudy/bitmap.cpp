// 学习并实现位图
#include <iostream>
#include <vector>
using namespace std;

class BitMap
{
  public:
    BitMap(size_t size) :_size(size)
    {
      // 开所需要的比特位
      int num = (size / 8) + 1;
      _bit.resize(num);
    }

    // 位图标记
    void BitSet(size_t val)
    {
      if(val > _size)
      {
        return ;
      }
      // 表示所在的字符类型空间
      int charindex = val / 8;
      // 表示所在字符中的比特位
      int bitindex = val % 8;

      // 将所表示的比特位置为 1
      _bit[charindex] |= (1 << bitindex);
    }
    // 位图删除
    void ReSet(size_t val)
    {
      if(val > _size)
      {
        return ;
      }
      // 表示所在的字符类型空间
      int charindex = val / 8;
      // 表示所在字符中的比特位
      int bitindex = val % 8;

      // 将所表示的比特位置为 0
      _bit[charindex] &= ~(1 << bitindex);

    }

    // 查找某个数是否存在
    bool Find(size_t val)
    {
      if(val > _size)
      {
        return false;
      }
      // 表示所在的字符类型空间
      int charindex = val / 8;
      // 表示所在字符中的比特位
      int bitindex = val % 8;

      return _bit[charindex] & (1 << bitindex);
    }


    // 统计个数
    int count()
    {
      int sum = 0;
      for(size_t i = 0; i < _bit.size(); ++i)
      {
        char num = _bit[i];
        for(size_t j = 0; j < 8; ++j)
        {
          if((num & 1) == 1)
          {
            sum++;
          }

          num = num >> 1;
        }
      }

      return sum;
    }

  private:
    // 位图
    vector<char> _bit;

    // 海量数据中最大的一个数据(用来开辟最大比特位) 
    size_t _size;
};


void Test()
{
  BitMap m(30);
  m.BitSet(7);
  m.BitSet(2);
  m.BitSet(6);
  m.BitSet(1);
  m.BitSet(0);
  m.BitSet(8); 
  m.BitSet(10);
  m.BitSet(20);
  m.BitSet(30);

  cout << m.count() << "--------" << endl;

  m.ReSet(1);
  m.ReSet(7);


  cout << m.Find(10) << endl;
  cout << m.Find(7) << endl;
  cout << m.Find(1) << endl;
  cout << m.Find(0) << endl;
  cout << m.Find(2) << endl;
  cout << m.Find(8) << endl;
  cout << m.Find(6) << endl;

  cout << m.count() << "--------" << endl;
}


int main()
{
  Test();
  return 0;
}
