#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union {
	int i;
	long l;
	float f;
	double d;
	void *v;
	char *s;
	char c;
} jval;

int jval_i(jval j);

jval new_jval_int(int val);

jval new_jval_float(float val);

jval new_jval_double(double val);

jval new_jval_string(char* val);

jval new_jval_void(void* val, size_t size);

jval new_jval_long(long val);

jval new_jval_char(char val);

void exch(jval *a, jval *b);

void sort_gen(jval *arr, int l, int r, int (*compare)(jval *, jval *));

void sort_gen_int(jval *arr, int l, int r);

int search_gen(jval *arr, int l, int r, jval val, int (*compare)(jval *, jval *));

int search_gen_int(jval *arr, int l, int r, jval val);

int compare_int(jval *a, jval *b);
