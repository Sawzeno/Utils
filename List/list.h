#pragma once

#include  <stdarg.h>
#include  <stdint.h>
#include  <stdbool.h>

#include"../Log/log.h"


typedef struct ListNode ListNode;
typedef struct List List;
typedef struct ListInfo ListInfo;

struct ListNode{
  void*     item;
  ListNode* next;
};

struct ListInfo{
  void* (*createItemInfo) (void* , va_list args);
  void (*debugItemInfo)  (void*);
};

struct List{
  ListNode* head;
  ListNode* tail;
  ListInfo*  info;
  U64       size;
};

List*     initList        (ListInfo* info );
List*     createList      (ListInfo* info , U64 size    , ... );
ListNode* createListNode  (ListInfo* info , void* item  , va_list args  );
ListNode* addListNode     (List*    list  , void* item  , va_list args  );
ListNode* getListNode     (List*    list  , U64 index );

List*     splitList       (List*  list , U64 index);
U64       shrinkList      (List*  list , U64 index);
bool      debugList       (List*  list);
U64       freeItems       (List*  list);
