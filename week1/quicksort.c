#include "sort.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 10000

int intCmp(void const *x, void const *y)
{
	if (x == y)
		return 0;
	else if (x > y)
		return 1;
	else
		return -1;
}

int *createArray(int size)
{
	int i;
	int *a;
	a = (int *)malloc(sizeof(int) * size);
	if(a == NULL)
		exit(1);
	srand(time(NULL));
	for(i = 0; i < size; ++i)
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
	start = time(NULL);
	quick2Ways(a, 0, MAX);
	end = time(NULL);
	// display(a, MAX);
	printf("Time difference 1: %f\n", difftime(end, start));

	start = time(NULL);
	quick3Ways(b, 0, MAX);
	end = time(NULL);
	// display(a, MAX);
	printf("Time difference 2: %f\n", difftime(end, start));

	start = time(NULL);
	qsort(c, MAX, sizeof(int), intCmp);
	end = time(NULL);
	// display(a, MAX);
	printf("Time difference 3: %f\n", difftime(end, start));

	free(a);
	free(b);
	free(c);
}