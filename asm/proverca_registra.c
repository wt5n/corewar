/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proverca_registra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:28:45 by heantoni          #+#    #+#             */
/*   Updated: 2021/02/03 20:53:02 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					proverca_instruction(char *str, t_chempion *ch, \
		t_new_st_label *label)
{
	t_new_st_label	*label2;
	t_label			*lab;
	char			*str2;

	int i;
	str2 = ft_strdup(str);
	//printf("%s\n", str2);
	i = number_pr(str2);
	//printf("%d\n", i);
	if (i != -3 && i < (int)ft_strlen(str))
		str2[i] = '\0';
	label2 = label;
	while (label2)
	{
		lab = label2->lab;
		while (lab)
		{
			//printf("lab = !%s!   !%s!\n", lab->name, str2);
			//printf("smeche = !%d!   !%d!\n", lab->op->smechenee, ch->mestnoe_smehenee);
			if ((ft_strcmp(lab->name, str2)) == 0)
					{
						//printf("!!!!!!   %d\n", lab->op->smechenee - ch->mestnoe_smehenee);
						if (lab->op == NULL)
							{
								//printf("sme = %d   mes_sme = %d    mes_size = %d\n", ch->smehenee, ch->mestnoe_smehenee, ch->smehenee - ch->mestnoe_smehenee);
								return (ch->smehenee - ch->mestnoe_smehenee);
							}
						return (lab->op->smechenee - ch->mestnoe_smehenee);
					}
			lab = lab->next;
		}
		label2 = label2->next;
	}
	ch->flag = -1;
	return (-1);
}

void				byte_code(short tmp2, t_chempion *ch)
{
	ch->code[ch->tu] = tmp2 >> 8;
	(ch->tu)++;
	ch->code[ch->tu] = tmp2 & 255;
}

int					proverca_registr2(char *srez, t_chempion *ch, \
		t_new_st_label *label, t_op_strukt *new_op)
{
	char			*srez2;
	long			k2;
	int				k;
	int				flag;

	//printf("reg2 = %s\n", srez);
	flag = 0;
	if (srez[0] == ':')
	{
		flag = 1;
		srez2 = ft_strdup(&srez[1]);
	}
	else
		srez2 = ft_strdup(&srez[2]);
	ch->flag = 0;
	//printf("%d\n", new_op->name);
	if (op_tab[new_op->name].size == 1 || flag == 1)
	{
		//printf("%d   %s\n", new_op->name, srez2);
		if ((k = proverca_instruction(srez2, ch, label)) < 0)
			k = 65536 + k;
		//printf("k = %d\n", k);
		//printf(" srez2 = %s\n", srez2);
		
		if (ch->flag == -1)
			return (-1);
		byte_code(k, ch);
	}
	else
	{
		if ((k2 = proverca_instruction(srez2, ch, label)) < 0)
			k2 = 4294967296 + k2;
		if (ch->flag == -1)
			return (-1);
		byte_code(k2 >> 16, ch);
		(ch->tu)++;
		byte_code(k2, ch);
	}
	return (1);
}

void				proverca_registr3(char *srez, t_chempion *ch, \
		t_op_strukt *new_op)
{
	long			k2;
	int				k;

	k = 0;
	if (op_tab[new_op->name].size == 0)
	{
		k2 = ft_latoi(&srez[1]);
		if (k2 < 0)
			k2 = 4294967296 + k2;
		byte_code(k2 >> 16, ch);
		(ch->tu)++;
		byte_code(k2, ch);
	}
	if (((k = ft_atoi(&srez[1])) < 0) && op_tab[new_op->name].size == 1)
		k = 65536 + k;
	if (op_tab[new_op->name].size == 1)
		byte_code(k, ch);
}

int					proverca_registr(char *srez, t_chempion *ch, \
		t_new_st_label *label, t_op_strukt *new_op)
{
	int				tmp;
	long			tmp2;

	//printf("proverka = %s\n", srez);
	if (srez[0] == 'r')
	{
		if ((tmp = ft_atoi(&srez[1])) <= 99 && tmp >= 0)
			ch->code[ch->tu] = tmp;
		else
			return (-1);
	}
	else if (srez[0] == DIRECT_CHAR)
	{
		if (srez[1] == LABEL_CHAR)
		{
			if (label_last(&label)->lab->op == NULL)
				label->lab->op->smechenee = 0;
			if (proverca_registr2(srez, ch, label, new_op) < 0)
				return (-1);
		}
		else
			proverca_registr3(srez, ch, new_op);
	}
	else if (srez[0] == LABEL_CHAR)
	{
		if (proverca_registr2(srez, ch, label, new_op) < 0)
			return (-1);
	}
	else if ((tmp2 = ft_latoi(srez)) >= 0)
	{
		byte_code(tmp2, ch);
	}
	else if ((tmp2 = ft_latoi(srez)) < 0)
	{
		tmp2 = 4294967296 + tmp2;
		byte_code(tmp2, ch);
	}
	return (1);
}
