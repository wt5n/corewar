#include "libft.h"

static void	reverse_clean(char **res, char *temp, int cnt)
{
	int i;

	i = 0;
	*res = (char *)malloc(sizeof(char) * (cnt + 2));
	if (*res == NULL)
		return ;
	(*res)[cnt + 1] = '\0';
	while (cnt >= 0)
	{
		(*res)[i] = temp[cnt];
		cnt--;
		i++;
	}
}

char		*ft_itoa_base(unsigned long long int input, int base, int height)
{
	char	temp[33];
	char	*res;
	int		i;
	char	*symbols;

	i = 0;
	if (base < 2 || base > 16)
		return (0);
	if (height == 0)
		symbols = ft_strdup("0123456789abcdef");
	else if (height == 1)
		symbols = ft_strdup("0123456789ABCDEF");
	while (input >= (unsigned int)base)
	{
		temp[i] = symbols[input % base];
		input /= base;
		i++;
	}
	temp[i] = symbols[input];
	reverse_clean(&res, temp, i);
	free(symbols);
	return (res);
}
