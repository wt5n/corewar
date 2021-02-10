#include "asm.h"

void    free_op_struct(t_op_strukt *op)
{
    t_op_strukt *op2;

    while (op)
    {
       op2 = op;
       op = op->next;
       free(op2->stroca);
       free(op2);
    }
    free(op);
}

void    free_lab(t_new_st_label **label)
{
    t_new_st_label **label2;
    t_label         *lab;
    t_label         *lab2;

    while (*label)
    {
        label2 = label;
        lab = (*label2)->lab;
        while (lab)
        {
            lab2 = lab;
            lab = lab->next;
            free(lab2->name);
            free(lab2);
        }
        free(lab);
        label = &((*label)->next);
        free(*label2);
    }
}