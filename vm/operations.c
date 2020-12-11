#include "inc/vm.h"

void	op_add(t_koretko *kor, int *a, int *b, int *c)
{
	*c = *a + *b;
	kor->carry = *c == 0 ? 1 : 0;
}

void	op_sub(t_koretko *kor, int *a, int *b, int *c)
{
	*c = *a - *b;
	kor->carry = *c == 0 ? 1 : 0;
}

void 	op_st(t_koretko *kor, int *a, int *b)
{

}