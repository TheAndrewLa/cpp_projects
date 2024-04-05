cmake_minimum_required(VERSION 3.2)
project(SquareMatrix)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB ${CMAKE_SOURCE_DIR}/library/matrix.h ${CMAKE_SOURCE_DIR}/library/matrix.cpp)

set(MAIN_SOURCE ${CMAKE_SOURCE_DIR}/main.cpp)
set(TEST_SOURCE ${CMAKE_SOURCE_DIR}/main_test.cpp)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)

# Config with test and other shit
add_executable(test_matrix ${LIB} ${TEST_SOURCE})
target_compile_options(test_matrix PRIVATE -Wall -Wextra -Werror -fsanitize=undefined)
target_link_options(test_matrix PRIVATE -fsanitize=undefined -pthread)
target_link_libraries(test_matrix PRIVATE gtest pthread)

# Config without tests and sanitizers
add_executable(main_matrix ${LIB} ${MAIN_SOURCE})
