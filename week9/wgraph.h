#include <libfdr/jrb.h>
#include <libfdr/dllist.h>
//../../lib/include/libfdr/jrb.h
#include <utility.h>
//../../lib/include/utility.h
//2 headers are taken from ../../lib/include
#include <stdio.h>

#define INFINITIVE_VALUE  10000000
#define UNDEFINED -1
typedef struct {
	JRB edges;
	JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char *name);
char *getVertexName(Graph graph, int id);
int hasEdge(Graph graph, int v1, int v2);
void addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2); // return INFINITIVE_VALUE if no edge between v1 and v2
int inDegree(Graph graph, int v, int *output);
//traverse: start from all vertices to 1 vertex
int outDegree(Graph graph, int v, int *output);
//traverse: start from 1 vertex v to all outer vertices
void showVertexName(Graph graph, int id);
int getMaxId(Graph g);
int getMinId(Graph g);
void BFS(Graph graph, int start, int stop, void (*visitFunc)(Graph, int));
void DFS(Graph graph, int start, int stop, void (*visitFunc)(Graph, int));
void DFS_all(Graph graph, void (*visitFunc)(Graph, int));
//use when the graph is not connected
void DFS_ulti(Graph graph, int start, int stop, void (*visitFunc)(Graph, int), int *visited);
int isCyclicUtil(Graph graph, int vertex); //check for vertex v about existing a cycle
int DAG(Graph graph); //check for acylic graph
// return the total weight of the path and the path is given via path and its length.
// Return INFINITIVE_VALUE if no path is found
void topologicalSort(Graph g, int *output, int *n, void (* visitFunc)(Graph, int));
double shortestPath(Graph graph, int s, int t, int* path, double* length);
void dropGraph(Graph graph);
