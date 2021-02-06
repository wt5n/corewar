/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:05:18 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/23 20:53:13 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					analiz_registr(char *srez, t_op_strukt **op)
{
	int				k;
	int				probel;

	probel = 0;
	while (srez[probel] == '\t' || srez[probel] == '\r' || \
	srez[probel] == '\f' || srez[probel] == '\v' || srez[probel] == ' ')
		probel++; 
	//printf("!%c!    ----  %d\n", srez[probel], probel);
	if (srez[probel] == 'r')
	{
		
		if ((k = ft_atoi(&srez[probel + 1])) >= 0 && k < 100) //&& k < REG_NUMBER)
		{
			//printf("****\n");
			(*op)->size += T_REG;
		}
		else
			return (-1);
	}
	else if (srez[probel] == DIRECT_CHAR)
	{
		if (op_tab[(*op)->name].size == 0)
			(*op)->size += T_DIR * 2;
		else
			(*op)->size += T_DIR;
		//printf("per_i = %d\n", (*op)->size);
	}
	else
		(*op)->size += 2;
	//printf("%s per_i = %d\n",srez, (*op)->size);
	return (1);
}

int					pars_register(char *str, t_op_strukt **op)
{
	int				tecyhee;
	char			*srez;
	int				n;

//printf("str = %s\n", str);
	n = 0;
	if (kol_sim(str, COMMENT_CHAR) != -1)
		str[kol_sim(str, COMMENT_CHAR)] = '\0';
	if (kol_sim(str, ALT_COMMENT_CHAR) != -1)
		str[kol_sim(str, ALT_COMMENT_CHAR)] = '\0';
	(*op)->stroca = ft_strdup(str);
	//printf("stroca = !%s!\n", (*op)->stroca);
	while (n >= 0)
	{
		if ((tecyhee = kol_sim_not(str, ' ')) < 0)
			return (-1);
		n = kol_sim(&str[tecyhee], SEPARATOR_CHAR);
		if (n >= 0)
		{
			srez = cut_one(&str[tecyhee], SEPARATOR_CHAR, 0);
			tecyhee += (n + 1);
			str = str + tecyhee;
		}
		else
			srez = cut_one(&str[tecyhee], '\0', 0);
		//printf("srez = %s\n", srez);
		if (analiz_registr(srez, op) < 0)
			return (-1);
	}
	return (1);
}

void				zap_label(t_new_st_label **label, t_op_strukt *op)
{
	t_label			*lab;
	t_new_st_label	*new_label;

	new_label = *label;
	while (new_label->next)
		new_label = new_label->next;
	lab = new_label->lab;
	while (lab)
	{
		lab->op = op;
		lab = lab->next;
	}
	//printf("op = %s\n", op->stroca);
}

int					pars_operation(char *line, t_chempion *ch, \
		t_op_strukt **op, t_new_st_label **label)
{
	char			*srez;
	t_op_strukt		*new_op;
	t_new_st_label	*new_label;
	int				probel;

	//printf("op = %s\n", line);
	probel = number_pr(line);
	srez = cut_one(&line[propysc_probel(line)], \
	line[propysc_probel(line) + probel], 0);
	//printf("srez_new = !%s!\n", srez);
	if (operation_name(srez, op) < 0)
		return (-1);
	if (ch->flag_label == 1)
		zap_label(label, operation_last(op));
	new_op = operation_last(op);
	//printf("propysk = %d\n", propysc_probel(line) + probel + 1);
	if ((pars_register(&line[propysc_probel(line) + probel + 1], &new_op)) < 0)
		return (-1);
	new_op->smechenee = ch->smehenee;
	ch->smehenee += new_op->size;
	//printf("new_op = %d\n", ch->smehenee);
	if (ch->flag_label == 1)
	{
		new_label = label_last(label);
		new_label->smehenee = ch->smehenee;
		//printf("%s\n", new_label->lab->name);
	}
	//printf("&&&");
	return (1);
}
