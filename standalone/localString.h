#pragma once

#include<stdint.h>

#define ISNULL(X)  if(X ==  NULL){       \
  fprintf(stderr,"ERROR : %s is NULL in %s at %d!\n",#X,__FUNCTION__, __LINE__);  \
  exit(EXIT_FAILURE);            \
}\

#define ISINVAL(X,Y,Z) if(X Y Z){  \
  fprintf(stderr,"ERROR : %s %s %s in %s at %d!\n",#X,#Y,#Z,__FUNCTION__, __LINE__);\
  return 0;\
}\

typedef struct  localString  localString;
typedef struct  LSList  LSList;

struct localString{
  char*         string;
  localString*  next;
};

struct LSList{
  localString*  head;
  localString*  tail;
  uint64_t  size;
};

localString*     initNode      ();
localString*     createNode    (const char* string);
localString*     addNode       (LSList* list , const char* string);
localString*     editNode      (localString* node , const char* string);
localString*     insertNextNode(LSList* list , localString* node,const char* string);
localString*     getNode       (LSList* list , uint64_t index);
localString*     deleteNextNode(LSList* list , localString* node);

LSList*     initLSList      ();
LSList*     createLSList    (uint64_t size);
LSList*     splitLSList     (LSList* list , uint64_t index);
uint64_t    shrinkLSList    (LSList* list , uint64_t size);
uint64_t    printLSList     (LSList* list);
uint64_t    freeLSList      (LSList* list);
