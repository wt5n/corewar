#include "inc/vm.h"

void	read_magic_number(char *argv, int fd, t_cw *cw)
{
	int buf;

	fd = open(argv, O_RDONLY);
	read(fd, &buf, MAGIC_NUMBER_LENGTH);
	if (buf != -209458688)
		output_error(1, cw);
}

void	read_champ_name(int fd, t_champ *champ, t_cw *cw)
{
	char buf[PROG_NAME_LENGTH];
	int	 tmp;

	read(fd, &tmp, 4);
//	if (tmp != 0)
//		output_error(3, cw);
	read(fd, buf, PROG_NAME_LENGTH);
	champ->name = ft_strndup(buf, ft_strlen(buf));
}

void	read_champ_code_size(int fd, t_champ *champ, t_cw *cw)
{
	int tmp;
	unsigned char size[4];

	read(fd, &tmp, 4);
	if (tmp != 0)
		output_error(3, cw);
	read(fd, &size, 4);
	champ->code_size = ft_bin_to_dec(size, 4);
	if (champ->code_size < 0 || champ->code_size > CHAMP_MAX_SIZE + 1)
		output_error(4, cw);
}

void	read_champ_comm(int fd, t_champ *champ, t_cw *cw)
{
	char comm[2048];

	read(fd, comm, 2048);
	champ->comm = ft_strndup(comm, ft_strlen(comm));
}

void	read_champ_code(int fd, t_champ *champ, t_cw *cw)
{
	char	tmp[4];
	unsigned char *size;

	read(fd, &tmp, 4);
	size = (unsigned char*)ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE + 1);
	read(fd, size, champ->code_size);
	champ->code = size;
}