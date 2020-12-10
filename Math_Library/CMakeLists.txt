cmake_minimum_required(VERSION 3.8)
project(Math_Library)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ldl -g -fopenmp")


include_directories(
        ${GTEST_INCLUDE_DIRS}
)

add_executable(MathLib Factory.cpp Functions.cpp main.cpp)
target_link_libraries(MathLib ${GTEST_LIBRARIES} ${LIBS})

add_executable(TestMath Factory.cpp Functions.cpp GTest.cpp)
target_link_libraries(TestMath ${GTEST_LIBRARIES} ${LIBS})
enable_testing()
add_test(TestMath "./TestMath")