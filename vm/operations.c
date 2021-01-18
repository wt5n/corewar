#include "inc/vm.h"

void	op_lld(t_cw *cw, t_koretko *kor)
{
	int value;

	kor->step += 2;
	value = get_value(cw, kor, kor->args[0]);
	kor->regs[cw->map[get_adrs(kor, 0)]] = value;
	kor->step++;
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
	kor->step += 2;
	ft_printf("%c", is_reg(cw, kor));
}

void	op_fork(t_cw *cw, t_koretko *kor)
{
	t_koretko	*koretko;
	int			i;

	kor->step++;
	i = -1;
	kor->ind_adrs = get_value(cw, kor, kor->args[0]) % IDX_MOD;
	cw->num_of_koretko++;
	koretko = create_koretko(cw->num_of_koretko, get_adrs(kor, 0));
	while (i++ < REG_NUMBER)
		koretko->regs[i] = kor->regs[i];
	koretko->carry = kor->carry;
	koretko->last_alive = kor->last_alive;
	chain_kor(&cw->kors, koretko);
	kor->ind_adrs = 0;
}

void	op_lfork(t_cw *cw, t_koretko *kor)
{
	t_koretko	*koretko;
	int			i;

	kor->step++;
	i = -1;
	kor->ind_adrs = get_value(cw, kor, kor->args[0]);
	cw->num_of_koretko++;
	koretko = create_koretko(cw->num_of_koretko, get_adrs(kor, 0));
	while (i++ < REG_NUMBER)
		koretko->regs[i] = kor->regs[i];
	koretko->carry = kor->carry;
	koretko->last_alive = kor->last_alive;
	chain_kor(&cw->kors, koretko);
	kor->ind_adrs = 0;
}

void	op_zjmp(t_cw *cw, t_koretko *kor)
{
	int	adrs;

	kor->step++;
	if (kor->carry)
	{
		adrs = get_value(cw, kor, kor->args[0]) % IDX_MOD;
		kor->ind_adrs = adrs;
		kor->position = get_adrs(kor, 0);
		kor->ind_adrs = 0;
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
	int first_arg;
	int second_arg;

	kor->step += 2;
	first_arg = is_reg(cw, kor);
	if (kor->args[1] == T_REG)
	{
		second_arg = cw->map[get_adrs(kor, 0)];
		kor->regs[second_arg - 1] = first_arg;
	}
	else
	{
		second_arg = get_value(cw, kor, kor->args[1]) % IDX_MOD;
		kor->ind_adrs = second_arg;
		write_value(cw, get_adrs(kor, 0), first_arg, op_tab[kor->op_code - 1].tdir_size);
		kor->ind_adrs = 0;
	}
}

void 	op_sti(t_cw *cw, t_koretko *kor)
{
	int first_arg;
	int second_arg;
	int	third_arg;

	kor->step += 2;
	first_arg = is_reg(cw, kor);
	if (kor->args[1] == T_REG)
	{
		second_arg = cw->map[get_adrs(kor, 0)];
		kor->step++;
	}
	else
		second_arg = get_value(cw, kor, kor->args[1]);
	if (kor->args[2] == T_REG)
	{
		third_arg = cw->map[get_adrs(kor, 0)];
		kor->step++;
	}
	else
		third_arg = get_value(cw, kor, kor->args[2]);
	kor->ind_adrs = (second_arg + third_arg) % IDX_MOD;
	write_value(cw, get_adrs(kor, 0), first_arg, op_tab[kor->op_code - 1].tdir_size);
	kor->ind_adrs = 0;
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
	kor->step++;
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
	kor->ind_adrs = 0;
	kor->step++;
}

void	op_live(t_cw *cw, t_koretko *kor)
{
	int player;
	t_champ *champ;

	kor->step++;
	player = get_value(cw, kor, kor->args[0]);
	cw->num_of_lives++;
	kor->num_live_cycle = cw->cycles;
	if (player <= -1 && player >= -cw->num_of_champ)
	{
		champ = cw->champs[mod_n(player) - 1];
		champ->live_cycle = cw->cycles;
		champ->lives_num++;
		cw->last_player = player;
	}
}