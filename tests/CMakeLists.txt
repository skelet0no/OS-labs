include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 17)

add_executable(tests test1.cpp)

# target_link_libraries(test1 PRIVATE GTest::GTest)
# target_include_directories(test1 PRIVATE ../laba1)

add_test(test1 test1)
