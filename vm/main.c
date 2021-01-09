#include "inc/vm.h"

void  read_magic_number(char *argv, int fd)
{
	unsigned int buf;

	fd = open(argv, O_RDONLY);
	read(fd, &buf, MAGIC_NUMBER_LENGTH);
	char *vv = adv_ft_itoa(COREWAR_EXEC_MAGIC, 16, 'a');
	char *vv2 = adv_ft_itoa(buf, 16, 'a');
	vv2 = ft_strndup(vv2, 6);
	char *vv3 = ft_strrev(vv2);
	ft_swap_two_let(vv3);
//	printf("%s\n", vv3);
}

void 	read_champ_name(int fd, t_champ *champ)
{
	char buf[PROG_NAME_LENGTH];
	char tmp[4];

	read(fd, &tmp, 4);
	read(fd, buf, PROG_NAME_LENGTH);
	champ->name = ft_strndup(buf, ft_strlen(buf));
	printf("%s\n", champ->name);
}

void	read_champ_code_size(int fd, t_champ *champ)
{
	char tmp[4];
	int size;
	char *str;

	read(fd, &tmp, 4);
	read(fd, &size, 4);
	str = adv_ft_itoa(size, 16, 'a');
	str = ft_strrev(str);
	ft_swap_two_let(str);
	champ->code_size = ft_atoi_base(str, 16);
	printf("%d\n", champ->code_size);
}

void	read_champ_comm(int fd, t_champ *champ)
{
	char comm[2048];

	read(fd, comm, 2048);
	champ->comm = ft_strndup(comm, ft_strlen(comm));
	printf("%s\n", champ->comm);
}

void	read_champ_code(int fd, t_champ *champ) {
	char	tmp[4];
	char	*code;

	code = (char*)ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE + 1);
	code[CHAMP_MAX_SIZE] = '\0';
	read(fd, &tmp, 4);
	unsigned char *size;
	size = (unsigned char*)ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE + 1);
	read(fd, size, 22);
	champ->code = size;
}

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

	cw->champs = (t_champ**)ft_memalloc(sizeof(t_champ*) * MAX_PLAYERS);
	while (++i < argc)
		create_champ(cw, i);
	i = -1;

	cw->map = (unsigned char*)ft_memalloc(sizeof(char) * 4097);
	cw->kors = (t_koretko*)ft_memalloc(sizeof(t_koretko));
	while (++i < 4096)
		cw->map[i] = 0;
	cw->map[4096] = '\0';

	i = 0;
	while (++i < argc)
	{
		read_champion(argv[i], cw->champs[i - 1], cw);
	}
	nums_of_champs(cw, argc, argv);
	circle(cw);
//	for (int k = 0; k < 22; k++)
//	{
//		printf("%#x ", cw->champs[1]->code[k]);
//	}
//	printf("%d\n", (cw->champs[1]->code[1] & 192) >> 6);
//	printf("%d\n", (cw->champs[1]->code[1] & 48) >> 4);
//	printf("%d\n", (cw->champs[1]->code[1] & 12) >> 2);
//	printf("%c", cw->champs[1]->code[0]);
	return (0);
}