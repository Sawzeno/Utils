#pragma once

typedef struct Node Node;
typedef struct Space Space;

struct Node{
  int   value;
  Node* left;
  Node* right;
};

struct Space{
  int   available;
  Node* head;
};

Node*   createNode(int value);
Space*  createSpace(int value);
void    subdivide(Node* node , int levels);
void    divide(Node* node , int percentage);
void    draw(Node* head , int level);

