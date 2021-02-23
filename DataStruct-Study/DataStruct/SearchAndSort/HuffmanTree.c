// 哈夫曼树操作:
// 1.构建哈夫曼树,将字符转化为哈夫曼编码。
// 2.对哈夫曼编码进行解码,从而转化为字符。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define leaf 8                      // 叶子结点(用它进行哈夫曼编码)
#define SUMNODE (2 * leaf - 1)      // 总叶子结点
#define Maxwight 10000              // 最大权值为:10000

// 哈夫曼树结点
typedef struct HuffmanTreeNode {

  int weight;        // 权值
  int leftchild;     // 左孩子下标
  int rightchild;    // 右孩子下标
  int partent;       // 父节点下标
  char ch;           // 需要编码的字符
} HuffmanTreeNode;

// 哈夫曼编码结构体
typedef struct {

  // 注:在定义结构的时候不能同时初始化成员变量,因为在定义的时候并未对他分匹配内存,
  // 初值是无法储存的,应该声明变量后,再进行手动赋值。

  char bit[8];       // 对单个字符进行的编码
  int start;         // 编码在位串中的起始位置
  char ch;           // 所编写的字符
}HuffmanTreeCode;


// 遍历哈夫曼数组,将最小的权值所在下标放到 min1 中,将倒数第二小的放到 min2 中。
void Selet_Min_Wight(HuffmanTreeNode arry[], int size, int* min1, int* min2) {

  // 先初始化两个下标。
  *min1 = *min2 = 0;

  // 假设最小的两个权值为 Maxwight 
  int Min_wight1 = Maxwight;
  int Min_wight2 = Maxwight;

  // 遍历数组,寻找数组中最小的权值所对应的两个下标。
  int i = 0;
  for(i = 0; i < size; i++) {

    // 由于在建立的哈夫曼树的时候,由叶子结点向树根进行建立,所以在查找的时候,只要查找叶子结点。
    if(arry[i].partent == -1) {

      if(arry[i].weight < Min_wight1) {

        // 如果该权值比倒数第一小,那么将倒数第一权值用它进行替换,
        // 并且,用倒数第一权值来替换倒数第二权值.
        Min_wight2 = Min_wight1;
        Min_wight1 = arry[i].weight;
        *min2 = *min1;
        *min1 = i;
      }

      // 如果该权值比倒数第二小的权值小,那么将倒数第二权值用它进行替换.
      else if(arry[i].weight < Min_wight2) {
  
        Min_wight2 = arry[i].weight;
        *min2 = i;
      }
    }
  }
}

// 建立哈夫曼树
void HuffmanTree(HuffmanTreeNode arry[]) {

  
  // 初始化哈夫曼数组
  int i = 0;
  for(i = 0; i < SUMNODE; i++) {

    // 将哈夫曼数组的叶子结点进行初始化
    arry[i].ch = '0';
    arry[i].leftchild = -1;
    arry[i].partent = -1;
    arry[i].rightchild = -1;
    arry[i].weight = Maxwight;
  }

  // 用户输入:
  printf("请输入需要编码的字符以及对应的权值:\n如:(A 30)\n");
  int j = 0;
  char ch = '0';
  int weight = 0;
  for(j = 0; j < leaf; j++) {

    scanf("%c %d",&ch,&weight);

    // 读取缓冲区的残留空格。
    getchar();

    arry[j].ch = ch;
    arry[j].weight = weight;

  }

  // 构建哈夫曼树
  // 由于构建树的时候,由叶子结点向上进行构建,所以只需要构建出根来,最后再将叶子结点链接起来即可。
  int k = leaf;
  for(k = leaf; k < SUMNODE; k++){

    // 先选择出叶子结点中权值最小的两个结点
    int min1 = 0;
    int min2 = 0;
    Selet_Min_Wight(arry,k,&min1,&min2);
    
    // 将两个较小的权值,组成一个根结点
    arry[min1].partent = k;
    arry[min2].partent = k;

    // 根结点链接子节点
    arry[k].leftchild = min1;
    arry[k].rightchild = min2;
    arry[k].weight = arry[min1].weight + arry[min2].weight;
  }

}


void HuffmanCode(HuffmanTreeCode code[], HuffmanTreeNode node[]) {


  // 在进行编码前,先建立好哈夫曼树,再对每个叶子结点字符进行编码。
  HuffmanTree(node);

  // 不用创建临时变量,将所有的编码,边建立,边存放,主要搞清楚所有的每个结构体是干什么用的即可。


  // 对于每个叶子结点进行哈夫曼编码,将每个编码放置到一个结构体中。
  int i = 0;
  for(i = 0; i < leaf; i++) {

    // 用来保存子节点的下标。
    int c = i;

    code[i].ch = node[i].ch;

    // 由于上面利用 8 个字节位来储存编码,并且在编码的过程中是由底向上进行编码,所以
    // 将开始位置置为 8 。
    code[i].start = 8;

    // 用来保存父节点的位置。
    int p = 0;
    p = node[i].partent;
    while(p != -1) {

      code[i].start--;
      if(node[p].leftchild == c) {

        // 说明该叶子结点就是左子树
        code[i].bit[code[i].start] = '0';
      }
      else if(node[p].rightchild == c) {

        // 说明该叶子结点就是右子树
        code[i].bit[code[i].start] = '1';
      }

      // 更改子节点的下标
      c = p;

      // 更改父节点的位置
      p = node[p].partent;
    }

  }

}


// 对哈夫曼编码进行解码
void HuffmanCodeDele(HuffmanTreeCode code[], HuffmanTreeNode node[]) {

  printf("解码如下:");
  // 对每一个编码字符数组进行从根到叶子结点的搜素。
  int i = 0;
  for(i = 0; i < leaf; i++) {

    // 从根部向叶子结点进行搜素,直到没有子节点。
    // 只保存树的各个结点的下标即可。
    int root = SUMNODE - 1;
    for(root; (node[root].leftchild != -1 && node[root].rightchild != -1); ) {

      // 保存字符编码数组开始位置
      int j = code[i].start;
      for(j; j < 8; j++) {

        // 从字符开始位置进行遍历,直到达到字符数组尾部
        if(code[i].bit[j] == '0') {

          // 走向左子树
          root = node[root].leftchild;
        }
        else if(code[i].bit[j] == '1') {

          // 走向右子树
          root = node[root].rightchild;
        }

      }

    }

    // 到达了叶子结点,找到了该字符,输出.
    printf("%c \t",node[root].ch);

  }

  printf("\n");
}
int main () {

  // 由于结点结构体要保存所有的结点(叶子节点 + 各个根结点),所以创建 SUMNODE 这么大
  HuffmanTreeNode node[SUMNODE];
  
  // 只需要保存叶子结点的编码即可.
  HuffmanTreeCode code[leaf];
  HuffmanCode(code,node);
  int j = 0;
  for(j = 0; j < leaf; j++) {

    printf("第 %d 个字符 %c 的编码为 ",j + 1, code[j].ch);
    
    int k = code[j].start;    // 保存了每个字符编码的起始位置
    for(k; k < 8; k++) {

      printf("%c",code[j].bit[k]);
    }

    printf("\n");
  }

  // 进行解码:
  HuffmanCodeDele(code,node);

  return 0;
}
