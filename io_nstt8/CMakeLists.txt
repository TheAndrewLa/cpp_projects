cmake_minimum_required(VERSION 3.2)
project(BasicIO)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

file(GLOB LIBRARY ${PROJECT_SOURCE_DIR}/library/*.cpp ${PROJECT_SOURCE_DIR}/library/*.hpp)
add_executable(release ${PROJECT_SOURCE_DIR}/main.cpp ${LIBRARY})
