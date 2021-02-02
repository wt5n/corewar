#include "inc/vm.h"

void	chain_kor(t_koretko **kors, t_koretko *kor)
{
	kor->next = *kors;
	*kors = kor;
}

t_koretko	*create_koretko(int id, int position)
{
	t_koretko *kor;

	if (!(kor = (t_koretko*)ft_memalloc(sizeof(t_koretko))))
		return NULL;
	kor->next = NULL;
	kor->id = id;
	kor->position = position;
//	ft_printf("create PUNK id = %d, position = %d\n", kor->id, kor->position);
	return kor;
}

void	delete_koretko(t_koretko **kors, t_koretko *prev, t_koretko *cur)
{
	if (prev == NULL)
		*kors = cur->next;
	else
		prev->next = (cur->next == NULL) ? NULL: cur->next;
	free(cur);
}