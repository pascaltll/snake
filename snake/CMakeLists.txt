cmake_minimum_required(VERSION 3.21)
project(snake)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

set(SOURCE_FILES scr/main.cpp scr/snake.cpp scr/snake_map.cpp)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
add_executable(snake ${SOURCE_FILES})
target_link_libraries(snake gtest gtest_main)
