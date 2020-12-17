#include "asm.h"

void        zap_struct_ascii(t_chempion *ch, char *str, t_new_st_label **label)
{
    if (ch->flag == 1 && ft_strlen(str) <= PROG_NAME_LENGTH)
        ch->name = ft_strdup(str);
    else if (ch->flag == 2 && ft_strlen(str) <= COMMENT_LENGTH)
        ch->comment = ft_strdup(str);
    else if (ch->flag == 3 && proverca_label(str) > 0)
        {
            if (ch->flag_label == 1)
                add_label(str, &((*label)->lab));
            else
                {
                    ch->flag_label = 1;
                    add_st_label(str, label);
                }
        }
}

int         operation_name(char *srez, t_op_strukt **op)
{
    if (ft_strcmp("sti", srez) == 0)
        {
            add_op_struct(op);
            (*op)->name = 11;
        }
    else
        return (-1);
    return (1);
}

void        label_size(t_new_st_label **label, int kol, t_chempion *ch)
{
    t_new_st_label *n_label;
    int     i;

    kol = 0;
    n_label = *label;
    i = 0;
    while (n_label && i < ch->flag_label)
    {
        n_label = n_label->next;
        i++;
    }
}


/*int         analiz_register(char *srez, t_new_st_label **label, t_chempion *ch)
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

int         pars_register(char *str, t_chempion *ch, t_new_st_label **label)
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
}*/

int         pars_operation(char *line, t_chempion *ch, t_op_strukt **op)
{
    int     tecyhee;
    char    *srez;

    tecyhee = kol_sim_not(line, ' ');
    if (tecyhee == -1)
        return (2);
    srez = cut_one(&line[tecyhee], ' ', 0);
    tecyhee += (ft_strlen(srez) + 1);
    if (operation_name(srez, op) < 0)
        {
            free(srez);
            return (-1);
            ch->flag = 1; //del
        }
    free(srez);
    //pars_register(&line[tecyhee], ch, label);
    return (1);
}

int         pars_one(char *line, t_chempion *ch, t_new_st_label **label, t_op_strukt **op)
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
   else
        {
            if (pars_operation(line, ch, op) < 0)
                return (-1);
            ch->flag_label = 0;
            //label????
        }
    return (1);
}

int       read_line(int fd, t_chempion *ch, t_new_st_label **label, t_op_strukt **op)
{
    char    *line;

    while (get_next_line(fd, &line) > 0)
	{
        if (pars_one(line, ch, label, op) < 0)
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

void			init_asm(t_chempion *ch, t_new_st_label **label)
{
	ch->name = NULL;
	ch->comment = NULL;
	ch->code = NULL;
    ch->flag_label = 0;
    (*label)->lab = NULL;
    (*label)->next = NULL;
    zap_operation(ch);
}

int				    main(int argc, char *argv[])
{
    int			    fd;
	t_chempion	    ch;
    t_new_st_label  *label;
    t_op_strukt     *op;

    label = (t_new_st_label*)malloc(sizeof(t_new_st_label));
    if (argc == 2)
    {
		if (file_argv(argv[1]) < 0 || (fd = open(argv[1], O_RDONLY)) < 0)
            return (-1);
		init_asm(&ch, &label);
        if (read_line(fd, &ch, &label, &op) < -1)
            return (-1);
	}
    else
    {
        return (-1);
    }
    //printf("%s\n", ch.name);
    //printf("%s\n", ch.comment);
    //print_struct(label);
    close(fd);
    return (0);
}