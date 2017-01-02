#include "digraph.h"

int list[10];
int i = 0;
void storeVertexName(Graph graph, int id);

int main()
{
    Graph g = createGraph();
    int output[10];
    int n;
    int id[4];
    char name[4][100];
    printf("Type in the name for 4 vertices: \n");
    for(int j = 0; j <= 4; ++j)
    {
        printf("ID = ");
        scanf("%d", &id[j]);
        printf("%d-th vertex name: ", j);
        scanf("%s", name[j]);
        myfflush();
    }
    for(int j = 0; j <= 4; ++j)
        addVertex(g, id[j], name[j]);
    for(int j = 0; j <= 4; ++j)
    {
        printf("ID = %d: ", id[j]);
        showVertexName(g, id[j]);
        printf("\n");
    }
    // addVertex(g, 0, "0");
    // addVertex(g, 1, "1");
    // addVertex(g, 2, "2");
    // addVertex(g, 3, "3");
    // addVertex(g, 4, "4");

    addEdge(g, 1, 0);
    addEdge(g, 2, 1);
    addEdge(g, 3, 4);
    addEdge(g, 4, 0);



// #define PRINT_ADJACENT_VERTIES(v) {                                 \
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
        topologicalSort(g, output, &n, storeVertexName);
        for (int i = 0; i <= getMaxId(g); ++i)
            printf("%d ", list[i]);
        printf("\n");
        topologicalSort(g, output, &n, showVertexName);
        printf("\n");
    }
    dropGraph(g);
    // free(list);
    return 0;
}

void storeVertexName(Graph graph, int id)
{
    if (graph.edges == NULL || graph.vertices == NULL)
        return ;
    JRB node = jrb_find_int(graph.vertices, id);
    if (node != NULL) {
        list[i++] = id;
    }
}
