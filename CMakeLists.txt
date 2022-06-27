cmake_minimum_required(VERSION 3.20)

project(MovieMaker)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ../build)

add_executable(MovieMaker main.cpp Image.cpp Image.h Algorithm.h FlipHorizontally.cpp FlipHorizontally.h FlipVertically.cpp FlipVertically.h InvertColors.cpp InvertColors.h Frame.cpp Frame.h Movie.cpp Movie.h Interpolation.cpp Interpolation.h ReduceColors.cpp ReduceColors.h)

target_include_directories(MovieMaker PRIVATE libraries)