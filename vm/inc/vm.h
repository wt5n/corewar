#ifndef VM_H
# define VM_H

#include "../libft/inc/printf.h"
#include "op.h"

// #define CHAMP_NAME_LENGTH 4
#define MAGIC_NUMBER_LENGTH 4

// #define MAGIC_NUMBER 0xea83f3


typedef struct s_champ
{
	int number;
	char *name;
	int code_size;
	char *comm;
	char *code;
} t_champ;

typedef struct s_cw
{
	t_champ **champs;
	char	*map;
}				t_cw;

void 	ft_swap_two_let(char *str);

#endif

//90 65 e2 42 fc 7f