# CMakeList.txt : CMake project for CPPBallFind, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(CPPBallFind)
set(CMAKE_CXX_STANDARD 17)
find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS})

# Add source to this project's executable.
add_executable (CPPBallFind "CPPBallFind.cpp" "CPPBallFind.h" "shapes_finder.cpp" "shapes_finder.h" "img_mod.h" "img_mod.cpp" "logic_loop.cpp")

# TODO: Add tests and install targets if needed.
target_link_libraries( CPPBallFind ${OpenCV_LIBS})
