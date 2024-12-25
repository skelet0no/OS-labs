cmake_minimum_required(VERSION 3.10)

set(SubProjectName "laba2")

add_executable(laba2 main.cpp)

add_library(cards cards.cpp cards.h)

target_link_libraries(laba2 PRIVATE cards)

add_executable(laba2_tests tests/test.cpp)
target_link_libraries(laba2_tests PRIVATE cards gtest_main)

enable_testing()
add_test(NAME laba2_tests COMMAND LW2_test)