/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:54:00 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/20 20:45:51 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*t;

	t = (unsigned char*)destination;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		t[i] = cc;
		i++;
	}
	return (t);
}
