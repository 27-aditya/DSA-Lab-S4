#include <stdio.h>
#include <stdlib.h>

// basic definitions for color
#define red 0
#define black 1

// node for red black with color
struct node {
  int data;
  int color;
  struct node *left;
  struct node *right;
  struct node *parent;
};

// function to create node
struct node *createnode(int key) {
  struct node *p = (struct node *)malloc(sizeof(struct node));
  if (p) {
    p->data = key;
    p->color = red;
    p->parent = p->left = p->right = NULL;
  }
  return p;
}

// defining a rbt
struct redblacktree {
  struct node *root;
};

// function for left rotation
void leftrotate(struct redblacktree *rbt, struct node *x) {
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

/*
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
}*/

// function for right rotation
void rightrotate(struct redblacktree *rbt, struct node *x) {
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
}

/*
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
*/

// function for checking the insert cases 
void insertfix(struct redblacktree *rbt, struct node *z) {
  while (z->parent && z->parent->color == red) {
    if (z->parent == z->parent->parent->left) {
      struct node *y = z->parent->parent->right;
      if (y && y->color == red) { // if uncle is red
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      } 
      else{
        if (z == z->parent->right) {
          z = z->parent;
          leftrotate(rbt, z);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        rightrotate(rbt, z->parent->parent);
      }
    } 
    else{
      struct node *y = z->parent->parent->left;
      if (y && y->color == red) {
        z->parent->color = black;
        y->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      }
      else {
        if (z == z->parent->left) {
          z = z->parent;
          rightrotate(rbt, z);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        leftrotate(rbt, z->parent->parent);
      }
    }
  }
  // changing roots color to black
  rbt->root->color = black;
}

// function for inserting in a rbt
void insert(struct redblacktree *rbt, int key) {
  struct node *z = createnode(key);
  struct node *y = NULL;
  struct node *x = rbt->root;

  while (x != NULL) {
    y = x;
    if (z->data < x->data)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;
  if (y == NULL)
    rbt->root = z;
  else if (z->data < y->data)
    y->left = z;
  else
    y->right = z;

  z->left = NULL;
  z->right = NULL;
  z->color = red;

  insertfix(rbt, z); // calling the insert fix function for  recoloring and rotations
}

// printing function for a node
void printhelper(struct node *node) {
  if (node != NULL) {
    printf("(%d%c", node->data, (node->color == red) ? 'R' : 'B');
    printhelper(node->left);
    //printf("");
    printhelper(node->right);
    printf(")");
  } 
  else {
    printf("()");
  }
}

// wrapper function for printing the tree
void printtree(struct redblacktree *tree) {
  printhelper(tree->root);
  printf("\n");
}

// function for deleting a node
void freenode(struct node *node) {
  if (node != NULL) {
    freenode(node->left);
    freenode(node->right);
    free(node);
  }
}

// wrapper function for deleting a tree
void freetree(struct redblacktree *rbt) {
  freenode(rbt->root);
  free(rbt);
}

// main menu for calling functions
int main() {
  struct redblacktree *red_black_tree = (struct redblacktree *)malloc(sizeof(struct redblacktree));
  red_black_tree->root = NULL;
  char input[100]; // assuming max input length is 100 characters
  int num;
  while (1) {
    scanf("%s", input);
    if (input[0] == 'e' && input[1] == '\0') // check if input is 'e'
      break;
    else {
      num = atoi(input);
      insert(red_black_tree, num);
      printtree(red_black_tree);
    }
  }
  freetree(red_black_tree);
  return 0;
}
