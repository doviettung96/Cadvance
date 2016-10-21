#include "libfdr.h"

#define MAX 1000

void main() {
	int i = 0;
	int rd;
	int key;
	jval val[MAX];
	JRB tree = make_jrb();
	JRB result = make_jrb();
	srand(time(NULL));
	for (i = 0; i < MAX; ++i)
	{
		rd = rand() % 1000;
		val[i] = new_jval_i(rd);
		tree = jrb_insert_int(tree, i, val[i]);
	}
	printf("Type in the key: ");
	scanf("%d", &key);
	result = jrb_find_int(tree, key);
	if(result != NULL)
		printf("\nResult: %d\n", result.key.i);

}

