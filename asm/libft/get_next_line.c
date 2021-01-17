/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cport <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 16:42:07 by cport             #+#    #+#             */
/*   Updated: 2019/11/26 22:00:46 by cport            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_line	*new_fd_list(int fd)
{
	t_line	*new;

	new = (t_line *)malloc(sizeof(t_line));
	new->fd = fd;
	new->memorized = NULL;
	new->next = NULL;
	return (new);
}

int		get_status(int count, char *line, char *memorized, char *sep)
{
	if (!line || count < 0)
	{
		if (memorized)
			ft_strdel(&memorized);
		return (-1);
	}
	if (sep || (memorized && (ft_strlen(line) || ft_strlen(memorized))))
		return (1);
	if (!ft_strlen(line) && !count)
	{
		ft_strdel(&line);
		return (0);
	}
	return (1);
}

char	*process_memorized(char *memorized, char **line)
{
	char	*sep;

	sep = NULL;
	if (memorized)
		if ((sep = ft_strchr(memorized, '\n')))
		{
			*sep = '\0';
			*line = ft_strdup(memorized);
			ft_strcpy(memorized, ++sep);
		}
		else
		{
			*line = ft_strdup(memorized);
			ft_strclr(memorized);
		}
	else
		*line = ft_strnew(0);
	return (sep);
}

int		process_line(const int fd, char **line, char **memorized, int count)
{
	char			buf[BUFF_SIZE + 1];
	char			*sep;
	char			*tmp_free;

	if (fd < 0 || read(fd, buf, 0) || !line || !BUFF_SIZE || !(BUFF_SIZE + 1))
		return (-1);
	sep = process_memorized(*memorized, line);
	while (!sep && (count = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[count] = '\0';
		if ((sep = ft_strchr(buf, '\n')))
		{
			*sep = '\0';
			tmp_free = *memorized;
			*memorized = ft_strdup(++sep);
			ft_strdel(&tmp_free);
		}
		tmp_free = *line;
		*line = ft_strjoin(*line, buf);
		ft_strdel(&tmp_free);
		if (!*line || count < 0)
			break ;
	}
	return (get_status(count, *line, *memorized, sep));
}

int		get_next_line(int fd, char **line)
{
	static t_line	*head;
	t_line			*tmp;
	int				count;

	count = 0;
	if (!head)
		head = new_fd_list(fd);
	tmp = head;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = new_fd_list(fd);
		tmp = tmp->next;
	}
	return (process_line(tmp->fd, line, &tmp->memorized, count));
}
