cmake_minimum_required(VERSION 3.20)
project(assignment)

set(CMAKE_CXX_STANDARD 17)

add_executable(assignment main.cpp drawing.h Canvas.cpp Shape.cpp Figures/Figures.h Figures/Circle.h Figures/Circle.cpp
        Figures/Rectangle.h Figures/Rectangle.cpp Figures/Triangle.h Figures/Triangle.cpp)
