// 利用引用计数实现可以标记数据重复的位图，布隆过滤器
// 说明：本质上我们为了节省空间一般用一位比特位进行标记数据的 2 种状态，但是数据如果有重复，我们一位无法完成标记，
// 因此上，需要多个比特位进行标记状态，具体需要几位我们视情况而定，这里我们假定数据最多重复两次，用两位进行标记。
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
    BitMap(const size_t size = 100) :_size(size)
    {
      _bit.resize(_size);
    }

    // 位图标记
    bool BitSet(size_t val)
    {
      if(val > _size)
      {
        return false; 
      }

      // 计算下标
      int charindex = val / 4;
      int bitindex = (val % 4) * 2;

      // 需要用来标记的两个比特位
      int one_bit = (_bit[charindex] & (1 << bitindex)) >> bitindex;
      int two_bit = (_bit[charindex] & (1 << (bitindex + 1))) >> bitindex;
      
      // 00 10 11
      // 第一次
      if(one_bit == 0 && two_bit == 0)
      {
        _bit[charindex] |=  (1 << bitindex);
        return true;
      }
      // 第二次
      else if (one_bit == 1 && two_bit == 0)
      {
        _bit[charindex] |=  (1 << (bitindex + 1));
        return true;
      }
      // 两次以上
      else 
      {
        return false;
      }
      
      return false;
    }

    // 位图删除
    bool ReSet(size_t val)
    {
      if(val > _size)
      {
        return false;
      }
      int charindex = val / 4;
      int bitindex = (val % 4) * 2;

      // 需要用来标记的两个比特位
      int one_bit = (_bit[charindex] & (1 << bitindex)) >> bitindex;
      int two_bit = (_bit[charindex] & (1 << (bitindex + 1))) >> bitindex;

      // 没有数据
      if(one_bit == 0 && two_bit == 0)
      {
        return false;
      }
      // 一个数据
      else if (one_bit == 1 && two_bit == 0)
      {
        _bit[charindex] &= ~(1 << bitindex);
        return true;
      }
      // 两个数据
      else 
      {
        _bit[charindex] &= ~(1 << (bitindex + 1));
        return true;
      }
      
      return false;
    }

    // 查找
    bool Find(size_t val)
    {
      if(val > _size)
      {
        return false;
      }
      int charindex = val / 4;
      int bitindex = (val % 4) * 2;

      int one_bit = (_bit[charindex] & (1 << bitindex)) >> bitindex;
      int two_bit = (_bit[charindex] & (1 << (bitindex + 1))) >> bitindex;
      if(one_bit == 0 && two_bit == 0)
      {
        return false;
      }
      else 
      {
        return true;
      }
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

    bool Delete(const T& val)
    {
      // 哈希函数 1 // 匿名函数对象
      size_t val1 = HashFun1()(val) % _size;
      if(_bit.ReSet(val1) != 1)
      {
        return false;
      }
      
      // 哈希函数 2
      size_t val2 = HashFun2()(val) % _size;
      if(_bit.ReSet(val2) != 1)
      {
        return false;
      }

      // 哈希函数 3
      size_t val3 = HashFun3()(val) % _size;
      if(_bit.ReSet(val3) != 1)
      {
        return false;
      }

      return true;
    }

  
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


  cout << bm.Delete("quit") << endl;
  cout << bm.Delete("str") << endl;

  cout << bm.BloomFilterTest("string") << endl;
  cout << bm.BloomFilterTest("ing") << endl;
  cout << bm.BloomFilterTest("str") << endl;
  cout << bm.BloomFilterTest("sort") << endl;
  cout << bm.BloomFilterTest("quit") << endl;
  cout << bm.BloomFilterTest("seng") << endl;
  return 0;
}
