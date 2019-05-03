cmake_minimum_required(VERSION 3.12)
project(zad1m)

set(CMAKE_CXX_STANDARD 17)

add_executable(zad1m zad1.cpp ../zad2/PriorityQueue.h ../zad2/graphs.h ../zad3/graphsMST.h ../zad3/UnionFind.h)