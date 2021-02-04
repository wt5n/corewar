#include "inc/vm.h"

void	read_magic_number(char *argv, int fd, t_cw *cw)
{
	int buf;
	int check;
	fd = open(argv, O_RDONLY);
	check = read(fd, &buf, MAGIC_NUMBER_LENGTH);
	check < MAGIC_NUMBER_LENGTH ? output_error(10, cw) : 0;
	if (buf != -209458688)
		output_error(1, cw);
}

void	read_champ_name(int fd, t_champ *champ, t_cw *cw)
{
	char	buf[PROG_NAME_LENGTH];
	int		tmp;
	int		check;

	check = read(fd, &tmp, 4);
	check < 4 ? output_error(10, cw) : 0;
	if (tmp > 0)
		output_error(3, cw);
	check = read(fd, buf, PROG_NAME_LENGTH);
	check < PROG_NAME_LENGTH ? output_error(10, cw) : 0;
	champ->name = ft_strndup(buf, ft_strlen(buf));
}

void	read_champ_code_size(int fd, t_champ *champ, t_cw *cw)
{
	int tmp;
	unsigned char size[4];
	int		check;

	check = read(fd, &tmp, 4);
	check < 4 ? output_error(10, cw) : 0;
	if (tmp != 0)
		output_error(3, cw);
	check = read(fd, &size, 4);
	check < 4 ? output_error(10, cw) : 0;
	champ->code_size = ft_bin_to_dec(size, 4);
	champ->code_size == 0 ? output_error(10, cw) : 0;
	if (champ->code_size < 0 || champ->code_size > CHAMP_MAX_SIZE + 1)
		output_error(4, cw);
}

void	read_champ_comm(int fd, t_champ *champ, t_cw *cw)
{
	char comm[2048];
	int		check;

	check = read(fd, comm, 2048);
	check < COMMENT_LENGTH ? output_error(10, cw) : 0;
	champ->comm = ft_strndup(comm, ft_strlen(comm));
}

void	read_champ_code(int fd, t_champ *champ, t_cw *cw)
{
	char	tmp[4];
	unsigned char *size;
	int check;

	check = read(fd, &tmp, 4);
	check < 4 ? output_error(10, cw) : 0;
	size = (unsigned char*)ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE + 1);
	check = read(fd, size, champ->code_size);
	check < champ->code_size ? output_error(10, cw) : 0;
	champ->code = size;
	check = read(fd, size, 1);
	check == 1 ? output_error(10, cw) : 0;
}