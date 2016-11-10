#include <libfdr/jrb.h>
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
void dropGraph(Graph graph);
