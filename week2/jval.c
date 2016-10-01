#include "jval.h"

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