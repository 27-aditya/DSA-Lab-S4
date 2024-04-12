#include <stdio.h>
#include <stdlib.h>

// node with height as character
struct node{
  int data;
  int height;
  struct node *left;
  struct node *right;
};

// function for getting height of a node
int nodeheight(struct node *p){
  int hl, hr;
  // access the height and return it
  hl = p && p->left  ? p->left->height : 0; 
  hr = p && p->right ? p->right->height : 0;

  // return the bigger number of both
  return hl>hr ? hl+1 : hr+1; 
}

// function for balance factor to check for rotations
int balancefactor(struct node* p){
  // base condition for null pointer and also termination condition
  if (!p)
    return 0; 
  int hl, hr;
  // get the height of the node
  hl = p->left ? p->left->height : 0;
  hr = p->right ? p->right->height : 0;
  
  // return the difference of the left and right tree
  return hl - hr;
}

// left left rotation
struct node *LLrotation(struct node *t, int *rightr){
  struct node *tl = t->left;
  struct node *tlr = t->left->right;

  tl->right = t;
  t->left = tlr;

  // update the heights
  t->height = nodeheight(t);
  tl->height = nodeheight(tl);
  
  // increase the counter
  (*rightr)++;
  return tl;
}

/*void leftrotate(struct redblacktree *rbt, struct node *x) {
  struct node *y = x->right;
  x->right = y->left;

  if (y->left != NULL)
      y->left->parent = x;
  y->parent = x->parent;

  if (x->parent == NULL)
    rbt->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}
*/

// right right rotation
struct node *RRrotation(struct node *t, int *leftr){
  struct node *tr = t->right;
  struct node *trl = t->right->left;

  tr->left = t;
  t->right = trl;

  // update the height
  t->height = nodeheight(t);
  tr->height = nodeheight(tr);

  // increase the counter
  (*leftr)++;
  return tr;
}

/*void rightrotate(struct redblacktree *rbt, struct node *x) {
  struct node *y = x->left;
  x->left = y->right;

  if (y->right != NULL)
    y->right->parent = x;
  y->parent = x->parent;

  if (x->parent == NULL)
    rbt->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->right = x;
  x->parent = y;
}*/

// left right rotation
struct node *LRrotation(struct node *t, int *leftr, int *rightr){
  struct node *tl = t->left;
  struct node *tlr = t->left->right;

  tl->right = t->right;
  t->left = tlr->right;

  tlr->left = tl;
  tlr->right = t;

  // update the height
  t->height = nodeheight(t);
  tl->height = nodeheight(tl);
  tlr->height = nodeheight(tlr);
  
  // increase the counter
  (*leftr)++;
  (*rightr)++;
  return tlr;
}

// rigth left rotation
struct node *RLrotation(struct node *t, int *leftr, int *rightr){
  struct node *tr = t->right;
  struct node *trl = t->right->left;

  tr->left = trl->left;
  t->right = trl->right;

  trl->left = t;
  trl->right = tr;

  // update the height
  t->height = nodeheight(t);
  tr->height = nodeheight(tr);
  trl->height = nodeheight(trl);

  // increase the counter
  (*leftr)++;
  (*rightr)++;
  return trl;
}

// recursive insert function
struct node *insert(struct node *t, int key, int *leftr, int *rightr){
  
  //base condition
  struct node *p;
  if((t) == NULL){ 
    p = (struct node *)malloc(sizeof(struct node));
    p->data = key;
    p->left = p->right = NULL;
    p->height = 1;
    return p;
  }
  
  if(key > (t)->data){
    (t)->right = insert(t->right, key, leftr, rightr);
  }
  else if(key < (t)->data){
    (t)->left = insert(t->left, key, leftr, rightr);
  }

  t->height = nodeheight(t);

  // check the balance factor for rotations
  if(balancefactor(t) == 2 && balancefactor(t->left) == 1)
    return LLrotation(t, leftr);
  else if(balancefactor(t) == 2 && balancefactor(t->left) == -1)
    return LRrotation(t, leftr, rightr);
  else if(balancefactor(t) == -2 && balancefactor(t->right) == -1)
    return RRrotation(t,  rightr);
  else if(balancefactor(t) == -2 && balancefactor(t->right) == 1)
    return RLrotation(t, leftr, rightr);

  return t;
}

// inorder traversal
void inorder(struct node *p){
  if(p){
    inorder(p->left);
    printf("%d ",p->data);
    inorder(p->right);
  }
}

// preorder traversal
void preorder(struct node *t){
  if(t){
    printf("%d ",t->data);
    preorder(t->left);
    preorder(t->right);
  }
}

// search function
void search(struct node *t, int key){
  int found = 0;
  struct node *p = t;
  // check for the key 
  while (t != NULL){
    if(key > t->data)
      t = t->right;
    else if(key < t->data)
      t = t->left;
    else if(key == t->data){
      found = 1;
      break;
    }
  }
  //if not there print -1
  if(found == 0)
    printf("-1\n");
  else if(found == 1){
    // if present print the ancestors
    while (p){
      if(key > p->data){
        printf("%d ",p->data);
        p = p->right;
      }
      else if(key < p->data){
        printf("%d ",p->data);
        p = p->left;
      }
      else if(key == p->data){
        printf("%d\n",key);
        break;
      }
    }
  }
}

/*
int keysearch(struct node *p, int key){
  if( p== NULL)
    return 0;
  while (p){
    if(p->data < key)
      p = p->right;
    else if(p->data > key)
      p = p->left;
    else if(p->data == key)
      return 1;
    else 
      return 0;
  }
}
*/

int main(){
  struct node *p = NULL;
  int leftr = 0;
  int rightr = 0;
  char op;
  // menu for operations
  while (1){
    scanf("%c", &op);
    switch (op) {
      case 'i':{
        int key;
        scanf("%d",&key);
        p = insert(p, key, &leftr, &rightr);
        break;
      }
      case 'x':{
        int key;
        scanf("%d",&key);
        search(p, key);
        break;
      }
      case 'p':{
        preorder(p);
        printf("\n");
        break;
      }
      case 's':{
        printf("%d %d\n",rightr, leftr);
        break;
      }
      case 'e':
        return 0;
    }
  }
}