#include "asm.h"

// 1 - T_DIR
// 2 - T_REG
// 3 - T_IND
// 4 - T_DIR + T_IND 
// 5 - T_REG + T_IND
// 6 - vse
// 7 - T_REG + T_DIR

void    zap_registr(t_chempion *ch)
{
    ch->reg[0].code = 2;
    ch->reg[1].code = 1;
    ch->reg[2].code = 3;
    ch->reg[0].size = 1;
    ch->reg[1].size = 0;
    ch->reg[2].size = 2;
}

void    zap_operation4(t_chempion *ch)
{
    ch->op[12].name = "lld";
    ch->op[12].code = 13;
    ch->op[12].kol_argument = 2;
    ch->op[12].type_arg = 1;
    ch->op[12].registr = 42;
    ch->op[12].size = 4;
    ch->op[13].name = "lldi";
    ch->op[13].code = 14;
    ch->op[13].kol_argument = 3;
    ch->op[13].type_arg = 1;
    ch->op[13].registr = 672;
    ch->op[13].size = 2;
    ch->op[14].name = "lfork";
    ch->op[14].code = 15;
    ch->op[14].kol_argument = 1;
    ch->op[14].type_arg = 0;
    ch->op[14].registr = 1;
    ch->op[14].size = 2;
    ch->op[15].name = "aff";
    ch->op[15].code = 16;
    ch->op[15].kol_argument = 1;
    ch->op[15].type_arg = 1;
    ch->op[15].registr = 2;
    ch->op[15].size = 4;
}

void    zap_operation3(t_chempion *ch)
{
    ch->op[9].name = "ldi";
    ch->op[9].code = 10;
    ch->op[9].kol_argument = 3;
    ch->op[9].type_arg = 1;
    ch->op[9].registr = 672;
    ch->op[9].size = 2;
    ch->op[10].name = "sti";
    ch->op[10].code = 11;
    ch->op[10].kol_argument = 3;
    ch->op[10].type_arg = 1;
    ch->op[10].registr = 267;
    ch->op[10].size = 2;
    ch->op[11].name = "fork";
    ch->op[11].code = 12;
    ch->op[11].kol_argument = 1;
    ch->op[11].type_arg = 0;
    ch->op[11].registr = 1;
    ch->op[11].size = 2;
    zap_operation4(ch);
}


void    zap_operation2(t_chempion *ch)
{
    ch->op[6].name = "or";
    ch->op[6].code = 7;
    ch->op[6].kol_argument = 3;
    ch->op[6].type_arg = 1;
    ch->op[6].registr = 662;
    ch->op[6].size = 4;
    ch->op[7].name = "xor";
    ch->op[7].code = 8;
    ch->op[7].kol_argument = 3;
    ch->op[7].type_arg = 1;
    ch->op[7].registr = 662;
    ch->op[7].size = 4;
    ch->op[8].name = "zjmp";
    ch->op[8].code = 9;
    ch->op[8].kol_argument = 1;
    ch->op[8].type_arg = 0;
    ch->op[8].registr = 1;
    ch->op[8].size = 2;
    zap_operation3(ch);
}

void    zap_operation1(t_chempion *ch)
{
    ch->op[3].name = "add";
    ch->op[3].code = 4;
    ch->op[3].kol_argument = 3;
    ch->op[3].type_arg = 1;
    ch->op[3].registr = 222;
    ch->op[3].size = 4;
    ch->op[4].name = "sub";
    ch->op[4].code = 5;
    ch->op[4].kol_argument = 3;
    ch->op[4].type_arg = 1;
    ch->op[4].registr = 222;
    ch->op[4].size = 4;
    ch->op[5].name = "and";
    ch->op[5].code = 6;
    ch->op[5].kol_argument = 3;
    ch->op[5].type_arg = 1;
    ch->op[5].registr = 662;
    ch->op[5].size = 4;
    zap_operation2(ch);
}

void    zap_operation(t_chempion *ch)
{
    ch->op[0].name = "live";
    ch->op[0].code = 1;
    ch->op[0].kol_argument = 1;
    ch->op[0].type_arg = 0;
    ch->op[0].registr = 1;
    ch->op[0].size = 4;
    ch->op[1].name = "ld";
    ch->op[1].code = 2;
    ch->op[1].kol_argument = 2;
    ch->op[1].type_arg = 1;
    ch->op[1].registr = 42;
    ch->op[1].size = 4;
    ch->op[2].name = "st";
    ch->op[2].code = 3;
    ch->op[2].kol_argument = 2;
    ch->op[2].type_arg = 1;
    ch->op[2].registr = 25;
    ch->op[2].size = 4;
    zap_operation1(ch);
}