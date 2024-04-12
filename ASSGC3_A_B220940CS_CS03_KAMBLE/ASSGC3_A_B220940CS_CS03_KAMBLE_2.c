#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define maxnode 100

// structure for queue
struct queue{
  int data[maxnode];
  int front, rear;
};

// function for creating a queue
struct queue* createqueue() {
  struct queue* q = (struct queue*)malloc(sizeof(struct queue));
  q->front = -1; // initialize front and rear
  q->rear = -1;  
  return q;
}

// function for enqueuing 
void enqueue(struct queue* q, int item) {
  // check if queue full
  if (q->rear == maxnode - 1) {
    printf("queue is full\n");
    return;
  }
  // initial condition
  if (q->front == -1) {
    q->front = 0;
  }
  // add the number
  q->rear++;
  q->data[q->rear] = item;
}

// function for dequeue
int dequeue(struct queue* q) {
  // check for queue empty
  if (q->front == -1) {
    printf("queue is empty\n");
    return -1;
  }
  int item = q->data[q->front];
  q->front++;
  if (q->front > q->rear) {
    q->front = q->rear = -1;
  }
  return item;
}

// function for checking if queue is empty
bool isempty(struct queue* q) {
  return q->front == -1;
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

// bfs algorithm
void bfs(int adj[][maxnode], int start, int n) {
  int i = start;
  int j;
  // make a queue for storing
  struct queue* q = createqueue(); 
  int visited[n]; // visited hash
  for (int k = 0; k < n; k++) // initialize hash
    visited[k] = 0;
  // mark initial node as visited
  visited[i] = 1;
  printf("%d ", i);
  enqueue(q, i); // enqueue it 
  while (!isempty(q)) {
    i = dequeue(q);
    for (j = 0; j < n; j++) {
      // if there is an edge and it is not visited
      if (adj[i][j] == 1 && visited[j] == 0) {
        printf("%d ", j); // print it
        visited[j] = 1;
        enqueue(q, j); // add it to the queue
      }
    }
  }
}

// bfs algorithm which does not print but give back visited hash
void bfsc(int adj[][maxnode], int start, int n, int visited[]) {
  int i = start;
  int j;
  struct queue* q = createqueue(); 
  visited[start] = 1;
  enqueue(q, start);
  while (!isempty(q)) {
    i = dequeue(q);
    for (j = 0; j < n; j++) {
      if (adj[j][i] == 1 && visited[j] == 0) {
        visited[j] = 1;
        enqueue(q, j);
      }
    }
  }
}

// function for topological sort
bool istopologicalsortpossible(int graph[][maxnode], int n) {
  // array for degrees of nodes
  int indegree[maxnode] = {0};

  // loop for calculating the degrees of all the nodes
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (graph[i][j] == 1) {
        indegree[j]++;
      }
    }
  }

  // initialize a queue
  struct queue* q = createqueue();

  // add all the nodes with 0 degree to the queue
  for (int i = 0; i < n; ++i) {
    if (indegree[i] == 0) {
      enqueue(q, i);
    }
  }

  // count the components
  int count = 0; 

  // removing the nodes with 0 degree, updating the degrees of the nodes
  while (!isempty(q)) {
    int vertex = dequeue(q);
    count++;

    for (int i = 0; i < n; ++i) {
      if (graph[vertex][i] == 1) {
        indegree[i]--;
        if (indegree[i] == 0) {
          enqueue(q, i);
        }
      }
    }
  }

  // if the count is not equal to the number of vertices
  if (count != n) {
    return false;
  }

  return true;
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

// dfs algorithm
void dfs(int vertex, int graph[][maxnode], int n, bool visited[], struct queue* q) {
  visited[vertex] = true; // visited hash
  for (int i = 0; i < n; ++i) {
    // if edge exists and not visited
    if (graph[vertex][i] == 1 && !visited[i]) {
      dfs(i, graph, n, visited, q); 
    }
  }
  enqueue(q, vertex); // enqueue it into the queue
}

// dfs on the transpose graph which returns the number of components and the component hash
void dfs_reverse(int vertex, int graph[][maxnode], int n, bool visited[], int component[], int component_number) {
  visited[vertex] = true; // visited hash
  component[vertex] = component_number; // add the component number to the component hash
  for (int i = 0; i < n; ++i) {
    // if edge exists and not visited
    if (graph[i][vertex] == 1 && !visited[i]) {
      dfs_reverse(i, graph, n, visited, component, component_number);
    }
  }
}

// function to find out the number of strongly connected components
int numberofstronglyconnectedcomponents(int graph[][maxnode], int n) {
  bool visited[maxnode] = {false}; // visited hash
  struct queue* q = createqueue(); // creating a queue

  // if not visited call dfs
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs(i, graph, n, visited, q);
    }
  }

  // transpose of the graph
  int transposedGraph[maxnode][maxnode];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      transposedGraph[i][j] = graph[j][i]; 
    }
  }

  // reset the visited hash
  for (int i = 0; i < n; ++i) {
    visited[i] = false;
  }

  // component count and hash
  int component[maxnode] = {0}; 
  int component_number = 0;

  // call dfs reverse and get the component number and component hash
  while (!isempty(q)) {
    int vertex = dequeue(q);
    if (!visited[vertex]) {
      dfs_reverse(vertex, transposedGraph, n, visited, component, component_number++);
    }
  }

  return component_number;
}


int main() {
  int n;
  char command;
  scanf("%d", &n);
  int graph[maxnode][maxnode];

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &graph[i][j]);
    }
  }

  while (1) {
    scanf(" %c", &command);
    switch (command) {
      case 't':
        printf("%d\n", istopologicalsortpossible(graph, n) ? 1 : -1);
        break;

      case 'c':
        printf("%d\n", numberofstronglyconnectedcomponents(graph, n));
        break;

      case 'x':
        return 0;
    }
  }

  return 0;
}
