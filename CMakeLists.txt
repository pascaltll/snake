cmake_minimum_required(VERSION 3.21)
project(snake)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES scr/main.cpp scr/snake.cpp scr/snake_map.cpp scr/game.cpp)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
add_executable(snake ${SOURCE_FILES})







