cmake_minimum_required(VERSION 3.2)
project(Treap)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB ${CMAKE_SOURCE_DIR}/library/treap.hpp)

set(MAIN_SOURCE ${CMAKE_SOURCE_DIR}/main.cpp)
set(TEST_SOURCE ${CMAKE_SOURCE_DIR}/main_test.cpp)

include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)

# Config with tests, sanitizers and other kinda debug stuff
add_executable(test_treap ${LIB} ${TEST_SOURCE})
target_compile_options(test_treap PRIVATE -Wall -Wextra -Werror -fsanitize=undefined)
target_link_options(test_treap PRIVATE -fsanitize=undefined)
target_link_libraries(test_treap PRIVATE gtest pthread)

# Config without tests and sanitizers
add_executable(treap_main ${LIB} ${MAIN_SOURCE})
