#include <stdio.h>
#include <stdlib.h>

typedef union {
	int i;
	long l;
	float f;
	double d;
	void *v;
	char *s;
	char c;
} Jval;

Jval new_jval_i(int i);
Jval new_jval_l(long l);
Jval new_jval_f(float f);
Jval new_jval_d(double d);
Jval new_jval_v(void *v);
int jval_i(Jval j);
long jval_l(Jval j);
float jval_f(Jval j);
double jval_d(Jval j);
void *jval_v(Jval j);

