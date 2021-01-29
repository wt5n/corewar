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
	//printf("%s\n", line);
	if ((k = pars_operation(line, ch, op, label)) < 0)
		return (-1);
	if (k != 0 && k != 3)
		ch->flag_label = 0;
	return (1);
}

int		pars_one2(char *line, t_chempion *ch, t_new_st_label **label)
{
	//printf("line = %s\n", line);
	if (ch->name == NULL)
		{
			if ((pars_name(line, ch, label)) < 0)
				return (-1);
		}
	else
		if (pars_name(line, ch, label) < 0)
			return (-1);
	return (1);
}

int		pars_one(char *li, t_chempion *ch, t_new_st_label **labe, \
		t_op_strukt **op)
{
	int	i;
	int	probel;

	i = 0;
	if (li && li[0] != ' ' && li[0] != '\0' && li[0] != '\t' && \
	li[0] != '\n' && li[0] != '#')
	{
		if (li[0] == '.')
		{
			//printf(".\n");
			if (pars_one2(li, ch, labe) < 0)
				return (-1);
		}
		else
		{
			if ((par_l(li, ch, labe, &i)) < 0)
				{
					printf("\n******\n");
					if (par3(li, ch, labe, op) < 0)
					return (-1);
				}
			else
			{
				if (propysc_probel(&(li[i])) != 3)
					if (par3(&(li[i]), ch, labe, op) < 0)
						return (-1);
			}
				//pars_one(&(li[i]), ch, labe, op);
		}
	}
	else
	{
		printf("%s\n", li);
		if (li && (li[0] == ' ' || li[0] == '\t') && \
		(probel = kol_sim_not(li, ' ') != 0 || (probel = kol_sim_not(li, '\t')) != 0))
		if (li[probel] != '#' && par3(&(li[probel]), ch, labe, op) < 0)
			return (-1);
	}
	return (1);
}
