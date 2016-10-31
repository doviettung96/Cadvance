#include "graph_rb.h"

Graph createGraph()
{
	return make_jrb();
}

int adjacent(Graph graph, int v1, int v2)
{
	if (graph == NULL)
		return 0;
	JRB findv1;
	JRB findv2, adjacentofV1;
	findv1 = jrb_find_int(graph, v1);
	// find v1 in the graph
	if (findv1 == NULL)
		return 0;
	adjacentofV1 = (JRB) jval_v(findv1->val);
	//a tree contains all adjacent node of V1
	findv2 = jrb_find_int(adjacentofV1, v2);
	if (findv2 != NULL)
		return 1;
	return 0;
}

// int adjacent(Graph graph, int v, int v2){
//      if(graph == NULL)
//           return 0;
                                    
//      JRB node = jrb_find_int(graph, v);                           
//      JRB tree;                                                
//      if(node == NULL)                                         
//           return 0;                                               
//      tree = (JRB) jval_v(node->val);                      
//      JRB f = jrb_find_int(tree, v2);
//      if(f != NULL)
//           return 1;
//      return 0;

// }


// void addEdge(Graph graph, int v, int v2) {
// 	if (adjacent(graph, v, v2))
// 		return;

// #define ADD_EDGE_MACRO(v, v2)  {                        \
//           JRB node = jrb_find_int(graph, v);                \
//           JRB tree;                                     \
//           if(node == NULL){                             \
//                tree = make_jrb();                       \
//                jrb_insert_int(graph, v, new_jval_v(tree));  \
//           }                                             \
//           else                                          \
//                tree = (JRB) jval_v(node->val);          \
//                jrb_insert_int(tree, v2, new_jval_i(1)); \
//                                                         \
//      } while(0);

// 	ADD_EDGE_MACRO(v, v2);
// #ifndef UDGGIN
// 	ADD_EDGE_MACRO(v2, v);
// #endif
// #undef ADD_EDGE_MACRO

// }

void addEdge(Graph graph, int v1, int v2)
{
	if (adjacent(graph, v1, v2))
		return;
#define ADD_EDGE_MACRO(v1, v2) {  								\
		JRB findNode = jrb_find_int(graph, v1); 					\
		JRB nodev1;												\
		JRB adjacentofV1; 										\
		if (findNode == NULL) 									\
		{														\
			nodev1 = make_jrb();								\
			jrb_insert_int(graph, v1, new_jval_v(nodev1)); 		\
		}														\
		else 													\
			nodev1 = (JRB) jval_v(findNode->val); 				\
			jrb_insert_int(nodev1, v2, new_jval_i(1)); 			\
	}	while(0);

	ADD_EDGE_MACRO(v1, v2);
	ADD_EDGE_MACRO(v2, v1);
#undef ADD_EDGE_MACRO

}


int getAdjacentVertices (Graph graph, int v, int* output)
{
	if (graph == NULL)
		return 0;

	JRB  adjacentofV1;
	int total = 0;
	JRB findNode = jrb_find_int(graph, v);

	if (findNode == NULL)
		return 0;
	adjacentofV1 = (JRB) jval_v(findNode->val);
	jrb_traverse(findNode, adjacentofV1)
	{
		output[total++] = jval_i(findNode->key);
	}
	return total;

	// if (graph == NULL)
	// 	return 0;
	// JRB node = jrb_find_int(graph, v);
	// JRB tree;
	// if (node == NULL)
	// 	return 0;
	// int total = 0;
	// tree = (JRB) jval_v(node->val);
	// jrb_traverse(node, tree)
	// output[total++] = jval_i(node->key);
	// return total;
}

void dropGraph(Graph graph)
{
	JRB ptr;
	jrb_traverse(ptr, graph)
	{
		jrb_free_tree(jval_v(ptr->val));
	}
	jrb_free_tree(graph);
	graph = NULL;
	//maybe add graph == NULL then check if the context error is reduced or not
}