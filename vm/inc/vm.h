#ifndef VM_H
# define VM_H

#include "../libft/inc/printf.h"
#include "op.h"

#define MAGIC_NUMBER_LENGTH 4


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
}				t_koretko;

typedef struct		s_cw
{
	t_champ			**champs;
	unsigned char	*map;
	int				num_of_champ;
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