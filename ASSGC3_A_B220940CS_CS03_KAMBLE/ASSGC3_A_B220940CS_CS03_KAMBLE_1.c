#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// node 
struct node {
  int dest;
  struct node* next;
};

// adjacency list
struct adjlist {
  struct node* head;
};

// graph -> array of adjacency list
struct graph {
  int v;
  struct adjlist* array;
};

// function for creating newnode
struct node* newnode(int dest) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node));
  new_node->dest = dest;
  new_node->next = NULL;
  return new_node;
}

// function for creating graph
struct graph* creategraph(int v) {
  struct graph* g = (struct graph*)malloc(sizeof(struct graph));
  g->v = v;
  g->array = (struct adjlist*)malloc(v * sizeof(struct adjlist));
  
  for (int i = 0; i < v; ++i)
    g->array[i].head = NULL; // initialize all pointers to NULL
  
  return g;
}

// function for adding edges in the list
void edgeadd(struct graph *graph, int src, int dest){
  struct node *nnode = newnode(dest); // add edge from src to dest
  nnode->next = graph->array[src].head;
  graph->array[src].head = nnode;

  struct node *dnode = newnode(src); // for undirected add edge from dest to src as well 
  dnode->next = graph->array[dest].head;
  graph->array[dest].head = dnode;
}

// function for creating matrix from adj list
int **creatematrix(struct graph *g){
  int vertex = g->v;
  int **matrix = (int **)malloc(vertex * sizeof(int *)); // allocate memory
  // loop for traversing the list
  for (int i = 0; i < vertex; i++) {
    struct node *current = g->array[i].head;
    matrix[i] = (int*)calloc(vertex, sizeof(int));
    // if edge exists put 1 in the matrix
    while (current) {
      matrix[i][current->dest] = 1;
      current = current->next;
    }
  }
  return matrix;  
}

/*void dfs(int g[][7], int start, int n){
  int i = start;
  int j;
  static int visited[7] = {0};
  if(visited[i] == 0){
    printf("%d ",i);
    visited[i] = 1;
    for(j = 1; j < n; j++){
      if(g[i][j] == 1 && visited[j] == 0)
        dfs(g, j, n);
    }
  }
}*/

// dfs function for number of components
void dfscc(struct graph *g, int *visited, int v, int **matrix){
  visited[v] = 1; // mark node as visited
  for (int i = 0; i < g->v; i++) {
    if (matrix[v][i] && !visited[i]) // if not visited and exists then traverse with dfs
      dfscc(g, visited, i, matrix); // recursive dfs call
  }
}

// function for calculating number of components
int noofcomponents(struct graph *g){
  int *visited = (int *)malloc(g->v * sizeof(int)); // visited hash
  int count = 0;
  int **matrix = creatematrix(g);

  for (int v = 0; v < g->v; v++)
    visited[v] = 0;  

  for (int i = 0; i < g->v; i++) {
    // if not visited then the increase the count by 1 as new component found
    if (!visited[i]) { 
      count++;
      dfscc(g, visited, i, matrix); // call for dfs
    }
  }

  // free memory from heap
  free(visited);
  for (int i = 0; i < g->v; i++)
    free(matrix[i]);
  free(matrix);

  return count;
}

// dfs function for size of components
void dfsizes(struct graph *g, int *visited, int v, int *size, int **matrix){
  visited[v] = 1;
    // increment size for the current vertex
  (*size)++;
  for (int i = 0; i < g->v; i++) {
    if (matrix[v][i] && !visited[i]) {
      dfsizes(g, visited, i, size, matrix); // recursive call
    }
  }
}

// function to print the sizes of components
void sizeofcomponents(struct graph *g){
  int *visited = (int *)malloc(g->v * sizeof(int)); // allocate memory
  // initialize to 0
  for (int i = 0; i < g->v; i++)
    visited[i] = 0;

  int *sizes = (int *)malloc(g->v *sizeof(int)); // allocate memory
  int components = 0; // initialize  counter

  for (int i = 0; i < g->v; i++) {
    if (!visited[i]) {
      int size = 0;
      dfsizes(g, visited, i, &size, creatematrix(g)); // calculate size of current component
      sizes[components++] = size; // store in sizes array
    }
  }

  // sort sizes in ascending order
  for (int i = 0; i < components - 1; i++) {
    for (int j = 0; j < components - i - 1; j++) {
      if (sizes[j] > sizes[j + 1]) {
        int temp = sizes[j];
        sizes[j] = sizes[j + 1];
        sizes[j + 1] = temp;
      }
    }
  }

  // print sizes of components
  for (int i = 0; i < components; i++)
    printf("%d ", sizes[i]);
  printf("\n");

  // free allocated memory
  free(visited);
  free(sizes);
}


