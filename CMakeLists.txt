cmake_minimum_required(VERSION 3.2)
project(Lucrarea3)

#C++ standrad
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#header for .cpp files
include_directories(inc)

set(SOURCES
    src/main.cpp
    src/Buffer.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})