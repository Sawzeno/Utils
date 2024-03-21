#include  <stdio.h>
#include  <stdlib.h>
#include  <stdbool.h>

#include  "list.h"

ListNode* createListNode(ListInfo info , void* item){

  ISNULL(&info)
    ListNode* node =  malloc(sizeof(ListNode));
  MEMERR(node);

  node->item  = info.createInfo(item);
  node->next  = NULL;

  return node;
}

ListNode* getListNode(List* list, U64 index) {
  ISNULL(list)

  if (index > list->size || index < 1) {
    LOG_WARNING("Invalid index")
    return NULL;
  }

  U64 i = 1;
  ListNode* temp = list->head;
  while (i < index && temp != NULL) {
    temp = temp->next;
    ++i;
  }

  return temp;
}

ListNode* addListNode(List* list , void* item){
  ISNULL(list)

  ListNode* node  = createListNode(list->info , item);

  if(list->head == NULL){
    list->head  = node;
    list->tail  = list->head;
  }else{
    list->tail->next  = node;
    list->tail  = node;
  }

  ++list->size;
  return list->tail;
}

List* initList(ListInfo info) {
  List* list = malloc(sizeof(List));
  MEMERR(list)
  list->head = NULL;
  list->tail = NULL;
  list->info = info;
  list->size = 0;

  return list;
}

List* createList(ListInfo info, U64 size) {
  ISNULL(&info)
  List* list = initList(info);
  if (size == 0) {
    return list;
  }

  list->size = size;
  list->head = createListNode(info, NULL);

  ListNode* temp = list->head;
  for (U64 i = 1; i < list->size; ++i) {
    temp->next = createListNode(info , NULL);
    temp = temp->next;
  }

  list->tail = temp;
  return list;
}

bool validList(List* list ) {
  ISNULL(list)

  ListNode* temp = list->head;
  U64 count = 0;

  while (temp != NULL) {
    ++count;

    if(temp->item == NULL){
      LOG_WARNING("ITEM EMPTY");
    }else{
      list->info.debugInfo(temp->item);
    }

    temp = temp->next;
  }

  if (count == list->size) {
    return true;
  } else {
    return false;
  }
}

U64 freeItems(List* list) {
  ISNULL(list)

  if (validList(list) == false) {
    LOG_WARNING("INVALID LIST")
    return 0;
  }

  U64 count = 0;
  ListNode* temp = list->head;
  ListNode* next;
  while (temp != NULL) {
    next = temp->next;
    next  = NULL;
    temp = next;
    ++count;
  }

  list->size -= count;
  list->head = NULL;
  list->tail = NULL;

  return count;
}

U64 shrinkList  (List*  list , U64 index){

  if (validList(list) == false) {
    LOG_WARNING("INVALID LIST")
    return 0;
  }

  if(index  >= list->size){
    LOG_WARNING("index greater than size")
    return 0;
  }

  ListNode* node = getListNode(list, index);
  if (!node) {
    LOG_WARNING("ListNode not found at index")
    return 0;
  }
  list->tail  = node;

  node  = node->next;
  ListNode* temp;
  U64 i = 0;
  while(node  !=  NULL){
    temp  = node->next;
    free(node);
    node  = temp;
    ++i;
  }

  list->tail->next  = NULL;
  list->size -=i;

  return i;
}

List* splitList(List* list , U64 index){
  ISNULL(list);
  if(index  >= list->size){
    LOG_WARNING("index greater than size")
    return 0;
  }
  List* newlist = initList(list->info);
  ISNULL(newlist)

  ListNode* newListHead  = getListNode(list, index);
  ISNULL(newListHead)

  newlist->size = list->size - index;
  newlist->head = newListHead->next;
  newlist->tail = list->tail;

  newListHead->next  = NULL;
  list->tail  = newListHead;
  list->size  = index;

  return newlist;
}
