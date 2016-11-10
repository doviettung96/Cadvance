#include "graph_rb.h"

#define MAXSECTION 4

void main()
{
	int i, n, output[100];
	int choice;
	int v, v2;
	Graph g;
	char sections[MAXSECTION][40] = {"Create the graph", "Add edges", "Show adjacent vertices of a vertex", "Exit and free"};
	do {
		choice = getMenu(sections, MAXSECTION);
		switch (choice)
		{
		case 1:
			g = createGraph();
			printf("Graph created!\n");
			break;
		case 2:
			printf("Type in v1_v2: ");
			scanf("%d_%d", &v, &v2);
			addEdge(g, v, v2);

			break;
		case 3:
			printf("Type in a vertex: ");
			scanf("%d", &v);
			n = getAdjacentVertices (g, v, output);
			if (n == 0)
				printf("No adjacent vertices of node 1\n");
			else
			{
				printf("Adjacent vertices of node %d:", v);
				for (i = 0; i < n; i++)
					printf("%5d", output[i]);
			}
			printf("\n");
			break;
		case 4:
			dropGraph(g);
			break;
		default: printf("Choice must be from 1 to %d\n", MAXSECTION);
			exit(1);
		}
	} while (choice  != MAXSECTION);
}