#include "wgraph.h"



int list[10];
int i = 0;
void storeVertexName(Graph graph, int id);
void print_node(Graph g, int i);

int main()
{
    Graph g = createGraph();
    int output[100];
    int n;
    int s, t, path[1000];
    double length[1000];

    addVertex(g, 0, "C");
    addVertex(g, 1, "G");
    addVertex(g, 2, "B");
    addVertex(g, 3, "A");
    addVertex(g, 4, "D");
    addVertex(g, 5, "E");
    addVertex(g, 6, "F");
    addVertex(g, 7, "H");

    addEdge(g, 0, 2, 1);
    addEdge(g, 0, 3, 1);
    addEdge(g, 0, 1, 1);
    addEdge(g, 0, 6, 1);
    addEdge(g, 2, 5, 1);
    addEdge(g, 3, 4, 1);
    addEdge(g, 3, 5, 1);
    addEdge(g, 4, 5, 1);
    addEdge(g, 4, 6, 1);
    addEdge(g, 5, 6, 1);
    addEdge(g, 6, 7, 1);

    s = 0;
    t = 4;

    double weight = shortestPath(g, s, t, path, length);
    if (weight == INFINITIVE_VALUE)
        printf("No path between % d and % d\n", s, t);
    else {
        printf("Path between %d and %d: ", s, t);
        for (int i = 0; i < 10; i++)
            if (path[i])
                printf(" %4d %.2f", path[i], length[i]);
        printf("\nTotal weight: %f", weight);
    }

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

    // PRINT_ADJACENT_VERTIES(0);
    // PRINT_ADJACENT_VERTIES(1);
    // PRINT_ADJACENT_VERTIES(2);
    // PRINT_ADJACENT_VERTIES(3);
    // PRINT_ADJACENT_VERTIES(4);
    // PRINT_ADJACENT_VERTIES(5);
#undef PRINT_ADJACENT_VERTIES

    printf("\n");
    printf("BFS order: \n");
    BFS(g, 0, -1, showVertexName);
    printf("\n");

    printf("DFS order: \n");
    DFS(g, 0, -1, showVertexName);
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

void print_node(Graph g, int i) {
    printf("%d ", i);
}


