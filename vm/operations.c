#include "inc/vm.h"

int		get_adrs(t_koretko *koretko, int modif)
{
	int	adrs;

	adrs = (koretko->position + koretko->step + modif) % MEM_SIZE;
	if (adrs < 0)
		adrs += MEM_SIZE;
	return (adrs);
}

int		if_reg(t_cw *cw, t_koretko *koretko)
{
	int reg;

	reg = cw->map[get_adrs(koretko, 0)];
	koretko->step++;
	return (koretko->regs[reg - 1]);
}

int		if_dir(t_cw *cw, t_koretko *koretko, int n)
{
	int value;
	int sign;
	int i;
	//00 07
	i = 0;
	value = 0;
	sign = cw->map[get_adrs(koretko, 0)] & 128;
	koretko->step += n;
	while (n)
	{
		if (sign)
			value += (cw->map[get_adrs(koretko, n)] ^ 255) << (i++ * 8);
		else
			value += (cw->map[get_adrs(koretko, n)]) << (i++ * 8);
		n--;
	}
	if (sign)
		value = ~value;
	return value;
}

int 	if_indir(t_cw *cw, t_koretko *koretko, int n)
{
	int adrs;
	int value;

	adrs = if_dir(cw, koretko, T_IND);
	return value;
}

int get_value(t_cw *cw, t_koretko *koretko, int arg)
{
	if (arg == T_REG)
		return (if_reg(cw, koretko));
	else if (arg == T_DIR)
		return (if_dir(cw, koretko, op_tab[koretko->op_code - 1].tdir_size));
	else if (arg == T_IND)
		return (if_indir(cw, koretko, arg));
	else
		return 0;
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
//	pos = get_value();
//	n_koretrko = create_koretko(cw->num_of_koretko + 1, pos % IDX_MOD);
	while (++i < REG_NUMBER)
		n_koretrko->regs[i] = kor->regs[i];
	n_koretrko->carry = kor->carry;
	n_koretrko->last_alive = kor->last_alive;
//	chain_kor(&cw->kors, n_koretrko);
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