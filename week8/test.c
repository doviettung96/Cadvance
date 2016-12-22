#include "digraph.h"

void main()
{
    Graph g = createGraph();
    int output[10];
    JRB node;
    int n;

    addVertex(g, 0, "CS102"); addVertex(g, 1, "CS140");
    addVertex(g, 2, "CS160"); addVertex(g, 3, "CS302");
    addVertex(g, 4, "CS311"); addVertex(g, 5, "MATH300");
    addEdge(g, 0, 1); addEdge(g, 0, 2);
    addEdge(g, 1, 3); addEdge(g, 5, 4); addEdge(g, 3, 4);
    if (!DAG(g))
        printf("Can not make topological sort\n");
    else
    {
    printf("The topological order: \n");
    topologicalSort(g, output, &n, showVertexName);
    }
    dropGraph(g);

}