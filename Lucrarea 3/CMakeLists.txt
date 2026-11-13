cmake_minimum_required(VERSION 3.2) #versiunea minima required pe pc
project(Lucrarea3)

#C++ standrad 
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON) #compilator capabil pt C++14 required
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(inc) #pt a gasi fisierele header (Buffer.hpp)
set(SOURCES
    src/main.cpp
    src/Buffer.cpp
) #fisierele care vor fi compilate

add_executable(${PROJECT_NAME} ${SOURCES}) #programul final