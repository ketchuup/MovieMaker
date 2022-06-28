cmake_minimum_required(VERSION 3.20)

project(MovieMaker)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ../build)

set(YAMI4 ${CMAKE_CURRENT_SOURCE_DIR}/libraries/yami4-cpp/yamicpp-debug.lib ${CMAKE_CURRENT_SOURCE_DIR}/libraries/yami4-core/yamicore-debug.lib)

if (${MSVC})
	link_libraries(ws2_32.lib Winmm.lib)
endif()

add_executable(Server Server.cpp Image.cpp Image.h Algorithm.h FlipHorizontally.cpp FlipHorizontally.h FlipVertically.cpp FlipVertically.h InvertColors.cpp InvertColors.h Frame.cpp Frame.h Movie.cpp Movie.h Interpolation.h Identity.cpp Identity.h Linear.cpp Linear.h Logarithmic.cpp Logarithmic.h ReduceColors.cpp ReduceColors.h Saver.h FileSaver.cpp FileSaver.h ReplySaver.cpp ReplySaver.h)
target_link_libraries(Server ${YAMI4})
target_include_directories(Server PRIVATE libraries)

add_executable(Client Client.cpp Image.cpp Image.h)
target_link_libraries(Client ${YAMI4})
target_include_directories(Client PRIVATE libraries)