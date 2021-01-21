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
	koretko->position = get_adrs(koretko, 0);
	koretko->step = 0;
	koretko->op_code = 0;
	koretko->args[0] = 0;
	koretko->args[1] = 0;
	koretko->args[2] = 0;
}

void	read_byte(t_koretko *koretko, t_cw *cw)
{
	int i;
	int j;

	i = -1;
	j = 6;
	koretko->op_code = cw->map[koretko->position];
	if (koretko->op_code >= 0x01 && koretko->op_code <= 0x10)
	{
		while (++i < op_tab[koretko->op_code - 1].num_of_args)
		{
			koretko->args[i] = (cw->map[koretko->position + 1] & (3 * ft_pow(2, j))) >> j;
			j -= 2;
		}
		if (is_correct_args(i, koretko->args, cw, koretko))
			koretko->delay = op_tab[koretko->op_code - 1].delay - 1;
		else
			wrong_args(koretko);
	}
	else
	{
		koretko->op_code = 0;
		koretko->position = get_adrs(koretko, 1);
	}
}

void	make_op(t_cw *cw)
{
	t_koretko *cur;

	cw->cycles++;
	cw->cycles_to_check++;
	cur = cw->kors;
	while (cur)
	{
		if (cur->delay > 0)
			cur->delay--;
		if (cur->delay == 0)
		{
			if (cur->op_code > 0)
				exec_op(cw, cur);
			read_byte(cur, cw);
		}
//		else
		cur = cur->next;
	}
}

void	cycle(t_cw *cw)
{
	place_pl_and_kors(cw);
	while (cw->num_of_koretko)
	{
		make_op(cw);
		if (cw->cycles_to_die == cw->cycles_to_check
			|| cw->cycles_to_die <= 0)
		{
			printf("ctd = %d, ctc = %d, nol = %d, cyc = %d\n", cw->cycles_to_die,
		  	cw->cycles_to_check, cw->num_of_lives, cw->cycles);
			check_cycles(cw);
		}
		if (cw->cycles_to_check % 100 == 0)
			printf("ctd = %d, ctc = %d, nol = %d , cyc = %d\n", cw->cycles_to_die,
		  cw->cycles_to_check, cw->num_of_lives, cw->cycles);
		if (cw->cycles == 5)
		{
			ft_print_memory(cw->map, 4096);
			exit(1);
		}
	}
	ft_printf("Graz! %d is winner!", cw->last_player);
}