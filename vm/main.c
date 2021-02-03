#include "inc/vm.h"

void 	read_champion(char *argv, t_champ *champ, t_cw *cw)
{
	int fd;
	fd = open(argv, O_RDONLY);
	read_magic_number(argv, fd, cw);
	read_champ_name(fd, champ, cw);
	read_champ_code_size(fd, champ, cw);
	read_champ_comm(fd, champ, cw);
	read_champ_code(fd, champ, cw);
	// cw->num_of_champ++;
	close(fd);
}

void	create_champ(t_cw *cw, int id)
{
	cw->champs[id] = (t_champ*)ft_memalloc(sizeof(t_champ));
	cw->champs[id]->number = id + 1;
	// cw->champs[id]->name = (char*)ft_memalloc(sizeof(char));
	// cw->champs[id]->comm = (char*)ft_memalloc(sizeof(char));
	// cw->champs[id]->code = (unsigned char*)ft_memalloc(sizeof(unsigned char));
}

int 	has_cor(char *str)
{
	int a;
	char *s;

	a = ft_strlen(str);
	if (a > 4)
	{
		s = ft_strsub(str, a - 4, 4);
		if (ft_strcmp(s, ".cor") == 0)
		{
			free(s);
			return (1);
		}
		free(s);
	}
	return (0);
}

int			ft_atoi_only_dig(const char *str, t_cw *cw)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v'
	|| *str == ' ' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
		output_error(6, cw);
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	while (*str)
	{
		if ((*str < '1') || (*str > '9'))
			output_error(6, cw);
		res = res * 10 + (*str - '0');
		if (res > MAX_PLAYERS)
			output_error(6, cw);
		str++;
	}
	return (int)(res);
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
			if (num < 0 || num > (cw->num_of_champ - 1) || cw->champs[num] != NULL)
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


int 	parse_player(t_cw *cw, int ac, char **av, int i)
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
		{
			cw->vs = 1;
		}
		else if (!ft_strcmp(av[i], "-v30"))
		{
			continue;
		}
		else if (ft_strcmp(av[i], "-n") == 0 || has_cor(av[i]))
			i += parse_player(cw, ac, av, i);
		else
		{
			print_usage();
		}
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