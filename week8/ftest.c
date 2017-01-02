#include "digraph.h"

int main()
{
	IS is;
	Graph graph = createGraph();
	int n;
	int output[10];
	is = new_inputstruct("input.txt");

	get_line(is);
	int num = atoi(is->fields[0]);
	char *name1, *name2;

	name2 = (char *)malloc(sizeof(char) * 10);

	for (int i = 0; i < num; ++i)
	{
		get_line(is);
		for (int j = 0; j < is->NF; ++j)
		{
			name1 = (char *)malloc(sizeof(char) * 10);
			strcpy(name1, is->fields[0]);
			add_vertex_auto_increment(graph, name1);
			if (j < 1)
				continue;

			strcpy(name2, is->fields[j]);
			addEdge(graph, getVertexId(graph, name2), getVertexId(graph, name1));
		}
	}
	for (int i = 0; i < num; ++i)
		showVertexName(graph, i + 1);
	printf("\nNumber of vertices: %d\n", countVertices(graph));
	printf("Number of edges: %d\n", countEdges(graph));
	printf("Topological sort order:\n");
	topologicalSort(graph, &n, output, showVertexName);
	
	printf("\n");
	free(name1);
	free(name2);
	dropGraph(graph);
	jettison_inputstruct(is);
	return 0;
}