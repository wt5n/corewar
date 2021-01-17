#include "asm.h"

int make_file(char *name_file)
{
	int fd1;
	int i;
	char *new_name;

	if ((new_name = (char *)malloc(sizeof(char) * (ft_strlen(name_file) + 4))) < 0)
		return (-1);
	i = 0;
	while (i < (int)(ft_strlen(name_file) - 1))
	{
		new_name[i] = name_file[i];
		i++;
	}
	new_name[i++] = 'c';
	new_name[i++] = 'o';
	new_name[i++] = 'r';
	new_name[i++] = 'r'; //del
	new_name[i] = '\0';
	if ((fd1 = open(new_name, O_CREAT | O_WRONLY, 0644)) < 0)
	{
		free(new_name);
		return (-1);
	}
	return (fd1);
}

int write_code3(int fd1, t_chempion ch, char **nullu)
{
	int len_comment;
	char *comment;
	int i;

	i = 0;
	len_comment = ft_strlen(ch.comment);
	if ((comment = (char *)malloc(sizeof(char) * (COMMENT_LENGTH - len_comment))) < 0)
		return (-1);
	while (i < COMMENT_LENGTH - len_comment)
	{
		comment[i] = 0;
		i++;
	}
	write(fd1, comment, COMMENT_LENGTH - len_comment);
	(*nullu)[0] = 0;
	(*nullu)[1] = 0;
	(*nullu)[2] = 0;
	(*nullu)[3] = 0;
	write(fd1, *nullu, 4);
	write(fd1, ch.code, ch.smehenee);
	return (1);
}

int write_code2(int fd1, t_chempion ch)
{
	char *nullu;
	short m;
	int i;

	i = 0;
	if ((nullu = (char *)malloc(sizeof(char) * 4)) < 0)
		return (-1);
	nullu[0] = 0;
	nullu[1] = 0;
	nullu[2] = 0;
	nullu[3] = 0;
	write(fd1, nullu, 4);
	free(nullu);
	m = ch.smehenee >> 16;
	nullu[0] = m >> 8;
	nullu[1] = m & 255;
	m = ch.smehenee;
	nullu[2] = m >> 8;
	nullu[3] = m & 255;
	write(fd1, nullu, 4);
	write(fd1, ch.comment, ft_strlen(ch.comment));
	write_code3(fd1, ch, &nullu);
	return (1);
}

int write_code1(int fd1, t_chempion ch)
{
	char *name;
	int len_name;

	len_name = ft_strlen(ch.name);
	if ((name = (char *)malloc(sizeof(char) * (PROG_NAME_LENGTH - len_name))) < 0)
		return (-1);
	int i = 0;
	while (i < PROG_NAME_LENGTH - len_name)
	{
		name[i] = 0;
		i++;
	}
	write(fd1, name, PROG_NAME_LENGTH - len_name);
	free(name);
	write_code2(fd1, ch);
	return (1);
}

int write_code(char *name_file, t_chempion ch)
{
	int fd1;
	char *magic;
	short m;

	fd1 = make_file(name_file);
	magic = (char *)malloc(sizeof(char) * 4);
	magic[0] = COREWAR_EXEC_MAGIC >> 24;
	magic[1] = (char)((COREWAR_EXEC_MAGIC >> 16) & 255);
	m = (short)COREWAR_EXEC_MAGIC;
	magic[2] = m >> 8;
	magic[3] = m & 255;
	write(fd1, magic, 4);
	free(magic);
	ch.size += 4;
	ch.size += PROG_NAME_LENGTH;
	write(fd1, ch.name, ft_strlen(ch.name));
	write_code1(fd1, ch);
	close(fd1);
	return (1);
}