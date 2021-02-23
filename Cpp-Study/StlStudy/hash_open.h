// 哈希冲突开散列
#include <vector>
using namespace std;

// 数据结点
template<class T>
struct HashNode 
{
    T _val;
    HashNode<T>* _next;

    // 构造函数
    HashNode(const T& val = T()) :_val(val), _next(nullptr) {}
};

// 哈希表类在找的时候找不到，因为它在下方，因此需要在这声明
template<class K, class T>
class HashTable;

// 迭代器
template<class K, class T>
class __Hash_Iterator
{
  // typedef 
  typedef HashNode<T> HashNode;
  typedef __Hash_Iterator<K, T> Self;
  typedef HashTable<K, T> HashTable; 

  private:
    // 结点指针
    HashNode* _node;
    // 用来计算当前结点的位置
    HashTable* _ptable;

  public:
    // 结点指针构造函数
    __Hash_Iterator(HashNode* node, HashTable* ptable) :_node(node), _ptable(ptable) {}
    
    const T& operator*()
    {
      return _node->_val;
    }

    const T* operator->()
    {
      return &(operator*());
    }

    // 前置++
    Self operator++()
    {
      if(_node->_next == nullptr)
      {
        // 已到底某一条链的尽头，需要到下一个链的头部
        size_t index = _node->_val % _ptable->_table.size();
        while(_ptable->_table.size() != ++index) 
        {
          if(_ptable->_table[index] != nullptr)
          {
            _node = _ptable->_table[index];
            return *this;
          }
        }

        // 到达尽头
        _node = nullptr;
      }
      else 
      {
        // 没有到达某一条链的尽头
        _node = _node->_next;
      }

      return *this;
    }

    bool operator!=(const Self& s)
    {
      return _node != s._node;
    }

};

// 哈希表
template<class K, class T>
class HashTable 
{
  // typedef 
  typedef HashNode<T> HashNode;
  typedef __Hash_Iterator<K, T> iterator;
  
  friend class __Hash_Iterator<K, T>;

  private:
    vector<HashNode*> _table;
    size_t _size;
  
  public:
    iterator begin()
    {
      for(int i = 0; i < _table.size(); ++i)
      {
        if(_table[i] != nullptr)
        {
          return iterator(_table[i], this);
        }
      }

      return iterator(nullptr, this);
    }

    iterator end()
    {
      return iterator(nullptr, this);
    }

    bool Insert(const T& val)
    {
      // 负载因子
      if(_table.size() == 0 || 10 * _size / _table.size() >= 10)
      {
        // 增容                                可用素数表进行优化
        int newsize = _table.size() == 0 ? 10 : _table.size() * 2;

        // 现代写法
        HashTable<K, T> newtable;
        newtable._table.resize(newsize);

        // 将旧表中的数据全部移动到新表
        for(size_t i = 0; i < _table.size(); ++i)
        {
          HashNode* cur = _table[i];
          while(cur)
          {
            // 这里不能调用新表的插入，调用会导致内存泄漏(旧表中的结点无法释放)，需要自行头插。
            HashNode* next = cur->_next;

            // 头插
            size_t index = cur->_val % newtable._table.size();
            cur->_next = newtable._table[index];
            newtable._table[index] = cur;

            cur = next;
          }

          _table[i] = nullptr;
        }

        _table.swap(newtable._table);
      }


      // 计算映射位置
      size_t index = val % _table.size();
      HashNode* cur = _table[index];
      while(cur)
      {
        if(cur->_val == val)
        {
          return false;
        }

        cur = cur->_next;
      }

      // 头插
      HashNode* newnode = new HashNode(val);
      newnode->_next = _table[index];
      _table[index] = newnode;

      return true;
    }

    HashNode* Find(const T& val)
    {
      // 计算映射位置
      size_t index = val % _table.size();
      HashNode* cur = _table[index];
      while(cur)
      {
        if(cur->_val == val)
        {
          return cur;
        }

        cur = cur->_next;
      }

      return nullptr;
    }

    bool Erase(const T& val)
    {
      size_t index = val % _table.size();
      HashNode* cur = _table[index];
      HashNode* prev = nullptr;
      while(cur)
      {
        if(cur->_val == val && prev != nullptr)
        {
          prev->_next = cur->_next;
          delete cur;
          return true;
        }
        else if (cur->_val == val)
        {
          _table[index] = cur->_next;
          delete cur;
          return true;
        }

        prev = cur;
        cur = cur->_next;
      }

      return false;
    }
};
