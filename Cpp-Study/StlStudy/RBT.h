#include <iostream>
#include <map>
using namespace std;

typedef enum color {RED, BLACK} color;

template <class K, class V>
class RBTreeNode
{
  public:
    RBTreeNode(const pair<K,V>& kv) :_kv(kv), _left(nullptr), _right(nullptr), _parent(nullptr),
    _col(RED) {}            // 注：新插入结点的颜色必须为红色，因为每条路径的黑色结点数目是相同的
                            // 如果新插入黑色，那么会影响每条路径的黑色数目，而新插入红色结点，影响较小
    pair<K, V> _kv;

    RBTreeNode<K,V>* _left;
    RBTreeNode<K,V>* _right;
    RBTreeNode<K,V>* _parent;

    color _col;             // 利用颜色来进行控制近似平衡
};

template <class K, class V>
class RBTree
{
  typedef RBTreeNode<K, V> Node;
  public:
    RBTree(Node* root = nullptr) :_root(root) {}
    ~RBTree() { Destroy(_root); }


    bool Insert(const pair<K, V>& kv)
    {
      // 创建新的结点
      Node* newnode = new Node(kv);

      if(_root == nullptr)
      {
        _root = newnode;
        _root->_col = BLACK;
        return true;
      }

      Node* par = nullptr;
      Node* cur = _root;
      while(cur)
      {
        if(cur->_kv.first > kv.first)
        {
          par = cur;
          cur = cur->_left;
        }
        else if(cur->_kv.first < kv.first)
        {
          par = cur;
          cur = cur->_right;
        }
        else 
        {
          return false;
        }
      }

      // 位置找到，链接指针
      cur = newnode;
      if(cur->_kv.first < par->_kv.first)
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
      return true;
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
