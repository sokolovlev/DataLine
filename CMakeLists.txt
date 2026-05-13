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
        ConfigClass.cpp
        ConfigClass.h
        #test.cpp
)

target_link_options(DataLine PRIVATE -static-libstdc++ -static-libgcc)
