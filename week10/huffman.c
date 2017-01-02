#include "huffman.h"


int compareFunc(void const *a, void const *b)
{
	int m, n;
	m = *((int *)a);
	n = *((int *)b);
	if (m == n)
		return 0;
	else if (m > n)
		return 1;
	else
		return -1;
}

void createHuffmanTable(HuffmanTree htree, Coding *htable)
{

}

HuffmanTree makeHuffman (char * buffer, int size)
{
	HuffmanTree htree;
	htree.graph = createGraph();
	JRB root = make_jrb();
// int freq; //the frequency of a character
// 	char bits[2]
// Coding huffmanTable[256];
	if (htree.graph.edges == NULL || htree.graph.vertices == NULL)
		return NULL;

	for (int i = 0; i < 256; ++i)
		huffmanTable[i].freq = 0;
	for (int i = 0; i < size; ++i)
		huffmanTable[buffer[i]].freq++;

	int countNode = 0;
	Dllist queue = new_dllist();
	for (int i = 0; i < 256; ++i)
		if (huffmanTable[i].freq > 0)
		{
			JRB node = jrb_find_int(htree.graph.vertices, i);
			if (node == NULL)
				jrb_insert_int(htree.graph.vertices, i, new_jval_i(huffmanTable[i].freq));
			countNode++;
		JRB queue_node = make_jrb();
		queue_node->key = new_jval_i(huffmanTable[i].freq);
		queue_node->val = new_jval_v(node);
		dll_append(queue, new_jval_v(queue_node));
		}

	//creating nodes and append to the queue

	while (!dll_empty(queue))
	{
		Dllist node1 = dll_first(queue);
		JRB tree1 = (JRB) jval_v(node->val);
		dll_delete_node(node1);
		Dllist node2 = dll_first(queue);
		JRB tree2 = (JRB) jval_v(node->val);
		dll_delete_node(node2);
		

	}
	// Coding temp[256];
	// memcpy(temp, huffmanTable, 256 * sizeof(Coding));
	// qsort(temp, 256, sizeof(Coding), compareFunc);

}