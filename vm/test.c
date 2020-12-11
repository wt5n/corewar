#include "inc/vm.h"

void	op_add(t_koretko *kor, int *a, int *b, int *c)
{
	*c = *a + *b;
	kor->carry = *c == 0 ? 1 : 0;
}

int main()
{
	t_cw *cw;
	int	i = -1;
	cw = (t_cw*)ft_memalloc(sizeof(t_cw));
	cw->champs = (t_champ**)ft_memalloc(sizeof(t_champ*) * MAX_PLAYERS);
	cw->champs[0] = (t_champ*)ft_memalloc(sizeof(t_champ));
	cw->map = (unsigned char*)ft_memalloc(sizeof(char) * 4097);
	cw->kors = (t_koretko**)ft_memalloc(sizeof(t_koretko*) * MAX_PLAYERS);
	cw->rgtrs = (int*)ft_memalloc(sizeof(int) * REG_NUMBER);
	while (++i < 4096)
		cw->map[i] = 0;
	cw->map[4096] = '\0';

	cw->rgtrs[0] = 1;
	cw->rgtrs[1] = -1;
	cw->rgtrs[2] = 10;
	cw->kors[0] = (t_koretko*)ft_memalloc(sizeof(t_koretko));

	cw->kors[0]->carry = 5;
	op_add(cw->kors[0], &cw->rgtrs[0], &cw->rgtrs[1], &cw->rgtrs[2]);
	printf("%d carry %d", cw->rgtrs[2], cw->kors[0]->carry);
	return (0);
}
