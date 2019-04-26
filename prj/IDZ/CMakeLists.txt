cmake_minimum_required(VERSION 3.0)

project(IDZ)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(IDZ idz.cpp)
target_link_libraries(IDZ ${OpenCV_LIBS})