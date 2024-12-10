# Задание: Создать библиотеку pipes из read_pipe.c write_pipe.c
cmake_minimum_required(VERSION 3.10)

project(pipes)

# set(SOURCES read_pipe.c write_pipe.c)
file(GLOB SOURCES "*.c")

add_library(pipes ${SOURCES})