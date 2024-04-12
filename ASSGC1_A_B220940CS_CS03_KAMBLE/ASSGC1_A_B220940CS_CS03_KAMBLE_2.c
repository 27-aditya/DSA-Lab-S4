#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node *createnode(int x){
    struct node *t;
    t = (struct node *)malloc(sizeof(struct node));
    t->next = NULL;
    t->data = x;
    return t;
}

void listinsert(struct node **p, int x){
    
    struct node *t;
    t = createnode(x);
    struct node *temp;
    temp = *p;
    if((*p) == NULL){
        (*p) = t;
        (*p)->next = NULL;
    }
    else{
        while(temp->next != NULL){
            temp = temp->next ;
        }
        temp->next = t;
    }
} 

int listdelete(struct node **p, int index){
    int x = -1;
    struct node *c;
    struct node *t = (*p);
    struct node *temp = NULL;
    if(index == 1){
        temp = (*p);
        *p = (*p)->next;
        x = temp->data;
        free(temp);
        return x;
    }
    else{
        for(int i = 0; i < index-1; i++){
            c = t;
            t = t->next;
        }
        temp = t;
        c->next = t->next;
        x = temp->data;
        free(temp);
        return x; 
    }
    return x;
}

char listpal(struct node *p){
  int arr[10000];
  int i  = 0, count = 0;
  struct node *p1 = p;
  while (p1 != NULL){
    arr[i] = p1->data;
    p1 = p1->next;
    i++;
    count++;  
  }
  for(int i = 0; i < count; i++){
    if(arr[i] != arr[count - i -1]){
      return 'N';
    }
    else{
      return 'Y';
    }
  }   
} 

void listdisplay(struct node *p){
    while(p){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void listrduplicate(struct node **p){
    struct node *ptr1, *ptr2, *dup;
    ptr1 = *p;
 
    while (ptr1 != NULL && ptr1->next != NULL) {
        ptr2 = ptr1;
 
        while (ptr2->next != NULL) {
            if (ptr1->data == ptr2->next->data) {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                free(dup);
            }
            else
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    listdisplay(*p);
}

int main(){
    struct node *a = NULL; 
    char ch;
    int num, index;
    while(1){
      scanf("%c",&ch);
      switch (ch){
      case 'a':
        scanf("%d",&num);
        listinsert(&a, num);
        break;
      case 'r':
        scanf("%d",&index);
        printf("%d\n",listdelete(&a, index));
        break;
      case 'd':
        listrduplicate(&a);
        break;
      case 'p':
        printf("%c\n",listpal(a));
        break;
      case 's':
        listdisplay(a);
        break;
      case 'e':
        return;
        break;
      }
    }
}