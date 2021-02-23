#include <iostream>
#include <map>
using namespace std;

typedef enum color {RED, BLACK} color;

template <class V>
class RBTreeNode
{
  public:
    RBTreeNode(const V& val) :_val(val), _left(nullptr), _right(nullptr), _parent(nullptr),
    _col(RED) {}            // 注：新插入结点的颜色必须为红色，因为每条路径的黑色结点数目是相同的
                            // 如果新插入黑色，那么会影响每条路径的黑色数目，而新插入红色结点，影响较小
    V _val;

    RBTreeNode<V>* _left;
    RBTreeNode<V>* _right;
    RBTreeNode<V>* _parent;

    color _col;             // 利用颜色来进行控制近似平衡
};

// 迭代器类模板
// 说明：1.由于底层适配上层的容器，因此，必须使用模板(不同的值有不同的指针和不同的引用)
//       2.由于迭代器本质就是指针，因此，需要指针来作为支撑
//       3.由于访问的某些地方需要修改，因此，需要引用来进行支撑
// 迭代器结构
template <class V, class Ptr, class Ref>
class __RBTree_iterator
{
  public:
    // 成员变量(迭代器的本质:结点指针)
    typedef RBTreeNode<V> Node;
    Node* _pnode;

  public:
    // 利用一个指针来构造迭代器
    __RBTree_iterator(Node* pnode) :_pnode(pnode) {};


  public:
    // 返回自身类型方便(++ / --)
    typedef __RBTree_iterator<V, Ptr, Ref> Self;

    // 中序：前根后
    // ++it
    Self& operator++()
    {
      // 当前结点的右树为空
      if(_pnode->_right == nullptr)
      {
        Node* par = _pnode->_parent;
        while(par != nullptr && par->_right == _pnode)
        {
          _pnode = par;
          par = par->_parent;
        }

        _pnode = par;
      }
      // 右树没空，就去右树的最左结点
      else 
      {
        _pnode = _pnode->_right;
        while(_pnode->_left)
        {
          _pnode = _pnode->_left;
        }
      }

      return *this;
    }

    Self operator++(int)
    {
      Node* temp = *this;
      ++(*this);
      return temp;
    }

    bool operator!=(const Self& s) const 
    {
      return _pnode != s._pnode; 
    }

    Ref operator*()
    {
      return _pnode->_val;
    }

    Ptr operator->()
    {
      return &(operator*());
    }
};

                             // 传入仿函数 
template <class K, class V, class KeyOfVal>
class RBTree
{

  public:
  // 普通迭代器
  typedef __RBTree_iterator<V, V*, V&>  iterator;
  // const 迭代器
  typedef __RBTree_iterator<V, const V*, const V&> const_iterator;

  typedef RBTreeNode<V> Node;
  // 搜索树迭代器部分
  public:
    iterator begin()
    {
      Node* cur = _root;
      while(cur->_left)
      {
        cur = cur->_left;
      }

      // 构造出一个迭代器类型
      return iterator(cur);
    } 
    iterator end()
    {
      return iterator(nullptr);
    }

    const_iterator begin() const
    {
      Node* cur = _root;
      while(cur->_left)
      {
        cur = cur->_left;
      }

      return const_iterator(cur);
    } 
    const_iterator end() const
    {
      return const_iterator(nullptr);
    }
 
  // 搜索树部分
  public:
    RBTree(Node* root = nullptr) :_root(root) {}
    ~RBTree() { Destroy(_root); }

    iterator Find(const V& val)
    {
      Node* cur = _root;
      KeyOfVal kov;

      while(cur)
      {
        if(kov(cur->_val) > kov(val)) 
        {
          cur = cur->_left;
        }
        else if(kov(cur->_val) < kov(val))
        {
          cur = cur->_right;
        }
        else 
        {
          // 找到了
          return iterator(cur);
        }
      }

      return iterator(nullptr);
    }


