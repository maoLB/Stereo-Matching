cmake_minimum_required(VERSION 2.8)

#  SAD
# project(SAD)

# find_package(OpenCV REQUIRED)

# include_directories(${OpenCV_INCLUDE_DIRS})

# add_executable(SAD SAD.cpp)
# target_link_libraries(SAD ${OpenCV_LIBS})


# DP
project(DP)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(DP DP.cpp)
target_link_libraries(DP ${OpenCV_LIBS})
