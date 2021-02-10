/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:01:55 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/24 16:13:04 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <stdio.h> //del
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "op.h"

typedef struct				s_op
{
	char					*name;
	int						arg;
	int						reg[3];
	int						code_op;
	int						neponatca;
	char					*poasny;
	int						code_type;
	int						size;
}							t_op;

extern						t_op op_tab[17];

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
	int						i;
	int						n;
	int						tu;
	int						fd;
	int						len_com;
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

int							kol_sim(char *str, char c);
int							kol_sim_not(char *str, char c);
t_label						*add_label(char *str, t_label **label);
t_new_st_label				*add_st_label(char *str, t_new_st_label **label);
void						print_struct(t_new_st_label *label); //del
void						print_op(t_op_strukt *op); //del
int							pars_name(char *line, t_chempion *ch);
int							par_l(char *line, t_chempion *ch, \
		t_new_st_label **label);
int							proverca_label(char *str);
void						zap_struct_ascii(t_chempion *ch, char *str, \
		t_new_st_label **label);
char						*cut_one(char *str, char c, int n);
void						zap_operation(t_chempion *ch);
t_op_strukt					*add_op_struct(t_op_strukt **label);
void						zap_registr(t_chempion *ch);
int							operation_name(char *srez, t_op_strukt **op);
int							pars_operation(char *line, t_chempion *ch, \
		t_op_strukt **op, t_new_st_label **label);
int							pars_one(char *line, t_chempion *ch, \
		t_new_st_label **label, t_op_strukt **op);
void						trace_byte_code(t_chempion *ch, \
		t_new_st_label *label, t_op_strukt *op);
int							propysc_probel(char *str);
int							number_pr(char *str);
int							write_code(char *name_file, t_chempion *ch);
int							pars_one(char *line, t_chempion *ch, \
		t_new_st_label **label, t_op_strukt **op);
t_op_strukt					*operation_last(t_op_strukt **op);
t_new_st_label				*label_last(t_new_st_label **label);
t_label						*new_add_label(char *str);
int							proverca_registr(char *srez, t_chempion *ch, \
		t_new_st_label *label, t_op_strukt *new_op);
int							proverca(char c);
int							ft_abs(int a);
void				proverca_registr3(char *srez, t_chempion *ch, \
		t_op_strukt *new_op);
int		lab_ch(char *str);
void    free_lab(t_new_st_label **label);
void    free_op_struct(t_op_strukt *op);

#endif
