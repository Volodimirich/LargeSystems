cmake_minimum_required(VERSION 3.8)

project(Simulated_annealing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread -O3")

#add_library(SolutionScheduling Solution/SolutionScheduling.h Solution/SolutionScheduling.cpp)
#add_library(MutationScheduling Mutation/MutationScheduling.h Mutation/MutationScheduling.cpp)
#add_library(XmlLibrary XmlLibrary/tinyxml2.cpp XmlLibrary/tinyxml2.h)

#include_directories(Solution)
include_directories(Mutation)
include_directories(Temperature)


add_executable(${PROJECT_NAME} main.cpp Temperature/Temperature.cpp Mutation/Mutation.cpp main.cpp Structures.h Temperature/Temperature.h Mutation/Mutation.h Simulating/Simulating.h Simulating/Simulating_parralel.h Generator/Generator_csv.cpp Generator/Generator_csv.h)
#target_link_libraries(${PROJECT_NAME} SolutionScheduling)
#target_link_libraries(${PROJECT_NAME} MutationScheduling)
