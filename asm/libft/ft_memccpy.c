/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:26:47 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/23 21:17:24 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*t2;
	unsigned char	ch;

	t2 = (unsigned char*)src;
	t = (unsigned char*)dest;
	ch = (unsigned char)c;
	i = 0;
	while (t != t2 && i < n)
	{
		t[i] = t2[i];
		i++;
		if (t2[i - 1] == ch)
			return ((void*)(t + i));
	}
	return (NULL);
}
