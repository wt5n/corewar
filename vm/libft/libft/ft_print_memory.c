#include "libft.h"

void	ft_print_hex(unsigned char c)
{
	size_t	i;
	size_t	j;

	char *base = "0123456789abcdef";
	write(1, &base[c / 16], 1);
	write(1, &base[c % 16], 1);
}

void	ft_print_memory(const void *addr, size_t size)
{
	size_t i;
	size_t j;

	unsigned  char *p;

	i = 0;
	p = (unsigned char*)addr;
	while (i < size)
	{
		j = 0;
		if (i == 0)
			ft_printf("0x0000 : ");
		else
			ft_printf("%0#6x : ", i);
		// ft_printf("%05d ", 1);
		while (j < 64 && i + j < size)
		{
			ft_print_hex(p[i + j]);
//			if (j % 2)
			write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i += 64;
	}
}
