cmake_minimum_required(VERSION 3.16)

project(mortgage_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_library(mortgage src/mortgage.cpp)
target_include_directories(mortgage PUBLIC include)

if(BUILD_TESTING)
    find_package(GTest REQUIRED)

    add_executable(mortgage_tests tests/mortgage_test.cpp)
    target_link_libraries(mortgage_tests PRIVATE mortgage GTest::gtest_main)

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(mortgage PRIVATE -Wall -Wextra -Wpedantic -Werror)
        target_compile_options(mortgage_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()

    add_test(NAME mortgage_tests COMMAND mortgage_tests)
endif()