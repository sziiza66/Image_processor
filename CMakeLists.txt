cmake_minimum_required(VERSION 3.5)

project(ImageProcessor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Говорят, что это нелучшее решение, но так гораздо удобнее, по крайней мере в этом проекте
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(image_processor ${HEADERS} ${SOURCES})
