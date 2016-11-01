#include "graph_rb.h"

void main()
{
	Graph g = createGraph();
	addEdge(g, 0, 1);
	addEdge(g, 1, 2);
	addEdge(g, 1, 3);
	addEdge(g, 2, 3);
	addEdge(g, 2, 4);
	addEdge(g, 4, 5);
	printf("\nBFS: start from node 1 to 5: ");
	BFS(g, 1, 4, printVertex);
	printf("\nBFS: start from node 1 to all: ");
	BFS(g, 1, -1, printVertex);
	printf("\nDFS: start from node 1 to 5: ");
	DFS(g, 1, 4, printVertex);
	printf("\nDFS: start from node 1 to all: ");
	DFS(g, 1, -1, printVertex);
}