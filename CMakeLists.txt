cmake_minimum_required(VERSION 3.26)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
project(semestral)

set(CMAKE_CXX_STANDARD 20)

add_executable(semestral main.cpp
        src/CTile.h
        src/CMap.cpp
        src/CMap.h
        src/CPoint.cpp
        src/CPoint.h
        src/CTileGenerator.cpp
        src/CTileConfig.h
        src/CTileConfig.cpp
        src/CTile.cpp
        src/CImageConnector.h
        src/CImageConnector.cpp
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(semestral ${OpenCV_LIBS})