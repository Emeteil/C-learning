cmake_minimum_required(VERSION 3.10)
project(translator)

add_compile_options(-Wall -pedantic -finput-charset=UTF-8 -fexec-charset=UTF-8)

find_package(CURL REQUIRED)

find_path(JANSSON_INCLUDE_DIR jansson.h)
find_library(JANSSON_LIBRARY NAMES jansson)

if(JANSSON_INCLUDE_DIR AND JANSSON_LIBRARY)
    set(JANSSON_FOUND TRUE)
    set(JANSSON_INCLUDE_DIRS ${JANSSON_INCLUDE_DIR})
    set(JANSSON_LIBRARIES ${JANSSON_LIBRARY})
endif()

add_executable(translate
    main.c
    utils/hash_table.c
    utils/args_processing.c
    utils/file_processing.c
    utils/translation.c
    utils/internet_search.c
)

target_include_directories(translate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${JANSSON_INCLUDE_DIRS})

target_link_libraries(translate ${CURL_LIBRARIES} ${JANSSON_LIBRARIES} pthread)

find_library(CUNIT_LIBRARY NAMES cunit)
add_executable(test_hash_table
    tests/test_hash_table.c
    utils/hash_table.c
    utils/args_processing.c
    utils/file_processing.c
    utils/translation.c
    utils/internet_search.c
)

target_include_directories(test_hash_table PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${JANSSON_INCLUDE_DIRS})

target_link_libraries(test_hash_table ${CUNIT_LIBRARY} ${CURL_LIBRARIES} ${JANSSON_LIBRARIES} pthread)

add_executable(test_translation
    tests/test_translation.c
    utils/hash_table.c
    utils/args_processing.c
    utils/file_processing.c
    utils/translation.c
    utils/internet_search.c
)

target_include_directories(test_translation PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${JANSSON_INCLUDE_DIRS})

target_link_libraries(test_translation ${CUNIT_LIBRARY} ${CURL_LIBRARIES} ${JANSSON_LIBRARIES} pthread)

enable_testing()
add_test(NAME hash_table_test COMMAND test_hash_table)
add_test(NAME translation_test COMMAND test_translation)