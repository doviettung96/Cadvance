#include <libfdr/jrb.h>
#include <libfdr/dllist.h>
#include <libfdr/fields.h>
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
void index_to_name(int i, int j, char *name);
void add_all_vertices(Graph G, char *fn);
void add_all_edges(Graph G, char *fn);
void add_vertex_auto_increment(Graph graph, char *name);
char *getVertexName(Graph graph, int id);
int countVertices(Graph graph);
int countEdges(Graph graph);
int hasEdge(Graph graph, int v1, int v2);
void addEdge(Graph graph, int v1, int v2);
int inDegree(Graph graph, int v, int *output);
//traverse: start from all vertices to 1 vertex
int outDegree(Graph graph, int v, int *output);
//traverse: start from 1 vertex v to all outer vertices
void showVertexName(Graph graph, int id);
int getVertexId(Graph graph, char *name);
int getMaxId(Graph g);
int getMinId(Graph g);
void BFS(Graph graph, int start, int stop, void (*visitFunc)(Graph, int));
void DFS(Graph graph, int start, int stop, void (*visitFunc)(Graph, int));
void DFS_all(Graph graph, void (*visitFunc)(Graph, int));
//apply when the graph is not connected
void DFS_ulti(Graph graph, int start, int stop, void (*visitFunc)(Graph, int), int *visited);
int isCyclicUtil(Graph graph, int vertex);
//check for vertex v about existing a cycle
int DAG(Graph graph);
//check for acylic graph
void topologicalSort(Graph g, int *output, int *n, void (* visitFunc)(Graph, int));
void dropGraph(Graph graph);
