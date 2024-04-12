#include <stdio.h>
#include <stdlib.h>

// node structure
struct node {
  int dest;
  struct node* next;
};

// adjacency list structure
struct adjlist {
  struct node* head;
};

// graph structure
struct graph {
  int v;
  struct adjlist* array;
};

// create adjlistnode
struct node* newnode(int dest) {
  struct node* new_node = (struct node*)malloc(sizeof(struct node)); // allocate memory
  new_node->dest = dest; // set the edge
  new_node->next = NULL;
  return new_node; // return the node
}

// create graph
struct graph* creategraph(int v) {
  struct graph* g = (struct graph*)malloc(sizeof(struct graph)); // allocate memory
  g->v = v;
  g->array = (struct adjlist*)malloc(v * sizeof(struct adjlist));
  
  for (int i = 0; i < v; ++i) // initialize to null
    g->array[i].head = NULL;
  
  return g;
}

// function for adding edges
void edgeadd(struct graph* g, int src, int dest) {
  struct node* new_node = newnode(dest); // allocate memory
  new_node->next = g->array[src].head; // add node to the list
  g->array[src].head = new_node; // set the head pointer

  // undirected graph has both way edges
  new_node = newnode(src);
  new_node->next = g->array[dest].head;
  g->array[dest].head = new_node;
}

// convert adjacency list to adjacency matrix
int** createadjmatrix(struct graph* g) {
  int v = g->v; // store vertices
  int** matrix = (int**)malloc(v * sizeof(int*)); // allocate memory

  // if node is not null add 1 in the adj matrix.
  for (int i = 0; i < v; ++i) {
    matrix[i] = (int*)calloc(v, sizeof(int));
    struct node* current = g->array[i].head;
    while (current) {
      matrix[i][current->dest] = 1;
      current = current->next;
    }
  }

  return matrix;
}

// print the adjacency matrix
void printmatrix(int** matrix, int v) {
  for (int i = 0; i < v; ++i) {
    for (int j = 0; j < v; ++j)
      printf("%d ", matrix[i][j]);
    printf("\n");
  }
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

void printallpathsdfs(int vertex, int** graph, int* visited, int v, int dest, int* path, int path_index, int* found_paths) {
  visited[vertex] = 1; // maintain a visited hash
  path[path_index] = vertex; // store in the path array
  path_index++; // move to next index

  if (vertex == dest) { // termination condition if destination reached
    for (int i = 0; i < path_index; ++i) {
      printf("%d ", path[i]);
    }
    printf("\n");
    *found_paths = 1; // Update found_paths to indicate a path was found
  } else {
    for (int i = 0; i < v; ++i) {
      if (graph[vertex][i] && !visited[i]) { // check for not visited vertices in the graph
        printallpathsdfs(i, graph, visited, v, dest, path, path_index, found_paths); // traverse them with dfs
      }
    }
  }

  visited[vertex] = 0; // reset all the visited for other calls
}

// wrapper function to print all paths
void printallpaths(struct graph* g, int src, int dest) {
  int v = g->v;
  int** matrix = createadjmatrix(g); // adjacency matrix
  int* visited = (int*)calloc(v, sizeof(int)); // visited hash
  int* path = (int*)malloc(v * sizeof(int)); // path array 
  int path_index = 0;
  int found_paths = 0;

  printallpathsdfs(src, matrix, visited, v, dest, path, path_index, &found_paths); // calling the function

  // Check if any paths were found
  if (!found_paths) {
    printf("-1\n");
  }

  // deleting after the function is completed
  free(visited);
  free(path);
  for (int i = 0; i < v; ++i)
    free(matrix[i]);
  free(matrix);
}


// dfs traversal
void dfs(int vertex, int** graph, int* visited, int v) {
  visited[vertex] = 1;
  for (int i = 0; i < v; ++i) {
    if (graph[vertex][i] && !visited[i])
      dfs(i, graph, visited, v);
  }
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


// valid tree function
int isvalidtree(int** graph, int v) {
  int* visited = (int*)calloc(v, sizeof(int));
  int components = 0;

  // check if all nodes are visited
  for (int i = 0; i < v; ++i) {
    if (!visited[i]) {
      components++;
      dfs(i, graph, visited, v);
    }
  }

  // tree has one less edge than the number of vertices
  int edge_count = 0;
  for (int i = 0; i < v; ++i) {
    for (int j = i + 1; j < v; ++j) {
      if (graph[i][j])
        edge_count++;
    }
  }

  //delete the array
  free(visited);

  if (edge_count == v - 1 && components == 1)
    return 1; // valid tree
  else
    return -1; // not valid tree
}

// function menu
int main() {
  int v;
  scanf("%d", &v);

  // creating graph 
  struct graph* g = creategraph(v);

  // input adjacency list
  for (int i = 0; i < v; ++i) {
    int node, adj;
    scanf("%d", &node);
    while (1) {
      char next_char;
      if ((next_char = getchar()) == '\n') // check for enter
        break;
      ungetc(next_char, stdin); // input buffer
      scanf("%d", &adj);
      edgeadd(g, node, adj); // add the edges
    }
  }

  // making the adjacency matrix
  int** matrix = createadjmatrix(g);

  char op;
  while (1) {
    scanf("%c", &op);
    switch (op) {
    case 'a':
      int src, dest;
      scanf("%d %d", &src, &dest);
      printallpaths(g, src, dest);
    break;

    case 't':
      printf("%d\n", isvalidtree(matrix, v));
      break;

    case 'x':
      return 0;
    }
  }

  // free the matrix
  for (int i = 0; i < v; ++i)
    free(matrix[i]);
  free(matrix);

  return 0;
}
