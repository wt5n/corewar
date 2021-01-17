/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 12:59:10 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/25 18:44:26 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*t;
	int		kol;
	int		i;

	kol = ft_strlen(needle);
	if (*needle == '\0')
		return ((char*)haystack);
	while (*needle && *haystack)
	{
		t = ft_strchr(haystack, needle[0]);
		if (t == 0)
			return (0);
		else
		{
			i = 1;
			while (needle[i] != '\0' && (t[i] == needle[i]))
				i++;
			if (needle[i] == '\0')
				return (t);
		}
		haystack = t + 1;
	}
	return (NULL);
}
