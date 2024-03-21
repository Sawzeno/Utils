#pragma once

#include  <stdint.h>
#include  <stdbool.h>

#include  "../Log/log.h"

#define U64 uint64_t

typedef struct  TreeNode  TreeNode;
typedef struct  Tree      Tree;
typedef struct  TreeInfo  TreeInfo;

struct  TreeNode{
  void*     item;
  TreeNode* left;
  TreeNode* right;
};

struct Tree{
  TreeNode* head;
}; 
