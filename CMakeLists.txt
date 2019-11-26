cmake_minimum_required(VERSION 2.8.11)
project(localiza C)

set(CMAKE_C_STANDARD 99)

include_directories(include)
file(GLOB SOURCES src/*.c src/helpers/*.c)

add_executable(localiza ${SOURCES})