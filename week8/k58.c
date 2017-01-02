#include "digraph.h"
int id[20];
	typedef struct
	{
		char name[20];
	}_name;
	_name save[20];
int inputFile(Graph *graph);


int main()
{	
	int id1;
	int i, j, number;
	int edge_num = 0;
	Graph graph;
	// printf("NODE1\n");
	graph = createGraph();
	// number is int var that shows the number of vertices
	number = inputFile(&graph);
	// for(i = 1; i <= number; i++)
	// {
	// 	printf("* %s \n", getVertexName(graph,i));
	// }
	// printf("Enter an ID \n");
 //    scanf("%d" ,&id1);
    // printf("CODE: %s \n", getVertexName(graph, id[id1]));


	printf("1. Number of vertices = %d\n", number);
	// number of edges
	for(i = 1; i <= number; i++)
	{
		for(j = i + 1; j <= number; j++)
			{
				if( (hasEdge(graph, i, j) == 1) || (hasEdge(graph, j, i) == 1) )
					edge_num++;
			}	
	}
	printf("2. Number of edge_num = %d\n", edge_num);
	printf("3. Kiem tra tinh chu trinh\n");
	

	if (DAG(graph) == 0)
        printf("Co chu trinh\n");
    else
    {
    	printf("HOP LE\n");
    	printf("Enter an ID \n");
    	scanf("%d" ,&id1);
    	printf("CODE: %s \n", getVertexName(graph, id[id1]));
    //     printf("The topological order: \n");
    //     topologicalSort(g, output, &n, showVertexName);
    //     printf("\n");
    }
    dropGraph(graph);
	return 0;
}

int inputFile(Graph *g)
{
	int number, i;
	char str[150];
	char *token;
	int v1, v2;
	
	// int id = 1;
	FILE *f1;
	// printf("NODE2\n");
	f1 = fopen ("class.dat", "r");
	if (f1 == NULL)
	{
		printf("Can't open file!");
		return 0;
	}
	else
	{
		// printf("NODE3\n");
		// Graph g;
		// (*g) = createGraph();
		fscanf(f1, "%d\n", &number);
		printf("number = %d \n", number);
		for(i = 1; i <= number; i++)
		{
			fgets(str, 50, f1);
			token = strtok(str, " ");
			v1 = token[0] - '0';
			id[v1] = v1;
			strcpy(save[v1].name, token);
			addVertex((*g), id[v1], save[v1].name);
			token = strtok(NULL, " ");
			while(token[0] != '\n')
			{
			v2 = token[0] - '0';
			id[v2] = v2;
			strcpy(save[v2].name, token);
			addVertex((*g), id[v2], save[v2].name);
			addEdge((*g), id[v2], id[v1]);
			token = strtok(NULL, " ");
			}
		}
		fclose(f1);
		for(i = 1; i <= number; i++)
		{
			showVertexName(*g, i);
			printf("\n");
		}
		return number;
	}
			// return g;

}