/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksenaida <ksenaida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 16:20:38 by ksenaida          #+#    #+#             */
/*   Updated: 2019/09/21 22:21:32 by ksenaida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*out;
	int		len;
	int 	i;

	i = 0;
	len = ft_strlen(str);
	if (!(out = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (--len >= 0)
	{
		out[i] = str[len];
		i++;
	}
	out[i] = '\0';
	return (out);
}
