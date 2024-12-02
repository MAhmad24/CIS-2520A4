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
    //open the file in reading mode
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        //Print an error message if the file could not be opened
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }

    // Allocate memory for the graph structure
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph)
    {
        //print an error message if memory could not be allocated
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

    //close the file
    fclose(file);

    //convert adjacency matrix to adjacency list
    createAdjacencyList(graph);

    //return the created graph
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


    //print the header for the adjacency list
    printf("Adjacency List:\n");

    //iterate over each vertex and print the adjacency list
    for (int i = 0; i < graph->numVertices; i++)
    {

        //get the head of the adjacency list for the current vertex
        Node *temp = graph->adjList[i];

        //print the vertex number
        printf("Vertex %d: ", i + 1);

        //traverse the adjacency list and print the connected vertices
        while (temp)
        {
            printf("-> %d (%d) ", temp->vertex + 1, graph->adjMatrix[i][temp->vertex]);
            temp = temp->next;
        }

        //indicate the end of the adjacency list
        printf("NULL\n");
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph)
{

    
    //iterate over each vertex and create a new node for the adjacency list
    for (int i = 0; i < graph->numVertices; i++)
    {

        //initialize the adjacency list for the current vertex
        graph->adjList[i] = NULL;
        Node *last = NULL;

        //iterate over each possible adjecent vertex 
        for (int j = 0; j < graph->numVertices; j++)
        {

            //check if there is an edge between the current vertex and the adjacent vertex
            if (graph->adjMatrix[i][j] != 0)
            {

                //create a new node for the adjacent vertex
                Node *newNode = createNode(j);

                //add the new node to the adjacency list
                if (graph->adjList[i] == NULL)
                {
                    graph->adjList[i] = newNode;
                }
                else
                {
                    //otherwise, add the new node to the end of the adjacency list
                    last->next = newNode;
                }
                //update the last node in the adjacency list
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

    //array to keep track of visited vertices
    bool visited[MAX_VERTICES] = {false};

    //queue to store the vertices to be visited
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    //mark the start vertex as visited and add it to the queue
    visited[startVertex] = true;
    queue[rear++] = startVertex;


    printf("Final BFS Order:\n");

    //continue until the queue is empty
    while (front < rear)
    {

        //dequeue the font vertex from the queue
        int currentVertex = queue[front++];

        //print the current vertex
        printf("%d ", currentVertex + 1);

        //get all adjacent vertices of the current vertex
        Node *temp = graph->adjList[currentVertex];
        while (temp)
        {

            //if an adjacent vertex has not been visited, mark it as visited and add it to the queue
            int adjVertex = temp->vertex;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            //move to the next ajacent vertex
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

    //mark the current vertex as visited and print it
    visited[vertex] = true;
    printf("%d ", vertex + 1);

    //recur for all adjacent vertices of the current vertex
    Node *temp = graph->adjList[vertex];
    while (temp)
    {
        int adjVertex = temp->vertex;

        //if an adjacent vertex has not been visited, recur for it
        if (!visited[adjVertex])
        {
            //gotta try to think of a comment here (DON'T FORGET)
            dfsUtil(graph, adjVertex, visited);
        }
        //move to the next adjacent vertex
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

    //array to keep track of visited vertices
    bool visited[MAX_VERTICES] = {false};
    printf("Final DFS Order:\n");

    //start the recursive DFS traversal from the start vertex
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

    //array to store the shortest distance from the start vertex to each vertex
    int dist[MAX_VERTICES];

    //will be true if the vertex is included in the shortest path tree
    bool sptSet[MAX_VERTICES];

    //initialize all distances as infinite and sptSet[] as false
    for (int i = 0; i < graph->numVertices; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    //distance of start vertex from itself is always 0
    dist[startVertex] = 0;

    //find shortest path for all vertices
    for (int count = 0; count < graph->numVertices - 1; count++)
    {

        //pick the minimum distance vertex from the set of vertices not yet processed
        int min = INT_MAX, minIndex;

        for (int v = 0; v < graph->numVertices; v++)
        {
            if (!sptSet[v] && dist[v] <= min)
            {
                min = dist[v];
                minIndex = v;
            }
        }

        //mark the picked vertex as processed
        int u = minIndex;
        sptSet[u] = true;

        //update the distance value of the adjacent vertices of the picked vertex
        for (int v = 0; v < graph->numVertices; v++)
        {

            // Update dist[v] if it is not in sptSet, there is an edge from u to v,
            // and the total weight of the path from startVertex to v through u is
            // smaller than the current value of dist[v]
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
    // Iterate over each vertex in the graph
    for (int i = 0; i < graph->numVertices; i++)
    {
        // Free the adjacency list for the current vertex
        Node *temp = graph->adjList[i];
        while (temp)
        {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }

    // Free the adjacency list array
    free(graph->adjList);

    // Free the adjacency matrix
    for (int i = 0; i < graph->numVertices; i++)
    {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);

    // Free the graph structure itself
    free(graph);
}
