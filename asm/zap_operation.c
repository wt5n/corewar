#include "asm.h"

void    zap_registr(t_chempion *ch)
{
    ch->reg[0].code = 2;
    ch->reg[1].code = 1;
    ch->reg[2].code = 3;
    ch->reg[0].size = 1;
    ch->reg[1].size = 0;
    ch->reg[2].size = 2;
}