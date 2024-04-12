#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

struct node{
  struct node *left;
  struct node *right;
  int data;
};

struct queue{
  int front;
  int rear;
  int size;
  struct node **Q;
};

struct node *createnode(int key){
  struct node *q;
  q = (struct node *)malloc(sizeof(struct node));
  q->left = q->right = NULL;
  q->data = key;
  return q;
}

void create(struct queue *q, int size){
  q->size = size;
  q->front = q->rear = 0;//q->front = q->rear = -1; normal queue
  q->Q = (struct node **)malloc(q->size*sizeof(struct node *));
}

void enqueue(struct queue *q, struct node * x){
  if((q->rear+1)%q->size == q->front)
    printf("Queue is full\n");
  else{
    q->rear = (q->rear+1)%q->size;
    q->Q[q->rear] = x;
  }
}

struct node *dequeue(struct queue *q){
  struct node* x = NULL;
  if(q->rear == q->front)
    printf("Queue is empty\n");
  else{
    q->front = (q->front+1)%q->size;
    x = q->Q[q->front];
  }
  return x;
}

int isempty(struct queue q){
  return q.front == q.rear;
}

struct node *createtree(char arr[], int size, int *preindex){
  if (*preindex >= size || arr[*preindex] == ')')
    return NULL;

  int num = 0;
  while (*preindex < size && isdigit(arr[*preindex])) {
    num = num * 10 + (arr[*preindex] - '0');
    (*preindex)++;
  }

  struct node *root = createnode(num);

  if (*preindex < size && arr[*preindex] == '(') {
    (*preindex)++;
    root->left = createtree(arr, size, preindex);
    (*preindex)++;
  }

  if (*preindex < size && arr[*preindex] == '(') {
    (*preindex)++; 
    root->right = createtree(arr, size, preindex);
    (*preindex)++;
  }

  return root;
}

/*height of the tree
int height(struct node *p){
  int x, y;
  if(p != NULL){
    x = height(p->left);
    y = height(p->right);
    if (x > y){
      return x+1;
    }
    else{
      return y+1;
    }
  }
  return 0;
}*/

// right view of bst
void rightview(struct node *root){
  if(root == NULL)
    return;
  printf("%d ",root->data);
  if(root->right != NULL)
    rightview(root->right);
  else
    rightview(root->left);
}

// checks if tree is bst
int isbst(struct node *root, int min, int max){
  int l,r;  
  if(root == NULL)
      return 1;
  if(root->data <= min || root->data >= max)
    return 0;

  return isbst(root->left, min, root->data) && isbst(root->right, root->data, max);
}

// gets the max sum using isbst 
int maximumsumbst(struct node *root){
  int sum;
  int leftsum, rightsum;

  if(root == NULL)
    return 0;

  if(isbst(root, INT_MIN, INT_MAX)){
    sum = 0;
    sum += (root->left != NULL) ? maximumsumbst(root->left) : 0;
    sum += (root->right != NULL) ? maximumsumbst(root->right) : 0;
    return sum + root->data;
  }
  else{
    leftsum = maximumsumbst(root->left);
    rightsum = maximumsumbst(root->right);
    return (leftsum > rightsum) ? leftsum : rightsum;
  }
}

/* inorder traversal in array
void inorder(struct node *root, int arr[], int *index){
  if (root == NULL)
    return;

  inorder(root->left, arr, index);
  arr[(*index)++] = root->data;
  inorder(root->right, arr, index);
}*/

/*
void postordertraversal(struct node* root) {
  if (root != NULL) {
      postordertraversal(root->left);
      postordertraversal(root->right);
      printf("%d ", root->data);
  }
}*/

// levelorder using queue
void levelorder(struct node *p){
  struct queue q;
  create(&q, 100);
  printf("%d ",p->data);
  enqueue(&q, p);
  while (!isempty(q)){
    p = dequeue(&q);
    if(p->left){
      printf("%d ",p->left->data);
      enqueue(&q, p->left);
    }
    if(p->right){
      printf("%d ",p->right->data);
      enqueue(&q, p->right);
    }
  }
}


int main(){
  char arr[100];
  scanf("%s",arr);
  int preindex = 0;
  int size = strlen(arr);
  struct node *root = createtree(arr, size, &preindex);
  char ch;
  while(1){
    scanf("%c",&ch);
    switch (ch){
    case 'l':
      levelorder(root);
      printf("\n");
    break;
    case 'm':
      printf("%d\n",maximumsumbst(root));
    break;
    case 'r':
      rightview(root);
      printf("\n");
    break;
    case 'e':
      return;
    break;
    }
  }

}