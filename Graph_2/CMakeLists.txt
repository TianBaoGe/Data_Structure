cmake_minimum_required(VERSION 3.8)
project(Graph_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Graph.h Vertex.h Edge.h UFSets.h MSTEdge.h)
add_executable(Graph_2 ${SOURCE_FILES})