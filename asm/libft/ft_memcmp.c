/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:17:36 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/24 18:35:08 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*st;
	unsigned char	*st2;
	size_t			i;

	i = 0;
	st = (unsigned char*)s1;
	st2 = (unsigned char*)s2;
	while (i < n)
	{
		if (st[i] != st2[i])
			return (st[i] - st2[i]);
		i++;
	}
	return (0);
}
