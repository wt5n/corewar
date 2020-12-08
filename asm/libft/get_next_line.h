/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cport <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:47:32 by cport             #+#    #+#             */
/*   Updated: 2020/02/26 22:18:25 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>

typedef struct		s_line
{
	int				fd;
	char			*memorized;
	struct s_line	*next;
}					t_line;

int					get_next_line(const int fd, char **line);

#endif
