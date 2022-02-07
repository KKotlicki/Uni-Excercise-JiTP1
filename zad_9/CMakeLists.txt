cmake_minimum_required(VERSION 3.21)
project(zad_9)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(.)

add_executable(zad_c9 vec_test.cpp vec.h error_messenger.h tst.h)
