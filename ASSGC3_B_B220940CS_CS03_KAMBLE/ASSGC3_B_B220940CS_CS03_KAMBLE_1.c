#include <stdio.h>

# define infi 32768 // define infinite 
# define maxnode 100 // define maxnode

// prims algorithm 
void prims(int matrix[][maxnode], int n, int start, int flag){
  int sum = 0; 
  int i, j, k, u;
  int min = infi;
  int near[n];
  int edges[2][n];
  
  for (int i = 0; i < n; i++) // initialize near array
    near[i] = infi;
  
  // check for the min weight edge along with the start vertex
  for(i = 0; i < n; i++){
    if(matrix[start][i] < min){
      min = matrix[start][i];
      u = i;
    }
  }
  
  // update near array as selected
  near[start] = -1;
  // include in the edges matrix
  edges[0][0] = start; 
  edges[1][0] = u;
  near[u] = -1;

  // refill the near matrix by checking the vertices are closer to which vertex
  for(i = 0; i < n; i++){
    if(near[i] != -1){
      if(matrix[i][start] < matrix[i][u]) // if closer to start
        near[i] = start;
      else // if closer to u
        near[i] = u;
    }
  }

  // check for rest of the edges in the same manner
  for (i = 0; i < n-1; i++){
    min = infi;
    // find next min weight edge
    for(j = 0; j < n; j++){
      if(near[j] != -1 && matrix[j][near[j]] < min){
        min = matrix[j][near[j]];
        k = j;
      }
    }

    // update the edges and near
    edges[0][i+1] = near[k];
    edges[1][i+1] = k;
    near[k] = -1;

    // update the near matrix as done before
    for (j = 0; j < n; j++){
      if(near[j] != -1 && matrix[j][k] < matrix[j][near[j]])
        near[j] = k;
    }
  }
  // chose flag to either print sum or edges path
  if(flag){
    for (int i = 0; i < n-1; i++)
      printf("%d %d ",edges[0][i],edges[1][i]);
  }
  else{
    for(i = 0; i < n; i++)
      sum += matrix[edges[0][i]][edges[1][i]];
    printf("%d\n",sum);
  }
}

/*int prims(){for ( i = 1; i < n; i++){
    for(j = i; j < n; j++){
      if(cost[i][j] < min){
        min = cost[i][j];
        u = i;
        v = j;
      }
    }
  }
  t[0][0] = u;
  t[1][0] = v;
  near[u] = near[v] = 0;
  for (i = 1; i <= n; i++){
    if(near[i] != 0){
      if(cost[i][u] < cost[i][v])
        near[i] = u;
      else
        near[i] = v;
    }
  }
  for (i = 1; i < n-1; i++){
    min = I;
    for (j = 1; j <= n; j++){
      if(near[j] != 0 && cost[j][near[j]] < min){
        min = cost[j][near[j]];
        k = j;
      }
    }
    t[0][i] = k; t[1][i] = near[k];
    near[k] = 0;
    for (j = 1; j <= n; j++){
      if(near[j] != 0 && cost[j][k] < cost[j][near[j]])
        near[j] = k;
    }
}*/

// main function with menu
int main(){
  int num;
  int n;
  char ip[10];
  scanf("%d",&n);
  int matrix[maxnode][maxnode];
  for(int i = 0; i < n;  i++){
    for (int j = 0; j < n; j++){
      scanf("%d",&num);
      if(num == 0)
        matrix[i][j] = infi;
      else
        matrix[i][j] = num;
    }
  }
  char op;
  while(1){
    scanf("%c",&op);
    if(op == 't')
      prims(matrix, n, 0 ,0);
    else if(op == 's'){
      int inp;
      scanf("(%d)",&inp);
      prims(matrix, n, inp, 1);
    }
    else if(op == 'x')
      return 0;
  }
}