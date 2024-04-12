#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node{
  struct node *left;
  int data;
  struct node *right;
};

struct queue{
  int front;
  int rear;
  int size;
  struct node **Q;
};

void create(struct queue *q, int size){
  q->size = size;
  q->front = q->rear = -1; //normal queue
  q->Q = (struct node **)malloc(q->size*sizeof(struct node *));
}

int isempty(struct queue q){
  return q.front == q.rear;
}

void enqueue(struct queue *q, struct node * x){
  if(q->rear == q->front-1)
    printf("Queue is full\n");
  else{
    q->rear = q->rear+1;
    q->Q[q->rear] = x;
  }
}

struct node *dequeue(struct queue *q){
  struct node* x = NULL;
  if(q->rear == q->front)
    printf("Queue is empty\n");
  else{
    q->front = q->front+1;
    x = q->Q[q->front];
  }
  return x;
}

struct node *buildtree(int *inorder, int inordersize, int *preorder, int preordersize){
  if(preordersize == 0 || inordersize == 0)
    return NULL;
  int rootdata = preorder[0];
  struct node *root;
  root = (struct node *)malloc(sizeof(struct node));
  root->data = rootdata;
  root->left = root->right = NULL;

  int rootpos;
  for(rootpos = 0; rootpos< inordersize; ++rootpos)
  {
    if(inorder[rootpos] == rootdata)
      break;
  }

  root->left = buildtree(inorder, rootpos, preorder+1, rootpos);
  root->right = buildtree(inorder+rootpos+1, inordersize-rootpos-1, preorder+rootpos+1, preordersize-rootpos-1);
  return root;
}

void postordertraversal(struct node* root) {
  if (root != NULL) {
      postordertraversal(root->left);
      postordertraversal(root->right);
      printf("%d ", root->data);
  }
}

/*void levelorder(struct node *p){
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
}*/

// height of the tree
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
}

// length of longest path from two leaf nodes
int diameter(struct node *root){
  int x, y;
  if(root != NULL){
    x = height(root->left);
    y = height(root->right);
  }
  return x+y+1;
}

// sum of the left leaf nodes
int leftleafsum(struct node *root){
  if(root == 0)
    return 0;
  
  if(root->left != NULL && root->left->left == NULL && root->left->right == NULL){
    return root->left->data + leftleafsum(root->right);
  }
  else{
    return leftleafsum(root->left) + leftleafsum(root->right);
  }
  
}

// find the largest value of each level
void finder(int* res, struct node* root, int d){
  if(!root)
    return;
  if(d == res[0]){
    res[0]++;
    res = (int*)realloc(res, (res[0] + 1) * sizeof(int));
    res[res[0]] = root->data;
  } 
  else{
    res[d + 1] = (res[d + 1] > root->data) ? res[d + 1] : root->data;
  }
  // recursive calls
  finder(res, root->left, d + 1);
  finder(res, root->right, d + 1);
}

// take the max values into an array
int* maxelementofeachlevel(struct node* root, int* size){
  int* res = (int*)malloc(sizeof(int));
  res[0] = 0;
  finder(res, root, 0);
  *size = res[0] + 1;
  return res;
}

// zigzag level order traversal
void zigzagtraversal(struct node* root) {
  if (!root)
      return;
  struct node* currentlevel[1000];
  struct node* nextlevel[1000];
  int current_top = -1;
  int next_top = -1;

  currentlevel[++current_top] = root;

  int lefttoright = 1;
  while (current_top != -1){
    struct node* temp = currentlevel[current_top--];
    if(temp){
      printf("%d ", temp->data);
      if(lefttoright){
        if (temp->left)
          nextlevel[++next_top] = temp->left;
        if (temp->right)
          nextlevel[++next_top] = temp->right;
        }
      else{
        if (temp->right)
          nextlevel[++next_top] = temp->right;
        if (temp->left)
          nextlevel[++next_top] = temp->left;
      }
    }
    if(current_top == -1){
      lefttoright = !lefttoright;
      int temp_top = current_top;
      current_top = next_top;
      next_top = temp_top;
      for(int i = 0; i <= current_top; ++i){
        currentlevel[i] = nextlevel[i];
      }
    }
  }
}


int main(){
  int preorder[100];
  int inorder[100];
  int n;
  scanf("%d",&n);
  for(int i = 0; i < n; i++)
    scanf("%d",&inorder[i]);
  for(int i = 0; i < n; i++)
    scanf("%d",&preorder[i]);
  char ch;
  struct node *root = buildtree(inorder, n, preorder, n);
  int size;
  int *arr = maxelementofeachlevel(root, &size);
  while(1){
    scanf("%c",&ch);
    switch (ch){
    case 'p':
      postordertraversal(root);
      printf("\n");
      break;
    case 'z':
      zigzagtraversal(root);
      printf("\n");
      break;
    case 'm':
      //levelmax(root);
      for (int i = 1; i < height(root)+1; i++)
        printf("%d ",arr[i]);
      printf("\n");
      break;
    case 'd':
      printf("%d\n",diameter(root));
      break;
    case 's':
      printf("%d\n",leftleafsum(root));
      break;
    case 'e':
      return;
      break;
    }
  }
}