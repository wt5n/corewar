#include "inc/vm.h"

int get_value(t_cw *cw, t_koretko *koretko);

void	op_add(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int c;
	int value;

	a = get_value(cw, kor);
	b = get_value(cw, kor);
	c = get_value(cw, kor);
	kor->step += 5;
	value = kor->regs[a - 1] + kor->regs[b];
	kor->carry = value == 0 ? 1 : 0;
}

void	op_sub(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int c;
	int value;

	a = get_value(cw, kor);
	b = get_value(cw, kor);
	c = get_value(cw, kor);
	kor->step += 5;
	value = kor->regs[a - 1] - kor->regs[b];
	kor->carry = value == 0 ? 1 : 0;
}

void 	op_and(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int reg;
	int value;

	a = get_value(cw, kor);
	b = get_value(cw, kor);
	reg = get_value(cw, kor);
	kor->step += 5;
	value = a & b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
}

void 	op_or(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int reg;
	int value;

	a = get_value(cw, kor);
	b = get_value(cw, kor);
	reg = get_value(cw, kor);
	kor->step += 5;
	value = a | b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
}

void 	op_xor(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int reg;
	int value;

	a = get_value(cw, kor);
	b = get_value(cw, kor);
	reg = get_value(cw, kor);
	kor->step += 5;
	value = a ^ b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
}

void 	op_st(t_cw *cw, t_koretko *kor)
{
	int reg;
	int second_arg;

	reg = get_value(cw, kor);
	second_arg =
	if (kor-)
}

//void	op_live(t_koretko *kor, int arg)
//{
//
//	if (arg == )
//}