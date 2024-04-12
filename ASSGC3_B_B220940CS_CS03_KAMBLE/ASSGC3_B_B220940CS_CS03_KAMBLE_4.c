#include <stdio.h>

// define parameters to be used globally
#define maxnode 100
#define v 4
#define infi 9999999

// function for minimum number
int min(int num1, int num2){
  if(num1 < num2)
    return num1;
  return num2;
}

// floyd-warshall algorithm
void floydmarshall(int graph[][maxnode], int vertex){
  int i, j, k;

  // outermost loop for the updating the distance matrix
  // inner two loops for updating distances by checking the direct and roundabout path
  for(k = 0; k < vertex; k++){
    for(i = 0; i < vertex; i++){
      for(j = 0; j < vertex; j++){
        graph[i][j] = min(graph[i][j], (graph[i][k]+graph[k][j])); // update the matrix with less weight of either
      }
    }
  }

  // print loop prints -1 for infi and else normal
  for(i = 0; i < vertex; i++){
    for(j = 0; j < vertex; j++){
      if(graph[i][j] == infi)
        printf("-1 ");
      else  
        printf("%d ",graph[i][j]);
    }
    printf("\n");
  } 
}

/*void floydWarshall(int dist[][V])
{
    int i, j, k;
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    printSolution(dist);
}*/

// main function
int main(){
  int vertex, num;
  scanf("%d",&vertex);

  int graph[maxnode][maxnode];

  for(int i = 0; i < vertex; i++){
    for(int j = 0; j < vertex; j++){
      scanf("%d",&num);
      if(num == -1)
        graph[i][j] = infi;
      else
        graph[i][j] = num;
    }
  }

  // calling the algorithm
  floydmarshall(graph, vertex);
}