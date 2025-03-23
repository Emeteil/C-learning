cmake_minimum_required(VERSION 3.10)

project(binary_files)

set(CMAKE_BUILD_TYPE Debug) # debud mod
include_directories(${CMAKE_SOURCE_DIR}) # without ../header.h
include_directories("utils")

file(GLOB SOURCE_LIB "utils/*.c")

add_library(MY_LIB ${SOURCE_LIB})

add_executable(a.out main.c)

target_link_libraries(a.out MY_LIB)