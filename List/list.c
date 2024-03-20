#include  <stdlib.h>
#include  <stdio.h>
#include  <stdbool.h>
#include  <unistd.h>
#include  "list.h"


Node* createNode(ListInfo info , void* item){
  
  ISNULL(&info)
  Node* node =  malloc(sizeof(Node));
  MEMERR(node);
  
  node->item  = info.createInfo(item);
  node->next  = NULL;

  return node;
}

Node* getNode(List* list, U64 index){
  ISNULL(list)
  if(index >= list->size || index < 0 ){
    LOG_WARNING("invalid index")
    return NULL;
  }

  U64 i = 1;
  Node* temp = list->head;
  while(i < index && temp != NULL){
    temp = temp->next;
    ++i;
  }

  return temp;
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
  list->head = createNode(info, NULL);

  Node* temp = list->head;
  for (U64 i = 1; i < list->size; ++i) {
    temp->next = createNode(info , NULL);
    temp = temp->next;
  }

  list->tail = temp;
  return list;
}

bool debugList(List* list) {
  ISNULL(list)

  Node* temp = list->head;
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

Node* addNode(List* list , void* item){
  ISNULL(list)

  Node* node  = createNode(list->info , item);

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


U64 freeItems(List* list) {
  ISNULL(list)

  if (debugList(list) == false) {
    LOG_WARNING("INVALID LIST")
    return 0;
  }

  U64 count = 0;
  Node* temp = list->head;
  Node* next;
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
  
  if(index  >= list->size){
    LOG_WARNING("index greater than size")
    return 0;
  }
  Node* node  = getNode(list , index);
  list->tail  = node;

  node  = node->next;
  Node* temp;
  uint64_t i = 0;
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
