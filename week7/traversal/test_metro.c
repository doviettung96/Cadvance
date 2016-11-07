#include "graph_rb.h"

#define MAXSECTION 5

typedef struct {
	char name[100];
} station;

typedef struct {
	station *station_list;
	int station_num;
	Graph graph;
} map;

map data;

map inputfromFile(char fileName[]);
void showAdjacent(char name[]);
void showNode(int vertex);
void shortestPath(char m1[], char m2[]);
map get_data_from_file(const char *file_name);

void main()
{
	int i;
	char name[100];
	char m1[100], m2[100];
	char sections[MAXSECTION][40] = {"Input from file", "Show the list of metro stations", "Find nearby stations", "Shortest path", "Exit"};
	int choice;
	do {
		choice = getMenu(sections, MAXSECTION);
		switch (choice)
		{
		case 1:
			data = get_data_from_file("input.graph");
			// data = inputfromFile("input.graph");
			break;
		case 2:
			printf("%s\n", "LIST OF METRO STATIONS");
			for (i = 0; i < data.station_num; ++i)
			{
				printf("%3d. %s\n", i + 1, data.station_list[i].name);
			}
			printf("\n\n");
			break;
		case 3:
			printf("Type in a station name: ");
			scanf("%[^\n]", name);
			myfflush();
			showAdjacent(name);
			break;
		case 4:
			printf("Type in the name of 2 stations: ");

			printf("\n1st: ");
			scanf("%[^\n]", m1);
			myfflush();
			printf("2nd: ");
			scanf("%[^\n]", m2);
			myfflush();

			printf("The shortest path between %s and %s: \n", m1, m2);
			shortestPath(m1, m2);
			printf("\n");
			break;
		case 5:
			free(data.station_list);
			dropGraph(data.graph);
			break;
		default:
			printf("Choice must be from 1 to %d\n", MAXSECTION);
			exit(1);
		}
	} while (choice != MAXSECTION && choice != 0);
}

void showNode(int vertex)
{
	printf(" %s ", data.station_list[vertex - 1].name);
}

void shortestPath(char m1[], char m2[])
{
	int i;
	int v1 = 0, v2 = 0;
	for (i = 0; i < data.station_num; ++i)
	{
		if (strcmp(data.station_list[i].name, m1) == 0)
			v1 = i + 1;
		if (strcmp(data.station_list[i].name, m2) == 0)
			v2 = i + 1;
	}

	if (v1 != 0 && v2 != 0)
		BFS(data.graph, v1, v2, showNode);
	else
		printf("Wrong station name\n");
}

void showAdjacent(char name[])
{
	int i;
	int v1 = 0;
	int output[10];
	int numberofAdjacent;

	for (i = 0; i < data.station_num; ++i)
		if (strcmp(data.station_list[i].name, name) == 0)
		{
			v1 = i + 1;
			break;
		}

	if (v1 != 0)
	{
		numberofAdjacent = getAdjacentVertices(data.graph, v1, output);
		// printf("%d\n", numberofAdjacent);
		for (i = 0; i < numberofAdjacent; ++i)
			showNode(output[i]);
		printf("\n\n");
	}
	else
		printf("Wrong station name\n");
}


map get_data_from_file(const char *file_name) {
	FILE *f = fopen(file_name, "r");
	if (f == NULL) {
		fprintf(stderr, "Can't Open file %s !!\n", file_name);
		exit(1);
	}

	char temp[100];

	while (1) {
		fgets(temp, 100, f);
		if (strcmp(temp, "[STATIONS]\n") == 0)
			break;
	}

	int MAX = 10;
	map ret;

	ret.station_list = (station *)malloc(sizeof(station) * MAX);
	ret.station_num = 0;
	ret.graph = createGraph();

	// station name parse

	while (1) {
		fgets(temp, 100, f);
		if (strcmp(temp, "[LINES]\n") == 0)
			break;
		if (strcmp(temp, "\n") == 0)
			continue;

		int i;
		for (i = 0; temp[i] != '\0' && temp[i] != '='; i++);
		if (temp[i] == '\0')
			continue;

		if (ret.station_num == MAX - 1) {
			MAX += 10;
			ret.station_list = (station *)realloc(ret.station_list, sizeof(station) * MAX);
			if (ret.station_list == NULL) {
				fprintf(stderr, "Reallocate failed in %s:%d !!\n", __FILE__, __LINE__);
				exit(1);
			}
		}

		sscanf(temp, "S%*d=%[^\n]\n", ret.station_list[(ret.station_num)++].name);
	}

	// lines parse
	while (1) {
		fgets(temp, 100, f);
		if (feof(f))
			break;
		if (strcmp(temp, "\n") == 0)
			continue;

		int i;
		for (i = 0; temp[i] != '\0' && temp[i] != '='; i++);
		if (temp[i] == '\0')
			continue;
		char temp2[100];

		sscanf(temp, "%*[^=]=%[^\n]", temp2);

		char *p = strtok(temp2, " ");
		int v;
		v = p[1] - '0';
		p = strtok(NULL, " ");
		while ( p != NULL )
		{
			int v2 = p[1] - '0';
			addEdge(ret.graph, v, v2);
			v = v2;
			p = strtok(NULL, " ");
		}
	}
	fclose(f);
	return ret;
}

map inputfromFile(char fileName[])
{
	map input;
	FILE *fin;
	int MAX = 10;
	if ((fin = fopen(fileName, "r")) == 0)
	{
		printf("Can't open file %s\n", fileName);
		exit(1);
	}
	int i = 0;
	char temp[100];
	char str[100];

	input.station_list = (station *)malloc(sizeof(station) * MAX);
	input.graph = createGraph();
	input.station_num = 0;

	while (1)
	{
		fgets(temp, 100, fin);
		if (strcmp(temp, "[STATIONS]\n") == 0)
			break;
	}

	for (int j = 0; j < MAX - 1; ++j)
	{
		fscanf(fin, "S%*d=%[^\n]\n", input.station_list[(input.station_num)++].name);
		// printf("%s ", input.station_list[j].name);
	}
	// printf("Error!\n");

	while (1)
	{
		fgets(temp, 100, fin);
		if (strcmp(temp, "[LINES]\n") == 0)
			break;
	}
	if (input.station_num == MAX - 1)
	{
		MAX += 10;
		input.station_list = (station *)realloc(input.station_list, sizeof(station) * MAX);
	}
	while (!feof(fin))
	{
		// printf("Error!\n");
		fscanf(fin, "%*[^=]=%[^\n]\n", str);

		char *token = strtok(str, " ");
		int v;
		v = token[1] - '0';
		token = strtok(NULL, " ");
		while ( token != NULL )
		{
			int v2 = token[1] - '0';
			addEdge(input.graph, v, v2);
			v = v2;
			token = strtok(NULL, " ");
		}
		// token = strtok(str, " ");
		// v1 = token[1] - '0';
		// token = strtok(NULL, " ");

		// //get the first token]
		// while (token != NULL)
		// {
		// 	v2 = token[1] - '0';
		// 	addEdge(input.graph, v1, v2);
		// 	v1 = v2;
		// 	token = strtok(NULL, " ");
		// }
		// printf("Error!\n");

		//walk through other tokens

		// for (int j = 0; j < i - 1; ++j)
		// 	addEdge(input.graph, vertices[i], vertices[i + 1]);
	}
	fclose(fin);
	return input;
}

