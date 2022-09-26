#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap * mapNew = (TreeMap *)malloc(sizeof(TreeMap));

  mapNew->root = NULL;
  mapNew->current = NULL;
  mapNew->lower_than = lower_than;
  
  return (mapNew);
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if(tree == NULL) return;

  TreeNode *newNodo = createTreeNode(key, value);
  TreeNode *nodoAux;
  
  searchTreeMap(tree, key);
  nodoAux = tree->current;
  newNode->parent = nodoAux;

  if (tree->lower_than(nodoAux->pair->key, key) == 1) {
    nodoAux->right = newNode;
  }else if (tree->lower_than(key, nodoAux->pair->key) == 1) {
    nodoAux->left = newNode;
  }
    
  tree->current = newNode;

}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  TreeNode *newNodo = tree->root;
  
  if(tree->root == NULL)
  {
    return(NULL);
  }
  else
  {
    while(newNodo != NULL)
    {
      if(is_equal(tree, newNodo->pair->key, key) == 1)
      {
        tree->current = newNodo;
        return (newNodo->pair);
      }
      if(tree->lower_than(newNodo->pair->key, key) == 0)
      {
        newNodo = newNodo->left;
      }
      else
      {
        newNodo = newNodo->right;
      }
    }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
