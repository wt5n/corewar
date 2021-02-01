#include "inc/vm.h"

int 	correct_for_func(int ar, int func_sum)
{
	if (func_sum == 1 && ar == 1)
		return (1);
	else if (func_sum == 2 && ar == 2)
		return (1);
	else if (func_sum == 3 && (ar == 1 || ar == 2))
		return (1);
	else if (func_sum == 5 && (ar == 3 || ar == 1))
		return (1);
	else if (func_sum == 6 && (ar == 3 || ar == 2 ))
		return (1);
	else if (func_sum == 7 && (ar == 3 || ar == 2 || ar == 1))
		return (1);
	else if (func_sum == 0 && ar == 0)
		return (1);
	return (0);
}

int		is_correct_args(int i, int *ar, t_cw *cw, t_koretko *koretko)
{
	int step;
	int j;
	t_op *op;

	step = 2;
	j = -1;
	op = &op_tab[koretko->op_code - 1];
//	if (koretko->id == 18 && cw->cycles > 8017)
//		printf("4tob tebya\n");
	while (++j != i)
	{
//		printf("ar[j] = %d op_tab = %d, and = %d\n", ar[j], op->args[j], ar[j] & op->args[j]);
		if (!(correct_for_func(ar[j], op->args[j])))
			return (0);
		if (ar[j] == T_REG && (cw->map[get_adrs(koretko, step, 0)] < 1 ||
								   (cw->map[get_adrs(koretko, step, 0)] > 16)))
			return (0);
		if (koretko->args[j] == REG_CODE)
			step++;
		else if (koretko->args[j] == DIR_CODE)
			step += op_tab[koretko->op_code - 1].tdir_size;
		else
			step += 2;
	}
	return (1);
}

void	wrong_args(t_cw *cw, t_koretko *kor)
{
	int	i;

	i = -1;
	kor->step += 2;
	while (++i < op_tab[kor->op_code - 1].num_of_args)
	{
		if (kor->args[i] == REG_CODE)
			kor->step++;
		else if (kor->args[i] == DIR_CODE)
			kor->step += op_tab[kor->op_code - 1].tdir_size;
		else if (kor->args[i] == IND_CODE)
			kor->step += 2;
		kor->args[i] = 0;
	}
	kor->position = get_adrs(kor, 0, 0);
	kor->step = 0;
	kor->op_code = 0;
}

void	check_cycles(t_cw *cw)
{
	cw->num_of_checks++;
	t_koretko	*kor;
	t_koretko	*tmp;
	t_koretko	*prev;

	kor = cw->kors;
	prev = NULL;
	while (kor)
	{
		if (cw->cycles - kor->last_alive >= cw->cycles_to_die ||
			cw->cycles_to_die <= 0)
		{
//			ft_printf("DIE PUNK id = %d, cycle = %d!!! ctd = %d\n", kor->id, cw->cycles, cw->cycles_to_die);
			tmp = kor->next;
			delete_koretko(kor->id, &cw->kors, prev);
			cw->num_of_koretko--;
//			ft_printf("cw->num_of_koretko = %d\n", cw->num_of_koretko);
			kor = tmp;
		}
		else
		{
			prev = kor;
			kor = kor->next;
		}
	}
	if (cw->num_of_checks == MAX_CHECKS || cw->num_of_lives >= NBR_LIVE)
	{
		cw->cycles_to_die -= CYCLE_DELTA;
		cw->num_of_checks = 0;
	}
	cw->num_of_lives = 0;
	cw->cycles_to_check = 0;
}
