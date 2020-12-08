/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:57:10 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/25 21:14:06 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*t2;

	if (dest == NULL && src == NULL)
		return (NULL);
	t2 = (unsigned char*)src;
	t = (unsigned char*)dest;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			t[i] = t2[i];
			i++;
		}
	}
	else
		while (n != 0)
		{
			i = n - 1;
			t[i] = t2[i];
			n--;
		}
	return (dest);
}
