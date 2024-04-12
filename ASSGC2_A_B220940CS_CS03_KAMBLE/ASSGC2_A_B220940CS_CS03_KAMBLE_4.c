#include <stdlib.h>
#include <stdio.h>

// node with color
struct node{
  int d;
  int c;
  struct node *right,*left;
};

// function for creating node
struct node* createnode(int d, int c){
  struct node* new=(struct node*)malloc(sizeof(struct node));
  new->d=d;
  new->c=c;
  new->left=NULL;
  new->right=NULL;
  return new;
}

// function for creating tree
struct node* createtree(char ch[], int* i){
  int key=0; int c=0;
  struct node* root=NULL;
  // untill termination character is reached
  while(ch[*i]!='\0'){
    // if open bracket skip 
    if(ch[*i]=='(') {
      (*i)+=2;
      // if bracket skip
      if(ch[*i]==')'){
        (*i)++;
        return NULL;
      }
      int s=1;
      if(ch[*i]=='-'){
        s=-1;
        (*i)++;
      }
      // getting number from character
      while(ch[*i]>='0'&&ch[*i]<='9'){
        key=key*10+(int)(ch[*i]-'0');
        (*i)++;
      }
      key*=s;
      (*i)++;
      // checking for red and black color
      if(ch[*i]=='R'||ch[*i]=='r'){
        c=0;
        (*i)+=2;
      }
      if(ch[*i]=='B'||ch[*i]=='b'){
        c=1;
        (*i)+=2;            
      }
      // recursicely creating subtrees
      root=createnode(key,c);
      root->left=createtree(ch,i);
      root->right=createtree(ch,i);
      while(ch[*i]!=')')
        (*i)++;
    }
    else if (ch[*i]==')'){
      (*i)++;
      return root;
    }
    else 
      (*i)++;  
  }
  return root;
}

/*struct node *createtree(char arr[], int size, int *preindex){
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
}*/

// function to check rbt properties
int check(struct node* tree, int count, int *valid)
{
  // if null bse condition
  if(tree==NULL)
    return count;

  // c equal to 1 condition
  if(tree->c==1) 
    count++;
  
  if(tree->c==0 &&((tree->left && tree->left->c==0)||(tree->right &&tree->right->c==0))) 
    *valid=0;
  
  int lc = check(tree->left,count,valid);
  int rc = check(tree->right,count,valid);
  
  if(lc!=rc) 
    *valid=0;
  
  return lc;
}

/*void rbtcheckstruct node *root, int key){
  if(root == NULL)
    return;

  if(key > root->data){
    rbtcheckroot->right, key);
    printf("%d ",root->data);
  }
  else if(key < root->data){
    rbtcheckroot->left, key);
    printf("%d ",root->data);
  }
}*/

int isbst(struct node *root, int min, int max){
  int l,r;  
  if(root == NULL)
      return 1;
  if(root->d <= min || root->d >= max)
    return 0;

  return isbst(root->left, min, root->d) && isbst(root->right, root->d, max);
}

// main function
int main()
{
  char ch[500];
  fgets(ch,500,stdin);

  struct node* tree=NULL;
  int c=0;
  tree=createtree(ch,&c);
  
  int valid=1;
  int count=0;
  
  valid = isbst(tree, 0, 32768);
  
  if(tree->c==0) 
    valid=0;
  else{
    check(tree,count,&valid);
  }
  
  if(valid) 
    printf("1\n");
  else 
    printf("0\n");
  
  return 0;
}
