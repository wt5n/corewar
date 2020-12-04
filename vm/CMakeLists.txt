cmake_minimum_required(VERSION 3.17)
project(corewar)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

set(SRC
        main.c)

add_executable(corewar
        ${SRC} )

add_subdirectory(libft)
target_link_libraries(corewar libft)