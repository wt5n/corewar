#include "asm.h"
#include <stdio.h>

void        print_struct(t_new_st_label *label)
{
    t_new_st_label  *new_label;
    t_label         *la;

    new_label = label;
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