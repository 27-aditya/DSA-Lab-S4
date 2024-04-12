#include <stdio.h>
#include <stdbool.h>

#define size 20

// max 
int max(int m, int n){
  return (m>n) ? m : n;
}
// hash function
int hash(int key){
  return key % size;
}
// linear probe
int probe(int a[], int key){
  
  int index = hash(key);
  int i = 0;
  while(a[(index + i) % size] != -1 && i < size)
    i++;
  return (index + i) % size;
}
// insert usin linear probe
void insert(int ht[], int key){
  int index = hash(key);

  if(ht[index] != -1){
    index = probe(ht, key);
  }
  ht[index] = key;
}
/*void sortedinsert(struct node **h, int key) {
  struct node *p, *q = NULL, *t = *h;
  p = (struct node *)malloc(sizeof(struct node));
  if (!p) {
    return;
  }
  p->next = NULL;
  p->data = key;

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
}*/
// search using linear probe
int search(int a[], int key){
  int index = hash(key);
  int i = 0;
  while(a[(index + i) % size] != key && i < size) // linear probe
    i++;
  if(a[(index + i) % size] == key)
    return (index + i) % size;
  return -1;
}
/*void search(int ht[], int key, int hashsize) {
  int pos = 0;
  bool found = false;
  int index = hash(key, hashsize);
  int current = ht[index];
  while (current != NULL) {
    if (key == current) {
      printf("%d %d\n", index, pos);
      found = true;
      return;
    }
    current = current++;
    pos++;
  }
  if (!found)
    printf("-1\n");
}*/
// take one array hash it comapre with second
void unionab(int arr1[], int arr2[], int size1, int size2){
  int ht1[size] = {-1};
  bool duplicate[size] = {false};
  for(int i = 0; i < size1; i++){
      if(!duplicate[arr1[i]]){ 
      insert(ht1, arr1[i]);
      printf("%d ", arr1[i]);
      duplicate[arr1[i]] = true;
    }
  }

  for(int i = 0; i < size2; i++){
    if(!duplicate[arr2[i]]){
      printf("%d ", arr2[i]);
      insert(ht1, arr2[i]);
      duplicate[arr2[i]] = true;
    }
  }
}
// take one array hash it intersect it with the second
void intersectionab(int arr1[], int arr2[], int size1, int size2){
  int ht1[size] = {-1};
  int s = 0;
  bool duplicate[size] = {false};
  for(int i = 0; i < size1; i++){
    insert(ht1, arr1[i]);
  }

  for(int i = 0; i < size2; i++){
    if((search(ht1, arr2[i]) != -1) && !duplicate[arr2[i]]){ 
      printf("%d ", arr2[i]);
      duplicate[arr2[i]] = true;
      s++;
    }
  }
  if(s == 0)
    printf("-1");
}
// take one array hash it substract it from the other
void differenceab(int arr1[], int arr2[], int size1, int size2){
  int ht1[size] = {-1};
  int s = 0;
  bool duplicates[size] = {false};
  for(int i = 0; i < size2; i++){
    if(!duplicates[arr2[i]]){ 
      insert(ht1, arr2[i]);
      duplicates[arr2[i]] = true;
    }
  }
  for(int i = 0; i < size1; i++){
    if((search(ht1, arr1[i]) == -1) && !duplicates[arr1[i]]){ 
      printf("%d ", arr1[i]);
      duplicates[arr1[i]] = true;
      s++;
    }
  }
  if(s==0)
    printf("-1");
}
// main
int main(){
  int m, n;
  scanf("%d %d", &m, &n);
  int arr1[100];
  int arr2[100];
  for (int i = 0; i < m; i++)
    scanf("%d", &arr1[i]);

  for (int i = 0; i < n; i++)
    scanf("%d", &arr2[i]);
  char op;
  while (1){
    scanf(" %c", &op);
    switch (op) {
      char a, b;
      case 'u':{
        scanf(" %c %c", &a, &b);
        if (a == 'A' && b == 'B')
          unionab(arr1, arr2, m, n);
        else
          unionab(arr2, arr1, n, m);
        printf("\n");
        break;
      }
      case 'i':{
        scanf(" %c %c", &a, &b);
        if (a == 'B' && b == 'A')
          intersectionab(arr1, arr2, m, n);
        else
          intersectionab(arr2, arr1, n, m);
        printf("\n");
        break;
      }
      case 's':{
        scanf(" %c %c", &a, &b);
        if (a == 'A' && b == 'B')
          differenceab(arr1, arr2, m, n);
        else
          differenceab(arr2, arr1, n, m);
        printf("\n");
        break;
      }
      case 'e':
        return 0;
    }
  }
}
