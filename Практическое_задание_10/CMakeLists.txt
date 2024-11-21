cmake_minimum_required(VERSION 3.10)

project(Практическое_задание_10)

set(SOURCE_EXE main_task_4_for_5.c)

file(GLOB SOURCE_LIB "functions/*.c")

add_library(MY_LIB ${SOURCE_LIB})

add_executable(a.out ${SOURCE_EXE})

target_link_libraries(a.out MY_LIB)