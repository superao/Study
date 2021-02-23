// 利用红黑树适配出 set 容器
#include "rbt.h"

template<class K>
class Set 
{
  public: 
    // 仿函数
    class SetKeyOfVal
    {
      public:
        const K& operator()(const K& val)
        {
          return val;
        }
    };

    // 迭代器部分
    // 这里体现了 typename 与 class 的唯一区别：
    // typename 告诉编译器后面这是类型，后面找不到需要的东西先别急着报错，等到前面实例化了，你再继续实例化后面的东西
    typedef typename RBTree<K, K, SetKeyOfVal>::iterator iterator;
    typedef typename RBTree<K, K, SetKeyOfVal>::const_iterator const_iterator;

    // Key 模型不允许修改，因此只有 const 迭代器
    const_iterator begin() const 
    {
      return _rbt.begin();
    }

    const_iterator end() const
    {
      return _rbt.end();
    }

  public:
    bool Insert(const K& val)
    {
      return _rbt.Insert(val).second;
    }

    iterator Find(const K& val)
    {
      return _rbt.Find(val);
    }


  private:
    RBTree<K, K, SetKeyOfVal> _rbt;
};
