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
	int v;

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
		v = jval_i(node->val);
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
	int v;

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

	while (!dll_empty(stack))
	{
		Dllist node = dll_last(stack);
		v = jval_i(node->val);
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