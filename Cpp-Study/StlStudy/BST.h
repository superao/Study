#include <iostream>
using namespace std;

// 实现以下功能:
// 1.插入
// 2.删除
// 3.查找


// 类模板
template<class K>
class BSTreeNode
{
  public:
    BSTreeNode(const K& key = K()) :_key(key), _left(nullptr), _right(nullptr) {}

    K _key;
    BSTreeNode<K>* _left;    // 类模板指针
    BSTreeNode<K>* _right;   // 类模板指针
};



template<class K>
class BSTree 
{
  // 必须写在类中，否则 Node 无法知道 K 是什么类型
  typedef BSTreeNode<K> Node;

  public:
    // 构造函数，构造出一颗树
    BSTree(Node* root = nullptr) :_root(root) {}

    ~BSTree()
    {
      Destory(_root);
    }

    // 插入
    // 空树:直接插入到根节点
    // 非空树:
    // 1.从根结点开始比较大小
    // 2.大的往右边走，小的往左边走
    // 3.找到自己位置后，将该位置与父节点相链接
    bool Insert(const K& key)
    {

      // 新的结点
      Node* newnode = new Node(key);

      // 空树
      if(_root == nullptr)
      {
        // 申请新节点，放入数据。
        _root = newnode;
        return true;
      }
      // 非空树
      else 
      {
        Node* par = nullptr;
        Node* cur = _root;
        while(cur)
        {
          if(cur->_key < key)
          {
            par = cur;
            cur = cur->_right;
          }
          else if(cur->_key > key)
          {
            par = cur;
            cur = cur->_left;
          }
          else 
          {
            // 已经存在，插入失败
            return false;
          }
        }
        
        if(key > par->_key)
        { 
          cur = newnode;
          par->_right = cur;
        }
        else 
        {
          cur = newnode;
          par->_left = cur;
        }

        return true;
      }
      
      return false;
    }


    // 查找:
    // 1.从根结点一直向下走，直到找到对应的结点
    Node* Find(const K& key)
    {
      Node* cur = _root;
      while(cur != nullptr && cur->_key != key)
      {
        if(cur->_key > key)
        {
          cur = cur->_left;
        }
        else if(cur->_key < key)
        {
          cur = cur->_right;
        }
      }

      if(cur == nullptr)
      {
        return nullptr;
      }
      else 
      {
        return cur;
      }
    }


    // 删除 ***
    // 分三种情况进行删除
    // 1.叶子结点和带有一个孩子的结点一起处理
    // 2.带有两个孩子的结点
    void Erase(const K& key)
    {

      Node* del = nullptr;

      // 查找它
      Node* par = nullptr;
      Node* cur = _root;
      while(cur != nullptr && cur->_key != key)
      {
        if(cur->_key > key)
        {
          par = cur;
          cur = cur->_left;
        }
        else if(cur->_key < key)
        {
          par = cur;
          cur = cur->_right;
        }
      }

      // 空树或者没有找到，直接退出
      if(cur == nullptr)
      {
        return ;
      }
      // 找到了
      else 
      {
        del = cur;
      }

      // 情况一:
      if(cur->_right == nullptr)
      {
        if(cur == _root)
        {
          _root = cur->_left;
        }
        else 
        {
          if(cur == par->_left)
          {
            par->_left = cur->_left;
          }
          else if(cur == par->_right)
          {
            par->_right = cur->_left;
          }
        }
      }
      else if(cur->_left == nullptr)
      {
        if(cur == _root)
        {
          _root = cur->_right;
        }
        else 
        {
          if(cur == par->_left)
          {
            par->_left = cur->_right;
          }
          else if(cur == par->_right)
          {
            par->_right = cur->_right;
          }
        }
      }

      // 情况二:
      if(cur->_left != nullptr && cur->_right != nullptr)
      {
        Node* re = cur->_right;
        Node* p = cur;
        while(re && re->_left)
        {
          p = re;
          re = re->_left;
        }

        cur->_key = re->_key;

        if(re == p->_right)
        {
          p->_right = re->_right;
        }
        else if(re == p->_left)
        {
          p->_left = re->_right;
        }

        del = re;

      }

      delete del;
      return ;
    }


    // 中序遍历
    void InOrder()
    {
      // 递归需要封装一层，否则无法调用到私有成员
      inorder(_root);
    }


  private:
    void Destory(Node* root)
    {
      // 空树直接返回
      if(root == nullptr)
      {
        return ;
      }

      // 先释放它的左子树
      Destory(root->_left);
      // 再释放它的右子树
      Destory(root->_right);
      // 再释放自己
      delete root;

      return ;
    }

    void inorder(Node* root)
    {
      if(root == nullptr)
      {
        return;
      }

      inorder(root->_left);
      cout << root->_key << endl;
      inorder(root->_right);

      return;
    }

  // 一颗树只需要有它的根就行
  private:
    Node* _root;
};
