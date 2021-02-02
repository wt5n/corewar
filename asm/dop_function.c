/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:20:14 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/20 20:22:56 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		propysc_probel(char *str)
{
	int	i;

	i = 0;
	while (str && (str[i] == '\t' || str[i] == ' '))
		i++;
	if (str[i] == '\0')
		return (-3);
	return (i);
}

int		number_pr(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\t' && str[i] != ' ')
		i++;
	if (str[i] == '\0')
		return (3);
	return (i);
}

int		kol_sim_not(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] == c)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int		kol_sim(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

int		proverca(char c)
{
	if (c == 'r')
		return (REG_CODE);
	else if (c == '%')
		return (DIR_CODE);
	else
		return (IND_CODE);
	return (-1);
}
