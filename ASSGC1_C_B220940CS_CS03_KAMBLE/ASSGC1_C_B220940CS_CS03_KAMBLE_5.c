#include <stdio.h>
// count the distinct integers in the first window
void countdistinct(int n, int k, int arr[], int index){
  int window[100] = {0};
  int count = 0;
  // chuck for the first window
  for (int i = index; i < index+k; i++){
    if(window[arr[i]] == 0)
      count++;
    window[arr[i]]++;
  }
  printf("%d ",count);
  // increase the index and check for the net window
  if(index + k < n) // termiantion case as the last window also need to be of size k
    countdistinct(n, k, arr, index+1); // increased the value of index to go to the next window
}
/*void countdistinct(int n, int k, int arr[], int index){
  int window[100] = {0};
  int count = 0;
  for (int i = index; i < index+k; i++){
    if(window[arr[i]] == 0)
      count++;
    window[arr[i]]++;
  }
  printf("%d ",count); 
  countdistinct(n, k, arr, index+1); 
}*/
// wrapper function for count distinct just passes index value and calls the function
void countdistinctwrapper(int n, int k, int arr[]){
  int index = 0;
  countdistinct(n, k, arr, index);
}

int main(){
  int n, k;
  scanf("%d %d",&n ,&k);
  int arr1[100];
  for (int i = 0; i < n; i++)
    scanf("%d",&arr1[i]); 
  
  countdistinctwrapper(n, k, arr1);
}
