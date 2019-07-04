cmake_minimum_required(VERSION 3.0)

project(nibbler)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Core)
add_subdirectory(BlockRenderer)

add_executable(nibbler main.cpp)
target_link_libraries(nibbler PRIVATE Core)
target_include_directories(nibbler PRIVATE Core/include)
