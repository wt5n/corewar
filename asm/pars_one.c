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

int		par3(char *line, t_chempion *ch, t_new_st_label **label, \
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

int		pars_one(char *li, t_chempion *ch, t_new_st_label **labe, \
		t_op_strukt **op)
{
	int	i;

	i = 0;
	if (li && li[0] != ' ' && li[0] != '\0' && li[0] != '\t' && \
	li[0] != '\n')
	{
		if (li[0] == '.')
		{
			if (pars_one2(li, ch, labe) < 0)
				return (-1);
		}
		else
		{
			if ((par_l(li, ch, labe, &i)) < 0 && (par3(li, ch, labe, op) < 0))
				return (-1);
			else
				pars_one(&(li[i]), ch, labe, op);
		}
	}
	else
	{
		if (par3(li, ch, labe, op) < 0)
			return (-1);
	}
	return (1);
}
