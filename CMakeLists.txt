cmake_minimum_required(VERSION 3.26)
project(semestral)
find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(semestral main.cpp
        src/CTile.h
        src/CMap.cpp
        src/CMap.h
        src/Point.cpp
        src/Point.h
        src/TileGenerator.cpp
        src/CTileConfig.h
        src/CTileConfig.cpp
        src/CTile.cpp)
