#include<stdlib.h>
#include"bspace.h"

Node* createNode(int value){
  Node* node  =  malloc(sizeof(Node));
  node->value =  value;
  node->left  = NULL;
  node->right = NULL;
  return node;
}

Space* createSpace(int value){
  Space* space      = malloc(sizeof(Space));
  space->available  = value;
  space->head       = createNode(space->available);
  return space;
}

//[LEFT] = [OBEJCT]   [RIGHT] = [WORLD]
void subdivide(Node* node , int levels){
  if(levels == 0 || node->value == 1){
    return;
  }
  if(node->value %2 != 0){
    node->left  = createNode((node->value/2) + 1);
  }else{
    node->left  = createNode(node->value/2);
  }
  subdivide(node->left,   levels - 1);   
  node->right  = createNode(node->value/2);
  subdivide(node->right,  levels - 1);
}

void divide(Node* node , int percentage){

  int temp = node->value;
  temp *= percentage;
  node->left  = createNode(temp/100 + temp%100);
  node->right = createNode(node->value - node->left->value);
}

void draw(Node* head , int level){
  if(head  == NULL){
    return;
  }
  int i = 0 ;
  while(i < level){
    printf(" ");
    i++;
  }
  i = 0;
  printf("|\n");
  while(i < level){
    printf(" ");
    i++;
  }
  printf("|");

  printf("%d|\n" , head->value);
  draw(head->left , level + 1);
  draw(head->right, level + 1);
}

