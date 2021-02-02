#include "inc/vm.h"

void	chain_kor(t_koretko **kors, t_koretko *kor)
{
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
	int sign;

	i = 0;
	sign = value & 125;
	while (--size >= 0)
	{
		if (sign)
			cw->map[(adrs + size) % 4096] = 1;
		else
			cw->map[(adrs + size) % 4096] = (value >> i * 8) & 255;
		i++;
	}
}


int read_value(t_cw *cw, int adrs, int size)
{
	int value;

	value = 0;
	int i = 0;
	while (size)
	{
		value += cw->map[adrs + size - 1] << i * 8;
		size--;
		i++;
	}
	return value;
}

int has_cor(char *str)
{
	int a;

	a = ft_strlen(str);
	if (a > 4)
	{
		if (ft_strcmp(ft_strsub(str, a - 4, 4), ".cor") == 0)
		{
			printf("ok\n");
			return 1;
		}
	}
	else
	{
		printf("bad\n");
		return 0;
	}
}

int main(int ac, char **av)
{
//	char map[2];
	int	n = 300;

	int j[3] = {3, 3, 1};
	int x[3] = {T_REG | T_DIR | T_IND, T_IND | T_DIR, T_IND};
	// 0 1 2 3 12 13 123 23
	printf("1 - %d\n", 1 | 2);
	printf("2 - %d\n", 1 | 4);
	printf("3 - %d\n", 1 | 2 | 4);
	printf("3 - %d\n", 2 | 4);
//	printf("%d\n", );
//	for (int i = 0; i < 2; i++)
//		map[i] = 0;

//	has_cor("a");
//	has_cor("a.cor");
//	has_cor(".cor");
//	t_cw *cw;
//	cw = (t_cw*)ft_memalloc(sizeof(t_cw));
//	write_value(cw, 3, 0x13, 2);
//
//
//	ft_print_memory(cw->map, 4096);


}
