NAME = corewar

CC = gcc

FLAG = -Wall -Wextra

FLAGINC = -I

PATH_LIB = ./libft/

HEARDS = inc/

CFILE = functions.c \
	cycle.c \
    operations.c \
    operations2.c \
    operations3.c \
    utils.c \
    args.c \
    parse.c \
    main.c \
    init.c \
    checks.c \
    koretko_utils.c \
    errors.c \
    vis.c

OBG = functions.o \
   cycle.o \
   operations.o \
   operations2.o \
   operations3.o \
   utils.o \
   args.o \
   parse.o \
   main.o \
   init.o \
   checks.o \
   koretko_utils.o \
   errors.o \
   vis.o

all: $(NAME)
$(NAME): $(OBG)
	@make -s $(FLAG) -C $(PATH_LIB)
	@$(CC)  -g -I $(HEARDS) -o $(NAME) $(OBG) -L $(PATH_LIB) -lftprintf -L lib -lSDL2 -lSDL2_ttf
	@echo "\033[0;36m*** Corwar has compiled. Let the combat begin! *** \033[0m"

%.o: %.c $(HEARDS)
	@$(CC) $(FLAGINC) $(FLAG) -c $< -o $@

clean:
	@make -s -C $(PATH_LIB) clean
	@rm -rf $(OBG)
	@echo "\033[0;35m*** Object files has cleaned *** \033[0m"

fclean: clean
	@make -s -C $(PATH_LIB) fclean
	@rm -rf $(NAME)
	@echo "\033[0;31m*** Corewar has removed *** \033[0m"

re: fclean all

.PHONY: make clean fclean re
