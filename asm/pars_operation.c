#include "asm.h"

int         analiz_registr(char *srez, t_op_strukt **op)
{
    int     k;

    if (srez[0] == 'r')
    {
        if ((k = ft_atoi(&srez[1])) > 0 && k < REG_NUMBER)
            {
                (*op)->size += T_REG;
                //printf("str - %s   size - %d\n", (*op)->stroca, (*op)->size);
            }
        else
            return (-1);
    }
    else if (srez[0] == '%')
    {
        if (op_tab[(*op)->name].size == 0)
            (*op)->size += T_DIR * 2;
        else
             (*op)->size += T_DIR;
    }
    else 
        (*op)->size += 2;
    //if (srez[0] == DIRECT_CHAR && srez[1] == ':' || ft_atoi(&srez[1]) > 0)
    //     label_size(label, 1, ch);
    return (1);
}

int         pars_register(char *str, t_op_strukt **op)//t_new_st_label **label, 
{
    int     tecyhee;
    char    *srez;
    int     n;

    n = 0;
    (*op)->stroca = ft_strdup(str);
    //printf("%s\n", (*op)->stroca);
    while (n >= 0)
    {if ((tecyhee = kol_sim_not(str, ' ')) < 0)
        {
            return (-1);
        }
    n = kol_sim(&str[tecyhee], SEPARATOR_CHAR);
    if (n >= 0)
    {
        srez = cut_one(&str[tecyhee], SEPARATOR_CHAR, 0);
        tecyhee += (n + 1);
        str = str + tecyhee;
    }else
        srez = cut_one(&str[tecyhee], '\0', 0);
    if (analiz_registr(srez, op) < 0)
        return (-1);
        //printf("%s - %d\n", srez, (*op)->size);
    } 
    return (1);
}

void            zap_label(t_new_st_label  **label, t_op_strukt **op)
{
    t_label     *lab;

    lab = (*label)->lab;
    while (lab)
    {
        lab->op = &(**op);
        lab = lab->next;
    }
}

int         pars_operation(char *line, t_chempion *ch, t_op_strukt **op, t_new_st_label  **label)
{
    int     tecyhee;
    char    *srez;

    tecyhee = kol_sim_not(line, ' ');
    if (tecyhee == -1)
        return (2);
    srez = cut_one(&line[tecyhee], ' ', 0);
    tecyhee += (ft_strlen(srez) + 1);
    if (operation_name(srez, op) < 0)
        {
            free(srez);
            return (-1);
        }
    if (ch->flag_label == 1)
        zap_label(label, op);
    free(srez);
    pars_register(&line[tecyhee], op); //, label);
    ch->smehenee += (*op)->size;
    (*label)->smehenee = ch->smehenee;
    return (1);
}