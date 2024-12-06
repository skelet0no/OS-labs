cmake_minimum_required(VERSION 3.10)

set(SubProjectName "laba4")

add_library(lib1 SHARED lib1.cpp
        lib1.h)

add_library(lib2 SHARED lib2.cpp
        lib2.h)

add_executable(laba4 main.cpp)
target_link_libraries(laba4 PRIVATE lib1 lib2)

add_executable(laba4_dynamic dynamicMain.cpp)

#add_executable(laba4_tests tests/test.cpp)
#target_link_libraries(laba4_tests PRIVATE lib gtest_main)
#
#enable_testing()
#add_test(NAME laba4_tests COMMAND LW2_test)