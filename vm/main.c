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
	printf("%s\n", vv3);
}

void 	read_champ_name(int fd, t_champ *champ)
{
	char buf[PROG_NAME_LENGTH];
	char tmp[4];

	read(fd, &tmp, 4);
	read(fd, buf, PROG_NAME_LENGTH);
	champ->name = ft_strndup(buf, ft_strlen(buf));
	printf("%s\n", buf);
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
	printf("%s\n", str);
}

void	read_champ_comm(int fd, t_champ *champ)
{
	char comm[2048];

	read(fd, comm, 2048);
	champ->comm = comm;
	printf("%s\n", comm);
}

void	read_champ_code(int fd, t_champ *champ) {
	char tmp[4];
	char *str;
	char	*code;
	int	i;
	int j;
	int x;

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

void	ultimate()
{
	int fd;
	int i = 0, j = 0, k = 0, l = 0, c = 0;
	char buf[2];
	int *size1 = (unsigned int *)malloc(sizeof(unsigned int) * 4);
	char *p_name = (char *)ft_memalloc(sizeof(char) * 129);
	char *p_comment = (char *)ft_memalloc(sizeof(char) * 2049);
	p_name[128] = '\0';
	p_comment[2048] = '\0';
	int p_code[22];

	fd = open("batman.cor", O_RDONLY);
	while (read(fd, buf, 1) > 0)
	{
		if (i >= 4 && i <= 132)
			p_name[j++] = buf[0];
		if (i >= 136 && i <= 139)
			size1[l++] = (unsigned int)buf[0];
		if (i >= 140 && i <= 2186)
			p_comment[k++] = (unsigned char)buf[0];
		if (i >= 2192 && i <= (2874))
			p_code[c++] = (char)(buf[0]);
		i++;
	}
	printf("%s\n", p_name);
	printf("%s\n", p_comment);
	for (int o = 0; o < 4; o++) {
		printf("%d ",size1[o]);
	}
	printf("\n");
	for (int o = 0; o < 22; o++) {
		printf("%x", p_code[o]);
	}
}

void	fill_map(t_cw *cw)
{
	int	i;
	int	j;
	int	shift;
	int	start;

	i = -1;
	shift = 4096 / cw->num_of_champ;
	while (++i < cw->num_of_champ)
	{
		start = shift * i;
		j = -1;
		while (++j < CHAMP_MAX_SIZE)
		{
			cw->map[start + j] = cw->champs[i]->code[j];
		}
	}
}

int	main(int argc, char **argv)
{
	t_cw *cw;
	int	i = -1;
//	t_champ champ_one;

//	printf("%c %c %c %c %c %c\n", 0x90, 0x65, 0xe2, 0x42, 0xfc, 0x7f);
//	ultimate();
//	printf("%d\n", adv_ft_itoa(, 16, 'a');
//	exit(1);

//	int	tab[10] = {0, 23, 150, 255,
//					  12, 16,  21, 42};
//
//	ft_print_memory(tab, sizeof(tab));
//	exit(1);

	cw = (t_cw*)ft_memalloc(sizeof(t_cw));
	cw->champs = (t_champ**)ft_memalloc(sizeof(t_champ*) * MAX_PLAYERS);
	cw->champs[0] = (t_champ*)ft_memalloc(sizeof(t_champ));
	cw->map = (unsigned char*)ft_memalloc(sizeof(char) * 4097);
	while (++i < 4096)
		cw->map[i] = 0;
	cw->map[4096] = '\0';

	argv[1] = "batman.cor";

	read_champion(argv[1], cw->champs[0], cw);
	fill_map(cw);
	ft_print_memory(cw->map, 4096);
	return (0);
}