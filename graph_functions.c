#include "graph.h"

/* function will display the primary user interface
    This is already done for you*/
void prompt(void)
{
    // Display the menu options to the user
    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }

    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
    {
        fprintf(stderr, "Error: Could not allocate memory for graph\n");
        fclose(file);
        return NULL;
    }

    // Determine the number of vertices by reading the file line by line
    graph->numVertices = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        graph->numVertices++;
    }

    // Allocate memory for the adjacency matrix
    fseek(file, 0, SEEK_SET); // Reset file pointer to the beginning
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            fscanf(file, "%d", &graph->adjMatrix[i][j]);
        }
    }

    fclose(file);
    createAdjacencyList(graph);
    return graph;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        fprintf(stderr, "Error: Could not allocate memory for node\n");
        return NULL;
    }
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}
/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph)
{
    // Implement the function logic here

    printf("Adjacency List:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->adjList[i];
        printf("Vertex %d: ", i + 1);
        while (temp)
        {
            printf("-> %d (%d) ", temp->vertex + 1, graph->adjMatrix[i][temp->vertex]);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        graph->adjList[i] = NULL;
        Node *last = NULL;
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (graph->adjMatrix[i][j] != 0)
            {
                Node *newNode = createNode(j);
                if (graph->adjList[i] == NULL)
                {
                    graph->adjList[i] = newNode;
                }
                else
                {
                    last->next = newNode;
                }
                last = newNode;
            }
        }
    }
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex)
{
    bool visited[MAX_VERTICES] = {false};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    printf("Final BFS Order:\n");
    while (front < rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex + 1);

        Node *temp = graph->adjList[currentVertex];
        while (temp)
        {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

/**
 * Helper function for DFS that performs the recursive part of the traversal.
 * @param graph Pointer to the Graph structure.
 * @param vertex The current vertex being visited.
 * @param visited Array to keep track of visited vertices.
 */
void dfsUtil(Graph *graph, int vertex, bool visited[])
{
    visited[vertex] = true;
    printf("%d ", vertex + 1);

    Node *temp = graph->adjList[vertex];
    while (temp)
    {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex])
        {
            dfsUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex)
{
    bool visited[MAX_VERTICES] = {false};
    printf("Final DFS Order:\n");
    dfsUtil(graph, startVertex, visited);
    printf("\n");
}

/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex)
{
    int dist[MAX_VERTICES];
    bool sptSet[MAX_VERTICES];

    for (int i = 0; i < graph->numVertices; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[startVertex] = 0;

    for (int count = 0; count < graph->numVertices - 1; count++)
    {
        int min = INT_MAX, minIndex;

        for (int v = 0; v < graph->numVertices; v++)
        {
            if (!sptSet[v] && dist[v] <= min)
            {
                min = dist[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        sptSet[u] = true;

        for (int v = 0; v < graph->numVertices; v++)
        {
            if (!sptSet[v] && graph->adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + graph->adjMatrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph->adjMatrix[u][v];
            }
        }
    }

    printf("\nShortest distance from vertex 1:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("Shortest distance from vertex 1 to vertex %d: %d\n", i + 1, dist[i]);
    }
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->numVertices; i++)
    {
        Node *temp = graph->adjList[i];
        while (temp)
        {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph);
}
