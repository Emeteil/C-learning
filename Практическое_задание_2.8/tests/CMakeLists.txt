cmake_minimum_required(VERSION 3.10)
project(my_tests)

enable_testing()

find_library(CUNIT_LIBRARY NAMES cunit)
add_executable(my_tests test_functions.c ../functions.c)
target_link_libraries(my_tests ${CUNIT_LIBRARY})

add_test(NAME my_tests COMMAND my_tests)