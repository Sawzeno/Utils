#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#include  "list.h"

Node* initNode(){
  Node* node  = malloc(sizeof(Node));
  ISNULL(node)
  node->string  = NULL;
  node->next    = NULL;
  return node;
}

Node* createNode(const char* string){
  ISNULL(string);
  Node* node  = initNode();

  node->string  = malloc(sizeof(char) * strlen(string));
  ISNULL(node->string);

  strcpy(node->string , string);
  
  return node;
}

Node* editNode(Node* node , const char* string){
    ISNULL(node);
    ISNULL(string);
  
    free(node->string);
    node->string  = malloc(sizeof(char) * strlen(string));

    strcpy(node->string, string);

    return node;
}

Node* addNode(List* list , const char* string){
  ISNULL(list)
  ISNULL(string)

  Node* node  = createNode(string);

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

Node* insertNextNode(List* list , Node* node , const char* string){

  ISNULL(list)
  ISNULL(node)
  ISNULL(string)

  Node* next  = createNode(string);
  Node* temp  = node->next;
  node->next  = next;
  next->next  = temp;

  ++list->size;
  return next;
}

Node* deleteNextNode(List* list , Node* prev){
  ISNULL(list)
  ISNULL(prev)
  ISNULL(prev->next)

  Node* node  = prev->next;
  Node* temp  = node->next;

  free(node->string);
  free(node);

  prev->next  = temp;
  --list->size;

  return prev;
}

Node* getNode(List* list , int index){

  ISNULL(list)
  ISINVAL(index , > , list->size)
  ISINVAL(index , == , 0)

  int i = 1;
  Node* temp = list->head;

  while(i < index){
    temp  = temp->next;
    ++i;
  }

  return temp;
}


List* initList(){

  List* list  = malloc(sizeof(List));
  ISNULL(list)

  list->head  = NULL;
  list->tail  = NULL;
  list->size  = 0;
  return list;
}

List* createList(int size){

  ISINVAL(size, ==, 0)
  List* list  = initList();
  list->size  = size;
  list->head  = initNode();
  Node* temp  = list->head;
  int i = 1;

  while(i < list->size){
    temp->next  = initNode();
    temp  = temp->next;
    ++i;
  }

  list->tail =  temp;
  return list;
}

List* splitList(List* list , int index){
  ISNULL(list);
  ISINVAL(index, >= , list->size)

  List* newlist = initList();
  Node* node  = getNode(list, index);
  
  newlist->size = list->size - index;
  newlist->head = node->next;
  newlist->tail = list->tail;

  node->next  = NULL;
  list->tail  = node;
  list->size  = index;

  return newlist;
}

int shrinkList(List* list , int size){
  ISINVAL(size, >=, list->size)

  Node* node  = getNode(list , size);
  list->tail  = node;

  node  = node->next;
  Node* temp;
  int i = 0;
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

int  printList(List* list){
 
  ISNULL(list)
  
  Node* head  = list->head;
  printf("SIZE  : %d\n" , list->size);
  int i = 1;
  while(head  != NULL){
    printf("%d  : %s\n" ,i,head->string);
    head  = head->next;
    ++i;
  }

  return i;
}

int freeList(List* list){

  ISNULL(list)
  Node* temp  = list->head;
  Node* next;
  
  int numNodes = 0;
  while(temp != NULL){
    numNodes++;
    temp  = temp->next;
  }
  if(numNodes  !=  list->size){
    ISINVAL(numNodes , != , list->size)
  }

  temp  = list->head;

  int numDeleted = 0;
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

  printf("NUMDELETED  : %d\n" , numDeleted);
  return numDeleted;
}


