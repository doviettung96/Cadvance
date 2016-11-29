#include "digraph.h"

Graph createGraph()
{
	Graph graph;
	graph.edges = make_jrb();
	graph.vertices = make_jrb();
	return graph;
}

void addVertex(Graph graph, int id, char *name)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return;
	JRB node = jrb_find_int(graph.vertices, id);
	if (node == NULL)
		jrb_insert_int(graph.vertices, id, new_jval_s(name));
}

char *getVertexName(Graph graph, int id)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return NULL;

	JRB node = jrb_find_int(graph.vertices, id);
	if (node != NULL) {
		return jval_s(node->val);
	}
	return NULL;
}

void showVertexName(Graph graph, int id)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return ;

	JRB node = jrb_find_int(graph.vertices, id);
	if (node != NULL) {
		printf("%s ", jval_s(node->val));
	}
}


int hasEdge(Graph graph, int v1, int v2)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return 0;

	JRB node = jrb_find_int(graph.edges, v1);
	if (node == NULL)
		return 0;
	JRB tree = (JRB) jval_v(node ->val);
	JRB findV2 = jrb_find_int(tree, v2);
	if (findV2 != NULL)
		return 1;
	return 0;
}

void addEdge(Graph graph, int v1, int v2)
{
	if (hasEdge(graph, v1, v2))
		return;

#define ADD_EDGE_MACRO(v1, v2) {  								\
		JRB node = jrb_find_int(graph.edges, v1); 					\
		JRB tree;												\
		if (node == NULL) 									\
		{														\
			tree = make_jrb();								\
			jrb_insert_int(graph.edges, v1, new_jval_v(tree)); 		\
		}														\
		else 													\
			tree = (JRB) jval_v(node->val); 				\
			jrb_insert_int(tree, v2, new_jval_i(1)); 			\
	}	while(0);

	ADD_EDGE_MACRO(v1, v2);
#ifndef DIRECTED_GRAPH
	ADD_EDGE_MACRO(v2, v1);
#endif
#undef ADD_EDGE_MACRO

}

int outDegree(Graph graph, int v, int *output)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return 0;

	JRB node = jrb_find_int(graph.edges, v);
	if (node == NULL)
		return 0;
	int total = 0;
	JRB tree = (JRB)jval_v(node->val);
	jrb_traverse(node, tree)
	{
		output[total++] = jval_i(node->key);
	}

	return total;
}

int inDegree(Graph graph, int v, int *output)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return 0;

	JRB node = jrb_find_int(graph.edges, v);
	if (node == NULL)
		return 0;
	int total = 0;
	jrb_traverse(node, graph.vertices)
	{
		if (hasEdge(graph, jval_i(node->key), v))
			output[total++] = jval_i(node->key);
	}

	return total;
}



void BFS(Graph graph, int start, int stop, void (*visitFunc)(Graph, int))
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return;

	int max_id = getMaxId(graph);

	int *visited = (int*)malloc(sizeof(int) * (max_id + 1));
	if (visited == NULL) {
		fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
		exit(1);
	}

	JRB node;
	jrb_traverse(node, graph.vertices)
	visited[jval_i(node->key)] = 0;

	Dllist queue = new_dllist();

	node = jrb_find_int(graph.edges, start);
	if (graph.edges == NULL)
		goto end;


	dll_append(queue, new_jval_i(start));

	while (!dll_empty(queue))
	{
		Dllist node = dll_first(queue);
		int v = jval_i(node->val);
		dll_delete_node(node);

		if (visited[v] == 0)
		{
			visitFunc(graph, v);
			visited[v] = 1;
		}

		if (v == stop)
			goto end;

		JRB u = jrb_find_int(graph.edges, v);

		if (u == NULL)
			continue;

		JRB connect_to_u = (JRB)jval_v(u->val);
		JRB temp;
		jrb_traverse(temp, connect_to_u)
		{
			if (visited[jval_i(temp->key)] == 0)
				dll_append(queue, new_jval_i(temp->key.i));
		}
	}

end:
	printf("\n");

	free(visited);
	free_dllist(queue);
}

