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
	int			flag;
}				t_chempion;

typedef struct		s_label
{
	char			*name;
	int				size;
	struct s_label	*next;
}					t_label;

int         kol_sim(char *str, char c);
int         kol_sim_not(char *str, char c);
t_label     *add_label(char *str, t_label **label);
void        print_struct(t_label *label); //del
int         pars_name(char *line, t_chempion *ch, t_label **label);
int         pars_label(char *line, t_chempion *ch, t_label **label);

#endif