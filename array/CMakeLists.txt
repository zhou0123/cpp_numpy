add_library(array STATIC array.cpp)


set(CMAKE_BUILD_TYPE Release)

find_library(OpenMP REQUIRED)
target_include_directories(array PUBLIC .)

target_link_libraries(array PUBLIC OpenMP::OpenMP_CXX)
target_compile_options(array PUBLIC -ffast-math -march=native)
