cmake_minimum_required(VERSION 3.10)

project(testing)

enable_testing()

set(CIPHER_SRC_DIR ${CMAKE_SOURCE_DIR}/cipher)
set(CIPHER_API_SRC_DIR ${CMAKE_SOURCE_DIR}/cipher_api)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Исходники с шифрованием
include_directories(${CIPHER_SRC_DIR})
add_subdirectory(${CIPHER_SRC_DIR})

# API к шифрам, которое необходимо протестировать
include_directories(${CIPHER_API_SRC_DIR})
add_subdirectory(${CIPHER_API_SRC_DIR})

# Здесь сами тесты
include_directories(${TEST_DIR})
add_subdirectory(${TEST_DIR})

add_executable(a.out app/example.c)
target_link_libraries(a.out cipher_api)

add_test(NAME my_tests COMMAND my_tests)