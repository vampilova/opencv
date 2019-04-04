cmake_minimum_required(VERSION 3.0)

project(kr)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(kr kr.cpp)
target_link_libraries(kr ${OpenCV_LIBS})