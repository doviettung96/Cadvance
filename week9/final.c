#include "wgraph.h"

#define MAXSECTION 8
Graph input(char *fileName, int *num_vertices, int *num_edges);

// char** str_split(char* a_str, const char a_delim);
// Graph inputFromFile(char fileName[]);
int fatherandmother(Graph graph, int num_vertices);
int nomorethan2(Graph graph, int num_vertices);
void noti(int mode);

void main()
{
	Graph graph;
	int choice;
	int n, output[10];
	char fileName[100];
	char name[10];
	int num_edges, num_vertices;
	char sections[MAXSECTION][40] = {"Create graph from file", "Can't be both", "No more than 2 parents",
	                                 "DAG", "List all", "Topological Sort", "Find all ascendants",
	                                 "Exit"
	                                };
	do {
		choice = getMenu(sections, MAXSECTION);
		switch (choice)
		{
		case 1:

			printf("Type in a file name: ");
			scanf("%[^\n]", fileName);
			myfflush();

			graph = input(fileName, &num_vertices, &num_edges);
			printf("Success!\n");

			break;
		case 2:
			noti(fatherandmother(graph, num_vertices));
			break;
		case 3:
			noti(nomorethan2(graph, num_vertices));
			break;
		case 4:
			if (DAG(graph))
				noti(1);
			else
				noti(0);
			break;
		case 5:

			break;

		case 6:

			break;
		case 7:
			printf("Type in a name: ");
			scanf("%[^\n]", name);
			myfflush();

			topologicalSort(graph, output, &n);
			printf("Ascendants of %s\n", name);
			for (int i = getVertexId(graph, name) - 1; i > 0; --i)
				printf("%d ", output[i]);
			printf("\n");
			break;
		case MAXSECTION:

			break;
		default:
			printf("Choice must be from 1 to %d\n", MAXSECTION);
			exit(1);
		}
	} while (choice != MAXSECTION && choice != 0);
}

Graph input(char *fileName, int *num_vertices, int *num_edges)
{
	IS is;
	char *name;
	int parent, child;
	double rel;
	// int num_vertices, num_edges;

	Graph graph = createGraph();

	is = new_inputstruct(fileName);

	if (!is) {
		printf("Can't read file");
		exit(1);
	}

	if (get_line(is) >= 0) {
		*num_vertices = atoi(is->fields[0]);
		*num_edges = atoi(is->fields[1]);
	}

	for (int i = 1; i <= *num_vertices; ++i)
	{
		get_line(is);
		name = (char*)malloc(sizeof(char) * 10);
		strcpy(name, is->fields[0]);
		add_vertex_auto_increment(graph, name);
	}

	for (int i = 0; i < *num_edges; ++i)
	{
		get_line(is);
		for (int j = 0; j < is->NF; ++j)
		{
			parent = atoi(is->fields[0]);
			child = atoi(is->fields[1]);
			rel = atof(is->fields[2]);
			if (rel > 1)
			{
				printf("Wrong format of data\n");
				exit(1);
			}
		}
		addEdge(graph, parent, child, rel);
	}

	printf("Number of members: %d\n", *num_vertices);
	printf("Number of relationships: %d\n", *num_edges);
	jettison_inputstruct(is);
	free(name);
	return graph;
}

int fatherandmother(Graph graph, int num_vertices)
{
	int i;
	int n;
	int *output;
	float temp;
	for (i = 1; i <= num_vertices; ++i)
	{
		output = (int *)malloc(sizeof(int) * (num_vertices + 1));
		n = outDegree(graph, i, output);
		temp = getEdgeValue(graph, i, *output);
		for (int j = 1; j < n; ++j)
		{
			if (temp != getEdgeValue(graph, i, *(output + j)))
			{
				free(output);
				return 0;
			}
		}
	}
	free(output);
	return 1;
}

int nomorethan2(Graph graph, int num_vertices)
{
	int n;
	int *output;
	float temp;
	int count1 = 0;
	int count2 = 0;
	for (int i = 1; i <= num_vertices; ++i)
	{
		output = (int *)malloc(sizeof(int) * (num_vertices + 1));
		n = inDegree(graph, i, output);
		for (int j = 0; j < n; ++j)
		{
			if (getEdgeValue(graph, *(output + j), i) == 0)
				count1++;
			if (getEdgeValue(graph, *(output + j), i) == 1)
				count2++;
		}
	}
	if (count1 > 1 || count2 > 1) {
		free(output);
		return 0;
	}
	free(output);
	return 1;
}
void noti(int mode)
{
	if (mode == 1)
		printf("CONSISTENCY\n");
	else
		printf("INCONSISTENCY\n");
}

// Graph inputFromFile(char fileName[])
// {
// 	Graph graph = createGraph();
// 	FILE *f = fopen(fileName, "r");
// 	if (f == NULL) {
// 		fprintf(stderr, "Can't Open file %s !!\n", fileName);
// 		exit(1);
// 	}

// 	int num_line;
// 	fscanf(f, "%d\n", &num_line);
// 	char input_list[100];
// 	char name[num_line][100];
// 	char **token;
// 	int v1, v2;

// 	while (!feof(f))
// 	{
// 		char temp[100];
// 		fgets(temp, 100, f);
// 		if (temp[strlen(temp) - 1] == 10 )
// 			temp[strlen(temp) - 1] = 0;

// 		token = str_split(temp, ' ');

// 		v1 = atoi(*(token));
// 		addVertex(graph, v1, *(token));
// 		if (token)
// 		{
// 			for (int i = 1; * (token + i); i++)
// 			{
// 				v2 = atoi(*(token + i));
// 				addEdge(graph, v2, v1);
// 			}
// 		}
// 	}
// 	for (int i = 0; * (token + i); i++)
// 		free(*(token + i));
// 	fclose(f);
// 	free(token);
// 	return graph;
// }

