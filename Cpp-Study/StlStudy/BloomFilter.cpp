#include <iostream>
#include <vector>
using namespace std;

// 仿函数
template<class T> 
class HashFun1 
{
  public:
    size_t operator()(const T& str)
    {
      size_t hash = 0;
      for (auto& ch : str)
      {
        hash = hash * 599 + ch;

      }
      return hash;
    }
};

template<class T> 
class HashFun2 
{
  public:
    size_t operator()(const T& str)
    {
      size_t hash = 0;
      for (auto& ch : str)
      {
        hash = hash * 652 + ch;

      }
      return hash;
    }
};

template<class T> 
class HashFun3 
{
  public:
    size_t operator()(const T& str)
    {
      size_t hash = 0;
      for (auto& ch : str)
      {
        hash = hash * 131 + ch;

      }
      return hash;
    }
};

class BitMap
{
  public:
    BitMap(const size_t size) :_size(size)
    {
      _bit.resize(_size);
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

    // 位图空间大小
    size_t _size;
};


// 布隆过滤器 = 哈希函数(3个仿函数/函数对象) + 位图
template<class T, class HashFun1 = HashFun1<T>, class HashFun2 = HashFun2<T>, class HashFun3 = HashFun3<T>>
class BloomFilter 
{
  public:
    BloomFilter(const size_t size = 100) :_size(size), _bit(_size) {}

    // 映射
    void BloomFilterSet(const T& val)
    {
      // 哈希函数 1 // 匿名函数对象
      size_t val1 = HashFun1()(val) % _size;
      _bit.BitSet(val1);
      
      // 哈希函数 2
      size_t val2 = HashFun2()(val) % _size;
      _bit.BitSet(val2);

      // 哈希函数 3
      size_t val3 = HashFun3()(val) % _size;
      _bit.BitSet(val3);
    }
    
    // 查找
    bool BloomFilterTest(const T& val)
    {
      // 哈希函数 1
      size_t val1 = HashFun1()(val) % _size;
      if(_bit.Find(val1) != 1)
      {
        return false;
      }
      
      // 哈希函数 2
      size_t val2 = HashFun2()(val) % _size;
      if(_bit.Find(val2) != 1)
      {
        return false;
      }

      // 哈希函数 3
      size_t val3 = HashFun3()(val) % _size;
      if(_bit.Find(val3) != 1)
      {
        return false;
      }

      return true;     // 误判
    }

    // 布隆过滤器是没有删除功能的，因为一个值映射了多个位置，
    // 当删除某个值的时候会影响到其他的值，因此是严格意义上是没有删除功能的。
  
  private:
    // 空间个数
    size_t _size;

    // 位图
    BitMap _bit;
};

int main()
{

  BloomFilter<string> bm;
  bm.BloomFilterSet("string");
  bm.BloomFilterSet("ing");
  bm.BloomFilterSet("str");
  bm.BloomFilterSet("sort");
  bm.BloomFilterSet("quit");
  bm.BloomFilterSet("insert");
  bm.BloomFilterSet("seng");

  cout << bm.BloomFilterTest("string") << endl;
  cout << bm.BloomFilterTest("ing") << endl;
  cout << bm.BloomFilterTest("str") << endl;
  cout << bm.BloomFilterTest("sort") << endl;
  cout << bm.BloomFilterTest("quit") << endl;
  cout << bm.BloomFilterTest("seng") << endl;

  return 0;
}














