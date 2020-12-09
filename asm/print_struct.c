#include "asm.h"
#include <stdio.h>

void        print_struct(t_label *label)
{
    while(label)
    {
        printf("%s\n", label->name);
        label = label->next;
    }
}