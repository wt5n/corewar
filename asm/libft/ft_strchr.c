/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 20:38:52 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/24 18:50:43 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*t;
	int		i;
	int		n;

	t = (char*)s;
	i = 0;
	n = ft_strlen(s);
	while (i < n + 1)
	{
		if (*t != c)
			t++;
		else
			return (t);
		i++;
	}
	return (0);
}
