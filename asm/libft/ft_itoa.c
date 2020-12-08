/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:30:01 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/26 22:11:05 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*perevorot(int n, char *newstr, int flag, int kol)
{
	newstr[kol] = '\0';
	kol--;
	if (n == 0)
	{
		newstr[kol] = '0';
		return (newstr);
	}
	if (flag == 1)
		n = n * (-1);
	while (n > 0)
	{
		newstr[kol] = n % 10 + '0';
		n = n / 10;
		kol--;
	}
	if (flag == 1)
		newstr[kol] = '-';
	return (newstr);
}

static int		scet(long new, int kol)
{
	while (new > 0)
	{
		new = new / 10;
		kol++;
	}
	return (kol);
}

char			*ft_itoa(int n)
{
	char		*newstr;
	int			kol;
	int			new;
	int			flag;

	kol = 0;
	new = n;
	flag = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		new *= (-1);
		kol = 1;
		flag = 1;
	}
	kol = scet(new, kol);
	if (n == 0 || n == (-0))
		kol = 1;
	newstr = (char*)malloc(sizeof(char) * (kol + 1));
	if (newstr == NULL)
		return (0);
	return (perevorot(n, newstr, flag, kol));
}
