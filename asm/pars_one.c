#include "asm.h"

int		pars_one(char *line, t_chempion *ch, t_new_st_label **label, \
		t_op_strukt **op)
{
	int i;
	int	k;

	i = 0;
	if (line && line[0] != ' ' && line[0] != '\0' && line[0] != '\t' && \
			line[0] != '\n')
	{
		if (line[0] == '.')
		{
			if (ch->name == NULL && (pars_name(line, ch, label)) < 0)
				return (-1);
			else
				pars_name(line, ch, label);
		}
		else
		{
			if ((pars_label(line, ch, label, &i)) < 0)
				return (-1);
			pars_one(&(line[i]), ch, label, op);
		}
	}
	else
	{
		k = 0;
        if ((k = pars_operation(line, ch, op, label)) < 0)
            return (-1);
        if (k != 0 && k != 3)
            ch->flag_label = 0;
    }
    return (1);
}