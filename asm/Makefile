NAME = asm
INCLUDES = -I./libft/
CC = gcc
SRC =  asm.c dop_function.c str_label.c print_struct.c pars.c zap_operation.c
LIB_FT = ./libft/libft.a 
OBJ = $(patsubst %.c, %.o, $(SRC))
CFLAGS = -Wall -Werror -Wextra $(INCLUDES)

.PHONY: lib all clean fclean re

all:	$(NAME)

%.o: %.c asm.h
		$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(LIB_FT) $(OBJ)
		$(CC) -o $@ $(OBJ) -L./libft -lft

libft_a:
		$(MAKE) -C ./libft

$(LIB_FT): libft_a

clean:
		$(MAKE) -C ./libft/ clean
		rm -f $(OBJ)

fclean: clean
		$(MAKE) -C ./libft/ fclean
		rm -f $(NAME)

re: fclean $(NAME)