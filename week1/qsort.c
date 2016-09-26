#include "qsort.h"

void exch(int *a, int i, int j)
{
	int temp;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void quick2Ways(int a[], int left, int right)
{
	int i = left - 1;
	int j = right;
	int pivot = a[right];
	while (1)
	{
		while (i <= right && a[++i] < pivot);
		//stop when a[i] >= pivot
		while (j >= left && a[--j] > pivot);
		//stop when a[j] <= pivot

		if (i >= j)
			break;
		//when pointer cross

		exch(a, i, j);
		//take the smaller to the left and bigger to the right of the pivot
	}


	exch(a, i, right);
	//exchange pivot into middle
	j = i - 1;
	i = i + 1;
	//move cursor to adjacent to a[i]
	quick2Ways(a, left, j);
	quick2Ways(a, i, right);
}

void quick3Ways(int a[], int left, int right)
{
	int i = left - 1;
	int j = right;
	int p = left - 1; //for 3 ways partitioning
	int q = right; //for 3 ways parttioning
	int pivot = a[right]; //choose a pivot as the rightmost one
	if (right <= 1)
		return;
	while (1)
	{
		while (i <= right && a[++i] < pivot);
		while (j >= left && a[--j] > pivot)

			exch(a, i, j);
		//just like the 2 way

		if (a[i] == pivot)
		{
			p++;
			exch(a, p, i);
		}
		//if a[i] == pivot then exchange it to the left
		if (a[j] == pivot)
		{
			q--;
			exch(a, q, j);
		}
		//if a[j] == pivot then exchange it to the right most before pivot

		exch(a, i, right);
		//exchange pivot to middle

		if (i >= j)
			break;
		//pointer cross

		j = i - 1;
		i = i + 1;
		//move cursor to adjacent to a[i]

		//from left to p and from q to right, there are all pivot-equal elements

		for (int k = left; k < p; ++k, --j)
			exch(a, k, j);
		for (int k = right - 1; k > q; --k, ++i)
			exch(a, i, k);
		quick3Ways(a, left, j);
		quick3Ways(a, i, right);
	}
}