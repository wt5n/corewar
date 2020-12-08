#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "op.h"

typedef struct	s_chempion
{
	char		*name;
	char		*comment;
	char		*code;
}				t_chempion;

int         kol_sim(char *str, char c);
int         kol_sim_not(char *str, char c);

#endif