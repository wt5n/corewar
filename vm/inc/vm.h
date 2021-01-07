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
	t_reg		*regs;
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
	t_koretko 		**kors;
	int				*rgtrs;
}					t_cw;

void 	ft_swap_two_let(char *str);
void	ft_print_memory(const void *addr, size_t size);


#endif

//90 65 e2 42 fc 7f