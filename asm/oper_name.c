#include "asm.h"

int         operation_name1(char *srez, t_op_strukt **op)
{
    if (ft_strcmp("xor", srez) == 0)
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

int         operation_name(char *srez, t_op_strukt **op, t_chempion *ch)
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
    else  
        if (operation_name1(srez, op) < 0)
            return (-1);
    (*op)->size += 1;
    if (ch->op[(*op)->name].type_arg == 1)
        (*op)->size += 1;
    return (1);
}