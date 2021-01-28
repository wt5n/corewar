NAME = corewar

CC = gcc

FLAG = -Wall -Wextra -Werror

FLAGINC = -I

PATH_LIB = ./libft/

HEARDS = inc/vm.h \
	inc/vm_op.h	\
	inc/op.h

CFILE = functions.c \
	cycle.c \
    operations.c \
    args.c \
    parse.c \
    main.c \
    init.c \
    checks.c \
    koretko_utils.c \
    errors.c \

OBG = functions.o \
   cycle.o \
   operations.o \
   args.o \
   parse.o \
   main.o \
   init.o \
   checks.o \
   koretko_utils.o \
   errors.o \

all: $(NAME)
$(NAME): $(OBG)
	make $(FLAG) -C $(PATH_LIB)
	$(CC) -I $(HEARDS) -o $(NAME) $(OBG) -L $(PATH_LIB) -lftprintf

%.o: %.c $(HEARDS)
	$(CC) $(FLAGINC) $(FLAG) -c $< -o $@

clean:
	make -C $(PATH_LIB) clean
	rm -f $(OBG)
	echo "\033[0;33mCleaned corewar\033[0m"

fclean: clean
	make -C $(PATH_LIB) fclean
	rm -f $(NAME)
	echo "\033[0;33mDeleted corewar\033[0m"

re: fclean all

.PHONY: make clean fclean re
