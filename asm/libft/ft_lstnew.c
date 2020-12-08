/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 12:26:12 by heantoni          #+#    #+#             */
/*   Updated: 2019/09/29 14:43:05 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newt;

	newt = (t_list*)malloc(sizeof(t_list));
	if (newt)
	{
		if (content == NULL)
		{
			newt->content = NULL;
			content_size = 0;
		}
		else
		{
			if ((newt->content = (void*)malloc(content_size)) != NULL)
				ft_memcpy(newt->content, content, content_size);
			else
			{
				free(newt);
				return (NULL);
			}
		}
		newt->content_size = content_size;
		newt->next = NULL;
		return (newt);
	}
	return (NULL);
}
