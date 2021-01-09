#include "asm.h"

int         operation_name(char *srez, t_op_strukt **op)
{
    int     i;
    t_op_strukt *new_op;

    i = 0;
    while (op_tab[i].name != 0 && ft_strcmp(op_tab[i].name, srez) != 0)
        i++;
    if (op_tab[i].name == 0)
        return (-1);
    add_op_struct(op);
    new_op = *op;
    while (new_op->next)
        new_op = new_op->next;
    new_op->name = op_tab[i].code_op - 1;
    new_op->size += 1;
    if (op_tab[new_op->name].code_type == 1)
        new_op->size += 1;
    //printf("**** %d\n", (*op)->size);
    return (1);
}