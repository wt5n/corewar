#include "inc/vm.h"

int		is_correct_args(int i, int *ar, t_cw *cw, t_koretko *koretko)
{
	int step;
	int j;

	step = 2;
	j = -1;
	while (++j != i)
	{
		if (!(ar[j] & op_tab[koretko->op_code - 1].args[j]) ||
			(ar[j] == T_REG && (cw->map[get_adrs(koretko, step, 0)] < 1 ||
								(cw->map[get_adrs(koretko, step, 0)] > 16))))
			return (0);
		if (koretko->args[j] == T_REG)
			step++;
		else if (koretko->args[j] == T_DIR)
			step += op_tab[koretko->op_code - 1].tdir_size;
		else
			step += 2;
	}
	return (1);
}

void wrong_args(t_koretko *kor)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (kor->args[i] == T_REG)
			kor->step++;
		else if (kor->args[i] == T_DIR)
			kor->step += op_tab[kor->op_code - 1].tdir_size;
		else
			kor->step += 2;
	}
	kor->position = get_adrs(kor, 0, 0);
	kor->step = 0;
	kor->op_code = 0;
}

void	check_cycles(t_cw *cw)
{
	cw->num_of_checks++;
	t_koretko *kor;

	kor = cw->kors;
	while (kor)
	{
		if (cw->cycles - kor->last_alive >= cw->cycles_to_die ||
			cw->cycles_to_die <= 0)
		{
			ft_printf("DIE PUNK id = %d, cycle = %d!!! ctd = %d\n", kor->id, cw->cycles, cw->cycles_to_die);

			delete_koretko(kor->id, &cw->kors);
			cw->num_of_koretko--;
		}
		kor = kor->next;
	}
	if (cw->num_of_checks == MAX_CHECKS || cw->num_of_lives >= NBR_LIVE)
	{
		cw->cycles_to_die -= CYCLE_DELTA;
		cw->num_of_checks = 0;
	}
	cw->num_of_lives = 0; // изменить у игроков ???
	cw->cycles_to_check = 0;
}
