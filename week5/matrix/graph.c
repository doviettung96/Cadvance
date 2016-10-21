#include "graph.h"

Graph createGraph(int sizeMax)
{
	Graph graph;
	graph.sizeMax = sizeMax;
	graph.matrix = (int *)malloc(sizeof(int) * sizeMax * sizeMax);
	if (graph.matrix != NULL)
		return graph;
}

void addEdge(Graph graph, int v1, int v2)
{
	if (v1 > graph.sizeMax || v2 > graph.sizeMax)
	{
		printf("Error!\n");
		return;
	}

	graph.matrix[v1 * (graph.sizeMax) + v2] = 1;
	graph.matrix[v2 * (graph.sizeMax) + v1] = 1;
}

int adjacent(Graph graph, int v1, int v2)
{
	if (graph.matrix == NULL)
		return 0;
	if (graph.matrix[v1 * (graph.sizeMax) + v2] == 1 & graph.matrix[v2 * (graph.sizeMax) + v1] == 1)
		return 1;
	return 0;
}

int getAdjacentVertices(Graph graph, int vertex, int *output)
{
	int i, j = 0;
	for (i = 0; i < graph.sizeMax; ++i)
	{
		if (i == vertex)
			continue;
		//duplicate
		if (adjacent(graph, i, vertex) == 1)
		{
			output[j] = i;
			++j;
		}
	}
	return j;
	//number of adjacent vertices for a certain vertex
}

void dropGraph(Graph graph)
{
	free(graph.matrix);
}