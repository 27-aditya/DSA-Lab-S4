#include <stdio.h>
#include <stdlib.h>

// define the parameters
# define infi 32768

// structure for node
struct node{
  int dest;
  int weight;
  struct node *next;
};

// structure for list
struct adjlist{
  struct node *head;
};

// structure for graph
struct graph{
  int v;
  struct adjlist *array;
};

// funciton for creating newnode
struct node *newnode(int dest, int weight){
  struct node *nnode = (struct node *)malloc(sizeof(struct node));
  nnode->dest = dest; // update destination
  nnode->weight = weight; // update weight
  nnode->next = NULL;
  return nnode;
}

// function for creating graph
struct graph *creategraph(int v){
  // allot storage
  struct graph* g = (struct graph*)malloc(sizeof(struct graph));
  g->v = v;
  g->array = (struct adjlist*)malloc(v * sizeof(struct adjlist));

  // initialize head pointers to NULL
  for (int i = 0; i < v; ++i)
    g->array[i].head = NULL; 

  return g;
}

// function fo radding egdes to the graph
void edgeadd(struct graph* graph, int src, int dest, int weight) {
  struct node* nnode = newnode(dest, weight); 
  nnode->next = graph->array[src].head; 
  graph->array[src].head = nnode;
}

// function for creating edge matrix
int **createedgematrix(struct graph *g, int *edges){
  int v = g->v;
  int **edgematrix = NULL;

  *edges = 0;

  // calculate the number of edges 
  for (int i = 0; i < v; i++){
    struct node *temp = g->array[i].head;
    while(temp != NULL){
      (*edges)++;
      temp = temp->next;
    }
  }

  // allot storage
  edgematrix = (int **)malloc(3*sizeof(int *));
  for (int i = 0; i < 3; i++){
    edgematrix[i] = (int *)malloc(*edges * sizeof(int));
  }
  
  // fill the matrix by traversing the graph
  int edgeindex = 0;
  for (int i = 0; i < v; i++){
    struct node *temp = g->array[i].head;
    while (temp != NULL){
      if(i <= temp->dest){
        edgematrix[0][edgeindex] = i;
        edgematrix[1][edgeindex] = temp->dest;
        edgematrix[2][edgeindex] = temp->weight;
        edgeindex++;
      }
      temp = temp->next;
    }
  }
  return edgematrix;
}

// function for union 
void unio(int *set, int u, int v){
  if(set[u] < set[v]){ // unite the set with less number of components into the other one
    set[u] += set[v];
    set[v] = u;
  }
  else{
    set[v] += set[u];
    set[u] = v;
  }
}

// function to find the parent in the set
int find(int *set, int u){
  int x = u, v = 0;
  while (set[x] > 0){
    x = set[x]; // traverse until you find the parent
  }
  // if the given node is parent
  while(u != x){
    v = set[u];
    set[u] = x;
    u = v;
  }
  return x;
}

/*void unio(int u, int v){
  if (set[u] < set[v]){
    set[u] += set[v];
    set[v] = u;
  }
  else{
    set[v] += set[u];
    set[u] = v;
  }
}

int find(int u){
  int x = u, v = 0;
  while (set[x] > 0){
    x = set[x];
  }
  while(u != x){
    v = set[u];
    set[u] = x;
    u = v;
  }
  return x;
}*/

// kruskals algorithm
void kruskals(struct graph *g, int n){
  // initialize variables and allot storage
  int min, i, j, k, u, v, sum = 0;
  int edges = 0;
  int **edgematrix = createedgematrix(g, &edges);
  int *set = (int *)malloc(sizeof(int) *edges);
  int included[edges];
  int mst[2][n-1];
  for(i = 0; i < edges; i++){
    set[i] = -1;
    included[i] = 0;
  }
  i = 0;

  // loop to find the min weighted edge in the matrix which has not been included yet
  while(i < n-1){
    k = -1; // flag for checking if edge found
    min = infi;
    for(j = 0; j < edges; j++){
      if(included[j] == 0 && edgematrix[2][j] < min){ // if less weighted edge and not included include it
        min = edgematrix[2][j];
        u = edgematrix[0][j];
        v = edgematrix[1][j];
        k = j;
      }
    }

    // if edge found and parents are not same which means cannot form cycle
    // include into the mst matrix and increase the weighted sum of the path
    if(k != -1 && find(set, u) != find(set, v)){
      mst[0][i] = u;
      mst[1][i] = v;
      unio(set, find(set, u), find(set, v));
      sum += min;
      i++;
    }
    included[k] = 1; // mark the edge index as included
  }

  printf("%d",sum);
}

/*int kruskals(){nt i = 0, j, k, n = 7, e = 9, min, u , v;
  while (i < n-1){
    min = I;
    for (j = 0; j < e; j++){
      if(included[j] == 0 && edges[2][j] < min){
        min = edges[2][j];
        u = edges[0][j];
        v = edges[1][j];
        k = j;
      }
    }
    if(find(u) != find(v)){
      t[0][i] = u;
      t[1][i] = v;
      unio(find(u), find(v));
      i++;
    }
    included[k] = 1;
  }}*/

// main function
int main(){
  int n ;
  scanf("%d", &n);
  struct graph *g = creategraph(n);
  char str[n][100];
  for(int i = 0; i < n; i++){
    fgets(str[i],100,stdin);
  }
  char str1[n][100];
  for(int i = 0; i < n; i++){
    fgets(str1[i],100,stdin);
  }
  for(int i = 0;i<n;i++){
    int a = 0;
    int k = 0;
    while(k<strlen(str[i]) && str[i][k]<='9' && str[i][k]>='0'){
      a = a*10 + str[i][k] - '0';
      k++;
    }
    k++;
    int j = k;
    while(k < strlen(str[i])){
      int b = 0;
      while( k<strlen(str[i]) && str[i][k]<='9' && str[i][k]>='0'){
        b = b*10 + str[i][k] - '0';
        k++;
      }
      k++;
      int wt = 0;
      while( j<strlen(str1[i]) && str1[i][j]<='9' && str1[i][j]>='0'){
        wt = wt*10 + str1[i][j] - '0';
        j++;
      }
      j++;
      if(a<b)edgeadd(g,a,b,wt);
    }    
  }

  // calling the algorithm  
  kruskals(g, n);
}

