#include "asm.h"
#include <stdio.h>

int         proverca(char *str)
{
    int     i;
    int     k;
    char    *label_char;

    i = 0;
    label_char = LABEL_CHARS;
    while (str[i] != '\0')
    {
        k = 0;
        while (label_char[k] != '\0' && label_char[k] != str[i])
            k++;
        if (label_char[k] == '\0')
            return (-1);
        i++;
    }
    return (1);
}

void        zap_struct_ascii(t_chempion *ch, char *str, t_label **label)
{
    if (ch->flag == 1 && ft_strlen(str) <= PROG_NAME_LENGTH)
        ch->name = ft_strdup(str);
    else if (ch->flag == 2 && ft_strlen(str) <= COMMENT_LENGTH)
        ch->comment = ft_strdup(str);
    else if (ch->flag == 3 && proverca(str) > 0)
        add_label(str, label);
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

int         pars_one(char *line, t_chempion *ch, t_label **label)
{
    if (line && line[0] != ' ' && line[0] != '\0' && line[0] != '\t' && line[0] != '\n')
    {
        if (line[0] == '.')
        {
            if ((pars_name(line, ch, label)) < 0)
                return (-1);
        }
        else 
            if ((pars_label(line, ch, label)) < 0)
                return (-1);
    }
    return (1);
}

int       read_line(int fd, t_chempion *ch, t_label **label)
{
    char    *line;

    while (get_next_line(fd, &line) > 0)
	{
        if (pars_one(line, ch, label) < 0)
            {
                free(line);
                return (-1);
            }
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

void			init_asm(t_chempion *ch, t_label **label)
{
	ch->name = NULL;
	ch->comment = NULL;
	ch->code = NULL;
    *label = NULL;
    //(*label)->name = NULL;
}

int				main(int argc, char *argv[])
{
    int			fd;
	t_chempion	ch;
    t_label     *label;

    if (argc == 2)
    {
		if (file_argv(argv[1]) < 0 || (fd = open(argv[1], O_RDONLY)) < 0)
            {
                return (-1);
            }
		init_asm(&ch, &label);
        if (read_line(fd, &ch, &label) < -1)
            return (-1);
	}
    else
    {
        return (-1);
    }
    printf("%s\n", ch.name);
    printf("%s\n", ch.comment);
    print_struct(label);
    close(fd);
    return (0);
}