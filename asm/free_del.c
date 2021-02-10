#include "asm.h"

void    free_op_struct(t_op_strukt *op)
{
    t_op_strukt *op_next;

    while (op)
    {
       op_next = op->next;
       free(op->stroca);
       free(op);
       op = op_next;
    }
    free(op);
}

void    free_lab(t_new_st_label *label)
{
    t_new_st_label *label_next;
    t_label         *lab;
    t_label         *lab_next;

    while (label)
    {
        lab = (t_label*)label->lab;
        label_next = label->next;
        free(label);
        while (lab)
        {
            lab_next = lab->next;
            free(lab->name);
           free(lab);
            lab = lab_next;
        }
        free(lab);
        label = label_next;
    }
    free(label);
}