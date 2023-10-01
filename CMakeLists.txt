cmake_minimum_required(VERSION 3.26)
project(semestral)

set(CMAKE_CXX_STANDARD 20)

add_executable(semestral main.cpp
        src/Tile.cpp
        src/Tile.h
        src/Map.cpp
        src/Map.h)
