/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:33:46 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/20 21:01:15 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*cut_one(char *str, char c, int n)
{
	char	*srez;
	int		n_line;

	n_line = kol_sim(&(str[n]), c);
	if (n_line != (int)ft_strlen(str))
		str[n_line] = '\0';
	srez = ft_strdup(&str[0]);
	return (srez);
}

int			pars_name(char *line, t_chempion *ch, t_new_st_label **label)
{
	char	*srez;
	int		tecyhee;

	srez = NULL;
	tecyhee = kol_sim(line, ' ') + 1;
	srez = cut_one(line, ' ', 0);
	if (tecyhee > 0 && (ft_strcmp(srez, NAME_CMD_STRING) == 0 || \
				ft_strcmp(srez, COMMENT_CMD_STRING) == 0))
	{
		if (ft_strcmp(srez, NAME_CMD_STRING) == 0)
			ch->flag = 1;
		else
			ch->flag = 2;
		tecyhee = tecyhee + kol_sim_not(&(line[tecyhee]), ' ');
		if (line[tecyhee] != '"')
			return (-1);
		line[tecyhee + kol_sim(&line[tecyhee + 1], '"') + 1] = '\0';
		srez = ft_strdup(&line[tecyhee + 1]);
	}
	else
		return (-1);
	zap_struct_ascii(ch, srez, label);
	return (1);
}

int			proverca_label(char *str)
{
	int		i;
	int		k;
	char	*label_char;

	i = 0;
	label_char = LABEL_CHARS;
	while (str[i] != '\0')
	{
		k = 0;
		while (label_char[k] != '\0' && label_char[k] != str[i])
			k++;
		if (label_char[k] == '\0')
			return (-1);
		i++;
	}
	return (1);
}

int			pars_label(char *line, t_chempion *ch, t_new_st_label **label, \
		int *i)
{
	char	*srez;
	int		tecyhee;

	tecyhee = 0;
	srez = NULL;
	if ((tecyhee = kol_sim(line, ':') + 1) != 0)
	{
		srez = cut_one(line, ':', 0);
		ch->flag = 3;
		zap_struct_ascii(ch, srez, label);
		free(srez);
		(*i) = tecyhee;
	}
	else
		return (-1);
	return (1);
}
