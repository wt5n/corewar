#include "inc/vm.h"

void	read_magic_number(char *argv, int fd)
{
	int buf;

	fd = open(argv, O_RDONLY);
	read(fd, &buf, MAGIC_NUMBER_LENGTH);
	if (buf != -209458688)
		output_error(1);
}

void	read_champ_name(int fd, t_champ *champ)
{
	char buf[PROG_NAME_LENGTH];
	char tmp[4];

	read(fd, &tmp, 4);
	read(fd, buf, PROG_NAME_LENGTH);
	champ->name = ft_strndup(buf, ft_strlen(buf));
//	ft_printf("%s\n", champ->name);
}

void	read_champ_code_size(int fd, t_champ *champ)
{
	int tmp;
	unsigned char size[4];

	read(fd, &tmp, 4);
	if (tmp != 0)
		output_error(3);
	read(fd, &size, 4);
	champ->code_size = ft_bin_to_dec(size, 4);
	if (champ->code_size < 0 || champ->code_size > CHAMP_MAX_SIZE + 1)
		output_error(4);
}

void	read_champ_comm(int fd, t_champ *champ)
{
	char comm[2048];

	read(fd, comm, 2048);
	champ->comm = ft_strndup(comm, ft_strlen(comm));
//	ft_printf("%s\n", champ->comm);
}

void	read_champ_code(int fd, t_champ *champ) {
	char	tmp[4];
	char	*code;
	unsigned char *size;

	code = (char*)ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE + 1);
	code[CHAMP_MAX_SIZE] = '\0';
	read(fd, &tmp, 4);
	size = (unsigned char*)ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE + 1);
	read(fd, size, champ->code_size);
	champ->code = size;
}