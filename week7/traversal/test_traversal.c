#include "graph_rb.h"

void main()
{
	Graph g = createGraph();


	addEdge(g, 1, 0);
	addEdge(g, 2, 1);
	addEdge(g, 3, 4);
	addEdge(g, 4, 0);
	// printf("\nBFS: start from node 1 to 5: ");
	// BFS(g, 1, 4, printVertex);
	printf("\nBFS: start from node 1 to all: ");
	BFS(g, 1, -1, printVertex);
	// printf("\nDFS: start from node 1 to 5: ");
	// DFS(g, 1, 4, printVertex);
	printf("\nDFS: start from node 1 to all: ");
	DFS(g, 1, -1, printVertex);
}