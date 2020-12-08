/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 20:13:30 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/23 20:47:02 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t dl;

	i = 0;
	dl = ft_strlen(dest);
	while (i < n && *src)
	{
		dest[dl] = *src;
		src++;
		dl++;
		i++;
	}
	dest[dl] = '\0';
	return (dest);
}
