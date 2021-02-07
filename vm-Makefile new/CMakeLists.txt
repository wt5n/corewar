cmake_minimum_required(VERSION 3.17)
project(corewar)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

set(SRC
        functions.c
        cycle.c
        operations.c
        args.c
        parse.c
        main.c
        init.c
        checks.c
        koretko_utils.c
        errors.c utils.c operations2.c operations3.c)

add_executable(corewar ${SRC})

add_subdirectory(libft)
target_link_libraries(corewar libft)