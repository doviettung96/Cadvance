#include "gen.h"

#include <time.h>
#include <string.h>

#define MAX 10000000

int *createArray(int size)
{
	int i;
	int *a;
	a = (int *)malloc(sizeof(int) * size);
	if (a == NULL)
		exit(1);
	srand(time(NULL));
	for (i = 0; i < size; ++i)
		a[i] = rand() % 10;
	return a;
}

void display(int a[], int size)
{
	int i;
	for (i = 0; i < size; ++i)
		printf("%d ", a[i]);
}

void main()
{
	int *a = createArray(MAX);
	int *b, *c;
	b = (int *)malloc(sizeof(int) * MAX);
	c = (int *)malloc(sizeof(int) * MAX);
	time_t start, end;


	memcpy(b, a, MAX * sizeof(int));
	memcpy(c, a, MAX * sizeof(int));
	// for(int i = 0; i < MAX; ++i)
	// 	printf("%d ", a[i]);
	start = time(NULL);
	quick2Ways(a, sizeof(int), 0 , MAX - 1 , intCompare);
	end = time(NULL);
	// display(a, MAX);
	printf("\nTime difference 1: %f\n", difftime(end, start));

	start = time(NULL);
	quick3Ways(b, sizeof(int), 0 , MAX - 1, intCompare);
	end = time(NULL);
	// display(b, MAX);
	printf("\nTime difference 2: %f\n", difftime(end, start));

	start = time(NULL);
	qsort(c, MAX, sizeof(int), intCompare);
	end = time(NULL);
	// display(c, MAX);
	printf("\nTime difference 3: %f\n", difftime(end, start));

	free(a);
	free(b);
	free(c);
}