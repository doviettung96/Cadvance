#include "gen.h"

int intCompare(void const *x, void const *y)
{
	int m, n;
	m = *((int *)x);
	n = *((int *)y);
	if (m > n)
		return 1;
	else if (m < n)
		return -1;
	else
		return 0;
}

void exch(void *buf, int size, int i, int j) {
	char temp[size];
	memcpy(temp, (char *)buf + i, size);
	memcpy((char *)buf + i, (char *)buf + j, size);
	memcpy((char *)buf + j, temp, size);
}

void quick2Ways(void *buf, int size, int left, int right, int (*compare)(void const*, void const*))
{
	//from size we know the data type
	int i = left - 1;
	int j = right;

	if (right <= left )
		return;

	while (1)
	{
		while (compare((char *)buf + (++i) * size, (char *)buf + right * size) < 0);
		//(char *) *size = int, float ... *
		//stop when a[i] >= pivot
		while (compare((char *)buf + (--j) * size, (char *)buf + right * size) > 0)
			if(j == left)
				break;
		//stop when a[j] <= pivot

		if (i >= j)
			break;
		//when pointer cross

		exch(buf, size, i, j);
		//take the smaller to the left and bigger to the right of the pivot
	}


	exch(buf, size , i, right);
	//exchange pivot into middle
	j = i - 1;
	i = i + 1;
	//move cursor to adjacent to a[i]
	quick2Ways(buf, size, left, j, compare);
	quick2Ways(buf, size, i, right, compare);
}

void quick3Ways(void *buf, int size, int left, int right, int (*compare)(void const*, void const*))
{
	int i = left - 1;
	int j = right;
	int p = left - 1; //for 3 ways partitioning
	int q = right; //for 3 ways parttioning

	if (right <= left)
		return;
	while (1)
	{
		while (compare((char *)buf + (++i) * size, (char *)buf + right * size) < 0);
		//(char *) *size = int, float ... *
		//stop when a[i] >= pivot
		while (compare((char *)buf + (--j) * size, (char *)buf + right * size) > 0)
			if(j == left)
				break;
		//stop when a[j] <= pivot

		if (i >= j)
			break;
		//pointer cross

		exch(buf, size, i, j);
		//just like the 2 way

		if (compare((char *)buf + i * size, (char *)buf + right * size) == 0)
			exch(buf, size, ++p, i);

		//if a[i] == pivot then exchange it to the left
		if (compare((char *)buf + j * size, (char *)buf + right * size) == 0)
			exch(buf, size, --q, j);
		//if a[j] == pivot then exchange it to the right most before pivot

	}
	exch(buf, size, i, right);
	//exchange pivot to middle



	j = i - 1;
	i = i + 1;
	//move cursor to adjacent to a[i]

	//from left to p and from q to right, there are all pivot-equal elements

	for (int k = left; k <= p; ++k)
		exch(buf, size, k, j--);
	for (int k = right - 1; k >= q; --k)
		exch(buf, size, i++, k);
	quick3Ways(buf, size, left, j, compare);
	quick3Ways(buf, size, i, right, compare);
}
