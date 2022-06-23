cmake_minimum_required(VERSION 3.20)

project(MovieMaker)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ../build)

add_executable(MovieMaker main.cpp Image.cpp Image.h)

target_include_directories(MovieMaker PRIVATE libraries)