#ifndef ASM_H
# define ASM_H

#include <stdio.h> //del

# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "op.h"

typedef struct	s_op
{
	char		*name; // 0
	int			arg; // 1
	int			reg[3]; // 2
	int			code_op; // 3
	int			neponatca; //4
	char		*poasny; //5
	int			code_type; // 6
	int			size; // 7
}				t_op;

extern t_op op_tab[17];

typedef struct				s_registr
{
	int						code;
	int						size;
}							t_registr;

typedef struct				s_op_strukt
{
	int						size;
	int						name;
	int						smechenee;
	char					*stroca;
	struct s_op_strukt		*next;
}							t_op_strukt;

typedef struct				s_chempion
{
	char					*name;
	char					*comment;
	char					*code;
	int						size;
	int						flag;
	int						flag_label;
	int						smehenee;
	int						mestnoe_smehenee;
	int						mestnoe_size;
	t_registr				reg[3];
}							t_chempion;

typedef struct				s_label
{
	char					*name;
	t_op_strukt				*op;
	struct s_label			*next;
}							t_label;

typedef struct				s_new_st_label
{
	t_label					*lab;
	int						smehenee;
	struct s_new_st_label	*next;
}							t_new_st_label;

int				kol_sim(char *str, char c);
int         	kol_sim_not(char *str, char c);
t_label			*add_label(char *str, t_label **label);
t_new_st_label	*add_st_label(char *str, t_new_st_label **label);
void        	print_struct(t_new_st_label *label); //del
void            print_op(t_op_strukt *op); //del
int         	pars_name(char *line, t_chempion *ch, t_new_st_label **label);
int         	pars_label(char *line, t_chempion *ch, t_new_st_label **label);
int         	proverca_label(char *str);
void        	zap_struct_ascii(t_chempion *ch, char *str, t_new_st_label **label);
char        	*cut_one(char *str, char c, int n);
void    		zap_operation(t_chempion *ch);
t_op_strukt		*add_op_struct(t_op_strukt **label);
void			zap_registr(t_chempion *ch);
int         	operation_name(char *srez, t_op_strukt **op);
int         	pars_operation(char *line, t_chempion *ch, t_op_strukt **op, t_new_st_label  **label);
void			trace_byte_code(t_chempion *ch, t_new_st_label *label, t_op_strukt *op);

t_op_strukt *operation_last(t_op_strukt **op);
t_new_st_label *label_last(t_new_st_label **label);

#endif