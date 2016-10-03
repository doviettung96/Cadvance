#include "jval.h"
#include <time.h>

#define MAX 100

jval *create_array_jval_int(int size, int min, int max);
void print_array_jval(jval* arr, int size);

void main() {
	jval *a = create_array_jval_int(MAX, 0, 10);
	print_array_jval(a, MAX);
	sort_gen_int(a, 0, MAX - 1);
	print_array_jval(a, MAX);
}

jval *create_array_jval_int(int size, int min, int max) {
	jval* array;
	array = (jval *)malloc(sizeof(jval) * size);
	if (array == NULL) {
		fprintf(stderr, "Allocate failed in %s:%d", __FILE__, __LINE__);
		exit(1);
	}
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++) {
		array[i].i = min + rand() % (max - min);
	}
	return array;
}

void print_array_jval(jval* arr, int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%d\t", jval_i(arr[i]));
	}
	printf("\n");
}