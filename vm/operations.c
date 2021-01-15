#include "inc/vm.h"

int		get_adrs(t_koretko *koretko, int modif)
{
	int	adrs;

	if (koretko->ind_adrs > 0)
		adrs = koretko->position + koretko->ind_adrs + modif;
	else
		adrs = koretko->position + koretko->step + modif;
	adrs %= MEM_SIZE;
	if (adrs < 0)
		adrs += MEM_SIZE;
	return (adrs);
}

int		is_reg(t_cw *cw, t_koretko *koretko)
{
	int reg;

	reg = cw->map[get_adrs(koretko, 0)];
	koretko->step++;
	return (koretko->regs[reg - 1]);
}

int		is_dir(t_cw *cw, t_koretko *koretko, int n)
{
	int value;
	int sign;
	int i;

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

int 	is_indir(t_cw *cw, t_koretko *koretko, int n)
{
	int adrs;
	int value;

	adrs = is_dir(cw, koretko, T_IND);
	if (koretko->op_code != 13)
		adrs %= IDX_MOD;
	koretko->ind_adrs = adrs;
	value = is_dir(cw, koretko, n);
	koretko->ind_adrs = 0;
	return value;
}

int get_value(t_cw *cw, t_koretko *koretko, int arg)
{
	if (arg == T_REG)
		return (is_reg(cw, koretko));
	else if (arg == T_DIR)
		return (is_dir(cw, koretko, op_tab[koretko->op_code - 1].tdir_size));
	else if (arg == T_IND)
		return (is_indir(cw, koretko, arg));
	else
		return 0;
}

void	op_lld(t_cw *cw, t_koretko *kor)
{
	int value;

	kor->step += 2;
	value = get_value(cw, kor, op_tab[kor->op_code - 1].tdir_size);
	kor->regs[is_reg(cw, kor) - 1] = value;
}

void	op_add(t_cw *cw, t_koretko *kor)
{
	int a;
	int value;

	kor->step += 2;
	value = is_reg(cw, kor) + is_reg(cw, kor);
	a = cw->map[get_adrs(kor, 0)];
	kor->regs[a - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
}

void	op_sub(t_cw *cw, t_koretko *kor)
{
	int a;
	int value;

	kor->step += 2;
	value = is_reg(cw, kor) - is_reg(cw, kor);
	a = cw->map[get_adrs(kor, 0)];
	kor->regs[a - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
}

void 	op_aff(t_cw *cw, t_koretko *kor)
{
	int a;

	kor->step += 2;
	a = cw->map[get_adrs(kor, 0)];
	kor->step++;
	ft_printf("%c", kor->regs[a - 1]);
}

void	op_fork(t_cw *cw, t_koretko *kor)
{
	t_koretko	*koretko;
	int 	adrs;
	int			i;

	kor->step += 2;
	i = -1;
	adrs = get_value(cw, kor, kor->args[0]);
	koretko = create_koretko(cw->num_of_koretko++, kor->position + (adrs % IDX_MOD));
	while (i++ < REG_NUMBER)
		koretko->regs[i] = kor->regs[i];
	koretko->carry = kor->carry;
	koretko->last_alive = kor->last_alive;
	chain_kor(&cw->kors, koretko);
}

void	op_lfork(t_cw *cw, t_koretko *kor)
{
	t_koretko	*koretko;
	int 	adrs;
	int			i;

	kor->step += 2;
	i = -1;
	adrs = get_value(cw, kor, kor->args[0]);
	koretko = create_koretko(cw->num_of_koretko++, kor->position + adrs);
	while (i++ < REG_NUMBER)
		koretko->regs[i] = kor->regs[i];
	koretko->carry = kor->carry;
	koretko->last_alive = kor->last_alive;
	chain_kor(&cw->kors, koretko);
}

void	op_zjmp(t_cw *cw, t_koretko *kor)
{
	int	adrs;

	kor->step++;
	adrs = get_value(cw, kor, kor->args[0]);
	if (kor->carry)
	{
		adrs %= IDX_MOD;
		kor->ind_adrs = adrs;
		kor->position = get_adrs(kor, 0);
		kor->step = 0;
	}
}

void 	op_and(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int reg;
	int value;

	kor->step += 2;
	a = get_value(cw, kor, kor->args[0]);
	b = get_value(cw, kor, kor->args[1]);
	reg = get_adrs(kor, 0);
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

	kor->step += 2;
	a = get_value(cw, kor, kor->args[0]);
	b = get_value(cw, kor, kor->args[1]);
	reg = get_adrs(kor, 0);
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

	kor->step += 2;
	a = get_value(cw, kor, kor->args[0]);
	b = get_value(cw, kor, kor->args[1]);
	reg = get_adrs(kor, 0);
	value = a ^ b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
}

void 	op_st(t_cw *cw, t_koretko *kor)
{
	int reg;
	int second_arg;

	kor->step += 2;
	reg = is_reg(cw, kor);
	if (kor->args[1] == T_REG)
	{
		second_arg = get_adrs(kor, 0);
		kor->regs[second_arg - 1] = reg;
	}
	else
	{
		second_arg = is_indir(cw, kor, T_IND);
		second_arg %= IDX_MOD;
	}
//	reg = get_value(cw, kor, get_arg_type(cw, kor->position));
//
}

void	op_ld(t_cw *cw, t_koretko *kor)
{
	int value;
	int reg;

	kor->step += 2;
	value = get_value(cw, kor, kor->args[0]);
	kor->carry = value == 0 ? 1 : 0;
	reg = get_adrs(kor, 0);
	kor->regs[reg - 1] = value;
	kor->step++;
}

void	op_ldi(t_cw *cw, t_koretko *kor)
{
	int first_arg;
	int second_arg;
	int reg;

	kor->step += 2;
	first_arg = get_value(cw, kor, kor->args[0]);
	second_arg = get_value(cw, kor, kor->args[1]);
	reg = get_adrs(kor, 0);
	kor->ind_adrs = (first_arg + second_arg) % IDX_MOD;
	kor->regs[reg - 1] = get_value(cw, kor, T_DIR);
}

void	op_lldi(t_cw *cw, t_koretko *kor)
{
	int first_arg;
	int second_arg;
	int reg;

	first_arg = get_value(cw, kor, kor->args[0]);
	second_arg = get_value(cw, kor, kor->args[1]);
	reg = get_adrs(kor, 0);
	kor->ind_adrs = first_arg + second_arg;
	kor->regs[reg - 1] = get_value(cw, kor, T_DIR);
}

void	op_live(t_cw *cw, t_koretko *kor)
{
	int player;
	t_champ *champ;

	player = get_value(cw, kor, kor->args[0]);
	cw->num_of_lives++;
	kor->num_live_circle = cw->cycles;
	if (player <= -1 && player >= -cw->num_of_champ)
	{
		champ = cw->champs[mod_n(player) - 1];
		champ->live_cycle = cw->cycles;
		champ->lives_num++;
		cw->last_player = player;
	}
}