/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zap_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 21:01:48 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/23 21:01:50 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label				*ft_add_label(t_label **label, char *str)
{
	t_label			*next;
	t_label			*n_label;

	if (!(n_label = new_add_label(str)))
		return (NULL);
	next = *label;
	n_label->next = next;
	*label = n_label;
	return (n_label);
}

t_label				*add_label(char *str, t_label **label)
{
	if (!*label)
		return (*label = new_add_label(str));
	return (ft_add_label(label, str));
}

t_new_st_label		*new_st_add_label(char *str)
{
	t_new_st_label	*label;

	if (!(label = (t_new_st_label *)malloc(sizeof(t_new_st_label))))
		return (NULL);
	label->lab = new_add_label(str);
	label->next = NULL;
	return (label);
}

t_new_st_label		*ft_st_add_label(t_new_st_label **label, char *str)
{
	t_new_st_label	*n_label;
	t_new_st_label	*new_label;
	t_new_st_label	*next;

	new_label = *label;
	next = *label;
	if (!(n_label = new_st_add_label(str)))
		return (NULL);
	while (new_label->next)
		new_label = new_label->next;
	new_label->next = n_label;
	return (next);
}

t_new_st_label		*add_st_label(char *str, t_new_st_label **label)
{
	if (!*label)
		return (*label = new_st_add_label(str));
	return (ft_st_add_label(label, str));
}
