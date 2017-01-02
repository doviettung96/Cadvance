#include "digraph.h"

#define MAXSECTION 14

int i = 0;

void main()
{
	int choice;
	int search;
	char temp[100];

	int id[100];
	char name[100][100];
	Graph graph;
	char sections[MAXSECTION][40] = {"Create graph", "Add vertex", "Get vertex name",
	                                 "BFS", "DFS", "Drop graph",
	                                };
	do {
		choice = getMenu(sections, MAXSECTION);
		switch (choice)
		{
		case 1:
			graph = createGraph();
			printf("Create!!!\n");
			break;
		case 2:
			printf("Type in id: ");
			scanf("%d", &id[i]);
			printf("Type in a name: ");
			scanf("%s", name[i]);
			myfflush();
			addVertex(graph, id[i], name[i]);
			++i;
			break;
		case 3:
			printf("Enter an ID\n");
			scanf("%d", &search);
			myfflush();
			showVertexName(graph, search);
			break;
		case 4:
			printf("BFS order: \n");
			BFS(graph, 0, -1, showVertexName);
			printf("\n");
			break;
		case 5:
			printf("DFS order: \n");
			DFS(graph, 0, -1, showVertexName);
			printf("\n");
			break;
		case MAXSECTION:
			dropGraph(graph);
			break;
		default:
			printf("Choice must be from 1 to %d\n", MAXSECTION);
			exit(1);
		}
	} while (choice != MAXSECTION && choice != 0);
}

