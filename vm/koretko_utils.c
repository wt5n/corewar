/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koretko_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:02:34 by hlikely           #+#    #+#             */
/*   Updated: 2021/02/04 20:03:03 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/vm.h"

void		chain_kor(t_koretko **kors, t_koretko *kor)
{
	kor->next = *kors;
	*kors = kor;
}

t_koretko	*create_koretko(int id, int position)
{
	t_koretko	*kor;

	if (!(kor = (t_koretko*)ft_memalloc(sizeof(t_koretko))))
		return (NULL);
	kor->next = NULL;
	kor->id = id;
	kor->position = position;
	return (kor);
}
