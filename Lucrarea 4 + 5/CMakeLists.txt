cmake_minimum_required(VERSION 3.2)   # versiunea minima de CMake

project(Lucrarea45)                # numele proiectului

set(CMAKE_CXX_STANDARD 14)            # cerem C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)   # CMake verifica ca exista compilatorul potrivit
set(CMAKE_CXX_EXTENSIONS OFF)         # -std=c++14 in loc de -std=gnu++14

# Warning-uri utile (unele sunt INTENTIONATE: Item 4 si Item 12)
add_compile_options(-Wall -Wextra)

# headerele se gasesc in folderul inc
include_directories(inc)

set(myfiles
    src/main.cpp
    src/lucrare4.cpp
    src/lucrare5.cpp
    inc/common.hpp
    inc/lucrare4.hpp
    inc/lucrare5.hpp)

add_executable(${PROJECT_NAME} ${myfiles})