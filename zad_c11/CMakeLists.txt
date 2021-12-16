
cmake_minimum_required(VERSION 3.21)
project(zad_c11)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(.)

add_executable(zad_c11
        entry.h
        word_counter.h
        zad_11.cpp)

