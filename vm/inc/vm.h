#ifndef VM_H
# define VM_H

#include "../libft/inc/printf.h"
#include "op.h"
#include "vm_op.h"

#define MAGIC_NUMBER_LENGTH 4

typedef struct	s_champ
{
	int 		number;
	char		*name;
	int 		code_size;
	char		*comm;
	unsigned char *code;
	int 		live_cycle;
	int 		lives_num;
}				t_champ;

typedef struct	s_koretko
{
	int 		id;
	int 		carry;
	int 		position;
	int			num_live_circle;
	int			last_alive;
	int			delay;
	int			step;
	int			regs[REG_NUMBER];
	int 		args[3];
	int 		op_code;
	int			parent_id;
	int 		ind_adrs;
	struct s_koretko	*next;
}				t_koretko;

typedef struct		s_cw
{
	t_champ			**champs;
	unsigned char	*map;
	int				num_of_champ;
	int				num_of_koretko;
	int				cycles;
	int 			last_player;
	int 			num_of_lives;
	int 			cycles_to_die;
	int				cycles_to_check;
	int				num_of_checks;
	t_koretko 		*kors;
}					t_cw;

void 	ft_swap_two_let(char *str);
void	ft_print_memory(const void *addr, size_t size);
void 	circle(t_cw *cw);
int		is_reg(t_cw *cw, t_koretko *koretko);
int		get_adrs(t_koretko *koretko, int modif);
int		is_dir(t_cw *cw, t_koretko *koretko, int n);
t_koretko	*create_koretko(int id, int position);
void	chain_kor(t_koretko **kors, t_koretko *kor);

#endif

//90 65 e2 42 fc 7f