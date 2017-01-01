#include "digraph.h"

int main()
{
    Graph g = createGraph();
    int output[10];
    int n;

    addVertex(g, 0, "0");
    addVertex(g, 1, "1");
    addVertex(g, 2, "2");
    addVertex(g, 3, "3");
    addVertex(g, 4, "4");

<<<<<<< HEAD
=======
    // addEdge(g, 1, 0);
    // addEdge(g, 0, 2);
    // addEdge(g, 2, 1);
    // addEdge(g, 0, 3);
    // addEdge(g, 1, 4);
>>>>>>> parallel
    addEdge(g, 1, 0);
    addEdge(g, 2, 1);
    addEdge(g, 3, 4);
    addEdge(g, 4, 0);
<<<<<<< HEAD
    printf("\n");
    printf("DFS order\n");
    DFS(g, 0, -1, showVertexName);
    printf("BFS order\n");
    BFS(g, 0, -1, showVertexName);
    printf("\n");
    if (!DAG(g))
=======



// #define printfINT_ADJACENT_VERTIES(v) {                                 \
//           n = outDegree(g, v, output);                              \
//           if(n == 0)                                                \
//                printf("No adjacent vertices of node " #v " \n");     \
//           else{                                                     \
//                printf("Adjacent vertices of node "#v": ");          \
//                for(int i = 0; i < n; i++)                               \
//                     printf("%5d", output[i]);                       \
//                printf("\n");                                        \
//           }                                                         \
//      }

//     PRINT_ADJACENT_VERTIES(0);
//     PRINT_ADJACENT_VERTIES(1);
//     PRINT_ADJACENT_VERTIES(2);
//     PRINT_ADJACENT_VERTIES(3);
//     PRINT_ADJACENT_VERTIES(4);
//     PRINT_ADJACENT_VERTIES(5);
// #undef PRINT_ADJACENT_VERTIES

    printf("BFS order: \n");
    BFS(g, 0, -1, showVertexName);
    printf("\n");

    printf("DFS order: \n");
    DFS(g, 0, -1, showVertexName);
    printf("\n");

    printf("DFS_all order: \n");
    DFS_all(g, showVertexName);
    printf("\n");


    if (DAG(g) == 0)
        printf("Can not make topological sort\n");
    else
    {
        printf("The topological order: \n");
        topologicalSort(g, output, &n, showVertexName);
        printf("\n");
    }
    dropGraph(g);
    // free(list);
    return 0;
}

