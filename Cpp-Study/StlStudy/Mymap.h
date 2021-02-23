// 利用红黑树适配出 map 容器
#include "rbt.h"

template<class K, class V>
class Map 
{
  public:
    // 仿函数
    class MapKeyOfVal
    {
      public:
        const K& operator()(const pair<K, V>& val)
        {
          return val.first;
        }
    };

    // 迭代器部分
    typedef typename RBTree<K, pair<K, V>, MapKeyOfVal>::iterator iterator; 
    typedef typename RBTree<K, pair<K, V>, MapKeyOfVal>::const_iterator const_iterator; 

    iterator begin()
    {
      return _rbt.begin();
    }

    iterator end()
    {
      return _rbt.end();
    }

    const_iterator begin() const 
    {
      return _rbt.begin();
    }

    const_iterator end() const
    {
      return _rbt.end();
    }

  public:
    pair<iterator, bool> Insert(const pair<K, V>& val)
    {
      return _rbt.Insert(val);
    }

    iterator Find(const pair<K, V>& val)
    {
      return _rbt.Find(val);
    }

    V& operator[](const K& key)
    {
      // 利用Insert返回值中的迭代器进行操作
      pair<iterator, bool> it = _rbt.Insert(make_pair(key, V()));
      // 需要重载 operator-> 来完成否则需要 *(is.first).second，并且此处还省略了一个箭头
      return it.first->second; 
    }

  private:
    RBTree<K, pair<K,V>, MapKeyOfVal> _rbt;
};
