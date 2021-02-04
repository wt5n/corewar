/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:47:50 by hlikely           #+#    #+#             */
/*   Updated: 2021/02/04 19:52:10 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/vm.h"

void	exec_op(t_cw *cw, t_koretko *koretko)
{
	koretko->op_code == 1 ? op_live(cw, koretko) : 0;
	koretko->op_code == 2 ? op_ld(cw, koretko) : 0;
	koretko->op_code == 3 ? op_st(cw, koretko) : 0;
	koretko->op_code == 4 ? op_add(cw, koretko) : 0;
	koretko->op_code == 5 ? op_sub(cw, koretko) : 0;
	koretko->op_code == 6 ? op_and(cw, koretko) : 0;
	koretko->op_code == 7 ? op_or(cw, koretko) : 0;
	koretko->op_code == 8 ? op_xor(cw, koretko) : 0;
	koretko->op_code == 9 ? op_zjmp(cw, koretko) : 0;
	koretko->op_code == 10 ? op_ldi(cw, koretko) : 0;
	koretko->op_code == 11 ? op_sti(cw, koretko) : 0;
	koretko->op_code == 12 ? op_fork(cw, koretko) : 0;
	koretko->op_code == 13 ? op_lld(cw, koretko) : 0;
	koretko->op_code == 14 ? op_lldi(cw, koretko) : 0;
	koretko->op_code == 15 ? op_lfork(cw, koretko) : 0;
	koretko->op_code == 16 ? op_aff(cw, koretko) : 0;
	koretko->position = get_adrs(koretko, 0, 0);
	koretko->step = 0;
	koretko->op_code = 0;
	koretko->args[0] = 0;
	koretko->args[1] = 0;
	koretko->args[2] = 0;
}

void	if_cor_op(t_koretko *koretko, t_cw *cw)
{
	int i;
	int j;

	i = -1;
	j = 6;
	if (op_tab[koretko->op_code - 1].code_args)
	{
		while (++i < op_tab[koretko->op_code - 1].num_of_args)
		{
			koretko->args[i] =
					(cw->map[koretko->position + 1] & (3 * ft_pow(2, j))) >> j;
			j -= 2;
		}
		if (!(is_correct_args(i, koretko->args, cw, koretko)))
		{
			wrong_args(koretko);
			return ;
		}
	}
	else
		koretko->args[0] = op_tab[koretko->op_code - 1].args[0];
	exec_op(cw, koretko);
}

void	read_byte(t_koretko *koretko, t_cw *cw)
{
	if (koretko->op_code >= 1 && koretko->op_code <= 16)
		if_cor_op(koretko, cw);
	else
		koretko->position = get_adrs(koretko, 1, 0);
}

void	make_op(t_cw *cw)
{
	t_koretko *cur;

	cw->cycles++;
	cw->cycles_to_check++;
	cur = cw->kors;
	while (cur)
	{
		if (cur->delay == 0)
		{
			cur->op_code = cw->map[cur->position];
			if (cur->op_code >= 1 && cur->op_code <= 16)
				cur->delay = op_tab[cur->op_code - 1].delay;
		}
		if (cur->delay > 0)
			cur->delay--;
		if (cur->delay == 0)
			read_byte(cur, cw);
		cur = cur->next;
	}
}

void	cycle(t_cw *cw)
{
	place_pl_and_kors(cw);
	while (cw->num_of_koretko)
	{
		if (cw->dump_cycle == cw->cycles)
		{
			ft_print_memory(cw->map, 4096);
			exit(1);
		}
		make_op(cw);
		if (cw->cycles_to_die == cw->cycles_to_check
			|| cw->cycles_to_die <= 0)
			check_cycles(cw);
	}
	cw->last_player *= -1;
	ft_printf("Contestant %d, \"%s\", has won !\n",
			cw->last_player, cw->champs[cw->last_player - 1]->name);
	free_after_finish(cw);
}
