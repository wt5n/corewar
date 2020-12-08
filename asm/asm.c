#include "asm.h"
#include <stdio.h>

void        zap_struct_ascii(t_chempion *ch, char *str, int flag)
{
    if (flag == 1)
        ch->name = ft_strdup(str);
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

    ch->name = NULL; //?????????
    if (line[0] == '.')
    {
        tecyhee = kol_sim(line, ' ') + 1;
        srez = cut_one(line, ' ', 0);
        if (ft_strcmp(srez, NAME_CMD_STRING) == 0)
        {
            free(srez);
            n_line = kol_sim_not(&(line[tecyhee]), ' ');
            tecyhee = tecyhee + n_line;
            n_line = kol_sim(&line[tecyhee + 1], '"');
            line[tecyhee + n_line + 1] = '\0';
            srez = ft_strdup(&line[tecyhee + 1]);
            zap_struct_ascii(ch, srez, 1);
        }
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
    close(fd);
    return (0);
}