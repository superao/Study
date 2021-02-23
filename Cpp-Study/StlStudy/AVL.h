#include <iostream>
#include <vector>
#include <map>
using namespace std;

// 树结点(Key / Value 模型)
template<class K, class V>
class AVLTreeNode
{
  public:
    // 初始化
    AVLTreeNode(const pair<K, V>& kv) :_kv(kv), _left(nullptr), _right(nullptr), _parent(nullptr), _bf(0) {}

    // 成员变量
    pair<K, V> _kv;           // 键值对(K/V模型)

    // 三叉链
    // 目的:为了方便寻找父节点,调节平衡因子
    AVLTreeNode<K, V>* _left;
    AVLTreeNode<K, V>* _right;
    AVLTreeNode<K, V>* _parent;

    // 平衡因子
    int _bf;
};


// 树结构
template<class K, class V>
class AVLTree 
{
  typedef AVLTreeNode<K, V> Node;
  public:
    // 初始化
    AVLTree(Node* root = nullptr) :_root(root) {}

    // 1.插入 + 2.旋转
    bool Insert(const pair<K, V>& kv)
    {
      Node* newnode = new Node(make_pair(kv.first, kv.second));
      // 空树
      if(_root == nullptr)
      {
        _root = newnode;
        return true;
      }

      // 非空树
      // 1.查找位置
      Node* par = nullptr;
      Node* cur = _root;
      while(cur)
      {
        // Key 进行比较
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
          // 已经存在
          return false;
        }
      }

      // 找到位置,插入结点,更新父节点平衡因子
      cur = newnode;
      if(par->_kv.first > kv.first)
      {
        par->_left = cur;
        cur->_parent = par;
        par->_bf--;
      }
      else 
      {
        par->_right = cur;
        cur->_parent = par;
        par->_bf++;
      }

      // 持续更新祖先平衡因子
      while(par->_bf)
      {
        if(abs(par->_bf) == 2)
        {
          // 停止更新,进行旋转
          break;
        }
        
        // 这里就是搞三叉链的目的
        // 如果父节点不为空，则继续向上更新
        // 如果父节点为空，则说明已经更新到了根节点直接退出
        if(par->_parent)
        {
          cur = par;
          par = par->_parent;
        }
        else 
        {
          break;
        }

        if(cur == par->_left)
        {
          par->_bf--;
        }
        else 
        {
          par->_bf++;
        }
      }
       
      // 平衡因子的绝对值为 2 时，进行旋转，
      if(abs(par->_bf) == 2)
      {
        // 进行旋转
        if(par->_bf == 2)
        {
          if(cur->_bf == 1)
          {
            RotateL(par);
          }
          else if(cur->_bf == -1)
          {
            RotateRL(par);
          }
        }
        else if(par->_bf == -2)
        {
          if(cur->_bf == 1)
          {
            RotateLR(par);
          }
          else if(cur->_bf == -1)
          {
            RotateR(par);
          }
        }
      }

      return true;
    }

    // 左单旋
    void RotateL(Node* parent)
    {
      Node* subR = parent->_right;
      Node* subRL = subR->_left;

      // 先处理subR的所有链
      subR->_left = parent;
      Node* pparent = parent->_parent;
      subR->_parent = pparent;

      // 再处理 par 的所有链
      parent->_parent = subR;
      parent->_right = subRL;
      // subRL 不为空，则父节点指向par
      if(subRL)
        subRL->_parent = parent;


      if(parent == _root)
      {
        _root = subR;
      }
      else 
      {
        if(pparent->_left == parent)
        {
          pparent->_left = subR;
        }
        else 
        {
          pparent->_right = subR;
        }
      }

      parent->_bf = subR->_bf = 0;
    }


    // 右单旋
    void RotateR(Node* parent)
    {
      Node* subL = parent->_left;
      Node* subLR = subL->_right;

      // 先处理 subL 的所有链
      subL->_right = parent;
      Node* pparent = parent->_parent;
      subL->_parent = pparent;

      // 再处理 par 的所有链
      parent->_parent = subL;
      parent->_left = subLR;
      if(subLR)
        subLR->_parent = parent;

      if(parent == _root)
      {
        _root = subL;
      }
      else 
      {
        if(pparent->_left == parent)
        {
          pparent->_left = subL;
        }
        else 
        {
          pparent->_right = subL;
        }
      }

      parent->_bf = subL->_bf = 0;
    }

    // 双旋 -- 先左后右
    void RotateLR(Node* parent)
    {
      Node* subL = parent->_left;
      Node* subLR = subL->_right;

      // 提前保存subLR的平衡因子
      int bf = subLR->_bf;

      // 先以subL为根左旋
      RotateL(subL);

      // 再以par为根右旋
      RotateR(parent);

      // 处理平衡因子带来的错误
      if(bf == 0)
      {
        subL->_bf = parent->_bf = 0;
      }
      else if(bf == 1)
      {
        parent->_bf = 0;
        subL->_bf = -1;
      }
      else if(bf == -1)
      {
        subL->_bf = 0;
        parent->_bf = 1;
      }
    }
    
    // 双旋 -- 先右后左
    void RotateRL(Node* parent)
    {
      Node* subR = parent->_right;
      Node* subRL = subR->_left;

      // 提前保存subRL的平衡因子
      int bf = subRL->_bf;

      // 先以subL为根进行右旋
      RotateR(subR);

      // 再以par为根进行左旋
      RotateL(parent);

      // 处理平衡因子带来的错误
      if(bf == 0)
      {
        subR->_bf = parent->_bf = 0;
      }
      else if(bf == 1)
      {
        subR->_bf = 0;
        parent->_bf = -1;
      }
      else if(bf == -1)
      {
        parent->_bf = 0;
        subR->_bf = 1;
      }
    }

    // 3.验证
    // 中序遍历
    void Inorder()
    {
      inorder(_root);
    }

    // 求树的高度
    int Hight()
    {
      return hight(_root);
    }

    // 判断是否为平衡树
    bool Isbalance()
    {
      return isbalance(_root);
    }
    

  private:

    bool isbalance(Node* root)
    {
      if(root == nullptr)
      {
        return true;
      }

      int lefthight = hight(root->_left);
      int righthight = hight(root->_right);

      if(root->_bf != righthight - lefthight)
      {
        cout << "平衡因子异常: " << root->_kv.first << endl;
        return false;
      }

      // 平衡树的三大要素:
      // 自身为平衡树
      // 左子树为平衡树
      // 右子树为平衡树
      return abs(lefthight - righthight) < 2
        && isbalance(root->_left)
        && isbalance(root->_right);
    }


    int hight(Node* root)
    {
      if(root == nullptr)
      {
        return 0;
      }

      int lefthight = hight(root->_left);
      int righthight = hight(root->_right);

      // 自身高度 = Max(left, right) + 1;
      return lefthight > righthight ? lefthight + 1 : righthight + 1;
    }

    void inorder(Node* root)
    {
      if(root == nullptr)
        return ;

      inorder(root->_left);
      cout << root->_kv.first << endl;
      inorder(root->_right);
    }


    Node* _root;
};
