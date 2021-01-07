#include "inc/vm.h"


t_koretko	*create_koretko(int id)
{
	t_koretko *kor;

	if (!(kor = (t_koretko*)ft_memalloc(sizeof(t_koretko))))
		return NULL;
	if (!(kor->regs = (t_reg*)ft_memalloc(sizeof(t_reg))))
		return NULL;
	kor->next = NULL;
	kor->id = id;
	return kor;
}

void	chain_kor(t_koretko **kors, t_koretko *kor)
{
	kor->next = *kors;
	*kors = kor;
}

void	place_pl_and_kors(t_cw *cw)
{
	int position;
	int player_id;
	t_koretko	*kor;

	position = 0;
	player_id = 0;
	while (++player_id <= cw->num_of_champ)
	{
		ft_memcpy(&(cw->map[position]), cw->champs[player_id - 1]->code,
			(size_t)cw->champs[player_id - 1]->code_size);
		kor = create_koretko(cw->num_of_koretko + 1);
		kor->position = position;
		kor->regs->r1 = player_id;
		kor->parent_id = player_id;
		chain_kor(&cw->kors, kor);
		position += MEM_SIZE / cw->num_of_champ;
		cw->num_of_koretko++;
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
	int i;

	i = -1;
	cw->last_alive = cw->champs[0]->number;
	cw->cycles_to_die = CYCLE_TO_DIE;
	place_pl_and_kors(cw);
	ft_printf("Introducing contestants...\n");
	while (++i < cw->num_of_champ)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		cw->champs[i]->number, cw->champs[i]->code_size,
		cw->champs[i]->name, cw->champs[i]->comm);
	while (cw->num_of_koretko)
	{
		make_op(cw);
		if (cw->cycles_to_die == cw->cycles)
		{
//			check_cycles(cw);
		}
	}
}