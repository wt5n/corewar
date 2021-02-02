/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proverca_registra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:28:45 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/24 14:48:42 by heantoni         ###   ########.fr       */
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
	i = 0;
	while (str2[i] && str2[i] != ' ' && str2[i] != '\t')
		i++;
	if (i < (int)ft_strlen(str))
		str2[i] = '\0';
	label2 = label;
	while (label2)
	{
		lab = label2->lab;
		while (lab)
		{
			//printf("lab->name = %s, str = %s!\n",lab->name, str);
			if ((ft_strcmp(lab->name, str2)) == 0)
				return (lab->op->smechenee - ch->mestnoe_smehenee);
			lab = lab->next;
		}
		label2 = label2->next;
	}
	ch->flag = -1;
	return (-1);
}

void				byte_code(short tmp2, t_chempion *ch)
{
	//printf("tmp = %d\n", tmp2);
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

	/*int i;
	i = 0;
	while (srez[i] && srez[i] != ' ' && srez[i] != '\t')
		i++;
	//printf("i = %d    ", i);
	if (i < (int)ft_strlen(srez))
		srez[i] = '\0';*/
	//printf("probel = %d", probel);
	//if (probel>0)
	//	srez[probel] = '\0';
	srez2 = ft_strdup(&srez[2]);
	//printf("%s\n", srez2);
	ch->flag = 0;
	if (op_tab[new_op->name].size == 1)
		{
			if ((k = proverca_instruction(srez2, ch, label)) < 0)
				k = 65536 + k;
				//printf("srez2 = %s k = %d\n", srez2, k);
				//printf("%d\n",ch->flag);
			if (ch->flag == -1)
				return (-1);
			byte_code(k, ch);
		}
		else
		{
			if ((k = proverca_instruction(srez2, ch, label)) < 0)
				k2 = 4294967296 + k;
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

	if (srez[0] == 'r')
	{
		if ((tmp = ft_atoi(&srez[1])) <= 99 && tmp > 0)
			ch->code[ch->tu] = tmp;
		else
		{
			return (-1);
		}
		
	}
	else if (srez[0] == DIRECT_CHAR)
	{
		if (srez[1] == LABEL_CHAR)
		{
			//printf("sr = %s\n", srez);
			if (proverca_registr2(srez, ch, label, new_op) < 0)
				return (-1);
		}
		else
		{
			proverca_registr3(srez, ch, new_op);
		}
	}
	else if ((tmp2 = ft_latoi(srez)) >= 0)
	{
		//printf("cheslo = %ld\n", tmp2);
		byte_code(tmp2, ch);
	}
	else if ((tmp2 = ft_latoi(srez)) < 0)
	{
		tmp2 = 4294967296 + tmp2;
		//printf("cheslo = %ld\n", tmp2);
		byte_code(tmp2, ch);
	}
	return (1);
}
