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
	if (line[0] == COMMENT_CHAR || line[0] == ALT_COMMENT_CHAR)
		return (1);
	if (pars_operation(line, ch, op, label) < 0)
		return (-1);
	ch->flag_label = 0;
	return (1);
}

int		pars_one2(char *line, t_chempion *ch)
{
	if (pars_name(line, ch) < 0)
		return (-1);
	return (1);
}

int		pars_one(char *li, t_chempion *ch, t_new_st_label **labe, \
		t_op_strukt **op)
{
	int	i;
	int	probel;

	i = 0;
	probel = propysc_probel(li);
		if (probel == -3)
			return 1;
	if (li[probel] && li[probel] != ' ' && li[probel] != '\0' && li[probel] != '\t' && \
	li[probel] != '\n' && li[probel] != COMMENT_CHAR && li[probel] != ALT_COMMENT_CHAR)
	{
		if (li[probel] == '.')
		{
			if (pars_one2(&(li[probel]), ch) < 0)
				return (-1);
		}
		else
		{
			if (ch->name == NULL || ch->comment == NULL) //??????????? 
				return (-1);
			int	lab = lab_ch(&(li[probel]));
			if (lab == -2 || lab == -1)
				{	
					if (par3(&(li[probel]), ch, labe, op) < 0)
						return (-1);
				}
			else
				{
					li[lab] = '\0';
					if ((par_l(&(li[probel]), ch, labe)) < 0)
						return (-1);
					i = lab - probel + 1;
					probel = propysc_probel(&(li[i]));
					if (probel == -3)
							return 1;
					if (par3(&(li[i+probel]), ch, labe, op) < 0)
							return (-1);
				}
		}
	}
	return (1);
}
