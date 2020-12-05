#include "inc/vm.h"

void	ft_print_memory(const void *addr, size_t size);

void  read_magic_number(char *argv, int fd)
{
	unsigned int buf;

	fd = open(argv, O_RDONLY);
	read(fd, &buf, MAGIC_NUMBER_LENGTH);
	char *vv = adv_ft_itoa(COREWAR_EXEC_MAGIC, 16, 'a');
	char *vv2 = adv_ft_itoa(buf, 16, 'a');

	// printf("%s\n", vv);
	// printf("%s\n", vv2);

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
	champ->code_size = ft_atoi(str);  ///// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	printf("%s\n", str);
}

void	read_champ_comm(int fd, t_champ *champ)
{
	char comm[2048];

	read(fd, comm, 2048);

	champ->comm = comm;
	printf("%s\n", comm);
}

void	read_champ_code(int fd, t_champ *champ)
{
	int code;
	char *str;
	int tmp;

	read(fd, &tmp, 4);
	read(fd, &code, champ->code_size);
//	printf("%d\n", code);
	str = adv_ft_itoa(code, 16, 'a');
//	printf("%s\n", str);
	str = ft_strrev(str);
	ft_swap_two_let(str);
//	champ->code = str;
	printf("%s\n", str);
}


void 	read_champion(char *argv, t_champ *champ)
{
	int fd;
//	char *buf[4];
	fd = open(argv, O_RDONLY);
	read_magic_number(argv, fd);
	read_champ_name(fd, champ);

	read_champ_code_size(fd, champ);
	read_champ_comm(fd, champ);
	read_champ_code(fd, champ);

}


int	main(int argc, char **argv)
{
	t_cw *cw;
//	t_champ champ_one;

//	printf("%c %c %c %c %c %c\n", 0x90, 0x65, 0xe2, 0x42, 0xfc, 0x7f);


	cw = (t_cw*)ft_memalloc(sizeof(t_cw));
	cw->champs = (t_champ**)ft_memalloc(sizeof(t_champ*) * 4);
	cw->champs[0] = (t_champ*)ft_memalloc(sizeof(t_champ));

	argv[1] = "batman.cor";

	read_champion(argv[1], cw->champs[0]);
	return (0);
}