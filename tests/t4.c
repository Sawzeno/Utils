#include  "utils.h"

#define ADDNODE(list, newNode) \
  do { \
    list->tail = addNextNode(list->tail, newNode); \
  } while(0)

#define INSERTNODE(prev, newNode) \
  do { \
    Node* temp = prev->next; \
    addNextNode(prev, newNode); \
    addNextNode(newNode, temp); \
  } while (0)

typedef struct Node Node;
typedef struct List List;

struct Node {
  Node* next;
  char  item;
};

struct List {
  Node* head;
  Node* tail;
};

Node* createNode(Node* next, char item) {
  Node* node = calloc(1, sizeof(Node));
  MEMERR(node);
  node->next = next;
  node->item = item;
  return node;
}

Node* addNextNode( Node* prev, Node* newNode) {
  ISNULL(newNode,NULL);
  ISNULL(prev,NULL);

  prev->next = newNode;

  return newNode;
}

List* createList() {
  List* list = calloc(1, sizeof(List));
  MEMERR(list);

  Node* dummy = createNode( NULL, '\0');
  list->head = list->tail = dummy;
  return list;
}

int printList(List* list) {
  Node* temp = list->head->next;
  while (temp != NULL) {
    printf("%c", temp->item);
    temp = temp->next;
  }
  printf("\n");
  return 0;
}

void freeList(List* list) {
  Node* current = list->head;
  Node* next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

int main() {
  List* listA = createList();
  List* listB = createList();
  char* string1 = "Hi Mom!";
  char* string2 = "Hi Dad!";

  for (int i = 0; string1[i] != '\0'; ++i) {
    Node* newNode = createNode(NULL,  string1[i]);
    ADDNODE(listA , newNode);
  }
  for(int i = 0 ; string2[i] != '\0'; ++i){
    Node* newNode = createNode(NULL,  string2[i]);
    ADDNODE(listB , newNode);
  }

  printList(listA);
  printList(listB);

  freeList(listA);
  freeList(listB);
  return 0;
}

