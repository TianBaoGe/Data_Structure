cmake_minimum_required(VERSION 3.8)
project(List)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES ListNode.h Main.cpp ListNode.cpp List.cpp List.h Student.h Function.h Function.cpp)
add_executable(List ${SOURCE_FILES})