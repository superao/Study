// 二叉查找树:动态查找表.

#include <stdio.h>
#include <stdlib.h>


// 树中每个结点的结构.
typedef struct Node{

  int val;
  struct Node* left;
  struct Node* right;
} BiNode;

// 查找指定元素(递归写法)
BiNode* BST_Find(BiNode* root, int v) {

  // 如果为空树,那么直接返回NULL.
  if(root == NULL) {

    return NULL;
  }

  // 如果根节点为所查找的值,那么直接返回根节点的地址
  if(root->val == v) {

    return root;
  }

  // 递归的去子树查找。
  else if(root->val > v) {
    
    // 如果所查找的值小于根节点的值,那么就去左子树进行查找,如果找到了一路返回到最上层。
    return BST_Find(root->left, v);
  }
  else {

    // 反之,就去右子树进行查找,如果找到了一路返回到最上层。
    return BST_Find(root->right, v);
  }
}

// 查找指定元素(循环写法)
BiNode* BST_find(BiNode* root, int v) {

  // 如果不为空树,并且根节点的值不是所查找的值,那么就参与循环
  while(root && root->val != v) {

    // 如果小于根节点那么就去左子树
    if(root->val > v) {

      root = root->left;
    }
    else if(root->val < v) {

      // 如果大于根节点那么就去右子树
      root = root->right;
    } 
  }

  // 当循环出来时,有两种情况:
  // 1.root 为空(NULL),要不该树是空树,要不在该树中没有找到该元素.
  // 2.root->val 就是所要查找的值,那么返回该地址
  return root;
}


// 寻找树中的最大值(递归写法)
BiNode* Find_Max(BiNode* root) {

  // 如果为空树,直接返回 NULL.
  if(root == NULL) {

    return NULL;
  }

  // 不是空树,一直递归到最右边,直到为空.
  if(root->right != NULL) {

    // 这样的话,保证了下一层返回到上一层又会继续返回,从而达到了返回的是一个相同的地址.
    return Find_Max(root->right);
  }
  else {

    return root;
  }
}


// 寻找树中的最大值(循环写法)
BiNode* Find_Max1(BiNode* root) {

  // 如果不为空树,参与循环
  if(root != NULL) {

    // 如果根节点的右子树不为空,那么一直向右走,直到走到右结点为空,那么此时根节点的所在的值就是该树的最大值
    while(root->right != NULL) {

      root = root->right;
    }
  }
  else {

    return NULL;
  }

  return root;
}


// 插入某个元素,返回根节点的地址
// 注意一点:当我们在插入的时候,最后一定找到的是叶子结点,我们在插入的过程中只要满足BST树的性质即可。
BiNode* BST_Insert(BiNode* root, int v) {

  // 如果为空树,那么就直接插入到根节点上
  if(root == NULL) {

    // 申请一个结点用来储存数据
    root = (BiNode*)malloc(sizeof(BiNode));
    root->val = v;
    root->left = root->right = NULL;
  }
  // 如果不是空树比较大小,找到合适的位置,插入元素,并且链接下一层与上一层.
  else if(root->val > v) {

    root->left = BST_Insert(root->left,v);
  }
  else if(root->val < v) {

    root->right = BST_Insert(root->right, v);
  }
  else 
    printf("插入失败,元素已经存在\n");

  return root;
}



// 删除某个元素,返回根节点的地址。
BiNode* Bst_Delete(BiNode* root, int v) {

  BiNode* Tem = NULL;

  // 如果为空树,那么该元素不存在,删除失败
  if(root == NULL) {

    printf("该元素不存在,删除失败\n");
  }
  // 递归删除某个结点
  // 思路:先递归找到该节点所在的位置,然后分情况再进行删除。
  // 递归查找过程如下:从根节点一步一步的递归将树“放小”,直到递归到它自己本身即可。
  else if(root->val > v) {

    // 左子树中进行递归
    root->left = Bst_Delete(root->left, v);
  }
  else if(root->val < v) {

    // 右子树中进行递归
    root->right = Bst_Delete(root->right, v);
  }


  // 已经递归到了该元素本身,进行删除.
  else {

    // 如果该元素有左右子树,则
    if(root->left != NULL && root->right != NULL) {

      Tem = Find_Max1(root->left);
      root->val = Tem->val;
      root->left = Bst_Delete(root->left, Tem->val);
    }

    // 只有一颗子树或者没有子树。
    else{

      // 方便释放空间
      Tem = root;

      // 如果只有右子树
      if(root->left == NULL) {

        root = root->right;
      }
      // 如果只有左子树
      else if(root->right == NULL) {

        root = root->left;
      }

      // 没有子树,直接释放空间。
      // 释放空间
      free(Tem);
    }
  }

  return root;
}

// 利用数组来构建一颗BST树.
BiNode* Creat_BST(int arry[], int size) {

  // 首先,利用数组首元素先创建一颗树,然后用数组其他元素来逐渐的来把该颗构建完整.
  BiNode* root = (BiNode*)malloc(sizeof(BiNode));
  root->val = arry[0];
  root->left = root->right = NULL;


  int i = 1;
  for(i = 1; i < size; i++) {

    BST_Insert(root, arry[i]);
  }

  return root;
}


// 树的中序遍历
void Bst_Traver(BiNode* root) {

  if(root == NULL) {

    return ;
  }

  Bst_Traver(root->left);
  printf("%d\t", root->val);
  Bst_Traver(root->right);
}


int main() {

  int arry[] = {6,2,5,1,7,8,23,0,12,14,456};
  int size = sizeof(arry) / sizeof(int);

  BiNode* root = Creat_BST(arry,size);

  Bst_Traver(root);

  printf("\n");

  BST_Insert(root, 1000);
 

  Bst_Traver(root);


  // 创建一个临时变量,方便读取该地址的值。
  BiNode* t = BST_find(root,0);
  printf("======%d======",t->val);

  printf("\n");
  return 0;
}
