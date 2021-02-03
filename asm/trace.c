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
	//printf("kol = %d %d\n", kol, type);
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
	int				k;

	//printf("str = !%s!\n",*str);
	if (n >= 0)
	{
		//k = propysc_probel(*(str));
		srez = cut_one(&((*str)[*tecyhee]), SEPARATOR_CHAR, 0);
		//printf("tecyhee = %d, srez = !%s!\n", *tecyhee, srez);
		(*tecyhee) += n + 1;
		(*str) = (*str) + *tecyhee;
		//printf("stroca = %s\n", *str);
	}
	else
		{
			//k = propysc_probel(*(str));
			srez = cut_one(&((*str)[*tecyhee]), '\0', 0);
			//printf("srez = %s\n", srez);
		}
	k = propysc_probel(srez);
	//printf("srez = !%s!\n", &srez[k]);
	(*type) = (((*type) << 2) + (proverca(srez[k])));
	return (srez);
}

char				op_reg(char *str, t_chempion *ch, t_new_st_label *label, \
		t_op_strukt *new_op)
{
	int				n;
	unsigned char	type;
	int				tecyhee;
	char			*srez = NULL;
	int				kol;
	//int				k;

	n = 0;
	kol = 0;
	type = 0;
	while (n >= 0)
	{
		if ((tecyhee = kol_sim_not(str, ' ')) < 0)
			return (-1);
		tecyhee = propysc_probel(str);
		n = kol_sim(&str[tecyhee], SEPARATOR_CHAR);
		//printf("srez_do = !%s!\n", str);
		srez = op_reg3(n, &str, &tecyhee, &type);
		kol += 1;
		//printf("srez = !%s!    tecyhee = %d\n", srez, tecyhee);
		//k = propysc_probel(srez);
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
	int				k;

	str = last_op->stroca;
	ch->mestnoe_smehenee = last_op->smechenee;
	ch->mestnoe_size = last_op->size;
	//printf("i = %d  tu = %d smeche = %d\n", ch->i, ch->tu, ch->mestnoe_smehenee);
	//if (ch->i <= ch->mestnoe_smehenee)
	//{
		//printf("name = %d\n", last_op->name);
		ch->code[ch->i] = last_op->name + 1;
		(ch->i)++;
		k = propysc_probel(str);
		if (k != -3)
		{
			if (op_tab[last_op->name].code_type == 1)
		{
			ch->tu = (ch->i) + 1;
			//printf("!%s!\n", &(str[k]));
			ch->code[ch->i] = op_reg(&(str[k]), ch, label, last_op);
		}
		else
		{
			ch->tu = ch->i;
			op_reg(&(str[k]), ch, label, last_op);
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
	//printf("ch->smehenee = %d\n", ch->smehenee);
	ch->code = (char*)malloc(sizeof(char) * ch->smehenee);
	while (op_new)
	{
		pars_stroca(ch, op_new, label);
		op_new = op_new->next;
	}
}
