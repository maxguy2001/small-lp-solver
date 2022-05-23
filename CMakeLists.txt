cmake_minimum_required(VERSION 3.22.0)

set(CMAKE_CXX_COMPILER clang++-12)

project(lp)

add_executable(${PROJECT_NAME} main.cpp main.hpp)
add_executable(test test.cpp test.hpp)

add_subdirectory(solvers)
add_subdirectory(utils)

target_link_libraries(${PROJECT_NAME} solvers utils)
target_link_libraries(test solvers utils)
