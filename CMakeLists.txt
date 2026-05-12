cmake_minimum_required(VERSION 4.0)
project(DataLine)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataLine main.cpp
        SeparatorClass.cpp
        SeparatorClass.h
        setLimit.h

        ManagerClass.cpp
        ManagerClass.h

        MergeSortedClass.cpp
        MergeSortedClass.h
        ParametersClass.cpp
        ParametersClass.h
)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/input)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tech)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)