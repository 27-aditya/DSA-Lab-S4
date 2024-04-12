#include <stdio.h>
#include <stdbool.h>
// chuck for prime
bool prime(int num) {
  if (num <= 1) return false; 
  for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) return false;
  }
  return true;
}
// smallest and nearest priime
int nearestsmallerprime(int num) {
  if (num <= 1) return -1; 
  for (int i = num - 1; i >= 2; i--)
    if (prime(i)) return i; 
  return -1;
}
// hash function
int hash(int key, int size) {

  return key % size;
}
// linear probe with pointer for collisiions
int linearprobe(int a[], int key, int size, int *collisions){
  int index = hash(key, size);
  int i = 0;
  while(a[(index + i) % size] != -1 && i < size){
    i++;
    (*collisions)++;
  }
  return (index + i) % size;
}
/*int probe(int a[], int key){
  
  int index = hash(key);
  int i = 0;
  while(a[(index + i) % size] != -1 && i < size)
    i++;
  return (index + i) % size;
}*/
// quadratic probe with pointer for collisiions
int quadraticprobe(int a[], int key, int size, int *collisions){ 
  int index = hash(key, size);
  int i = 0;
  while(a[(index + i*i) % size] != -1 && i < size){
    i++;
    (*collisions)++;
  }
  return (index + i*i) % size;
}
// double hash with pointer for collisiions
int doublehash(int a[], int key, int size, int *collisions){
  int r = nearestsmallerprime(size);
  int index1 = hash(key,size);
  int index2 = r - (key % r);
  int i = 0;
  while(a[(index1 + i*index2) % size] != -1 && i < size){
    i++;
    (*collisions)++;
  }
  return (index1 + i*index2) % size;
}
// insert using linear probe
void insertlinear(int ht[], int key, int size, int *collisions){
  int index = hash(key, size);

  while (ht[index] != -1) {
    index = linearprobe(ht, key, size, collisions);
  }

  ht[index] = key;
  printf("%d ",index);
}
// insert using quadratic probe
void insertquadratic(int ht[], int key, int size, int *collisions){
  int index = hash(key, size);

  if(ht[index] != -1){
    index = quadraticprobe(ht, key, size, collisions);
  }
  ht[index] = key;
  printf("%d ",index);
}
// insert using double hash
void insertdouble(int ht[], int key, int size, int *collisions){
  int index = hash(key, size);

  if(ht[index] != -1){
    index = doublehash(ht, key, size, collisions);
  }
  ht[index] = key;
  printf("%d ", index);
}

int main(){
  int size;
  int arr[100];
  // collisions pointers
  int lcollisions = 0;
  int qcollisions = 0;
  int dcollisions = 0;
  scanf("%d",&size);

  int ht1[100];
  int ht2[100];
  int ht3[100];
  // initialize the array
  for(int i = 0; i < size; i++){ 
    ht1[i] = -1;
    ht2[i] = -1;
    ht3[i] = -1;
  }
  for(int i = 0; i < size-1; i++)
    scanf(" %d",&arr[i]);
  // linear probe case
  for(int i = 0; i < size-1; i++)
    insertlinear(ht1, arr[i], size, &lcollisions);
  printf("\n");
  printf("%d\n", lcollisions);
  // quadratic probe case
  for(int i = 0; i < size-1; i++)
    insertquadratic(ht2, arr[i], size, &qcollisions);
  printf("\n");
  printf("%d\n", qcollisions);
  // double hash case
  for(int i = 0; i < size-1; i++)
    insertdouble(ht3, arr[i], size, &dcollisions);
  printf("\n");
  printf("%d\n", dcollisions);
  return 0;
}
