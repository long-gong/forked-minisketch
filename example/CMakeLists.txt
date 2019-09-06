cmake_minimum_required(VERSION 3.0)

project(minisketch-example)

add_executable(minisketch_example example.cpp)
target_link_libraries(minisketch_example minisketch)