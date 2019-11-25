cmake_minimum_required(VERSION 2.8.11)
project(localiza C)

set(CMAKE_C_STANDARD 99)

#file(GLOB_RECURSE SOURCES src/*)

#add_executable(localiza ${SOURCES})
add_executable(localiza src/localiza.c src/localiza.h src/flags.c src/flags.h src/helpers/helpers.c src/helpers/helpers.h src/helpers/dstring.c src/helpers/dstring.h src/targets.c src/targets.h src/helpers/structs.h src/searchTerm.c src/searchTerm.h)