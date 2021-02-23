#include <iostream>
#include <vector>
using namespace std;

// 结点的状态
enum State
{
  EMPTY,
  EXIST,
  DELETE
};

// 哈希结点
template<class T>
struct HashNode 
{
  // 结点的值
  T _val;

  // 结点的状态(利用缺省值置空)
  State _sta;
};

// 哈希表
// 哈希函数：除留余数法
template<class K, class T>
class HashTable
{
  // typedef:
  typedef HashNode<T> Node;
  public:
    bool Insert(const T& val)
    {
      // 负载因子，保证有足够的空间，否则会无限线性探测下去
      if(_table.size() == 0 || 10 * _size / _table.size() > 6)
      {
        // 增容
        size_t newsize = _table.size() == 0 ? 10 : _table.size() * 2;

        // 重新映射
        // 传统写法：利用哈希函数重新计算，重新进行探测，最后在放入数据
        // 现代写法：创建新表，浅层递归，让别人去打工，我和他进行交换
        HashTable<K, T> _newtable;
        _newtable._table.resize(newsize);
        for(int i = 0; i < _table.size(); ++i)
        {
          if(_table[i]._sta == EXIST)
          {
            _newtable.Insert(_table[i]._val);
          }
        }

        // 进行交换
        _table.swap(_newtable._table);
      }


      // 计算地址/下标
      size_t index = val % _table.size();

      // 线性探测 index = index + i;
      // 线性探测在解决哈希冲突的时候，比较容易发生数据"堆积"现象，这样的话很大程度的减慢了我们的效率
//      while(_table[index]._sta == EXIST)
//      {
//        // 存在
//        if(_table[index]._val == val)
//        {
//          return false;
//        }
//
//        index++;
//        if(index == _table.size())
//        {
//          index = 0;
//        }
//      }
//
//      // 合适位置找到
//      _table[index]._val = val;
//      _table[index]._sta = EXIST;
//
//    // 二次探测 index = index + i ^ 2;
//    // 二次探测在一定程度上减少了我们数据"堆积"现象，虽然有，但是比较少，因此在一定程度上优化了我们的线性探测
//    // 但是需要严格控制我们的负载因子，否则还是会冲突，这样导致了我们的空间利用率比较低。我们还需要优化。
      size_t pos = index;
      int i = 1;
      while(_table[pos]._sta == EXIST)
      {
        if(_table[pos]._val == val)
        {
          return false;
        }

        pos = index + i * i;
        i++;
        if(pos >= _table.size())
        {
          pos = 0;
        }
      }

      _table[pos]._val = val;
      _table[pos]._sta = EXIST;

      // 增加计数
      _size++;

      return true;
    }

    size_t Find(const T& val)
    {
      size_t index = val % _table.size();
      while(_table[index]._sta != EXIST)
      {
        index++;
        if(index == _table.size())
        {
          index = 0;
        }
      }

      if(_table[index]._val == val)
      {
        return index;
      }
      else 
      {
        return -1;
      }
    }

    bool Erase(const T& val)
    {
      size_t index = Find(val);
      if(index >= 0 && index < _table.size())
      {
        _table[index]._sta = DELETE;
        _size--;

        return true;
      }
      else 
      {
        return false;
      }
    }

    vector<Node> _table;

    // 关联式容器中数据的个数需要自己统计，它不像序列式容器每个位置都存放了数据
    size_t _size = 0;  

    // 由于要考虑增容等一些比较恶心的问题，我们考虑用 vector 来辅助我们实现
    //HashNode* _table;
    //size_t _size;
    //size_t _capacity;
};



// 测试
void Hash_text()
{
  HashTable<int, int> t;
  t.Insert(2);
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    cout << t._table[i]._val << " ";
  }
  cout << endl;
  t.Insert(12);
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    cout << t._table[i]._val << " ";
  }
  cout << endl;
  t.Insert(32);
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    cout << t._table[i]._val << " ";
  }
  cout << endl;
  t.Insert(3);
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    cout << t._table[i]._val << " ";
  }
  cout << endl;
  t.Insert(4);
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    cout << t._table[i]._val << " ";
  }
  cout << endl;
  t.Insert(42);
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    cout << t._table[i]._val << " ";
  }
  cout << endl;
  t.Insert(0);
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    cout << t._table[i]._val << " ";
  }
  cout << endl;
  t.Insert(11);
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    cout << t._table[i]._val << " ";
  }
  cout << endl;
  t.Insert(11);
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    cout << t._table[i]._val << " ";
  }
  cout << endl;

  cout << "-----------------------------" << endl;

  cout << t.Erase(17) << endl;
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    if(t._table[i]._sta == EXIST)
      cout << t._table[i]._val << " ";
  }
  cout << endl;
  cout << t.Erase(1000) << endl;
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    if(t._table[i]._sta == EXIST)
      cout << t._table[i]._val << " ";
  }
  cout << endl;
  cout << t.Erase(2) << endl;
  for(size_t i = 0; i < t._table.size(); ++i)
  {
    if(t._table[i]._sta == EXIST)
      cout << t._table[i]._val << " ";
  }
  cout << endl;
}

