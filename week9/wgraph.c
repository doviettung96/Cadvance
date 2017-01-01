#include "wgraph.h"

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

double getEdgeValue(Graph graph, int v1, int v2)
{
	if (graph.edges == NULL || graph.vertices == NULL)
		return 0;

	if (!hasEdge(graph, v1, v2))
		return INFINITIVE_VALUE;
	JRB node = jrb_find_int(graph.edges, v1);
	JRB tree = (JRB) jval_v(node->val);
	JRB nodeV2 = jrb_find_int(tree, v2);
	return jval_d(nodeV2->val);
}

void addEdge(Graph graph, int v1, int v2, double weight)
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
			jrb_insert_int(tree, v2, new_jval_d(weight)); 			\
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
	free(in_degree_table);
	free_dllist(queue);
}

double shortestPath(Graph graph, int s, int t, int* path, double* length) {
  if (graph.edges == NULL || graph.vertices == NULL)
    return INFINITIVE_VALUE;

  if (path == NULL || length == NULL)
    return INFINITIVE_VALUE;

  int i, max_id = getMaxId(graph);
  if (t > max_id || s > max_id)
    return INFINITIVE_VALUE;

  double *dist = malloc(sizeof(double) * (max_id + 1));  // free ?
  int *prev = malloc(sizeof(int) * (max_id + 1));
  if (!dist || !prev) {
    fprintf(stderr, "%s%s:%d\n", "Allocated Failed in ", __FILE__, __LINE__);
    exit(1);
  }

  Dllist queue = new_dllist();   // free ?
  int min_id = getMinId(graph);

  JRB node;
  jrb_traverse(node, graph.vertices) {
    int u = jval_i(node->key);
    if (u != s) {
      dist[u] = INFINITIVE_VALUE;
      prev[u] = UNDEFINED;
    }
    dll_append(queue, new_jval_i(u));
  }

  dist[s] = 0;

  while (!dll_empty(queue)) {
    // extract min
    int u;
    {
      Dllist tmp, min_node = dll_first(queue);
      int min = jval_i(dll_first(queue)->val);
      dll_traverse(tmp, queue) {
        int tmp_node_i = jval_i(tmp->val);
        if (dist[min] > dist[tmp_node_i]) {
          min = tmp_node_i;
          min_node = tmp;
        }
      }
      u = min;
      dll_delete_node(min_node);
    }

    //
    int *out_degree_u_list = malloc(sizeof(int) * (max_id + 1));  // free ?
    if (!out_degree_u_list) {
      fprintf(stderr, "%s%s:%d\n", "Allocated Failed in ", __FILE__, __LINE__);
      exit(1);
    }
    int out_degree_u = outDegree(graph, u, out_degree_u_list);
    if (out_degree_u == 0)
      continue;

    int i;
    for (i = 0; i < out_degree_u; i++) {
      int v = out_degree_u_list[i];
      double alt = dist[u] + getEdgeValue(graph, u, v);
      if (alt < dist[v]) {
        dist[v] = alt;
        prev[v] = u;
        dll_append(queue, new_jval_i(v));
      }

    }
    free(out_degree_u_list);

  }

  for (i = min_id; i <= max_id; i++) {
    length[i] = dist[i];
  }

  if (prev[t] != -1) {
    int j = 1;
    path[0] = t;
    while (1) {
      path[j] = prev[path[j - 1]];
      if (path[j] == s || path[j] == -1)
        break;
      j++;
    }
    path[++j] = -1;
  }
  double ret = dist[t];
  //
  free_dllist(queue);
  free(dist);
  free(prev);
  return ret;
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