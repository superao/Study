// 删除链表中所有的 v 值。
// 尾插法 --> 尾插到结果链表中

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {

  int val;
  struct ListNode *next;
};

// 申请结点
struct ListNode* Buy(int x) {

  struct ListNode* a = (struct ListNode*)malloc(sizeof(struct ListNode));
  a->next = NULL;
  a->val = x;

  return a;
}


struct ListNode* removeElements(struct ListNode* head, int val) {

  // 创建一个结果链表
  struct ListNode* result = NULL;
  
  // 保存结果链表最后一个结点
  struct ListNode* last = NULL;

  // 保存头结点
  struct ListNode* cur = head;

  // 进行循环
  for(cur; cur != NULL; cur = cur->next) {

    // 如果不是 v 就将它尾插到结果链表上。
    if(cur->val != val) {

      // 尾插到结果链表上
      if(result == NULL && last == NULL) {

        result = cur;
        last = cur;
      }
      else{

        last->next = cur;
        last = last->next;
      }
   }
}

  // 例如: 1 -> 2 -> 2 -> 3 -> 2; 删除 2 结点。
  // 尾插完成后,原链表中有可能最后一个元素是 V ,它虽然没有进入条件语句,没有尾插到结果链表中,
  // 但是,由于原来链表就链接着它,所以尾插完成后,需要置空,从而切断原来链表的相连关系.
if(last != NULL) {

  last->next = NULL;
}

  return result;
}

// 测试
void Text() {

  // 创建一个链表
  struct ListNode* head = Buy(1);
  struct ListNode* b = Buy(2); 
  struct ListNode* c = Buy(2);
  struct ListNode* d = Buy(3);
  struct ListNode* e = Buy(2);
 
  head->next = b;
  b->next = c;
  c->next = d;
  d->next = e;
  e->next = NULL;

  struct ListNode* cur = head;
  for(cur; cur != NULL; cur = cur->next) {

    printf("%d\t",cur->val);
  }

  printf("\n");

  cur = removeElements(head,2);
  for(cur; cur != NULL; cur = cur->next) {

    printf("%d\t",cur->val);
  }
  


  printf("\n");
}

int main () {

  Text();

  return 0;
}
