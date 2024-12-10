# Задание: Создать библиотеку из background.c и слинковать ее с библиотекой pipes
cmake_minimum_required(VERSION 3.10)

project(background)

add_library(background background.c)

include_directories("../pipes")

target_link_libraries(background pipes)