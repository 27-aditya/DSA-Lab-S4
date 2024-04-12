#include <stdio.h>
#include <stdlib.h>

// node with key, value, height
struct node{
  int data;
  int value;
  int height;
  struct node *left;
  struct node *right;
};

// function for node height
int nodeheight(struct node *p){
  int hl, hr;
  hl = p && p->left  ? p->left->height : 0;
  hr = p && p->right ? p->right->height : 0;

  // return the bigger height
  return hl>hr ? hl+1 : hr+1; 
}

// function for balance factor
int balancefactor(struct node *p){
  // base condition
  if(!p)
    return 0;

  int hl, hr;

  hl = nodeheight(p->left);
  hr = nodeheight(p->right);

  // return the difference of the heights
  return hl-hr;
}

// function for left left rotation
struct node *LLrotation(struct node *t){
  struct node *tl = t->left;
  struct node *tlr = t->left->right;

  // adjust the pointers
  tl->right = t;
  t->left = tlr;

  // update height
  t->height = nodeheight(t);
  tl->height = nodeheight(tl);
  
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

// function for right right rotation
struct node *RRrotation(struct node *t){
  struct node *tr = t->right;
  struct node *trl = t->right->left;

  // adjust the pointers
  tr->left = t;
  t->right = trl;

  // update the height
  t->height = nodeheight(t);
  tr->height = nodeheight(tr);

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

// function for left right rotaation
struct node *LRrotation(struct node *t){
  struct node *tl = t->left;
  struct node *tlr = t->left->right;

  // adjust the pointers
  tl->right = t->right;
  t->left = tlr->right;

  tlr->left = tl;
  tlr->right = t;

  // update the heights
  t->height = nodeheight(t);
  tl->height = nodeheight(tl);
  tlr->height = nodeheight(tlr);
  return tlr;
}

// function for right left rotation
struct node *RLrotation(struct node *t){
  struct node *tr = t->right;
  struct node *trl = t->right->left;

  // adjust the pointers
  tr->left = trl->left;
  t->right = trl->right;

  trl->left = t;
  trl->right = tr;

  // update the heights
  t->height = nodeheight(t);
  tr->height = nodeheight(tr);
  trl->height = nodeheight(trl);

  return trl;
}

// function for the searching a key
int keysearch(struct node *p, int key){
  // if tree is NULL 
  if( p== NULL)
    return 0;
  while (p){
    // traversal 
    if(p->data < key)
      p = p->right;
    else if(p->data > key)
      p = p->left;
    else if(p->data == key)
    // if present return 1
      return 1;
    else 
    // if not present return 0
      return 0;
  }
}

struct node *insert(struct node *t, int key, int nvalue) {
  // base condition
  if (t == NULL) {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = key;
    p->value = nvalue;
    p->left = p->right = NULL;
    p->height = 1;
    return p;
  }

  // traverse according to the condition
  if (key > t->data) {
    t->right = insert(t->right, key, nvalue);
  }
  else if (key < t->data) {
    t->left = insert(t->left, key, nvalue);
  } 
  else{
    // key already exists, update the value
    t->value = nvalue;
    return t;
  }

  t->height = nodeheight(t);

  // check the balancefactor for rotations
  if (balancefactor(t) == 2 && balancefactor(t->left) == 1)
    return LLrotation(t);
  else if (balancefactor(t) == 2 && balancefactor(t->left) == -1)
    return LRrotation(t);
  else if (balancefactor(t) == -2 && balancefactor(t->right) == -1)
    return RRrotation(t);
  else if (balancefactor(t) == -2 && balancefactor(t->left) == 1)
    return RLrotation(t);

  return t;
}

// inorder traversal
void printelements(struct node *p){
  if(p){
    printelements(p->left);
    printf("%d ",p->data);
    printelements(p->right);
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
void find(struct node *t, int key){
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
      printf("%d %d\n",t->data, t->value);
      break;
    }
  }
  // if not present print -1
  if(found == 0)
    printf("-1\n");
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

// function for chekcing if the tree is empty
void empty(struct node *p){
  if(p == NULL)
    printf("1\n");
  else
    printf("0\n");
}

// function for the number of nodes in the tree
int size(struct node *p){
  int x = 0, y = 0;
  if(p == NULL)
    return 0;
  else{
    x = size(p->left);
    y = size(p->right);
    return x+y+1;
  }
}

// function for getting the asked key or its inorder successor
struct node* lower_bound(struct node *root, int key) {
  struct node *result = NULL;
  while (root != NULL) {
    if (root->data >= key) {
      result = root;
      root = root->left;
    }
    else{
      root = root->right;
    }
  }
  return result;
}

// function for printing the low bound
void lowbound(struct node *root, int key) {
  struct node *lb_node = lower_bound(root, key);

  if (lb_node != NULL) {
    printf("%d %d\n", lb_node->data, lb_node->value);
  }
  else{
    // if lb_node is NULL, it means no node with key = given key was found.
    struct node *successor = NULL;
    struct node *temp = root;

    // traverse to find the next larger key
    while (temp != NULL) {
      if (temp->data > key) {
        successor = temp;
        temp = temp->left;
      }
      else{
        temp = temp->right;
      }
    }

    if(successor != NULL) {
      printf("%d %d\n", successor->data, successor->value);
    }
    else {
      printf("-1\n"); // if no successor found, the tree is empty
    }
  }
}

// main menu for calling functions
int main(){
  struct node *p = NULL;
  char op;
  while (1){
    scanf("%c", &op);
    switch (op) {
      case 'i':{
        int key, value;
        scanf("%d %d",&key, &value);
        p = insert(p, key, value);
        break;
      }
      case 'l':{
        int find;
        scanf("%d",&find);
        lowbound(p, find);
        break;
      }
      case 'f':{
        int key;
        scanf("%d",&key);
        find(p, key);
        break;
      }
      case 's':{
        printf("%d\n",size(p));
        break;
      }
      case 'e':{
        empty(p);
        break;
      }
      case 'p':{
        printelements(p);
        printf("\n");
        break;
      }
      case 't':
        return 0;
    }
  }
}
