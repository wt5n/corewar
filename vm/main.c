#include "inc/vm.h"

void 	read_champion(char *argv, t_champ *champ, t_cw *cw)
{
	int fd;
	fd = open(argv, O_RDONLY);
	read_magic_number(argv, fd);
	read_champ_name(fd, champ);
	read_champ_code_size(fd, champ);
	read_champ_comm(fd, champ);
	read_champ_code(fd, champ);
	cw->num_of_champ++;
}

void	create_champ(t_cw *cw, int id)
{
	cw->champs[id] = (t_champ*)ft_memalloc(sizeof(t_champ));
	cw->champs[id]->name = (char*)ft_memalloc(sizeof(char));
	cw->champs[id]->comm = (char*)ft_memalloc(sizeof(char));
	cw->champs[id]->code = (unsigned char*)ft_memalloc(sizeof(unsigned char));
}

int 	has_cor(char *str)
{
	int a;

	a = ft_strlen(str);
	if (a > 4)
	{
		if (ft_strcmp(ft_strsub(str, a - 4, 4), ".cor") == 0)
			return (1);
	}
	return (0);
}

void 	check_player(t_cw *cw, char **av, int i)
{
	int num;

	if (!ft_strcmp(av[i], "-n"))
	{
		if (av[i + 1] && av[i + 2] && has_cor(av[i + 2]))
		{
			num = ft_atoi(av[i + 1]);
//			if (num > 0 && num <= MAX_PLAYERS)
//			{
//
//			}
//			else
//				print_usage();
		}
	}
//	else
//		create_champ(cw, )
}

void	parse_flags(int ac, char **av, t_cw *cw)
{
	int i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp(av[i], "-d") || !ft_strcmp(av[i], "-dump"))
		{
			if (av[i + 1])
			{
				cw->dump_cycle = ft_atoi(av[i + 1]);
				i++;
			}
		}
		else if (!ft_strcmp(av[i], "-v"))
			cw->vs = 1;
		else if (ft_strcmp(av[i], "-n") == 0 || has_cor(av[i]))
			check_player(cw, av, i);
//		else
//			print_usage();
	}
}


int		main(int argc, char **argv)
{
	t_cw *cw;
	int	i = -1;
	cw = (t_cw*)ft_memalloc(sizeof(t_cw));
	while (++i < 2)
		create_champ(cw, i);
	i = -1;
	while (++i < 4096)
		cw->map[i] = 0;
	i = 0;
	while (++i < argc)
		read_champion(argv[i], cw->champs[i - 1], cw);
	cycle(cw);
	return (0);
}