// dfs for finding number of bridges
void dfsbridges(struct graph* graph, int u, bool visited[], int parent[], int low[], int disc[], int* bridges, int* time) {
  int **adj = creatematrix(graph); // create matrix
  visited[u] = true; 
  disc[u] = low[u] = (*time)++; // initialize discovery time and low value for the current node
  for (int v = 0; v < graph->v; v++) { 
    if (adj[u][v]) { // check edge between nodes u and v
      if (!visited[v]) {
        parent[v] = u; // set parent of v as u
        dfsbridges(graph, v, visited, parent, low, disc, bridges, time); // recursive call
        low[u] = low[u] < low[v] ? low[u] : low[v];
        if (low[v] > disc[u]) // check for bridge
          (*bridges)++; // increment counter
      } 
      else if(v != parent[u]) { 
        low[u] = low[u] < disc[v] ? low[u] : disc[v]; // update low value of u
      }
    }
  }
}

// function to print number of bridges in graph
int noofbridges(struct graph* graph) {
  // allocate memory 
  bool* visited = (bool*)malloc(graph->v * sizeof(bool)); 
  int* parent = (int*)malloc(graph->v * sizeof(int)); 
  int* low = (int*)malloc(graph->v * sizeof(int)); 
  int* disc = (int*)malloc(graph->v * sizeof(int)); 
  int bridges = 0; 
  int time = 0; 

  // initialize visited, parent, and disc arrays
  for (int i = 0; i < graph->v; i++) {
    visited[i] = false;
    parent[i] = -1;
  }

  // dfs to find bridges
  for (int i = 0; i < graph->v; i++) {
    if (!visited[i])
      dfsbridges(graph, i, visited, parent, low, disc, &bridges, &time);
  }

  // free memory alloted in heap
  free(visited);
  free(parent);
  free(low);
  free(disc);
  
  // return the number of bridges.
  return bridges > 0 ? bridges : -1;
}

// dfs for articulation points
void dfsarticulation(struct graph* graph, int u, bool visited[], int parent[], bool ap[], int low[], int disc[], int* time) {
  int **adj = creatematrix(graph); // create matrix
  visited[u] = true; 
  int children = 0; // initialize children count
  disc[u] = low[u] = (*time)++; 
  for (int v = 0; v < graph->v; v++) { 
    if (adj[u][v]) { 
      if (!visited[v]) { 
        children++; // increment children count
        parent[v] = u; // set parent of v as u
        dfsarticulation(graph, v, visited, parent, ap, low, disc, time); // recursive call
        low[u] = low[u] < low[v] ? low[u] : low[v]; 
        if (parent[u] == -1 && children > 1) 
          ap[u] = true; 
        if (parent[u] != -1 && low[v] >= disc[u])
          ap[u] = true; 
      }
      else if (v != parent[u]) { 
        low[u] = low[u] < disc[v] ? low[u] : disc[v]; 
      }
    }
  }
}

// function to print number of articulation points
int nooofarticulationpoints(struct graph* graph) {
  // allocate memory
  bool* visited = (bool*)malloc(graph->v * sizeof(bool)); 
  int* parent = (int*)malloc(graph->v * sizeof(int)); 
  int* low = (int*)malloc(graph->v * sizeof(int)); 
  int* disc = (int*)malloc(graph->v * sizeof(int)); 
  bool* ap = (bool*)malloc(graph->v * sizeof(bool)); 
  // initialize variables
  int time = 0; 
  int count = 0; 

  // initialize visited hash, parent, and ap arrays
  for (int i = 0; i < graph->v; i++) {
    visited[i] = false;
    parent[i] = -1;
    ap[i] = false;
  }

  // perform dfs
  for (int i = 0; i < graph->v; i++) {
    if (!visited[i])
      dfsarticulation(graph, i, visited, parent, ap, low, disc, &time);
  }

  // count the articulation points
  for (int i = 0; i < graph->v; i++) {
    if (ap[i])
      count++;
  }

  // free memory alloted in heap
  free(visited);
  free(parent);
  free(low);
  free(disc);
  free(ap);

  // return number of count
  return count > 0 ? count : -1;
}


/*void bfs(int g[][7], int start, int n){
  int i = start;
  int j;
  struct queue q;
  create(&q, n);
  int visited[7] = {0};

  printf("%d ",i);
  visited[i] = 1;
  enqueue(&q,i);

  while (!isempty(q)){
    i = dequeue(&q);
    for(j = 1; j < n; j++){
      if(g[i][j] == 1 && visited[j] == 0){
        printf("%d ",j);
        visited[j] = 1;
        enqueue(&q, j);
      }
    }
  }
}*/


int main() {
  int v;
  scanf("%d", &v);

  struct graph* g = creategraph(v);

  for (int i = 0; i < v; ++i) {
    int node, adj;
    scanf("%d", &node);
    while (1) {
      char next_char;
      if ((next_char = getchar()) == '\n')
        break;
      ungetc(next_char, stdin);
      scanf("%d", &adj);
      edgeadd(g, node - 1, adj - 1); // adjust for nodes startiing with 1
    }
  }

  // menu 
  char op;
  while (1) {
    scanf(" %c", &op);
    switch (op) {
      case 'n':
        printf("%d\n", noofcomponents(g));
      break;
      case 's':
        sizeofcomponents(g);
      break;
      case 'b':
        printf("%d\n", noofbridges(g));
      break;
      case 'a':
        printf("%d\n", nooofarticulationpoints(g));
      break;
      case 't':
        return 0;
      }
  }
}