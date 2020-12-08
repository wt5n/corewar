#include "asm.h"

int         kol_sim_not(char *str, char c)
{
    int     i;

    i = 0;
    while (str[i] == c)
        i++;
    return (i);
}

int         kol_sim(char *str, char c)
{
    int     i;

    i = 0;
    while (str[i] != c)
        i++;
    return (i);
}

