cmake_minimum_required(VERSION 3.21)
project(snake)

set(CMAKE_CXX_STANDARD 20)


set(SOURCE_FILES main.cpp snake.cpp snake_map.cpp head.h)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
add_executable(snake ${SOURCE_FILES})
