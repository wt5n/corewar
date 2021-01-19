#ifndef VM_H
# define VM_H

#include "../libft/inc/printf.h"
#include "op.h"
#include "vm_op.h"

#define MAGIC_NUMBER_LENGTH 4

typedef struct			s_champ
{
	int					number;
	char				*name;
	int					code_size;
	char				*comm;
	unsigned char		*code;
	int					live_cycle;
	int					lives_num;
}						t_champ;

typedef struct			s_koretko
{
	int					id;
	int					carry;
	int					position;
	int					num_live_cycle;
	int					last_alive;
	int					delay;
	int					step;
	int					regs[REG_NUMBER];
	int					args[3];
	int					op_code;
	int					parent_id;
	int					ind_adrs;
	struct s_koretko	*next;
}						t_koretko;

typedef struct			s_cw
{
	t_champ				*champs[MAX_PLAYERS];
	unsigned char	 	map[MEM_SIZE];
	int					num_of_champ;
	int					num_of_koretko;
	int					cycles;
	int 				last_player;
	int 				num_of_lives;
	int 				cycles_to_die;
	int					cycles_to_check;
	int					num_of_checks;
	t_koretko 			*kors;
}						t_cw;

void					ft_swap_two_let(char *str);
void					ft_print_memory(const void *addr, size_t size);


// args.c
int			get_adrs(t_koretko *koretko, int modif);
int			is_reg(t_cw *cw, t_koretko *koretko);
int			is_dir(t_cw *cw, t_koretko *koretko, int n);
int 		is_indir(t_cw *cw, t_koretko *koretko);
int			get_value(t_cw *cw, t_koretko *koretko, int arg);
void	write_value(t_cw *cw, int adrs, int value, int size);

// operations.c
void		op_live(t_cw *cw, t_koretko *kor);
void		op_ld(t_cw *cw, t_koretko *kor);
void		op_st(t_cw *cw, t_koretko *kor);
void		op_add(t_cw *cw, t_koretko *kor);
void		op_sub(t_cw *cw, t_koretko *kor);
void		op_and(t_cw *cw, t_koretko *kor);
void		op_or(t_cw *cw, t_koretko *kor);
void		op_xor(t_cw *cw, t_koretko *kor);
void		op_zjmp(t_cw *cw, t_koretko *kor);
void		op_ldi(t_cw *cw, t_koretko *kor);
void		op_sti(t_cw *cw, t_koretko *kor);
void		op_fork(t_cw *cw, t_koretko *kor);
void		op_lld(t_cw *cw, t_koretko *kor);
void		op_lldi(t_cw *cw, t_koretko *kor);
void		op_lfork(t_cw *cw, t_koretko *kor);
void		op_aff(t_cw *cw, t_koretko *kor);

// parse.c
void		read_magic_number(char *argv, int fd);
void		read_champ_name(int fd, t_champ *champ);
void		read_champ_code_size(int fd, t_champ *champ);
void		read_champ_comm(int fd, t_champ *champ);
void		read_champ_code(int fd, t_champ *champ);

// init.c
void		place_pl_and_kors(t_cw *cw);

// koretko_utils.c
t_koretko	*create_koretko(int id, int position);
void		delete_koretko(int id, t_koretko **kors);
void		chain_kor(t_koretko **kors, t_koretko *kor);

// checks.c
void		check_cycles(t_cw *cw);
void		wrong_args(t_koretko *kor);
int			is_correct_args(int i, int *ar, t_cw *cw, t_koretko *koretko);

// cycle.c
void		cycle(t_cw *cw);

#endif
