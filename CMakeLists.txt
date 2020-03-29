cmake_minimum_required(VERSION 3.15)
project(Ragrep)

set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Wextra -pedantic -Werror)
add_executable(ragrep main.c)
