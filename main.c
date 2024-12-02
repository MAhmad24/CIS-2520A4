#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * A basic menu based structure has been provided
 */

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    Graph *graph = readGraph(argv[1]);
    if (!graph)
    {
        return 1;
    }

    int choice;

    do
    {
        // Display the options
        prompt();

        // Get user input
        printf("Enter a Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            // Display Adjacency List
            displayAdjacencyList(graph);
            break;
        case 2:
            // Perform Breadth-First Search (BFS)
            bfs(graph, 0); // Start BFS from vertex 1 (index 0)
            break;
        case 3:
            // Perform Depth-First Search (DFS)
            dfs(graph, 0); // Start DFS from vertex 1 (index 0)
            break;
        case 4:
            // Find Shortest Path using Dijkstra's Algorithm
            dijkstra(graph, 0); // Start Dijkstra's from vertex 1 (index 0)
            break;
        case 5:
            // Exit
            printf("Exiting...\n");
            freeGraph(graph);
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (true);

    freeGraph(graph);
    return 0;
}
