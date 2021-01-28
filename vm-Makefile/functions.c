#include "inc/vm.h"

void 	ft_swap_two_let(char *str)
{
	int 	i;
	char	tmp;

	i = 0;
	while (str[i] != '\0')
	{
		tmp = str[i];
		str[i] = str[i + 1];
		str[i + 1] = tmp;
		i += 2;
	}
}
