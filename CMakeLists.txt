cmake_minimum_required(VERSION 3.17)
project(simple_kniffel C)

set(CMAKE_C_STANDARD 99)

add_executable(simple_kniffel main.c kniffel.c kniffel.h player.c player.h)