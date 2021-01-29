#include "inc/vm.h"

void	op_lld(t_cw *cw, t_koretko *kor)
{
	int value;
	int reg;

	kor->step += 2;
	value = get_value(cw, kor, kor->args[0], 0);
	kor->carry = value == 0 ? 1 : 0;
	reg = cw->map[get_adrs(kor, 0, 0)];
	kor->regs[reg - 1] = value;
	kor->step++;
}

void	op_add(t_cw *cw, t_koretko *kor)
{
	int a;
	int value;

	kor->step += 2;
	value = is_reg(cw, kor) + is_reg(cw, kor);
	a = cw->map[get_adrs(kor, 0, 0)];
	kor->regs[a - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
	kor->step++;
}

void	op_sub(t_cw *cw, t_koretko *kor)
{
	int a;
	int value;

	kor->step += 2;
	value = is_reg(cw, kor) - is_reg(cw, kor);
	a = cw->map[get_adrs(kor, 0, 0)];
	kor->regs[a - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
	kor->step++;
}

void 	op_aff(t_cw *cw, t_koretko *kor)
{
	kor->step += 2;
	ft_printf("%c", is_reg(cw, kor));
}

void	op_fork(t_cw *cw, t_koretko *old_kor)
{
	t_koretko	*new_kor;
	int			i;

	old_kor->step++;
	i = -1;
	old_kor->ind_adrs = is_dir(cw, old_kor, op_tab[old_kor->op_code - 1].tdir_size, 0) % IDX_MOD;
	cw->num_of_koretko++;
	cw->last_id++;
//	ft_printf("fork on %d cycle new_kor->id = %d ", cw->cycles, cw->last_id);
//	ft_printf("kor # %d \n", old_kor->id);
	new_kor = create_koretko(cw->last_id, get_adrs(old_kor, 0, 1));
	while (++i < REG_NUMBER)
		new_kor->regs[i] = old_kor->regs[i];
	new_kor->carry = old_kor->carry;
	new_kor->last_alive = old_kor->last_alive;
	new_kor->parent_id = old_kor->parent_id;
	chain_kor(&cw->kors, new_kor);
	old_kor->ind_adrs = 0;
}

void	op_lfork(t_cw *cw, t_koretko *old_kor)
{
	t_koretko	*new_kor;
	int			i;

	old_kor->step++;
	i = -1;
	old_kor->ind_adrs = get_value(cw, old_kor, old_kor->args[0], 0);
	cw->num_of_koretko++;
	cw->last_id++;
//	ft_printf("lfork on %d cycle ", cw->cycles);
//	ft_printf("kor # %d \n", old_kor->id);
	new_kor = create_koretko(cw->last_id, get_adrs(old_kor, 0, 1));
	while (++i < REG_NUMBER)
		new_kor->regs[i] = old_kor->regs[i];
	new_kor->carry = old_kor->carry;
	new_kor->last_alive = old_kor->last_alive;
	new_kor->parent_id = old_kor->parent_id;
	chain_kor(&cw->kors, new_kor);
	old_kor->ind_adrs = 0;
}

void	op_zjmp(t_cw *cw, t_koretko *kor)
{
	int	adrs;

	kor->step++;
	adrs = get_value(cw, kor, kor->args[0], 0) % IDX_MOD;
	if (kor->carry)
	{
		kor->ind_adrs = adrs;
		kor->position = get_adrs(kor, 0, 1);
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
	a = get_value(cw, kor, kor->args[0], 0);
	b = get_value(cw, kor, kor->args[1], 0);
	reg = cw->map[get_adrs(kor, 0, 0)];
	value = a & b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
	kor->step++;
}

void 	op_or(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int reg;
	int value;

	kor->step += 2;
	a = get_value(cw, kor, kor->args[0], 0);
	b = get_value(cw, kor, kor->args[1], 0);
	reg = cw->map[get_adrs(kor, 0, 0)];
	value = a | b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
	kor->step++;
}

void 	op_xor(t_cw *cw, t_koretko *kor)
{
	int a;
	int b;
	int reg;
	int value;

	kor->step += 2;
	a = get_value(cw, kor, kor->args[0], 0);
	b = get_value(cw, kor, kor->args[1], 0);
	reg = cw->map[get_adrs(kor, 0, 0)];
	value = a ^ b;
	kor->regs[reg - 1] = value;
	kor->carry = value == 0 ? 1 : 0;
	kor->step++;
}

void 	op_st(t_cw *cw, t_koretko *kor)
{
	int first_arg;
	int second_arg;

	kor->step += 2;
	first_arg = is_reg(cw, kor);
	if (kor->args[1] == T_REG)
	{
		second_arg = cw->map[get_adrs(kor, 0, 0)];
		kor->regs[second_arg - 1] = first_arg;
		kor->step++;
	}
	else
	{
		second_arg = is_dir(cw, kor, IND_SIZE, 0) % IDX_MOD;
		kor->ind_adrs = second_arg;
		write_value(cw, get_adrs(kor, 0, 1), first_arg, DIR_SIZE);
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
	second_arg = get_value(cw, kor, kor->args[1], 0);
	third_arg = get_value(cw, kor, kor->args[2], 0);
	kor->ind_adrs = (second_arg + third_arg) % IDX_MOD;
	write_value(cw, get_adrs(kor, 0, 1), first_arg, DIR_SIZE);
	kor->ind_adrs = 0;
}

void	op_ld(t_cw *cw, t_koretko *kor)
{
	int value;
	int reg;

	kor->step += 2;
	value = get_value(cw, kor, kor->args[0], 0);
	kor->carry = value == 0 ? 1 : 0;
	reg = cw->map[get_adrs(kor, 0, 0)];
	kor->regs[reg - 1] = value;
	kor->step++;
}

void	op_ldi(t_cw *cw, t_koretko *kor)
{
	int first_arg;
	int second_arg;
	int reg;

	kor->step += 2;
	first_arg = get_value(cw, kor, kor->args[0], 0);
	second_arg = get_value(cw, kor, kor->args[1], 0);
	reg = cw->map[get_adrs(kor, 0, 0)];
	kor->ind_adrs = (first_arg + second_arg) % IDX_MOD;
	kor->regs[reg - 1] = is_dir(cw, kor, DIR_SIZE, 1);
	kor->ind_adrs = 0;
	kor->step++;
}

void	op_lldi(t_cw *cw, t_koretko *kor)
{
	int first_arg;
	int second_arg;
	int reg;

	kor->step += 2;
	first_arg = get_value(cw, kor, kor->args[0], 0);
	second_arg = get_value(cw, kor, kor->args[1], 0);
	reg = cw->map[get_adrs(kor, 0, 0)];
	kor->ind_adrs = first_arg + second_arg;
	kor->carry = kor->ind_adrs == 0 ? 1 : 0;
	kor->regs[reg - 1] = is_dir(cw, kor, DIR_SIZE, 1);
	kor->ind_adrs = 0;
	kor->step++;
}

void	op_live(t_cw *cw, t_koretko *kor)
{
	int player;

	kor->step++;
	player = get_value(cw, kor, kor->args[0], 0);
	cw->num_of_lives++;
	kor->last_alive = cw->cycles;
	if (player <= -1 && player >= cw->num_of_champ * -1)
	{

//		ft_printf("LIVE player = %d, kor->id %d cycle %d\n", player, kor->id, cw->cycles);
		cw->last_player = player;
	}
}