cmake_minimum_required(VERSION 3.12)
project(numpy LANGUAGES CXX)


set(CMAKE_BUILD_TYPE Release)

add_subdirectory(array)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC array)
target_compile_options(main PUBLIC -ffast-math -march=native)