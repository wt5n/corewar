#include "asm.h"

int     proverca(char c)
{
    if (c == 'r')
        return (REG_CODE);
    else if (c == '%')
        return (DIR_CODE);
    else
        return (IND_CODE);
    return (-1);
}

int     op_reg(char *str)
{ 
    int n;
    int type;
    int tecyhee;
    char *srez;

    n = 0;
    type = 0;
    while (n >= 0)
    {
        if ((tecyhee = kol_sim_not(str, ' ')) < 0)
        {
            return (-1);
        }
    n = kol_sim(&str[tecyhee], SEPARATOR_CHAR);
    if (n >= 0)
    {
        srez = cut_one(&str[tecyhee], SEPARATOR_CHAR, 0);
        tecyhee += (n + 1);
        str = str + tecyhee;
    }
    else
        srez = cut_one(&str[tecyhee], '\0', 0);
    type = ((type << 2) + (proverca(srez[0])));
    } 
    return (type);
}

void    pars_stroca(t_chempion *ch, t_new_st_label *label, t_op_strukt *op, char *str)
{
    int i;

    i = 0;
    //printf("%s %d\n", str, ch->smehenee);
    ch->code = (char*)malloc(sizeof(char) * ch->smehenee);
    while (i < ch->smehenee)
    {
        ch->code[i] = op->name + 1;
        if (op_tab[op->name].code_type == 1)
            {
                printf("******");
                ch->code[i + 1] = op_reg(str);
                printf("code = %d\n", ch->code[i+1]);
            }
        i += 2;
       //??????????????????????????????
    }
    label->smehenee = 0; //del
}

void    trace_byte_code(t_chempion *ch, t_new_st_label *label, t_op_strukt *op)
{
    t_op_strukt *op_new;

    op_new = op;
    while (op_new)
    {
        pars_stroca(ch, label, op, op_new->stroca);
        op_new = op_new->next;
    }
    label->smehenee = 0; //del
}