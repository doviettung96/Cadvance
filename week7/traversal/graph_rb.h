#include <libfdr/jrb.h>
#include <libfdr/dllist.h>
//../../lib/include/libfdr/jrb.h
#include <utility.h>
//../../lib/include/utility.h
//2 headers are taken from ../../lib/include 
#include <stdio.h>

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices (Graph graph, int v, int* output);
void printVertex(int vertex);
void BFS(Graph graph, int start, int stop, void (*func)(int));
void DFS(Graph graph, int start, int stop, void (*func)(int));
void dropGraph(Graph graph);
