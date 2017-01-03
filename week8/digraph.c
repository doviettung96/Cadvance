#include "digraph.h"

Graph createGraph()
{
	Graph graph;
	graph.edges = make_jrb();
	graph.vertices = make_jrb();
	return graph;
}

void index_to_name(int i, int j, char *name){
	sprintf(name, "%d%d", i, j);
}

void add_all_vertices(Graph G, char *fn){
	IS is = new_inputstruct(fn);
	if(!is){
		printf("error!\n");
		return;
	}
	char *name;
	while(get_line(is) >= 0){
		name = (char*)malloc(sizeof(char)*10);
		strcpy(name, is->fields[0]);
		add_vertex_auto_increment(G, name);
		log("add vertex: '%s'\n", name);
	}
	jettison_inputstruct(is);
}

void add_all_edges(Graph G, char *fn){
	IS is = new_inputstruct(fn);
	if(!is){
		printf("error!\n");
		return;
	}
	char name1[10], name2[10];
	int v1, v2, i;
	double w;
	char *token;
	char temp[100];
	while(get_line(is) >= 0){
		strcpy(name2, is->fields[0]);
		for(i=2; i<is->NF; i++){
			strcpy(temp, is->fields[i]);
			token = strtok(temp, "-");
			if(token){
				strcpy(name1, token);
				token = strtok(NULL, "-");
				w = atof(token);
				v1 = get_vertex_id(G, name1);
				v2 = get_vertex_id(G, name2);
				if(v1 < 0 || v2 < 0)
					continue;
				add_edge(G, v1, v2, w, DIRECTED);
				log("add edge %s -> %s weight=%f\n", name1, name2, w);	
			}
		}
	}
	jettison_inputstruct(is);
}
int countVertices(Graph graph)
{
	int count = 0;
	JRB node;
	jrb_traverse(node, graph.vertices)
	count++;
	return count;
}

int countEdges(Graph graph)
{
	int count = 0;
	JRB node;
	int output[getMaxId(graph) + 1];
	jrb_traverse(node, graph.vertices)
	count += inDegree(graph, jval_i(node->key), output);
	return count;
}

void addVertex(Graph graph, int id, char *name)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return;
	JRB node = jrb_find_int(graph.vertices, id);
	if (node == NULL)
		jrb_insert_int(graph.vertices, id, new_jval_s(name));
}

void add_vertex_auto_increment(Graph graph, char *name) {
	if (graph.edges == NULL || graph.vertices == NULL)
		return;
	if (getVertexId(graph, name) != -1)
		return;
	int v = getMaxId(graph) + 1;
	addVertex(graph, v, name);
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

int getVertexId(Graph graph, char *name)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return -1;

	JRB node;
	jrb_traverse(node, graph.vertices)
	if (!strcmp(name, jval_s(node->val)))
		return jval_i(node->key);
	return -1;
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
	output[total++] = jval_i(node->key);
	return total;
}


int inDegree(Graph graph, int v, int *output)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return 0;

	JRB node = jrb_find_int(graph.vertices, v);
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

	node = jrb_find_int(graph.vertices, start);
	if (node == NULL)
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

	node = jrb_find_int(graph.vertices, start);
	if (node == NULL)
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


void DFS_all(Graph graph, void (*visitFunc)(Graph, int))
{
	int max_id = getMaxId(graph);

	int *visited = (int*)malloc(sizeof(int) * (max_id + 1));
	if (visited == NULL) {
		fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
		exit(1);
	}
	for (int i = 0; i <= max_id; ++i)
		visited[i] = 0;

	for (int i = 0 ; i <= max_id; ++i)
		if (!visited[i])
			DFS_ulti(graph, i, -1, visitFunc, visited);
	free(visited);
}

