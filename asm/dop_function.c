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
	while (str[i] != '\0' && (str[i] == '\t' || str[i] == ' ' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '\0')
		return (-3);
	return (i);
}

int		number_pr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\t' && str[i] != ' ' && str[i] != '\v' && str[i] != '\r')
		i++;
	if (str[i] == '\0')
		return (-3);
	return (i);
}

int		kol_sim_not(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == c)
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
	//printf("r = %c\n", c);
	if (c == 'r')
		return (REG_CODE);
	else if (c == '%')
		return (DIR_CODE);
	else
		return (IND_CODE);
	return (-1);
}

int		probels(char c)
{
	if (c == '\t' || c == '\r' || c == ' ' || c == '\v')
		return (1);
	return (0); 
}

int		lab_ch(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != LABEL_CHAR)
	{
		if (probels(str[i]) == 1)
			return (-2); 
		i++;
	}	
	if (str[i] == '\0')
		return (-1);
	return (i);
}