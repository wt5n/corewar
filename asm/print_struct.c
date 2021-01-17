#include "asm.h"
#include <stdio.h>

void            print_op(t_op_strukt *op)
{
    t_op_strukt *new_op;
    int kol;

    new_op = op;
    kol = 0;
    //printf("name = %d\n", new_op->name);
    while (new_op != NULL)
    {
        printf("%d   size = %d\n", new_op->name, new_op->size);
        kol += new_op->size;
        new_op = new_op->next;
    }
    printf("kol_size = %d\n", kol);
}

void        print_struct(t_new_st_label *label)
{
    t_new_st_label  *new_label;
    t_label         *la;

    new_label = label;
    //printf("%s\n", new_label->lab->name);
    while(new_label)
    {
        la = new_label->lab;
        while (la)
        {
        printf("%s   size = %d   smechenee = %d \n", la->name, la->op->size, la->op->smechenee);
        la = la->next;
        }
        new_label = new_label->next;
    }
}