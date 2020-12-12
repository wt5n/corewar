#include "asm.h"

void        zap_struct_ascii(t_chempion *ch, char *str, t_label **label)
{
    if (ch->flag == 1 && ft_strlen(str) <= PROG_NAME_LENGTH)
        ch->name = ft_strdup(str);
    else if (ch->flag == 2 && ft_strlen(str) <= COMMENT_LENGTH)
        ch->comment = ft_strdup(str);
    else if (ch->flag == 3 && proverca_label(str) > 0)
        add_label(str, label);
}

int         operation_name(char *srez, t_chempion *ch)
{
    if (ft_strcmp("sti", srez) == 0)
          ch->op_name = 11;
    else
        return (-1);
    return (1);
}

void        label_size(t_label **label, int kol, t_chempion *ch)
{
    t_label *n_label;
    int     i;

    n_label = *label;
    i = 0;
    while (n_label && i < ch->flag_label)
    {
        n_label->size += kol;
        n_label = n_label->next;
        i++;
    }
}


int         analiz_register(char *srez, t_label **label, t_chempion *ch)
{
    int     k;

    if (srez[0] == 'r')
    {
        if ((k = ft_atoi(&srez[1])) > 0 && k < REG_NUMBER)
            label_size(label, 1, ch);
        else
            return (-1);
    }
    if (srez[0] == DIRECT_CHAR && srez[1] == ':' || ft_atoi(&srez[1]) > 0)
         label_size(label, 1, ch);
    return (1);
}

int         pars_register(char *str, t_chempion *ch, t_label **label)
{
    int     tecyhee;
    char    *srez;
    int     n;

    n = 0;
    while (n >= 0)
    {if ((tecyhee = kol_sim_not(str, ' ')) < 0)
        return (-1);
    n = kol_sim(&str[tecyhee], SEPARATOR_CHAR);
    if (n >= 0)
    {
        srez = cut_one(&str[tecyhee], SEPARATOR_CHAR, 0);
        tecyhee += (n + 1);
        str = str + tecyhee;
    }else
        srez = cut_one(&str[tecyhee], '\0', 0);
    if (analiz_register(srez, label, ch) < 0)
        {
            free(srez);
            return (-1);
        }
        free(srez);
    } 
    return (1);
}

int         pars_operation(char *line, t_chempion *ch, t_label **label)
{
    int     tecyhee;
    char    *srez;

    tecyhee = kol_sim_not(line, ' ');
    if (tecyhee == -1)
        return (-1);
    srez = cut_one(&line[tecyhee], ' ', 0);
    tecyhee += (ft_strlen(srez) + 1);
    if (operation_name(srez, ch) < 0)
        {
            free(srez);
            return (-1);
        }
    free(srez);
    pars_register(&line[tecyhee], ch, label);

    return (1);
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
    else if (ch->flag_label == 1)
        {
            if (pars_operation(line, ch, label) < 0)
                return (-1);
        }
        else if (ft_strlen(line) != 0)
            return (-1);
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
    ch->flag_label = 0;
    *label = NULL;
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