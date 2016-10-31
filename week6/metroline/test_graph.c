#include "graph_rb.h"

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



void main()
{
	int i;
	char name[30];

	//do not use *output when you don't malloc it
	data = inputfromFile("input.graph");
	printf("%s\n", "LIST OF METRO STATIONS");
	for (i = 0; i < data.station_num; ++i)
	{
		printf("%3d. %s\n", i + 1, data.station_list[i].name);
	}
	printf("\n\n");

	printf("Type in a station name: ");
	scanf("%[^\n]", name);
	// printf("%s\n", name);
	showAdjacent(name);

	free(data.station_list);
	dropGraph(data.graph);
}

void showAdjacent(char name[])
{
	int i;
	int v1;
	int output[10];
	int numberofAdjacent;

	for (i = 0; i < data.station_num; ++i)
		if (strcmp(data.station_list[i].name, name) == 0)
		{
			v1 = i + 1;
			break;
		}

	numberofAdjacent = getAdjacentVertices(data.graph, v1, output);
	// printf("%d\n", numberofAdjacent);
	for (i = 0; i < numberofAdjacent; ++i)
		printf(" %s ", data.station_list[output[i] - 1].name);
	printf("\n\n");
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
	char *token;
	int v1, v2;

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
		fscanf(fin, "S%*d=%[^\n]\n", input.station_list[input.station_num++].name);
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
		fscanf(fin, "M%*d=%[^\n]\n", str);

		token = strtok(str, " ");
		v1 = token[1] - '0';
		token = strtok(NULL, " ");

		//get the first token]
		while (token != NULL)
		{
			v2 = token[1] - '0';
			addEdge(input.graph, v1, v2);
			v1 = v2;
			token = strtok(NULL, " ");
		}
		// printf("Error!\n");

		//walk through other tokens

		// for (int j = 0; j < i - 1; ++j)
		// 	addEdge(input.graph, vertices[i], vertices[i + 1]);
	}
	fclose(fin);
	return input;
}

