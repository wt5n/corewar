/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:53:06 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/26 22:12:19 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*zap(char const *s, int kol, int start)
{
	char		*newstr;
	int			i;

	i = 0;
	newstr = (char*)malloc(sizeof(*s) * kol);
	if (newstr == NULL)
		return (0);
	while (i < kol - 1)
	{
		newstr[i] = s[start + i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char			*ft_strtrim(char const *s)
{
	int			start;
	int			kol;
	int			i;

	i = 0;
	if (s == 0)
		return (NULL);
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i] != '\0')
		i++;
	start = i;
	i = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\0')
		i--;
	kol = i - start + 2;
	if (start > i)
		return (ft_strnew(0));
	return (zap(s, kol, start));
}
