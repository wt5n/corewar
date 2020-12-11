#include "inc/vm.h"

void circle(t_cw *cw)
{
	int i;

	i = -1;
	cw->last_alive = cw->champs[0]->number;
	cw->cycles_to_die = CYCLE_TO_DIE;
	while (++i < cw->num_of_champ)
	{
		cw->kors[i] = (t_koretko*)ft_memalloc(sizeof(t_koretko));
		cw->kors[i]->id = i;
	}
}