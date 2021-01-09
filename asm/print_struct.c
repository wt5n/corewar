#include "asm.h"
#include <stdio.h>

void            print_op(t_op_strukt *op)
{
    t_op_strukt *new_op;

    new_op = op;
    //printf("name = %d\n", new_op->name);
    while (new_op != NULL)
    {
        printf("%d   size = %d\n", new_op->name, new_op->size);
        new_op = new_op->next;
    }
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
        printf("%s\n", la->name);
        la = la->next;
        }
        new_label = new_label->next;
    }
}