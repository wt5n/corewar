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

int         pars_one(char *line, t_chempion *ch, t_new_st_label **label, t_op_strukt **op)
{
    if (line && line[0] != ' ' && line[0] != '\0' && line[0] != '\t' && line[0] != '\n')
    {
        if (line[0] == '.')
        {
            if (ch->name == NULL && (pars_name(line, ch, label)) < 0)
                return (-1);
            else
               pars_name(line, ch, label);
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

void			init_asm(t_chempion *ch, t_new_st_label **label, t_op_strukt **op)
{
	ch->name = NULL;
	ch->comment = NULL;
	ch->code = NULL;
    ch->flag_label = 0;
    ch->smehenee = 0;
    (*op) = NULL;
    (*label)->lab = NULL;
    (*label)->next = NULL;
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
		init_asm(&ch, &label, &op);
        if (read_line(fd, &ch, &label, &op) < -1)
            return (-1);
	}
    else
    {
        return (-1);
    }
    trace_byte_code(&ch, label, op);
    //printf("%s\n", ch.name);
    //printf("%s\n", ch.comment);
    //print_struct(label);
    //print_op(op);
    close(fd);
    return (0);
}