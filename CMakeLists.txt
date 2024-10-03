cmake_minimum_required(VERSION 3.28)
project(tracker_tester_cpp)

set(OpenCV_DIR /home/pardusumsu/code/opencv-4.10.0/build)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(tracker_tester_cpp main.cpp
        trackers.cpp
        trackers.h)

target_link_libraries(tracker_tester_cpp ${OpenCV_LIBS})
