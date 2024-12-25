cmake_minimum_required(VERSION 3.10)

set(SubProjectName "laba1")

add_executable(laba1 main.cpp)

add_executable(child child.cpp)

add_library(divider divider.cpp divider.h)

set_target_properties(constants PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(src PRIVATE utils constants)
target_link_libraries(laba1 PRIVATE utils constants src)
target_link_libraries(child PRIVATE utils constants)

add_dependencies(laba1 child)

add_executable(laba1_tests tests/test.cpp)
add_dependencies(laba1_tests child)
target_link_libraries(laba1_tests PRIVATE src utils gtest_main)

enable_testing()
add_test(NAME laba1_tests COMMAND LW1_test)