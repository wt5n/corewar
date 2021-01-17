#include "inc/vm.h"

void	chain_kor(t_koretko **kors, t_koretko *kor)
{
	// t_koretko	*current;

	// current = kors;
	// while(current->next != NULL)
	// 	current = current->next;
	// curent->next = kor;
	kor->next = *kors;
	*kors = kor;
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

int		ft_pow(int a, int pow)
{
	int res;

	res = a;
	if (pow == 0)
		return (1);
	while (--pow)
	{
		res *= a;
	}
	return (res);
}

void	write_value(t_cw *cw, int adrs, int value, int size)
{
	int	i;

	i = 0;
	while (--size >= 0)
	{
		cw->map[(adrs + size) % 4096] = value >> i * 8 & 255;
		i++;
	}
}

int main(int ac, char **av)
{
//	char map[2];
	int	n = 300;
	int j = 2;
	int	x = 0;

//	for (int i = 0; i < 2; i++)
//		map[i] = 0;

	t_cw *cw;
	cw = (t_cw*)ft_memalloc(sizeof(t_cw));
	write_value(cw, 0, 64949, 4);

//	map[1] = n >> 0 * 8 & 255;
//	map[0] = n >> 1 * 8 & 255;

	// map[1] = n & 255 >> 1 * 8;
//	/**/printf("%#x", map[0]);
//	 printf("%x\n", map[1]);
	ft_print_memory(cw->map, 4096);


}
