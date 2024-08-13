cmake_minimum_required(VERSION 3.16)
project(ex1_stavimn C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex1_stavimn
        cipher.c
        cipher.h
        main.c
        tests.c
        tests.h main2.cpp)
