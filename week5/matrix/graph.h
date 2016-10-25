#include <utility.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *matrix;
	int sizeMax;
} Graph;

Graph createGraph(int sizeMax);
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int vertex, int *output);
//return the numer of adjacent vertices
void dropGraph(Graph graph);