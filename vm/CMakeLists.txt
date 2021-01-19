cmake_minimum_required(VERSION 3.17)
project(corewar)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

set(SRC
        ft_print_memory.c
        functions.c
        cycle.c
        operations.c
        args.c
        parse.c
        main.c init.c checks.c koretko_utils.c)

add_executable(corewar ${SRC})

add_executable(test test.c
                ft_print_memory.c)

add_subdirectory(libft)
target_link_libraries(corewar libft)
target_link_libraries(test libft)