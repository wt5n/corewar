#include "asm.h"
#include <stdio.h>

void        zap_struct_ascii(t_chempion *ch, char *str)
{
    if (ch->flag == 1 && ft_strlen(str) <= PROG_NAME_LENGTH)
        ch->name = ft_strdup(str);
    else if (ch->flag == 2 && ft_strlen(str) <= COMMENT_LENGTH)
                ch->comment = ft_strdup(str);
}

char        *cut_one(char *str, char c, int n)
{
    char    *srez;
    int     n_line;

    n_line = kol_sim(&(str[n]), c);
    if (n_line != (int)ft_strlen(str))
        str[n_line] = '\0';
    srez = ft_strdup(&str[0]);
    return (srez);
}

int         pars_one(char *line, t_chempion *ch)
{
    char    *srez;
    int     n_line;
    int     tecyhee;

    if (line[0] == '.')
    {
        tecyhee = kol_sim(line, ' ') + 1;
        srez = cut_one(line, ' ', 0);
        if (ft_strcmp(srez, NAME_CMD_STRING) == 0 || ft_strcmp(srez, COMMENT_CMD_STRING) == 0)
        {
            if (ft_strcmp(srez, NAME_CMD_STRING) == 0)
                ch->flag = 1;
            else
                ch->flag = 2;
            free(srez);
            n_line = kol_sim_not(&(line[tecyhee]), ' ');
            tecyhee = tecyhee + n_line;
            if (line[tecyhee] != '"')
                return(-1);
            n_line = kol_sim(&line[tecyhee + 1], '"');
            line[tecyhee + n_line + 1] = '\0';
            srez = ft_strdup(&line[tecyhee + 1]);
            zap_struct_ascii(ch, srez);
            free(srez);
        }
        else
            return (-1);
    }
    
    return (1);
}

int       read_line(int fd, t_chempion *ch)
{
    char    *line;

    while (get_next_line(fd, &line) > 0)
	{
        if (pars_one(line, ch) < 0)
            return (-1);
        free(line);
    }
    return (1);
}

int         file_argv(char *str)
{
    if (str[ft_strlen(str) - 1] == 's' && str[ft_strlen(str) - 2] == '.')
        return (1);
    return (-1);
}

void			init_asm(t_chempion *ch)
{
	ch->name = NULL;
	ch->comment = NULL;
	ch->code = NULL;
}

int				main(int argc, char *argv[])
{
    int			fd;
	t_chempion	ch;

    if (argc == 2)
    {
		if (file_argv(argv[1]) < 0 || (fd = open(argv[1], O_RDONLY)) < 0)
            {
                return (-1);
            }
		init_asm(&ch);
        if (read_line(fd, &ch) < -1)
            return (-1);
	}
    else
    {
        return (-1);
    }
    printf("%s\n", ch.name);
    printf("%s\n", ch.comment);
    close(fd);
    return (0);
}