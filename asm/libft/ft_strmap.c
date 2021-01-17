/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 13:27:40 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/26 22:03:57 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*t;
	int		i;

	if (s && f)
	{
		t = (char*)malloc(sizeof(char const) * (ft_strlen(s) + 1));
		if (t == NULL)
			return (0);
		i = 0;
		while (s[i])
		{
			t[i] = f(s[i]);
			i++;
		}
		t[i] = '\0';
		return (t);
	}
	return (0);
}
