cmake_minimum_required(VERSION 3.21)
project(snake)

set(CMAKE_CXX_STANDARD 20)


set(SOURCE_FILES main.cpp snake.cpp snake_map.cpp head.h)
add_executable(snake ${SOURCE_FILES})
