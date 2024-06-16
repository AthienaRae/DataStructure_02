Write a C program to create a graph and perform a Breadth First Search and Depth First Search. 

Algorithm:
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Adjacency list node
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Graph structure
struct Graph {
    int V;
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the adjacency list of a graph
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// BFS function
void BFS(struct Graph* graph, int startVertex) {
    int visited[MAX] = {0};

    int queue[MAX];
    int front = -1;
    int rear = -1;

    visited[startVertex] = 1;
    queue[++rear] = startVertex;

    while (front != rear) {
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);

        struct AdjListNode* temp = graph->array[currentVertex].head;

        while (temp) {
            int adjVertex = temp->dest;

            if (!visited[adjVertex]) {
                queue[++rear] = adjVertex;
                visited[adjVertex] = 1;
            }
            temp = temp->next;
        }
    }
}

// DFS function
void DFSUtil(struct Graph* graph, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);

    struct AdjListNode* temp = graph->array[v].head;
    while (temp) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex])
            DFSUtil(graph, adjVertex, visited);
        temp = temp->next;
    }
}

void DFS(struct Graph* graph, int startVertex) {
    int visited[MAX] = {0};
    DFSUtil(graph, startVertex, visited);
}

// Main function
int main() {
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printf("Adjacency list of the graph:\n");
    printGraph(graph);

    printf("\nBFS starting from vertex 0:\n");
    BFS(graph, 0);

    printf("\nDFS starting from vertex 0:\n");
    DFS(graph, 0);

    return 0;
}
 
