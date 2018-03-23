cmake_minimum_required(VERSION 3.8)
project(Vector)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Vector.h Vector.h Priority_Queue.h)
add_executable(Vector ${SOURCE_FILES})