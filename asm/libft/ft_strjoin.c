/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:30:05 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/26 22:10:25 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*per(char const *s2, int dl2)
{
	char	*newstr;

	newstr = (char*)malloc(sizeof(char) * (dl2 + 1));
	if (newstr == 0)
		return (NULL);
	ft_strcat(newstr, s2);
	return (newstr);
}

static char	*vtor(char const *s1, char const *s2, int dl1, int dl2)
{
	char	*newstr2;
	int		i;

	newstr2 = (char*)malloc(sizeof(char) * (dl1 + dl2 + 1));
	if (newstr2 == 0)
		return (NULL);
	i = 0;
	while (i < dl1)
	{
		newstr2[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < dl2)
	{
		newstr2[dl1 + i] = s2[i];
		i++;
	}
	newstr2[dl1 + i] = '\0';
	return (newstr2);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		dl2;
	int		dl1;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (per(s2, ft_strlen(s2)));
	else
	{
		if (s2 == NULL)
		{
			return (per(s1, ft_strlen(s1)));
		}
		else
		{
			dl2 = ft_strlen(s2);
			dl1 = ft_strlen(s1);
			return (vtor(s1, s2, dl1, dl2));
		}
	}
}
