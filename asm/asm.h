#ifndef ASM_H
# define ASM_H

#include <stdio.h> //del

# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "op.h"





typedef struct		s_operation
{
	
	
	
}					t_operation;

typedef struct			s_chempion
{
	char				*name;
	char				*comment;
	char				*code;
	int					flag;
	int					flag_label;
	t_operation			op[16];
}						t_chempion;

typedef struct		s_label
{
	char			*name;
	t_operation		*op;
	struct s_label	*next;
}					t_label;


int         kol_sim(char *str, char c);
int         kol_sim_not(char *str, char c);
t_label     *add_label(char *str, t_label **label);
void        print_struct(t_label *label); //del
int         pars_name(char *line, t_chempion *ch, t_label **label);
int         pars_label(char *line, t_chempion *ch, t_label **label);
int         proverca_label(char *str);
void        zap_struct_ascii(t_chempion *ch, char *str, t_label **label);
char        *cut_one(char *str, char c, int n);

#endif