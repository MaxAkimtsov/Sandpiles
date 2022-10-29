cmake_minimum_required(VERSION 3.23)
project(Sandpile)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)

add_executable(Sandpile
        lib/BMP.cpp
        lib/BMP.h
        lib/SandpileGenerator.cpp
        lib/SandpileGenerator.h
        main.cpp)
