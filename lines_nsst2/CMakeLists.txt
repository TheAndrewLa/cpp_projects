set(CMAKE_MINIMUM_REQUIRED_VERSION 3.2)
project(Lines)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_subdirectory("${CMAKE_SOURCE_DIR}/googletest" "googletest")

set(LIB ${CMAKE_SOURCE_DIR}/library/lines.cpp ${CMAKE_SOURCE_DIR}/library/lines.h)

set(MAIN_SOURCE ${CMAKE_SOURCE_DIR}/main.cpp)
set(TEST_SOURCE ${CMAKE_SOURCE_DIR}/main_test.cpp)

# Config with test and 'TEST' define
add_executable(test_lines ${LIB} ${TEST_SOURCE})
target_compile_definitions(test_lines PRIVATE TEST)
target_compile_options(test_lines PRIVATE -Wall -Wextra -Werror -pedantic -fsanitize=undefined)
target_link_options(test_lines PRIVATE -fsanitize=undefined)
target_link_libraries(test_lines PRIVATE gtest_main gmock_main)

# Config without tests and sanitizers and 'RELEASE' define
add_executable(main_lines ${LIB} ${MAIN_SOURCE})
target_compile_definitions(main_lines PRIVATE RELEASE)
