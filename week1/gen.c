#include <stdio.h>

typedef union {
	int i;
	long l;
	float f;
	double d;
	void *v;
	char *s;
	char c;
} Jval;

Jval new_jval_i(int i)
{
	Jval j;
	j.i = i;
	return j;
}
Jval new_jval_l(long l)
{
	Jval j;
	j.l = l;
	return j;
}
Jval new_jval_f(float f)
{
	Jval j;
	j.f = f;
	return j;
}
Jval new_jval_d(double d)
{
	Jval j;
	j.d = d;
	return j;
}
Jval new_jval_v(void *v)
{
	Jval j;
	j.v = v;
	return j;
}

int jval_i(Jval j)
{
	return j.i;
}
long jval_l(Jval j)
{
	return j.l;
}
float jval_f(Jval j)
{
	return j.f;
}
double jval_d(Jval j)
{
	return j.d;
}
void *jval_v(Jval j)
{
	return j.v;
}

void exch(void *buf, int size, int i, int j)
{
	void *temp = buf[i];
	buf[i] = buf[j];
	buf[j] = temp;
}

void sort(void* a, int size, int l, int r,
          int (*compare)(void*, void*)) {
	if (r <= l) return;
	int i = l - 1, j = r;
	int p = l - 1, q = r;
	while (1)	{
		while ( compare((char*)a + (++i)*size, (char*)a + r * size) < 0 );
		while (compare((char*)a + r * size, (char*)a + (--j)*size) < 0 )
			if (j == l) break;
		if (i >= j) break;
		exch(a, size, i, j);
		if (compare((char*)a + i * size, (char*)a + r * size) == 0)
			exch(a, size, ++p, i);
		if (compare((char*)a + j * size, (char*)a + r * size) == 0)
			exch(a, size, --q, j);
	}
	exch(a, size, i, r);
	j = i - 1;
	i = i + 1;
	for (int k = l ; k <= p; k++) exch(a, size, k, j--);
	for (int k = r - 1; k >= q; k--) exch(a, size, k, i++);
	sort(a, size, l, j, compare);
	sort(a, size, i, r, compare);
}

void main()
{

}