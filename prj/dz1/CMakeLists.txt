cmake_minimum_required(VERSION 3.0)

project(dz1)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(dz1 dz1.cpp)
target_link_libraries(dz1 ${OpenCV_LIBS})