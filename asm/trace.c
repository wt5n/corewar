/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:49:26 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/24 15:29:37 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char				op_reg2(unsigned char type, int kol)
{
	type = type << 2;
	if (kol == 1)
		type = type << 4;
	else if (kol == 2)
		type = type << 2;
	return (type);
}

char				*op_reg3(int n, char **str, int *tecyhee, \
		unsigned char *type)
{
	char			*srez;

	if (n >= 0)
	{
		srez = cut_one(&((*str)[*tecyhee]), SEPARATOR_CHAR, 0);
		(*tecyhee) += (n + 1);
		(*str) = (*str) + *tecyhee;
	}
	else
		srez = cut_one(&((*str)[*tecyhee]), '\0', 0);
	(*type) = (((*type) << 2) + (proverca(srez[0])));
	return (srez);
}

char				op_reg(char *str, t_chempion *ch, t_new_st_label *label, \
		t_op_strukt *new_op)
{
	int				n;
	unsigned char	type;
	int				tecyhee;
	char			*srez;
	int				kol;

	n = 0;
	kol = 0;
	type = 0;
	while (n >= 0)
	{
		if ((tecyhee = kol_sim_not(str, ' ')) < 0)
			return (-1);
		n = kol_sim(&str[tecyhee], SEPARATOR_CHAR);
		srez = op_reg3(n, &str, &tecyhee, &type);
		kol += 1;
		if ((proverca_registr(srez, ch, label, new_op)) < 0)
			return (-1);
		(ch->tu)++;
	}
	return (op_reg2(type, kol));
}

void				pars_stroca(t_chempion *ch, t_op_strukt *last_op, \
		t_new_st_label *label)
{
	char			*str;

	str = last_op->stroca;
	ch->mestnoe_smehenee = last_op->smechenee;
	ch->mestnoe_size = last_op->size;
	if (ch->i <= ch->mestnoe_smehenee)
	{
		ch->code[ch->i] = last_op->name + 1;
		(ch->i)++;
		if (op_tab[last_op->name].code_type == 1)
		{
			ch->tu = (ch->i) + 1;
			ch->code[ch->i] = op_reg(str, ch, label, last_op);
		}
		else
		{
			ch->tu = ch->i;
			op_reg(str, ch, label, last_op);
		}
	}
	ch->i = ch->tu;
}

void				trace_byte_code(t_chempion *ch, t_new_st_label *label, \
		t_op_strukt *op)
{
	t_op_strukt		*op_new;

	op_new = op;
	ch->i = 0;
	ch->code = (char*)malloc(sizeof(char) * ch->smehenee);
	while (op_new)
	{
		pars_stroca(ch, op_new, label);
		op_new = op_new->next;
	}
}
