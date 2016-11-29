#include "digraph.h"

void main()
{
    Graph g = createGraph();
    int output[10];
    JRB node;
    int n;
    addVertex(g, 0, "V0");
    addVertex(g, 1, "V1");
    addVertex(g, 2, "V2");
    addVertex(g, 3, "V3");
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    addEdge(g, 1, 3);
    for (int i = 0; i <= 3; ++i)
        printf("%s ", getVertexName(g, i));
    printf("\n");
//    if (DAG(g))
//    printf("The graph is acycle\n");
//    else
//    printf("Have cycles in the graph\n");
    dropGraph(g);
}