cmake_minimum_required(VERSION 3.8)
project(AVL)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES BinNode.h Main.cpp AVL.h)
add_executable(AVL ${SOURCE_FILES})