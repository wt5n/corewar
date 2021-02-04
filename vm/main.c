/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlikely <hlikely@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 20:03:34 by hlikely           #+#    #+#             */
/*   Updated: 2021/02/04 20:05:39 by hlikely          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/vm.h"

void	op_live(t_cw *cw, t_koretko *kor)
{
	int player;

	kor->step++;
	player = get_value(cw, kor, kor->args[0], 0);
	cw->num_of_lives++;
	kor->last_alive = cw->cycles;
	if (player <= -1 && player >= cw->num_of_champ * -1)
		cw->last_player = player;
}

void	parse_flags(int ac, char **av, t_cw *cw)
{
	int i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-d") || !ft_strcmp(av[i], "-dump"))
		{
			if (i + 1 >= ac)
				output_error(7, cw);
			if (av[i + 1])
			{
				cw->dump_cycle = ft_atoi(av[i + 1]);
				if (cw->dump_cycle < 0)
					output_error(8, cw);
				i++;
			}
		}
		else if (!ft_strcmp(av[i], "-v"))
			cw->vs = 1;
		else if (ft_strcmp(av[i], "-n") == 0 || has_cor(av[i]))
			i += parse_player(cw, ac, av, i);
		else
			print_usage();
	}
}

int		main(int argc, char **argv)
{
	int		i;
	t_cw	*cw;

	i = -1;
	if (argc < 2)
		print_usage();
	cw = (t_cw*)ft_memalloc(sizeof(t_cw));
	cw->dump_cycle = -1;
	while (++i < 4096)
		cw->map[i] = 0;
	parse_flags(argc, argv, cw);
	if (cw->num_of_champ == 0)
		output_error(5, cw);
	check_players_n(cw, argc, argv);
	check_players_wo_n(cw, argc, argv);
	cycle(cw);
	return (0);
}