void DFS(Graph graph, int start, int stop, void (*visitFunc)(Graph, int))
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return;

	int max_id = getMaxId(graph);

	int *visited = (int*)malloc(sizeof(int) * (max_id + 1));
	if (visited == NULL) {
		fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
		exit(1);
	}

	JRB node;
	jrb_traverse(node, graph.vertices)
	visited[jval_i(node->key)] = 0;

	Dllist stack = new_dllist();

	node = jrb_find_int(graph.edges, start);
	if (graph.edges == NULL)
		goto end;


	dll_append(stack, new_jval_i(start));
//prepare before visiting all vertices
	while (!dll_empty(stack))
	{
		Dllist node = dll_last(stack);
		int v = jval_i(node->val);
		dll_delete_node(node);

		if (visited[v] == 0)
		{
			visitFunc(graph, v);
			visited[v] = 1;
		}

		if (v == stop)
			goto end;

		JRB u = jrb_find_int(graph.edges, v);

		if (u == NULL)
			continue;

		JRB connect_to_u = (JRB)jval_v(u->val);
		JRB temp;
		jrb_traverse(temp, connect_to_u)
		{
			if (visited[jval_i(temp->key)] == 0)
				dll_append(stack, new_jval_i(temp->key.i));
		}
	}

end:
	printf("\n");

	free(visited);
	free_dllist(stack);
}

int isCyclicUtil(Graph graph, int vertex)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return 0;

	int max_id = getMaxId(graph);

	int *visited = (int*)malloc(sizeof(int) * (max_id + 1));
	if (visited == NULL) {
		fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
		exit(1);
	}

	JRB node;
	jrb_traverse(node, graph.vertices)
	visited[jval_i(node->key)] = 0;

	Dllist stack = new_dllist();

	node = jrb_find_int(graph.edges, vertex);
	if (graph.edges == NULL)
		goto end;

	int flag = 0;

	dll_append(stack, new_jval_i(vertex));
//prepare before visit all  vertices

	while (!dll_empty(stack))
	{
		Dllist node = dll_last(stack);
		int v = jval_i(node->val);
		dll_delete_node(node);

		if (visited[v] == 0)
		{
			visited[v] = 1;
			if (flag == 0 && v == vertex)
				visited[v] = 0;
		}

		if (v == vertex && visited[vertex] == 1)
		{
			free(visited);
			free_dllist(stack);
			return 1;
		}
		//there is a cycle

		flag = flag + 1;

		JRB u = jrb_find_int(graph.edges, v);

		if (u == NULL)
			continue;

		int *out_degree_list = (int *)malloc(sizeof(int) * (max_id + 1));
		if (out_degree_list == NULL) {
			fprintf(stderr, "%s %s:%d\n", "malloc failed in", __FILE__, __LINE__);
			exit(1);
		}
		//out degree vertices of u
		int out_degree_num = outDegree(graph, v, out_degree_list);
		if (out_degree_num == 0)
			continue;

		for (int i = 0; i < out_degree_num; ++i)
		{
			int temp = out_degree_list[i];
			if (visited[temp] == 0)
				dll_append(stack, new_jval_i(temp));
		}

		free(out_degree_list);
	}

end:
	free(visited);
	free_dllist(stack);
	return 0;
}

int DAG(Graph graph)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return 0;
	JRB node;
	jrb_traverse(node, graph.vertices)
	{
		if (isCyclicUtil(graph, jval_i(node->key)))
			return 0;
	}
	return 1;
}

int getMaxId(Graph g) {
	if (g.edges == NULL || g.vertices == NULL)
		return 0;
	int max_id = 0;
	JRB tmp;
	jrb_traverse(tmp, g.vertices) {
		int key = jval_i(tmp->key);
		if (key > max_id)
			max_id = key;
	}
	return max_id;
}

int getMinId(Graph g) {
	if (g.edges == NULL || g.vertices == NULL)
		return 0;
	int min_id = 10000000;
	JRB tmp;
	jrb_traverse(tmp, g.vertices) {
		int key = jval_i(tmp->key);
		if (key < min_id)
			min_id = key;
	}
	return min_id;
}

void dropGraph(Graph graph)
{
	JRB ptr;
	jrb_traverse(ptr, graph.edges)
	{
		jrb_free_tree(jval_v(ptr->val));
	}
	jrb_free_tree(graph.vertices);
	jrb_free_tree(graph.edges);
	//maybe add graph == NULL then check if the context error is reduced or not
}