# Здесь собрать тесты
cmake_minimum_required(VERSION 3.10)

project(my_tests)

find_library(CUNIT_LIBRARY NAMES cunit)
add_executable(my_tests test_algorithm.c)
target_link_libraries(my_tests ${CUNIT_LIBRARY})
target_link_libraries(my_tests cipher_api)

# add_test(NAME my_tests COMMAND my_tests)