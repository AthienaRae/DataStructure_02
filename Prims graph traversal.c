Write a C program to create a graph and find a minimum spanning tree using prims algorithm. 

Algorithm:
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[][V], int V) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

void primMST(int graph[][V], int V) {
    int parent[V]; 
    int key[V];
    int mstSet[V]; 

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    
    key[0] = 0;
    parent[0] = -1; 
    for (int count = 0; count < V - 1; count++) {
        
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;

    
        for (int v = 0; v < V; v++) {
            
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    
    printMST(parent, graph, V);
}

int main() {
    int V;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);

    int graph[V][V];

    printf("Enter the adjacency matrix for the graph (%d vertices x %d vertices):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Print the solution
    primMST(graph, V);

    return 0;
}
 
