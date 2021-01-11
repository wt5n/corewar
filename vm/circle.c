#include "inc/vm.h"


t_koretko	*create_koretko(int id, int position)
{
	t_koretko *kor;

	if (!(kor = (t_koretko*)ft_memalloc(sizeof(t_koretko))))
		return NULL;
	kor->next = NULL;
	kor->id = id;
	kor->position = position;
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
		kor = create_koretko(cw->num_of_koretko + 1, position);
		kor->regs[0] = player_id;
		kor->parent_id = player_id;
		chain_kor(&cw->kors, kor);
		position += MEM_SIZE / cw->num_of_champ;
		cw->num_of_koretko++;
	}
}

int		is_correct_args(int i, int *ar, t_cw *cw, t_koretko *koretko)
{
	int x = 0;

	while (--i)
	{
		if (!(ar[i] & op_tab[koretko->op_code - 1].args[i]) ||
			(ar[i] == T_REG && (cw->map[koretko->position + 2 + x] < 1 ||
			(cw->map[koretko->position + 2 + x] > 16))))
		{

			return (0);
		}

		printf("%d\n", cw->map[koretko->position + 2 + x]);
		x += ar[i];

	}
	return (1);
}

void	exec_op(t_cw *cw, t_koretko *koretko)
{


//	koretko->step += n;
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
		koretko->delay = op_tab[koretko->op_code - 1].delay;
		while (++i < op_tab[koretko->op_code - 1].num_of_args)
		{
			koretko->args[i] = (cw->map[koretko->position + 1] & (3 * ft_pow(2, j))) >> j;
			j -= 2;
		}
		if (koretko->args[2] & T_DIR)
			printf("true");
		if (is_correct_args(i, koretko->args, cw, koretko))
			exec_op(cw, koretko);
		else

			printf("koretko->step += n;");
		printf("1 - %d 2 - %d 3 - %d\n", koretko->args[0], koretko->args[1], koretko->args[2]);

		for (int v = 0; v < 22; v++ )
			printf("%#x ", cw->map[v]);
		printf("\n");
		exit(1);
	}
	else
		koretko->step += 1;
}



void	make_op(t_cw *cw)
{
	t_koretko *cur;

	cw->cycles++;
	cur = cw->kors;
	while (cur)
	{
		if (cur->delay == 0)
			read_byte(cur, cw);
		else if (cur->delay > 0)
			cur->delay--;
		cur = cur->next;
	}
}

void	delete_koretko(int id, t_koretko **kors)
{
	t_koretko *current;
	t_koretko *prev;

	current = *kors;
	if (current->id == id)
		*kors = current->next;
	else
	{
		while (id != current->id)
		{
			prev = current;
			current = current->next;
		}
		prev->next = current->next;
	}
	free(current);
}

void	check_cycles(t_cw *cw)
{
	cw->num_of_checks++;
	t_koretko *kor;

	kor = cw->kors;
	while (kor)
	{
		if (cw->cycles - kor->last_alive  >= cw->cycles_to_die ||
			cw->cycles_to_die <= 0)
		{
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

void circle(t_cw *cw)
{
	int i;

	i = -1;
	cw->last_player = cw->champs[0]->number;
	cw->cycles_to_die = CYCLE_TO_DIE;
	place_pl_and_kors(cw);
	ft_printf("Introducing contestants...\n");
	while (++i < cw->num_of_champ)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		cw->champs[i]->number, cw->champs[i]->code_size,
		cw->champs[i]->name, cw->champs[i]->comm);
//	printf("%#x\n\n", cw->map[2048 + 4]);
//	ft_print_memory(cw->map, 4096);
	while (cw->num_of_koretko)
	{
		make_op(cw);
		if (cw->cycles_to_die == cw->cycles_to_check
			|| cw->cycles_to_die <= 0)
			check_cycles(cw);
	}
}