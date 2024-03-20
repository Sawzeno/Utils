#include<stdint.h>
#include<stdbool.h>

#define LOG_ERROR(fmt, ...) \
    fprintf(stderr, "[ERROR] %s: " fmt " [%s:%d]\n", __FUNCTION__, ##__VA_ARGS__, __FILE__, __LINE__);\
    exit(EXIT_FAILURE);\

#define LOG_WARNING(fmt, ...) \
    fprintf(stdout, "[WARNING] %s: " fmt " [%s:%d]\n", __FUNCTION__, ##__VA_ARGS__, __FILE__, __LINE__);\

#define MEMERR(X) if(X  ==  NULL){  \
        LOG_ERROR("%s allocation failed", #X);\
        }\

#define ISNULL(X) if(X  ==  NULL){\
        LOG_WARNING("%s is NULL",#X);\
          return 0;\
        }\

#define U64 uint64_t
#define DEBUG write(STDOUT_FILENO, "\x1b[2;93mDEBUG\x1b[0m\n", 18);

typedef struct Node Node;
typedef struct List List;
typedef struct ListInfo ListInfo;

struct Node{
  void* item;
  Node* next;
};

struct ListInfo{
  void* (*createInfo) (void*);
  void  (*debugInfo)  (void*);
};

struct List{
  Node*     head;
  Node*     tail;
  ListInfo  info;
  U64       size;
};

Node* createNode  (ListInfo info , void* item);
List* initList    (ListInfo info);
List* createList  (ListInfo info , U64 size);
Node* addNode     (List* list , void* item);
bool  debugList   (List* list);
U64   freeItems   (List* list);
U64   shrinkList  (List*  list , U64 index);
Node* getNode(List* list ,U64 index);

