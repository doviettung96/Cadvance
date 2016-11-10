#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//for memcpy

int intCompare(void const *x, void const *y);
void exch(void *buf, int size, int i, int j);
void quick2Ways(void *buf, int size, int left, int right, int (*compare)(void const*, void const*));
void quick3Ways(void *buf, int size, int left, int right, int (*compare)(void const*, void const*));
int search(void *buf, int size, int left, int right, void *val, int (*compare)(void *, void *));