cmake_minimum_required(VERSION 3.10)

project(lists)

set(CMAKE_BUILD_TYPE Debug) # debud mod
include_directories(${CMAKE_SOURCE_DIR}) # without ../header.h
include_directories("utils")

file(GLOB SOURCE_LIB "utils/*.c")

add_library(MY_LIB ${LIB_TYPE} ${SOURCE_LIB}) # STATIC or SHARED

add_executable(a.out main.c)

target_link_libraries(a.out MY_LIB)