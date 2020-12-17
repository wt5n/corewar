#ifndef ASM_H
# define ASM_H

#include <stdio.h> //del

# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "op.h"

typedef struct			s_op_strukt
{
	int					size;
	int					name;
	struct s_op_strukt	*next;
}						t_op_strukt;

typedef struct		s_operation
{
	char			*name;
	int				code;
	int				kol_argument;
	int				registr;
	int				type_arg;
	int				size;
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
	struct s_label	*next;
}					t_label;

typedef struct				s_new_st_label
{
	t_label					*lab;
	struct s_new_st_label	*next;
}							t_new_st_label;

int				kol_sim(char *str, char c);
int         	kol_sim_not(char *str, char c);
t_label			*add_label(char *str, t_label **label);
t_new_st_label	*add_st_label(char *str, t_new_st_label **label);
void        	print_struct(t_new_st_label *label); //del
int         	pars_name(char *line, t_chempion *ch, t_new_st_label **label);
int         	pars_label(char *line, t_chempion *ch, t_new_st_label **label);
int         	proverca_label(char *str);
void        	zap_struct_ascii(t_chempion *ch, char *str, t_new_st_label **label);
char        	*cut_one(char *str, char c, int n);
void    		zap_operation(t_chempion *ch);
t_op_strukt    *add_op_struct(t_op_strukt **label);

#endif