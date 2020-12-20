#include "asm.h"

int         operation_name(char *srez, t_op_strukt **op)
{
    int     i;

    i = 0;
    while (op_tab[i].name != 0 && ft_strcmp(op_tab[i].name, srez) != 0)
        i++;
    if (op_tab[i].name == 0)
        return (-1);
    add_op_struct(op);
    (*op)->name = op_tab[i].code_op - 1;
    (*op)->size += 1;
    if (op_tab[(*op)->name].code_type == 1)
        (*op)->size += 1;
    //printf("**** %d\n", (*op)->size);
    return (1);
}