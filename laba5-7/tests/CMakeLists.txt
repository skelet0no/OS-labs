cmake_minimum_required(VERSION 3.10)

project(MainTests)

set(CMAKE_CXX_STANDARD 17)

# Подключаем Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

include_directories(${ZMQ_INCLUDE_DIRS})

add_executable(MainTests tests.cpp)

# Линкуем с библиотеками Google Test
target_link_libraries(MainTests ${GTEST_LIBRARIES} pthread)
target_link_libraries(MainTests ${ZMQ_LIBRARIES} pthread)