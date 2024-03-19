#pragma once

#define ISNULL(X)  if(X ==  NULL){       \
  fprintf(stderr,"ERROR : %s is NULL in %s at %d!\n",#X,__FUNCTION__, __LINE__);  \
  exit(EXIT_FAILURE);            \
}\

#define ISINVAL(X,Y,Z) if(X Y Z){  \
  fprintf(stderr,"ERROR : %s %s %s in %s at %d!\n",#X,#Y,#Z,__FUNCTION__, __LINE__);\
  return 0;\
}\

typedef struct Node   Node;
typedef struct List   List;


struct Node{
  char* string;
  Node* next;
};

struct List{
  Node* head;
  Node* tail;
  int   size;
};

Node*   initNode      ();
Node*   createNode    (const char* string);
Node*   addNode       (List* list , const char* string);
Node*   editNode      (Node* node , const char* string);
Node*   insertNextNode(List* list , Node* node,const char* string);
Node*   getNode       (List* list , int index);
Node*   deleteNextNode(List* list , Node* node);
List*   initList    ();
List*   createList  (int size);
List*   splitList   (List* list , int index);
int     shrinkList  (List* list , int size);
int     printList   (List* list);
int     freeList    (List* list);
