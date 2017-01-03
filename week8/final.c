#include "digraph.h"

#define MAXSECTION 7
Graph input(char fileName[]);
// char** str_split(char* a_str, const char a_delim);
Graph inputFromFile(char fileName[]);

void main()
{
	Graph graph;
	IS is;
	char fileName[30];
	char sections[MAXSECTION][40] = {"Create graph from file", "DAG", "Get prerequisites",
	                                 "Choose 3 or 5", "List all", "Topological Sort", "Drop graph",
	                                };
	do {
		choice = getMenu(sections, MAXSECTION);
		switch (choice)
		{
		case 1:
			printf("Type in a file name");
			scanf("%[^\n]", fileName);
			myfflush();

			graph = input(fileName);

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:
			break;
		case 5:

			break;

		case 6:

			break;
		case MAXSECTION:

			break;
		default:
			printf("Choice must be from 1 to %d\n", MAXSECTION);
			exit(1);
		}
	} while (choice != MAXSECTION && choice != 0);
}

Graph input(char fileName[])
{
	Graph graph = createGraph();
	IS is;
	char *name, *name1, *name2;
	int num_vertices, num_edges;
	is = new_inputstruct(fileName);

	if (!is) {
		printf("Can't read file");
		exit(1);
	}
	if (get_line(is) >= 0) {
		num_vertices = atoi(is->fields[0]);
		num_edges = atoi(is->fields[1]);
	}

	for (int i = 1; i <= num_vertices; ++i)
	{
		get_line(is);
		name = (char*)malloc(sizeof(char) * 10);
		strcpy(name, is->fields[i]);
		add_vertex_auto_increment(graph, name);
	}

	for(int i = 0; i < num_edges; ++i)
	{
		get_line(is);
		for(int j = 0; j < is->NF; ++j)
		{
			
		}
	}

	printf("Number of members: %d\n", num_vertices);
	printf("Number of relationships: %d\n", num_edges);
	jettison_inputstruct(is);
	free(name);
	return graph;
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

