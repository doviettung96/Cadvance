#include "wgraph.h"

#define MAXSECTION 7

// char** str_split(char* a_str, const char a_delim);
Graph inputFromFile(char fileName[]);

void main()
{
	int choice;
	int search;
	char temp[100];
	Graph graph;
	int output[10];
	int n;
	int num_line;
	int *num_of_pre;
	char *result;
	char file_name[100];
	char sections[MAXSECTION][40] = {"Create graph", "DAG", "Get prerequisites",
	                                 "Choose 3 or 5", "List all", "Topological Sort", "Drop graph",
	                                };
	do {
		choice = getMenu(sections, MAXSECTION);
		switch (choice)
		{
		case 1:

			// printf("Type in file name: ");
			// scanf("%[^\n]", file_name);
			// myfflush();
			graph = inputFromFile("input.txt");
			printf("Create!!!\n");
			num_line = countVertices(graph);
			printf("\nNumber of vertices: %d\n", num_line);
			printf("Number of edges: %d\n", countEdges(graph));
			break;
		case 2:
			if (DAG(graph))
				printf("Valid\n");
			else
				printf("Has cycle\n");
			break;
		case 3:
			printf("Enter an ID\n");
			scanf("%d", &search);
			myfflush();
			result = (char *)malloc(sizeof(char) * 100);
			result = getVertexName(graph, search);
			if (!result)
				printf("Doesn't exist\n");
			else
			{
				n = inDegree(graph, search, output);
				for (int i = 0; i < n; ++i)
				{
					showVertexName(graph, output[i]);
					printf("Weight: %f\n", getEdgeValue(graph, output[i], search));
				}
			}
			break;
		case 4:
			break;
		case 5:
			num_of_pre = (int *)malloc(sizeof(int) * num_line);
			for (int i = 1; i < num_line + 1; ++i)
				num_of_pre[i] = inDegree(graph, i, output);
			for (int j = 0; j < num_line; ++j)
			{
				printf("Has %d- precourses: ", j);
				for (int i = 1; i < num_line + 1; ++i)
					if (num_of_pre[i] == j)
						showVertexName(graph, i);

				printf("\n");
			}
			free(num_of_pre);
			break;

		case 6:
			topologicalSort(graph, output, &n, showVertexName);
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

Graph inputFromFile(char fileName[])
{
	Graph graph = createGraph();
	FILE *f = fopen(fileName, "r");
	if (f == NULL) {
		fprintf(stderr, "Can't Open file %s !!\n", fileName);
		exit(1);
	}

	int num_line;
	fscanf(f, "%d\n", &num_line);
	char input_list[100];
	char name[num_line][100];
	char **token;
	int v1, v2;

	while (!feof(f))
	{
		char temp[100];
		fgets(temp, 100, f);
		if (temp[strlen(temp) - 1] == 10 )
			temp[strlen(temp) - 1] = 0;

		token = str_split(temp, ' ');

		v1 = atoi(*(token));
		addVertex(graph, v1, *(token));
		if (token)
		{
			for (int i = 1; * (token + i); i++)
			{
				v2 = atoi(*(token + i));
				addEdge(graph, v2, v1, 0);
			}
		}
	}
	for (int i = 0; * (token + i); i++)
		free(*(token + i));
	fclose(f);
	free(token);
	return graph;
}

