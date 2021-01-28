#include "inc/vm.h"

void	exec_op(t_cw *cw, t_koretko *koretko)
{
//	 if (cw->cycles >= 1021)
//		 ft_printf("hello\n");
	koretko->op_code == 1 ? op_live(cw, koretko) : 0;
	koretko->op_code == 2 ? op_ld(cw, koretko) : 0;
	koretko->op_code == 3 ? op_st(cw, koretko) : 0;
	koretko->op_code == 4 ? op_add(cw, koretko) : 0;
	koretko->op_code == 5 ? op_sub(cw, koretko) : 0;
	koretko->op_code == 6 ? op_and(cw, koretko) : 0;
//	if (cw->cycles == 8019 && koretko->id != 18)
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

void	read_byte(t_koretko *koretko, t_cw *cw)
{
	int i;
	int j;

	i = -1;
	j = 6;
	// if (cw->cycles == 25)
	// 	ft_printf("hello\n");
	if (koretko->op_code >= 1 && koretko->op_code <= 16)
	{
		if (op_tab[koretko->op_code - 1].code_args)
		{
			while (++i < op_tab[koretko->op_code - 1].num_of_args)
			{
				koretko->args[i] = (cw->map[koretko->position + 1] & (3 * ft_pow(2, j))) >> j;
				j -= 2;
			}
		}
		else
		{
			koretko->args[0] = op_tab[koretko->op_code - 1].args[0];
			i = 1;
		}
		if (is_correct_args(i, koretko->args, cw, koretko))
			exec_op(cw, koretko);
		else
			wrong_args(cw, koretko);
	}
	else
		koretko->position = get_adrs(koretko, 1, 0);
}

void	make_op(t_cw *cw)
{
	t_koretko *cur;

	cw->cycles++;
	cw->cycles_to_check++;
	cur = cw->kors;
//	printf("cycle = %d, cyc = %d, cyd = %d\n", cw->cycles, cw->cycles_to_check, cw->cycles_to_die);
	while (cur)
	{
//		if (cur->id == 18 && cw->cycles > 8017)
//			printf("4tob tebya");
//		ft_printf("op_code - %d, id - %d\n", cur->op_code, cur->id);
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
//		if (cw->cycles == 8018)
//			ft_printf("here\n");
		make_op(cw);
		if (cw->cycles_to_die == cw->cycles_to_check
			|| cw->cycles_to_die <= 0)
		{
//			ft_printf("ctd = %d, ctc = %d, nol = %d, cyc = %d\n", cw->cycles_to_die,
//		  	cw->cycles_to_check, cw->num_of_lives, cw->cycles);
			check_cycles(cw);
		}
//		if (cw->cycles_to_check % 100 == 0)
//			ft_printf("ctd = %d, ctc = %d, nol = %d , cyc = %d\n", cw->cycles_to_die,
//		  cw->cycles_to_check, cw->num_of_lives, cw->cycles);
		if (cw->cycles == 6065)
		{
			ft_print_memory(cw->map, 4096);
			t_koretko  *cur;
			cur = cw->kors;
//			while (cur)
//			{
//				ft_printf("koretko #%d on position %d in map %#x "
//			  "koretko->live %d op_code %d\n", cur->id, cur->position,
//			  cw->map[cur->position], cur->last_alive, cur->op_code);
//				cur = cur->next;
//			}
			ft_printf("cycle is %d\nnum of kors = %d\n"
			 "cycle_to_die = %d\nnum_of_lives = %d\n",
			 cw->cycles, cw->num_of_koretko, cw->cycles_to_die, cw->num_of_lives);

			exit(1);
		}
	}
	cw->last_player *= -1;
	printf("Contestant %d, \"%s\", has won ! cycle = %d\n", cw->last_player, cw->champs[cw->last_player - 1]->name, cw->cycles);
	ft_print_memory(cw->map, 4096);
}