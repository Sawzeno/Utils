#include "utils.h"

#define MAXNODES 32

typedef struct Node Node;
typedef struct Tree Tree;

struct Tree{
  Node* bank;
  Node* root;
  int   cap;
  int   size;
};

Tree tree;

struct Node{
  Node* left;
  Node* right;
  void* item;
};

Node* createNode(Node* left, Node* right, void* item){
  Node* node  = calloc(1, sizeof(Node));
  MEMERR(node);

  node->left  = left;
  node->right = right;
  node->item  = item;

  return node;
}

Node* addNode(Node* parent, Node* left, Node* right){
  ISNULL(parent, NULL);
  if(left == NULL && right ==  NULL){
    return NULL;
  }
  parent->left  = left;
  parent->right = right;
  return parent->left == NULL ? parent->right : parent->left;
}

Node* printNode(Node* root){
  if(root == NULL){
    return NULL;
  }else{
    printNode(root->left);
    printNode(root->right);
    UINFO("%s",(const char*)(root->item));
    return NULL;
  }
}

Node* createTree(Node* root, int levels){

  char* leftstr  = calloc(64, sizeof(char));
  sprintf(leftstr,  "left   level: %d",levels);
  char* rightstr  = calloc(64, sizeof(char));
  sprintf(rightstr, "right  level: %d",levels);

  if(levels < 1){
    return NULL;
  }else{
    Node* left = createNode(NULL, NULL, (void*)leftstr);
    Node* right= createNode(NULL, NULL, (void*)rightstr);    
    addNode(root, left, right);
    createTree(left, levels-1);
    createTree(right,levels-1);
    return NULL;
  }
}


int main(void){

  tree.cap  = MAXNODES;
  tree.bank = calloc(tree.cap, sizeof(Node));
  MEMERR(tree.bank);
  tree.root = tree.bank;
  Node* root = createNode(NULL, NULL, (void*)"root");
  int levels  = 2;
  createTree(root, levels);
  printNode(root);
  return 0;
}

