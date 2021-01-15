#include "inc/vm.h"

void	read_magic_number(char *argv, int fd)
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

void	read_champ_name(int fd, t_champ *champ)
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