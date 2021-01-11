#include "inc/vm.h"

int get_value(t_cw *cw, t_koretko *koretko, int arg)
{
	int ass;
	int value;

	ass = 0;
	ass = cw->map[(koretko->position + koretko->step) % MEM_SIZE];
	if (arg == T_REG)
	{
		value = ass;
	}
	else if (arg == T_DIR)
	{

	}
	else if (arg == T_IND)
	{

	}
	return value;
}

void	op_add(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int c;
	int value;
	kor->step += 2;
	a = cw->map[kor->position + kor->step];
	kor->step += kor->args[0];
	b = cw->map[kor->position + kor->step];
	kor->step += kor->args[1];
	c = cw->map[kor->position + kor->step];
	kor->step += kor->args[2];
	value = kor->regs[a - 1] + kor->regs[b - 1];
	kor->regs[c - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
}

void	op_sub(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int c;
	int value;

	kor->step += 2;
	a = cw->map[kor->position + kor->step];
	kor->step += kor->args[0];
	b = cw->map[kor->position + kor->step];
	kor->step += kor->args[1];
	c = cw->map[kor->position + kor->step];
	kor->step += kor->args[2];
	value = kor->regs[a - 1] - kor->regs[b - 1];
	kor->regs[c - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
}

void 	op_aff(t_cw *cw, t_koretko *kor)
{
	int a;

	kor->step += 2;
	a = cw->map[kor->position + kor->step];
	kor->step++;
	ft_printf("%c", kor->regs[a - 1]);
}

void	op_fork(t_cw *cw, t_koretko *kor)
{
	t_koretko	*n_koretrko;
	int			i;

	i = -1;
	pos = get_value();
	n_koretrko = create_koretko(cw->num_of_koretko + 1, pos % IDX_MOD);
	while (++i < REG_NUMBER)
		n_koretrko->regs[i] = kor->regs[i];
	n_koretrko->carry = kor->carry;
	n_koretrko->last_alive = kor->last_alive;
	chain_kor(&cw->kors, n_koretrko);
}

void 	op_and(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int reg;
	int value;

	a = get_value(cw, kor, kor->args[0]);
	b = get_value(cw, kor, kor->args[1]);
	reg = get_value(cw, kor, kor->args[2]);
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

//	a = get_value(cw, kor, get_arg_type(cw, kor->position));
//	b = get_value(cw, kor, get_arg_type(cw, kor->position));
//	reg = get_value(cw, kor, get_arg_type(cw, kor->position));
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

//	a = get_value(cw, kor, get_arg_type(cw, kor->position));
//	b = get_value(cw, kor, get_arg_type(cw, kor->position));
//	reg = get_value(cw, kor, get_arg_type(cw, kor->position));
	kor->step += 5;
	value = a ^ b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
}

void 	op_st(t_cw *cw, t_koretko *kor)
{
	int reg;
	int second_arg;

//	reg = get_value(cw, kor, get_arg_type(cw, kor->position));
//
}

//void	op_live(t_koretko *kor, int arg)
//{
//
//	if (arg == )
//}second_arg =
////	if (kor-)