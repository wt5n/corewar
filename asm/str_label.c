/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:54:00 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/23 20:59:37 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label				*new_add_label(char *str)
{
	t_label			*label;

	if (!(label = (t_label *)malloc(sizeof(t_label))))
		return (NULL);
	label->next = NULL;
	label->name = ft_strdup(str);
	label->op = NULL;
	return (label);
}

t_op_strukt			*new_op_struct()
{
	t_op_strukt		*op;

	if (!(op = (t_op_strukt *)malloc(sizeof(t_op_strukt))))
		return (NULL);
	op->name = 0;
	op->size = 0;
	op->stroca = NULL;
	op->next = NULL;
	return (op);
}

t_op_strukt			*ft_add_op_struct(t_op_strukt **op)
{
	t_op_strukt		*n_op;
	t_op_strukt		*new_op;
	t_op_strukt		*new2_op;

	if (!(n_op = new_op_struct()))
		return (NULL);
	new_op = *op;
	new2_op = *op;
	while (new_op->next)
		new_op = new_op->next;
	new_op->next = n_op;
	return (new2_op);
}

t_op_strukt			*add_op_struct(t_op_strukt **op)
{
	if (!*op)
		return (*op = new_op_struct());
	return (ft_add_op_struct(op));
}
