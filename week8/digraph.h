#include <libfdr/jrb.h>
#include <libfdr/dllist.h>
//../../lib/include/libfdr/jrb.h
#include <utility.h>
//../../lib/include/utility.h
//2 headers are taken from ../../lib/include
#include <stdio.h>

typedef struct {
	JRB edges;
	JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char *name);
char *getVertexName(Graph graph, int id);
int hasEdge(Graph graph, int v1, int v2);
void addEdge(Graph graph, int v1, int v2);
int inDegree(Graph graph, int v, int *output);
//traverse: start from all vertices to 1 vertex
int outDegree(Graph graph, int v, int *output);
//traverse: start from 1 vertex v to all outer vertices
void showVertexName(Graph graph, int id);
int getMaxId(Graph g);
int getMinId(Graph g);
void BFS(Graph graph, int start, int stop, void (*visitFunc)(Graph, int));
void DFS(Graph graph, int start, int stop, void (*visitFunc)(Graph, int));
int isCyclicUtil(Graph graph, int vertex);
//check for vertex v about existing a cycle
int DAG(Graph graph);
//check for acylic graph
void topologicalSort(Graph g, int *output, int *n, void (* visitFunc)(Graph, int));
void dropGraph(Graph graph);
