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

void	nums_of_champs(t_cw *cw, int ac, char **av)
{
	int num;
	int i;

	i = -1;
	num = 1;
	while (++i < ac - 1)
	{
//		if (ft_strcmp(av[i], "-n"))
//		{
//
//		}
		cw->champs[i]->number = num;
		num++;
	}
}

void	create_champ(t_cw *cw, int id)
{
	cw->champs[id] = (t_champ*)ft_memalloc(sizeof(t_champ));
	cw->champs[id]->name = (char*)ft_memalloc(sizeof(char) * 1);
	cw->champs[id]->comm = (char*)ft_memalloc(sizeof(char) * 1);
	cw->champs[id]->code = (unsigned char*)ft_memalloc(sizeof(unsigned char) * 1);
}

int	main(int argc, char **argv)
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
	nums_of_champs(cw, argc, argv);
	cycle(cw);
	return (0);
}