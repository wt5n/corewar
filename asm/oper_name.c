/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:30:25 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/20 20:33:21 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_new_st_label		*label_last(t_new_st_label **label)
{
	t_new_st_label	*new_label;

	new_label = *label;
	while (new_label->next)
		new_label = new_label->next;
	return (new_label);
}

t_op_strukt			*operation_last(t_op_strukt **op)
{
	t_op_strukt		*new_op;

	new_op = *op;
	while (new_op->next)
		new_op = new_op->next;
	return (new_op);
}

int					operation_name(char *srez, t_op_strukt **op)
{
	int				i;
	t_op_strukt		*new_op;

	i = 0;
	while (op_tab[i].name != 0 && ft_strcmp(op_tab[i].name, srez) != 0)
		i++;
	if (op_tab[i].name == 0)
		return (-1);
	add_op_struct(op);
	new_op = operation_last(op);
	new_op->name = op_tab[i].code_op - 1;
	new_op->size += 1;
	if (op_tab[new_op->name].code_type == 1)
		new_op->size += 1;
	return (1);
}
