cmake_minimum_required(VERSION 3.21)
project(zad_c15)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/TheVoyageoftheBeagle.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
include_directories(.)

add_executable(zad_c15 zad_c15.cpp word_counter.h)
