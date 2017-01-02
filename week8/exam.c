#include "digraph.h"

#define MAXSECTION 6

char** str_split(char* a_str, const char a_delim);
Graph inputFromFile(char fileName[]);

void main()
{
	int choice;
	int search;
	char temp[100];
	Graph graph;
	int num_line;
	char result[100];
	char file_name[100];
	char sections[MAXSECTION][40] = {"Create graph", "DAG", "Get vertex name",
	                                 "BFS", "DFS", "Drop graph",
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

			printf("\nNumber of vertices: %d\n", countVertices(graph));
			printf("Number of edges: %d\n", countEdges(graph));
			break;
		case 2:
			// for (int i = 0; i < 4; ++i)
			// 	showVertexName(graph, i + 1);
			// printf("\n");
			if (DAG(graph))
				printf("Valid\n");
			else
				printf("Has cycle\n");
			break;
		case 3:
			printf("Enter an ID\n");
			scanf("%d", &search);
			myfflush();
			result = getVertexName(graph, search);
			if(!result)
				printf("Doesn't exist\n");
			else
			{
				
			}
			break;
		case 4:
			printf("BFS order: \n");
			BFS(graph, 1, -1, showVertexName);
			printf("\n");
			break;
		case 5:
			printf("DFS order: \n");
			DFS(graph, 1, -1, showVertexName);
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
				addEdge(graph, v2, v1);
			}
		}
	}
	for (int i = 0; * (token + i); i++)
		free(*(token + i));
	fclose(f);
	free(token);
	return graph;
}

char** str_split(char* a_str, const char a_delim)
{
	char** result    = 0;
	size_t count     = 0;
	char* tmp        = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	while (*tmp)
	{
		if (a_delim == *tmp)
		{
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	count += last_comma < (a_str + strlen(a_str) - 1);

	count++;

	result = malloc(sizeof(char*) * count);

	if (result)
	{
		size_t idx  = 0;
		char* token = strtok(a_str, delim);

		while (token)
		{
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}
