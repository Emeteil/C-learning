cmake_minimum_required(VERSION 3.10)

project(ConsoleSnack)

set(SOURCE_EXE main.c)

file(GLOB SOURCE_LIB "utils/*.c")

add_library(MY_LIB ${SOURCE_LIB})

add_executable(a.out ${SOURCE_EXE})

target_link_libraries(a.out MY_LIB)