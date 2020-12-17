cmake_minimum_required(VERSION 3.17)
project(Genetic_Algorithm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O5")

add_executable(Genetic_Algorithm main.cpp Genetic.cpp MainCycle.cpp)