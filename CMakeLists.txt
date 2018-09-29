cmake_minimum_required(VERSION 2.8)
project(cifar-10_reader_demo)
add_definitions(-std=c++11)

find_package(OpenCV REQUIRED)
link_directories(${OpenCV_LIBRARY_DIRS})
include_directories(.)

add_library(cifar-10_reader
    cifar-10_reader/cifar-10_reader.cpp)

add_executable(cifar-10_reader_demo
    demo.cpp)
target_link_libraries(cifar-10_reader_demo
    cifar-10_reader
    ${OpenCV_LIBS})
