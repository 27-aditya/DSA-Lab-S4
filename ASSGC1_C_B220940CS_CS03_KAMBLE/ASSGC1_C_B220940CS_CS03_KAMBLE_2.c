#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
  int data;
  struct node *next;
};
// hashh function
int hash(int key, int hashsize) {
  return key % hashsize;
}
// insert while maintaining sort
void sortedinsert(struct node **h, int key) {
  struct node *p, *q = NULL, *t = *h;
  p = (struct node *)malloc(sizeof(struct node));
  //bool duplicate[100] = {false};
  	  if (!p)
	    return;
	  p->next = NULL;
	  p->data = key;
  //if(!duplicate[index]){
	  if (*h == NULL)
	    *h = p;
	  else {
	    while (t && t->data < key) {
	      q = t;
	      t = t->next;
	    }
	    if (t == *h) {
	      p->next = *h;
	      *h = p;
	    }
	    else {
	      p->next = q->next;
	      q->next = p;
	    }
		}
	//}
	//else{
	//	printf("-1\n");
	//	return;
	//}
	//duplicate[index] = true;
}
/*void insert(int ht[], int key){
  int index = hash(key);

  if(ht[index] != -1){
    index = probe(ht, key);
  }
  ht[index] = key;
}*/
// wrapper for insert
void sortedhashtable(struct node *ht[], int key, int hashsize) {
  int index = hash(key, hashsize);
  sortedinsert(&ht[index], key);
}
// search through the chain
void search(struct node *ht[], int key, int hashsize) {
  int pos = 1;
  bool found = false;
  int index = hash(key, hashsize);
  struct node *current = ht[index];
  while (current != NULL) {
    if (key == current->data) {
      printf("%d %d\n", index, pos);
      found = true;
      return;
    }
    current = current->next;
    pos++;
  }
  if (!found)
    printf("-1\n");
}
/*int search(int a[], int key){
  int index = hash(key);
  int i = 0;
  while(a[(index + i) % size] != key && i < size) // linear probe
    i++;
  if(a[(index + i) % size] == key)
    return (index + i) % size;
  return -1;
}*/
// delete in the chain
void delete(struct node *ht[], int key, int hashsize) {
  int index = hash(key, hashsize);
  struct node *p = ht[index], *q = NULL;
  int pos = 1;
  while (p && p->data != key) {
    q = p;
    p = p->next;
    pos++;
  }
  if (p == NULL) {
    printf("-1\n");
    return;
  }
  if (q == NULL){ 
    ht[index] = p->next;
  }
  else{ 
    q->next = p->next;
  }
  free(p);
  printf("%d %d\n",index, pos); // Add newline character here
}
// update and rehash the array 
void updatehash(struct node *ht[], int oldkey, int newkey, int hashsize) {
  int oldindex = hash(oldkey, hashsize);
  int newindex = hash(newkey, hashsize);
  struct node *a = ht[oldindex], *b = NULL;
  while (a != NULL && a->data != oldkey) {
    b = a;
    a = a->next;
  }
  if (a == NULL) {
    printf("-1\n");
    return;
  }
  struct node *temp = ht[newindex];
  while (temp != NULL) {
    if (temp->data == newkey) {
      printf("-1\n");
      return;
    }
    temp = temp->next;
  }
  int index = hash(oldkey, hashsize);
  struct node *p = ht[index], *q = NULL;
  int pos = 1;
  while (p != NULL && p->data != oldkey) {
    q = p;
    p = p->next;
    pos++;
  }
  if (q == NULL){ 
    ht[index] = p->next;
  }
  else{ 
    q->next = p->next;
  }
  free(p);
  printf("%d %d\n",oldindex, pos);
  sortedhashtable(ht, newkey, hashsize); 
}

// print the chain according to the index
void printhashchain(struct node *ht[], int index, int hashsize) {   
  if (index >= 0 && index < hashsize) {
    struct node *p = ht[index];
    while (p != NULL) {
      printf("%d ", p->data);
      p = p->next;
    }
    if(ht[index] == NULL)
      printf("-1");
    printf("\n");
  }
}
// main
int main(){
  char op;
  int hashsize;
  scanf("%d",&hashsize);
  struct node *ht[hashsize];
  bool duplicates[100] = {false};
  int index;
  for (int i = 0; i < hashsize; i++)
    ht[i] = NULL;

  while (1){
    scanf(" %c", &op);
    switch (op) {
      case 'i':{
        int a;
        scanf("%d",&a);
        index = hash(a, hashsize);
        if(!duplicates[a]){ 
        	sortedhashtable(ht, a, hashsize); // check for duplicates
        	duplicates[a] = true;
        }
        else
        	printf("-1\n");
        break;
      }
      case 'd':{
        int b;
        scanf("%d",&b);
        delete(ht, b, hashsize);
        duplicates[b] = false; // revert back the value in the hashtable
        break;
      }
      case 'u':{
        int oldkey, newkey;
        scanf("%d %d",&oldkey, &newkey);
        updatehash(ht, oldkey, newkey, hashsize);
        break;
      }
      case 's':{
        int key;
        scanf("%d",&key);
        search(ht, key, hashsize);
        break;
      }
      case 'p':{
        int index;
        scanf("%d",&index);
        if(index < hashsize)
          printhashchain(ht, index, hashsize);
        break;
      }
      case 'e':
        return 0;
    }
  }
}
