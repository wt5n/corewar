NAME = libftprintf.a

SRC1 = add_func.c \
       adv_itoa.c \
       ap_arith.c \
       ft_printf.c \
       handling_f.c \
       handling_lf.c \
       nulz.c \
       parsing.c \
       type_b.c \
       type_c.c \
       type_di.c \
       type_di_add.c \
       type_f.c \
       type_f_add.c \
       type_o.c \
       type_other.c \
       type_p.c \
       type_s.c \
       type_u.c \
       type_x.c

OBJ1 = add_func.o \
       adv_itoa.o \
       ap_arith.o \
       ft_printf.o \
       handling_f.o \
       handling_lf.o \
       nulz.o \
       parsing.o \
       type_b.o \
       type_c.o \
       type_di.o \
       type_di_add.o \
       type_f.o \
       type_f_add.o \
       type_o.o \
       type_other.o \
       type_p.o \
       type_s.o \
       type_u.o \
       type_x.o

HDR = ./inc/
LIBFT = libft/
FLAGS = -Wall -Wextra -Werror
LIBFTO = ./libft/*.o

all: $(NAME)

$(NAME): $(OBJ1) $(SRC1) $(LIBFT) $(HDR)
	make -C $(LIBFT)
	ar rc $(NAME) $(OBJ1) $(LIBFTO)

%.o:%.c
	gcc -c -Wall -Wextra -Werror -I$(HDR) $<

clean:
	rm -rf $(OBJ1)
	make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re