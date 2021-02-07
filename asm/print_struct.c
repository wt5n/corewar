/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:42:29 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/24 15:45:33 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

void				print_op(t_op_strukt *op)
{
	t_op_strukt		*new_op;
	int				kol;

	new_op = op;
	kol = 0;
	int i = 0;
	while (new_op != NULL)
	{
		//printf("%s   size = %d", op_tab[new_op->name].name, new_op->size);
		kol += new_op->size;
		//printf("    kol = %d\n", kol);
		new_op = new_op->next;
		i++;
		//printf("    i = %d\n", i);
		//printf("%d\n", kol);
		//if (kol == 312)
		//	printf("my i = %d\n",i);
	}
	//printf("kol_size = %d\n", kol);
}

void				print_struct(t_new_st_label *label)
{
	t_new_st_label	*new_label;
	t_label			*la;

    new_label = label;
	while (new_label)
	{
		la = new_label->lab;
		while (la)
		{
			//printf("%s   size = %d   smechenee = %d \n", la->name, la->op->size, la->op->smechenee);
			la = la->next;
		}	
		//printf("      \n");
		new_label = new_label->next;
	}
}
