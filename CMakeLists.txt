cmake_minimum_required(VERSION 3.20)
project(snake)

set(CMAKE_CXX_STANDARD 17)
include_directories(./src/include)

add_executable(snake  main.cpp snake.cpp snake_map.cpp)
