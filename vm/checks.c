/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksenaida <ksenaida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:54:59 by hlikely           #+#    #+#             */
/*   Updated: 2021/02/07 15:56:37 by ksenaida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/vm.h"

int		correct_for_func(int ar, int func_sum)
{
	if (func_sum == 1 && ar == 1)
		return (1);
	else if (func_sum == 2 && ar == 2)
		return (1);
	else if (func_sum == 3 && (ar == 1 || ar == 2))
		return (1);
	else if (func_sum == 5 && (ar == 3 || ar == 1))
		return (1);
	else if (func_sum == 6 && (ar == 3 || ar == 2))
		return (1);
	else if (func_sum == 7 && (ar == 3 || ar == 2 || ar == 1))
		return (1);
	else if (func_sum == 0 && ar == 0)
		return (1);
	return (0);
}

int		is_correct_args(int i, int *ar, t_cw *cw, t_koretko *koretko)
{
	int		step;
	int		j;
	t_op	*op;

	step = 2;
	j = -1;
	op = &g_op_tab[koretko->op_code - 1];
	while (++j != i)
	{
		if (!(correct_for_func(ar[j], op->args[j])))
			return (0);
		if (ar[j] == T_REG && (cw->map[get_adrs(koretko, step, 0)] < 1 ||
		(cw->map[get_adrs(koretko, step, 0)] > REG_NUMBER)))
			return (0);
		if (koretko->args[j] == REG_CODE)
			step++;
		else if (koretko->args[j] == DIR_CODE)
			step += g_op_tab[koretko->op_code - 1].tdir_size;
		else
			step += 2;
	}
	return (1);
}

void	wrong_args(t_koretko *kor)
{
	int	i;

	i = -1;
	kor->step += 2;
	while (++i < g_op_tab[kor->op_code - 1].num_of_args)
	{
		if (kor->args[i] == REG_CODE)
			kor->step++;
		else if (kor->args[i] == DIR_CODE)
			kor->step += g_op_tab[kor->op_code - 1].tdir_size;
		else if (kor->args[i] == IND_CODE)
			kor->step += 2;
		kor->args[i] = 0;
	}
	kor->position = get_adrs(kor, 0, 0);
	kor->step = 0;
	kor->op_code = 0;
}

void	cycle_to_die_check(t_cw *cw)
{
	if (cw->num_of_checks == MAX_CHECKS || cw->num_of_lives >= NBR_LIVE)
	{
		cw->cycles_to_die -= CYCLE_DELTA;
		cw->num_of_checks = 0;
	}
	cw->num_of_lives = 0;
	cw->cycles_to_check = 0;
}

void	check_cycles(t_cw *cw)
{
	t_koretko	*kor;
	t_koretko	*tmp;
	t_koretko	*prev;

	kor = cw->kors;
	prev = NULL;
	cw->num_of_checks++;
	while (kor)
	{
		if (cw->cycles - kor->last_alive >= cw->cycles_to_die ||
			cw->cycles_to_die <= 0)
		{
			tmp = kor->next;
			if (prev == NULL)
				cw->kors = kor->next;
			else
				prev->next = (kor->next == NULL) ? NULL : kor->next;
			free(kor);
			cw->num_of_koretko--;
			kor = tmp;
		}
		else
		{
			prev = kor;
			kor = kor->next;
		}
	}
}
