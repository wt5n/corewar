/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:41:35 by hlikely           #+#    #+#             */
/*   Updated: 2021/02/04 19:41:37 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/vm.h"

int		parse_player(t_cw *cw, int ac, char **av, int i)
{
	if (!ft_strcmp(av[i], "-n"))
	{
		if (i + 2 < ac && has_cor(av[i + 2]))
		{
			ft_atoi_only_dig(av[i + 1], cw);
			cw->num_of_champ++;
			return (2);
		}
		else
			output_error(6, cw);
	}
	cw->num_of_champ++;
	return (0);
}

void	read_champion(char *argv, t_champ *champ, t_cw *cw)
{
	int fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		output_error(9, cw);
	read_magic_number(argv, fd, cw);
	read_champ_name(fd, champ, cw);
	read_champ_code_size(fd, champ, cw);
	read_champ_comm(fd, champ, cw);
	read_champ_code(fd, champ, cw);
	close(fd);
}

void	create_champ(t_cw *cw, int id)
{
	cw->champs[id] = (t_champ*)ft_memalloc(sizeof(t_champ));
	cw->champs[id]->number = id + 1;
}

void	check_players_n(t_cw *cw, int ac, char **av)
{
	int	i;
	int	num;

	i = 0;
	while (++i < ac)
	{
		if (ft_strcmp(av[i], "-n") == 0)
		{
			num = ft_atoi_only_dig(av[i + 1], cw) - 1;
			if (num < 0 || num > (cw->num_of_champ - 1) ||
									cw->champs[num] != NULL)
				output_error(6, cw);
			create_champ(cw, num);
			read_champion(av[i + 2], cw->champs[num], cw);
		}
	}
}

void	check_players_wo_n(t_cw *cw, int ac, char **av)
{
	int	i;
	int num;

	i = 0;
	num = 0;
	while (++i < ac)
	{
		if (ft_strcmp(av[i], "-n") == 0)
			i += 2;
		else if (has_cor(av[i]))
		{
			while (cw->champs[num] != NULL)
				num++;
			create_champ(cw, num);
			read_champion(av[i], cw->champs[num], cw);
		}
	}
}
