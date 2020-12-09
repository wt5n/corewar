#include "asm.h"

int         kol_sim_not(char *str, char c)
{
    int     i;

    i = 0;
    while (str && str[i] == c)
        i++;
    return (i);
}

int         kol_sim(char *str, char c)
{
    int     i;

    i = 0;
    while (str && str[i] != '\0' && str[i] != c)
        i++;
    if (str[i] == '\0')
        return (-1);
    return (i);
}

