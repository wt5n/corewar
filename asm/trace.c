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

void        proverca_registr(char *srez, t_chempion *ch, int i)
{
    if (srez[0] == 'r')
    {
        
    }
}

int         op_reg(char *str1, t_chempion *ch, int i)
{ 
    int     n;
    char    type;
    int     tecyhee;
    char    *srez;
    char    *str;

    n = 0;
    str = str1;
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
    proverca_registr(srez, ch, i);
    //printf("!!! - %d\n", type);
    } 
    return (type);
}

void    pars_stroca(t_chempion *ch, t_new_st_label *label, t_op_strukt *op, char *str)
{
    int i;
    t_op_strukt *new_op;

    i = 0;
    new_op = op;
    printf("%s smehenee = %d\n", str, ch->smehenee);
    ch->code = (char*)malloc(sizeof(char) * ch->smehenee);
    while (i < ch->smehenee)
    {
        //printf("%s %d\n", str, ch->smehenee);
        ch->code[i] = (char)new_op->name + 1;
        i++;
        //printf("code[0] = %d\n", ch->code[i]);
        //printf("op - %d type - %d\n", new_op->name, op_tab[new_op->name].code_type);
        if (op_tab[new_op->name].code_type == 1)
            {
                //printf("******");
                ch->code[i] = op_reg(str, ch, i);
                printf("code[1] = %d\n", ch->code[i]);
                //printf("code = %d\n", ch->code[i+1]);
            }
        i++;
        new_op = new_op->next;
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