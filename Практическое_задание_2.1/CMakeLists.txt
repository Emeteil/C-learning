cmake_minimum_required(VERSION 3.10)

project(sorts)

set(CMAKE_BUILD_TYPE Debug) # debud mod
include_directories(${CMAKE_SOURCE_DIR}) # without ../header.h

file(GLOB SOURCE_LIB "sorts/*.c")

add_library(MY_LIB ${SOURCE_LIB} funcs.c)

add_executable(a.out main.c)

target_link_libraries(a.out MY_LIB)