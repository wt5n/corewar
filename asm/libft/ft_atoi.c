/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 20:13:23 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/27 23:01:15 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		pro(char *str)
{
	if (*str == ' ' || *str == '\n' || *str == '\v' || \
			(*str == '\t') || (*str == '\f') || (*str == '\r'))
		return (1);
	return (0);
}

static int		flag(char *str)
{
	int		fl;

	fl = 1;
	if (*str == '-')
		fl = -1;
	return (fl);
}

int				ft_atoi(char *str)
{
	long long	chuslo;
	int			fl;

	chuslo = 0;
	while (pro(str) == 1)
		str++;
	fl = flag(str);
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		chuslo = chuslo * 10 + (*str - '0');
		str++;
	}
	if ((chuslo > (chuslo * 10)) && fl == -1)
		return (0);
	if (chuslo > (chuslo * 10))
		return (-1);
	return (fl * chuslo);
}
