/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 21:01:52 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/20 21:17:16 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		pars_one3(char *line, t_chempion *ch, t_new_st_label **label, \
		t_op_strukt **op)
{
	int k;

	k = 0;
	if ((k = pars_operation(line, ch, op, label)) < 0)
		return (-1);
	if (k != 0 && k != 3)
		ch->flag_label = 0;
	return (1);
}

int		pars_one2(char *line, t_chempion *ch, t_new_st_label **label)
{
	if (ch->name == NULL && (pars_name(line, ch, label)) < 0)
		return (-1);
	else
		pars_name(line, ch, label);
	return (1);
}

int		pars_one(char *line, t_chempion *ch, t_new_st_label **label, \
		t_op_strukt **op)
{
	int	i;

	i = 0;
	if (line && line[0] != ' ' && line[0] != '\0' && line[0] != '\t' && \
	line[0] != '\n')
	{
		if (line[0] == '.')
		{
			if (pars_one2(line, ch, label) < 0)
				return (-1);
		}
		else
		{
			if ((pars_label(line, ch, label, &i)) < 0 && \
					(pars_one3(line, ch, label, op) < 0))
				return (-1);
			else
				pars_one(&(line[i]), ch, label, op);
		}
	}
	else
	{
		if (pars_one3(line, ch, label, op) < 0)
			return (-1);
	}
	return (1);
}
