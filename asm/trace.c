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

int         ft_abs(int a)
{
    if (a < 0)
        return (-a);
    return (a); 
}

int                 proverca_instruction(char *str, t_chempion *ch, t_new_st_label *label)
{
    t_new_st_label  *label2;
    t_label         *lab;

    //printf("!!!!");
    label2 = label;
    //printf("%s\n", str); //del
    while (label2)
    {
        
        lab = label2->lab;
        while (lab)
        {
            //printf("&&&   %s    %s\n", lab->name, str);
            if ((ft_strcmp(lab->name, str)) == 0)
            {
                //printf("in = %d\n", (lab->op->smechenee - ch->mestnoe_smehenee));
                //flag = 1;
                return (lab->op->smechenee - ch->mestnoe_smehenee);
            }
        lab = lab->next;
        }
        label2 = label2->next;
    }
    ch->flag = -1;
    return (-1);
}

int        proverca_registr(char *srez, t_chempion *ch, int *i, t_new_st_label *label, t_op_strukt *new_op)
{
    char    *srez2;
    int     k;
    int     tmp;
    short tmp2;

    //printf("@@@ - %s\n", srez);
    //printf("@@@ - %d\n", new_op->name);
    //printf("@@@ - %s\n", label->lab->name);
    if (srez[0] == 'r')
        {
            if ((tmp = ft_atoi(&srez[1])) <= 255)
            {
                ch->code[*i] = tmp;
            }
        }
    else if (srez[0] == DIRECT_CHAR)
            {
                if (srez[1] == LABEL_CHAR)
                {
                   srez2 = ft_strdup(&srez[2]);
                    //printf("mmm - %s\n", srez2);
                    ch->flag = 0;
                    //printf("RRRRRR");
                    //k = proverca_instruction(srez2, ch, label);
                    //printf("ch->mestnoe = %d   ch->size = %d   k == %d\n", ch->mestnoe_smehenee, ch->mestnoe_size, k);
                    if ((k = proverca_instruction(srez2, ch, label)) > 0 && ch->flag != -1)
                        {
                            //printf("&&& new_op->name %d", op_tab[new_op->name].size);
                            //printf("k = %d\n", k);
                            /*if (op_tab[new_op->name].size == 0) 
                           {
                               //printf("&&&");
                                k = 65535 + k + 1;
                               // printf("k = %d\n", k);
                                ch->code[*i] = (char)k >> 8;
                               // printf("code1 = %d\n", ch->code[i]);
                                i++;
                                ch->code[*i] = (char)k & 255;
                               // printf("code2 = %d\n", ch->code[i]);
                           }
                           else*/ if (op_tab[new_op->name].size == 1) //??????
                           {
                               //printf("&&&");
                               tmp2 = k;
                                ch->code[*i] = k >> 8; 
                               printf("         code[%d] = %d\n", *i, ch->code[*i]);
                                (*i)++;
                                ch->code[*i] = k & 255;  
                               // printf("code2 = %d\n", ch->code[i]);
                           } 
                        }
                    if (ch->flag == -1)
                        return (-1);
                    free(srez2); //??????????
                }
                else
                {
                    if  ((k = ft_atoi(&srez[1])) >= 0)
                    {
                        if (op_tab[new_op->name].size == 1)
                        {
                            tmp2 = k;
                            ch->code[*i] = k >> 8; 
                            printf("         code[%d] = %d\n", *i, ch->code[*i]);
                            (*i)++;
                            ch->code[*i] = k & 255; 
                        }
                        else
                        {
                            tmp2 = k << 16;
                            ch->code[*i] = k >> 8; 
                            printf("         code[%d] = %d\n", *i, ch->code[*i]);
                            (*i)++;
                            ch->code[*i] = k & 255;
                            printf("         code[%d] = %d\n", *i, ch->code[*i]);
                            (*i)++;
                            tmp2 = k;
                            ch->code[*i] = k >> 8;
                            printf("         code[%d] = %d\n", *i, ch->code[*i]);
                            (*i)++;
                            ch->code[*i] = k & 255;
                        }
                        
                    }
                }
            }     
    return (1);
}

int         op_reg(char *str1, t_chempion *ch, t_new_st_label *label, t_op_strukt *new_op, int *tu)
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
    if ((proverca_registr(srez, ch, tu, label, new_op)) < 0)
        return (-1);
    printf("         code[%d] = %d\n", *tu, ch->code[*tu]);
    (*tu)++;
    } 
    type = type << 2;
    return (type);
}

void    pars_stroca(t_chempion *ch, t_op_strukt *op, t_op_strukt *last_op, int *i, t_new_st_label *label)
{
    t_op_strukt *new_op; //del
    char *str;
    //int nenugno;
    int tu;

    new_op = op; //del
    tu = 0;
    str = last_op->stroca;
    //printf("%s smehenee = %d\n", str, last_op->smechenee);
    ch->mestnoe_smehenee = last_op->smechenee;
    ch->mestnoe_size = last_op->size;
   
    if (*i <= ch->mestnoe_smehenee)
    {
       // printf("^^^^  %s %d\n", str, new_op->name);
        ch->code[*i] = last_op->name + 1;
        printf("         code[%d] = %d\n", *i, ch->code[*i]);
        (*i)++;
        //printf("op - %d type - %d\n", new_op->name, op_tab[new_op->name].code_type);
        if (op_tab[last_op->name].code_type == 1)
            { 
                //printf("!!!");
                tu = (*i) + 1;
                //printf("****** %d\n", tu);
                ch->code[*i] = op_reg(str, ch, label, last_op, &tu);
                printf("         code[%d] = %d\n", *i, ch->code[*i]);
                //printf("code = %d\n", ch->code[i+1]);
            }
        else
        {
            tu = (*i) + 1;
            op_reg(str, ch, label, last_op, &tu);
        }
        
            //printf("tu = %d", tu);
        //nenugno = op_reg(str, ch, st_i, label, new_op);
        //i++;
        //new_op = new_op->next;
       //??????????????????????????????
    }
(*i) = tu;
//printf("i = %d", *i);
}

void    trace_byte_code(t_chempion *ch, t_new_st_label *label, t_op_strukt *op)
{
    t_op_strukt *op_new;
    int         i;

    op_new = op;
    i = 0;
    ch->code = (char*)malloc(sizeof(char) * ch->smehenee);
    while (op_new)
    {
        printf("name %d:\n", op_new->name + 1);
        pars_stroca(ch, op, op_new, &i, label);
       // printf("i2 = %d", i);
        op_new = op_new->next;
    }
}