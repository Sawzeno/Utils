#include  <stdio.h>
#include  <inttypes.h>
#include  <stdlib.h>
#include  <string.h>

#include  "localString.h"

localString* initNode(){
  localString* node  = malloc(sizeof(localString));
  ISNULL(node)
  node->string  = NULL;
  node->next    = NULL;
  return node;
}

localString* createNode(const char* string){
  ISNULL(string);
  localString* node  = initNode();

  uint64_t size = strlen(string);
  node->string  = malloc(sizeof(char) * size + 1);
  ISNULL(node->string);
  node->string[size]  = '\0';
  strcpy(node->string , string);

  return node;
}

localString* editNode(localString* node , const char* string){
  ISNULL(node);
  ISNULL(string);

  free(node->string);
  uint64_t size = strlen(string);
  node->string  = malloc(sizeof(char) * size + 1);

  strcpy(node->string, string);
  node->string[size]  = '\0';
  return node;
}

localString* addNode(LSList* list , const char* string){
  ISNULL(list)
  ISNULL(string)

  localString* node  = createNode(string);

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

localString* insertNextNode(LSList* list , localString* node , const char* string){

  ISNULL(list)
  ISNULL(node)
  ISNULL(string)

  localString* next  = createNode(string);
  localString* temp  = node->next;
  node->next  = next;
  next->next  = temp;

  ++list->size;
  return next;
}

localString* deleteNextNode(LSList* list , localString* prev){
  ISNULL(list)
  ISNULL(prev)
  ISNULL(prev->next)

  localString* node  = prev->next;
  localString* temp  = node->next;

  free(node->string);
  free(node);

  prev->next  = temp;
  --list->size;

  return prev;
}

localString* getNode(LSList* list , uint64_t index){

  ISNULL(list)
  ISINVAL(index , > , list->size)
  ISINVAL(index , == , 0)

  uint64_t i = 1;
  localString* temp = list->head;

  while(i < index){
    temp  = temp->next;
    ++i;
  }

  return temp;
}

LSList* initLSList(){

  LSList* list  = malloc(sizeof(LSList));
  ISNULL(list)

  list->head  = NULL;
  list->tail  = NULL;
  list->size  = 0;
  return list;
}

LSList* createLSList(uint64_t size){

  ISINVAL(size, ==, 0)
  LSList* list  = initLSList();
  list->size  = size;
  list->head  = initNode();
  localString* temp  = list->head;
  uint64_t i = 1;

  while(i < list->size){
    temp->next  = initNode();
    temp  = temp->next;
    ++i;
  }

  list->tail =  temp;
  return list;
}

LSList* splitLSList(LSList* list , uint64_t index){
  ISNULL(list);
  ISINVAL(index, >= , list->size)

  LSList* newlist = initLSList();
  localString* node  = getNode(list, index);

  newlist->size = list->size - index;
  newlist->head = node->next;
  newlist->tail = list->tail;

  node->next  = NULL;
  list->tail  = node;
  list->size  = index;

  return newlist;
}

uint64_t shrinkLSList(LSList* list , uint64_t size){
  ISINVAL(size, >=, list->size)

  localString* node  = getNode(list , size);
  list->tail  = node;

  node  = node->next;
  localString* temp;
  uint64_t i = 0;
  while(node  !=  NULL){
    temp  = node->next;
    free(node->string);
    free(node);
    node  = temp;
    ++i;
  }

  list->tail->next  = NULL;
  list->size -=i;

  return i;
}

uint64_t  printLSList(LSList* list){

  ISNULL(list)

  localString* head  = list->head;
  printf("SIZE  : %"PRIu64"\n" , list->size);
  uint64_t count = 0;
  while(head  != NULL){
    ++count;
    printf("%"PRIu64"  : %s\n" ,count,head->string);
    head  = head->next;
  }

  return count;
}

uint64_t freeLSList(LSList* list){

  ISNULL(list)
  localString* temp  = list->head;
  localString* next;

  uint64_t numNodes = 0;
  while(temp != NULL){
    numNodes++;
    temp  = temp->next;
  }
  if(numNodes  !=  list->size){
    ISINVAL(numNodes , != , list->size)
  }

  temp  = list->head;

  uint64_t numDeleted = 0;
  while(temp  != NULL ){
    next  = temp->next;

    free(temp->string);
    free(temp);
    temp  = next;
    ++numDeleted;
  }

  list->size  -= numDeleted;
  list->head  = NULL;
  list->tail  = NULL;

  printf("NUMDELETED  : %"PRIu64"\n" , numDeleted);
  return numDeleted;
}


