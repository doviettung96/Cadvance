#include <libfdr/jrb.h>
#include <libfdr/dllist.h>
//../../lib/include/libfdr/jrb.h
#include <utility.h>
//../../lib/include/utility.h
//2 headers are taken from ../../lib/include 
#include <stdio.h>

typedef struct{
JRB edges;
JRB vertices;
}Graph;

Graph createGraph();
int hasEdge(Graph graph, int v1, int v2);
void addVertex(Graph graph, int id, char *name);
void addEdge(Graph graph, int v1, int v2);
int inDegree(Graph graph, int v, int *output);
int outDegree(Graph graph, int v, int *output);
char *getVertexName(graph graph, int id);
void printVertex(int vertex);
void BFS(Graph graph, int start, int stop, void (*func)(int));
void DFS(Graph graph, int start, int stop, void (*func)(int));
void dropGraph(Graph graph);
