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
            {
                int i = 0;
                if ((pars_label(line, ch, label, &i)) < 0)
                return (-1);
                pars_one(&(line[i]), ch, label, op);
            }
    }
    else
        {
            int k = 0;
            if ((k =pars_operation(line, ch, op, label)) < 0)
                return (-1);
            if (k != 0 && k !=3)
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
    ch->size = 0;
    (*op) = NULL;
    (*label) = NULL;
    //(*label)->next = NULL;
    zap_registr(ch);
}

int				    main(int argc, char *argv[])
{
    int			    fd;
	t_chempion	    ch;
    t_new_st_label  *label;
    t_op_strukt     *op;

    //label = (t_new_st_label*)malloc(sizeof(t_new_st_label));
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
    close(fd);
    //int fd1 = creat("aF", 0644);
    //char c = 'a';
    int fd1 = open("aFile", O_CREAT | O_WRONLY, 0644);
    char *magic;
    magic = (char*)malloc(sizeof(char) * 4);
    short m;
    magic[0] = COREWAR_EXEC_MAGIC >> 24;
    magic[1] = (char)((COREWAR_EXEC_MAGIC >> 16) & 255);
    m = (short)COREWAR_EXEC_MAGIC;
    magic[2] = m >> 8;
    magic[3] = m & 255;
    write(fd1, magic, 4);
    free(magic);
    ch.size += 4;
    ch.size += PROG_NAME_LENGTH;
    int len_name = ft_strlen(ch.name);
    write(fd1, ch.name, len_name);
    char *name;
    name = (char*)malloc(sizeof(char) * (PROG_NAME_LENGTH-len_name));
    int i = 0;
    while (i < PROG_NAME_LENGTH-len_name)
    {
        name[i] = 0;
        i++;
    }
     write(fd1, name, PROG_NAME_LENGTH-len_name);
     free(name);
     char *nullu;
     nullu = (char*)malloc(sizeof(char) * 4);
     nullu[0] = 0;
     nullu[1] = 0;
     nullu[2] = 0;
     nullu[3] = 0;
     write(fd1, nullu, 4);

     //printf("sm = %d\n", ch.smehenee);
     nullu[0] = (char)ch.smehenee >> 24;
     nullu[1] = (char)((ch.smehenee >> 16) & 255);
     m = ch.smehenee;
     //printf("m = %d\n", m);
     nullu[2] = m >> 8;
     nullu[3] = m & 255;
     //printf("nullu0 = %d\n", nullu[0]);
     //printf("nullu1 = %d\n", nullu[1]);
     //printf("nullu2 = %d\n", nullu[2]);
     //printf("nullu3 = %d\n", nullu[3]);
    write(fd1, nullu, 4);
    //printf("nullu3 = %d\n", nullu[3]);
    int len_comment = ft_strlen(ch.comment);
     write(fd1, ch.comment, len_comment);
    char *comment;
    comment = (char*)malloc(sizeof(char) * (COMMENT_LENGTH-len_comment));
   i = 0;
     while (i < COMMENT_LENGTH-len_comment)
    {
        comment[i] = 0;
        i++;
    }
write(fd1, comment, COMMENT_LENGTH-len_comment);
nullu[0] = 0;
     nullu[1] = 0;
     nullu[2] = 0;
     nullu[3] = 0;
     write(fd1, nullu, 4);
    write(fd1, ch.code, ch.smehenee);

    //printf("%s\n", ch.name);
    //printf("%s\n", ch.comment);
    print_struct(label);
    print_op(op);
    close(fd1);
    return (0);
}