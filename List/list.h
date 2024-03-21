#pragma once

#include<stdint.h>
#include<stdbool.h>

#include"../Log/log.h"

#define U64 uint64_t

typedef struct ListNode ListNode;
typedef struct List List;
typedef struct ListInfo ListInfo;

struct ListNode{
  void*     item;
  ListNode* next;
};

struct ListInfo{
  void* (*createInfo) (void*);
  void  (*debugInfo)  (void*);
};

struct List{
  ListNode* head;
  ListNode* tail;
  ListInfo  info;
  U64       size;
};

ListNode* createListNode  (ListInfo info , void* item);
ListNode* addListNode     (List*  list , void* item);
ListNode* getListNode     (List*  list ,U64 index);
List* initList    (ListInfo info);
List* createList  (ListInfo info , U64 size);
List* splitList   (List*  list , U64 index);
bool  validList   (List*  list);
U64   freeItems   (List*  list);
U64   shrinkList  (List*  list , U64 index);
