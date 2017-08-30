cmake_minimum_required(VERSION 2.8)

project (SAD)
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(sad sad.cpp)
target_link_libraries(sad ${OpenCV_LIBS})
