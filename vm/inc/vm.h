#ifndef VM_H
# define VM_H

#include "../libft/inc/printf.h"
#include "op.h"

#define MAGIC_NUMBER_LENGTH 4


typedef struct  s_reg
{
	int		r1;
	int		r2;
	int		r3;
	int		r4;
	int		r5;
	int		r6;
	int		r7;
	int		r8;
	int		r9;
	int		r10;
	int		r11;
	int		r12;
	int		r13;
	int		r14;
	int		r15;
	int		r16;
}				t_reg;

typedef struct s_champ
{
	int 		number;
	char		*name;
	int 		code_size;
	char		*comm;
	unsigned char *code;
}				t_champ;

typedef struct	s_koretko
{
	int 		id;
	int 		carry;
	int 		position;
	int			num_live_circle;
	int			delay;
	int			step;
	t_reg		*regs;
	int			parent_id;
	struct s_koretko	*next;
}				t_koretko;

typedef struct		s_cw
{
	t_champ			**champs;
	unsigned char	*map;
	int				num_of_champ;
	int				num_of_koretko;
	int				cycles;
	int 			last_alive;
	int 			num_of_lives;
	int 			cycles_to_die;
	int				num_of_check;
	t_koretko 		*kors;
}					t_cw;

void 	ft_swap_two_let(char *str);
void	ft_print_memory(const void *addr, size_t size);
void 	circle(t_cw *cw);

#endif

//90 65 e2 42 fc 7f