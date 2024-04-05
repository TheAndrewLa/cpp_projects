cmake_minimum_required(VERSION 3.2)
project(ScopedPointer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB ${CMAKE_SOURCE_DIR}/library/scoped_ptr.hpp)
set(MAIN_SOURCE ${CMAKE_SOURCE_DIR}/main.cpp)

# Config without tests and sanitizers
add_executable(sp_main ${LIB} ${MAIN_SOURCE})
