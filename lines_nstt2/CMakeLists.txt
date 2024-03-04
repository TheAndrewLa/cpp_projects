cmake_minimum_required(VERSION 3.28)
project(Lines)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(LIB ${CMAKE_SOURCE_DIR}/library/lines.cpp ${CMAKE_SOURCE_DIR}/library/lines.h)

set(MAIN_SOURCE ${CMAKE_SOURCE_DIR}/main.cpp)
set(TEST_SOURCE ${CMAKE_SOURCE_DIR}/main_test.cpp)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)

# Config with test and other shit
add_executable(test_lines ${LIB} ${TEST_SOURCE})
target_compile_options(test_lines PRIVATE -Wall -Wextra -Werror -fsanitize=undefined)
target_link_options(test_lines PRIVATE -fsanitize=undefined -pthread)
target_link_libraries(test_lines PRIVATE gtest pthread)

# Config without tests and sanitizers
add_executable(main_lines ${LIB} ${MAIN_SOURCE})
