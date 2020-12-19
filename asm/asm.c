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
    add_op_struct(op);
    if (ft_strcmp("sti", srez) == 0)
        (*op)->name = 10;
    else if (ft_strcmp("live", srez) == 0)
        (*op)->name = 0;
    else if (ft_strcmp("ld", srez) == 0)
        (*op)->name = 1;
    else if (ft_strcmp("st", srez) == 0)
        (*op)->name = 2;
    else if (ft_strcmp("add", srez) == 0)
        (*op)->name = 3;
    else if (ft_strcmp("sub", srez) == 0)
        (*op)->name = 4;
    else if (ft_strcmp("and", srez) == 0)
        (*op)->name = 5;
    else if (ft_strcmp("or", srez) == 0)
        (*op)->name = 6;
    else if (ft_strcmp("xor", srez) == 0)
        (*op)->name = 7;
    else if (ft_strcmp("zjmp", srez) == 0)
        (*op)->name = 8;
    else if (ft_strcmp("ldi", srez) == 0)
        (*op)->name = 9;
    else if (ft_strcmp("fork", srez) == 0)
        (*op)->name = 11;
    else if (ft_strcmp("lld", srez) == 0)
        (*op)->name = 12;
    else if (ft_strcmp("lldi", srez) == 0)
        (*op)->name = 13;
    else if (ft_strcmp("lfork", srez) == 0)
        (*op)->name = 14;
    else if (ft_strcmp("aff", srez) == 0)
        (*op)->name = 15;
    else
        return (-1);
    return (1);
}

/*void        label_size(t_new_st_label **label, int kol, t_chempion *ch)
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
}*/


int         analiz_registr(char *srez, t_op_strukt **op)
{
    int     k;

    if (srez[0] == 'r')
    {
        if ((k = ft_atoi(&srez[1])) > 0 && k < REG_NUMBER)
            (*op)->size += 1;
        else
            return (-1);
    }
    else if (srez[0] == '%')
    {
        if ((k = ft_atoi(&srez[1])) > 0)
            (*op)->size += k;
    }
    //if (srez[0] == DIRECT_CHAR && srez[1] == ':' || ft_atoi(&srez[1]) > 0)
    //     label_size(label, 1, ch);
    return (1);
}

int         pars_register(char *str, t_chempion *ch, t_op_strukt **op)//t_new_st_label **label, 
{
    int     tecyhee;
    char    *srez;
    int     n;

    n = 0;
    while (n >= 0)
    {if ((tecyhee = kol_sim_not(str, ' ')) < 0)
        {
            (*op)->name = 33;
            ch->flag = 90;
            return (-1);
        }
    n = kol_sim(&str[tecyhee], SEPARATOR_CHAR);
    if (n >= 0)
    {
        srez = cut_one(&str[tecyhee], SEPARATOR_CHAR, 0);
        tecyhee += (n + 1);
        str = str + tecyhee;
    }else
        srez = cut_one(&str[tecyhee], '\0', 0);
        if (analiz_registr(srez, op) < 0)
            return (-1);
        printf("%s\n", srez);
    } 
    return (1);
}

void            zap_label(t_new_st_label  **label, t_op_strukt **op)
{
    t_label     *lab;

    lab = (*label)->lab;
    while (lab)
    {
        lab->op = &(**op);
        lab = lab->next;
    }
}

int         pars_operation(char *line, t_chempion *ch, t_op_strukt **op, t_new_st_label  **label)
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
    if (ch->flag_label == 1)
        zap_label(label, op);
    free(srez);
    pars_register(&line[tecyhee], ch, op); //, label);
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
            if (pars_operation(line, ch, op, label) < 0)
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
    zap_registr(ch);
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
    print_op(op);
    close(fd);
    return (0);
}