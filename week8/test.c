#include "digraph.h"

void print_node(Graph g, int i) {
    printf("%d ", i);
}

int main()
{
    Graph g = createGraph();
    int output[10];
    int n;
    // addVertex(g, 0, "CS102");
    // addVertex(g, 1, "CS140");
    // addVertex(g, 2, "CS160");
    // addVertex(g, 3, "CS302");
    // addVertex(g, 4, "CS311");
    // addVertex(g, 5, "MATH300");
     addVertex(g, 0, "0");
     addVertex(g, 1, "1");
     addVertex(g, 2, "2");
     addVertex(g, 3, "3");
     addVertex(g, 4, "4");
     addVertex(g, 5, "5");

    addEdge(g, 5, 2);
    addEdge(g, 5, 0);
    addEdge(g, 4, 0);
    addEdge(g, 4, 1);
    addEdge(g, 2, 3);
    addEdge(g, 3, 1);

#define PRINT_ADJACENT_VERTIES(v) {                                 \
          n = outDegree(g, v, output);                              \
          if(n == 0)                                                \
               printf("No adjacent vertices of node " #v " \n");     \
          else{                                                     \
               printf("Adjacent vertices of node "#v": ");          \
               for(int i = 0; i < n; i++)                               \
                    printf("%5d", output[i]);                       \
               printf("\n");                                        \
          }                                                         \
     }

    PRINT_ADJACENT_VERTIES(0);
    PRINT_ADJACENT_VERTIES(1);
    PRINT_ADJACENT_VERTIES(2);
    PRINT_ADJACENT_VERTIES(3);
    PRINT_ADJACENT_VERTIES(4);
    PRINT_ADJACENT_VERTIES(5);
#undef PRINT_ADJACENT_VERTIES

    // DFS(g, 2, -1, showVertexName);

    if (DAG(g) == 0)
        printf("Can not make topological sort\n");
    else
    {
        printf("The topological order: \n");
        topologicalSort(g, output, &n, showVertexName);
        printf("\n");
    }
    dropGraph(g);
    return 0;
}

