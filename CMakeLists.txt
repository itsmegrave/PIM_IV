cmake_minimum_required(VERSION 3.10)
project(pim_iv C)

set(CMAKE_C_STANDARD 11)

add_executable(pim_iv
        main.c clearscr.h clearscr.c pausecmd.h pausecmd.c pausecmd.c)
