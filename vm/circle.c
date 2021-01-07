#include "inc/vm.h"


void	place_pl_and_kors(t_cw *cw)
{
	int position;
	int player_id;

	position = 0;
	player_id = 0;

	while (++player_id <= cw->num_of_champ)
	{
		ft_memcpy(&(cw->map[position]), vm->champs[id]->code, 
		(size_t)vm->player_id[id]->code_size);
		add_koretko(&vm->kors, create_koretko(cw->champs[player_id - 1], position));
		position += MEM_SIZE / cw->num_of_champ;
	}
}

void	make_op(t_cw *cw)
{
	t_koretko *cur;

	cw->cycles++;
	cur = cw->kors;
	while (cur)
	{

	}
}

void circle(t_cw *cw)
{
	// int i;

	// i = -1;
	// cw->last_alive = cw->champs[0]->number;
	// cw->cycles_to_die = CYCLE_TO_DIE;
	// while (++i < cw->num_of_champ)
	// {
	// 	ft_memcpy(&(vm->map))
	// 	cw->kors[i] = (t_koretko*)ft_memalloc(sizeof(t_koretko));
	// 	cw->kors[i]->id = i;
	// }

	while (cw->num_of_koretko)
	{
		make_op(cw);
		if (cw->cycles_to_die == cw->cycles)
		{
			check_cycles(cw);
		}
	}
}