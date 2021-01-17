#include "asm.h"

int         analiz_registr(char *srez, t_op_strukt **op)
{
    int     k;

    //printf("reg = %s\n", srez);
    if (srez[0] == 'r')
    {
        if ((k = ft_atoi(&srez[1])) > 0 && k < REG_NUMBER)
            {
                (*op)->size += T_REG;
                //printf("*\n");
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
    int     number;

    n = 0;
    //printf("stroc = %s\n", str);
    if ((number = kol_sim(str, '#')) != -1)
        str[number] = '\0';
    //printf("num = %d\n", number);
    (*op)->stroca = ft_strdup(str);
    //printf("op_str = %s\n", (*op)->stroca);
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
       // printf("%s - %d\n", srez, (*op)->size);
    } 
    return (1);
}

void            zap_label(t_new_st_label  **label, t_op_strukt *op)
{
    t_label     *lab;
    t_new_st_label  *new_label;

    new_label = *label;
    while (new_label->next)
        new_label = new_label->next;
    lab = new_label->lab;
    while (lab)
    {
        lab->op = op;
        lab = lab->next;
    }
}

int         pars_operation(char *line, t_chempion *ch, t_op_strukt **op, t_new_st_label  **label)
{
    int     tecyhee;
    char    *srez;
    t_op_strukt *new_op;
    t_new_st_label  *new_label;

    if (propysc_probel(line) == 3)
        return (3);
    //printf("stroca = %s\n", line);
    int propusc = propysc_probel(&line[0]);
    //printf("propusc = %d\n", propusc);
    int prob = number_pr(&line[propusc]);  
    //printf("probelov = %d\n", prob);  
    srez = cut_one(&line[propusc], line[propusc + prob], 0);
    //printf("srez1_operation = %s\n", srez);
    tecyhee = propusc + prob;
    //printf("ostalinoe = %s\n", &line[tecyhee + 1]);
    if (operation_name(srez, op) < 0)
        {
            free(srez);
            return (-1);
        }
    if (ch->flag_label == 1)
        zap_label(label, operation_last(op));
    free(srez);
    new_op = operation_last(op);
    new_label = label_last(label);
    pars_register(&line[tecyhee + 1], &new_op); //, label);
    new_op->smechenee = ch->smehenee;
    ch->smehenee += new_op->size;
    new_label->smehenee = ch->smehenee;
    return (1);
}