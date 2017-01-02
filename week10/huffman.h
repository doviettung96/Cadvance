#include "digraph.h"

typedef struct {
   Graph graph;
   JRB root;
} HuffmanTree;

typedef struct {
	int freq; //the frequency of a character
	char bits[2]; //the binary code for the character 'A' = 65
} Coding;
Coding huffmanTable[256];

HuffmanTree makeHuffman (char * buffer, int size);
void createHuffmanTable(HuffmanTree htree, Coding *htable);