#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node{
  struct node *left;
  struct node *right;
  int data;
};

// creating node
struct node *createnode(int key){
  struct node *q;
  q = (struct node *)malloc(sizeof(struct node));
  q->left = q->right = NULL;
  q->data = key;
  return q;
}

// creating tree while ignoring brackets
struct node *createtree(char arr[], int size, int *preindex){
  if (*preindex >= size || arr[*preindex] == ')')
    return NULL;

  int num = 0;
  while (*preindex < size && isdigit(arr[*preindex])) {
    num = num * 10 + (arr[*preindex] - '0');
    (*preindex)++;
  }

  struct node *root = createnode(num);
  // ignore bracket
  if (*preindex < size && arr[*preindex] == '(') {
    (*preindex)++;
    root->left = createtree(arr, size, preindex);
    (*preindex)++;
  }
  // ignore bracket
  if (*preindex < size && arr[*preindex] == '(') {
    (*preindex)++; 
    root->right = createtree(arr, size, preindex);
    (*preindex)++;
  }

  return root;
}

// inorder traversal in array
void inorder(struct node *root, int arr[], int *index){
  if (root == NULL)
    return;

  inorder(root->left, arr, index);
  arr[(*index)++] = root->data;
  inorder(root->right, arr, index);
}

/*
void postordertraversal(struct node* root) {
  if (root != NULL) {
      postordertraversal(root->left);
      postordertraversal(root->right);
      printf("%d ", root->data);
  }
}
*/

// printing values from inorder array
void printrangevalues(struct node *root, int k1, int k2){
  int index = 0;
  int ar[100] = {0};
  inorder(root, ar, &index);
  for (int i = 0; i < 100; i++){
    if(ar[i] >= k1 && ar[i] <= k2)
      printf("%d ",ar[i]);
  }
  printf("\n");
}

// call the recursive function first then print the number
void ancestors(struct node *root, int key){
  if(root == NULL)
    return;

  if(key > root->data){
    ancestors(root->right, key);
    printf("%d ",root->data);
  }
  else if(key < root->data){
    ancestors(root->left, key);
    printf("%d ",root->data);
  }
}

/*void ipreorder(struct node *p){
  struct stack st;
  stkcreate(&st,100);
  
  while(p || !stkisempty(st)){
    if(p){
      printf("%d ",p->data);
      push(&st, p);
      p = p->lchild;
    }
    else{
      p = pop(&st);
      p = p->rchild;
    }
  }
}*/

int main(){
  int index = 0;
  char ch;
  int k1, k2, v1;
  char arr[100];
  scanf("%s",arr);
  int size = strlen(arr);
  struct node *root = createtree(arr, size, &index);
  while(1){
    scanf("%c",&ch);
    switch (ch){
    case 'p':
      scanf("%d",&k1);
      scanf("%d",&k2);
      printrangevalues(root, k1, k2);
    break;
    case 'a':
      scanf("%d",&v1);
      printf("%d ",v1);
      ancestors(root, v1);
      printf("\n");
    break;
    case 'e':
      return;
    break;
    }
  }
  return 0;
}