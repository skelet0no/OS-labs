cmake_minimum_required(VERSION 3.10)

set(SubProjectName "laba3")

add_executable(laba3 main.cpp)

add_library(lib child.cpp child.h)

target_link_libraries(laba3 PRIVATE lib)

add_executable(laba3_tests tests/test.cpp)
target_link_libraries(laba3_tests PRIVATE lib gtest_main)

enable_testing()
add_test(NAME laba3_tests COMMAND LW3_test)
