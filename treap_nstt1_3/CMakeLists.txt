set(CMAKE_MINIMUM_REQUIRED_VERSION 3.2)
project(Treap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_subdirectory("${CMAKE_SOURCE_DIR}/googletest" "googletest")

set(LIB ${CMAKE_SOURCE_DIR}/library/treap.cpp ${CMAKE_SOURCE_DIR}/library/treap.h)

set(MAIN_SOURCE ${CMAKE_SOURCE_DIR}/main.cpp)
set(TEST_SOURCE ${CMAKE_SOURCE_DIR}/main_test.cpp)

# Config with test env and 'TEST' define
add_executable(test_treap ${LIB} ${TEST_SOURCE})
target_compile_definitions(test_treap PRIVATE TEST)
target_compile_options(test_treap PRIVATE -Wall -Wextra -Werror -fsanitize=undefined)
target_link_options(test_treap PRIVATE -fsanitize=undefined)
target_link_libraries(test_treap PRIVATE gtest_main gmock_main)

# Config without tests and sanitizers and 'RELEASE' define
add_executable(treap_main ${LIB} ${MAIN_SOURCE})
target_compile_definitions(treap_main PRIVATE RELEASE)
