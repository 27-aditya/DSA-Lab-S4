#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define parameters
#define infi 999999 
#define maxnode 100

// structure for node
struct node {
  int dest;
  int weight;
  struct node* next;
};

// strucuture for adjacency list
struct adjlist {
  struct node* head;
};

// structure for graph
struct graph {
  int v;
  struct adjlist* array;
};

// function for creating newnode with weight and destination
struct node* newnode(int dest, int weight) {
  struct node* nnode = (struct node*)malloc(sizeof(struct node)); // allocate storage
  nnode->dest = dest; // add destination
  nnode->weight = weight; // add weight
  nnode->next = NULL; 
  return nnode; 
}

// function for creating a graph
struct graph* newgraph(int v) {
  struct graph* g = (struct graph*)malloc(sizeof(struct graph)); // allocate storage
  g->v = v; // specify vertices
  g->array = (struct adjlist*)malloc(v * sizeof(struct adjlist)); // allot storage 

  for (int i = 0; i < v; i++)
    g->array[i].head = NULL; // initialize

  return g;
}

// function for adding edges in the graph
void edgeadd(struct graph* g, int src, int dest, int weight) {
  // adds the newnode to the head of the list
  struct node* nnode = newnode(dest, weight);
  nnode->next = g->array[src].head;
  g->array[src].head = nnode;
    
  // for undirected graph both way edges required
  struct node *dnode = newnode(src, weight);
  dnode->next = g->array[dest].head;
  g->array[dest].head = dnode;
}

// function to create adjacency matrix
int** createadjmatrix(struct graph* g) {
  int v = g->v;
  int** matrix = (int**)malloc(v * sizeof(int*)); // allot storage

  for (int i = 0; i < v; i++) {
    matrix[i] = (int*)malloc(v * sizeof(int)); 
    for (int j = 0; j < v; j++) {
      if (i == j)
        matrix[i][j] = 0; // diagonal has 0 weight as no self loops
      else
        matrix[i][j] = infi; // initialize to infinity else
    }
    struct node* current = g->array[i].head;
    while (current != NULL) {
      matrix[i][current->dest] = current->weight; // update the weights
      current = current->next;
    }
  }
  return matrix;
}

// function for calculating the minimum distance in the graph
int mindist(int vertex, int* dist, int* included) {
  int min = infi, index;

  // check for the not included edge with the minimum edge
  for (int i = 0; i < vertex; i++) {
    if (included[i] == 0 && dist[i] < min) {
      min = dist[i];
      index = i;
    }
  }
  return index; // return its index
} 

// dijkstras algorithm 
void dijkstra(struct graph* g, int vertex, int src) {
  // allot storage
  int* dist = (int*)malloc(vertex * sizeof(int));
  int* visited = (int*)malloc(vertex * sizeof(int));
  int** graph = createadjmatrix(g);

  // initialize the arrays
  for (int i = 0; i < vertex; i++) {
    dist[i] = infi;
    visited[i] = 0;
  }

  // put distance from the src as zero
  dist[src] = 0; 

  // find the edge with min weight
  for (int i = 0; i < vertex - 1; i++) {
    int u = mindist(vertex, dist, visited);

    visited[u] = 1; // mark it as visited

    // if not visited and the it has an edge also if the distance is less in the roundabout way update it
    for (int v = 0; v < vertex; v++) {
      if (!visited[v] && graph[u][v] != infi && dist[u] != infi && (dist[u] + graph[u][v] < dist[v]))
        dist[v] = dist[u] + graph[u][v];
    }
  }

  // print loop
  for (int i = 0; i < vertex; i++)
    printf("%d ", dist[i]);
  printf("\n");

  // free the alloted memory
  free(dist);
  free(visited);
}

/*void dijkstra(int graph[V][V], int src)
{
    int dist[V]; 
    bool sptSet[V]; 
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
}*/

// main function
int main() {
  int n;
  scanf("%d", &n);
  getchar(); 

  struct graph* g = newgraph(n);

  char str[maxnode][100];
  for (int i = 0; i < n; i++) {
    fgets(str[i], 100, stdin);
  }
  char str1[maxnode][100];
  for (int i = 0; i < n; i++) {
    fgets(str1[i], 100, stdin);
  }

  for (int i = 0; i < n; i++) {
    int a = 0;
    int k = 0;
    while (k < strlen(str[i]) && str[i][k] <= '9' && str[i][k] >= '0') {
      a = a * 10 + str[i][k] - '0';
      k++;
    }
    k++;
    int j = k;
    while (k < strlen(str[i])) {
      int b = 0;
      while (k < strlen(str[i]) && str[i][k] <= '9' && str[i][k] >= '0') {
        b = b * 10 + str[i][k] - '0';
        k++;
      }
      k++;
      int wt = 0;
      while (j < strlen(str1[i]) && str1[i][j] <= '9' && str1[i][j] >= '0') {
        wt = wt * 10 + str1[i][j] - '0';
        j++;
      }
      j++;
      if (a < b) edgeadd(g, a - 1, b - 1, wt); 
    }
  }
  
  int s;
  scanf("%d", &s);

  dijkstra(g, n, s - 1); //  call the algorithm

  // free the storage
  int** matrix = createadjmatrix(g);
  for (int i = 0; i < n; i++)
    free(matrix[i]);
  free(matrix);

  return 0;
}
