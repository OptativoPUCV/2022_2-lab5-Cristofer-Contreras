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
  TreeNode * padre= tree->root;
  TreeNode * nodoAux = NULL;
  
  if(searchTreeMap(tree,key)!=NULL) return; 
  
  while(padre!=NULL){
    nodoAux=padre;
    int resultados = tree->lower_than(key,padre->pair->key);
    if(resultados==1){
      padre=padre->left;
    }else{
        if(resultados==0){
        padre=padre->right;
      }else return;
    }
  }
  
  TreeNode * newNode= createTreeNode(key,value);
  newNode->parent=nodoAux;
  int resultado = tree->lower_than(key,nodoAux->pair->key);
  if(nodoAux!=NULL){
    if(resultado==1){
      nodoAux->left=newNode;
    }
    if(resultado==0){
      nodoAux->right=newNode;
    } 
    
  }
  if(nodoAux==NULL)tree->root=newNode;
  tree->current=newNode;
  return;
}

TreeNode * minimum(TreeNode * x){
  while(x->left!=NULL){
  x=x->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  // *Nodo con 2 hijos*
  if(node->left != NULL && node->right != NULL){
    TreeNode* aux = minimum(node->right);
    node->pair->key = aux->pair->key;
    node->pair->value = aux->pair->value;
    removeNode(tree , aux);
  }
  // *Nodo con 1 hijo*
  if (node->left == NULL && node->right != NULL){
    if(tree->lower_than(node->parent->pair->key , node->pair->key) == 1){
      node->parent->right = node->right;
      node->right->parent = node->parent;
    }
    else{
      node->parent->left = node->right;
      node->right->parent = node->parent;
    }
    return;
  }
  else if (node->left != NULL && node->right == NULL){
    if(tree->lower_than(node->parent->pair->key , node->pair->key) == 1){
      node->parent->right = node->left;
      node->left->parent = node->parent;
    }else{
      node->parent->left = node->left;
      node->left->parent = node->parent;
    }
    return;
  }
  // *Nodo con 0 Hijos*
  if (node->left == NULL && node->right == NULL){
    if(tree->lower_than(node->parent->pair->key , node->pair->key) == 1){
      node->parent->right = NULL;
    }else{
      node->parent->left = NULL;
    }
    return;
  }

  
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
  TreeNode * X = tree->root;
  tree->current=minimum(X);
  if(tree->current==NULL)return NULL;
  return tree->current->pair;
}
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
