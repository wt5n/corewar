#include "inc/vm.h"

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
		else if (!ft_strcmp(av[i], "-v30"))
			continue;
		else if (ft_strcmp(av[i], "-n") == 0 || has_cor(av[i]))
			i += parse_player(cw, ac, av, i);
		else
			print_usage();
	}
	if (cw->num_of_champ == 0)
		output_error(5, cw);
}

int		main(int argc, char **argv)
{
	int	i;

	if (argc < 2)
		print_usage();
	t_cw *cw;
	cw = (t_cw*)ft_memalloc(sizeof(t_cw));
	cw->dump_cycle = -1;
	i = -1;
	while (++i < 4096)
		cw->map[i] = 0;
	parse_flags(argc, argv, cw);
	check_players_n(cw, argc, argv);
	check_players_wo_n(cw, argc, argv);
	cycle(cw);
	return (0);
}