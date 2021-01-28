#include "libft.h"

int		ft_bin_to_dec(const unsigned char *bin, int size)
{
	int i;
	int value;

	i = 0;
	value = 0;
	while (size)
	{
		value += ((bin[size - 1] & 255) << (8 * i));
		i++;
		size--;
	}
	return (value);
}