    // 由于为了实现 map 的 operator[] 那么必修修改一下原来的 Insert 的返回值
    // operator[] 的功能：1.查找，插入  2.查找，修改(查找过程已经渗透到了插入过程中)
    // 如果只返回一个 bool 值是无法完成这一点的，因此上需要返回某个位置的迭代器
    pair<iterator, bool> Insert(const V& val)
    {
      // 创建新的结点
      Node* newnode = new Node(val);

      if(_root == nullptr)
      {
        _root = newnode;
        _root->_col = BLACK;
        return make_pair(iterator(newnode), true);
      }

      // 用来比较的仿函数对象
      KeyOfVal kov;

      Node* par = nullptr;
      Node* cur = _root;
      while(cur)
      {
        // 这里的比较需要仿函数来完成 ，因为我们也不知道传进来的是什么，不同的类型最后返回不同的值，返回之后再进行比较
        // if(cur->_kv.first > kv.first)
        if(kov(cur->_val) > kov(val))
        {
          par = cur;
          cur = cur->_left;
        }
        else if(kov(cur->_val) < kov(val))
        {
          par = cur;
          cur = cur->_right;
        }
        else 
        {
          // 已经存在，那么还是要返回原来地方的迭代器
          return make_pair(iterator(cur), false);
        }
      }

      // 位置找到，链接指针
      cur = newnode;
      if(kov(cur->_val) < kov(par->_val))
      {
        par->_left = cur;
        cur->_parent = par;
      }
      else 
      {
        par->_right = cur;
        cur->_parent = par;
      }

      // 控色
      // 控色的情况有三种，分别是：
      // 1.cur 为红色，par 为红色，ppar 为黑色，u 为红色
      // 2.cur 为红色，par 为红色，ppar 为黑色，u 为黑色/不存在(cur par ppar 为斜线)
      // 3.cur 为红色，par 为红色，ppar 为黑色，u 为黑色/不存在(cur par ppar 为折线)
     
      // 调色条件：
      // par存在且为红色
      while(par && par->_col == RED)
      {
        Node* ppar = par->_parent;

        if(ppar && ppar->_left == par)
        {
          Node* u = ppar->_right;
          // 情况1
          if(u && u->_col == RED)
          {
            ppar->_col = RED;
            par->_col = u->_col = BLACK;

            // 持续调色
            cur = ppar;
            par = cur->_parent;
            continue;
          }

          // 情况2 / 3：
          if(u == nullptr || (u && u->_col == BLACK))
          {
            // 先将情况 3 转化为情况 2
            if(par && par->_right == cur)
            {
              RotateL(par);
              swap(par, cur);
            }

            // 处理情况 2
            RotateR(ppar);
            par->_col = BLACK;
            ppar->_col = RED;

            break;
          }

        }
        else if(ppar && ppar->_right == par)
        {
          Node* u = ppar->_left;
          // 情况1
          if(u && u->_col == RED)
          {
            ppar->_col = RED;
            par->_col = u->_col = BLACK;

            // 持续调色
            cur = ppar;
            par = cur->_parent;
            continue;
          }

          // 情况2 / 3：
          if(u == nullptr || (u && u->_col == BLACK))
          {
            // 先将情况 3 转化为情况 2
            if(par && par->_left == cur)
            {
              RotateR(par);
              swap(par, cur);
            }

            // 处理情况 2
            RotateL(ppar);
            par->_col = BLACK;
            ppar->_col = RED;

            break;
          }
        }
      }

      _root->_col = BLACK;

      // 还是返回新建结点的地址(迭代器)
      return make_pair(iterator(newnode), true);
    }

    void RotateL(Node* par)
    {
      Node* subR = par->_right;
      Node* subRL = subR->_left;

      // 先解决掉 par 的所有链
      par->_right = subR->_left;
      if(subRL)
        subRL->_parent = par;
      Node* ppar = par->_parent;
      par->_parent = subR;

      // 再解决掉 subR 的所有链
      subR->_left = par;
      subR->_parent = ppar;

      if(ppar == nullptr)
      {
        _root = subR;
      }
      else 
      {
        if(par == ppar->_left)
        {
          ppar->_left = subR;
        }
        else 
        {
          ppar->_right = subR;
        }
      }

    }

    void RotateR(Node* par)
    {
      Node* subL = par->_left;
      Node* subLR = subL->_right;

      // 先解决掉 par 的所有链
      par->_left = subL->_right;
      if(subLR)
        subLR->_parent = par;
      Node* ppar = par->_parent;
      par->_parent = subL;

      // 再解决掉 subL 的所有链
      subL->_right = par;
      subL->_parent = ppar;

      if(ppar == nullptr)
      {
        _root = subL;
      }
      else 
      {
        if(ppar->_left == par)
        {
          ppar->_left = subL;
        }
        else 
        {
          ppar->_right = subL;
        }
      }

    }

    bool IsRBTree()
    {
      // 获取到根节点
      Node* root = _root;

      if(root == nullptr)
      {
        return true;
      }


      if(BLACK != root->_col)
      {
        cout << "错误：红黑树根节点为黑色" << endl;
        return false;
      }

      // 统计任意一条路径的黑结点数量(以左子树为例)
      size_t blackcout = 0;
      Node* cur = root;
      while(cur)
      {
        if(cur->_col == BLACK)
        {
          blackcout++;
        }

        cur = cur->_left;
      }

      // 检测红黑树的结点与颜色性质
      size_t k = 0;
      return _isRBTree(root, k, blackcout);
    }


    void Inorder()
    {
      inorder(_root);
    }

  private:

    void inorder(Node* root)
    {
      if(root == nullptr)
      {
        return ;
      }

      inorder(root->_left);
      cout << root->_kv.first << endl;
      inorder(root->_right);

      return ;
    }

    bool _isRBTree(Node* root, size_t k, size_t blackcout)
    {
      if(root == nullptr)
      {
        if(k != blackcout)
        {
          cout << "错误：每条路径黑色结点数目相同" << endl;
          return false;
        }
        return true;
      }

      // 统计黑色结点
      if(root->_col == BLACK)
      {
        k++;
      }

      // 检测是否有连续的红色结点出现
      Node* par = root->_parent;
      if(par && par->_col == RED && root->_col == RED)
      {
        cout << "错误：有连续的红色结点出现" << endl;
        return false;
      }

      // 判断当前树的左子树和右子树是否为红黑树
      return _isRBTree(root->_left, k, blackcout) && _isRBTree(root->_right, k, blackcout);

    }

    void Destroy(Node* root)
    {
      if(root == nullptr)
      {
        return ;
      }

      Destroy(root->_left);
      Destroy(root->_right);
      delete root;

      return;
    }

    Node* _root;
};