void DFS_ulti(Graph graph, int start, int stop, void (*visitFunc)(Graph, int), int *visited)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return;

	Dllist stack = new_dllist();
	JRB node = jrb_find_int(graph.vertices, start);
	if (node == NULL)
		return;

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
			return;

		JRB u = jrb_find_int(graph.edges, v);

		if (u == NULL)
			continue;

		JRB connect_to_u = (JRB) jval_v(u->val);
		JRB temp;
		jrb_traverse(temp, connect_to_u)
		{
			if (visited[jval_i(temp->key)] == 0)
				dll_append(stack, new_jval_i(temp->key.i));
		}
	}
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

	node = jrb_find_int(graph.vertices, vertex);
	if (node == NULL)
		goto end;

	int flag = 0;

	dll_append(stack, new_jval_i(vertex));
//prepare before visit all  vertices

	while (!dll_empty(stack))
	{
		Dllist node = dll_last(stack);
		int v = jval_i(node->val);
		dll_delete_node(node);
		//pop an element from the stack

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

		flag = flag + 1; //start to run the inverse way from the beginning

		JRB v_node = jrb_find_int(graph.vertices, v);

		if (v_node == NULL)
			continue;

		int *out_degree_list = (int *)malloc(sizeof(int) * (max_id + 1));
		if (out_degree_list == NULL) {
			fprintf(stderr, "%s %s:%d\n", "malloc failed in", __FILE__, __LINE__);
			exit(1);
		}
		//out degree vertices list of u

		int out_degree_num = outDegree(graph, v, out_degree_list);
		//number of out degree vertices of v
		if (out_degree_num == 0)
			continue;

		for (int i = 0; i < out_degree_num; ++i)
		{
			int temp = out_degree_list[i];
			if (visited[temp] == 0)
				dll_append(stack, new_jval_i(temp));
		}
		//traverse through the out degree list of vertex v
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

void topologicalSort(Graph g, int *output, int *n, void (* visitFunc)(Graph, int))
{
	int count = 0;
	if (g.edges == NULL || g.vertices == NULL)
		return;
	Dllist queue = new_dllist(); //initialize an empty queue
	JRB temp;
	JRB node = jrb_find_int(g.vertices, getMinId(g));
	if (node == NULL)
		goto end;

	int max_id = getMaxId(g);
	int *in_degree_table = malloc(sizeof(int) * (max_id + 1)); //in degree table of the DAG
	if (in_degree_table == NULL) {
		fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
		exit(1);
	}

	int *in_degree_list_v = malloc(sizeof(int) * (max_id + 1)); //in degree list of v
	if (in_degree_list_v == NULL) {
		fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
		exit(1);
	}

	jrb_traverse(temp, g.vertices)
	{
		int v = jval_i(temp->key);
		if ((in_degree_table[v] = inDegree(g, v, in_degree_list_v)) == 0)
			dll_append(queue, new_jval_i(v));
	}
	free(in_degree_list_v);
	//enqueue all the vertices with in_degree == 0

	while (!dll_empty(queue))
	{
		Dllist node = dll_first(queue);
		int u = jval_i(node->val);
		dll_delete_node(node);
		//just the normal dequeue
		output[count++] = u;
		visitFunc(g, u);

		int *out_degree_list_u = malloc(sizeof(int) * (max_id + 1)); //out degree list of u
		//we use it to consider arc(u, w)
		if (out_degree_list_u == NULL) {
			fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
			exit(1);
		}

		int out_degree_num_u = outDegree(g, u, out_degree_list_u);
		//traverse through all out degree vertices of u
		if (out_degree_num_u != 0) // if we have out degree vertices of u
		{
			for (int i = 0; i < out_degree_num_u; ++i)
			{
				int w = out_degree_list_u[i];
				in_degree_table[w] -= 1;

				if (in_degree_table[w] == 0)
					dll_append(queue, new_jval_i(w));
			}
		}
		free(out_degree_list_u);
	}
end:
	*n = count;
	free(in_degree_table);
	free_dllist(queue);
}

void dropGraph(Graph graph)
{
	JRB node;
	jrb_traverse(node, graph.edges)
	{
		jrb_free_tree(jval_v(node->val));
	}
	jrb_free_tree(graph.vertices);
	jrb_free_tree(graph.edges);
	//maybe add graph == NULL then check if the context error is reduced or not
}