/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 20:55:23 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/24 18:32:15 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*t2;

	t2 = (unsigned char*)src;
	t = (unsigned char*)dest;
	i = 0;
	while (t2 != t && i < n)
	{
		t[i] = t2[i];
		i++;
	}
	return (dest);
}
