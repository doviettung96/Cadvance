#include "jrb.h"
#include "jval.h"
// #include "dllist.h"
#include "fields.h"
#include <stdlib.h>

#define MAX 10

void main() {
	int i = 0;

	Jval val[MAX];
	JRB tree = make_jrb();
	JRB result, ptr;
	char name[30];
	int key;

	srand(time(NULL));
	for (i = 0; i < MAX; ++i)
	{

		val[i] = new_jval_i(rand() % 100);
		jrb_insert_int(tree, i, val[i]);
		// printf("Inserted!\n");
	}
	jrb_traverse(ptr, jrb_last(tree)) \ printf("%d", ptr->val.i);
	// for (i = 0; i < MAX; ++i)
	// {

	// 	result = jrb_find_int(tree, i);
	// 	val[i] = jrb_val(result);
	// 	// if (*found == 1)
	// 	printf("%d ", val[i].i);
	// }
	printf("\n");
	printf("Type in the key: ");
	scanf("%d", &key);
	result = jrb_find_int(tree, key);
	if (result != NULL)
		printf("\nResult: %d\n", result->val.i);

}

